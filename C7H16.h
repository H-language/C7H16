////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  heptane (C7H16)
//
//  author(s):
//  ENDESGA - https://x.com/ENDESGA | https://bsky.app/profile/endesga.bsky.social
//
//  https://github.com/H-language/C7H16
//  2025 - CC0 - FOSS forever
//

#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// dependencies
/// dependencies
//

#define _GNU_SOURCE

#if __linux__
	#include <errno.h>
	#include <poll.h>
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/extensions/Xrender.h>
	#include <X11/extensions/Xpresent.h>
	#include <X11/XKBlib.h>
	#include <X11/cursorfont.h>
#else
	__declspec( dllimport ) int __stdcall timeBeginPeriod( int );
#endif

#include <H.h>

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// version
/// version
//

#define C7H16_VERSION_MAJOR 0
#define C7H16_VERSION_MINOR 1
#define C7H16_VERSION_PATCH 0
#define C7H16_VERSION AS_BYTES( C7H16_VERSION_MAJOR ) "." AS_BYTES( C7H16_VERSION_MINOR ) "." AS_BYTES( C7H16_VERSION_PATCH )

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// dimensional
/// dimensional
//

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
		variant\
		{\
			TYPE##x2 axy;\
			TYPE##x2 bxy;\
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
#define to_n1x2( X2 ) n1x2( X2.x, X2.y )
#define to_n1x3( X3 ) n1x3( X3.x, X3.y, X3.z )
#define to_n1x4( X4 ) n1x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI( i1 );
#define i1x2( X_Y... ) _x2( i1, X_Y )
#define i1x3( X_Y_Z... ) _x3( i1, X_Y_Z )
#define i1x4( X_Y_Z_W... ) _x4( i1, X_Y_Z_W )
#define to_i1x2( X2 ) i1x2( X2.x, X2.y )
#define to_i1x3( X3 ) i1x3( X3.x, X3.y, X3.z )
#define to_i1x4( X4 ) i1x4( X4.x, X4.y, X4.z, X4.w )

DECLARE_TYPE_MULTI( n2 );
#define n2x2( X_Y... ) _x2( n2, X_Y )
#define n2x3( X_Y_Z... ) _x3( n2, X_Y_Z )
#define n2x4( X_Y_Z_W... ) _x4( n2, X_Y_Z_W )
#define to_n2x2( X2 ) n2x2( X2.x, X2.y )
#define to_n2x3( X3 ) n2x3( X3.x, X3.y, X3.z )
#define to_n2x4( X4 ) n2x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI( i2 );
#define i2x2( X_Y... ) _x2( i2, X_Y )
#define i2x3( X_Y_Z... ) _x3( i2, X_Y_Z )
#define i2x4( X_Y_Z_W... ) _x4( i2, X_Y_Z_W )
#define to_i2x2( X2 ) i2x2( X2.x, X2.y )
#define to_i2x3( X3 ) i2x3( X3.x, X3.y, X3.z )
#define to_i2x4( X4 ) i2x4( X4.x, X4.y, X4.z, X4.w )

DECLARE_TYPE_MULTI( n4 );
#define n4x2( X_Y... ) _x2( n4, X_Y )
#define n4x3( X_Y_Z... ) _x3( n4, X_Y_Z )
#define n4x4( X_Y_Z_W... ) _x4( n4, X_Y_Z_W )
#define to_n4x2( X2 ) n4x2( X2.x, X2.y )
#define to_n4x3( X3 ) n4x3( X3.x, X3.y, X3.z )
#define to_n4x4( X4 ) n4x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI( i4 );
#define i4x2( X_Y... ) _x2( i4, X_Y )
#define i4x3( X_Y_Z... ) _x3( i4, X_Y_Z )
#define i4x4( X_Y_Z_W... ) _x4( i4, X_Y_Z_W )
#define to_i4x2( X2 ) i4x2( X2.x, X2.y )
#define to_i4x3( X3 ) i4x3( X3.x, X3.y, X3.z )
#define to_i4x4( X4 ) i4x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI( r4 );
#define r4x2( X_Y... ) _x2( r4, X_Y )
#define r4x3( X_Y_Z... ) _x3( r4, X_Y_Z )
#define r4x4( X_Y_Z_W... ) _x4( r4, X_Y_Z_W )
#define to_r4x2( X2 ) r4x2( X2.x, X2.y )
#define to_r4x3( X3 ) r4x3( X3.x, X3.y, X3.z )
#define to_r4x4( X4 ) r4x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI_R( 4 );

DECLARE_TYPE_MULTI( n8 );
#define n8x2( X_Y... ) _x2( n8, X_Y )
#define n8x3( X_Y_Z... ) _x3( n8, X_Y_Z )
#define n8x4( X_Y_Z_W... ) _x4( n8, X_Y_Z_W )
#define to_n8x2( X2 ) n8x2( X2.x, X2.y )
#define to_n8x3( X3 ) n8x3( X3.x, X3.y, X3.z )
#define to_n8x4( X4 ) n8x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI( i8 );
#define i8x2( X_Y... ) _x2( i8, X_Y )
#define i8x3( X_Y_Z... ) _x3( i8, X_Y_Z )
#define i8x4( X_Y_Z_W... ) _x4( i8, X_Y_Z_W )
#define to_i8x2( X2 ) i8x2( X2.x, X2.y )
#define to_i8x3( X3 ) i8x3( X3.x, X3.y, X3.z )
#define to_i8x4( X4 ) i8x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI( r8 );
#define r8x2( X_Y... ) _x2( r8, X_Y )
#define r8x3( X_Y_Z... ) _x3( r8, X_Y_Z )
#define r8x4( X_Y_Z_W... ) _x4( r8, X_Y_Z_W )
#define to_r8x2( X2 ) r8x2( X2.x, X2.y )
#define to_r8x3( X3 ) r8x3( X3.x, X3.y, X3.z )
#define to_r8x4( X4 ) r8x4( X4.x, X4.y, X4.z, X4.w )
DECLARE_TYPE_MULTI_R( 8 );

#define grid_area( X, Y ) ( ( X ) * ( Y ) )
#define grid_index( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

////////////////////////////////
// dimensional flags

#define point_in_size( X, Y, W, H ) all( X >= 0, Y >= 0, X < W, Y < H )
#define point_not_in_size( X, Y, W, H ) any( X < 0, Y < 0, X >= W, Y >= H )

#define point_in_box( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) all( X >= TOPLEFT_X, Y >= TOPLEFT_Y, X <= BOTTOMRIGHT_X, Y <= BOTTOMRIGHT_Y )
#define point_not_in_box( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) any( X < TOPLEFT_X, Y < TOPLEFT_Y, X > BOTTOMRIGHT_X, Y > BOTTOMRIGHT_Y )

#define box_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) all( point_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )
#define box_not_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) any( point_not_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_not_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )

#define box_in_box( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) all( point_in_box( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_in_box( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )
#define box_not_in_box( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) any( point_not_in_box( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_not_in_box( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// nano
/// nano
//

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
	#else
		struct timespec ts = { time / nano_per_sec, time mod nano_per_sec };
		nanosleep( ref_of( ts ), nothing );
	#endif
}

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// pixel
/// pixel
//

