////////////////////////////////////////////////////////////////
//
//  Heptane Renderer (C7H16)
//
//  author(s):
//  ENDESGA - https://x.com/ENDESGA | https://bsky.app/profile/endesga.bsky.social
//
//  https://github.com/H-language/C7H16
//  2025 - CC0 - FOSS forever
//

#pragma once

////////////////////////////////
/// include(s)

#if __linux__
	//#include <alsa/asoundlib.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/extensions/Xrender.h>
	#include <X11/extensions/Xpresent.h>
	#include <X11/XKBlib.h>
	#include <X11/cursorfont.h>
#else
	__declspec( dllimport ) int __stdcall timeBeginPeriod( int );
#endif

#define C7H16
#include <H.h>

////////////////////////////////
/// version

#define C7H16_VERSION_MAJOR 0
#define C7H16_VERSION_MINOR 1
#define C7H16_VERSION_PATCH 0
#define C7H16_VERSION AS_BYTES( C7H16_VERSION_MAJOR ) "." AS_BYTES( C7H16_VERSION_MINOR ) "." AS_BYTES( C7H16_VERSION_PATCH )

////////////////////////////////
/// types

////////
// multi-dimensional

#define DECLARE_TYPE_2D( TYPE )\
	fusion( TYPE##x2 )\
	{\
		variant\
		{\
			TYPE x;\
			TYPE y;\
		};\
		variant\
		{\
			TYPE w;\
			TYPE h;\
		};\
	}

#define DECLARE_TYPE_3D( TYPE )\
	fusion( TYPE##x3 )\
	{\
		variant\
		{\
			TYPE x;\
			TYPE y;\
			TYPE z;\
		};\
		variant\
		{\
			TYPE w;\
			TYPE h;\
			TYPE d;\
		};\
	}

#define DECLARE_TYPE_4D( TYPE )\
	fusion( TYPE##x4 )\
	{\
		variant\
		{\
			TYPE x;\
			TYPE y;\
			TYPE z;\
			TYPE w;\
		};\
		variant\
		{\
			TYPE r;\
			TYPE g;\
			TYPE b;\
			TYPE a;\
		};\
	}

#define DECLARE_TYPE_2D_FN( TYPE )\
	embed TYPE##x2 TYPE##x2_invert( TYPE##x2 const V )\
	{\
		out make( TYPE##x2, .x = -V.x, .y = -V.y );\
	}\
	embed TYPE##x2 TYPE##x2_add( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out make( TYPE##x2, .x = A.x + B.x, .y = A.y + B.y );\
	}\
	embed TYPE##x2 TYPE##x2_add_##TYPE( TYPE##x2 const A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x + V, .y = A.y + V );\
	}\
	embed TYPE##x2 TYPE##x2_sub( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out make( TYPE##x2, .x = A.x - B.x, .y = A.y - B.y );\
	}\
	embed TYPE##x2 TYPE##x2_sub_##TYPE( TYPE##x2 const A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x - V, .y = A.y - V );\
	}\
	embed TYPE##x2 TYPE##x2_mul( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out make( TYPE##x2, .x = A.x * B.x, .y = A.y * B.y );\
	}\
	embed TYPE##x2 TYPE##x2_mul_##TYPE( TYPE##x2 const A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x * V, .y = A.y * V );\
	}\
	embed TYPE##x2 TYPE##x2_div( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out make( TYPE##x2, .x = A.x / B.x, .y = A.y / B.y );\
	}\
	embed TYPE##x2 TYPE##x2_div_##TYPE( TYPE##x2 const A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x / V, .y = A.y / V );\
	}\
	embed TYPE TYPE##x2_dot( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out A.x * B.x + A.y * B.y;\
	}\
	embed TYPE TYPE##x2_mag_sqr( TYPE##x2 const V )\
	{\
		out TYPE##x2_dot( V, V );\
	}\
	embed TYPE TYPE##x2_distance_sqr( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out TYPE##x2_mag_sqr( TYPE##x2_sub( B, A ) );\
	}

#define DECLARE_TYPE_3D_FN( TYPE )\
	embed TYPE##x3 TYPE##x3_invert( TYPE##x3 const V )\
	{\
		out make( TYPE##x3, .x = -V.x, .y = -V.y, .z = -V.z );\
	}\
	embed TYPE##x3 TYPE##x3_add( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, .x = A.x + B.x, .y = A.y + B.y, .z = A.z + B.z );\
	}\
	embed TYPE##x3 TYPE##x3_add_##TYPE( TYPE##x3 const A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x + V, .y = A.y + V, .z = A.z + V );\
	}\
	embed TYPE##x3 TYPE##x3_sub( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, .x = A.x - B.x, .y = A.y - B.y, .z = A.z - B.z );\
	}\
	embed TYPE##x3 TYPE##x3_sub_##TYPE( TYPE##x3 const A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x - V, .y = A.y - V, .z = A.z - V );\
	}\
	embed TYPE##x3 TYPE##x3_mul( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, .x = A.x * B.x, .y = A.y * B.y, .z = A.z * B.z );\
	}\
	embed TYPE##x3 TYPE##x3_mul_##TYPE( TYPE##x3 const A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x * V, .y = A.y * V, .z = A.z * V );\
	}\
	embed TYPE##x3 TYPE##x3_div( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, .x = A.x / B.x, .y = A.y / B.y, .z = A.z / B.z );\
	}\
	embed TYPE##x3 TYPE##x3_div_##TYPE( TYPE##x3 const A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x / V, .y = A.y / V, .z = A.z / V );\
	}\
	embed TYPE TYPE##x3_dot( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out A.x * B.x + A.y * B.y + A.z * B.z;\
	}\
	embed TYPE TYPE##x3_mag_sqr( TYPE##x3 const V )\
	{\
		out TYPE##x3_dot( V, V );\
	}\
	embed TYPE TYPE##x3_distance_sqr( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out TYPE##x3_mag_sqr( TYPE##x3_sub( B, A ) );\
	}\
	embed TYPE##x3 TYPE##x3_cross( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, .x = A.y * B.z - A.z * B.y, .y = A.z * B.x - A.x * B.z, .z = A.x * B.y - A.y * B.x );\
	}

#define DECLARE_TYPE_4D_FN( TYPE )\
	embed TYPE##x4 TYPE##x4_invert( TYPE##x4 const V )\
	{\
		out make( TYPE##x4, .x = -V.x, .y = -V.y, .z = -V.z, .w = -V.w );\
	}\
	embed TYPE##x4 TYPE##x4_add( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out make( TYPE##x4, .x = A.x + B.x, .y = A.y + B.y, .z = A.z + B.z, .w = A.w + B.w );\
	}\
	embed TYPE##x4 TYPE##x4_add_##TYPE( TYPE##x4 const A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x + V, .y = A.y + V, .z = A.z + V, .w = A.w + V );\
	}\
	embed TYPE##x4 TYPE##x4_sub( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out make( TYPE##x4, .x = A.x - B.x, .y = A.y - B.y, .z = A.z - B.z, .w = A.w - B.w );\
	}\
	embed TYPE##x4 TYPE##x4_sub_##TYPE( TYPE##x4 const A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x - V, .y = A.y - V, .z = A.z - V, .w = A.w - V );\
	}\
	embed TYPE##x4 TYPE##x4_mul( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out make( TYPE##x4, .x = A.x * B.x, .y = A.y * B.y, .z = A.z * B.z, .w = A.w * B.w );\
	}\
	embed TYPE##x4 TYPE##x4_mul_##TYPE( TYPE##x4 const A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x * V, .y = A.y * V, .z = A.z * V, .w = A.w * V );\
	}\
	embed TYPE##x4 TYPE##x4_div( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out make( TYPE##x4, .x = A.x / B.x, .y = A.y / B.y, .z = A.z / B.z, .w = A.w / B.w );\
	}\
	embed TYPE##x4 TYPE##x4_div_##TYPE( TYPE##x4 const A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x / V, .y = A.y / V, .z = A.z / V, .w = A.w / V );\
	}\
	embed TYPE TYPE##x4_dot( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out A.x * B.x + A.y * B.y + A.z * B.z + A.w * B.w;\
	}\
	embed TYPE TYPE##x4_mag_sqr( TYPE##x4 const V )\
	{\
		out TYPE##x4_dot( V, V );\
	}\
	embed TYPE TYPE##x4_distance_sqr( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out TYPE##x4_mag_sqr( TYPE##x4_sub( B, A ) );\
	}

#define DECLARE_TYPE_XD_FN_R( N, X )\
	embed r##N r##N##x##X##_length( const r##N##x##X V )\
	{\
		out r##N##_sqrt( r##N##x##X##_mag_sqr( V ) );\
	}\
	embed r##N r##N##x##X##_distance( const r##N##x##X A, const r##N##x##X B )\
	{\
		out r##N##_sqrt( r##N##x##X##_distance_sqr( A, B ) );\
	}\
	embed r##N##x##X r##N##x##X##_norm( const r##N##x##X V )\
	{\
		out r##N##x##X##_mul_##r##N( V, 1.0 / r##N##x##X##_length( V ) );\
	}\
	embed r##N##x##X r##N##x##X##_rotate( const r##N##x##X V, const r##N R )\
	{\
		r##N cos_angle = 0;\
		r##N sin_angle = 0;\
		r##N##_sincos( R, ref_of( sin_angle ), ref_of( cos_angle ) );\
		out r##N##x##X( V.x * cos_angle - V.y * sin_angle, V.x * sin_angle + V.y * cos_angle );\
	}

#define DECLARE_TYPE_MULTI( TYPE )\
	DECLARE_TYPE_2D( TYPE );\
	DECLARE_TYPE_3D( TYPE );\
	DECLARE_TYPE_4D( TYPE );\
	DECLARE_TYPE_2D_FN( TYPE );\
	DECLARE_TYPE_3D_FN( TYPE );\
	DECLARE_TYPE_4D_FN( TYPE )

#define DECLARE_TYPE_MULTI_R( N )\
	DECLARE_TYPE_XD_FN_R( N, 2 );\
	DECLARE_TYPE_XD_FN_R( N, 3 );\
	DECLARE_TYPE_XD_FN_R( N, 4 )

#define _x2( TYPE, X_Y... ) make( TYPE##x2, DEFAULTS( ( 0, 0 ), X_Y ) )
#define _x3( TYPE, X_Y_Z... ) make( TYPE##x3, DEFAULTS( ( 0, 0, 0 ), X_Y_Z ) )
#define _x4( TYPE, X_Y_Z_W... ) make( TYPE##x4, DEFAULTS( ( 0, 0, 0, 0 ), X_Y_Z_W ) )

DECLARE_TYPE_MULTI( n1 );
#define n1x2( X_Y... ) _x2( n1, X_Y )
#define n1x3( X_Y_Z... ) _x3( n1, X_Y_Z )
#define n1x4( X_Y_Z_W... ) _x4( n1, X_Y_Z_W )
DECLARE_TYPE_MULTI( i1 );
#define i1x2( X_Y... ) _x2( i1, X_Y )
#define i1x3( X_Y_Z... ) _x3( i1, X_Y_Z )
#define i1x4( X_Y_Z_W... ) _x4( i1, X_Y_Z_W )

DECLARE_TYPE_MULTI( n2 );
#define n2x2( X_Y... ) _x2( n2, X_Y )
#define n2x3( X_Y_Z... ) _x3( n2, X_Y_Z )
#define n2x4( X_Y_Z_W... ) _x4( n2, X_Y_Z_W )
DECLARE_TYPE_MULTI( i2 );
#define i2x2( X_Y... ) _x2( i2, X_Y )
#define i2x3( X_Y_Z... ) _x3( i2, X_Y_Z )
#define i2x4( X_Y_Z_W... ) _x4( i2, X_Y_Z_W )

DECLARE_TYPE_MULTI( n4 );
#define n4x2( X_Y... ) _x2( n4, X_Y )
#define n4x3( X_Y_Z... ) _x3( n4, X_Y_Z )
#define n4x4( X_Y_Z_W... ) _x4( n4, X_Y_Z_W )
DECLARE_TYPE_MULTI( i4 );
#define i4x2( X_Y... ) _x2( i4, X_Y )
#define i4x3( X_Y_Z... ) _x3( i4, X_Y_Z )
#define i4x4( X_Y_Z_W... ) _x4( i4, X_Y_Z_W )
DECLARE_TYPE_MULTI( r4 );
#define r4x2( X_Y... ) _x2( r4, X_Y )
#define r4x3( X_Y_Z... ) _x3( r4, X_Y_Z )
#define r4x4( X_Y_Z_W... ) _x4( r4, X_Y_Z_W )
DECLARE_TYPE_MULTI_R( 4 );

