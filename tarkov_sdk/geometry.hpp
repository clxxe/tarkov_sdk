#pragma once

namespace geometry
{
	class vec2_t
	{
	public:
		float x;
		float y;

		vec2_t( )
		{}

		vec2_t( float x, float y )
			: x( x ), y( y )
		{}
	};

	class vec3_t
	{
	public:
		float x;
		float y;
		float z;

		vec3_t( )
		{}

		vec3_t( float x, float y, float z )
			: x( x ), y( y ), z( z )
		{}
	};
}