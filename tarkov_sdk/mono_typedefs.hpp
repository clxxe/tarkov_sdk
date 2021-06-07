#pragma once

namespace mono_lib
{
	typedef void( __cdecl* mono_thread_attach )( void* domain );
	typedef void* ( __cdecl* mono_get_root_domain )( void );

	typedef void* ( __cdecl* mono_assembly_get_image )( void* assembly );
	typedef void* ( __cdecl* mono_class_from_name )( void* image, const char* name_space, const char* klass );
	typedef void* ( __cdecl* mono_class_get_method_from_name )( void* klass, const char* name, int );

	typedef void* ( __cdecl* mono_class_get_fields )( void* klass, void** iterator );
	typedef void* ( __cdecl* mono_class_get_methods )( void* klass, void** );
	typedef void* ( __cdecl* mono_domain_assembly_open )( void* domain, const char* name );

	typedef void* ( __cdecl* mono_class_get_field_from_name )( void* klass, const char* name );
	typedef void* ( __cdecl* mono_class_vtable )( void* domain, void* klass );
	typedef void* ( __cdecl* mono_vtable_get_static_field_data )( void* vtable );


	typedef std::uint32_t( __cdecl* mono_field_get_offset )( void* field );
	typedef void( __cdecl* mono_field_static_get_value )( void* vtable, void* field, std::uintptr_t* value );

	typedef char* ( __cdecl* mono_field_full_name )( void* field );
	typedef char* ( __cdecl* mono_method_full_name )( void* method, bool );

	mono_vtable_get_static_field_data vtable_get_static_field_data;
	mono_field_static_get_value field_static_get_value;
	mono_class_vtable class_vtable;
	mono_get_root_domain get_root_domain;
	mono_field_full_name field_full_name;
	mono_class_get_field_from_name class_get_field_from_name;
	mono_field_get_offset field_get_offset;
	mono_method_full_name method_full_name;
	mono_domain_assembly_open domain_assembly_open;
	mono_class_get_methods class_get_methods;
	mono_class_get_fields class_get_fields;
	mono_thread_attach thread_attach;
	mono_assembly_get_image assembly_get_image;
	mono_class_from_name class_from_name;
	mono_class_get_method_from_name class_get_method_from_name;
}