// BGRA for X11/Windows (little-endian)
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

#define pixel_bits 8
#define pixel_shift 2

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

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// canvas
/// canvas
//

type( canvas )
{
	n2x2 size;
	n4 area;
	pixel ref pixels;
};

#define canvas( WIDTH, HEIGHT, PIXELS... ) ( { temp n4 const _AREA = n4( WIDTH ) * n4( HEIGHT ); make( canvas, .size = n2x2( WIDTH, HEIGHT ), .area = _AREA, .pixels = to( pixel ref, DEFAULT( new_ref( pixel, _AREA ), PIXELS ) ) ); } )

fn delete_canvas( canvas ref const canvas_ref )
{
	delete_ref( canvas_ref->pixels );
	val_of( canvas_ref ) = make( canvas );
}

fn canvas_resize( canvas ref const canvas_ref, n2 const width, n2 const height )
{
	out_if( canvas_ref->size.w is width and canvas_ref->size.h is height );

	temp const n2x2 size_old = canvas_ref->size;
	temp n4 const area_old = canvas_ref->area;
	canvas_ref->size = n2x2( width, height );
	canvas_ref->area = n4( canvas_ref->size.w ) * n4( canvas_ref->size.h );
	canvas_ref->pixels = ref_resize( canvas_ref->pixels, canvas_ref->area << pixel_shift );
}

fn canvas_fill( canvas ref const canvas_ref, pixel const color )
{
	if_all( color.r is color.g, color.g is color.b, color.b is color.a )
	{
		bytes_fill( canvas_ref->pixels, color.r, canvas_ref->area << pixel_shift );
	}
	else
	{
		temp i4 filled = i4( canvas_ref->size.w );
		iter( first_row_index, filled )
		{
			canvas_ref->pixels[ first_row_index ] = color;
		}

		temp i4 remaining = canvas_ref->area - filled;
		do
		{
			temp i4 const count = pick( remaining < filled, remaining, filled );
			bytes_copy( ref_of( canvas_ref->pixels[ filled ] ), ref_of( canvas_ref->pixels[ 0 ] ), count << pixel_shift );
			filled += count;
			remaining -= count;
		}
		while( remaining );
	}
}

#define canvas_clear( CANVAS ) bytes_clear( CANVAS->pixels, CANVAS->area << pixel_shift )

////////////////////////////////
// check

#define canvas_check_pixel( CANVAS, X, Y ) ( point_in_size( X, Y, CANVAS->size.w, CANVAS->size.h ) )
#define canvas_check_pixel_index( CANVAS, INDEX ) ( INDEX >= 0 and INDEX < CANVAS->area )

////////////////////////////////
// get

#define canvas_get_pixel_index( CANVAS, INDEX ) CANVAS->pixels[ ( INDEX ) ]
#define canvas_get_pixel_index_safe( CANVAS, INDEX ) pick( canvas_check_pixel_index( INDEX ), canvas_get_pixel_index( CANVAS, INDEX ), pixel_invalid )
#define canvas_get_pixel( CANVAS, X, Y ) canvas_get_pixel_index( CANVAS, grid_index( X, Y, CANVAS->size.w ) )
#define canvas_get_pixel_safe( CANVAS, X, Y ) pick( canvas_check_pixel( CANVAS, X, Y ), canvas_get_pixel( CANVAS, X, Y ), pixel_invalid )

////////////////////////////////
// set

