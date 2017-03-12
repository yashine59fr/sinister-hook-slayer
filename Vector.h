#ifndef __SDK_VECTOR_H__
#define __SDK_VECTOR_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "stdafx.h"
#include "const.h"
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define FastSqrt(x)			(*sqrtf)(x)

#define M_RADPI 57.295779513082f // (180 / pi)
#define SQUARE( a ) a*a
#define rad(a) a*(M_PI/180)
#define deg(a) a*(180/M_PI)
#ifndef RAD2DEG
	#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
	#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

inline float sqrt2(float sqr)
{
	float root = 0;

	__asm
	{
		sqrtss xmm0, sqr
		movss root, xmm0
	}

	return root;
}

inline void SinCos(const float rad, float &sin, float &cos)
{
	const __m128 _ps_fopi = _mm_set_ss(1.27323954473516f);

	const __m128 _ps_0p5 = _mm_set_ss(0.5f);
	const __m128 _ps_1 = _mm_set_ss(1.0f);

	const __m128 _ps_dp1 = _mm_set_ss(-0.7851562f);
	const __m128 _ps_dp2 = _mm_set_ss(-2.4187564849853515625e-4f);
	const __m128 _ps_dp3 = _mm_set_ss(-3.77489497744594108e-8f);

	const __m128 _ps_sincof_p0 = _mm_set_ss(2.443315711809948e-5f);
	const __m128 _ps_sincof_p1 = _mm_set_ss(8.3321608736e-3f);
	const __m128 _ps_sincof_p2 = _mm_set_ss(-1.6666654611e-1f);
	const __m128 _ps_coscof_p0 = _mm_set_ss(2.443315711809948e-5f);
	const __m128 _ps_coscof_p1 = _mm_set_ss(-1.388731625493765e-3f);
	const __m128 _ps_coscof_p2 = _mm_set_ss(4.166664568298827e-2f);

	const __m128i _pi32_1 = _mm_set1_epi32(1);
	const __m128i _pi32_i1 = _mm_set1_epi32(~1);
	const __m128i _pi32_2 = _mm_set1_epi32(2);
	const __m128i _pi32_4 = _mm_set1_epi32(4);

	const __m128 _mask_sign_raw = *(__m128*)&_mm_set1_epi32(0x80000000);
	const __m128 _mask_sign_inv = *(__m128*)&_mm_set1_epi32(~0x80000000);


	__m128  xmm3 = _mm_setzero_ps();
	__m128i emm0, emm2, emm4;

	__m128 sign_bit_cos, sign_bit_sin;

	__m128 x, y, z;
	__m128 y1, y2;

	__m128 a = _mm_set_ss(rad);

	x = _mm_and_ps(a, _mask_sign_inv);
	y = _mm_mul_ps(x, _ps_fopi);

	emm2 = _mm_cvtps_epi32(y);
	emm2 = _mm_add_epi32(emm2, _pi32_1);
	emm2 = _mm_and_si128(emm2, _pi32_i1);
	y = _mm_cvtepi32_ps(emm2);

	emm4 = emm2;

	emm0 = _mm_and_si128(emm2, _pi32_4);
	emm0 = _mm_slli_epi32(emm0, 29);
	__m128 swap_sign_bit_sin = _mm_castsi128_ps(emm0);

	emm2 = _mm_and_si128(emm2, _pi32_2);
	emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
	__m128 poly_mask = _mm_castsi128_ps(emm2);

	x = _mm_add_ps(x, _mm_mul_ps(y, _ps_dp1));
	x = _mm_add_ps(x, _mm_mul_ps(y, _ps_dp2));
	x = _mm_add_ps(x, _mm_mul_ps(y, _ps_dp3));

	emm4 = _mm_sub_epi32(emm4, _pi32_2);
	emm4 = _mm_andnot_si128(emm4, _pi32_4);
	emm4 = _mm_slli_epi32(emm4, 29);

	sign_bit_cos = _mm_castsi128_ps(emm4);
	sign_bit_sin = _mm_xor_ps(_mm_and_ps(a, _mask_sign_raw), swap_sign_bit_sin);

	z = _mm_mul_ps(x, x);

	y1 = _mm_mul_ps(_ps_coscof_p0, z);
	y1 = _mm_add_ps(y1, _ps_coscof_p1);
	y1 = _mm_mul_ps(y1, z);
	y1 = _mm_add_ps(y1, _ps_coscof_p2);
	y1 = _mm_mul_ps(y1, z);
	y1 = _mm_mul_ps(y1, z);
	y1 = _mm_sub_ps(y1, _mm_mul_ps(z, _ps_0p5));
	y1 = _mm_add_ps(y1, _ps_1);

	y2 = _mm_mul_ps(_ps_sincof_p0, z);
	y2 = _mm_add_ps(y2, _ps_sincof_p1);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_add_ps(y2, _ps_sincof_p2);
	y2 = _mm_mul_ps(y2, z);
	y2 = _mm_mul_ps(y2, x);
	y2 = _mm_add_ps(y2, x);

	xmm3 = poly_mask;

	__m128 ysin2 = _mm_and_ps(xmm3, y2);
	__m128 ysin1 = _mm_andnot_ps(xmm3, y1);

	sin = _mm_cvtss_f32(_mm_xor_ps(_mm_add_ps(ysin1, ysin2), sign_bit_sin));
	cos = _mm_cvtss_f32(_mm_xor_ps(_mm_add_ps(_mm_sub_ps(y1, ysin1), _mm_sub_ps(y2, ysin2)), sign_bit_cos));
}
namespace ValveSDK
{
	class Vector
	{
	public:
		float x, y, z;
		Vector( void );
		Vector( float X, float Y, float Z );
		void Init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f );
		bool IsValid( ) const;
		float operator[]( int i ) const;
		float& operator[]( int i );
		inline void Zero( );
		bool operator==( const Vector& v ) const;
		bool operator!=( const Vector& v ) const;
		inline bool operator!() { return !x && !y && !z; }
		__forceinline Vector&	operator+=( const Vector &v );
		__forceinline Vector&	operator-=( const Vector &v );
		__forceinline Vector&	operator*=( const Vector &v );
		__forceinline Vector&	operator*=( float s );
		__forceinline Vector&	operator/=( const Vector &v );
		__forceinline Vector&	operator/=( float s );
		__forceinline Vector&	operator+=( float fl );
		__forceinline Vector&	operator-=( float fl );
		inline Vector NormalizeVec();
		inline float	Length( ) const;
		__forceinline float LengthSqr( void ) const
		{
			CHECK_VALID( *this );
			return ( x*x + y*y + z*z );
		}
		bool IsZero( float tolerance = 0.01f ) const
		{
			return ( x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance &&
				z > -tolerance && z < tolerance );
		}
		float	NormalizeInPlace( );
		__forceinline float	DistToSqr( const Vector &vOther ) const;
		float	Dot( const Vector& vOther ) const;
		float	Dots(const float* fOther) const;
		float	Length2D( void ) const;
		float	Length2DSqr( void ) const;
				Vector& operator=( const Vector &vOther );
		Vector	operator-( void ) const;
		Vector	operator+( const Vector& v ) const;
		Vector	operator-( const Vector& v ) const;
		Vector	operator*( const Vector& v ) const;
		Vector	operator/( const Vector& v ) const;
		Vector	operator*( float fl ) const;
		Vector	operator/( float fl ) const;
		// Base address...
		float* Base( );
		float const* Base( ) const;
		inline Vector Cross(Vector a) { return Vector(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x); }
		inline Vector Angle(Vector* up = 0)
		{
			if (!x && !y)
				return Vector(0, 0, 0);

			float roll = 0;

			if (up)
			{
				Vector left = (*up).Cross(*this);

				roll = deg(atan2f(left.z, (left.y * x) - (left.x * y)));
			}

			return Vector(deg(atan2f(-z, sqrt2(x*x + y*y))), deg(atan2f(y, x)), roll);
		}
		Vector Direction()
		{
			return Vector(cos(y * M_PI / 180.0f) * cos(x * M_PI / 180.0f), sin(y * M_PI / 180.0f) * cos(x * M_PI / 180.0f), sin(-x * M_PI / 180.0f)).NormalizeVec();
		}

