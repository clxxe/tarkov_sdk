#pragma once
#include "includes.hpp"

namespace process
{
	namespace memory
	{
		auto get_module_base( const wchar_t* name ) -> uint64_t
		{
			return ( uint64_t ) GetModuleHandle( name );
		}

		auto read_chain( uint64_t base, const std::vector<uint64_t>& offsets ) -> uint64_t
		{
			uint64_t result = *reinterpret_cast< uint64_t* >( base + offsets.at( 0 ) );
			for ( int i = 1; i < offsets.size( ); i++ ) {
				result = *reinterpret_cast< uint64_t* >( result + offsets.at( i ) );
			}
			return result;
		}
	}
}