#include "includes.h"
#include "gangshit.h"
#include "skCrypter.h"
#include "hashes.hpp"
#include "FONT.h"
#include "font2.h"

namespace Settings
{
	ModernWarfare3_t mw3 = ModernWarfare3_t{};
	Client_t client = Client_t{};
	mem_t mem = mem_t{};
}

HWND wndproc = 0;

const char* GenerateRandomString(int length) {
	static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char* randomString = new char[length + 1];

	for (int i = 0; i < length; ++i) {
		randomString[i] = charset[rand() % (sizeof(charset) - 1)];
	}

	randomString[length] = '\0';

	return randomString;
}

template<typename T>
static void SafeRelease(T*& res) {
	if (res)
		res->Release();
	res = NULL;
}
extern  LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//https://github.com/ocornut/imgui/blob/master/examples/example_win32_directx12/main.cpp
struct FrameContext {
	CComPtr<ID3D12CommandAllocator> command_allocator = NULL;
	CComPtr<ID3D12Resource> main_render_target_resource = NULL;
	D3D12_CPU_DESCRIPTOR_HANDLE main_render_target_descriptor;
};

// Data
static std::vector<FrameContext> g_FrameContext;
static UINT						g_FrameBufferCount = 0;

static CComPtr<ID3D12DescriptorHeap> g_pD3DRtvDescHeap = NULL;
static CComPtr<ID3D12DescriptorHeap> g_pD3DSrvDescHeap = NULL;
static CComPtr<ID3D12CommandQueue> g_pD3DCommandQueue = NULL;
static CComPtr<ID3D12GraphicsCommandList> g_pD3DCommandList = NULL;

