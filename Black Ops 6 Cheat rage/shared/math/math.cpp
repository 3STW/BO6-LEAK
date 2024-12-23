#include "../shared.hpp"

namespace shared::math
{
	angle_t calc_angle2( const vec3_t src, const vec3_t dst )
	{
		auto ret = angle_t();

		auto vec_delta = dst - src;

		vector_angles( vec_delta, ret );

		return ret;
	}

	void normalize_angle(angle_t& ang)
	{
		while (ang.x > 180.0f)
			ang.x -= 360.0f;
		while (ang.x < -180.0f)
			ang.x += 360.0f;

		// Make sure the Y component is within the range [-180, 180]
		if (ang.y > 180.0f)
			ang.y -= 360.0f;
		else if (ang.y < -180.0f)
			ang.y += 360.0f;
		// The Z component is already 0, so no further normalization is needed for it.

		
	}

	angle_t calc_angle(const vec3_t& src, const vec3_t& dst)
	{
		vec3_t delta = src - dst;

		angle_t ang;
		ang.x = std::atanf(-delta.z / delta.length_2d()) * (-(180.0 / M_PI));
		ang.y = std::atanf(delta.y / delta.x) * (180.0 / M_PI);
		ang.z = 0.f;

		if (delta.x >= 0.f)
			ang.y += 180.f;

		
		ang = ang.normalize();

		return ang;
	}

	void angle_vectors( const angle_t& ang, vec3_t& out_forward )
	{
		auto sine = vec2_t(),
			cosine = vec2_t();

		sincos( deg2rad( ang.x ), sine.x, cosine.x );
		sincos( deg2rad( ang.y ), sine.y, cosine.y );

		out_forward.x = cosine.x * cosine.y;
		out_forward.y = cosine.x * sine.y;
		out_forward.z = -sine.x;
	}

	void angle_vectors( const angle_t& ang, vec3_t& out_forward, vec3_t& out_right, vec3_t& out_up )
	{
		auto sine = vec3_t(),
			cosine = vec3_t();

		sincos( deg2rad( ang.x ), sine.x, cosine.x );
		sincos( deg2rad( ang.y ), sine.y, cosine.y );
		sincos( deg2rad( ang.z ), sine.z, cosine.z );

		out_forward.x = cosine.x * cosine.y;
		out_forward.y = cosine.x * sine.y;
		out_forward.z = -sine.x;

		out_right.x = ( -1 * sine.z * sine.x * cosine.y + -1 * cosine.z * -sine.y );
		out_right.y = ( -1 * sine.z * sine.x * sine.y + -1 * cosine.z * cosine.y );
		out_right.z = ( -1 * sine.z * cosine.x );

		out_up.x = ( cosine.z * sine.x * cosine.y + -sine.z * -sine.y );
		out_up.y = ( cosine.z * sine.x * sine.y + -sine.z * cosine.y );
		out_up.z = ( cosine.z * cosine.x );
	}

	void vector_angles( const vec3_t & vec, angle_t & out )
	{
		if ( vec.x == 0.0f && vec.y == 0.0f )
		{
			out.x = ( vec.z > 0.0f ) ? 270.0f : 90.0f;
			out.y = 0.0f;
		}
		else
		{
			out.x = atan2( -vec.z, vec.length_2d() ) * 180.f / static_cast< float >( M_PI );
			out.y = atan2( vec.y, vec.x ) * 180.f / static_cast< float >( M_PI );
		}

		out.z = 0.f;
	}

	void vector_transform( const vec3_t & in_vec, const matrix3x4_t & in_mat, vec3_t & out_vec )
	{
		out_vec.x = in_vec.dot( in_mat[ 0 ] ) + in_mat[ 0 ][ 3 ];
		out_vec.y = in_vec.dot( in_mat[ 1 ] ) + in_mat[ 1 ][ 3 ];
		out_vec.z = in_vec.dot( in_mat[ 2 ] ) + in_mat[ 2 ][ 3 ];
	}
}