DECLARE_TYPE_MULTI( n8 );
#define n8x2( X_Y... ) _x2( n8, X_Y )
#define n8x3( X_Y_Z... ) _x3( n8, X_Y_Z )
#define n8x4( X_Y_Z_W... ) _x4( n8, X_Y_Z_W )
DECLARE_TYPE_MULTI( i8 );
#define i8x2( X_Y... ) _x2( i8, X_Y )
#define i8x3( X_Y_Z... ) _x3( i8, X_Y_Z )
#define i8x4( X_Y_Z_W... ) _x4( i8, X_Y_Z_W )
DECLARE_TYPE_MULTI( r8 );
#define r8x2( X_Y... ) _x2( r8, X_Y )
#define r8x3( X_Y_Z... ) _x3( r8, X_Y_Z )
#define r8x4( X_Y_Z_W... ) _x4( r8, X_Y_Z_W )
DECLARE_TYPE_MULTI_R( 8 );

#define grid_area( X, Y ) ( ( X ) * ( Y ) )
#define grid_index( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

////////
// dimensional flags

#define point_in_size( X, Y, W, H ) all( X >= 0, Y >= 0, X < W, Y < H )
#define point_not_in_size( X, Y, W, H ) any( X < 0, Y < 0, X >= W, Y >= H )

#define point_in_box( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) all( X >= TOPLEFT_X, Y >= TOPLEFT_Y, X <= BOTTOMRIGHT_X, Y <= BOTTOMRIGHT_Y )
#define point_not_in_box( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) any( X < TOPLEFT_X, Y < TOPLEFT_Y, X > BOTTOMRIGHT_X, Y > BOTTOMRIGHT_Y )

#define box_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) all( point_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )
#define box_not_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) any( point_not_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_not_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )

#define box_in_box( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) all( point_in_box( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_in_box( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )
#define box_not_in_box( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) any( point_not_in_box( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_not_in_box( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )

////////
// dyadic n/2^k

type_from( i4 ) d4;
#define d4( VAL ) to( d4, VAL )
#define d4_bits 12

#define i4_to_d4( I4 ) ( d4( I4 ) << d4_bits )
#define d4_to_i4( D4 ) ( i4( ( D4 ) >> d4_bits ) )

#define r8_to_d4( R8 ) ( d4( r8_round( ( R8 ) * r8( 1 << d4_bits ) ) ) )

#define d4_min i4_min
#define d4_max i4_max
#define d4_clamp i4_clamp
#define d4_abs i4_abs

#define d4_trunc( D4 ) ( i4_to_d4( d4_to_i4( D4 ) ) )

#define d4_floor_to_i4( D4 ) ( d4_to_i4( D4 ) - pick( ( ( D4 ) < 0 ) && ( ( D4 ) & ( ( 1 << d4_bits ) - 1 ) ), 1, 0 ) )
#define d4_floor( D4 ) ( i4_to_d4( d4_floor_to_i4( D4 ) ) )

#define d4_ceil_to_i4( D4 ) ( d4_to_i4( ( D4 ) + pick( ( D4 ) > 0, ( ( 1 << d4_bits ) - 1 ), 0 ) ) )
#define d4_ceil( D4 ) ( i4_to_d4( d4_ceil_to_i4( D4 ) ) )

#define d4_round_to_i4( D4 ) ( d4_to_i4( ( D4 ) + pick( ( D4 ) >= 0, ( 1 << ( d4_bits - 1 ) ), -( 1 << ( d4_bits - 1 ) ) ) ) )
#define d4_round( D4 ) ( i4_to_d4( d4_round_to_i4( D4 ) ) )

#define d4_mul( A, B ) d4( ( i8( A ) * i8( B ) ) >> d4_bits )
#define d4_div( A, B ) d4( ( i8( A ) << d4_bits ) / i8( B ) )

type_from( i4x2 ) d4x2;

////////////////////////////////
/// time

#define nano_per_micro 1000
#define nano_per_milli 1000000
#define nano_per_sec 1000000000
#define nano_per_min 60000000000
#define nano_per_hour 3600000000000
#define micro_per_milli 1000
#define micro_per_sec 1000000
#define micro_per_min 60000000
#define micro_per_hour 3600000000
#define milli_per_sec 1000
#define milli_per_min 60000
#define milli_per_hour 3600000
#define sec_per_min 60
#define sec_per_hour 3600
#define min_per_hour 60

type_from( n8 ) nano;
#define nano( VAL ) n8( VAL )

embed nano _get_nano()
{
	#if OS_WINDOWS
		perm LARGE_INTEGER frequency;
		perm LARGE_INTEGER freq_start;
		LARGE_INTEGER current;

		once
		{
			QueryPerformanceFrequency( ref_of( frequency ) );
			QueryPerformanceCounter( ref_of( freq_start ) );
		}

		QueryPerformanceCounter( ref_of( current ) );

		out( ( current.QuadPart - freq_start.QuadPart ) * 1000000000ULL ) / frequency.QuadPart;
	#else
		struct timespec ts;
		clock_gettime( CLOCK_MONOTONIC, ref_of( ts ) );
		out to( nano, ts.tv_sec * nano_per_sec + ts.tv_nsec );
	#endif
}

embed nano get_nano()
{
	perm nano epoch = 0;
	once
	{
		epoch = _get_nano();
	}
	out _get_nano() - epoch;
}

fn nano_sleep( nano const time )
{
	#if OS_WINDOWS
		static flag timer_init = no;
		static HANDLE timer = nothing;
		if( not timer_init )
		{
			timer_init = yes;
			timeBeginPeriod( 1 );
			timer = CreateWaitableTimer( nothing, TRUE, nothing );
		}

		LARGE_INTEGER li = { .QuadPart = -( time / 100 ) };
		SetWaitableTimer( timer, ref_of( li ), 0, nothing, nothing, FALSE );
		WaitForSingleObject( timer, INFINITE );

		// Optional: spin-wait only the final microseconds for extra precision
		//LARGE_INTEGER freq, target, now;
		///QueryPerformanceFrequency( ref_of( freq ) );
		//QueryPerformanceCounter( ref_of( target ) );
		//target.QuadPart += ( time * freq.QuadPart ) / nano_per_sec;
		//while( QueryPerformanceCounter( ref_of( now ) ), now.QuadPart < target.QuadPart );
	#else
		struct timespec ts = { time / nano_per_sec, time mod nano_per_sec };
		nanosleep( ref_of( ts ), nothing );
	#endif
}

////////////////////////////////
/// anchor

group( anchor )
{
	anchor_top_left = 0x00, // 0000 0000
	anchor_top_center = 0x01, // 0000 0001
	anchor_top_right = 0x02, // 0000 0010
	anchor_middle_left = 0x10, // 0001 0000
	anchor_middle_center = 0x11, // 0001 0001
	anchor_middle_right = 0x12, // 0001 0010
	anchor_bottom_left = 0x20, // 0010 0000
	anchor_bottom_center = 0x21, // 0010 0001
	anchor_bottom_right = 0x22 // 0010 0010
};

embed n2 anchor_get_x( anchor const anchor, n2 const region_width, n2 const object_width )
{
	temp n1 const h_align = anchor & 0x0F;
	temp n2 const offset = region_width - object_width;
	out pick( h_align is 1, offset >> 1, pick( h_align is 2, offset, 0 ) );
}

embed n2 anchor_get_y( anchor const anchor, n2 const region_height, n2 const object_height )
{
	temp const n1 v_align = anchor >> 4;
	temp n2 const offset = region_height - object_height;
	out pick( v_align is 1, offset >> 1, pick( v_align is 2, offset, 0 ) );
}

////////////////////////////////
/// pixel

// BGRA for X11/Windows (little-endian)
#if IS_BIG_ENDIAN
	fusion( pixel )
	{
		n4 bgra;
		variant
		{
			n1 a;
			n1 r;
			n1 g;
			n1 b;
		};
	};
#else
	fusion( pixel )
	{
		n4 bgra;
		variant
		{
			n1 b;
			n1 g;
			n1 r;
			n1 a;
		};
	};
#endif

#define pixel_bits 8
#define pixel_shift 2

// construction is RGBA though, for consistency
#define pixel( R, G, B, A... ) make( pixel, .r = ( R ), .g = ( G ), .b = ( B ), .a = DEFAULT( 0xff, A ) )

#define pixel_invalid make( pixel, .bgra = 0 )

#define pixel_black pixel( 0x00, 0x00, 0x00 )
#define pixel_dark_gray pixel( 0x3f, 0x3f, 0x3f )
#define pixel_gray pixel( 0x7f, 0x7f, 0x7f )
#define pixel_light_gray pixel( 0xbf, 0xbf, 0xbf )
#define pixel_white pixel( 0xff, 0xff, 0xff )
#define pixel_red pixel( 0xff, 0x00, 0x00 )
#define pixel_yellow pixel( 0xff, 0xff, 0x00 )
#define pixel_green pixel( 0x00, 0xff, 0x00 )
#define pixel_cyan pixel( 0x00, 0xff, 0xff )
#define pixel_blue pixel( 0x00, 0x00, 0xff )
#define pixel_magenta pixel( 0xff, 0x00, 0xff )

////////////////////////////////
/// canvas

object( canvas )
{
	pixel ref pixels;
	n2x2 size;
	n4 area;
};

new_object_fn( canvas, n2 const width, n2 const height )
{
	temp const canvas out_canvas = new_object( canvas );
	out_canvas->size = n2x2( width, height );
	out_canvas->area = n4( out_canvas->size.w ) * n4( out_canvas->size.h );
	out_canvas->pixels = to( pixel ref, new_ref( pixel, out_canvas->area ) );

	out out_canvas;
}

delete_object_fn( canvas )
{
	delete_ref( this->pixels );

	delete_object( this );
}

object_fn( canvas, resize, n2 const width, n2 const height )
{
	out_if( this->size.w is width and this->size.h is height );

	temp const n2x2 size_old = this->size;
	temp n4 const area_old = this->area;
	this->size = n2x2( width, height );
	this->area = n4( this->size.w ) * n4( this->size.h );
	this->pixels = ref_resize( this->pixels, area_old << pixel_shift, this->area << pixel_shift );
}

object_fn( canvas, fill, pixel const color )
{
	if_all( color.r is color.g, color.g is color.b, color.b is color.a )
	{
		bytes_fill( this->pixels, color.r, this->area << pixel_shift );
	}
	else
	{
		temp i4 filled = i4( this->size.w );
		iter( first_row_index, filled )
		{
			this->pixels[ first_row_index ] = color;
		}

		temp i4 remaining = this->area - filled;
		do
		{
			temp i4 const count = pick( remaining < filled, remaining, filled );
			bytes_copy( ref_of( this->pixels[ filled ] ), ref_of( this->pixels[ 0 ] ), count << pixel_shift );
			filled += count;
			remaining -= count;
		}
		while( remaining );
	}
}

#define canvas_clear( CANVAS ) bytes_clear( CANVAS->pixels, CANVAS->area << pixel_shift )

////////
// check

#define canvas_check_pixel( CANVAS, X, Y ) ( point_in_size( X, Y, CANVAS->size.w, CANVAS->size.h ) )
#define canvas_check_pixel_index( CANVAS, INDEX ) ( INDEX >= 0 and INDEX < CANVAS->area )

////////
// get

#define canvas_get_pixel_index( CANVAS, INDEX ) CANVAS->pixels[ ( INDEX ) ]
#define canvas_get_pixel_index_safe( CANVAS, INDEX ) pick( canvas_check_pixel_index( INDEX ), canvas_get_pixel_index( CANVAS, INDEX ), pixel_invalid )
#define canvas_get_pixel( CANVAS, X, Y ) canvas_get_pixel_index( CANVAS, grid_index( X, Y, CANVAS->size.w ) )
#define canvas_get_pixel_safe( CANVAS, X, Y ) pick( canvas_check_pixel( CANVAS, X, Y ), canvas_get_pixel( CANVAS, X, Y ), pixel_invalid )

////////
// set

#define canvas_set_pixel_index( CANVAS, INDEX, PIXEL ) ( canvas_get_pixel_index( CANVAS, INDEX ) ) = ( PIXEL )
#define canvas_set_pixel_index_safe( CANVAS, INDEX, PIXEL ) if( canvas_check_pixel_index( CANVAS, INDEX ) ) canvas_set_pixel_index( CANVAS, INDEX, PIXEL )
#define canvas_set_pixel( CANVAS, X, Y, PIXEL ) ( canvas_get_pixel( CANVAS, X, Y ) ) = ( PIXEL )
#define canvas_set_pixel_safe( CANVAS, X, Y, PIXEL ) if( canvas_check_pixel( CANVAS, X, Y ) ) canvas_set_pixel( CANVAS, X, Y, PIXEL )

////////////////////////////////
/// draw

#define _canvas_draw_pixel_index_( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp i4 const _INDEX = INDEX;\
		temp pixel const _PIXEL = PIXEL;\
		skip_if( _PIXEL.a is 0 );\
		if( _PIXEL.a is max_n1 )\
		{\
			canvas_set_pixel_index( CANVAS, _INDEX, _PIXEL );\
		}\
		else\
		{\
			temp pixel ref const _p = ref_of( canvas_get_pixel_index( CANVAS, _INDEX ) );\
			temp n2 const _sa = n2( _PIXEL.a );\
			temp n2 const _ia = max_n1 - _sa;\
			_p->r = n1( ( n2( _PIXEL.r ) * _sa + n2( _p->r ) * _ia + 127 ) >> pixel_bits );\
			_p->g = n1( ( n2( _PIXEL.g ) * _sa + n2( _p->g ) * _ia + 127 ) >> pixel_bits );\
			_p->b = n1( ( n2( _PIXEL.b ) * _sa + n2( _p->b ) * _ia + 127 ) >> pixel_bits );\
			_p->a = n1( _sa + ( ( n2( _p->a ) * _ia + 127 ) >> pixel_bits ) );\
		}\
	}\
	END_DEF