LRESULT APIENTRY WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef long(__fastcall* Present) (IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
static Present OriginalPresent;

typedef void(*ExecuteCommandLists)(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists);
static ExecuteCommandLists OriginalExecuteCommandLists;

typedef long(__fastcall* ResizeBuffers)(IDXGISwapChain3* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
static ResizeBuffers OriginalResizeBuffers;

static WNDPROC OriginalWndProc;
static HWND Window = nullptr;
IDXGISwapChain3* g_pSwapChain;
static uint64_t* g_MethodsTable = NULL;
static bool g_Initialized = false;
bool init_hook = false;



LRESULT APIENTRY WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {



	if (msg == WM_KEYDOWN && wParam == VK_INSERT)
	{
		g_menu::b_menu_open = !g_menu::b_menu_open;
	}
	if (msg == WM_KEYDOWN && wParam == VK_HOME)
	{
		g_menu::b_menu_open = !g_menu::b_menu_open;
	}
	if (msg == WM_KEYDOWN && wParam == VK_F7)
	{
		g_menu::b_menu_open = !g_menu::b_menu_open;
	}

	if (g_Initialized) {

		if (g_menu::b_menu_open)
		{
			ImGuiIO& io = ImGui::GetIO();
			switch (msg) {
			case WM_LBUTTONDOWN:
				io.MouseDown[0] = true;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_LBUTTONUP:
				io.MouseDown[0] = false;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_RBUTTONDOWN:
				io.MouseDown[1] = true;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_RBUTTONUP:
				io.MouseDown[1] = false;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_MBUTTONDOWN:
				io.MouseDown[2] = true;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_MBUTTONUP:
				io.MouseDown[2] = false;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_MOUSEWHEEL:
				io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_MOUSEMOVE:
				io.MousePos.x = (signed short)(lParam);
				io.MousePos.y = (signed short)(lParam >> 16);
				return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_KEYDOWN:
				if (wParam < 256)
					io.KeysDown[wParam] = 1;
				return io.WantCaptureKeyboard ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_KEYUP:
				if (wParam < 256)
					io.KeysDown[wParam] = 0;
				return io.WantCaptureKeyboard ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			case WM_CHAR:
				// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
				if (wParam > 0 && wParam < 0x10000)
					io.AddInputCharacter((unsigned short)wParam);
				return io.WantCaptureKeyboard ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
			}
		}
		else
		{
			ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

		}





	}
	return CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
}


ImFont* icons;
ImFont* descriptionfont;

bool init_d3d12()
{

	if (g_Initialized)
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		return true;
	}


	if (!g_Initialized) {
		ID3D12Device* pD3DDevice;
		IDXGISwapChain3* pSwapChain = g_pSwapChain;
		if (FAILED(pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pD3DDevice))) {
			return false;
		}

		{
			DXGI_SWAP_CHAIN_DESC desc;
			pSwapChain->GetDesc(&desc);
			Window = desc.OutputWindow;
			if (!OriginalWndProc) {
				OriginalWndProc = (WNDPROC)SetWindowLongPtr(Window, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
			}
			g_FrameBufferCount = desc.BufferCount;
			g_FrameContext.clear();
			g_FrameContext.resize(g_FrameBufferCount);
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc = {};
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
			desc.NumDescriptors = g_FrameBufferCount;  // increase for textures
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

			if (pD3DDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pD3DSrvDescHeap)) != S_OK) {
				return false;
			}
		}

		{
			D3D12_DESCRIPTOR_HEAP_DESC desc;
			desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
			desc.NumDescriptors = g_FrameBufferCount;
			desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			desc.NodeMask = 1;

			if (pD3DDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pD3DRtvDescHeap)) != S_OK) {
				return false;
			}

			const auto rtvDescriptorSize = pD3DDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pD3DRtvDescHeap->GetCPUDescriptorHandleForHeapStart();

			for (UINT i = 0; i < g_FrameBufferCount; i++) {

				g_FrameContext[i].main_render_target_descriptor = rtvHandle;
				pSwapChain->GetBuffer(i, IID_PPV_ARGS(&g_FrameContext[i].main_render_target_resource));
				pD3DDevice->CreateRenderTargetView(g_FrameContext[i].main_render_target_resource, nullptr, rtvHandle);
				rtvHandle.ptr += rtvDescriptorSize;
			}

		}

		{
			ID3D12CommandAllocator* allocator;
			if (pD3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator)) != S_OK) {
				return false;
			}

			for (size_t i = 0; i < g_FrameBufferCount; i++) {
				if (pD3DDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_FrameContext[i].command_allocator)) != S_OK) {
					return false;
				}
			}

			if (pD3DDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_FrameContext[0].command_allocator, NULL, IID_PPV_ARGS(&g_pD3DCommandList)) != S_OK || g_pD3DCommandList->Close() != S_OK) {
				return false;
			}
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();




		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(Window);
		ImGui_ImplDX12_Init(pD3DDevice, g_FrameBufferCount,
			DXGI_FORMAT_R8G8B8A8_UNORM, g_pD3DSrvDescHeap,
			g_pD3DSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
			g_pD3DSrvDescHeap->GetGPUDescriptorHandleForHeapStart());


		ImGuiIO& io = ImGui::GetIO();

		ImFontConfig font_config;
		font_config.PixelSnapH = false;
		font_config.OversampleH = 5;
		font_config.OversampleV = 5;
		font_config.RasterizerMultiply = 1.2f;

		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin
			0x2010, 0x205E, // Punctuations
			0x0600, 0x06FF, // Farsi/Arabic
			0xFE00, 0xFEFF, // Farsi/Arabic
			0,
		};
		ImFontConfig cfg;
		cfg.FontDataOwnedByAtlas = false;
		g_menu::menu_font = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		g_menu::Regylar = io.Fonts->AddFontFromMemoryTTF(&Font1, sizeof Font1, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		g_menu::menu_font2 = io.Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		descriptionfont = io.Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());


		//g_menu::esp_font = io.Fonts->AddFontFromMemoryTTF(&NewESPFont, sizeof NewESPFont, 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

		ImFontConfig icons_config;
		mainfont = io.Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 21.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		titlefont = io.Fonts->AddFontFromMemoryTTF(&titlefonthxd, sizeof titlefonthxd, 26, NULL, io.Fonts->GetGlyphRangesCyrillic());
		icons = io.Fonts->AddFontFromMemoryTTF(&iconshxd2, sizeof iconshxd2, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
		//icons_smaller = io.Fonts->AddFontFromMemoryTTF(&iconshxd, sizeof iconshxd, 22, NULL, io.Fonts->GetGlyphRangesCyrillic());
		arrow = io.Fonts->AddFontFromMemoryTTF(&iconshxd, sizeof iconshxd, 15, NULL, io.Fonts->GetGlyphRangesCyrillic());
		icomoonfont = io.Fonts->AddFontFromMemoryTTF(&icomoon, sizeof icomoon, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());



		pD3DDevice->Release();
		g_Initialized = true;
	}

	return true;
}

