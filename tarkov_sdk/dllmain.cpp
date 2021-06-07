#include "includes.hpp"

auto on_startup( ) -> void
{
	AllocConsole( );
	freopen_s( reinterpret_cast< FILE** >( stdout ), "CONOUT$", "w", stdout );
	SetConsoleTitleA( "[occult] sdk" );

	mono_lib::setup( "Assembly-CSharp" ); // setup mono library on game assembly.
	//mono_lib::dump_fields( "EFT", "Player" ); used for dumping/debugging certain classes

	const auto unity_base = process::memory::get_module_base( L"UnityPlayer.dll" );

	const auto game_object_manager = *reinterpret_cast< uintptr_t* >( unity_base + engine::static_offsets::game_object_manager );

	const auto active_objects = *reinterpret_cast< std::array<uint64_t, 2>* >( game_object_manager + offsetof( engine::game_object_manager, last_active ) ); // last active object
	const auto game_world_object = engine::game_objects::get_from_list( active_objects[ 1 ], active_objects[ 0 ], "GameWorld" );

	const auto game_world = ( c_game_world* ) process::memory::read_chain( game_world_object, { 0x30, 0x18, 0x28 } );

	int player_count = game_world->get_player_count( );
	printf( "[~] players: %i\n", player_count );

	for ( int idx = 0; idx < game_world->get_player_count( ); idx++ )
	{
		const auto player = *reinterpret_cast< c_player** >( uint64_t( game_world->get_players( ) + 0x10 ) + ( 0x20 + ( idx * 8 ) ) );

		if ( !player )
			continue;

		if ( !engine::local_player )
		{
			if ( player->is_local( ) )
			{
				engine::local_player = player;
				printf( "[~] found local player\n" );
			}
		}
	}

	return;
}

auto __stdcall DllMain( void*, std::uint32_t call_reason, void* ) -> bool
{
	if ( call_reason != DLL_PROCESS_ATTACH )
		return false;

	on_startup( );

	return true;
}