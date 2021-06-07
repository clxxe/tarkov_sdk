#pragma once
#include "includes.hpp"

class c_player
{
public:
	auto is_local( ) -> bool
	{
		return *reinterpret_cast< bool* >( this + 0x18 );
	}
};