#define canvas_set_pixel_index( CANVAS, INDEX, PIXEL ) ( canvas_get_pixel_index( CANVAS, INDEX ) ) = ( PIXEL )
#define canvas_set_pixel_index_safe( CANVAS, INDEX, PIXEL ) if( canvas_check_pixel_index( CANVAS, INDEX ) ) canvas_set_pixel_index( CANVAS, INDEX, PIXEL )
#define canvas_set_pixel( CANVAS, X, Y, PIXEL ) ( canvas_get_pixel( CANVAS, X, Y ) ) = ( PIXEL )
#define canvas_set_pixel_safe( CANVAS, X, Y, PIXEL ) if( canvas_check_pixel( CANVAS, X, Y ) ) canvas_set_pixel( CANVAS, X, Y, PIXEL )

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// inputs
/// inputs
//

group( input_type )
{
	input_none,

	input_mouse_left,
	input_mouse_middle,
	input_mouse_right,
	input_scroll_up,
	input_scroll_down,
	input_scroll_left,
	input_scroll_right,

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

#define _INPUT_SET( NAME, LINUX_KEY, WINDOWS_KEY )[ OS_PICK( LINUX_KEY, WINDOWS_KEY ) ] = input_##NAME
#define _INPUT_SET_MASKED( NAME, LINUX_KEY, WINDOWS_KEY )[ OS_PICK( LINUX_KEY & 0x1ff, WINDOWS_KEY ) ] = input_##NAME

#define input_to_byte( INPUT ) ( ( INPUT ) - input_a + 'A' )

perm byte const _INPUT_MAP[] =
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

#define key_pressed( WINDOW_REF, KEY ) ( ( ( WINDOW_REF )->inputs[ input_##KEY ] & INPUT_MASK_PRESSED ) isnt 0 )
#define key_held( WINDOW_REF, KEY ) ( ( ( WINDOW_REF )->inputs[ input_##KEY ] & INPUT_MASK_HELD ) isnt 0 )
#define key_released( WINDOW_REF, KEY ) ( ( ( WINDOW_REF )->inputs[ input_##KEY ] & INPUT_MASK_RELEASED ) isnt 0 )

#define mouse_pressed( WINDOW_REF, BUTTON ) key_pressed( WINDOW_REF, mouse_##BUTTON )
#define mouse_held( WINDOW_REF, BUTTON ) key_held( WINDOW_REF, mouse_##BUTTON )
#define mouse_released( WINDOW_REF, BUTTON ) key_released( WINDOW_REF, mouse_##BUTTON )

#define mouse_scroll( WINDOW_REF, DIRECTION ) key_pressed( WINDOW_REF, scroll_##DIRECTION )

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// view
/// view
//

type( view );
type_fn( anon, view ref const ) view_ref_fn;

group( view_state )
{
	view_state_unknown,
	view_state_visible,
	view_state_hidden
};

type( view )
{
	view_state state;

	canvas canvas;

	#if OS_LINUX
		Pixmap pixmap;
		Picture picture;
	#elif OS_WINDOWS
		//
	#endif

	n2x4 clip_region;

	r4x2 pos;
	r4x2 scale;

	view_ref_fn fn_draw;
	anon ref draw_ref;

	flag update : 1;
	flag clip : 1;
	flag clear : 1;
}
packed;

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// window
/// window
//

type_from( OS_PICK( Window, HWND ) ) window_handle;
type_from( OS_PICK( XImage ref, BITMAPINFO ) ) window_image;
type_from( OS_PICK( XEvent, MSG ) ) window_event;

#ifndef window_max_name_size
	#define window_max_name_size 16
#endif

#ifndef window_max_views
	#define window_max_views 1
#endif

#ifndef window_max_inputs
	#define window_max_inputs 16
#endif

type( window );
type_fn( anon, window ref const ) window_ref_fn;

group( window_state )
{
	window_state_unknown,
	window_state_preparing,
	window_state_opening,
	window_state_ready,
	window_state_closing
};

type( window )
{
	window_state state;

	byte name[ window_max_name_size ];
	n2x2 size;

	window_handle handle;
	window_image image;

	#if OS_LINUX
		Atom event_delete;
		Picture picture;
	#elif OS_WINDOWS
		HDC window_dc;
	#endif

	window_ref_fn fn_start;
	window_ref_fn fn_resize;
	window_ref_fn fn_tick;

	view views[ window_max_views ];
	n1 views_count;

	n1 inputs[ inputs_count ];
	n1 inputs_pressed[ window_max_inputs ];
	n1 inputs_pressed_count;
	n1 inputs_released[ window_max_inputs ];
	n1 inputs_released_count;
	i4x2 mouse;

	flag visible : 1;
}
packed;

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// program
/// program
//

#ifndef program_max_windows
	#define program_max_windows 1
#endif

global
{
	#if OS_LINUX
		Display ref display;
		Visual ref visual;
		XRenderPictFormat ref format;
	#elif OS_WINDOWS
		HINSTANCE instance;
		HICON icon;
	#endif

	window windows[ program_max_windows ];
	n1 windows_count;
}
packed program;

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// view functions
/// view functions
//

////////////////////////////////
// hidden

fn _view_setup( view ref const view_ref )
{
	view_ref->update = yes;

	#if OS_LINUX
		temp i4 const screen = DefaultScreen( program.display );
		temp i4 const depth = DefaultDepth( program.display, screen );
		view_ref->pixmap = XCreatePixmap( program.display, RootWindow( program.display, screen ), view_ref->canvas.size.w, view_ref->canvas.size.h, depth );
		view_ref->picture = XRenderCreatePicture( program.display, view_ref->pixmap, program.format, 0, nothing );
	#elif OS_WINDOWS
		//
	#endif
}

////////////////////////////////
// visible

#define view_get_scaled_size( VIEW_REF ) r4x2( r4( VIEW_REF->canvas.size.w ) * VIEW_REF->scale.w, r4( VIEW_REF->canvas.size.h ) * VIEW_REF->scale.h )

fn view_zoom( view ref const view_ref, i4 const x, i4 const y, r4 const factor )
{
	temp r4 const new_scale = r4_clamp( view_ref->scale.w * factor, 0.1, 1000.0 );
	temp r4 const actual_factor = new_scale / view_ref->scale.w;
	view_ref->pos.x = r4( x ) - r4( x - view_ref->pos.x ) * actual_factor;
	view_ref->pos.y = r4( y ) - r4( y - view_ref->pos.y ) * actual_factor;
	view_ref->scale = r4x2( new_scale, new_scale );
}

fn view_resize( view ref const view_ref, n2x2 const window_size, n2x2 const size )
{
	out_if_any( view_ref is nothing, size.w is 0, size.h is 0 );

	if( view_ref->canvas.pixels is nothing )
	{
		view_ref->canvas = canvas( size.w, size.h );
	}
	else if( view_ref->canvas.size.w isnt size.w or view_ref->canvas.size.h isnt size.h )
	{
		canvas_resize( ref_of( view_ref->canvas ), size.w, size.h );
	}

	#if OS_LINUX
		if( view_ref->pixmap )
		{
			XRenderFreePicture( program.display, view_ref->picture );
			XFreePixmap( program.display, view_ref->pixmap );
		}
	#endif

	_view_setup( view_ref );
}

fn view_center( view ref const view_ref, i2x2 const center_position )
{
	out_if_nothing( view_ref->canvas.pixels );
	view_ref->pos.x = r4( center_position.x ) - ( r4( view_ref->canvas.size.w ) * view_ref->scale.w * 0.5 );
	view_ref->pos.y = r4( center_position.y ) - ( r4( view_ref->canvas.size.h ) * view_ref->scale.h * 0.5 );
}

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// window functions
/// window functions
//

////////////////////////////////
// hidden

fn _window_get_mouse_position( window ref const window_ref, i4 ref const out_x, i4 ref const out_y )
{
	#if OS_LINUX
		Window root;
		Window child;
		i4 root_x;
		i4 root_y;
		n4 mask;
		XQueryPointer( program.display, window_ref->handle, ref_of( root ), ref_of( child ), ref_of( root_x ), ref_of( root_y ), out_x, out_y, ref_of( mask ) );
	#elif OS_WINDOWS
		POINT cursor;
		GetCursorPos( ref_of( cursor ) );
		ScreenToClient( window_ref->handle, ref_of( cursor ) );
		val_of( out_x ) = cursor.x;
		val_of( out_y ) = cursor.y;
	#endif
}

fn _window_tick( window ref const window_ref )
{
	_window_get_mouse_position( window_ref, ref_of( window_ref->mouse.x ), ref_of( window_ref->mouse.y ) );

	// custom tick

	call( window_ref->fn_tick, window_ref );

	// input reset

	if( window_ref->inputs_pressed_count > 0 )
	{
		iter( input_index, window_ref->inputs_pressed_count )
		{
			window_ref->inputs[ window_ref->inputs_pressed[ input_index ] ] &= ~ INPUT_MASK_PRESSED;
		}
		window_ref->inputs_pressed_count = 0;
	}

	if( window_ref->inputs_released_count > 0 )
	{
		iter( input_index, window_ref->inputs_released_count )
		{
			window_ref->inputs[ window_ref->inputs_released[ input_index ] ] = 0;
		}
		window_ref->inputs_released_count = 0;
	}
}

fn _window_draw( window ref const window_ref )
{
	temp n1 count = window_ref->views_count;
	out_if( count is 0 );

	#if OS_LINUX
		perm GC gc = nothing;
		perm XTransform transform = { 0 };
		once
		{
			gc = XCreateGC( program.display, window_ref->handle, 0, nothing );
			transform.matrix[ 2 ][ 2 ] = XDoubleToFixed( 1.0 );
		}
	#elif OS_WINDOWS
		perm HBRUSH black_brush = nothing;
		once
		{
			black_brush = to( HBRUSH, GetStockObject( BLACK_BRUSH ) );
		}
		temp HDC const wdc = window_ref->window_dc;
	#endif

	temp i4 const win_w = window_ref->size.w;
	temp i4 const win_h = window_ref->size.h;

	iter( view_index, window_max_views )
	{
		temp view ref const view_ref = ref_of( window_ref->views[ view_index ] );

		if( view_ref->state is view_state_unknown ) next;

		if( view_ref->update is yes )
		{
			call( view_ref->fn_draw, view_ref );
			view_ref->update = no;
		}

		temp r4x2 const scaled_size = view_get_scaled_size( view_ref );
		skip_if( scaled_size.w is 0 or scaled_size.h is 0 );

		temp i4 const canvas_w = view_ref->canvas.size.w;
		temp i4 const canvas_h = view_ref->canvas.size.h;

		temp flag const clipped = view_ref->clip;

		temp i4 clip_l = 0;
		temp i4 clip_t = 0;
		temp i4 clip_r = 0;
		temp i4 clip_b = 0;

		if( clipped is yes )
		{
			clip_l = i4( view_ref->clip_region.axy.x );
			clip_t = i4( view_ref->clip_region.axy.y );
			clip_r = i4( view_ref->clip_region.bxy.x );
			clip_b = i4( view_ref->clip_region.bxy.y );

			skip_if( clip_r <= clip_l or clip_b <= clip_t );
		}

		temp i4 const view_l = i4( r4_floor( view_ref->pos.x ) );
		temp i4 const view_t = i4( r4_floor( view_ref->pos.y ) );
		temp i4 const view_r = i4( r4_ceil( view_ref->pos.x + scaled_size.w ) );
		temp i4 const view_b = i4( r4_ceil( view_ref->pos.y + scaled_size.h ) );
		temp r4 const scale_w = view_ref->scale.w;
		temp r4 const scale_h = view_ref->scale.h;

		#if OS_LINUX
			window_ref->image->data = to( byte ref, view_ref->canvas.pixels );
			window_ref->image->width = canvas_w;
			window_ref->image->height = canvas_h;
			window_ref->image->bytes_per_line = canvas_w << pixel_shift;
		#elif OS_WINDOWS
			window_ref->image.bmiHeader.biWidth = canvas_w;
			window_ref->image.bmiHeader.biHeight = -canvas_h;

			if( clipped is yes )
			{
				temp HRGN clip = CreateRectRgn( clip_l, clip_t, clip_r, clip_b );
				SelectClipRgn( wdc, clip );
				DeleteObject( clip );
			}
		#endif

		if( view_ref->clear is yes )
		{
			temp i4 clear_l;
			temp i4 clear_t;
			temp i4 clear_r;
			temp i4 clear_b;

			if( clipped is yes )
			{
				clear_l = clip_l;
				clear_t = clip_t;
				clear_r = clip_r;
				clear_b = clip_b;
			}
			else
			{
				clear_l = 0;
				clear_t = 0;
				clear_r = win_w;
				clear_b = win_h;
			}

			temp i4 const inner_l = i4_min( i4_max( view_l, clear_l ), clear_r );
			temp i4 const inner_t = i4_min( i4_max( view_t, clear_t ), clear_b );
			temp i4 const inner_r = i4_max( i4_min( view_r, clear_r ), clear_l );
			temp i4 const inner_b = i4_max( i4_min( view_b, clear_b ), clear_t );

			if( inner_t > clear_t or inner_b < clear_b or inner_l > clear_l or inner_r < clear_r )
			{
				#if OS_LINUX
					XSetForeground( program.display, gc, 0 );
				#endif

				if( clear_t < inner_t )
				{
					#if OS_LINUX
						XFillRectangle( program.display, window_ref->handle, gc, clear_l, clear_t, clear_r - clear_l, inner_t - clear_t );
					#elif OS_WINDOWS
						RECT r = make( RECT, clear_l, clear_t, clear_r, inner_t );
						FillRect( wdc, ref_of( r ), black_brush );
					#endif
				}

				if( inner_b < clear_b )
				{
					#if OS_LINUX
						XFillRectangle( program.display, window_ref->handle, gc, clear_l, inner_b, clear_r - clear_l, clear_b - inner_b );
					#elif OS_WINDOWS
						RECT r = make( RECT, clear_l, inner_b, clear_r, clear_b );
						FillRect( wdc, ref_of( r ), black_brush );
					#endif
				}

				if( clear_l < inner_l )
				{
					#if OS_LINUX
						XFillRectangle( program.display, window_ref->handle, gc, clear_l, inner_t, inner_l - clear_l, inner_b - inner_t );
					#elif OS_WINDOWS
						RECT r = make( RECT, clear_l, inner_t, inner_l, inner_b );
						FillRect( wdc, ref_of( r ), black_brush );
					#endif
				}

				if( inner_r < clear_r )
				{
					#if OS_LINUX
						XFillRectangle( program.display, window_ref->handle, gc, inner_r, inner_t, clear_r - inner_r, inner_b - inner_t );
					#elif OS_WINDOWS
						RECT r = make( RECT, inner_r, inner_t, clear_r, inner_b );
						FillRect( wdc, ref_of( r ), black_brush );
					#endif
				}
			}
		}

		if( scale_w is 1.0 and scale_h is 1.0 )
		{
			#if OS_LINUX
				if( clipped is yes )
				{
					XRectangle clip_rect = { clip_l, clip_t, clip_r - clip_l, clip_b - clip_t };
					XSetClipRectangles( program.display, gc, 0, 0, ref_of( clip_rect ), 1, Unsorted );
				}
				XPutImage( program.display, window_ref->handle, gc, window_ref->image, 0, 0, view_l, view_t, canvas_w, canvas_h );
				if( clipped is yes )
				{
					XSetClipMask( program.display, gc, None );
				}
			#elif OS_WINDOWS
				SetDIBitsToDevice( wdc, view_l, view_t, canvas_w, canvas_h, 0, 0, 0, canvas_h, view_ref->canvas.pixels, ref_of( window_ref->image ), DIB_RGB_COLORS );
			#endif
		}
		else
		{
			temp i4 const view_w = view_r - view_l;
			temp i4 const view_h = view_b - view_t;

			#if OS_LINUX
				XPutImage( program.display, view_ref->pixmap, gc, window_ref->image, 0, 0, 0, 0, canvas_w, canvas_h );

				transform.matrix[ 0 ][ 0 ] = XDoubleToFixed( 1.0 / scale_w );
				transform.matrix[ 1 ][ 1 ] = XDoubleToFixed( 1.0 / scale_h );
				XRenderSetPictureTransform( program.display, view_ref->picture, ref_of( transform ) );
				XRenderSetPictureFilter( program.display, view_ref->picture, "nearest", nothing, 0 );

				if( clipped is yes )
				{
					XRectangle clip_rect = { clip_l, clip_t, clip_r - clip_l, clip_b - clip_t };
					XRenderSetPictureClipRectangles( program.display, window_ref->picture, 0, 0, ref_of( clip_rect ), 1 );
				}
				XRenderComposite( program.display, PictOpSrc, view_ref->picture, None, window_ref->picture, 0, 0, 0, 0, view_l, view_t, view_w, view_h );
				if( clipped is yes )
				{
					XRectangle full_rect = { 0, 0, win_w, win_h };
					XRenderSetPictureClipRectangles( program.display, window_ref->picture, 0, 0, ref_of( full_rect ), 1 );
				}
			#elif OS_WINDOWS
				SetStretchBltMode( wdc, COLORONCOLOR ); //pick( scale_w <= 0.25 or scale_h <= 0.25, HALFTONE, COLORONCOLOR ) );
				StretchDIBits( wdc, view_l, view_t, view_w, view_h, 0, 0, canvas_w, canvas_h, view_ref->canvas.pixels, ref_of( window_ref->image ), DIB_RGB_COLORS, SRCCOPY );
			#endif
		}

		#if OS_WINDOWS
			if( clipped is yes )
			{
				SelectClipRgn( wdc, nothing );
			}
		#endif

		count -= 1;
		skip_if( count <= 0 );
	}
}

#define _window_event_resize OS_PICK( ConfigureNotify, WM_SIZE )
#define _window_event_draw OS_PICK( Expose, WM_PAINT )
#define _window_event_close OS_PICK( ClientMessage, WM_DESTROY )
#define _window_event_key_activate EVAL OS_PICK( ( KeyPress ), ( WM_KEYDOWN, WM_SYSKEYDOWN ) )
#define _window_event_key_deactivate EVAL OS_PICK( ( KeyRelease ), ( WM_KEYUP, WM_SYSKEYUP ) )
#define _window_event_mouse_move OS_PICK( MotionNotify, WM_MOUSEMOVE )
#define _window_event_focus_lost OS_PICK( FocusOut, WM_KILLFOCUS )

#define _window_add_input_pressed( VALUE )\
	if( not( window_ref->inputs[ VALUE ] & INPUT_MASK_HELD ) )\
	{\
		window_ref->inputs[ VALUE ] |= INPUT_MASK_PRESSED | INPUT_MASK_HELD;\
		window_ref->inputs_pressed[ window_ref->inputs_pressed_count++ ] = n1( VALUE );\
		is_input = yes;\
	}

#define _window_add_input_released( VALUE )\
	window_ref->inputs[ VALUE ] |= INPUT_MASK_RELEASED;\
	window_ref->inputs_released[ window_ref->inputs_released_count++ ] = n1( VALUE );\
	is_input = yes

#if OS_LINUX
	embed out_state _window_process_event( window ref const window_ref, i4 const event, window_event const ref e )
#elif OS_WINDOWS
	embed LRESULT CALLBACK _window_process_event( window_handle const h, i4 const event, WPARAM const wp, LPARAM const lp )
#endif
{
	#if OS_WINDOWS
		temp window ref const window_ref = to( window ref const, GetWindowLongPtr( h, GWLP_USERDATA ) );
	#endif
	jump_if_nothing( window_ref ) exit_events;

	temp flag is_input = no;

	with( event )
	{
		#if OS_LINUX
			//
		#elif OS_WINDOWS
			when( WM_ENTERSIZEMOVE )
			{
				//SetTimer( h, 1, 0, nothing );
				skip;
			}

			when( WM_EXITSIZEMOVE )
			{
				//KillTimer( h, 1 );
				skip;
			}

			when( WM_TIMER )
			{
				skip_if( wp isnt 1 );

				//_current_window_tick();
				//is_input = yes;
				//jump WINDOW_DRAW;
			}

			when( WM_ERASEBKGND )
			{
				out 1;
			}

			when( WM_SETCURSOR )
			{
				if( LOWORD( lp ) is HTCLIENT )
				{
					SetCursor( LoadCursor( nothing, IDC_ARROW ) );
					out yes;
				}
				skip;
			}
		#endif

		when( _window_event_resize )
		{
			temp n2 w = OS_PICK( e->xconfigure.width, LOWORD( lp ) );
			temp n2 h = OS_PICK( e->xconfigure.height, HIWORD( lp ) );

			window_ref->size.w = w;
			window_ref->size.h = h;

			call( window_ref->fn_resize, window_ref );
		} // fall through

		when( _window_event_draw )
		{
			WINDOW_DRAW:
			_window_draw( window_ref );

			#if OS_WINDOWS
				ValidateRect( h, nothing );
				out 0;
			#endif

			skip;
		}

		// inputs

		when( _window_event_mouse_move )
		{
			#if OS_LINUX
				window_event next_move;
				while( XCheckTypedWindowEvent( program.display, window_ref->handle, MotionNotify, ref_of( next_move ) ) );
			#endif
			is_input = yes;
			skip;
		}

		when( _window_event_key_activate )
		{
			temp byte key = _INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( program.display, e->xkey.keycode, 0, 0 ) & 0x1ff, wp & 0xff ) ];
			_window_add_input_pressed( key );
			skip;
		}

		when( _window_event_key_deactivate )
		{
			temp byte key = _INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( program.display, e->xkey.keycode, 0, 0 ) & 0x1ff, wp & 0xff ) ];
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
						_window_add_input_pressed( input_scroll_up );
						_window_add_input_released( input_scroll_up );
						skip;
					}

					when( 5 )
					{
						_window_add_input_pressed( input_scroll_down );
						_window_add_input_released( input_scroll_down );
						skip;
					}

					when( 6 )
					{
						_window_add_input_pressed( input_scroll_right );
						_window_add_input_released( input_scroll_right );
						skip;
					}

					when( 7 )
					{
						_window_add_input_pressed( input_scroll_left );
						_window_add_input_released( input_scroll_left );
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
				if( GET_WHEEL_DELTA_WPARAM( wp ) > 0 )
				{
					_window_add_input_pressed( input_scroll_up );
					_window_add_input_released( input_scroll_up );
				}
				else
				{
					_window_add_input_pressed( input_scroll_down );
					_window_add_input_released( input_scroll_down );
				}
				skip;
			}

			when( WM_MOUSEHWHEEL )
			{
				if( GET_WHEEL_DELTA_WPARAM( wp ) > 0 )
				{
					_window_add_input_pressed( input_scroll_right );
					_window_add_input_released( input_scroll_right );
				}
				else
				{
					_window_add_input_pressed( input_scroll_left );
					_window_add_input_released( input_scroll_left );
				}
				skip;
			}
		#endif

		when( _window_event_close )
		{
			#if OS_WINDOWS
				PostQuitMessage( 0 );
			#endif

			window_ref->state = window_state_closing;

			out success;
		}

		other skip;
	}

	if( is_input )
	{
		_window_tick( window_ref );
	}

	exit_events:
	#if OS_WINDOWS
		out DefWindowProc( h, event, wp, lp );
	#elif OS_LINUX
		out success;
	#endif
}