void cache()
{
	if (!g_Initialized)
		return;

	ImGui::EndFrame();
	ImGui::Render();
}

void RenderBegin()
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
}

void frameBegin()
{
	if (g_Initialized)
	{
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

	}

}
void RenderEnd()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
}

namespace main_game
{
	void ui_header()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::Begin("##A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
	}

	void ui_end()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
	}
	bool b_panic = false;
	void init(ImFont* font)
	{

		ui_header();

		aimbot::StandardAim();
		visuals::draw2();

		ui_end();
	}
}

void hk_wow64_prepare_for_exception(PEXCEPTION_RECORD exception_record, PCONTEXT context)
{
	std::unique_lock< std::mutex > lock_think(hook_mutex);
	{
		if (*Settings::mem.DVARBOOL_cl_packetdup.cast<uintptr_t*>() != 0xDEADBEEFF) // 0xD34DB33F
		{
			orig = *Settings::mem.DVARBOOL_cl_packetdup.cast<uintptr_t*>();
			*Settings::mem.DVARBOOL_cl_packetdup.cast<uintptr_t*>() = 0xDEADBEEFF;
		}
	}
	lock_think.unlock();
	if (exception_record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && exception_record->ExceptionInformation[1] >= 0xDEADBEEFF && exception_record->ExceptionInformation[1] <= 0xDEADBEEFF + 0x1000)
	{
		for (uintptr_t* registry_value = &context->Rax; registry_value <= &context->R15; registry_value++)
		{
			const auto delta = *registry_value - 0xDEADBEEFF;
			if (delta > 0x1000)
				continue;

			*registry_value = orig + delta;
		}

		if (!init_hook)
		{
			init_d3d12();
			init_hook = true;
		}

		Settings::client.cg = Settings::client.cg;
		Settings::client.cl = GameFunction::CL::GetClActiveClient(game_struct::LocalClientNum_t::LOCAL_CLIENT_0);
		Settings::client.local_entity = Settings::client.cg ? Settings::client.cg->predictedPlayerEntity() : nullptr;
		Settings::client.cmd = Settings::client.cl ? Settings::client.cl->CL_GetUserCmd(Settings::client.cl->GetCmdNumber()) : nullptr;
		//Settings::client.ps = *Settings::mem.playerstate_P.ps_ptr.cast<game_struct::playerState_t**>();

		std::unique_lock<std::recursive_mutex> render_lock(render_hook);
		{
			frameBegin();
			g_menu::Menu();  // nigger u have it working how?
			main_game::init(g_menu::esp_font);
			cache();


		}
		render_lock.unlock();

		*(uintptr_t*)_AddressOfReturnAddress() += 0x12;

	}
}

