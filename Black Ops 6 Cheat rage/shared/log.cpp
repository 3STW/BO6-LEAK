#include "../shared.hpp"

#include "../fmt/chrono.hpp"

typedef struct _RTL_USER_PROCESS_PARAMETERSS
{
	ULONG MaximumLength;
	ULONG Length;

	ULONG Flags;
	ULONG DebugFlags;

	HANDLE ConsoleHandle;
};

namespace shared::log
{
	bool m_init = false;

	HANDLE m_handle = INVALID_HANDLE_VALUE;

	void print(const char* text)
	{
		/// Check if console was allocated yet
		if (!m_init)
		{
			/// Allocate console
			auto is_console_allocated = AllocConsole();
			auto is_console_attached = AttachConsole(GetCurrentProcessId());

			/// Redirect out/in to console
			freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
			freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

			SetConsoleTitleA("gmod_modest console");

			m_init = is_console_allocated && is_console_attached;
		}

		/// Print text
		fmt::print("[{:%H:%M:%S}] - {} \n", fmt::localtime(std::time(nullptr)), text);
	}

	/// Wrapper for string objects
	void print(const std::string& text)
	{
		print(text.c_str());
	}

	void print_file(const char* text)
	{
#ifdef _DEBUG
		/// Open handle to file
		std::ofstream file("C:\\log.txt", std::ios::app);
#else
		/// Open handle to file
		std::ofstream file(fmt::format(XOR("C:\\{}.txt"), misc::generate_unique_random_string(CT_HASH("log"), 20), std::ios::app));
#endif
		if (!file.is_open())
			return;

		/// Print text
		file << text << std::endl;

		/// Close file handle
		file.close();
	}

	/// Wrapper for string objects
	void print_file(const std::string& text)
	{
		print_file(text.c_str());
	}

	void detach()
	{
		/// Sanity check
		if (!m_init)
			return;

		/// Close used handles first
		fclose(stdout);
		fclose(stdin);

		/// Now close the actual console
		FreeConsole();
		PostMessageW(GetConsoleWindow(), WM_CLOSE, 0, 0);
	}


	void  NotePad(const char* str, ...) {
		va_list ap;
		HWND notepad, edit;
		char buf[256];

		va_start(ap, str);
		vsprintf(buf, str, ap);
		va_end(ap);
		strcat(buf, "");

		notepad = FindWindow(NULL, ("Untitled - Notepad"));
		if (!notepad)
			notepad = FindWindow(NULL, ("*Untitled - Notepad"));

		edit = FindWindowEx(notepad, NULL, ("EDIT"), NULL);
		SendMessageA(edit, EM_REPLACESEL, 0, (LPARAM)buf);
	}
	void log_to_file(const char* str, ...)
	{
		va_list ap;
		char buf[256];

		va_start(ap, str);
		vsprintf(buf, str, ap);
		va_end(ap);
		strcat(buf, "\n");
		// this is skallers path... lol ik sm1 was lazy
		std::ofstream logFile("F:\\mw3cheat\\Build\\test.txt", std::ios::app);



		if (logFile.is_open()) {
			logFile << buf;
			logFile.close();
		}
		else {
			std::cerr << "Error opening log file." << std::endl;
		}
	}
}