////////////////////////////////
// visible

fn window_update( window ref const window_ref )
{
	#if OS_LINUX
		XClearArea( program.display, window_ref->handle, 0, 0, 0, 0, yes );
	#elif OS_WINDOWS
		InvalidateRect( window_ref->handle, nothing, no );
	#endif
}

fn window_show( window ref const window_ref )
{
	out_if( window_ref->visible is yes );

	#if OS_LINUX
		XMapRaised( program.display, window_ref->handle );
		XSync( program.display, no );
	#elif OS_WINDOWS
		SetFocus( window_ref->handle );
		SetForegroundWindow( window_ref->handle );
		ShowWindow( window_ref->handle, SW_SHOWNOACTIVATE );
	#endif

	window_ref->visible = yes;
}

embed view ref const window_create_view( window ref const window_ref, canvas canvas )
{
	temp n2 view_index = 0;

	while( window_ref->views[ view_index ].state isnt view_state_unknown )
	{
		view_index += 1;
	}

	temp view ref const view_ref = ref_of( window_ref->views[ view_index ] );

	view_ref->canvas = canvas;
	view_ref->scale = r4x2( 1.0, 1.0 );
	view_ref->state = view_state_visible;
	_view_setup( view_ref );

	window_ref->views_count += 1;

	out view_ref;
}

