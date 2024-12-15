#pragma once
#include "Zydis/Zydis.h"

namespace shared::zydis
{
	void init();

	ZydisDecodedInstruction decode( address_t RIP );
}