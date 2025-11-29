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

////////
// pixel

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
#define canvas_get_pixel( CANVAS, X, Y ) canvas_get_pixel_index( CANVAS, index_2d( X, Y, CANVAS->size.w ) )
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
			_canvas_draw_pixel_index_( CANVAS, _INDEX, _PIXEL );\
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
#define canvas_draw_pixel( CANVAS, X, Y, PIXEL, BLEND... ) canvas_draw_pixel_index( CANVAS, index_2d( X, Y, CANVAS->size.w ), PIXEL, BLEND )

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
/// display

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

object( window_canvas )
{
	canvas canvas;

	sizing_mode sizing;
	scaling_mode scaling;

	window_canvas_fn fn_draw;

	i4x2 pos;
	r4x2 scale;

	#if OS_LINUX
		Pixmap pixmap;
		Picture picture;
	#elif OS_WINDOWS
		//
	#endif
}
packed;

new_object_fn( window_canvas, canvas const canvas, sizing_mode const sizing, scaling_mode const scaling, window_canvas_fn const fn_draw )
{
	temp window_canvas out_window_canvas = new_object( window_canvas );
	out_window_canvas->canvas = canvas;
	out_window_canvas->sizing = sizing;
	out_window_canvas->scaling = scaling;
	out_window_canvas->fn_draw = fn_draw;
	out_window_canvas->scale = r4x2( 1.0, 1.0 );
	out out_window_canvas;
}

delete_object_fn( window_canvas )
{
	delete_canvas( this->canvas );

	delete_object( this );
}

object_fn( window_canvas, set_scale, r4x2 const scale )
{
	this->scale = scale;
	this->scaling = scaling_manual;
}
#define window_canvas_set_scale( WINDOW_CANVAS, WIDTH_SCALE, HEIGHT_SCALE... ) window_canvas_set_scale( WINDOW_CANVAS, r4x2( WIDTH_SCALE, DEFAULT( WIDTH_SCALE, HEIGHT_SCALE ) ) )

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
		XImage ref buffer_image;
		Pixmap buffer;
		Picture buffer_picture;
		XShmSegmentInfo buffer_shm;
	#elif OS_WINDOWS
		HBITMAP buffer;
		HDC buffer_dc;
		HDC window_dc;
	#endif

	list canvases;
	n2x2 size;

	flag clear_before_present;
	flag visible;
	flag bordered;
	flag close;

	n8 tick;

	byte inputs[ inputs_count ];
	n1 inputs_active;
	list inputs_pressed;
	list inputs_released;
	r4x2 scroll;
	i4 mouse_x;
	i4 mouse_y;

	window_fn fn_start;
	window_fn fn_resize;
	window_fn fn_tick;
	window_fn fn_draw;
};

global window current_window = nothing;
global list windows = nothing;

global r4 windows_fps_tick = 60;
global r4 windows_fps_draw = 60;
global nano windows_time_start = 0;
global nano windows_time_next_draw = 0;
global n8 windows_time_tick = 0;

#define window_set_fn_start( WINDOW, FN ) WINDOW->fn_start = to( window_fn, FN )
#define window_set_fn_resize( WINDOW, FN ) WINDOW->fn_resize = to( window_fn, FN )
#define window_set_fn_tick( WINDOW, FN ) WINDOW->fn_tick = to( window_fn, FN )
#define window_set_fn_draw( WINDOW, FN ) WINDOW->fn_draw = to( window_fn, FN )

#if OS_LINUX
	global Display ref windows_display = nothing;
#endif

////////
// visible window functions

object_fn( window, add_window_canvas, window_canvas in_window_canvas )
{
	list_add( this->canvases, in_window_canvas );
}