fn window_capture_mouse( window ref const window_ref )
{
	#if OS_LINUX
		XGrabPointer( program.display, window_ref->handle, no, ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime );
	#elif OS_WINDOWS
		SetCapture( window_ref->handle );
	#endif
}

fn window_release_mouse()
{
	#if OS_LINUX
		XUngrabPointer( program.display, CurrentTime );
	#elif OS_WINDOWS
		ReleaseCapture();
	#endif
}

////////////////////////////////
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

fn window_set_cursor( window ref const window_ref, cursor_type const cursor )
{
	//window_ref->changed_cursor = yes;
	#if OS_LINUX
		perm Cursor cache[ 256 ] = { 0 };
		if( not cache[ cursor ] )
		{
			cache[ cursor ] = XCreateFontCursor( program.display, cursor );
		}
		XDefineCursor( program.display, window_ref->handle, cache[ cursor ] );
	#else
		SetCursor( LoadCursor( NULL, MAKEINTRESOURCE( cursor ) ) );
	#endif
}

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// display functions
/// display functions
//

////////////////////////////////
// hidden

////////////////////////////////
// visible

embed n2 const display_get_width()
{
	#if OS_LINUX
		out n2( DisplayWidth( program.display, DefaultScreen( program.display ) ) );
	#elif OS_WINDOWS
		out n2( GetSystemMetrics( SM_CXSCREEN ) );
	#endif
}

