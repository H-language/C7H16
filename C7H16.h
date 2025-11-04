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

#define C7H16
#include <H.h>
#include <math.h>

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
	embed TYPE##x2 TYPE##x2_invert( const TYPE##x2 X )\
	{\
		out make( TYPE##x2, .x = -X.x, .y = -X.y );\
	}\
	embed TYPE##x2 TYPE##x2_add( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x + B.x, .y = A.y + B.y );\
	}\
	embed TYPE##x2 TYPE##x2_add_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x + V, .y = A.y + V );\
	}\
	embed TYPE##x2 TYPE##x2_sub( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x - B.x, .y = A.y - B.y );\
	}\
	embed TYPE##x2 TYPE##x2_sub_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x - V, .y = A.y - V );\
	}\
	embed TYPE##x2 TYPE##x2_mul( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x * B.x, .y = A.y * B.y );\
	}\
	embed TYPE##x2 TYPE##x2_mul_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x * V, .y = A.y * V );\
	}\
	embed TYPE##x2 TYPE##x2_div( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out make( TYPE##x2, .x = A.x / B.x, .y = A.y / B.y );\
	}\
	embed TYPE##x2 TYPE##x2_div_##TYPE( const TYPE##x2 A, const TYPE V )\
	{\
		out make( TYPE##x2, .x = A.x / V, .y = A.y / V );\
	}\
	embed TYPE TYPE##x2_dot( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out A.x * B.x + A.y * B.y;\
	}\
	embed TYPE TYPE##x2_mag_sqr( const TYPE##x2 A )\
	{\
		out TYPE##x2_dot( A, A );\
	}\
	embed TYPE TYPE##x2_distance_sqr( const TYPE##x2 A, const TYPE##x2 B )\
	{\
		out TYPE##x2_mag_sqr( TYPE##x2_sub( B, A ) );\
	}

#define DECLARE_TYPE_3D_FN( TYPE )\
	embed TYPE##x3 TYPE##x3_invert( const TYPE##x3 X )\
	{\
		out make( TYPE##x3, .x = -X.x, .y = -X.y, .z = -X.z );\
	}\
	embed TYPE##x3 TYPE##x3_add( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x + B.x, .y = A.y + B.y, .z = A.z + B.z );\
	}\
	embed TYPE##x3 TYPE##x3_add_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x + V, .y = A.y + V, .z = A.z + V );\
	}\
	embed TYPE##x3 TYPE##x3_sub( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x - B.x, .y = A.y - B.y, .z = A.z - B.z );\
	}\
	embed TYPE##x3 TYPE##x3_sub_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x - V, .y = A.y - V, .z = A.z - V );\
	}\
	embed TYPE##x3 TYPE##x3_mul( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x * B.x, .y = A.y * B.y, .z = A.z * B.z );\
	}\
	embed TYPE##x3 TYPE##x3_mul_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x * V, .y = A.y * V, .z = A.z * V );\
	}\
	embed TYPE##x3 TYPE##x3_div( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.x / B.x, .y = A.y / B.y, .z = A.z / B.z );\
	}\
	embed TYPE##x3 TYPE##x3_div_##TYPE( const TYPE##x3 A, const TYPE V )\
	{\
		out make( TYPE##x3, .x = A.x / V, .y = A.y / V, .z = A.z / V );\
	}\
	embed TYPE TYPE##x3_dot( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out A.x * B.x + A.y * B.y + A.z * B.z;\
	}\
	embed TYPE TYPE##x3_mag_sqr( const TYPE##x3 A )\
	{\
		out TYPE##x3_dot( A, A );\
	}\
	embed TYPE TYPE##x3_distance_sqr( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out TYPE##x3_mag_sqr( TYPE##x3_sub( B, A ) );\
	}\
	embed TYPE##x3 TYPE##x3_cross( const TYPE##x3 A, const TYPE##x3 B )\
	{\
		out make( TYPE##x3, .x = A.y * B.z - A.z * B.y, .y = A.z * B.x - A.x * B.z, .z = A.x * B.y - A.y * B.x );\
	}

#define DECLARE_TYPE_4D_FN( TYPE )\
	embed TYPE##x4 TYPE##x4_invert( const TYPE##x4 X )\
	{\
		out make( TYPE##x4, .x = -X.x, .y = -X.y, .z = -X.z, .w = -X.w );\
	}\
	embed TYPE##x4 TYPE##x4_add( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x + B.x, .y = A.y + B.y, .z = A.z + B.z, .w = A.w + B.w );\
	}\
	embed TYPE##x4 TYPE##x4_add_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x + V, .y = A.y + V, .z = A.z + V, .w = A.w + V );\
	}\
	embed TYPE##x4 TYPE##x4_sub( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x - B.x, .y = A.y - B.y, .z = A.z - B.z, .w = A.w - B.w );\
	}\
	embed TYPE##x4 TYPE##x4_sub_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x - V, .y = A.y - V, .z = A.z - V, .w = A.w - V );\
	}\
	embed TYPE##x4 TYPE##x4_mul( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x * B.x, .y = A.y * B.y, .z = A.z * B.z, .w = A.w * B.w );\
	}\
	embed TYPE##x4 TYPE##x4_mul_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x * V, .y = A.y * V, .z = A.z * V, .w = A.w * V );\
	}\
	embed TYPE##x4 TYPE##x4_div( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out make( TYPE##x4, .x = A.x / B.x, .y = A.y / B.y, .z = A.z / B.z, .w = A.w / B.w );\
	}\
	embed TYPE##x4 TYPE##x4_div_##TYPE( const TYPE##x4 A, const TYPE V )\
	{\
		out make( TYPE##x4, .x = A.x / V, .y = A.y / V, .z = A.z / V, .w = A.w / V );\
	}\
	embed TYPE TYPE##x4_dot( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out A.x * B.x + A.y * B.y + A.z * B.z + A.w * B.w;\
	}\
	embed TYPE TYPE##x4_mag_sqr( const TYPE##x4 A )\
	{\
		out TYPE##x4_dot( A, A );\
	}\
	embed TYPE TYPE##x4_distance_sqr( const TYPE##x4 A, const TYPE##x4 B )\
	{\
		out TYPE##x4_mag_sqr( TYPE##x4_sub( B, A ) );\
	}