object_fn( window, refresh )
{
	#if OS_LINUX
		XClearArea( windows_display, this->handle, 0, 0, 0, 0, yes );
	#elif OS_WINDOWS
		InvalidateRect( this->handle, nothing, no );
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
		struct
		{
			n4 flags;
			n4 functions;
			n4 decorations;
			i4 input_mode;
			n4 status;
		}
		hints = { 2, 0, 1, 0, 0 };
		Atom prop = XInternAtom( windows_display, "_MOTIF_WM_HINTS", False );
		XChangeProperty( windows_display, this->handle, prop, prop, 32, PropModeReplace, to( byte ref, ref_of( hints ) ), 5 );
		XSync( windows_display, no );
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
		struct
		{
			n4 flags;
			n4 functions;
			n4 decorations;
			i4 input_mode;
			n4 status;
		}
		hints = { 2, 0, 0, 0, 0 };
		Atom prop = XInternAtom( windows_display, "_MOTIF_WM_HINTS", False );
		XChangeProperty( windows_display, this->handle, prop, prop, 32, PropModeReplace, to( byte ref, ref_of( hints ) ), 5 );
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

	this->using_buffer = this->using_buffer or( this->canvases->count > 1 ) or this->clear_before_present;

	#if OS_LINUX
		temp n4 const screen = DefaultScreen( windows_display );
		temp n4 const depth = DefaultDepth( windows_display, screen );
		temp XRenderPictFormat ref format = XRenderFindVisualFormat( windows_display, DefaultVisual( windows_display, screen ) );

		if( this->using_buffer )
		{
			if( this->buffer_picture )
			{
				XRenderFreePicture( windows_display, this->buffer_picture );
				this->buffer_picture = 0;
			}

			if( this->buffer )
			{
				XFreePixmap( windows_display, this->buffer );
				this->buffer = 0;
			}

			if( this->buffer_image )
			{
				XShmDetach( windows_display, ref_of( this->buffer_shm ) );
				XSync( windows_display, False );
				shmdt( this->buffer_shm.shmaddr );
				shmctl( this->buffer_shm.shmid, IPC_RMID, 0 );
				this->buffer_image->data = nothing;
				XDestroyImage( this->buffer_image );
				this->buffer_image = nothing;
			}

			this->buffer_image = XShmCreateImage( windows_display, DefaultVisual( windows_display, screen ), depth, ZPixmap, nothing, ref_of( this->buffer_shm ), this->size.w, this->size.h );
			this->buffer_shm.shmid = shmget( IPC_PRIVATE, this->buffer_image->bytes_per_line * this->size.h, IPC_CREAT | 0777 );
			this->buffer_shm.shmaddr = this->buffer_image->data = shmat( this->buffer_shm.shmid, nothing, 0 );
			this->buffer_shm.readOnly = False;
			XShmAttach( windows_display, ref_of( this->buffer_shm ) );

			this->buffer_pixels = to( pixel ref, this->buffer_image->data );
			this->buffer = XShmCreatePixmap( windows_display, this->handle, this->buffer_image->data, ref_of( this->buffer_shm ), this->size.w, this->size.h, depth );
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

	iter_list( this->canvases, wc_index )
	{
		temp window_canvas const this_wc = list_get_iter( wc_index, window_canvas );

		with( this_wc->scaling )
		{
			when( scaling_integer_fit_floor, scaling_integer_fit_round, scaling_integer_fit_ceil, scaling_rational_fit )
			{
				temp r4 const scale = r4_min( r4( this->size.w ) / r4( this_wc->canvas->size.w ), r4( this->size.h ) / r4( this_wc->canvas->size.h ) );
				this_wc->scale.w = scale;
				this_wc->scale.h = scale;
				skip;
			}

			when( scaling_integer_fill_floor, scaling_integer_fill_round, scaling_integer_fill_ceil, scaling_rational_fill )
			{
				temp r4 const scale = r4_max( r4( this->size.w ) / r4( this_wc->canvas->size.w ), r4( this->size.h ) / r4( this_wc->canvas->size.h ) );
				this_wc->scale.w = scale;
				this_wc->scale.h = scale;
				skip;
			}

			when( scaling_integer_stretch_floor, scaling_integer_stretch_round, scaling_integer_stretch_ceil, scaling_rational_stretch )
			{
				this_wc->scale.w = r4( this->size.w ) / r4( this_wc->canvas->size.w );
				this_wc->scale.h = r4( this->size.h ) / r4( this_wc->canvas->size.h );
				skip;
			}

			other skip;
		}

		with( this_wc->scaling )
		{
			when( scaling_integer_stretch_floor )
			{
				this_wc->scale.w = r4_floor( this_wc->scale.w );
				this_wc->scale.h = r4_floor( this_wc->scale.h );
				skip;
			}

			when( scaling_integer_stretch_ceil )
			{
				this_wc->scale.w = r4_ceil( this_wc->scale.w );
				this_wc->scale.h = r4_ceil( this_wc->scale.h );
				skip;
			}

			when( scaling_integer_stretch_round )
			{
				this_wc->scale.w = r4_round( this_wc->scale.w );
				this_wc->scale.h = r4_round( this_wc->scale.h );
				skip;
			}

			when( scaling_integer_fit_floor, scaling_integer_fill_floor )
			{
				temp r4 const scale = r4_floor( this_wc->scale.w );
				this_wc->scale.w = scale;
				this_wc->scale.h = scale;
				skip;
			}

			when( scaling_integer_fit_ceil, scaling_integer_fill_ceil )
			{
				temp r4 const scale = r4_ceil( this_wc->scale.w );
				this_wc->scale.w = scale;
				this_wc->scale.h = scale;
				skip;
			}

			when( scaling_integer_fit_round, scaling_integer_fill_round )
			{
				temp r4 const scale = r4_round( this_wc->scale.w );
				this_wc->scale.w = scale;
				this_wc->scale.h = scale;
				skip;
			}

			other skip;
		}

		#if OS_LINUX
			if( this_wc->pixmap )
			{
				XRenderFreePicture( windows_display, this_wc->picture );
				XFreePixmap( windows_display, this_wc->pixmap );
			}

			this_wc->pixmap = XCreatePixmap( windows_display, this->handle, this_wc->canvas->size.w, this_wc->canvas->size.h, depth );
			this_wc->picture = XRenderCreatePicture( windows_display, this_wc->pixmap, format, 0, 0 );
		#endif
	}

	call( this, fn_resize );
}

fn _window_tick_once( window const this )
{
	window_get_mouse_position( this, ref_of( this->mouse_x ), ref_of( this->mouse_y ) );

	call( this, fn_tick );

	if( this->inputs_pressed->count > 0 )
	{
		iter_list( this->inputs_pressed, input_index )
		{
			temp byte ref const input_ref = ref_of( list_get_iter( input_index, byte ) );
			this->inputs[ val_of( input_ref ) ] = INPUT_MASK_HELD;
			val_of( input_ref ) = 0;
		}
		list_clear( this->inputs_pressed );
	}

	if( this->inputs_released->count > 0 )
	{
		iter_list( this->inputs_released, input_index )
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
	iter_list( this->canvases, wc_index )
	{
		temp window_canvas const this_wc = list_get_iter( wc_index, window_canvas );
		call( this_wc, fn_draw );
	}
}

fn _window_present( window const this )
{
	this->using_buffer = this->using_buffer or( this->canvases->count > 1 ) or this->clear_before_present;

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
	#elif OS_WINDOWS
		temp HDC const target_dc = pick( this->using_buffer, this->buffer_dc, this->window_dc );
	#endif

	if( this->clear_before_present )
	{
		#if OS_LINUX
				XRenderFillRectangle( windows_display, PictOpSrc, window_picture, ref_of( black ), 0, 0, this->size.w, this->size.h );
		#elif OS_WINDOWS
			PatBlt( target_dc, 0, 0, this->size.w, this->size.h, BLACKNESS );
		#endif
	}

	iter_list( this->canvases, wc_index )
	{
		temp window_canvas const this_wc = list_get_iter( wc_index, window_canvas );

		temp i4 const pos_x = this_wc->pos.x;
		temp i4 const pos_y = this_wc->pos.y;
		temp r4 const scale_w = this_wc->scale.w;
		temp r4 const scale_h = this_wc->scale.h;
		temp i4 const canvas_w = this_wc->canvas->size.w;
		temp i4 const canvas_h = this_wc->canvas->size.h;

		temp i4 const scaled_w = i4( r4_round( r4( canvas_w ) * scale_w ) );
		temp i4 const scaled_h = i4( r4_round( r4( canvas_h ) * scale_h ) );
		skip_if( scaled_w is 0 or scaled_h is 0 );

		#if OS_LINUX
			this->image->data = to( byte ref, this_wc->canvas->pixels );
			this->image->width = canvas_w;
			this->image->height = canvas_h;
			this->image->bytes_per_line = canvas_w << pixel_shift;
		#elif OS_WINDOWS
			this->image.bmiHeader.biWidth = canvas_w;
			this->image.bmiHeader.biHeight = -canvas_h;
		#endif

		if( scale_w is 1.0 and scale_h is 1.0 )
		{
			#if OS_LINUX
				XPutImage( windows_display, pick( this->using_buffer, this->buffer, this->handle ), gc, this->image, 0, 0, pos_x, pos_y, canvas_w, canvas_h );
			#elif OS_WINDOWS
				SetDIBitsToDevice( target_dc, pos_x, pos_y, canvas_w, canvas_h, 0, 0, 0, canvas_h, this_wc->canvas->pixels, ref_of( this->image ), DIB_RGB_COLORS );
			#endif
		}
		else
		{
			temp i4 const clip_x = i4_max( 0, pos_x );
			temp i4 const clip_y = i4_max( 0, pos_y );
			temp i4 const clip_r = i4_min( this->size.w, pos_x + scaled_w );
			temp i4 const clip_b = i4_min( this->size.h, pos_y + scaled_h );
			skip_if( clip_r <= clip_x or clip_b <= clip_y );

			#if OS_LINUX
				XPutImage( windows_display, this_wc->pixmap, gc, this->image, 0, 0, 0, 0, canvas_w, canvas_h );

				transform.matrix[ 0 ][ 0 ] = XDoubleToFixed( 1.0 / r8( scale_w ) );
				transform.matrix[ 1 ][ 1 ] = XDoubleToFixed( 1.0 / r8( scale_h ) );
				XRenderSetPictureTransform( windows_display, this_wc->picture, ref_of( transform ) );

				XRenderComposite( windows_display, PictOpSrc, this_wc->picture, None, pick( this->using_buffer, this->buffer_picture, window_picture ), clip_x - pos_x, clip_y - pos_y, 0, 0, clip_x, clip_y, clip_r - clip_x, clip_b - clip_y );
			#elif OS_WINDOWS
				temp i4 const src_x = i4( r4_floor( r4( clip_x - pos_x ) / scale_w ) );
				temp i4 const src_y = i4( r4_floor( r4( clip_y - pos_y ) / scale_h ) );
				temp i4 const src_w = i4( r4_ceil( r4( clip_r - pos_x ) / scale_w ) ) - src_x;
				temp i4 const src_h = i4( r4_ceil( r4( clip_b - pos_y ) / scale_h ) ) - src_y;

				if( scale_w < 1.0 or scale_h < 1.0 )
				{
					SetStretchBltMode( target_dc, HALFTONE );
					SetBrushOrgEx( target_dc, 0, 0, nothing );
				}
				else
				{
					SetStretchBltMode( target_dc, COLORONCOLOR );
				}
				StretchDIBits( target_dc, pos_x + i4( r4( src_x ) * scale_w ), pos_y + i4( r4( src_y ) * scale_h ), i4( r4( src_w ) * scale_w ), i4( r4( src_h ) * scale_h ), src_x, canvas_h - src_y - src_h, src_w, src_h, this_wc->canvas->pixels, ref_of( this->image ), DIB_RGB_COLORS, SRCCOPY );
			#endif
		}
	}

	if( this->using_buffer )
	{
		#if OS_LINUX
			XPresentPixmap( windows_display, this->handle, this->buffer, 0, 0, 0, 0, 0, 0, 0, 0, PresentOptionAsync, 0, 0, 0, 0, 0 );
		#elif OS_WINDOWS
			BitBlt( this->window_dc, 0, 0, this->size.w, this->size.h, this->buffer_dc, 0, 0, SRCCOPY );
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

				call( this, fn_tick );
				_window_draw( this );
				skip;
			}

			when( WM_ERASEBKGND )
			{
				skip_if( this->clear_before_present is yes );
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
			_window_set_size( this, PICK( OS_LINUX, e->xconfigure.width, LOWORD( lp ) ), PICK( OS_LINUX, e->xconfigure.height, HIWORD( lp ) ) );
			_window_resize( this );
			_window_draw( this );
		} // fall through

		when( window_event_draw )
		{
			#if OS_LINUX
				skip_if( e->xexpose.count isnt 0 );
			#endif

			_window_present( this );
			skip;
		}

		//

		when( window_event_mouse_move )
		{
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

	out_window->canvases = new_list( window_canvas );

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
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = to( type_of( wc.lpfnWndProc ), window_process_event );
		wc.hInstance = GetModuleHandle( nothing );
		wc.lpszClassName = out_window->name->bytes;
		wc.hbrBackground = to( type_of( wc.hbrBackground ), GetStockObject( BLACK_BRUSH ) );
		RegisterClass( ref_of( wc ) );

		RECT rect = { 0, 0, width, height };
		AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );

		out_window->handle = CreateWindow( out_window->name->bytes, out_window->name->bytes, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nothing, nothing, GetModuleHandle( nothing ), nothing );

		out_window->window_dc = GetDC( out_window->handle );

		out_window->image.bmiHeader.biSize = size_of( out_window->image.bmiHeader );
		out_window->image.bmiHeader.biPlanes = 1;
		out_window->image.bmiHeader.biBitCount = 32;
		out_window->image.bmiHeader.biCompression = BI_RGB;
		SetWindowLongPtr( out_window->handle, GWLP_USERDATA, to( LONG_PTR, out_window ) );
	#endif

	current_window = out_window;
	list_add( windows, current_window );
	out current_window;
}

delete_object_fn( window )
{
	delete_text( this->name );
	iter_list( this->canvases, canvas_id )
	{
		delete_window_canvas( list_get_iter( canvas_id, window_canvas ) );
	}
	delete_list( this->canvases );
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
	#endif
}

fn _C7H16_loop()
{
	windows_time_start = get_nano();
	windows_time_next_draw = windows_time_start;

	temp const nano frame_nano_tick = pick( windows_fps_tick > 0, nano_per_sec / windows_fps_tick, 0 );
	temp const nano frame_nano_draw = pick( windows_fps_draw > 0, nano_per_sec / windows_fps_draw, 0 );
	temp const flag event_driven = frame_nano_tick is 0 and frame_nano_draw is 0;

	loop
	{
		out_if( windows->count is 0 );

		// process
		iter_list( windows, window_id )
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
				iter_list( windows, window_id )
				{
					_window_tick_once( list_get_iter( window_id, window ) );
				}
			}

			// catch up (no input processing)
			while( windows_time_tick <= target_frames )
			{
				++windows_time_tick;
				iter_list( windows, window_id )
				{
					call( list_get_iter( window_id, window ), fn_tick );
				}
			}
		}

		// draw
		temp nano now = get_nano();
		if( frame_nano_draw > 0 and now >= windows_time_next_draw )
		{
			iter_list( windows, window_id )
			{
				temp window const this_window = list_get_iter( window_id, window );
				_window_draw( this_window );
				window_refresh( this_window );
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
			iter_list( windows, window_id )
			{
				if( list_get_iter( window_id, window )->tick < 3 )
				{
					all_ready = no;
					break;
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
					//MsgWaitForMultipleObjects( 0, nothing, FALSE, INFINITE, QS_ALLINPUT );
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
				#if OS_LINUX
					fd_set fds;
					FD_ZERO( ref_of( fds ) );
					temp i4 const fd = ConnectionNumber( windows_display );
					FD_SET( fd, ref_of( fds ) );
					temp nano const wait_ns = wake_time - now;
					struct timeval tv = { wait_ns / nano_per_sec, ( wait_ns % nano_per_sec ) / 1000 };
					select( fd + 1, ref_of( fds ), nothing, nothing, ref_of( tv ) );
				#elif OS_WINDOWS
					temp const n4 wait_ms = n4( ( wake_time - now ) / 1000000 );
					MsgWaitForMultipleObjects( 0, nothing, FALSE, wait_ms, QS_ALLINPUT );
				#endif
			}
		}
	}
}

fn _C7H16_close()
{
	iter_list( windows, window_index )
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