		inline Vector Forward()
		{
			float sp, sy, cp, cy;

			SinCos(rad(x), sp, cp);
			SinCos(rad(y), sy, cy);

			return Vector(cp*cy, cp*sy, -sp);
		}
		inline Vector Right()
		{
			float sp, sy, sr, cp, cy, cr;

			SinCos(rad(x), sp, cp);
			SinCos(rad(y), sy, cy);
			SinCos(rad(z), sr, cr);

			return Vector(1 * sr*sp*cy + -1 * cr*-sy, -1 * sr*sp*sy + -1 * cr*cy, -1 * sr*cr);
		}
		inline Vector Up()
		{
			float sp, sy, sr, cp, cy, cr;

			SinCos(rad(x), sp, cp);
			SinCos(rad(y), sy, cy);
			SinCos(rad(z), sr, cr);

			return Vector(cr*sp*cy + -sr*-sy, cr*sp*sy + -sr*cy, cr*cp);
		}
	};

	//===============================================
	inline void Vector::Init( float ix, float iy, float iz )
	{
		x = ix; y = iy; z = iz;
		CHECK_VALID( *this );
	}
	//===============================================
	inline Vector::Vector( float X, float Y, float Z )
	{
		x = X; y = Y; z = Z;
		CHECK_VALID( *this );
	}
	//===============================================
	inline Vector::Vector( void ){ }
	//===============================================
	inline void Vector::Zero( )
	{
		x = y = z = 0.0f;
	}
	inline Vector operator*(float fl, const Vector& v)
	{
		return v * fl;
	}
	//===============================================
	inline void VectorClear( Vector& a )
	{
		a.x = a.y = a.z = 0.0f;
	}
	

	FORCEINLINE float DotProduct(const Vector& a, const Vector& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	//===============================================
	inline Vector& Vector::operator=( const Vector &vOther )
	{
		CHECK_VALID( vOther );
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}
	//===============================================
	inline float& Vector::operator[]( int i )
	{
		Assert( ( i >= 0 ) && ( i < 3 ) );
		return ( ( float* )this )[ i ];
	}
	//===============================================
	inline float Vector::operator[]( int i ) const
	{
		Assert( ( i >= 0 ) && ( i < 3 ) );
		return ( ( float* )this )[ i ];
	}
	//===============================================
	inline bool Vector::operator==( const Vector& src ) const
	{
		CHECK_VALID( src );
		CHECK_VALID( *this );
		return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
	}
	//===============================================
	inline bool Vector::operator!=( const Vector& src ) const
	{
		CHECK_VALID( src );
		CHECK_VALID( *this );
		return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
	}
	//===============================================
	__forceinline void VectorCopy( const Vector& src, Vector& dst )
	{
		CHECK_VALID( src );
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
	}
	//===============================================
	__forceinline  Vector& Vector::operator+=( const Vector& v )
	{
		CHECK_VALID( *this );
		CHECK_VALID( v );
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	//===============================================
	__forceinline  Vector& Vector::operator-=( const Vector& v )
	{
		CHECK_VALID( *this );
		CHECK_VALID( v );
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	//===============================================
	__forceinline  Vector& Vector::operator*=( float fl )
	{
		x *= fl;
		y *= fl;
		z *= fl;
		CHECK_VALID( *this );
		return *this;
	}
	//===============================================
	__forceinline  Vector& Vector::operator*=( const Vector& v )
	{
		CHECK_VALID( v );
		x *= v.x;
		y *= v.y;
		z *= v.z;
		CHECK_VALID( *this );
		return *this;
	}
	//===============================================
	__forceinline Vector&	Vector::operator+=( float fl )
	{
		x += fl;
		y += fl;
		z += fl;
		CHECK_VALID( *this );
		return *this;
	}
	//===============================================
	__forceinline Vector&	Vector::operator-=( float fl )
	{
		x -= fl;
		y -= fl;
		z -= fl;
		CHECK_VALID( *this );
		return *this;
	}
	//===============================================
	__forceinline  Vector& Vector::operator/=( float fl )
	{
		Assert( fl != 0.0f );
		float oofl = 1.0f / fl;
		x *= oofl;
		y *= oofl;
		z *= oofl;
		CHECK_VALID( *this );
		return *this;
	}
	//===============================================
	__forceinline  Vector& Vector::operator/=( const Vector& v )
	{
		CHECK_VALID( v );
		Assert( v.x != 0.0f && v.y != 0.0f && v.z != 0.0f );
		x /= v.x;
		y /= v.y;
		z /= v.z;
		CHECK_VALID( *this );
		return *this;
	}
	//===============================================
	inline float Vector::Length( void ) const
	{
		CHECK_VALID( *this );

		float root = 0.0f;

		float sqsr = x*x + y*y + z*z;

		__asm
		{
			sqrtss xmm0, sqsr
				movss root, xmm0
		}

		return root;
	}
	//===============================================
	inline float Vector::Length2D( void ) const
	{
		CHECK_VALID( *this );

		float root = 0.0f;

		float sqst = x*x + y*y;

		__asm
		{
			sqrtss xmm0, sqst
				movss root, xmm0
		}

		return root;
	}
	//===============================================
	inline float Vector::Length2DSqr( void ) const
	{
		return ( x*x + y*y );
	}
	//===============================================
	inline Vector CrossProduct( const Vector& a, const Vector& b )
	{
		return Vector( a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x );
	}
	inline void CrossProduct2(const Vector& a, const Vector& b, Vector& result)
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}



	//===============================================
	float Vector::DistToSqr( const Vector &vOther ) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr( );
	}
	inline Vector Vector::NormalizeVec()
	{
		Vector& vecIn = *this;
		for (int axis = 0; axis < 3; ++axis)
		{
			while (vecIn[axis] > 180.f)
				vecIn[axis] -= 360.f;

			while (vecIn[axis] < -180.f)
				vecIn[axis] += 360.f;

		}

		vecIn[2] = 0.f;
		return vecIn;
	}
	//===============================================
	inline float Vector::NormalizeInPlace( )
	{
		Vector& v = *this;

		float iradius = 1.f / ( this->Length( ) + 1.192092896e-07F ); //FLT_EPSILON

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;

		return iradius;

	}
	//===============================================
	inline float VectorNormalize( Vector& v )
	{
		Assert( v.IsValid( ) );
		float l = v.Length( );
		if( l != 0.0f )
		{
			v /= l;
		}
		else
		{
			// FIXME: 
			// Just copying the existing implemenation; shouldn't res.z == 0?
			v.x = v.y = 0.0f; v.z = 1.0f;
		}
		return l;
	}
	//===============================================
	FORCEINLINE float VectorNormalize( float * v )
	{
		return VectorNormalize( *( reinterpret_cast< Vector * >( v ) ) );
	}
	//===============================================
	inline Vector Vector::operator+( const Vector& v ) const
	{
		Vector res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}

	//===============================================
	inline Vector Vector::operator-( const Vector& v ) const
	{
		Vector res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}
	//===============================================
	inline Vector Vector::operator*( float fl ) const
	{
		Vector res;
		res.x = x * fl;
		res.y = y * fl;
		res.z = z * fl;
		return res;
	}
	//===============================================
	inline Vector Vector::operator*( const Vector& v ) const
	{
		Vector res;
		res.x = x * v.x;
		res.y = y * v.y;
		res.z = z * v.z;
		return res;
	}
	//===============================================
	inline Vector Vector::operator/( float fl ) const
	{
		Vector res;
		res.x = x / fl;
		res.y = y / fl;
		res.z = z / fl;
		return res;
	}
	//===============================================
	inline Vector Vector::operator/( const Vector& v ) const
	{
		Vector res;
		res.x = x / v.x;
		res.y = y / v.y;
		res.z = z / v.z;
		return res;
	}
	inline float Vector::Dot( const Vector& vOther ) const
	{
		const Vector& a = *this;

		return( a.x*vOther.x + a.y*vOther.y + a.z*vOther.z );
	}
	inline float Vector::Dots(const float* fOther) const
	{
		const Vector& a = *this;

		return(a.x*fOther[0] + a.y*fOther[1] + a.z*fOther[2]);
	}
	inline float VectorLength( const Vector& v )
	{
		CHECK_VALID( v );
		return ( float )FastSqrt( v.x*v.x + v.y*v.y + v.z*v.z );
	}
	inline void VectorSubtract( const Vector& a, const Vector& b, Vector& c )
	{
		CHECK_VALID( a );
		CHECK_VALID( b );
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}
	inline void VectorAdd( const Vector& a, const Vector& b, Vector& c )
	{
		CHECK_VALID( a );
		CHECK_VALID( b );
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
	}
	inline float* Vector::Base( )
	{
		return ( float* )this;
	}
	inline float const* Vector::Base( ) const
	{
		return ( float const* )this;
	}
	class __declspec( align( 16 ) ) VectorAligned : public Vector
	{
	public:
		inline VectorAligned( void ) {};
		inline VectorAligned( float X, float Y, float Z )
		{
			Init( X, Y, Z );
		}
	public:
		explicit VectorAligned( const Vector &vOther )
		{
			Init( vOther.x, vOther.y, vOther.z );
		}

		VectorAligned& operator=( const Vector &vOther )
		{
			Init( vOther.x, vOther.y, vOther.z );
			return *this;
		}

		float w;	// this space is used anyway
	};

	typedef Vector QAngle;
}
struct Hitbox
{
	Hitbox(void)
	{
		hitbox = -1;
	}

	Hitbox(int newHitBox)
	{
		hitbox = newHitBox;
	}

	int  hitbox;
	ValveSDK::Vector points[9];
};
struct BestPoint
{
	BestPoint(void)
	{
		hitbox = -1;
		point = ValveSDK::Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	explicit BestPoint(int newHitBox)
	{
		hitbox = newHitBox;
		point = ValveSDK::Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	ValveSDK::Vector point;
	int  index;
	int  dmg;
	int  flags;
	int  hitbox;
};
enum
{
	FL_HIGH = (1 << 0),
	FL_LOW = (1 << 1),
	FL_SPECIAL = (1 << 2)
};
#endif