#define DECLARE_TYPE_XD_FN_R( N, X )\
	embed r##N r##N##x##X##_mag( const r##N##x##X A )\
	{\
		out r##N##_sqrt( r##N##x##X##_mag_sqr( A ) );\
	}\
	embed r##N r##N##x##X##_distance( const r##N##x##X A, const r##N##x##X B )\
	{\
		out r##N##_sqrt( r##N##x##X##_distance_sqr( A, B ) );\
	}\
	embed r##N##x##X r##N##x##X##_norm( const r##N##x##X A )\
	{\
		out r##N##x##X##_mul_##r##N( A, 1.0 / r##N##x##X##_mag( A ) );\
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

DECLARE_TYPE_MULTI( n1 );
DECLARE_TYPE_MULTI( i1 );
DECLARE_TYPE_MULTI( n2 );
DECLARE_TYPE_MULTI( i2 );
DECLARE_TYPE_MULTI( n4 );
DECLARE_TYPE_MULTI( i4 );
DECLARE_TYPE_MULTI( r4 );
DECLARE_TYPE_MULTI_R( 4 );
DECLARE_TYPE_MULTI( n8 );
DECLARE_TYPE_MULTI( i8 );
DECLARE_TYPE_MULTI( r8 );
DECLARE_TYPE_MULTI_R( 8 );

#define x2_area( x2 ) ( x2.w * x2.h )

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

#define d4_round_to_i4( D4 ) ( d4_to_i4( ( D4 ) + pick( ( D4 ) >= 0, ( 1 << ( d4_bits - 1 ) ), -( 1 << ( d4_bits - 1 ) ) ) ) )
#define d4_round( D4 ) ( i4_to_d4( d4_round_to_i4( D4 ) ) )

#define d4_ceil_to_i4( D4 ) ( d4_to_i4( ( D4 ) + pick( ( D4 ) > 0, ( ( 1 << d4_bits ) - 1 ), 0 ) ) )
#define d4_ceil( D4 ) ( i4_to_d4( d4_ceil_to_i4( D4 ) ) )

#define d4_floor_to_i4( D4 ) ( d4_to_i4( D4 ) - pick( ( ( D4 ) < 0 ) && ( ( D4 ) & ( ( 1 << d4_bits ) - 1 ) ), 1, 0 ) )
#define d4_floor( D4 ) ( i4_to_d4( d4_floor_to_i4( D4 ) ) )

#define d4_mul( A, B ) d4( ( i8( A ) * i8( B ) ) >> d4_bits )
#define d4_div( A, B ) d4( ( i8( A ) << d4_bits ) / i8( B ) )

type_from( i4x2 ) d4x2;

////////
// pixel

// BGRA for X11/Windows (little-endian)
#if IS_BIG_ENDIAN
	fusion( pixel )
	{
		n4 argb;
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
		n4 argb;
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
#define pixel( R, G, B, A ) ( ( pixel ) { .r = ( R ), .g = ( G ), .b = ( B ), .a = ( A ) } )

global pixel pixel_black = pixel( 0x00, 0x00, 0x00, 0xff );
global pixel pixel_dark_gray = pixel( 0x3f, 0x3f, 0x3f, 0xff );
global pixel pixel_gray = pixel( 0x7f, 0x7f, 0x7f, 0xff );
global pixel pixel_light_gray = pixel( 0xbf, 0xbf, 0xbf, 0xff );
global pixel pixel_white = pixel( 0xff, 0xff, 0xff, 0xff );
global pixel pixel_red = pixel( 0xff, 0x00, 0x00, 0xff );
global pixel pixel_yellow = pixel( 0xff, 0xff, 0x00, 0xff );
global pixel pixel_green = pixel( 0x00, 0xff, 0x00, 0xff );
global pixel pixel_cyan = pixel( 0x00, 0xff, 0xff, 0xff );
global pixel pixel_blue = pixel( 0x00, 0x00, 0xff, 0xff );
global pixel pixel_magenta = pixel( 0xff, 0x00, 0xff, 0xff );

////////////////////////////////
/// canvas

type( canvas )
{
	pixel ref pixels;
	n2x2 size;
};

global canvas ref current_canvas_ref = nothing;

#define index_2d( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

#define canvas( W, H ) make( canvas, .pixels = to( pixel ref, new_ref( pixel, ( W ) * ( H ) ) ), .size = make( n2x2, ( W ), ( H ) ) )

#define canvas_resize( CANVAS, WIDTH, HEIGHT )\
	START_DEF\
	{\
		temp const n2 _WIDTH = n2( WIDTH );\
		temp const n2 _HEIGHT = n2( HEIGHT );\
		skip_if( CANVAS.size.w is _WIDTH and CANVAS.size.h is _HEIGHT );\
		CANVAS.pixels = ref_resize( CANVAS.pixels, ( CANVAS.size.w * CANVAS.size.h ) << pixel_shift, ( _WIDTH * _HEIGHT ) << pixel_shift );\
		CANVAS.size.w = _WIDTH;\
		CANVAS.size.h = _HEIGHT;\
	}\
	END_DEF

#define canvas_fill( CANVAS, PIXEL )\
	START_DEF\
	{\
		temp const pixel _PIXEL = PIXEL;\
		temp const i4 _WIDTH = i4( CANVAS.size.w );\
		temp const i4 _AREA = _WIDTH * i4( CANVAS.size.h );\
		if_all( _PIXEL.r is _PIXEL.g, _PIXEL.g is _PIXEL.b, _PIXEL.b is _PIXEL.a )\
		{\
			bytes_fill( CANVAS.pixels, _PIXEL.r, _AREA << pixel_shift );\
		}\
		else\
		{\
			iter( _x, _WIDTH )\
			{\
				CANVAS.pixels[ _x ] = _PIXEL;\
			}\
			temp i4 _filled = _WIDTH;\
			while( _filled < _AREA )\
			{\
				temp const i4 _copy_count = pick( _AREA - _filled < _filled, _AREA - _filled, _filled );\
				bytes_copy( ref_of( CANVAS.pixels[ _filled ] ), ref_of( CANVAS.pixels[ 0 ] ), _copy_count << pixel_shift );\
				_filled += _copy_count;\
			}\
		}\
	}\
	END_DEF

#define canvas_clear( CANVAS ) bytes_clear( CANVAS.pixels, i4( CANVAS.size.w ) * i4( CANVAS.size.h ) << pixel_shift )

////////////////////////////////
/// canvas rendering

////////
// pixel

#define canvas_pixel_safe( CANVAS, X, Y ) ( point_in_size( X, Y, CANVAS.size.w, CANVAS.size.h ) )

#define canvas_get_pixel_index( CANVAS, INDEX ) CANVAS.pixels[ ( INDEX ) ]
#define canvas_get_pixel_row( CANVAS, X, ROW ) canvas_get_pixel_index( CANVAS, i4( X ) + i4( ROW ) )
#define canvas_get_pixel( CANVAS, X, Y ) canvas_get_pixel_row( CANVAS, X, i4( Y ) * i4( CANVAS.size.w ) )
#define canvas_get_pixel_safe( CANVAS, X, Y ) pick( canvas_pixel_safe( CANVAS, X, Y ), canvas_get_pixel( CANVAS, X, Y ), pixel( 0, 0, 0, 0 ) )

#define _canvas_draw_pixel_index_( CANVAS, INDEX, PIXEL, BLEND... ) ( canvas_get_pixel_index( CANVAS, INDEX ) ) = ( PIXEL )
#define _canvas_draw_pixel_row_( CANVAS, X, ROW, PIXEL ) ( canvas_get_pixel_row( CANVAS, X, ROW ) ) = ( PIXEL )
#define _canvas_draw_pixel_( CANVAS, X, Y, PIXEL ) ( canvas_get_pixel( CANVAS, X, Y ) ) = ( PIXEL )

#define _canvas_draw_pixel_index_avg( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp const pixel _PIXEL = PIXEL;\
		temp pixel const_ref _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->argb = ( ( _p->argb & 0xfefefefe ) >> 1 ) + ( ( ( _PIXEL.argb ) & 0xfefefefe ) >> 1 );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_add( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp const pixel _PIXEL = PIXEL;\
		temp pixel const_ref _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->r = n1( n2_min( n2( _p->r ) + n2( _PIXEL.r ), max_n1 ) );\
		_p->g = n1( n2_min( n2( _p->g ) + n2( _PIXEL.g ), max_n1 ) );\
		_p->b = n1( n2_min( n2( _p->b ) + n2( _PIXEL.b ), max_n1 ) );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_sub( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp const pixel _PIXEL = PIXEL;\
		temp pixel const_ref _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->r = pick( _p->r <= _PIXEL.r, min_n1, _p->r - _PIXEL.r );\
		_p->g = pick( _p->g <= _PIXEL.g, min_n1, _p->g - _PIXEL.g );\
		_p->b = pick( _p->b <= _PIXEL.b, min_n1, _p->b - _PIXEL.b );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_mul( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp const pixel _PIXEL = PIXEL;\
		temp pixel const_ref _p = ref_of( canvas_get_pixel_index( CANVAS, INDEX ) );\
		_p->r = n1( ( n2( _p->r ) * n2( _PIXEL.r ) + 127 ) >> pixel_bits );\
		_p->g = n1( ( n2( _p->g ) * n2( _PIXEL.g ) + 127 ) >> pixel_bits );\
		_p->b = n1( ( n2( _p->b ) * n2( _PIXEL.b ) + 127 ) >> pixel_bits );\
	}\
	END_DEF

#define _canvas_draw_pixel_index_blend( CANVAS, INDEX, PIXEL )\
	START_DEF\
	{\
		temp const i4 _INDEX = INDEX;\
		temp const pixel _PIXEL = PIXEL;\
		skip_if( _PIXEL.a is 0 );\
		if( _PIXEL.a is max_n1 )\
		{\
			_canvas_draw_pixel_index_( CANVAS, _INDEX, _PIXEL );\
		}\
		else\
		{\
			temp pixel const_ref _p = ref_of( canvas_get_pixel_index( CANVAS, _INDEX ) );\
			temp const n2 _sa = n2( _PIXEL.a );\
			temp const n2 _ia = max_n1 - _sa;\
			_p->r = n1( ( n2( _PIXEL.r ) * _sa + n2( _p->r ) * _ia + 127 ) >> pixel_bits );\
			_p->g = n1( ( n2( _PIXEL.g ) * _sa + n2( _p->g ) * _ia + 127 ) >> pixel_bits );\
			_p->b = n1( ( n2( _PIXEL.b ) * _sa + n2( _p->b ) * _ia + 127 ) >> pixel_bits );\
			_p->a = n1( _sa + ( ( n2( _p->a ) * _ia + 127 ) >> pixel_bits ) );\
		}\
	}\
	END_DEF

////////
// unified canvas_draw_pixel_*

#define canvas_draw_pixel_index( CANVAS, INDEX, PIXEL, BLEND... ) _canvas_draw_pixel_index_##BLEND( CANVAS, INDEX, PIXEL )
#define canvas_draw_pixel_row( CANVAS, X, ROW, PIXEL, BLEND... ) canvas_draw_pixel_index( CANVAS, i4( X ) + i4( ROW ), PIXEL, BLEND )
#define canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND... ) canvas_draw_pixel_row( CANVAS, i4( X ), i4( Y ) * i4( CANVAS.size.w ), PIXEL, BLEND )
#define canvas_draw_pixel_safe( CANVAS, X, Y, PIXEL, BLEND... ) if( canvas_pixel_safe( CANVAS, _X, _Y ) ) canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND )
#define canvas_draw_pixel_trans( CANVAS, X, Y, PIXEL, BLEND... ) if( canvas_pixel_safe( CANVAS, _X, _Y ) ) canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND )
#define canvas_draw_pixel_trans_safe( CANVAS, X, Y, PIXEL, BLEND... ) if( canvas_pixel_safe( CANVAS, _X, _Y ) ) canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND )

////////
// canvas to canvas

#define canvas_draw_canvas( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp const n2 _bytes_per_row = FROM_CANVAS.size.w << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS.pixels + ( TLx ) + ( ( TLy ) * TO_CANVAS.size.w );\
		temp const pixel ref _from_ref = FROM_CANVAS.pixels;\
		temp const i4 _to_step = TO_CANVAS.size.w;\
		temp const i4 _from_step = FROM_CANVAS.size.w;\
		temp i2 _h = FROM_CANVAS.size.h;\
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
		temp const i2 _W = i2_min( TO_CANVAS.size.w - _X, FROM_CANVAS.size.w - _OFFX );\
		skip_if( _W <= 0 );\
		temp const i2 _TLy = TLy;\
		temp const i2 _start_y = MAX( 0, _TLy );\
		temp const i2 _H = i2_min( TO_CANVAS.size.h, _TLy + FROM_CANVAS.size.h ) - _start_y;\
		skip_if( _H <= 0 );\
		temp const i2 _bytes_per_row = _W << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS.pixels + _start_y * TO_CANVAS.size.w + _X;\
		temp const pixel ref _from_ref = FROM_CANVAS.pixels + ( _start_y - _TLy ) * FROM_CANVAS.size.w + _OFFX;\
		temp const i4 _to_step = TO_CANVAS.size.w;\
		temp const i4 _from_step = FROM_CANVAS.size.w;\
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
		temp pixel ref _to_ref = TO_CANVAS.pixels + ( TLy ) * TO_CANVAS.size.w + ( TLx );\
		temp const pixel ref _from_ref = FROM_CANVAS.pixels;\
		temp const i2 _width = FROM_CANVAS.size.w;\
		temp const i4 _to_step = TO_CANVAS.size.w - _width;\
		temp i2 _h = FROM_CANVAS.size.h;\
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
		temp const i2 _W = i2_min( TO_CANVAS.size.w - _X, FROM_CANVAS.size.w - _OFFX );\
		skip_if( _W <= 0 );\
		temp const i2 _TLy = TLy;\
		temp const i2 _start_y = MAX( 0, _TLy );\
		temp const i2 _H = i2_min( TO_CANVAS.size.h, _TLy + FROM_CANVAS.size.h ) - _start_y;\
		skip_if( _H <= 0 );\
		temp pixel ref _to_ref = TO_CANVAS.pixels + _start_y * TO_CANVAS.size.w + _X;\
		temp const pixel ref _from_ref = FROM_CANVAS.pixels + ( _start_y - _TLy ) * FROM_CANVAS.size.w + _OFFX;\
		temp const i4 _to_step = TO_CANVAS.size.w - _W;\
		temp const i4 _from_step = FROM_CANVAS.size.w - _W;\
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
		temp pixel ref _to_ref = TO_CANVAS.pixels + ( TLy ) * TO_CANVAS.size.w + ( TLx );\
		temp const pixel ref _from_ref = FROM_CANVAS.pixels + ( PART_TLy ) * FROM_CANVAS.size.w + ( PART_TLx );\
		temp const i4 _to_step = TO_CANVAS.size.w;\
		temp const i4 _from_step = FROM_CANVAS.size.w;\
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
		temp const i2 _W = i2_min3( TO_CANVAS.size.w - _to_x, FROM_CANVAS.size.w - _from_x, PART_SIZEw - _offset_x );\
		skip_if( _W <= 0 );\
		temp const i2 _TLy = TLy;\
		temp const i2 _to_y = MAX( 0, _TLy );\
		temp const i2 _offset_y = _to_y - _TLy;\
		temp const i2 _from_y = PART_TLy + _offset_y;\
		temp const i2 _H = i2_min3( TO_CANVAS.size.h - _to_y, FROM_CANVAS.size.h - _from_y, PART_SIZEh - _offset_y );\
		skip_if( _H <= 0 );\
		temp const i2 _bytes_per_row = _W << pixel_shift;\
		temp pixel ref _to_ref = TO_CANVAS.pixels + ( _to_y * TO_CANVAS.size.w ) + _to_x;\
		temp const pixel ref _from_ref = FROM_CANVAS.pixels + ( _from_y * FROM_CANVAS.size.w ) + _from_x;\
		temp const i4 _to_step = TO_CANVAS.size.w;\
		temp const i4 _from_step = FROM_CANVAS.size.w;\
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
/// line

#define _line_fn( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )\
	START_DEF\
	{\
		temp i2 X_NAME = i2( Ax );\
		temp i2 Y_NAME = i2( Ay );\
		temp const i2 _LINE_FN##_x2 = i2( Bx );\
		temp const i2 _LINE_FN##_y2 = i2( By );\
		temp const i2 _LINE_FN##_xd = _LINE_FN##_x2 - X_NAME;\
		temp const i2 _LINE_FN##_yd = _LINE_FN##_y2 - Y_NAME;\
		temp i4 _LINE_FN##_hs = ( i4( X_NAME ) << 20 ) + 0x80000;\
		temp i4 _LINE_FN##_vs = ( i4( Y_NAME ) << 20 ) + 0x80000;\
		temp const i2 _LINE_FN##_ax = ABS( _LINE_FN##_xd );\
		temp const i2 _LINE_FN##_ay = ABS( _LINE_FN##_yd );\
		temp i2 _LINE_FN##_a = pick( _LINE_FN##_ax > _LINE_FN##_ay, _LINE_FN##_ax, _LINE_FN##_ay );\
		temp const i4 _LINE_FN##_recip = 0x100000 / i4( MAX( _LINE_FN##_a, 1 ) );\
		temp const i4 _LINE_FN##_xs = i4( _LINE_FN##_xd ) * _LINE_FN##_recip;\
		temp const i4 _LINE_FN##_ys = i4( _LINE_FN##_yd ) * _LINE_FN##_recip;\
		temp const i2 _LINE_FN##_i = 0;\
		++_LINE_FN##_a;\
		do\
		{\
			X_NAME = i2( _LINE_FN##_hs >> 20 );\
			Y_NAME = i2( _LINE_FN##_vs >> 20 );\
			CODE;\
			_LINE_FN##_hs += _LINE_FN##_xs;\
			_LINE_FN##_vs += _LINE_FN##_ys;\
		}\
		while( --_LINE_FN##_a );\
	}\
	END_DEF

#define _line_fn_eval( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE ) _line_fn( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )
#define line_fn( Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE ) _line_fn_eval( JOIN( _LINE_FN_, __COUNTER__ ), Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )

#define _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, SUFFIX... ) line_fn( Ax, Ay, Bx, By, _X, _Y, canvas_draw_pixel##SUFFIX( CANVAS, _X, _Y, PIXEL ) );
#define canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL )
#define canvas_draw_line_safe( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _safe )

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

#define get_anchor_offsets( X_NAME, Y_NAME, W, H, ANCHOR )\
	START_DEF\
	{\
		temp const n1 _h_align = ANCHOR & 0x0F;\
		temp const n1 _v_align = ANCHOR >> 4;\
		X_NAME = 0;\
		Y_NAME = 0;\
		if( _h_align is 1 ) X_NAME = W >> 1;\
		else if( _h_align is 2 ) X_NAME = W;\
		if( _v_align is 1 ) Y_NAME = H >> 1;\
		else if( _v_align is 2 ) Y_NAME = H;\
	}\
	END_DEF

////////////////////////////////
/// font

type( font )
{
	canvas pixels;
	n2x2 letter_size;
};

#define font( CANVAS ) make( font, .pixels = CANVAS, .letter_size.w = CANVAS.size.w >> 4, .letter_size.h = CANVAS.size.h >> 4 )

#define canvas_draw_bytes( CANVAS, FONT, BYTES, BYTES_SIZE, POS, ANCHOR, COLOR )\
	START_DEF\
	{\
		temp const byte const_ref _BYTES = BYTES;\
		temp const n2 _text_len = pick( BYTES_SIZE is 0, bytes_measure( _BYTES ), BYTES_SIZE );\
		temp const i2 _text_width = _text_len * FONT.letter_size.x;\
		temp const i2 _text_height = FONT.letter_size.y;\
		temp i2 _offset_x = 0;\
		temp i2 _offset_y = 0;\
		get_anchor_offsets( _offset_x, _offset_y, _text_width, _text_height, ANCHOR );\
		temp i2 _draw_x = POS.x - _offset_x;\
		temp i2 _draw_y = POS.y - _offset_y;\
		temp i2 _w = 0;\
		temp const pixel _color = COLOR;\
		iter( _l, _text_len )\
		{\
			temp const byte _letter = _BYTES[ _l ];\
			temp const i2 _letter_x = ( _letter & 0x0F ) * FONT.letter_size.x;\
			temp const i2 _letter_y = ( _letter >> 4 ) * FONT.letter_size.y;\
			iter_grid( _X, _Y, FONT.letter_size.w, FONT.letter_size.h )\
			{\
				if( canvas_get_pixel( FONT.pixels, _letter_x + _X, _letter_y + _Y ).a isnt 0 )\
				{\
					canvas_get_pixel( CANVAS, _draw_x + _w + _X, _draw_y + _Y ) = _color;\
				}\
			}\
			_w += FONT.letter_size.x;\
		}\
	}\
	END_DEF

////////////////////////////////
/// keyboard/mouse inputs

#if OS_LINUX
	#define INPUTS_MAX 512
#else
	#define INPUTS_MAX 256
#endif

global const byte ref OS_INPUT_MAP = nothing;

#define INPUT_MASK_PRESSED 0x1
#define INPUT_MASK_HELD 0x2
#define INPUT_MASK_RELEASED 0x4

group( input_type )
{
	input_none,
	input_mouse_left,
	input_mouse_right,
	input_cancel,
	input_mouse_middle,
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
	input_count
};

embed const byte const_ref _input_map()
{
	#if OS_LINUX
		#define XK_COMPRESS( XK ) ( XK & 0x1ff )
		perm const byte _INPUT_MAP[] =
			{
				[ XK_a ] = input_a,
				[ XK_b ] = input_b,
				[ XK_c ] = input_c,
				[ XK_d ] = input_d,
				[ XK_e ] = input_e,
				[ XK_f ] = input_f,
				[ XK_g ] = input_g,
				[ XK_h ] = input_h,
				[ XK_i ] = input_i,
				[ XK_j ] = input_j,
				[ XK_k ] = input_k,
				[ XK_l ] = input_l,
				[ XK_m ] = input_m,
				[ XK_n ] = input_n,
				[ XK_o ] = input_o,
				[ XK_p ] = input_p,
				[ XK_q ] = input_q,
				[ XK_r ] = input_r,
				[ XK_s ] = input_s,
				[ XK_t ] = input_t,
				[ XK_u ] = input_u,
				[ XK_v ] = input_v,
				[ XK_w ] = input_w,
				[ XK_x ] = input_x,
				[ XK_y ] = input_y,
				[ XK_z ] = input_z,

				[ XK_0 ] = input_0,
				[ XK_1 ] = input_1,
				[ XK_2 ] = input_2,
				[ XK_3 ] = input_3,
				[ XK_4 ] = input_4,
				[ XK_5 ] = input_5,
				[ XK_6 ] = input_6,
				[ XK_7 ] = input_7,
				[ XK_8 ] = input_8,
				[ XK_9 ] = input_9,

				[ XK_space ] = input_space,
				[ XK_grave ] = input_backtick,
				[ XK_minus ] = input_minus,
				[ XK_equal ] = input_equals,
				[ XK_bracketleft ] = input_leftbracket,
				[ XK_bracketright ] = input_rightbracket,
				[ XK_backslash ] = input_backslash,
				[ XK_semicolon ] = input_semicolon,
				[ XK_apostrophe ] = input_apostrophe,
				[ XK_comma ] = input_comma,
				[ XK_period ] = input_period,
				[ XK_slash ] = input_slash,

				[ XK_COMPRESS( XK_F1 ) ] = input_f1,
				[ XK_COMPRESS( XK_F2 ) ] = input_f2,
				[ XK_COMPRESS( XK_F3 ) ] = input_f3,
				[ XK_COMPRESS( XK_F4 ) ] = input_f4,
				[ XK_COMPRESS( XK_F5 ) ] = input_f5,
				[ XK_COMPRESS( XK_F6 ) ] = input_f6,
				[ XK_COMPRESS( XK_F7 ) ] = input_f7,
				[ XK_COMPRESS( XK_F8 ) ] = input_f8,
				[ XK_COMPRESS( XK_F9 ) ] = input_f9,
				[ XK_COMPRESS( XK_F10 ) ] = input_f10,
				[ XK_COMPRESS( XK_F11 ) ] = input_f11,
				[ XK_COMPRESS( XK_F12 ) ] = input_f12,

				[ XK_COMPRESS( XK_BackSpace ) ] = input_backspace,
				[ XK_COMPRESS( XK_Tab ) ] = input_tab,
				[ XK_COMPRESS( XK_Return ) ] = input_enter,
				[ XK_COMPRESS( XK_Escape ) ] = input_escape,
				[ XK_COMPRESS( XK_Delete ) ] = input_delete,
				[ XK_COMPRESS( XK_Insert ) ] = input_insert,

				[ XK_COMPRESS( XK_Home ) ] = input_home,
				[ XK_COMPRESS( XK_End ) ] = input_end,
				[ XK_COMPRESS( XK_Page_Up ) ] = input_pageup,
				[ XK_COMPRESS( XK_Page_Down ) ] = input_pagedown,
				[ XK_COMPRESS( XK_Left ) ] = input_left,
				[ XK_COMPRESS( XK_Up ) ] = input_up,
				[ XK_COMPRESS( XK_Right ) ] = input_right,
				[ XK_COMPRESS( XK_Down ) ] = input_down,

				[ XK_COMPRESS( XK_Shift_L ) ] = input_shift,
				[ XK_COMPRESS( XK_Shift_R ) ] = input_shift,
				[ XK_COMPRESS( XK_Control_L ) ] = input_ctrl,
				[ XK_COMPRESS( XK_Control_R ) ] = input_ctrl,
				[ XK_COMPRESS( XK_Caps_Lock ) ] = input_capslock,
				[ XK_COMPRESS( XK_Alt_L ) ] = input_alt,
				[ XK_COMPRESS( XK_Alt_R ) ] = input_alt,
				[ XK_COMPRESS( XK_Super_L ) ] = input_super,
				[ XK_COMPRESS( XK_Super_R ) ] = input_super,
				[ XK_COMPRESS( XK_Menu ) ] = input_menu,
			};
	#elif OS_WINDOWS
		perm const byte _INPUT_MAP[] =
			{
				[ 'A' ] = input_a,
				[ 'B' ] = input_b,
				[ 'C' ] = input_c,
				[ 'D' ] = input_d,
				[ 'E' ] = input_e,
				[ 'F' ] = input_f,
				[ 'G' ] = input_g,
				[ 'H' ] = input_h,
				[ 'I' ] = input_i,
				[ 'J' ] = input_j,
				[ 'K' ] = input_k,
				[ 'L' ] = input_l,
				[ 'M' ] = input_m,
				[ 'N' ] = input_n,
				[ 'O' ] = input_o,
				[ 'P' ] = input_p,
				[ 'Q' ] = input_q,
				[ 'R' ] = input_r,
				[ 'S' ] = input_s,
				[ 'T' ] = input_t,
				[ 'U' ] = input_u,
				[ 'V' ] = input_v,
				[ 'W' ] = input_w,
				[ 'X' ] = input_x,
				[ 'Y' ] = input_y,
				[ 'Z' ] = input_z,

				[ '0' ] = input_0,
				[ '1' ] = input_1,
				[ '2' ] = input_2,
				[ '3' ] = input_3,
				[ '4' ] = input_4,
				[ '5' ] = input_5,
				[ '6' ] = input_6,
				[ '7' ] = input_7,
				[ '8' ] = input_8,
				[ '9' ] = input_9,

				[ VK_F1 ] = input_f1,
				[ VK_F2 ] = input_f2,
				[ VK_F3 ] = input_f3,
				[ VK_F4 ] = input_f4,
				[ VK_F5 ] = input_f5,
				[ VK_F6 ] = input_f6,
				[ VK_F7 ] = input_f7,
				[ VK_F8 ] = input_f8,
				[ VK_F9 ] = input_f9,
				[ VK_F10 ] = input_f10,
				[ VK_F11 ] = input_f11,
				[ VK_F12 ] = input_f12,

				[ VK_SPACE ] = input_space,
				[ VK_ESCAPE ] = input_escape,
				[ VK_TAB ] = input_tab,
				[ VK_CAPITAL ] = input_capslock,
				[ VK_SHIFT ] = input_shift,
				[ VK_CONTROL ] = input_ctrl,
				[ VK_MENU ] = input_alt,
				[ VK_RETURN ] = input_enter,
				[ VK_BACK ] = input_backspace,
				[ VK_INSERT ] = input_insert,
				[ VK_DELETE ] = input_delete,
				[ VK_HOME ] = input_home,
				[ VK_END ] = input_end,
				[ VK_PRIOR ] = input_pageup,
				[ VK_NEXT ] = input_pagedown,

				[ VK_UP ] = input_up,
				[ VK_DOWN ] = input_down,
				[ VK_LEFT ] = input_left,
				[ VK_RIGHT ] = input_right,

				[ VK_OEM_3 ] = input_backtick,
				[ VK_OEM_MINUS ] = input_minus,
				[ VK_OEM_PLUS ] = input_equals,
				[ VK_OEM_4 ] = input_leftbracket,
				[ VK_OEM_6 ] = input_rightbracket,
				[ VK_OEM_5 ] = input_backslash,
				[ VK_OEM_1 ] = input_semicolon,
				[ VK_OEM_7 ] = input_apostrophe,
				[ VK_OEM_COMMA ] = input_comma,
				[ VK_OEM_PERIOD ] = input_period,
				[ VK_OEM_2 ] = input_slash,

				[ VK_LWIN ] = input_super,
				[ VK_RWIN ] = input_super,
				[ VK_APPS ] = input_menu,
			};
	#endif

	out to( const byte const_ref, ref_of( _INPUT_MAP ) );
}

////////////////////////////////
/// window

type_from( PICK( OS_LINUX, Window, HWND ) ) os_handle;
type_from( PICK( OS_LINUX, Display ref, HDC ) ) os_display;
type_from( PICK( OS_LINUX, XImage ref, BITMAPINFO ) ) os_image;
type_from( PICK( OS_LINUX, XEvent, MSG ) ) os_event;

object( window )
{
	os_handle handle;
	os_display display;
	os_image image;
	#if OS_LINUX
		GC gc;
		Picture pic;
		Pixmap pixmap;
		Pixmap present_pixmap;
		Picture present_pic;
		XTransform transform;
	#elif OS_WINDOWS
		flag wm_timer;
		flag wm_resize;
	#endif
	canvas buffer;
	n2x2 size_target;
	n2x2 buffer_max;
	n2 scale;
	anchor buffer_anchor;
	flag visible;
	flag refresh;
	flag close;
	window_fn start_fn;
	window_fn tick_fn;
	window_fn resize_fn;
	window_fn draw_fn;
	window_fn input_fn;
	n8 tick;
	nano start_nano;
	nano past_nano;
	nano target_frame_nano;
	r8 fps_target;
	r8 total_time;
	r8 delta_time;
	byte inputs[ INPUTS_MAX ];
	byte inputs_pressed[ 32 ];
	n1 inputs_pressed_count;
	byte inputs_released[ 32 ];
	n1 inputs_released_count;
	i4 mouse_x;
	i4 mouse_y;
	i2 mouse_delta_x;
	i2 mouse_delta_y;
	d4 mouse_pixel_x;
	d4 mouse_pixel_y;
};

global window current_window;

#define max_alive_windows 8
global window alive_windows[ max_alive_windows ];
global n1 alive_windows_count = 0;

#define key_pressed( KEY ) ( current_window->inputs[ input_##KEY ] & INPUT_MASK_PRESSED )
#define key_held( KEY ) ( current_window->inputs[ input_##KEY ] & INPUT_MASK_HELD )
#define key_released( KEY ) ( current_window->inputs[ input_##KEY ] & INPUT_MASK_RELEASED )

#define mouse_left_pressed() key_pressed( mouse_left )
#define mouse_middle_pressed() key_pressed( mouse_middle )
#define mouse_right_pressed() key_pressed( mouse_right )

#define mouse_left_held() key_held( mouse_left )
#define mouse_middle_held() key_held( mouse_middle )
#define mouse_right_held() key_held( mouse_right )

#define mouse_left_released() key_released( mouse_left )
#define mouse_middle_released() key_released( mouse_middle )
#define mouse_right_released() key_released( mouse_right )

object_fn( window, set_start_fn, const window_fn start_fn )
{
	out_if_nothing( this );
	this->start_fn = start_fn;
}

object_fn( window, set_tick_fn, const window_fn tick_fn )
{
	out_if_nothing( this );
	this->tick_fn = tick_fn;
}

object_fn( window, set_resize_fn, const window_fn resize_fn )
{
	out_if_nothing( this );
	this->resize_fn = resize_fn;
}

object_fn( window, set_draw_fn, const window_fn draw_fn )
{
	out_if_nothing( this );
	this->draw_fn = draw_fn;
}

object_fn( window, set_input_fn, const window_fn input_fn )
{
	out_if_nothing( this );
	this->input_fn = input_fn;
}

object_fn( window, clear_events )
{
	out_if( this is nothing );

	#if OS_LINUX
		Window root = DefaultRootWindow( this->display );
		XEvent release_event = { 0 };
		release_event.type = ButtonRelease;
		release_event.xbutton.display = this->display;
		release_event.xbutton.window = root;
		release_event.xbutton.root = root;
		release_event.xbutton.button = Button1;
		release_event.xbutton.time = CurrentTime;
		release_event.xbutton.same_screen = True;

		XSendEvent( this->display, root, False, SubstructureNotifyMask | SubstructureRedirectMask, ref_of( release_event ) );
		XFlush( this->display );

		XEvent e;
		while( XCheckWindowEvent( this->display, this->handle, ~ 0, ref_of( e ) ) )
		{
		}
	#elif OS_WINDOWS
		ReleaseCapture();

		MSG msg;
		while( PeekMessage( ref_of( msg ), this->handle, 0, 0, PM_REMOVE ) )
		{
		}
	#endif
}

object_fn( window, set_scale, const r8 scale )
{
	out_if_nothing( this );

	this->scale = n2_max( r8_ceil( scale ), 1 );

	#if OS_LINUX
		this->transform.matrix[ 0 ][ 0 ] = XDoubleToFixed( 1.0 / r8( this->scale ) );
		this->transform.matrix[ 1 ][ 1 ] = XDoubleToFixed( 1.0 / r8( this->scale ) );
	#endif
}

object_fn( window, update_scale )
{
	if( this->buffer_max.w > 0 or this->buffer_max.h > 0 )
	{
		window_set_scale( this, r8_max3( 1.0, r8( this->size_target.w ) / r8( this->buffer_max.w ), r8( this->size_target.h ) / r8( this->buffer_max.h ) ) );
	}
}

fn _window_set_size( const window this, const n2 width, const n2 height )
{
	out_if( this->size_target.w is width and this->size_target.h is height );
	this->size_target.w = width;
	this->size_target.h = height;

	window_update_scale( this );
}

fn _window_resize( const window this )
{
	out_if_any( this is nothing, this->size_target.w <= 1, this->size_target.h <= 1 );

	temp n2 buffer_w = ( this->size_target.w + this->scale - 1 ) / this->scale;
	temp n2 buffer_h = ( this->size_target.h + this->scale - 1 ) / this->scale;

	if( this->buffer.size.w isnt buffer_w or this->buffer.size.h isnt buffer_h ) canvas_resize( this->buffer, buffer_w, buffer_h );

	#if OS_LINUX
		this->image->data = to( byte ref, this->buffer.pixels );
		this->image->width = this->buffer.size.w;
		this->image->height = this->buffer.size.h;
		this->image->bytes_per_line = this->buffer.size.w << pixel_shift;

		if( this->pixmap )
		{
			XFreePixmap( this->display, this->pixmap );
			XRenderFreePicture( this->display, this->pic );
		}

		this->pixmap = XCreatePixmap( this->display, this->handle, this->buffer.size.w, this->buffer.size.h, DefaultDepth( this->display, DefaultScreen( this->display ) ) );
		this->pic = XRenderCreatePicture( this->display, this->pixmap, XRenderFindVisualFormat( this->display, DefaultVisual( this->display, DefaultScreen( this->display ) ) ), 0, 0 );
		XRenderSetPictureTransform( this->display, this->pic, ref_of( this->transform ) );

		if( this->present_pixmap )
		{
			XFreePixmap( this->display, this->present_pixmap );
			XRenderFreePicture( this->display, this->present_pic );
		}

		this->present_pixmap = XCreatePixmap( this->display, this->handle, this->size_target.w, this->size_target.h, DefaultDepth( this->display, DefaultScreen( this->display ) ) );
		this->present_pic = XRenderCreatePicture( this->display, this->present_pixmap, XRenderFindVisualFormat( this->display, DefaultVisual( this->display, DefaultScreen( this->display ) ) ), 0, 0 );
	#elif OS_WINDOWS
		this->image.bmiHeader.biWidth = this->buffer.size.w;
		this->image.bmiHeader.biHeight = -this->buffer.size.h;
	#endif
	call( this, resize_fn );
}

object_fn( window, resize, const n2 width, const n2 height )
{
	out_if_any( this is nothing, width <= 1, height <= 1 );

	window_clear_events( this );

	_window_set_size( this, width, height );
	_window_resize( this );

	#if OS_LINUX
		XResizeWindow( this->display, this->handle, width, height );
		XFlush( this->display );
	#elif OS_WINDOWS
		SetWindowPos( this->handle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );
	#endif
}

object_fn( window, set_buffer_max, const n2 width, const n2 height )
{
	out_if_nothing( this );

	if( this->buffer_max.w isnt width or this->buffer_max.h isnt height )
	{
		this->buffer_max.w = width;
		this->buffer_max.h = height;

		window_update_scale( this );
	}

	_window_resize( this );
}

fn _window_update( const window this )
{
	out_if_any( this is nothing, this->buffer.size.w <= 1, this->buffer.size.h <= 1 );

	temp nano now = get_nano();
	this->delta_time = r8( now - this->past_nano ) / r8( nano_per_sec );
	this->total_time += this->delta_time;
	this->past_nano = now;
	++this->tick;

	this->mouse_delta_x = this->mouse_x;
	this->mouse_delta_y = this->mouse_y;

	#if OS_LINUX
		Window _empty;
		i4 _root;
		n4 _mask;
		XQueryPointer( this->display, this->handle, ref_of( _empty ), ref_of( _empty ), ref_of( _root ), ref_of( _root ), ref_of( this->mouse_x ), ref_of( this->mouse_y ), ref_of( _mask ) );
	#elif OS_WINDOWS
		POINT cursor;
		GetCursorPos( ref_of( cursor ) );
		ScreenToClient( this->handle, ref_of( cursor ) );
		this->mouse_x = cursor.x;
		this->mouse_y = cursor.y;
	#endif

	this->mouse_delta_x -= this->mouse_x;
	this->mouse_delta_y -= this->mouse_y;

	temp const n2 scaled_width = this->buffer.size.w * this->scale;
	temp const n2 scaled_height = this->buffer.size.h * this->scale;

	temp const i4 overflow_w = i4( this->size_target.w ) - i4( scaled_width );
	temp const i4 overflow_h = i4( this->size_target.h ) - i4( scaled_height );

	temp i4 offset_x;
	temp i4 offset_y;

	get_anchor_offsets( offset_x, offset_y, overflow_w, overflow_h, this->buffer_anchor );

	this->mouse_pixel_x = d4_div( i4_to_d4( this->mouse_x - offset_x ), i4_to_d4( this->scale ) );
	this->mouse_pixel_y = d4_div( i4_to_d4( this->mouse_y - offset_y ), i4_to_d4( this->scale ) );

	call( this, tick_fn );

	if( this->refresh )
	{
		this->refresh = no;
		call( this, draw_fn );

		#if OS_LINUX
			if( this->scale > 1 )
			{
				XPutImage( this->display, this->pixmap, this->gc, this->image, 0, 0, 0, 0, this->buffer.size.w, this->buffer.size.h );
				XRenderComposite( this->display, PictOpSrc, this->pic, None, this->present_pic, 0, 0, 0, 0, offset_x, offset_y, scaled_width, scaled_height );
				XPresentPixmap( this->display, this->handle, this->present_pixmap, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
			}
			else
			{
				XPutImage( this->display, this->handle, this->gc, this->image, 0, 0, offset_x, offset_y, this->buffer.size.w, this->buffer.size.h );
			}
			XSync( this->display, no );
		#elif OS_WINDOWS
			if( this->scale > 1 )
			{
				SetStretchBltMode( this->display, COLORONCOLOR );
				StretchDIBits( this->display, offset_x, offset_y, scaled_width, scaled_height, 0, 0, this->buffer.size.w, this->buffer.size.h, this->buffer.pixels, ref_of( this->image ), DIB_RGB_COLORS, SRCCOPY );
			}
			else
			{
				SetDIBitsToDevice( this->display, offset_x, offset_y, this->buffer.size.w, this->buffer.size.h, 0, 0, 0, this->buffer.size.h, this->buffer.pixels, ref_of( this->image ), DIB_RGB_COLORS );
			}
		#endif
	}

	if( this->inputs_pressed_count > 0 )
	{
		iter( input, this->inputs_pressed_count )
		{
			this->inputs[ this->inputs_pressed[ input ] ] = INPUT_MASK_HELD;
			this->inputs_pressed[ input ] = 0;
		}
		this->inputs_pressed_count = 0;
	}

	if( this->inputs_released_count > 0 )
	{
		iter( input, this->inputs_released_count )
		{
			this->inputs[ this->inputs_released[ input ] ] = 0;
			this->inputs_released[ input ] = 0;
		}
		this->inputs_released_count = 0;
	}

	temp const nano target_end = this->start_nano + ( this->tick * this->target_frame_nano );
	now = get_nano();

	if( target_end > now )
	{
		nano_sleep( target_end - now );
	}
}

object_fn( window, set_fps, const r8 in_fps )
{
	this->fps_target = in_fps;
	this->target_frame_nano = to( nano, r8( nano_per_sec ) / this->fps_target );
}

object_fn( window, show )
{
	out_if( this->visible is yes );

	#if OS_LINUX
		XMapRaised( this->display, this->handle );
		XSync( this->display, no );
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
		XUnmapWindow( this->display, this->handle );
	#elif OS_WINDOWS
		ShowWindow( this->handle, SW_HIDE );
	#endif

	this->visible = no;
}

object_fn( window, center )
{
	out_if_nothing( this );

	#if OS_LINUX
		XMoveWindow( this->display, this->handle, ( DisplayWidth( this->display, DefaultScreen( this->display ) ) - this->size_target.w ) >> 1, ( DisplayHeight( this->display, DefaultScreen( this->display ) ) - this->size_target.h ) >> 1 );
		XSync( this->display, no );
	#elif OS_WINDOWS
		SetWindowPos( this->handle, NULL, ( GetSystemMetrics( SM_CXSCREEN ) - this->size_target.w ) >> 1, ( GetSystemMetrics( SM_CYSCREEN ) - this->size_target.h ) >> 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	#endif
}

object_fn( window, refresh )
{
	this->refresh = yes;
	#if OS_LINUX
		XClearArea( this->display, this->handle, 0, 0, 0, 0, yes );
		XSync( this->display, no );
	#elif OS_WINDOWS
		InvalidateRect( this->handle, nothing, no );
		UpdateWindow( this->handle );
	#endif
}

////////////////////////////////
/// window events

group( window_event_type, n2 )
{
	window_event_resize = PICK( OS_LINUX, ConfigureNotify, WM_SIZE ),
	window_event_refresh = PICK( OS_LINUX, Expose, WM_PAINT ),
	window_event_close = PICK( OS_LINUX, ClientMessage, WM_DESTROY ),
	window_event_key_activate = PICK( OS_LINUX, KeyPress, WM_KEYDOWN ),
	window_event_key_deactivate = PICK( OS_LINUX, KeyRelease, WM_KEYUP ),
	window_event_focus_lost = PICK( OS_LINUX, FocusOut, WM_KILLFOCUS )
};

#define HANDLE_MOUSE_DOWN( button_input )\
	if( not( this->inputs[ button_input ] & INPUT_MASK_HELD ) )\
	{\
		this->inputs[ button_input ] |= INPUT_MASK_PRESSED | INPUT_MASK_HELD;\
		this->inputs_pressed[ this->inputs_pressed_count++ ] = button_input;\
	}\
	is_input = yes

#define HANDLE_MOUSE_UP( button_input )\
	this->inputs[ button_input ] = INPUT_MASK_RELEASED;\
	this->inputs_released[ this->inputs_released_count++ ] = button_input;\
	is_input = yes

#if OS_LINUX
	embed out_state window_process_event( const window this, const window_event_type event, const os_event ref e )
#elif OS_WINDOWS
	embed LRESULT CALLBACK window_process_event( const os_handle h, const window_event_type event, const WPARAM wp, const LPARAM lp )
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
				this->wm_timer = yes;
				SetTimer( h, 1, 0, nothing );
				skip;
			}

			when( WM_EXITSIZEMOVE )
			{
				KillTimer( h, 1 );
				this->wm_resize = no;
				this->wm_timer = no;
				skip;
			}

			when( WM_TIMER )
			{
				if( wp is 1 )
				{
					if( this->wm_resize is yes )
					{
						_window_resize( this );
						this->wm_resize = no;
					}

					_window_update( this );
				}
				skip;
			}

			when( WM_ERASEBKGND ) out yes;
			when( WM_SETCURSOR )
			{
				if( LOWORD( lp ) is HTCLIENT )
				{
					SetCursor( LoadCursor( NULL, IDC_ARROW ) );
					out yes;
				}
				skip;
			}
		#endif

		when( window_event_focus_lost )
		{
			bytes_clear( this->inputs, INPUTS_MAX );
			bytes_clear( this->inputs_pressed, 32 );
			bytes_clear( this->inputs_released, 32 );
			this->inputs_pressed_count = 0;
			this->inputs_released_count = 0;
			skip;
		}

		when( window_event_resize )
		{
			this->refresh = yes;
			#if OS_WINDOWS
				this->wm_resize = yes;
				_window_set_size( this, LOWORD( lp ), HIWORD( lp ) );
				if( this->wm_timer is no )
				{
					_window_resize( this );
				}
			#elif OS_LINUX
				_window_set_size( this, e->xconfigure.width, e->xconfigure.height );
				_window_resize( this );
			#endif
			skip;
		}

		when( window_event_refresh )
		{
			this->refresh = yes;
			skip;
		}

		when( window_event_key_activate )
		{
			temp const byte key = OS_INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( this->display, e->xkey.keycode, 0, 0 ) & 0x1FF, wp & 0xff ) ];
			if( key isnt 0 and not( this->inputs[ key ] & INPUT_MASK_HELD ) )
			{
				this->inputs[ key ] |= INPUT_MASK_PRESSED | INPUT_MASK_HELD;
				this->inputs_pressed[ this->inputs_pressed_count++ ] = key;
			}
			is_input = yes;
			skip;
		}

		when( window_event_key_deactivate )
		{
			temp const byte key = OS_INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( this->display, e->xkey.keycode, 0, 0 ) & 0x1FF, wp & 0xff ) ];
			if( key isnt 0 )
			{
				this->inputs[ key ] = INPUT_MASK_RELEASED;
				this->inputs_released[ this->inputs_released_count++ ] = key;
			}
			is_input = yes;
			skip;
		}

		when( window_event_close )
		{
			#if OS_WINDOWS
				PostQuitMessage( 0 );
			#endif

			--alive_windows_count;

			out success;
		}

		#if OS_LINUX
			when( ButtonPress )
			{
				with( e->xbutton.button )
				{
					when( Button1 )
					{
						HANDLE_MOUSE_DOWN( input_mouse_left );
						skip;
					}
					when( Button2 )
					{
						HANDLE_MOUSE_DOWN( input_mouse_middle );
						skip;
					}
					when( Button3 )
					{
						HANDLE_MOUSE_DOWN( input_mouse_right );
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
						HANDLE_MOUSE_UP( input_mouse_left );
						skip;
					}
					when( Button2 )
					{
						HANDLE_MOUSE_UP( input_mouse_middle );
						skip;
					}
					when( Button3 )
					{
						HANDLE_MOUSE_UP( input_mouse_right );
						skip;
					}
				}
				skip;
			}
		#elif OS_WINDOWS
			when( WM_LBUTTONDOWN )
			{
				HANDLE_MOUSE_DOWN( input_mouse_left );
				skip;
			}
			when( WM_MBUTTONDOWN )
			{
				HANDLE_MOUSE_DOWN( input_mouse_middle );
				skip;
			}
			when( WM_RBUTTONDOWN )
			{
				HANDLE_MOUSE_DOWN( input_mouse_right );
				skip;
			}
			when( WM_LBUTTONUP )
			{
				HANDLE_MOUSE_UP( input_mouse_left );
				skip;
			}
			when( WM_MBUTTONUP )
			{
				HANDLE_MOUSE_UP( input_mouse_middle );
				skip;
			}
			when( WM_RBUTTONUP )
			{
				HANDLE_MOUSE_UP( input_mouse_right );
				skip;
			}
		#endif

		other skip;
	}
	if( is_input is yes )
	{
		call( this, input_fn );
	}
	exit_events:
	#if OS_WINDOWS
		out DefWindowProc( h, event, wp, lp );
	#elif OS_LINUX
		out success;
	#endif
}

object_fn( window, process )
{
	current_window = this;
	current_canvas_ref = ref_of( this->buffer );

	if( this->tick is 0 )
	{
		this->start_nano = get_nano();
		this->past_nano = this->start_nano;
		call( this, start_fn );
		_window_resize( this );
	}
	else if( this->tick is 1 )
	{
		this->refresh = yes;
		window_show( this );
		window_center( this );
	}

	os_event e;
	#if OS_LINUX
		while( XPending( this->display ) )
		{
			XNextEvent( this->display, ref_of( e ) );
			window_process_event( this, e.type, ref_of( e ) );
		}
	#elif OS_WINDOWS
		while( PeekMessage( ref_of( e ), 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( ref_of( e ) );
			DispatchMessage( ref_of( e ) );
		}
	#endif

	out_if( this->close is yes );

	_window_update( this );
}

////////
// new window

new_object_fn( window, const n2 width, const n2 height )
{
	temp const window out_window = new_object( window );

	out_window->scale = 1;
	out_window->size_target.w = width;
	out_window->size_target.h = height;
	out_window->buffer = canvas( width, height );
	out_window->buffer_anchor = anchor_middle_center;

	byte ref name = "test";

	#if OS_LINUX
		out_window->display = XOpenDisplay( 0 );
		temp i4 screen = DefaultScreen( out_window->display );

		out_window->handle = XCreateSimpleWindow( out_window->display, RootWindow( out_window->display, screen ), 0, 0, width, height, 0, 0, 0 );

		XSetWindowBackgroundPixmap( out_window->display, out_window->handle, None );
		XSelectInput( out_window->display, out_window->handle, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | FocusChangeMask );
		XkbSetDetectableAutoRepeat( out_window->display, yes, nothing );

		out_window->image = XCreateImage( out_window->display, DefaultVisual( out_window->display, screen ), DefaultDepth( out_window->display, screen ), ZPixmap, 0, to( byte ref, out_window->buffer.pixels ), width, height, 32, 0 );
		out_window->gc = XCreateGC( out_window->display, out_window->handle, 0, 0 );
		out_window->transform.matrix[ 2 ][ 2 ] = XDoubleToFixed( 1.0 );
	#elif OS_WINDOWS
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = to( type_of( wc.lpfnWndProc ), window_process_event );
		wc.hInstance = GetModuleHandle( nothing );
		wc.lpszClassName = name;
		wc.hbrBackground = nothing;
		RegisterClass( ref_of( wc ) );

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );

		out_window->handle = CreateWindow( name, name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nothing, nothing, GetModuleHandle( nothing ), nothing );

		out_window->display = GetDC( out_window->handle );

		out_window->image.bmiHeader.biSize = size_of( out_window->image.bmiHeader );
		out_window->image.bmiHeader.biWidth = width;
		out_window->image.bmiHeader.biHeight = -height;
		out_window->image.bmiHeader.biPlanes = 1;
		out_window->image.bmiHeader.biBitCount = 32;
		out_window->image.bmiHeader.biCompression = BI_RGB;
		SetWindowLongPtr( out_window->handle, GWLP_USERDATA, to( LONG_PTR, out_window ) );
	#endif
	window_set_fps( out_window, 60 );
	current_window = out_window;
	alive_windows[ alive_windows_count++ ] = current_window;
	out current_window;
}

////////////////////////////////
/// Heptane system functions

fn _C7H16_init()
{
	OS_INPUT_MAP = _input_map();
}

fn _C7H16_loop()
{
	temp flag close = no;
	loop
	{
		out_if( alive_windows_count is 0 );
		iter( window_id, alive_windows_count )
		{
			temp window this_window = alive_windows[ window_id ];
			window_process( this_window );
			if( this_window->close )
			{
				close = yes;
				skip;
			}
		}
		out_if( close );
	}
}

fn _C7H16_close()
{
}

#undef start
#define start\
	fn _C7H16_main( const i4 start_parameters_count, const byte const_ref const_ref start_parameters );\
	_main_fn\
	{\
		_C7H16_init();\
		_C7H16_main( start_parameters_count, start_parameters );\
		_C7H16_loop();\
		_C7H16_close();\
		out success;\
	}\
	fn _C7H16_main( const i4 start_parameters_count, const byte const_ref const_ref start_parameters )

////////////////////////////////////////////////////////////////
