#pragma once
#include "includes.hpp"

namespace engine 
{
	c_player* local_player;

	namespace static_offsets 
	{
		constexpr uintptr_t game_object_manager = 0x0;
	}

	
	struct base_object
	{
		uint64_t previous_object;
		uint64_t next_object;
		uint64_t object;
	};

	struct game_object_manager
	{
		uint64_t last_tagged;
		uint64_t tagged_objects;
		uint64_t last_active;
		uint64_t active_objects;
	};

	namespace game_objects 
	{
		// thanks frankie11
		auto get_from_list( uint64_t list, uint64_t last_object, const char* object_name ) -> uint64_t
		{
			base_object active = *reinterpret_cast< base_object* >( list );
			base_object last = *reinterpret_cast< base_object* >( last_object );

			char name_buffer[ 256 ];
			uint64_t name_pointer = 0x0;

			if ( active.object != 0x0 )
			{
				while ( active.object != 0 && active.object != last.object )
				{
					name_pointer = *reinterpret_cast< uint64_t* >( active.object + 0x60 );
					memcpy( &name_buffer, ( void* ) ( name_pointer + 0x0 ), sizeof( name_buffer ) );
					if ( strcmp( name_buffer, object_name ) == 0 )
					{
						return active.object;
					}

					active = *reinterpret_cast< base_object* >( active.next_object );
				}
			}
			if ( last.object != 0x0 )
			{
				name_pointer = *reinterpret_cast< uint64_t* >( last.object + 0x60 );
				memcpy( &name_buffer, ( void* ) ( name_pointer + 0x0 ), 256 );
				if ( strcmp( name_buffer, object_name ) == 0 )
				{
					return last.object;
				}
			}
			return uint64_t( );
		}
	}
}