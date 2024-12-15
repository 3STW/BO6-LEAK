#include "../shared.hpp"

namespace shared::zydis
{
	bool m_init = false;

	ZydisDecoder m_decoder;

	void init()
	{
		if ( m_init )
			return;

		ZydisDecoderInit( &m_decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64 );

		m_init = true;
	}

	ZydisDecodedInstruction decode( address_t RIP )
	{
		zydis::init();

		ZydisDecodedInstruction instruction;

		if ( ZYAN_SUCCESS( ZydisDecoderDecodeBuffer( &m_decoder, RIP.cast<void*>(), 20, &instruction ) ) )
			return instruction;

		return {};
	}
}