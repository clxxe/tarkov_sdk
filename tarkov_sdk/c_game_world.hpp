#pragma once
#include "includes.hpp"

class c_game_world
{
public:
	auto get_player_count( ) -> int
	{
		MONO_OFFSET( "EFT", "GameWorld", RegisteredPlayers );
		const auto players = *reinterpret_cast< uint64_t* >( this + RegisteredPlayers );
		return *reinterpret_cast< int* >( players + 0x18 );
	}

	auto get_players( ) -> uint64_t
	{
		MONO_OFFSET( "EFT", "GameWorld", RegisteredPlayers );
		return *reinterpret_cast< uint64_t* >( this + RegisteredPlayers );
	}
};