#define _canvas_draw_pixel_index_avg( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp pixel const _PIXEL = PIXEL;\
		temp pixel ref const _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->bgra = ( ( _p->bgra & 0xfefefefe ) >> 1 ) + ( ( ( _PIXEL.bgra ) & 0xfefefefe ) >> 1 );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_add( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp pixel const _PIXEL = PIXEL;\
		temp pixel ref const _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->r = n1( n2_min( n2( _p->r ) + n2( _PIXEL.r ), max_n1 ) );\
		_p->g = n1( n2_min( n2( _p->g ) + n2( _PIXEL.g ), max_n1 ) );\
		_p->b = n1( n2_min( n2( _p->b ) + n2( _PIXEL.b ), max_n1 ) );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_sub( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp pixel const _PIXEL = PIXEL;\
		temp pixel ref const _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->r = pick( _p->r <= _PIXEL.r, min_n1, _p->r - _PIXEL.r );\
		_p->g = pick( _p->g <= _PIXEL.g, min_n1, _p->g - _PIXEL.g );\
		_p->b = pick( _p->b <= _PIXEL.b, min_n1, _p->b - _PIXEL.b );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_mul( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp pixel const _PIXEL = PIXEL;\
		temp pixel ref const _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->r = n1( ( n2( _p->r ) * n2( _PIXEL.r ) + 127 ) >> pixel_bits );\
		_p->g = n1( ( n2( _p->g ) * n2( _PIXEL.g ) + 127 ) >> pixel_bits );\
		_p->b = n1( ( n2( _p->b ) * n2( _PIXEL.b ) + 127 ) >> pixel_bits );\
	}\
	END_DEF

#define canvas_draw_pixel_index( CANVAS, INDEX, PIXEL, BLEND... ) _canvas_draw_pixel_index_##BLEND( CANVAS, INDEX, PIXEL )
#define canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND... ) canvas_draw_pixel_index( CANVAS, grid_index( X, Y, CANVAS->size.w ), PIXEL, BLEND )

#define canvas_draw_pixel_safe( CANVAS, X, Y, PIXEL, BLEND... ) if( canvas_check_pixel( CANVAS, X, Y ) ) canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND )

////////////////////////////////
/// line

#define LINE_FN_SHIFT 20
#define LINE_FN_HALF ( 1 << ( LINE_FN_SHIFT - 1 ) )
#define LINE_FN_SCALE ( 1 << LINE_FN_SHIFT )

#define _line_fn( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )\
	START_DEF\
	{\
		temp i2 X_NAME = i2( Ax );\
		temp i2 Y_NAME = i2( Ay );\
		temp const i2 _LINE_FN##_x2 = i2( Bx );\
		temp const i2 _LINE_FN##_y2 = i2( By );\
		temp const i2 _LINE_FN##_xd = _LINE_FN##_x2 - X_NAME;\
		temp const i2 _LINE_FN##_yd = _LINE_FN##_y2 - Y_NAME;\
		temp i4 _LINE_FN##_hs = ( i4( X_NAME ) << LINE_FN_SHIFT ) + LINE_FN_HALF;\
		temp i4 _LINE_FN##_vs = ( i4( Y_NAME ) << LINE_FN_SHIFT ) + LINE_FN_HALF;\
		temp const i2 _LINE_FN##_ax = ABS( _LINE_FN##_xd );\
		temp const i2 _LINE_FN##_ay = ABS( _LINE_FN##_yd );\
		temp i2 _LINE_FN##_a = pick( _LINE_FN##_ax > _LINE_FN##_ay, _LINE_FN##_ax, _LINE_FN##_ay );\
		temp const i4 _LINE_FN##_recip = LINE_FN_SCALE / i4( MAX( _LINE_FN##_a, 1 ) );\
		temp const i4 _LINE_FN##_xs = i4( _LINE_FN##_xd ) * _LINE_FN##_recip;\
		temp const i4 _LINE_FN##_ys = i4( _LINE_FN##_yd ) * _LINE_FN##_recip;\
		temp const i2 _LINE_FN##_i = 0;\
		++_LINE_FN##_a;\
		do\
		{\
			X_NAME = i2( _LINE_FN##_hs >> LINE_FN_SHIFT );\
			Y_NAME = i2( _LINE_FN##_vs >> LINE_FN_SHIFT );\
			CODE;\
			_LINE_FN##_hs += _LINE_FN##_xs;\
			_LINE_FN##_vs += _LINE_FN##_ys;\
		}\
		while( --_LINE_FN##_a );\
	}\
	END_DEF

#define _line_fn_eval( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE ) _line_fn( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )
#define line_fn( Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE ) _line_fn_eval( JOIN( _LINE_FN_, __COUNTER__ ), Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )

#define _line_h_fn( _LINE_H_FN, Ax, Ay, Bx, X_NAME, Y_NAME, CODE )\
	START_DEF\
	{\
		temp i2 X_NAME = i2( Ax );\
		temp const i2 Y_NAME = i2( Ay );\
		temp const i2 _LINE_H_FN##_x2 = i2( Bx );\
		temp const i2 _LINE_H_FN##_step = pick( _LINE_H_FN##_x2 >= X_NAME, 1, -1 );\
		temp i2 _LINE_H_FN##_count = ABS( _LINE_H_FN##_x2 - X_NAME ) + 1;\
		do\
		{\
			CODE;\
			X_NAME += _LINE_H_FN##_step;\
		}\
		while( --_LINE_H_FN##_count );\
	}\
	END_DEF

#define _line_h_fn_eval( _LINE_H_FN, Ax, Ay, Bx, X_NAME, Y_NAME, CODE ) _line_h_fn( _LINE_H_FN, Ax, Ay, Bx, X_NAME, Y_NAME, CODE )
#define line_h_fn( Ax, Ay, Bx, X_NAME, Y_NAME, CODE ) _line_h_fn_eval( JOIN( _LINE_H_FN_, __COUNTER__ ), Ax, Ay, Bx, X_NAME, Y_NAME, CODE )

#define _line_v_fn( _LINE_V_FN, Ax, Ay, By, X_NAME, Y_NAME, CODE )\
	START_DEF\
	{\
		temp const i2 X_NAME = i2( Ax );\
		temp i2 Y_NAME = i2( Ay );\
		temp const i2 _LINE_V_FN##_y2 = i2( By );\
		temp const i2 _LINE_V_FN##_step = pick( _LINE_V_FN##_y2 >= Y_NAME, 1, -1 );\
		temp i2 _LINE_V_FN##_count = ABS( _LINE_V_FN##_y2 - Y_NAME ) + 1;\
		do\
		{\
			CODE;\
			Y_NAME += _LINE_V_FN##_step;\
		}\
		while( --_LINE_V_FN##_count );\
	}\
	END_DEF

#define _line_v_fn_eval( _LINE_V_FN, Ax, Ay, By, X_NAME, Y_NAME, CODE ) _line_v_fn( _LINE_V_FN, Ax, Ay, By, X_NAME, Y_NAME, CODE )
#define line_v_fn( Ax, Ay, By, X_NAME, Y_NAME, CODE ) _line_v_fn_eval( JOIN( _LINE_V_FN_, __COUNTER__ ), Ax, Ay, By, X_NAME, Y_NAME, CODE )

#define _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, SUFFIX... ) line_fn( Ax, Ay, Bx, By, _X, _Y, canvas_draw_pixel##SUFFIX( CANVAS, _X, _Y, PIXEL ) );
#define canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL )
#define canvas_draw_line_safe( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _safe )

#define _canvas_draw_line_h( CANVAS, Ax, Ay, Bx, PIXEL, SUFFIX... ) line_h_fn( Ax, Ay, Bx, _X, _Y, canvas_draw_pixel##SUFFIX( CANVAS, _X, _Y, PIXEL ) );
#define canvas_draw_line_h( CANVAS, Ax, Ay, Bx, PIXEL ) _canvas_draw_line_h( CANVAS, Ax, Ay, Bx, PIXEL )
#define canvas_draw_line_h_safe( CANVAS, Ax, Ay, Bx, PIXEL ) _canvas_draw_line_h( CANVAS, Ax, Ay, Bx, PIXEL, _safe )

#define _canvas_draw_line_v( CANVAS, Ax, Ay, By, PIXEL, SUFFIX... ) line_v_fn( Ax, Ay, By, _X, _Y, canvas_draw_pixel##SUFFIX( CANVAS, _X, _Y, PIXEL ) );
#define canvas_draw_line_v( CANVAS, Ax, Ay, By, PIXEL ) _canvas_draw_line_v( CANVAS, Ax, Ay, By, PIXEL )
#define canvas_draw_line_v_safe( CANVAS, Ax, Ay, By, PIXEL ) _canvas_draw_line_v( CANVAS, Ax, Ay, By, PIXEL, _safe )

////////////////////////////////
/// box

#define _box_fn( _BOX_FN, TLx, TLy, BRx, BRy, X_NAME, Y_NAME, CODE )\
	START_DEF\
	{\
		temp i2 _BOX_FN##_x1 = i2( TLx );\
		temp i2 _BOX_FN##_y1 = i2( TLy );\
		temp const i2 _BOX_FN##_x2 = i2( BRx );\
		temp const i2 _BOX_FN##_y2 = i2( BRy );\
		temp i2 X_NAME = _BOX_FN##_x1;\
		temp i2 Y_NAME = _BOX_FN##_y1;\
		temp i2 _BOX_FN##_w = _BOX_FN##_x2 - _BOX_FN##_x1 + 1;\
		do\
		{\
			Y_NAME = _BOX_FN##_y1;\
			CODE;\
			Y_NAME = _BOX_FN##_y2;\
			CODE;\
			++X_NAME;\
		}\
		while( --_BOX_FN##_w );\
		Y_NAME = _BOX_FN##_y1 + 1;\
		temp i2 _BOX_FN##_h = _BOX_FN##_y2 - _BOX_FN##_y1 - 1;\
		while( _BOX_FN##_h-- > 0 )\
		{\
			X_NAME = _BOX_FN##_x1;\
			CODE;\
			X_NAME = _BOX_FN##_x2;\
			CODE;\
			++Y_NAME;\
		}\
	}\
	END_DEF

#define _box_fn_eval( _BOX_FN, TLx, TLy, BRx, BRy, X_NAME, Y_NAME, CODE ) _box_fn( _BOX_FN, TLx, TLy, BRx, BRy, X_NAME, Y_NAME, CODE )
#define box_fn( TLx, TLy, BRx, BRy, X_NAME, Y_NAME, CODE ) _box_fn_eval( JOIN( _BOX_FN_, __COUNTER__ ), TLx, TLy, BRx, BRy, X_NAME, Y_NAME, CODE )

#define _canvas_draw_box( CANVAS, TLx, TLy, BRx, BRy, PIXEL, SUFFIX... ) box_fn( TLx, TLy, BRx, BRy, _X, _Y, canvas_draw_pixel##SUFFIX( CANVAS, _X, _Y, PIXEL ) );
#define canvas_draw_box( CANVAS, TLx, TLy, BRx, BRy, PIXEL ) _canvas_draw_box( CANVAS, TLx, TLy, BRx, BRy, PIXEL )
#define canvas_draw_box_safe( CANVAS, TLx, TLy, BRx, BRy, PIXEL ) _canvas_draw_box( CANVAS, TLx, TLy, BRx, BRy, PIXEL, _safe )

////////////////////////////////
/// canvas to canvas

#define canvas_draw_canvas( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp const n2 _bytes_per_row = FROM_CANVAS->size.w << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS->pixels + ( TLx ) + ( ( TLy ) * TO_CANVAS->size.w );\
		temp const pixel ref _from_ref = FROM_CANVAS->pixels;\
		temp const i4 _to_step = TO_CANVAS->size.w;\
		temp const i4 _from_step = FROM_CANVAS->size.w;\
		temp i2 _h = FROM_CANVAS->size.h;\
		do\
		{\
			bytes_copy( _to_ref, _from_ref, _bytes_per_row );\
			_to_ref += _to_step;\
			_from_ref += _from_step;\
		}\
		while( --_h );\
	}\
	END_DEF

#define canvas_draw_canvas_safe( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp const i2 _TLx = TLx;\
		temp const i2 _X = MAX( 0, _TLx );\
		temp const i2 _OFFX = _X - _TLx;\
		temp const i2 _W = i2_min( TO_CANVAS->size.w - _X, FROM_CANVAS->size.w - _OFFX );\
		skip_if( _W <= 0 );\
		temp const i2 _TLy = TLy;\
		temp const i2 _start_y = MAX( 0, _TLy );\
		temp const i2 _H = i2_min( TO_CANVAS->size.h, _TLy + FROM_CANVAS->size.h ) - _start_y;\
		skip_if( _H <= 0 );\
		temp const i2 _bytes_per_row = _W << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS->pixels + _start_y * TO_CANVAS->size.w + _X;\
		temp const pixel ref _from_ref = FROM_CANVAS->pixels + ( _start_y - _TLy ) * FROM_CANVAS->size.w + _OFFX;\
		temp const i4 _to_step = TO_CANVAS->size.w;\
		temp const i4 _from_step = FROM_CANVAS->size.w;\
		temp i2 _h = _H;\
		do\
		{\
			bytes_copy( _to_ref, _from_ref, _bytes_per_row );\
			_to_ref += _to_step;\
			_from_ref += _from_step;\
		}\
		while( --_h );\
	}\
	END_DEF

#define canvas_draw_canvas_trans( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp pixel ref _to_ref = TO_CANVAS->pixels + ( TLy ) * TO_CANVAS->size.w + ( TLx );\
		temp const pixel ref _from_ref = FROM_CANVAS->pixels;\
		temp const i2 _width = FROM_CANVAS->size.w;\
		temp const i4 _to_step = TO_CANVAS->size.w - _width;\
		temp i2 _h = FROM_CANVAS->size.h;\
		do\
		{\
			temp i2 _w = _width;\
			do\
			{\
				if( _from_ref->a )\
				{\
					val_of( _to_ref ) = val_of( _from_ref );\
				}\
				++_to_ref;\
				++_from_ref;\
			}\
			while( --_w );\
			_to_ref += _to_step;\
		}\
		while( --_h );\
	}\
	END_DEF

#define canvas_draw_canvas_trans_safe( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp const i2 _TLx = TLx;\
		temp const i2 _X = MAX( 0, _TLx );\
		temp const i2 _OFFX = _X - _TLx;\
		temp const i2 _W = i2_min( TO_CANVAS->size.w - _X, FROM_CANVAS->size.w - _OFFX );\
		skip_if( _W <= 0 );\
		temp const i2 _TLy = TLy;\
		temp const i2 _start_y = MAX( 0, _TLy );\
		temp const i2 _H = i2_min( TO_CANVAS->size.h, _TLy + FROM_CANVAS->size.h ) - _start_y;\
		skip_if( _H <= 0 );\
		temp pixel ref _to_ref = TO_CANVAS->pixels + _start_y * TO_CANVAS->size.w + _X;\
		temp const pixel ref _from_ref = FROM_CANVAS->pixels + ( _start_y - _TLy ) * FROM_CANVAS->size.w + _OFFX;\
		temp const i4 _to_step = TO_CANVAS->size.w - _W;\
		temp const i4 _from_step = FROM_CANVAS->size.w - _W;\
		temp i2 _h = _H;\
		do\
		{\
			temp i2 _w = _W;\
			do\
			{\
				if( _from_ref->a )\
				{\
					val_of( _to_ref ) = val_of( _from_ref );\
				}\
				++_to_ref;\
				++_from_ref;\
			}\
			while( --_w );\
			_to_ref += _to_step;\
			_from_ref += _from_step;\
		}\
		while( --_h );\
	}\
	END_DEF

#define canvas_draw_canvas_part( TO_CANVAS, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		temp const n2 _bytes_per_row = ( PART_SIZEw ) << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS->pixels + ( TLy ) * TO_CANVAS->size.w + ( TLx );\
		temp const pixel ref _from_ref = FROM_CANVAS->pixels + ( PART_TLy ) * FROM_CANVAS->size.w + ( PART_TLx );\
		temp const i4 _to_step = TO_CANVAS->size.w;\
		temp const i4 _from_step = FROM_CANVAS->size.w;\
		temp i2 _y = PART_SIZEh;\
		do\
		{\
			bytes_copy( _to_ref, _from_ref, _bytes_per_row );\
			_to_ref += _to_step;\
			_from_ref += _from_step;\
		}\
		while( --_y );\
	}\
	END_DEF

#define canvas_draw_canvas_part_safe( TO_CANVAS, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		temp const i2 _TLx = TLx;\
		temp const i2 _to_x = MAX( 0, _TLx );\
		temp const i2 _offset_x = _to_x - _TLx;\
		temp const i2 _from_x = PART_TLx + _offset_x;\
		temp const i2 _W = i2_min3( TO_CANVAS->size.w - _to_x, FROM_CANVAS->size.w - _from_x, PART_SIZEw - _offset_x );\
		skip_if( _W <= 0 );\
		temp const i2 _TLy = TLy;\
		temp const i2 _to_y = MAX( 0, _TLy );\
		temp const i2 _offset_y = _to_y - _TLy;\
		temp const i2 _from_y = PART_TLy + _offset_y;\
		temp const i2 _H = i2_min3( TO_CANVAS->size.h - _to_y, FROM_CANVAS->size.h - _from_y, PART_SIZEh - _offset_y );\
		skip_if( _H <= 0 );\
		temp const i2 _bytes_per_row = _W << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS->pixels + ( _to_y * TO_CANVAS->size.w ) + _to_x;\
		temp const pixel ref _from_ref = FROM_CANVAS->pixels + ( _from_y * FROM_CANVAS->size.w ) + _from_x;\
		temp const i4 _to_step = TO_CANVAS->size.w;\
		temp const i4 _from_step = FROM_CANVAS->size.w;\
		temp i2 _h = _H;\
		do\
		{\
			bytes_copy( _to_ref, _from_ref, _bytes_per_row );\
			_to_ref += _to_step;\
			_from_ref += _from_step;\
		}\
		while( --_h );\
	}\
	END_DEF

////////////////////////////////
/// inputs

group( input_type )
{
	input_none,
	input_mouse_left,
	input_mouse_middle,
	input_mouse_right,
	input_cancel,
	input_a,
	input_b,
	input_c,
	input_d,
	input_e,
	input_f,
	input_g,
	input_h,
	input_i,
	input_j,
	input_k,
	input_l,
	input_m,
	input_n,
	input_o,
	input_p,
	input_q,
	input_r,
	input_s,
	input_t,
	input_u,
	input_v,
	input_w,
	input_x,
	input_y,
	input_z,

	input_0,
	input_1,
	input_2,
	input_3,
	input_4,
	input_5,
	input_6,
	input_7,
	input_8,
	input_9,

	input_f1,
	input_f2,
	input_f3,
	input_f4,
	input_f5,
	input_f6,
	input_f7,
	input_f8,
	input_f9,
	input_f10,
	input_f11,
	input_f12,

	input_escape,
	input_tab,
	input_capslock,
	input_shift,
	input_ctrl,
	input_alt,
	input_space,
	input_enter,
	input_backspace,
	input_insert,
	input_delete,
	input_home,
	input_end,
	input_pageup,
	input_pagedown,

	input_up,
	input_down,
	input_left,
	input_right,

	input_backtick,
	input_minus,
	input_equals,
	input_leftbracket,
	input_rightbracket,
	input_backslash,
	input_semicolon,
	input_apostrophe,
	input_comma,
	input_period,
	input_slash,

	input_super,
	input_menu,

	inputs_count
};

#define INPUT_MASK_PRESSED 0x1
#define INPUT_MASK_HELD 0x2
#define INPUT_MASK_RELEASED 0x4

#define _INPUT_SET( NAME, LINUX_KEY, WINDOWS_KEY )[ PICK( OS_LINUX, LINUX_KEY, WINDOWS_KEY ) ] = input_##NAME
#define _INPUT_SET_MASKED( NAME, LINUX_KEY, WINDOWS_KEY )[ PICK( OS_LINUX, LINUX_KEY & 0x1ff, WINDOWS_KEY ) ] = input_##NAME

global byte const _INPUT_MAP[] =
	{
		_INPUT_SET( a, XK_a, 'A' ),
		_INPUT_SET( b, XK_b, 'B' ),
		_INPUT_SET( c, XK_c, 'C' ),
		_INPUT_SET( d, XK_d, 'D' ),
		_INPUT_SET( e, XK_e, 'E' ),
		_INPUT_SET( f, XK_f, 'F' ),
		_INPUT_SET( g, XK_g, 'G' ),
		_INPUT_SET( h, XK_h, 'H' ),
		_INPUT_SET( i, XK_i, 'I' ),
		_INPUT_SET( j, XK_j, 'J' ),
		_INPUT_SET( k, XK_k, 'K' ),
		_INPUT_SET( l, XK_l, 'L' ),
		_INPUT_SET( m, XK_m, 'M' ),
		_INPUT_SET( n, XK_n, 'N' ),
		_INPUT_SET( o, XK_o, 'O' ),
		_INPUT_SET( p, XK_p, 'P' ),
		_INPUT_SET( q, XK_q, 'Q' ),
		_INPUT_SET( r, XK_r, 'R' ),
		_INPUT_SET( s, XK_s, 'S' ),
		_INPUT_SET( t, XK_t, 'T' ),
		_INPUT_SET( u, XK_u, 'U' ),
		_INPUT_SET( v, XK_v, 'V' ),
		_INPUT_SET( w, XK_w, 'W' ),
		_INPUT_SET( x, XK_x, 'X' ),
		_INPUT_SET( y, XK_y, 'Y' ),
		_INPUT_SET( z, XK_z, 'Z' ),

		_INPUT_SET( 0, XK_0, '0' ),
		_INPUT_SET( 1, XK_1, '1' ),
		_INPUT_SET( 2, XK_2, '2' ),
		_INPUT_SET( 3, XK_3, '3' ),
		_INPUT_SET( 4, XK_4, '4' ),
		_INPUT_SET( 5, XK_5, '5' ),
		_INPUT_SET( 6, XK_6, '6' ),
		_INPUT_SET( 7, XK_7, '7' ),
		_INPUT_SET( 8, XK_8, '8' ),
		_INPUT_SET( 9, XK_9, '9' ),

		_INPUT_SET_MASKED( f1, XK_F1, VK_F1 ),
		_INPUT_SET_MASKED( f2, XK_F2, VK_F2 ),
		_INPUT_SET_MASKED( f3, XK_F3, VK_F3 ),
		_INPUT_SET_MASKED( f4, XK_F4, VK_F4 ),
		_INPUT_SET_MASKED( f5, XK_F5, VK_F5 ),
		_INPUT_SET_MASKED( f6, XK_F6, VK_F6 ),
		_INPUT_SET_MASKED( f7, XK_F7, VK_F7 ),
		_INPUT_SET_MASKED( f8, XK_F8, VK_F8 ),
		_INPUT_SET_MASKED( f9, XK_F9, VK_F9 ),
		_INPUT_SET_MASKED( f10, XK_F10, VK_F10 ),
		_INPUT_SET_MASKED( f11, XK_F11, VK_F11 ),
		_INPUT_SET_MASKED( f12, XK_F12, VK_F12 ),

		_INPUT_SET( space, XK_space, VK_SPACE ),
		_INPUT_SET( backtick, XK_grave, VK_OEM_3 ),
		_INPUT_SET( minus, XK_minus, VK_OEM_MINUS ),
		_INPUT_SET( equals, XK_equal, VK_OEM_PLUS ),
		_INPUT_SET( leftbracket, XK_bracketleft, VK_OEM_4 ),
		_INPUT_SET( rightbracket, XK_bracketright, VK_OEM_6 ),
		_INPUT_SET( backslash, XK_backslash, VK_OEM_5 ),
		_INPUT_SET( semicolon, XK_semicolon, VK_OEM_1 ),
		_INPUT_SET( apostrophe, XK_apostrophe, VK_OEM_7 ),
		_INPUT_SET( comma, XK_comma, VK_OEM_COMMA ),
		_INPUT_SET( period, XK_period, VK_OEM_PERIOD ),
		_INPUT_SET( slash, XK_slash, VK_OEM_2 ),

		_INPUT_SET_MASKED( backspace, XK_BackSpace, VK_BACK ),
		_INPUT_SET_MASKED( tab, XK_Tab, VK_TAB ),
		_INPUT_SET_MASKED( enter, XK_Return, VK_RETURN ),
		_INPUT_SET_MASKED( escape, XK_Escape, VK_ESCAPE ),
		_INPUT_SET_MASKED( delete, XK_Delete, VK_DELETE ),
		_INPUT_SET_MASKED( insert, XK_Insert, VK_INSERT ),
		_INPUT_SET_MASKED( home, XK_Home, VK_HOME ),
		_INPUT_SET_MASKED( end, XK_End, VK_END ),
		_INPUT_SET_MASKED( pageup, XK_Page_Up, VK_PRIOR ),
		_INPUT_SET_MASKED( pagedown, XK_Page_Down, VK_NEXT ),
		_INPUT_SET_MASKED( left, XK_Left, VK_LEFT ),
		_INPUT_SET_MASKED( up, XK_Up, VK_UP ),
		_INPUT_SET_MASKED( right, XK_Right, VK_RIGHT ),
		_INPUT_SET_MASKED( down, XK_Down, VK_DOWN ),

		_INPUT_SET_MASKED( shift, XK_Shift_L, VK_SHIFT ),
		_INPUT_SET_MASKED( ctrl, XK_Control_L, VK_CONTROL ),
		_INPUT_SET_MASKED( capslock, XK_Caps_Lock, VK_CAPITAL ),
		_INPUT_SET_MASKED( alt, XK_Alt_L, VK_MENU ),
		_INPUT_SET_MASKED( super, XK_Super_L, VK_LWIN ),
		_INPUT_SET_MASKED( menu, XK_Menu, VK_APPS ),
	};

#define key_pressed( KEY ) ( current_window->inputs[ input_##KEY ] & INPUT_MASK_PRESSED )
#define key_held( KEY ) ( current_window->inputs[ input_##KEY ] & INPUT_MASK_HELD )
#define key_released( KEY ) ( current_window->inputs[ input_##KEY ] & INPUT_MASK_RELEASED )

#define mouse_pressed( BUTTON ) key_pressed( mouse_##BUTTON )
#define mouse_held( BUTTON ) key_held( mouse_##BUTTON )
#define mouse_released( BUTTON ) key_released( mouse_##BUTTON )

#define _window_add_input_pressed( VALUE )\
	if( not( this->inputs[ VALUE ] & INPUT_MASK_HELD ) )\
	{\
		this->inputs[ VALUE ] |= INPUT_MASK_PRESSED | INPUT_MASK_HELD;\
		++this->inputs_active;\
		list_add( this->inputs_pressed, byte( VALUE ) );\
		is_input = yes;\
	}

#define _window_add_input_released( VALUE )\
	this->inputs[ VALUE ] = INPUT_MASK_RELEASED;\
	list_add( this->inputs_released, byte( VALUE ) );\
	is_input = yes

////////////////////////////////
/// windows

////////
// window canvas

group( sizing_mode )
{
	sizing_fixed,
	sizing_dynamic
};

group( scaling_mode )
{
	scaling_manual,

	scaling_integer_fit_floor,
	scaling_integer_fit_round,
	scaling_integer_fit_ceil,
	scaling_integer_fill_floor,
	scaling_integer_fill_round,
	scaling_integer_fill_ceil,
	scaling_integer_stretch_floor,
	scaling_integer_stretch_round,
	scaling_integer_stretch_ceil,

	scaling_rational_fit,
	scaling_rational_fill,
	scaling_rational_stretch
};

type( view_line )
{
	i2x2 a;
	i2x2 b;
	pixel color;
};

object( view )
{
	canvas canvas;

	sizing_mode sizing;
	scaling_mode scaling;

	flag update;
	pixel outline;
	view_fn fn_draw;
	anon ref draw_ref;
	list lines;

	r4x2 pos;
	r4x2 scale;
	r4x2 mouse;

	#if OS_LINUX
		Pixmap pixmap;
		Picture picture;
	#elif OS_WINDOWS
		//
	#endif
}
packed;

new_object_fn( view, canvas const canvas, sizing_mode const sizing, scaling_mode const scaling, view_fn const fn_draw )
{
	temp view out_view = new_object( view );
	out_view->canvas = canvas;
	out_view->sizing = sizing;
	out_view->scaling = scaling;
	out_view->update = yes;
	out_view->fn_draw = fn_draw;
	out_view->lines = new_list( view_line );
	out_view->scale = r4x2( 1.0, 1.0 );
	out out_view;
}

delete_object_fn( view )
{
	delete_canvas( this->canvas );
	delete_list( this->lines );

	delete_object( this );
}

#define view_get_scaled_size( VIEW ) r4x2( r4( VIEW->canvas->size.w ) * VIEW->scale.w, r4( VIEW->canvas->size.h ) * VIEW->scale.h )

object_fn( view, set_scale, r4x2 const scale )
{
	this->scale = scale;
	this->scaling = scaling_manual;
}
#define view_set_scale( WINDOW_CANVAS, WIDTH_SCALE, HEIGHT_SCALE... ) view_set_scale( WINDOW_CANVAS, r4x2( WIDTH_SCALE, DEFAULT( WIDTH_SCALE, HEIGHT_SCALE ) ) )

object_fn( view, zoom, i4 const x, i4 const y, r4 const factor )
{
	temp r4 const new_scale = r4_clamp( this->scale.w * factor, 0.2, 200.0 );
	temp r4 const actual_factor = new_scale / this->scale.w;
	this->pos.x = r4( x ) - r4( x - this->pos.x ) * actual_factor;
	this->pos.y = r4( y ) - r4( y - this->pos.y ) * actual_factor;
	view_set_scale( this, new_scale, new_scale );
}

object_fn( view, update )
{
	this->update = yes;
}

////////
// window

type_from( PICK( OS_LINUX, Window, HWND ) ) os_handle;
type_from( PICK( OS_LINUX, XImage ref, BITMAPINFO ) ) os_image;
type_from( PICK( OS_LINUX, XEvent, MSG ) ) os_event;

object( window )
{
	text name;

	os_handle handle;
	os_image image;

	flag using_buffer;
	pixel ref buffer_pixels;
	#if OS_LINUX
		Pixmap buffer;
		Picture buffer_picture;
	#elif OS_WINDOWS
		HBITMAP buffer;
		HDC buffer_dc;
		HDC window_dc;
	#endif

	list views;
	n2x2 size;

	flag clear : 1;
	flag visible : 1;
	flag bordered : 1;
	flag close : 1;
	flag changed_cursor : 1;

	n8 tick;
	r4 delta_time;

	byte inputs[ inputs_count ];
	n1 inputs_active;
	list inputs_pressed;
	list inputs_released;
	r4x2 scroll;
	i4x2 mouse;

	window_fn fn_start;
	window_fn fn_resize;
	window_fn fn_tick;
}
packed;

global window current_window = nothing;
global list windows = nothing;

global r4 windows_fps_tick = 0;
global r4 windows_fps_draw = 0;
global nano windows_time_start = 0;
global nano windows_time_next_draw = 0;
global n8 windows_time_tick = 0;

#define window_set_fn_start( WINDOW, FN ) WINDOW->fn_start = to( window_fn, FN )
#define window_set_fn_resize( WINDOW, FN ) WINDOW->fn_resize = to( window_fn, FN )
#define window_set_fn_tick( WINDOW, FN ) WINDOW->fn_tick = to( window_fn, FN )

#if OS_LINUX
	global Display ref windows_display = nothing;
#elif OS_WINDOWS
	global HICON windows_icon = nothing;
#endif

////////
// display

embed n2 const display_get_width()
{
	#if OS_LINUX
		out n2( DisplayWidth( windows_display, DefaultScreen( windows_display ) ) );
	#elif OS_WINDOWS
		out n2( GetSystemMetrics( SM_CXSCREEN ) );
	#endif
}

embed n2 const display_get_height()
{
	#if OS_LINUX
		out n2( DisplayHeight( windows_display, DefaultScreen( windows_display ) ) );
	#elif OS_WINDOWS
		out n2( GetSystemMetrics( SM_CYSCREEN ) );
	#endif
}

fn display_get_mouse_position( i4 ref const out_x, i4 ref const out_y )
{
	#if OS_LINUX
		Window root,
		child;
		i4 win_x,
		win_y;
		n4 mask;
		XQueryPointer( windows_display, DefaultRootWindow( windows_display ), ref_of( root ), ref_of( child ), out_x, out_y, ref_of( win_x ), ref_of( win_y ), ref_of( mask ) );
	#elif OS_WINDOWS
		POINT cursor;
		GetCursorPos( ref_of( cursor ) );
		val_of( out_x ) = cursor.x;
		val_of( out_y ) = cursor.y;
	#endif
}

embed n2 const display_get_fps()
{
	#if OS_LINUX
		temp XRRScreenConfiguration * config = XRRGetScreenInfo( windows_display, DefaultRootWindow( windows_display ) );
		temp n2 const hz = n2( XRRConfigCurrentRate( config ) );
		XRRFreeScreenConfigInfo( config );
		out hz;
	#elif OS_WINDOWS
		DEVMODE dm = { };
		dm.dmSize = sizeof( dm );
		EnumDisplaySettings( nothing, ENUM_CURRENT_SETTINGS, ref_of( dm ) );
		out n2( dm.dmDisplayFrequency );
	#endif
}

////////
// visible window functions

// view via window

object_fn( view, center )
{
	out_if_nothing( this->canvas );
	//
	temp i4 const scaled_w = i4( r4_round( r4( this->canvas->size.w ) * this->scale.w ) );
	temp i4 const scaled_h = i4( r4_round( r4( this->canvas->size.h ) * this->scale.h ) );
	this->pos.x = r4( i4( current_window->size.w ) - scaled_w ) * 0.5;
	this->pos.y = r4( i4( current_window->size.h ) - scaled_h ) * 0.5;
}

object_fn( view, clamp )
{
	temp r4x2 const scaled_size = view_get_scaled_size( this );

	with( this->scaling )
	{
		when( scaling_rational_fit, scaling_integer_fit_floor, scaling_integer_fit_round, scaling_integer_fit_ceil )
		{
			this->pos.x = r4_clamp( this->pos.x, 0, r4( current_window->size.w ) - scaled_size.w );
			this->pos.y = r4_clamp( this->pos.y, 0, r4( current_window->size.h ) - scaled_size.h );
			skip;
		}

		when( scaling_rational_fill, scaling_integer_fill_floor, scaling_integer_fill_round, scaling_integer_fill_ceil )
		{
			this->pos.x = r4_clamp( this->pos.x, r4( current_window->size.w ) - scaled_size.w, 0 );
			this->pos.y = r4_clamp( this->pos.y, r4( current_window->size.h ) - scaled_size.h, 0 );
			skip;
		}

		when( scaling_manual )
		{
			temp i4 const margin = i4_min( current_window->size.w, current_window->size.h ) >> 2;
			this->pos.x = r4_clamp( this->pos.x, -scaled_size.w + r4( margin ), r4( i4( current_window->size.w ) - margin ) );
			this->pos.y = r4_clamp( this->pos.y, -scaled_size.h + r4( margin ), r4( i4( current_window->size.h ) - margin ) );
			skip;
		}

		when( scaling_rational_stretch )
		{
			this->pos = r4x2();
			skip;
		}

		other skip;
	}
}

object_fn( window, add_view, view in_view )
{
	list_add( this->views, in_view );
}

// window

#define window_clear( WINDOW ) WINDOW->clear = yes

object_fn( window, update )
{
	#if OS_LINUX
		XClearArea( windows_display, this->handle, 0, 0, 0, 0, yes );
	#elif OS_WINDOWS
		InvalidateRect( this->handle, nothing, this->clear );
		//UpdateWindow( this->handle );
	#endif
}

object_fn( window, set_size, n2 const width, n2 const height )
{
	#if OS_LINUX
		XResizeWindow( windows_display, this->handle, width, height );
		XSync( windows_display, no );
	#elif OS_WINDOWS
		if( this->bordered )
		{
			RECT rect = { 0, 0, width, height };
			AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );
			SetWindowPos( this->handle, nothing, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );
		}
		else
		{
			SetWindowPos( this->handle, nothing, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );
		}
	#endif
}

object_fn( window, get_position, i4 ref const out_x, i4 ref const out_y )
{
	#if OS_LINUX
		Window child;
		XTranslateCoordinates( windows_display, this->handle, DefaultRootWindow( windows_display ), 0, 0, out_x, out_y, ref_of( child ) );
	#elif OS_WINDOWS
		RECT rect;
		GetWindowRect( this->handle, ref_of( rect ) );
		val_of( out_x ) = rect.left;
		val_of( out_y ) = rect.top;
	#endif
}

object_fn( window, set_position, i4 const x, i4 const y )
{
	#if OS_LINUX
		XMoveWindow( windows_display, this->handle, x, y );
		XSync( windows_display, no );
	#elif OS_WINDOWS
		SetWindowPos( this->handle, nothing, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	#endif
}

object_fn( window, get_mouse_position, i4 ref const out_x, i4 ref const out_y )
{
	#if OS_LINUX
		Window root,
		child;
		i4 root_x,
		root_y;
		n4 mask;
		XQueryPointer( windows_display, this->handle, ref_of( root ), ref_of( child ), ref_of( root_x ), ref_of( root_y ), out_x, out_y, ref_of( mask ) );
	#elif OS_WINDOWS
		POINT cursor;
		GetCursorPos( ref_of( cursor ) );
		ScreenToClient( this->handle, ref_of( cursor ) );
		val_of( out_x ) = cursor.x;
		val_of( out_y ) = cursor.y;
	#endif
}

object_fn( window, show )
{
	out_if( this->visible is yes );

	#if OS_LINUX
		XMapRaised( windows_display, this->handle );
		XSync( windows_display, no );
	#elif OS_WINDOWS
		SetFocus( this->handle );
		SetForegroundWindow( this->handle );
		ShowWindow( this->handle, SW_SHOWNOACTIVATE );
	#endif

	this->visible = yes;
}

object_fn( window, hide )
{
	out_if( this->visible is no );

	#if OS_LINUX
		XUnmapWindow( windows_display, this->handle );
	#elif OS_WINDOWS
		ShowWindow( this->handle, SW_HIDE );
	#endif

	this->visible = no;
}

object_fn( window, toggle_visible )
{
	if( this->visible )
	{
		window_hide( this );
	}
	else
	{
		window_show( this );
	}
}

object_fn( window, show_border )
{
	out_if( this->bordered is yes );

	#if OS_LINUX
		i4 orig_x,
		orig_y;
		window_get_position( this, ref_of( orig_x ), ref_of( orig_y ) );

		Atom prop = XInternAtom( windows_display, "_MOTIF_WM_HINTS", False );
		XDeleteProperty( windows_display, this->handle, prop );
		XWithdrawWindow( windows_display, this->handle, DefaultScreen( windows_display ) );
		XMapWindow( windows_display, this->handle );
		XSync( windows_display, no );

		window_set_position( this, orig_x, orig_y );
	#elif OS_WINDOWS
		temp n2 client_w = this->size.w;
		temp n2 client_h = this->size.h;

		POINT client_pos = { 0, 0 };
		ClientToScreen( this->handle, ref_of( client_pos ) );

		temp LONG_PTR style = GetWindowLongPtr( this->handle, GWL_STYLE );
		style |= WS_OVERLAPPEDWINDOW;
		SetWindowLongPtr( this->handle, GWL_STYLE, style );

		RECT rect = { 0, 0, client_w, client_h };
		AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );

		SetWindowPos( this->handle, nothing, client_pos.x + rect.left, client_pos.y + rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_FRAMECHANGED | SWP_NOZORDER );
	#endif

	this->bordered = yes;
}

object_fn( window, hide_border )
{
	out_if( this->bordered is no );

	#if OS_LINUX
		Window child;
		i4 x,
		y;
		XTranslateCoordinates( windows_display, this->handle, DefaultRootWindow( windows_display ), 0, 0, ref_of( x ), ref_of( y ), ref_of( child ) );

		variant
		{
			n4 flags;
			n4 functions;
			n4 decorations;
			i4 input_mode;
			n4 status;
		}
		hints = { 2, 0, 0, 0, 0 };
		Atom prop = XInternAtom( windows_display, "_MOTIF_WM_HINTS", False );
		XChangeProperty( windows_display, this->handle, prop, prop, 32, PropModeReplace, to( n1 ref, ref_of( hints ) ), 5 );
		XWithdrawWindow( windows_display, this->handle, DefaultScreen( windows_display ) );
		XMapWindow( windows_display, this->handle );
		XMoveWindow( windows_display, this->handle, x, y );
		XSync( windows_display, no );
	#elif OS_WINDOWS
		temp n2 client_w = this->size.w;
		temp n2 client_h = this->size.h;

		POINT client_pos = { 0, 0 };
		ClientToScreen( this->handle, ref_of( client_pos ) );

		temp LONG_PTR style = GetWindowLongPtr( this->handle, GWL_STYLE );
		style &= ~ ( WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU );
		SetWindowLongPtr( this->handle, GWL_STYLE, style );

		SetWindowPos( this->handle, nothing, client_pos.x, client_pos.y, client_w, client_h, SWP_FRAMECHANGED | SWP_NOZORDER );
	#endif

	this->bordered = no;
}

object_fn( window, toggle_border )
{
	if( this->bordered )
	{
		window_hide_border( this );
	}
	else
	{
		window_show_border( this );
	}
}

object_fn( window, center )
{
	#if OS_LINUX
		XMoveWindow( windows_display, this->handle, ( display_get_width() - this->size.w ) >> 1, ( display_get_height() - this->size.h ) >> 1 );
		XSync( windows_display, no );
	#elif OS_WINDOWS
		SetWindowPos( this->handle, nothing, ( display_get_width() - this->size.w ) >> 1, ( display_get_height() - this->size.h ) >> 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	#endif
}

////////
// cursor

group( cursor_type, i4 )
{
	cursor_arrow = PICK( OS_LINUX, XC_left_ptr, 32512 ),
	cursor_hand = PICK( OS_LINUX, XC_hand2, 32649 ),
	cursor_text = PICK( OS_LINUX, XC_xterm, 32513 ),
	cursor_crosshair = PICK( OS_LINUX, XC_crosshair, 32515 ),
	cursor_move = PICK( OS_LINUX, XC_fleur, 32646 ),
	cursor_size_horizontal = PICK( OS_LINUX, XC_sb_h_double_arrow, 32644 ),
	cursor_size_vertical = PICK( OS_LINUX, XC_sb_v_double_arrow, 32645 ),
	cursor_size_nwse = PICK( OS_LINUX, XC_bottom_right_corner, 32642 ),
	cursor_size_nesw = PICK( OS_LINUX, XC_bottom_left_corner, 32643 ),
	cursor_wait = PICK( OS_LINUX, XC_watch, 32514 ),
	cursor_not_allowed = PICK( OS_LINUX, XC_X_cursor, 32648 )
};

object_fn( window, set_cursor, cursor_type const cursor )
{
	this->changed_cursor = yes;
	#if OS_LINUX
		perm Cursor cache[ 256 ] = { 0 };
		if( not cache[ cursor ] )
		{
			cache[ cursor ] = XCreateFontCursor( windows_display, cursor );
		}
		XDefineCursor( windows_display, this->handle, cache[ cursor ] );
	#else
		SetCursor( LoadCursor( NULL, MAKEINTRESOURCE( cursor ) ) );
	#endif
}

////////
// hidden window functions

fn _window_clear_inputs( window const this )
{
	bytes_clear( this->inputs, inputs_count );
	this->inputs_active = 0;
	list_clear( this->inputs_pressed );
	list_clear( this->inputs_released );
}

fn _window_set_size( window const this, n2 const width, n2 const height )
{
	out_if( this->size.w is width and this->size.h is height );
	this->size.w = width;
	this->size.h = height;
}

fn _window_resize( window const this )
{
	out_if_any( this is nothing, this->size.w <= 1, this->size.h <= 1 );

	this->using_buffer = this->using_buffer or( this->views->count > 1 );

	#if OS_LINUX
		temp n4 const screen = DefaultScreen( windows_display );
		temp n4 const depth = DefaultDepth( windows_display, screen );
		temp XRenderPictFormat ref format = XRenderFindVisualFormat( windows_display, DefaultVisual( windows_display, screen ) );

		if( this->using_buffer )
		{
			if( this->buffer_picture )
			{
				XRenderFreePicture( windows_display, this->buffer_picture );
			}

			if( this->buffer )
			{
				XFreePixmap( windows_display, this->buffer );
			}

			this->buffer = XCreatePixmap( windows_display, this->handle, this->size.w, this->size.h, depth );

			temp GC temp_gc = XCreateGC( windows_display, this->buffer, 0, nothing );
			XSetForeground( windows_display, temp_gc, BlackPixel( windows_display, screen ) );
			XFillRectangle( windows_display, this->buffer, temp_gc, 0, 0, this->size.w, this->size.h );
			XFreeGC( windows_display, temp_gc );

			this->buffer_picture = XRenderCreatePicture( windows_display, this->buffer, format, 0, nothing );
		}
	#elif OS_WINDOWS
		if( this->using_buffer )
		{
			if( this->buffer )
			{
				DeleteObject( this->buffer );
			}

			if( this->buffer_dc )
			{
				DeleteDC( this->buffer_dc );
			}

			BITMAPINFO bmi = { sizeof( bmi.bmiHeader ), this->size.w, -this->size.h, 1, 32, BI_RGB };
			this->buffer = CreateDIBSection( this->window_dc, ref_of( bmi ), DIB_RGB_COLORS, to( anon ref ref, ref_of( this->buffer_pixels ) ), nothing, 0 );
			this->buffer_dc = CreateCompatibleDC( this->window_dc );
			SelectObject( this->buffer_dc, this->buffer );
		}
	#endif

	list_iter( this->views, view_index )
	{
		temp view const this_view = list_get_iter( view_index, view );

		with( this_view->scaling )
		{
			when( scaling_integer_fit_floor, scaling_integer_fit_round, scaling_integer_fit_ceil, scaling_rational_fit )
			{
				temp r4 const scale = r4_min( r4( this->size.w ) / r4( this_view->canvas->size.w ), r4( this->size.h ) / r4( this_view->canvas->size.h ) );
				this_view->scale.w = scale;
				this_view->scale.h = scale;
				skip;
			}

			when( scaling_integer_fill_floor, scaling_integer_fill_round, scaling_integer_fill_ceil, scaling_rational_fill )
			{
				temp r4 const scale = r4_max( r4( this->size.w ) / r4( this_view->canvas->size.w ), r4( this->size.h ) / r4( this_view->canvas->size.h ) );
				this_view->scale.w = scale;
				this_view->scale.h = scale;
				skip;
			}

			when( scaling_integer_stretch_floor, scaling_integer_stretch_round, scaling_integer_stretch_ceil, scaling_rational_stretch )
			{
				this_view->scale.w = r4( this->size.w ) / r4( this_view->canvas->size.w );
				this_view->scale.h = r4( this->size.h ) / r4( this_view->canvas->size.h );
				skip;
			}

			other skip;
		}

		with( this_view->scaling )
		{
			when( scaling_integer_stretch_floor )
			{
				this_view->scale.w = r4_floor( this_view->scale.w );
				this_view->scale.h = r4_floor( this_view->scale.h );
				skip;
			}

			when( scaling_integer_stretch_ceil )
			{
				this_view->scale.w = r4_ceil( this_view->scale.w );
				this_view->scale.h = r4_ceil( this_view->scale.h );
				skip;
			}

			when( scaling_integer_stretch_round )
			{
				this_view->scale.w = r4_round( this_view->scale.w );
				this_view->scale.h = r4_round( this_view->scale.h );
				skip;
			}

			when( scaling_integer_fit_floor, scaling_integer_fill_floor )
			{
				temp r4 const scale = r4_floor( this_view->scale.w );
				this_view->scale.w = scale;
				this_view->scale.h = scale;
				skip;
			}

			when( scaling_integer_fit_ceil, scaling_integer_fill_ceil )
			{
				temp r4 const scale = r4_ceil( this_view->scale.w );
				this_view->scale.w = scale;
				this_view->scale.h = scale;
				skip;
			}

			when( scaling_integer_fit_round, scaling_integer_fill_round )
			{
				temp r4 const scale = r4_round( this_view->scale.w );
				this_view->scale.w = scale;
				this_view->scale.h = scale;
				skip;
			}

			other skip;
		}

		#if OS_LINUX
			if( this_view->pixmap )
			{
				XRenderFreePicture( windows_display, this_view->picture );
				XFreePixmap( windows_display, this_view->pixmap );
			}

			this_view->pixmap = XCreatePixmap( windows_display, this->handle, this_view->canvas->size.w, this_view->canvas->size.h, depth );
			this_view->picture = XRenderCreatePicture( windows_display, this_view->pixmap, format, 0, 0 );
		#endif
	}

	call( this, fn_resize );
}

fn _window_tick_once( window const this )
{
	window_get_mouse_position( this, ref_of( this->mouse.x ), ref_of( this->mouse.y ) );

	list_iter( this->views, view_index )
	{
		temp view const this_view = list_get_iter( view_index, view );
		this_view->mouse = r4x2( r4( this->mouse.x - this_view->pos.x ) / this_view->scale.w, r4( this->mouse.y - this_view->pos.y ) / this_view->scale.h );
	}

	perm nano start_nano = 0;
	once start_nano = get_nano();

	this->delta_time = r4( get_nano() - start_nano ) / r4( nano_per_sec );
	start_nano = get_nano();

	call( this, fn_tick );

	if( this->inputs_pressed->count > 0 )
	{
		list_iter( this->inputs_pressed, input_index )
		{
			temp byte ref const input_ref = ref_of( list_get_iter( input_index, byte ) );
			this->inputs[ val_of( input_ref ) ] = INPUT_MASK_HELD;
			val_of( input_ref ) = 0;
		}
		list_clear( this->inputs_pressed );
	}

	if( this->inputs_released->count > 0 )
	{
		list_iter( this->inputs_released, input_index )
		{
			temp byte ref const input_ref = ref_of( list_get_iter( input_index, byte ) );
			this->inputs[ val_of( input_ref ) ] = 0;
			--this->inputs_active;
			val_of( input_ref ) = 0;
		}
		list_clear( this->inputs_released );
	}

	this->scroll = r4x2();
}

fn _window_draw( window const this )
{
	list_iter( this->views, view_index )
	{
		temp view const this_view = list_get_iter( view_index, view );
		next_if( this_view->update is no );
		call( this_view, fn_draw );
		this_view->update = no;
	}
}

fn _window_present( window const this )
{
	this->using_buffer = this->using_buffer or this->views->count > 1;

	#if OS_LINUX
		perm GC gc = nothing;
		perm XRenderPictFormat ref format = nothing;
		perm Picture window_picture = 0;
		perm XTransform transform = { 0 };
		perm XRenderColor black = { 0, 0, 0, 0xffff };

		once
		{
			gc = XCreateGC( windows_display, this->handle, 0, nothing );
			XSetForeground( windows_display, gc, 0 );
			format = XRenderFindVisualFormat( windows_display, DefaultVisual( windows_display, DefaultScreen( windows_display ) ) );
			window_picture = XRenderCreatePicture( windows_display, this->handle, format, 0, nothing );
			transform.matrix[ 2 ][ 2 ] = XDoubleToFixed( 1.0 );
			XPresentSelectInput( windows_display, this->handle, PresentCompleteNotifyMask );
		}
		temp Picture const target_picture = pick( this->using_buffer, this->buffer_picture, window_picture );
		temp Drawable const target_drawable = pick( this->using_buffer, this->buffer, this->handle );
	#elif OS_WINDOWS
		temp HDC const target_dc = pick( this->using_buffer, this->buffer_dc, this->window_dc );
		perm HBRUSH black_brush = nothing;
		once black_brush = to( HBRUSH, GetStockObject( BLACK_BRUSH ) );
	#endif

	temp i4 const win_w = this->size.w;
	temp i4 const win_h = this->size.h;
	temp flag const needs_clear = this->clear;

	this->clear = no;

	if( needs_clear and this->using_buffer is yes )
	{
		#if OS_LINUX
			XRenderFillRectangle( windows_display, PictOpSrc, target_picture, ref_of( black ), 0, 0, win_w, win_h );
		#elif OS_WINDOWS
			PatBlt( target_dc, 0, 0, win_w, win_h, BLACKNESS );
		#endif
	}

	temp i4 view_l = 0;
	temp i4 view_t = 0;
	temp i4 view_r = win_w;
	temp i4 view_b = win_h;

	list_iter( this->views, view_index )
	{
		temp view const this_view = list_get_iter( view_index, view );
		temp r4x2 const scaled_size = view_get_scaled_size( this_view );

		skip_if( scaled_size.w is 0 or scaled_size.h is 0 );

		temp i4 const canvas_w = this_view->canvas->size.w;
		temp i4 const canvas_h = this_view->canvas->size.h;

		view_l = i4( r4_round( this_view->pos.x ) );
		view_t = i4( r4_round( this_view->pos.y ) );
		view_r = view_l + i4( r4_round( scaled_size.w ) );
		view_b = view_t + i4( r4_round( scaled_size.h ) );

		#if OS_LINUX
			this->image->data = to( byte ref, this_view->canvas->pixels );
			this->image->width = canvas_w;
			this->image->height = canvas_h;
			this->image->bytes_per_line = canvas_w << pixel_shift;
		#elif OS_WINDOWS
			this->image.bmiHeader.biWidth = canvas_w;
			this->image.bmiHeader.biHeight = -canvas_h;
		#endif

		temp r4 const scale_w = this_view->scale.w;
		temp r4 const scale_h = this_view->scale.h;

		if( scale_w is 1.0 and scale_h is 1.0 )
		{
			#if OS_LINUX
				XPutImage( windows_display, target_drawable, gc, this->image, 0, 0, view_l, view_t, canvas_w, canvas_h );
			#elif OS_WINDOWS
				SetDIBitsToDevice( target_dc, view_l, view_t, canvas_w, canvas_h, 0, 0, 0, canvas_h, this_view->canvas->pixels, ref_of( this->image ), DIB_RGB_COLORS );
			#endif
		}
		else
		{
			temp r4 const clip_l = r4_max( 0, this_view->pos.x );
			temp r4 const clip_t = r4_max( 0, this_view->pos.y );
			temp r4 const clip_r = r4_min( r4( win_w ), this_view->pos.x + scaled_size.w );
			temp r4 const clip_b = r4_min( r4( win_h ), this_view->pos.y + scaled_size.h );
			skip_if( clip_r <= clip_l or clip_b <= clip_t );

			temp r4 const off_l = clip_l - this_view->pos.x;
			temp r4 const off_t = clip_t - this_view->pos.y;
			temp r4 const off_r = clip_r - this_view->pos.x;
			temp r4 const off_b = clip_b - this_view->pos.y;

			#if OS_LINUX
				XPutImage( windows_display, this_view->pixmap, gc, this->image, 0, 0, 0, 0, canvas_w, canvas_h );
				transform.matrix[ 0 ][ 0 ] = XDoubleToFixed( 1.0 / scale_w );
				transform.matrix[ 1 ][ 1 ] = XDoubleToFixed( 1.0 / scale_h );
				XRenderSetPictureTransform( windows_display, this_view->picture, ref_of( transform ) );
				XRenderComposite( windows_display, PictOpSrc, this_view->picture, None, target_picture, i4( r4_round( off_l ) ), i4( r4_round( off_t ) ), 0, 0, i4( r4_round( clip_l ) ), i4( r4_round( clip_t ) ), i4( r4_round( clip_r - clip_l ) ), i4( r4_round( clip_b - clip_t ) ) );
			#elif OS_WINDOWS
				temp r4 const src_l = r4_floor( off_l / scale_w );
				temp r4 const src_t = r4_floor( off_t / scale_h );
				temp r4 const src_r = r4_ceil( off_r / scale_w );
				temp r4 const src_b = r4_ceil( off_b / scale_h );

				SetStretchBltMode( target_dc, pick( scale_w < 1.0 or scale_h < 1.0, HALFTONE, COLORONCOLOR ) );
				StretchDIBits( target_dc, i4( r4_round( this_view->pos.x + src_l * scale_w ) ), i4( r4_round( this_view->pos.y + src_t * scale_h ) ), i4( r4_round( ( src_r - src_l ) * scale_w ) ), i4( r4_round( ( src_b - src_t ) * scale_h ) ), i4( src_l ), i4( r4( canvas_h ) - src_b ), i4( src_r - src_l ), i4( src_b - src_t ), this_view->canvas->pixels, ref_of( this->image ), DIB_RGB_COLORS, SRCCOPY );
			#endif
		}

		if( this_view->outline.a isnt 0 )
{
    temp i4 const outline_l = view_l - 1;
    temp i4 const outline_t = view_t - 1;
    temp i4 const outline_r = view_r;
    temp i4 const outline_b = view_b;

    #if OS_LINUX
        XSetForeground( windows_display, gc, ( n4( this_view->outline.r ) << 16 ) | ( n4( this_view->outline.g ) << 8 ) | n4( this_view->outline.b ) );
        XDrawRectangle( windows_display, target_drawable, gc, outline_l, outline_t, outline_r - outline_l, outline_b - outline_t );
    #elif OS_WINDOWS
        perm HBRUSH null_brush = nothing;
        once null_brush = to( HBRUSH, GetStockObject( NULL_BRUSH ) );

				temp HPEN color_pen = CreatePen( PS_SOLID, 1, RGB( this_view->outline.r, this_view->outline.g, this_view->outline.b ) );
        HPEN old_pen = to( HPEN, SelectObject( target_dc, color_pen ) );
        HBRUSH old_brush = to( HBRUSH, SelectObject( target_dc, null_brush ) );
        Rectangle( target_dc, outline_l, outline_t, outline_r + 1, outline_b + 1 );
        SelectObject( target_dc, old_pen );
        SelectObject( target_dc, old_brush );
    #endif
}

		// lines
		list_iter( this_view->lines, line_id )
		{
			temp view_line const this_line = list_get_iter( line_id, view_line );

			temp i4 const ax = view_l + i4( r4_round( r4( this_line.a.x ) * scale_w ) );
			temp i4 const ay = view_t + i4( r4_round( r4( this_line.a.y ) * scale_h ) );
			temp i4 const bx = view_l + i4( r4_round( r4( this_line.b.x ) * scale_w ) );
			temp i4 const by = view_t + i4( r4_round( r4( this_line.b.y ) * scale_h ) );

			temp pixel const color = this_line.color;

			#if OS_LINUX
				XSetForeground( windows_display, gc, ( n4( color.r ) << 16 ) | ( n4( color.g ) << 8 ) | n4( color.b ) );
				XDrawLine( windows_display, target_drawable, gc, ax, ay, bx, by );
			#elif OS_WINDOWS
				temp HPEN color_pen = CreatePen( PS_SOLID, 1, RGB( color.r, color.g, color.b ) );
				temp HPEN old_pen = to( HPEN, SelectObject( target_dc, color_pen ) );
				MoveToEx( target_dc, ax, ay, nothing );
				LineTo( target_dc, bx, by );
				SelectObject( target_dc, old_pen );
				DeleteObject( color_pen );
			#endif
		}
		list_clear( this_view->lines );
	}

	if( needs_clear and this->using_buffer is no )
	{
		temp i4 const ct = i4_max( 0, view_t );
		temp i4 const cb = i4_min( win_h, view_b );

		if( view_t > 0 )
		{
			#if OS_LINUX
				XRenderFillRectangle( windows_display, PictOpSrc, window_picture, ref_of( black ), 0, 0, win_w, view_t );
			#elif OS_WINDOWS
				RECT rc = { 0, 0, win_w, view_t };
				FillRect( target_dc, ref_of( rc ), black_brush );
			#endif
		}

		if( view_b < win_h )
		{
			#if OS_LINUX
				XRenderFillRectangle( windows_display, PictOpSrc, window_picture, ref_of( black ), 0, view_b, win_w, win_h - view_b );
			#elif OS_WINDOWS
				RECT rc = { 0, view_b, win_w, win_h };
				FillRect( target_dc, ref_of( rc ), black_brush );
			#endif
		}

		if( view_l > 0 )
		{
			#if OS_LINUX
				XRenderFillRectangle( windows_display, PictOpSrc, window_picture, ref_of( black ), 0, ct, view_l, cb - ct );
			#elif OS_WINDOWS
				RECT rc = { 0, ct, view_l, cb };
				FillRect( target_dc, ref_of( rc ), black_brush );
			#endif
		}

		if( view_r < win_w )
		{
			#if OS_LINUX
				XRenderFillRectangle( windows_display, PictOpSrc, window_picture, ref_of( black ), view_r, ct, win_w - view_r, cb - ct );
			#elif OS_WINDOWS
				RECT rc = { view_r, ct, win_w, cb };
				FillRect( target_dc, ref_of( rc ), black_brush );
			#endif
		}
	}

	if( this->using_buffer is yes )
	{
		#if OS_LINUX
			XPresentPixmap( windows_display, this->handle, this->buffer, 0, 0, 0, 0, 0, 0, 0, 0, PresentOptionAsync, 0, 0, 0, 0, 0 );
		#elif OS_WINDOWS
			BitBlt( this->window_dc, 0, 0, win_w, win_h, this->buffer_dc, 0, 0, SRCCOPY );
		#endif
	}
}

////////
// window events

group( window_event_type, n2 )
{
	window_event_resize = PICK( OS_LINUX, ConfigureNotify, WM_SIZE ),
	window_event_draw = PICK( OS_LINUX, Expose, WM_PAINT ),
	window_event_close = PICK( OS_LINUX, ClientMessage, WM_DESTROY ),
	window_event_key_activate = PICK( OS_LINUX, KeyPress, WM_KEYDOWN ),
	window_event_key_deactivate = PICK( OS_LINUX, KeyRelease, WM_KEYUP ),
	window_event_mouse_move = PICK( OS_LINUX, MotionNotify, WM_MOUSEMOVE ),
	window_event_focus_lost = PICK( OS_LINUX, FocusOut, WM_KILLFOCUS )
};

#if OS_LINUX
	embed out_state window_process_event( window const this, window_event_type const event, os_event const ref e )
#elif OS_WINDOWS
	embed LRESULT CALLBACK window_process_event( os_handle const h, window_event_type const event, WPARAM const wp, LPARAM const lp )
#endif
{
	#if OS_WINDOWS
		temp window this = to( window, GetWindowLongPtr( h, GWLP_USERDATA ) );
	#endif
	jump_if_nothing( this ) exit_events;

	temp flag is_input = no;

	with( event )
	{
		#if OS_WINDOWS
			when( WM_ENTERSIZEMOVE )
			{
				SetTimer( h, 1, 0, nothing );
				skip;
			}

			when( WM_EXITSIZEMOVE )
			{
				KillTimer( h, 1 );
				skip;
			}

			when( WM_TIMER )
			{
				skip_if( wp isnt 1 );

				_window_tick_once( this );
				jump WINDOW_PRESENT;
			}

			when( WM_ERASEBKGND )
			{
				out 1;
			}

			when( WM_SETCURSOR )
			{
				if( LOWORD( lp ) is HTCLIENT )
				{
					if( this->changed_cursor is no )
					{
						SetCursor( LoadCursor( nothing, IDC_ARROW ) );
					}
					else
					{
						this->changed_cursor = no;
					}
					out yes;
				}
				skip;
			}

			when( WM_NCPAINT )
			{
				skip_if( this->bordered is yes );
				out 1;
			}
		#endif

		when( window_event_focus_lost )
		{
			_window_clear_inputs( this );
			skip;
		}

		when( window_event_resize )
		{
			#if OS_LINUX
				temp n2 w = e->xconfigure.width;
				temp n2 h = e->xconfigure.height;
				// drain to get latest
				os_event next_resize;
				while( XCheckTypedWindowEvent( windows_display, this->handle, ConfigureNotify, ref_of( next_resize ) ) )
				{
					w = next_resize.xconfigure.width;
					h = next_resize.xconfigure.height;
				}
				_window_set_size( this, w, h );
			#elif OS_WINDOWS
				_window_set_size( this, LOWORD( lp ), HIWORD( lp ) );
			#endif
			_window_resize( this );

			//DRAW_AND_PRESENT:
			//_window_draw( this );
		} // fall through

		when( window_event_draw )
		{
			#if OS_LINUX
				skip_if( e->xexpose.count isnt 0 );
			#endif

			#if OS_WINDOWS
				//PAINTSTRUCT ps;
				//BeginPaint( this->handle, & ps );
			#endif
			//ValidateRect(this->handle, nothing);

			WINDOW_PRESENT:
			_window_draw( this );
			_window_present( this );

			#if OS_WINDOWS

				//EndPaint( this->handle, & ps );
			#endif
			skip;
		}

		//

		when( window_event_mouse_move )
		{
			#if OS_LINUX
				// drain to get latest
				os_event next_move;
				while( XCheckTypedWindowEvent( windows_display, this->handle, MotionNotify, ref_of( next_move ) ) );
			#endif
			is_input = yes;
			skip;
		}

		when( window_event_key_activate )
		{
			temp byte key = _INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( windows_display, e->xkey.keycode, 0, 0 ) & 0x1ff, wp & 0xff ) ];
			_window_add_input_pressed( key );
			skip;
		}

		when( window_event_key_deactivate )
		{
			temp byte key = _INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( windows_display, e->xkey.keycode, 0, 0 ) & 0x1ff, wp & 0xff ) ];
			_window_add_input_released( key );
			skip;
		}

		#if OS_LINUX
			when( ButtonPress )
			{
				with( e->xbutton.button )
				{
					when( Button1 )
					{
						_window_add_input_pressed( input_mouse_left );
						skip;
					}

					when( Button2 )
					{
						_window_add_input_pressed( input_mouse_middle );
						skip;
					}

					when( Button3 )
					{
						_window_add_input_pressed( input_mouse_right );
						skip;
					}

					when( 4 )
					{
						this->scroll.y += 1.0f;
						is_input = yes;
						skip;
					}

					when( 5 )
					{
						this->scroll.y -= 1.0f;
						is_input = yes;
						skip;
					}

					when( 6 )
					{
						this->scroll.x += 1.0f;
						is_input = yes;
						skip;
					}

					when( 7 )
					{
						this->scroll.x -= 1.0f;
						is_input = yes;
						skip;
					}
				}
				skip;
			}

			when( ButtonRelease )
			{
				with( e->xbutton.button )
				{
					when( Button1 )
					{
						_window_add_input_released( input_mouse_left );
						skip;
					}

					when( Button2 )
					{
						_window_add_input_released( input_mouse_middle );
						skip;
					}

					when( Button3 )
					{
						_window_add_input_released( input_mouse_right );
						skip;
					}
				}
				skip;
			}
		#elif OS_WINDOWS
			when( WM_LBUTTONDOWN )
			{
				_window_add_input_pressed( input_mouse_left );
				skip;
			}

			when( WM_MBUTTONDOWN )
			{
				_window_add_input_pressed( input_mouse_middle );
				skip;
			}

			when( WM_RBUTTONDOWN )
			{
				_window_add_input_pressed( input_mouse_right );
				skip;
			}

			when( WM_LBUTTONUP )
			{
				_window_add_input_released( input_mouse_left );
				skip;
			}

			when( WM_MBUTTONUP )
			{
				_window_add_input_released( input_mouse_middle );
				skip;
			}

			when( WM_RBUTTONUP )
			{
				_window_add_input_released( input_mouse_right );
				skip;
			}

			when( WM_MOUSEWHEEL )
			{
				this->scroll.y += r4_sign( GET_WHEEL_DELTA_WPARAM( wp ) );
				is_input = yes;
				skip;
			}

			when( WM_MOUSEHWHEEL )
			{
				this->scroll.x += r4_sign( GET_WHEEL_DELTA_WPARAM( wp ) );
				is_input = yes;
				skip;
			}
		#endif

		when( window_event_close )
		{
			#if OS_WINDOWS
				PostQuitMessage( 0 );
			#endif

			this->close = yes;

			out success;
		}

		other skip;
	}

	if( windows_fps_tick is 0 and is_input )
	{
		_window_tick_once( this );
	}

	exit_events:
	#if OS_WINDOWS
		out DefWindowProc( h, event, wp, lp );
	#elif OS_LINUX
		out success;
	#endif
}