embed n2 const display_get_height()
{
	#if OS_LINUX
		out n2( DisplayHeight( program.display, DefaultScreen( program.display ) ) );
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
		XQueryPointer( program.display, DefaultRootWindow( program.display ), ref_of( root ), ref_of( child ), out_x, out_y, ref_of( win_x ), ref_of( win_y ), ref_of( mask ) );
	#elif OS_WINDOWS
		POINT cursor;
		GetCursorPos( ref_of( cursor ) );
		val_of( out_x ) = cursor.x;
		val_of( out_y ) = cursor.y;
	#endif
}

//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// program functions
/// program functions
//

////////////////////////////////
// hidden

fn _program_setup()
{
	#if OS_LINUX
		program.display = XOpenDisplay( nothing );

		temp i4 const screen = DefaultScreen( program.display );
		program.visual = DefaultVisual( program.display, screen );
		program.format = XRenderFindVisualFormat( program.display, program.visual );
	#elif OS_WINDOWS
		#if DEBUG
			AllocConsole();
			freopen( "CONOUT$", "w", stdout );
		#endif
	#endif
}

fn _program_loop()
{
	loop
	{
		temp n1 count = program.windows_count;
		temp flag ready = yes;

		iter( i, program_max_windows )
		{
			window ref const w = ref_of( program.windows[ i ] );

			if( w->state is window_state_unknown ) next;

			with( w->state )
			{
				when( window_state_preparing )
				{
					w->state = window_state_opening;
					ready = no;
					skip;
				}

				when( window_state_opening )
				{
					window_show( w );
					w->state = window_state_ready;
					skip;
				}

				when( window_state_closing )
				{
					program.windows_count -= 1;
					w->state = window_state_unknown;
					skip;
				}

				other skip;
			}

			count -= 1;
			skip_if( count <= 0 );
		}

		out_if( program.windows_count is 0 );

		// events

		#if OS_LINUX
			XFlush( program.display );

			if( ready and not XPending( program.display ) )
			{
				struct pollfd pfd = { 0 };
				pfd.fd = ConnectionNumber( program.display );
				pfd.events = POLLIN;

				while( poll( ref_of( pfd ), 1, -1 ) < 0 and errno is EINTR );
			}

			window_event event;
			while( XPending( program.display ) )
			{
				XNextEvent( program.display, ref_of( event ) );

				iter( i, program.windows_count )
				{
					if( program.windows[ i ].handle is event.xany.window )
					{
						_window_process_event( ref_of( program.windows[ i ] ), event.type, ref_of( event ) );
						skip;
					}
				}
			}
		#elif OS_WINDOWS
			if( ready )
			{
				MsgWaitForMultipleObjects( 0, nothing, FALSE, INFINITE, QS_ALLINPUT );
			}

			window_event event;
			while( PeekMessage( ref_of( event ), 0, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( ref_of( event ) );
				DispatchMessage( ref_of( event ) );
			}
		#endif
	}
	print( "EXIT" newline );
}

fn _program_close()
{

}

////////////////////////////////
// visible

embed window ref const program_create_window( byte const ref const name, n2x2 const size )
{
	temp n2 window_index = 0;

	while( program.windows[ window_index ].state isnt window_state_unknown )
	{
		window_index += 1;
	}

	window ref const window_ref = ref_of( program.windows[ window_index ] );
	program.windows_count += 1;

	bytes_paste( window_ref->name, name );
	window_ref->size = size;
	window_ref->state = window_state_preparing;

	#if OS_LINUX
		temp i4 const screen = DefaultScreen( program.display );
		temp i4 const depth = DefaultDepth( program.display, screen );

		window_ref->handle = XCreateSimpleWindow( program.display, RootWindow( program.display, screen ), 0, 0, window_ref->size.w, window_ref->size.h, 0, 0, 0 );

		XSetWindowBackgroundPixmap( program.display, window_ref->handle, None );
		XSelectInput( program.display, window_ref->handle, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask | PointerMotionMask );
		XStoreName( program.display, window_ref->handle, window_ref->name );

		window_ref->event_delete = XInternAtom( program.display, "WM_DELETE_WINDOW", no );
		XSetWMProtocols( program.display, window_ref->handle, ref_of( window_ref->event_delete ), 1 );

		window_ref->image = XCreateImage( program.display, program.visual, depth, ZPixmap, 0, nothing, window_ref->size.w, window_ref->size.h, 32, 0 );

		window_ref->picture = XRenderCreatePicture( program.display, window_ref->handle, program.format, 0, nothing );
	#elif OS_WINDOWS
		WNDCLASS wclass = { 0 };
		wclass.lpfnWndProc = to( type_of( wclass.lpfnWndProc ), _window_process_event );
		wclass.hInstance = program.instance;
		wclass.lpszClassName = window_ref->name;
		RegisterClass( ref_of( wclass ) );

		RECT rect = { 0, 0, window_ref->size.w, window_ref->size.h };
		AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );

		window_ref->handle = CreateWindow( window_ref->name, window_ref->name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nothing, nothing, program.instance, nothing );

		window_ref->window_dc = GetDC( window_ref->handle );

		window_ref->image.bmiHeader.biSize = size_of( window_ref->image.bmiHeader );
		window_ref->image.bmiHeader.biPlanes = 1;
		window_ref->image.bmiHeader.biBitCount = 32;
		window_ref->image.bmiHeader.biCompression = BI_RGB;

		SendMessage( window_ref->handle, WM_SETICON, ICON_SMALL, to( LPARAM, program.icon ) );
		SendMessage( window_ref->handle, WM_SETICON, ICON_BIG, to( LPARAM, program.icon ) );

		SetWindowLongPtr( window_ref->handle, GWLP_USERDATA, to( LONG_PTR, window_ref ) );
	#endif

	out window_ref;
}

#undef start
#define start\
	fn _program_start( i4 const start_inputs_count, byte const ref const ref const start_inputs );\
	_main_fn\
	{\
		_program_setup();\
		_program_start( start_inputs_count, start_inputs );\
		_program_loop();\
		_program_close();\
		out success;\
	}\
	fn _program_start( i4 const start_inputs_count, byte const ref const ref const start_inputs )

//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
