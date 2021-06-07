#pragma once
#include "mono_typedefs.hpp"

using namespace mono_lib;
#define MONO_OFFSET(_namespace, class_name, var) static uint64_t var = field_get_offset( class_get_field_from_name( class_from_name( base_image, _namespace, class_name ), #var ) );

namespace mono_lib
{
	void* root_domain;
	void* base_image;
	void* base_assembly;

	auto setup_exports( ) -> void
	{
		HMODULE mod = LoadLibraryW( L"mono-2.0-bdwgc.dll" );
		if ( !mod )
			return;

		get_root_domain = ( mono_get_root_domain ) GetProcAddress( mod, "mono_get_root_domain" );

		field_full_name = ( mono_field_full_name ) GetProcAddress( mod, "mono_field_full_name" );
		class_get_field_from_name = ( mono_class_get_field_from_name ) GetProcAddress( mod, "mono_class_get_field_from_name" );
		field_get_offset = ( mono_field_get_offset ) GetProcAddress( mod, "mono_field_get_offset" );
		class_vtable = ( mono_class_vtable ) GetProcAddress( mod, "mono_class_vtable" );
		field_static_get_value = ( mono_field_static_get_value ) GetProcAddress( mod, "mono_field_static_get_value" );

		method_full_name = ( mono_method_full_name ) GetProcAddress( mod, "mono_method_full_name" );
		domain_assembly_open = ( mono_domain_assembly_open ) GetProcAddress( mod, "mono_domain_assembly_open" );
		class_get_fields = ( mono_class_get_fields ) GetProcAddress( mod, "mono_class_get_fields" );
		class_get_methods = ( mono_class_get_methods ) GetProcAddress( mod, "mono_class_get_methods" );

		thread_attach = ( mono_thread_attach ) GetProcAddress( mod, "mono_thread_attach" );

		assembly_get_image = ( mono_assembly_get_image ) GetProcAddress( mod, "mono_assembly_get_image" );
		class_from_name = ( mono_class_from_name ) GetProcAddress( mod, "mono_class_from_name" );
		class_get_method_from_name = ( mono_class_get_method_from_name ) GetProcAddress( mod, "mono_class_get_method_from_name" );
	}

	auto setup( const char* mono_assembly_name ) -> bool
	{
		setup_exports( );
		root_domain = get_root_domain( );
		thread_attach( root_domain );

		base_assembly = domain_assembly_open( root_domain, mono_assembly_name );
		base_image = assembly_get_image( base_assembly );

		return true;
	}

	auto dump_fields( const char* _namespace, const char* class_name ) -> void
	{
		void* iterator = NULL;
		const auto mono_class = class_from_name( base_image, _namespace, class_name );

		while ( auto field = class_get_fields( mono_class, &iterator ) )
		{
			printf( "[~] dumped %s: 0x%x\n", field_full_name( field ), field_get_offset( field ) );
		}
	}
}