////////
// new window

new_object_fn( window, byte const ref const name, n2 const width, n2 const height )
{
	temp window const out_window = new_object( window );

	temp n2 const name_size = bytes_measure( name );
	out_window->name = new_text_bytes( name, name_size );

	out_window->size.w = width;
	out_window->size.h = height;

	out_window->views = new_list( view );

	out_window->bordered = yes;

	out_window->inputs_pressed = new_list( byte );
	out_window->inputs_released = new_list( byte );

	#if OS_LINUX
		temp i4 screen = DefaultScreen( windows_display );

		out_window->handle = XCreateSimpleWindow( windows_display, RootWindow( windows_display, screen ), 0, 0, width, height, 0, 0, 0 );

		XSetWindowBackgroundPixmap( windows_display, out_window->handle, None );
		XSelectInput( windows_display, out_window->handle, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask | PointerMotionMask );
		XStoreName( windows_display, out_window->handle, out_window->name->bytes );

		out_window->image = XCreateImage( windows_display, DefaultVisual( windows_display, screen ), DefaultDepth( windows_display, screen ), ZPixmap, 0, nothing, width, height, 32, 0 );
	#elif OS_WINDOWS
		WNDCLASS wclass = { 0 };
		wclass.lpfnWndProc = to( type_of( wclass.lpfnWndProc ), window_process_event );
		wclass.hInstance = GetModuleHandle( nothing );
		wclass.lpszClassName = out_window->name->bytes;
		RegisterClass( ref_of( wclass ) );

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );

		out_window->handle = CreateWindow( out_window->name->bytes, out_window->name->bytes, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nothing, nothing, GetModuleHandle( nothing ), nothing );

		out_window->window_dc = GetDC( out_window->handle );

		out_window->image.bmiHeader.biSize = size_of( out_window->image.bmiHeader );
		out_window->image.bmiHeader.biPlanes = 1;
		out_window->image.bmiHeader.biBitCount = 32;
		out_window->image.bmiHeader.biCompression = BI_RGB;

		SetWindowLongPtr( out_window->handle, GWLP_USERDATA, to( LONG_PTR, out_window ) );
		SendMessage( out_window->handle, WM_SETICON, ICON_SMALL, ( LPARAM ) windows_icon );
		SendMessage( out_window->handle, WM_SETICON, ICON_BIG, ( LPARAM ) windows_icon );
	#endif

	current_window = out_window;
	list_add( windows, current_window );
	out current_window;
}