char packet_test_hook(int a1, unsigned int a2)
{
	auto ret = VariadicCall<char>(packet_hook_orginal, a1, a2);

	if (!init_hook)
	{
		init_d3d12();
		init_hook = true;
	}

	Settings::client.cg = CG_GetLocalClientGlobals();
	Settings::client.cl = GameFunction::CL::GetClActiveClient(game_struct::LocalClientNum_t::LOCAL_CLIENT_0);
	Settings::client.local_entity = Settings::client.cg ? Settings::client.cg->predictedPlayerEntity() : nullptr;

	::D3D12::DrawCB([]() -> void {

		g_menu::Menu();
		visuals::draw2();

		if (Settings::Aimbot::enabled)
		{
			aimbot::StandardAim();
		}
		}
	);



	return ret;
}

void strcatf_custom(char* cText, char* format, ...)
{
	char sz[500] = { 0 };
	va_list va_alist;
	va_start(va_alist, format);
	_vsnprintf(sz, sizeof(sz), format, va_alist);
	va_end(va_alist);
	strcat(cText, sz);
}

static long __stdcall ExecHandle(struct _EXCEPTION_POINTERS* ExPointer)
{
	//PVOID start, end;
		//GetModuleMemoryRange(start, end);
	std::ofstream outputFile(XOR("C:\\MW3Chair\\exception_dump.txt"), std::ios::app);


	{
		char cCode[128] =
		{
			'\0'
		};
		switch (ExPointer->ExceptionRecord->ExceptionCode)
		{
		case EXCEPTION_ACCESS_VIOLATION:
			strcatf_custom(cCode, (char*)"0x%x ( EXCEPTION_ACCESS_VIOLATION )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			strcatf_custom(cCode, (char*)"0x%x ( EXCEPTION_ILLEGAL_INSTRUCTION )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			strcatf_custom(cCode, (char*)"0x%x ( EXCEPTION_INT_DIVIDE_BY_ZERO )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		case EXCEPTION_INT_OVERFLOW:
			strcatf_custom(cCode, (char*)"0x%x ( EXCEPTION_INT_OVERFLOW )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		case EXCEPTION_FLT_UNDERFLOW:
			strcatf_custom(cCode, (char*)"0x%x ( EXCEPTION_FLT_UNDERFLOW )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		case EXCEPTION_FLT_INEXACT_RESULT:
			strcatf_custom(cCode, (char*)"0x%x ( EXCEPTION_FLT_INEXACT_RESULT )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		default:
			strcatf_custom(cCode, (char*)"0x%x ( UNKNOW )\r\n", ExPointer->ExceptionRecord->ExceptionCode);
			break;
		}

		char cErrorString[1024] = { '\0' };

		sprintf
		(
			cErrorString,
			"<> Exception Handler <>\r\n\r\n"
			"Assembly Info :\r\n\r\n"
			"Exception At : 0x%08X\r\n"
			"Exception Code : %s\r\n",
			ExPointer->ContextRecord->Rip,
			cCode
		);


		outputFile << cErrorString << std::endl;;

		outputFile.close();
	}

	return 0;

}

void EnableHandler(void)
{
	SetUnhandledExceptionFilter(ExecHandle);
}






namespace D3D12 {





	uintptr_t original{};





	long __fastcall HookPresent(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags) {


		g_pSwapChain = address_t(*Settings::mem.swapchain.cast<uintptr_t*>()).cast<IDXGISwapChain3*>();
		g_pD3DCommandQueue = *reinterpret_cast<decltype(g_pD3DCommandQueue)*>(Settings::mem.commandqueue.cast());


		std::unique_lock< std::recursive_mutex > lock_render(render_hook);
		{
			if (g_Initialized)
			{
				FrameContext& currentFrameContext = g_FrameContext[pSwapChain->GetCurrentBackBufferIndex()];
				currentFrameContext.command_allocator->Reset();

				D3D12_RESOURCE_BARRIER barrier;
				barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
				barrier.Transition.pResource = currentFrameContext.main_render_target_resource;
				barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
				barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
				g_pD3DCommandList->Reset(currentFrameContext.command_allocator, nullptr);
				g_pD3DCommandList->ResourceBarrier(1, &barrier);
				g_pD3DCommandList->OMSetRenderTargets(1, &currentFrameContext.main_render_target_descriptor, FALSE, nullptr);
				g_pD3DCommandList->SetDescriptorHeaps(1, &g_pD3DSrvDescHeap);
				ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pD3DCommandList);
				barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
				barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
				g_pD3DCommandList->ResourceBarrier(1, &barrier);
				g_pD3DCommandList->Close();
				g_pD3DCommandQueue->ExecuteCommandLists(1, (ID3D12CommandList**)&g_pD3DCommandList);
			}

		}
		lock_render.unlock();



		return OriginalPresent(pSwapChain, SyncInterval, Flags);
	}





	void HookExecuteCommandLists(ID3D12CommandQueue* queue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists) {
		if (!g_pD3DCommandQueue) {
			g_pD3DCommandQueue = queue;
		}

		OriginalExecuteCommandLists(queue, NumCommandLists, ppCommandLists);
	}

	void ResetState() {

		if (g_Initialized) {
			g_Initialized = false;
			ImGui_ImplWin32_Shutdown();
			ImGui_ImplDX12_Shutdown();
			init_hook = false;
		}

		g_pD3DCommandQueue = nullptr;
		g_FrameContext.clear();
		g_pD3DCommandList = nullptr;
		g_pD3DRtvDescHeap = nullptr;
		g_pD3DSrvDescHeap = nullptr;



	}

	long HookResizeBuffers(IDXGISwapChain3* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{

		HRESULT ret = S_OK;


		ResetState();
		return  OriginalResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	}

	Status Initd3d12() {
		WNDCLASSEX windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = GenerateRandomString(7);
		windowClass.hIconSm = NULL;

		::RegisterClassEx(&windowClass);

		HWND window = ::CreateWindow(windowClass.lpszClassName, GenerateRandomString(9), WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

		HMODULE libDXGI;
		HMODULE libD3D12;

		if ((libDXGI = ::GetModuleHandle(XOR("dxgi.dll"))) == NULL) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::ModuleNotFoundError;
		}

		if ((libD3D12 = ::GetModuleHandle(XOR("d3d12.dll"))) == NULL) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::ModuleNotFoundError;
		}

		void* CreateDXGIFactory;
		if ((CreateDXGIFactory = ::GetProcAddress(libDXGI, XOR("CreateDXGIFactory"))) == NULL) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		CComPtr<IDXGIFactory> factory;
		if (((long(__stdcall*)(const IID&, void**))(CreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&factory) < 0) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		CComPtr<IDXGIAdapter> adapter;
		if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		void* D3D12CreateDevice;
		if ((D3D12CreateDevice = ::GetProcAddress(libD3D12, XOR("D3D12CreateDevice"))) == NULL) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		CComPtr<ID3D12Device> device;
		if (((long(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(adapter, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)&device) < 0) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 0;

		CComPtr<ID3D12CommandQueue> commandQueue;
		if (device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue) < 0) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		CComPtr<ID3D12CommandAllocator> commandAllocator;
		if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&commandAllocator) < 0) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		CComPtr<ID3D12GraphicsCommandList> commandList;
		if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList) < 0) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		CComPtr<IDXGISwapChain> swapChain;
		if (factory->CreateSwapChain(commandQueue, &swapChainDesc, &swapChain) < 0) {
			::DestroyWindow(window);
			::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
			return Status::UnknownError;
		}

		g_MethodsTable = (uint64_t*)::calloc(150, sizeof(uint64_t));
		::memcpy(g_MethodsTable, *(uint64_t**)(void*)device, 44 * sizeof(uint64_t));
		::memcpy(g_MethodsTable + 44, *(uint64_t**)(void*)commandQueue, 19 * sizeof(uint64_t));
		::memcpy(g_MethodsTable + 44 + 19, *(uint64_t**)(void*)commandAllocator, 9 * sizeof(uint64_t));
		::memcpy(g_MethodsTable + 44 + 19 + 9, *(uint64_t**)(void*)commandList, 60 * sizeof(uint64_t));
		::memcpy(g_MethodsTable + 44 + 19 + 9 + 60, *(uint64_t**)(void*)swapChain, 18 * sizeof(uint64_t));

		::DestroyWindow(window);
		::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		return Status::Success;
	}


	Status Hook(uint16_t _index, void** _original, void* _function) {
		void* target = (void*)g_MethodsTable[_index];
		if (MH_CreateHook(target, _function, _original) != MH_OK || MH_EnableHook(target) != MH_OK) {
			return Status::UnknownError;
		}
		return Status::Success;
	}

	Status Unhook(uint16_t _index, void** _original, void* _function) {
		void* target = (void*)g_MethodsTable[_index];
		MH_DisableHook(target);
		return Status::Success;
	}

	LRESULT APIENTRY WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		if (g_Initialized) {

			if (g_menu::b_menu_open)
			{
				ImGuiIO& io = ImGui::GetIO();
				switch (msg) {
				case WM_LBUTTONDOWN:
					io.MouseDown[0] = true;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_LBUTTONUP:
					io.MouseDown[0] = false;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_RBUTTONDOWN:
					io.MouseDown[1] = true;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_RBUTTONUP:
					io.MouseDown[1] = false;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_MBUTTONDOWN:
					io.MouseDown[2] = true;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_MBUTTONUP:
					io.MouseDown[2] = false;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_MOUSEWHEEL:
					io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_MOUSEMOVE:
					io.MousePos.x = (signed short)(lParam);
					io.MousePos.y = (signed short)(lParam >> 16);
					return io.WantCaptureMouse ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_KEYDOWN:
					if (wParam < 256)
						io.KeysDown[wParam] = 1;
					return io.WantCaptureKeyboard ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_KEYUP:
					if (wParam < 256)
						io.KeysDown[wParam] = 0;
					return io.WantCaptureKeyboard ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				case WM_CHAR:
					// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
					if (wParam > 0 && wParam < 0x10000)
						io.AddInputCharacter((unsigned short)wParam);
					return io.WantCaptureKeyboard ? 0 : CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
				}
			}
			else
			{
				ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

			}





		}
		return CallWindowProc(OriginalWndProc, hWnd, msg, wParam, lParam);
	}


	void DrawCB(const std::function<void(void)>& callback)
	{
		std::unique_lock<std::recursive_mutex> render_lock(render_hook);
		{
			init_d3d12();

			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
			ImGui::Begin(XOR("##A"), reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			ImGui::PopStyleVar();
			ImGui::PopStyleColor();
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			window->DrawList->PushClipRectFullScreen();
			{
				std::invoke(callback);
			}
			ImGui::End();
			cache();
		}
		render_lock.unlock();
	}

	Status InstallHooks() {

		Hook(140, (void**)&OriginalPresent, HookPresent);
		Hook(145, (void**)&OriginalResizeBuffers, HookResizeBuffers);
		return Status::Success;
	}

	Status RemoveHooks() {
		//Unhook(54, (void**)&OriginalExecuteCommandLists, HookExecuteCommandLists);
		Unhook(140, (void**)&OriginalPresent, HookPresent);
		Unhook(145, (void**)&OriginalResizeBuffers, HookResizeBuffers);

		if (Window && OriginalWndProc) {
			SetWindowLongPtr(Window, GWLP_WNDPROC, (__int3264)(LONG_PTR)OriginalWndProc);
		}

		ResetState();

		ImGui::DestroyContext();

		//wait for hooks to finish if in one. maybe not needed, but seemed more stable after adding it.
		Sleep(1000);
		return Status::Success;
	}
}