delete_object_fn( window )
{
	delete_text( this->name );
	list_iter( this->views, canvas_id )
	{
		delete_view( list_get_iter( canvas_id, view ) );
	}
	delete_list( this->views );
	delete_list( this->inputs_pressed );
	delete_list( this->inputs_released );

	delete_object( this );
}

////////
// window process

fn _window_process_events( window const this )
{
	os_event event;
	#if OS_LINUX
		while( XPending( windows_display ) )
		{
			XNextEvent( windows_display, ref_of( event ) );
			window_process_event( this, event.type, ref_of( event ) );
		}
	#elif OS_WINDOWS
		while( PeekMessage( ref_of( event ), 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( ref_of( event ) );
			DispatchMessage( ref_of( event ) );
		}
	#endif
}

fn _window_process( window const this )
{
	current_window = this;

	++this->tick;

	if( this->tick is 1 )
	{
		_window_resize( this );
		window_center( this );
		call( this, fn_start );
	}
	else if( this->tick is 2 )
	{
		window_show( this );
	}

	_window_process_events( this );
}

////////////////////////////////
/// Heptane system functions

fn _C7H16_init()
{
	windows = new_list( window );

	#if OS_LINUX
		windows_display = XOpenDisplay( nothing );
		XkbSetDetectableAutoRepeat( windows_display, yes, nothing );
	#elif OS_WINDOWS
		windows_icon = LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE( 1 ) );
		#if DEBUG
			AllocConsole();
			freopen( "CONOUT$", "w", stdout );
		#endif
	#endif
}

fn _C7H16_loop()
{
	windows_time_start = get_nano();
	windows_time_next_draw = windows_time_start;

	temp nano prev_frame_nano_tick = 0;

	loop
	{
		out_if( windows->count is 0 );

		temp const nano frame_nano_tick = pick( windows_fps_tick > 0, nano_per_sec / windows_fps_tick, 0 );
		temp const nano frame_nano_draw = pick( windows_fps_draw > 0, nano_per_sec / windows_fps_draw, 0 );
		temp const flag event_driven = frame_nano_tick is 0 and frame_nano_draw is 0;

		if( frame_nano_tick > 0 and prev_frame_nano_tick is 0 )
		{
			windows_time_start = get_nano();
			windows_time_tick = 0;
		}
		prev_frame_nano_tick = frame_nano_tick;

		// process
		list_iter( windows, window_id )
		{
			temp window const this_window = list_get_iter( window_id, window );
			_window_process( this_window );

			if( this_window->close )
			{
				out_if( window_id is 0 );

				list_delete( windows, window_id );
				--window_id;
				skip_if( window_id < 0 );
			}
		}

		// tick
		if( frame_nano_tick > 0 )
		{
			temp const nano elapsed = get_nano() - windows_time_start;
			temp const n8 target_frames = n8( elapsed / frame_nano_tick );

			// main tick (inputs reset after fn_tick)
			if( windows_time_tick <= target_frames )
			{
				++windows_time_tick;
				list_iter( windows, window_id )
				{
					_window_tick_once( list_get_iter( window_id, window ) );
				}
			}

			// catch up (no input processing)
			while( windows_time_tick <= target_frames )
			{
				++windows_time_tick;
				list_iter( windows, window_id )
				{
					//call( list_get_iter( window_id, window ), fn_tick );
				}
			}
		}

		// draw
		temp nano now = get_nano();
		if( frame_nano_draw > 0 and now >= windows_time_next_draw )
		{
			list_iter( windows, window_id )
			{
				temp window const this_window = list_get_iter( window_id, window );
				//_window_draw( this_window );
				window_update( this_window );
				_window_process_events( this_window );
			}

			windows_time_next_draw += frame_nano_draw;
			if( windows_time_next_draw < now )
			{
				windows_time_next_draw = now + frame_nano_draw;
			}
		}

		// wait
		if( event_driven )
		{
			temp flag all_ready = yes;
			list_iter( windows, window_id )
			{
				if( list_get_iter( window_id, window )->tick < 3 )
				{
					all_ready = no;
					skip;
				}
			}

			if( all_ready )
			{
				#if OS_LINUX
					fd_set fds;
					FD_ZERO( ref_of( fds ) );
					temp i4 const fd = ConnectionNumber( windows_display );
					FD_SET( fd, ref_of( fds ) );
					select( fd + 1, ref_of( fds ), nothing, nothing, nothing );
				#elif OS_WINDOWS
					MsgWaitForMultipleObjects( 0, nothing, FALSE, INFINITE, QS_ALLINPUT );
				#endif
			}
		}
		else
		{
			temp const nano next_tick = pick( frame_nano_tick > 0, windows_time_start + frame_nano_tick * windows_time_tick, 0 );
			temp const nano next_draw = pick( frame_nano_draw > 0, windows_time_next_draw, 0 );
			temp nano wake_time = 0;

			if( next_tick > 0 and next_draw > 0 )
			{
				wake_time = MIN( next_tick, next_draw );
			}
			else if( next_tick > 0 )
			{
				wake_time = next_tick;
			}
			else if( next_draw > 0 )
			{
				wake_time = next_draw;
			}

			now = get_nano();
			if( wake_time > now )
			{
				nano_sleep( wake_time - now );
			}
		}
	}
}

fn _C7H16_close()
{
	list_iter( windows, window_index )
	{
		delete_window( list_get_iter( window_index, window ) );
	}
	delete_list( windows );
}

#undef start
#define start\
	fn _C7H16_main( i4 const start_parameters_count, byte const ref const ref const start_parameters );\
	_main_fn\
	{\
		_C7H16_init();\
		_C7H16_main( start_parameters_count, start_parameters );\
		_C7H16_loop();\
		_C7H16_close();\
		out success;\
	}\
	fn _C7H16_main( i4 const start_parameters_count, byte const ref const ref const start_parameters )

////////////////////////////////////////////////////////////////
