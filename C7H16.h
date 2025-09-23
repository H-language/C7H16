/////// /////// /////// /////// /////// /////// ///////
//
//  C7H16 - v0.1 - @ENDESGA - 2025 - Made in NZ - CC0 - foss forever
//
/////// /////// /////// /////// /////// /////// ///////

#pragma once

///////

#define C7H16

#include "../H/H.h"

//

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

//

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

#define pixel_bits 2

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

//

#define index_2d( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

type( canvas )
{
	pixel ref pixels;
	n2x2 size;
};

global canvas ref current_canvas_ref = nothing;

#define _canvas( W, H ) make( canvas, .pixels = to( pixel ref, new_ref( pixel, ( W ) * ( H ) ) ), .size = make( n2x2, ( W ), ( H ) ) )
#define _eval_canvas( WIDTH_HEIGHT... ) _canvas( WIDTH_HEIGHT )
#define canvas( WIDTH_HEIGHT... ) _eval_canvas( DEFAULTS( ( 1, 1 ), WIDTH_HEIGHT ) )

#define canvas_resize( CANVAS, WIDTH, HEIGHT )\
	START_DEF\
	{\
		temp const n2 _WIDTH = n2( WIDTH );\
		temp const n2 _HEIGHT = n2( HEIGHT );\
		skip_if( CANVAS.size.w is _WIDTH and CANVAS.size.h is _HEIGHT );\
		CANVAS.pixels = ref_resize( CANVAS.pixels, ( CANVAS.size.w * CANVAS.size.h ) << pixel_bits, ( _WIDTH * _HEIGHT ) << pixel_bits );\
		CANVAS.size.w = _WIDTH;\
		CANVAS.size.h = _HEIGHT;\
	}\
	END_DEF

#define canvas_fill( CANVAS, PIXEL )\
	START_DEF\
	{\
		temp const pixel _PIXEL = PIXEL;\
		if_all( _PIXEL.r is _PIXEL.g, _PIXEL.g is _PIXEL.b, _PIXEL.b is _PIXEL.a )\
		{\
			bytes_fill( CANVAS.pixels, _PIXEL.r, i4( CANVAS.size.w ) * i4( CANVAS.size.h ) << pixel_bits );\
		}\
		else\
		{\
			iter( _p, i4( CANVAS.size.w ) * i4( CANVAS.size.h ) )\
			{\
				CANVAS.pixels[ _p ] = _PIXEL;\
			}\
		}\
	}\
	END_DEF

#define canvas_clear( CANVAS ) if_something( CANVAS.pixels ) bytes_clear( CANVAS.pixels, i4( CANVAS.size.w ) * i4( CANVAS.size.h ) << pixel_bits )

//

#define canvas_pixel_safe( CANVAS, X, Y ) ( point_in_size( X, Y, CANVAS.size.w, CANVAS.size.h ) )
#define _canvas_get_pixel_index( CANVAS, INDEX ) CANVAS.pixels[ ( INDEX ) ]

#define canvas_get_pixel_row( CANVAS, X, ROW ) _canvas_get_pixel_index( CANVAS, i4( X ) + ( ROW ) )
#define canvas_get_pixel( CANVAS, X, Y ) canvas_get_pixel_row( CANVAS, X, i4( Y ) * i4( CANVAS.size.w ) )
#define canvas_get_pixel_safe( CANVAS, X, Y ) pick( canvas_pixel_safe( CANVAS, X, Y ), canvas_get_pixel( CANVAS, X, Y ), pixel( 0, 0, 0, 0 ) )

//

#define _canvas_draw_pixel_index( CANVAS, INDEX, PIXEL ) ( _canvas_get_pixel_index( CANVAS, INDEX ) ) = ( PIXEL )

#define canvas_draw_pixel_row( CANVAS, X, ROW, PIXEL ) ( canvas_get_pixel_row( CANVAS, X, ROW ) ) = ( PIXEL )
#define canvas_draw_pixel( CANVAS, X, Y, PIXEL ) ( canvas_get_pixel( CANVAS, X, Y ) ) = ( PIXEL )
#define canvas_draw_pixel_safe( CANVAS, X, Y, PIXEL ) if( canvas_pixel_safe( CANVAS, X, Y ) ) canvas_get_pixel( CANVAS, X, Y ) = ( PIXEL )

#define canvas_draw_pixel_mix( CANVAS, X, Y, PIXEL )\
	START_DEF\
	{\
		temp const pixel _p = canvas_get_pixel( CANVAS, X, Y );\
		canvas_get_pixel( CANVAS, X, Y ).argb = ( ( _p.argb & 0xfefefefe ) >> 1 ) + ( ( ( PIXEL.argb ) & 0xfefefefe ) >> 1 );\
	}\
	END_DEF

#define canvas_draw_pixel_mix_safe( CANVAS, X, Y, PIXEL )\
	START_DEF\
	{\
		skip_if( not canvas_pixel_safe( CANVAS, X, Y ) );\
		temp const pixel _p = canvas_get_pixel( CANVAS, X, Y );\
		canvas_get_pixel( CANVAS, X, Y ).argb = ( ( _p.argb & 0xfefefefe ) >> 1 ) + ( ( ( PIXEL.argb ) & 0xfefefefe ) >> 1 );\
	}\
	END_DEF

#define canvas_draw_pixel_multiply( CANVAS, X, Y, PIXEL )\
	START_DEF\
	{\
		temp pixel const_ref _p = ref_of( canvas_get_pixel( CANVAS, X, Y ) );\
		_p->r = ( n2( _p->r ) * n2( PIXEL.r ) ) >> 8;\
		_p->g = ( n2( _p->g ) * n2( PIXEL.g ) ) >> 8;\
		_p->b = ( n2( _p->b ) * n2( PIXEL.b ) ) >> 8;\
	}\
	END_DEF

///////

#define canvas_draw_canvas( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp const n2 _W = FROM_CANVAS.size.w << pixel_bits;\
		iter( _Y, FROM_CANVAS.size.h )\
		{\
			bytes_copy( ref_of( canvas_get_pixel( FROM_CANVAS, 0, _Y ) ), _W, ref_of( canvas_get_pixel( TO_CANVAS, TLx, TLy + _Y ) ) );\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_safe( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		temp const i2 _X = MAX( 0, TLx );\
		temp const i2 _OFFX = _X - TLx;\
		temp i2 _W = i2_min( TO_CANVAS.size.w - _X, FROM_CANVAS.size.w - _OFFX );\
		skip_if( _W < 0 );\
		_W <<= pixel_bits;\
		range( _Y, MAX( 0, TLy ), i2_min( TO_CANVAS.size.h - 1, TLy + FROM_CANVAS.size.h - 1 ) )\
		{\
			bytes_copy( ref_of( canvas_get_pixel( FROM_CANVAS, _OFFX, _Y - TLy ) ), _W, ref_of( canvas_get_pixel( TO_CANVAS, _X, _Y ) ) );\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_mix( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		iter( _Y, FROM_CANVAS.size.h )\
		{\
			iter( _X, FROM_CANVAS.size.w )\
			{\
				temp const pixel _PIXEL = canvas_get_pixel( FROM_CANVAS, _X, _Y );\
				canvas_draw_pixel_mix( TO_CANVAS, TLx + _X, TLy + _Y, _PIXEL );\
			}\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_multiply( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		iter( _Y, FROM_CANVAS.size.h )\
		{\
			iter( _X, FROM_CANVAS.size.w )\
			{\
				temp const pixel _PIXEL = canvas_get_pixel( FROM_CANVAS, _X, _Y );\
				canvas_draw_pixel_multiply( TO_CANVAS, TLx + _X, TLy + _Y, _PIXEL );\
			}\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_trans( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		iter( _Y, FROM_CANVAS.size.h )\
		{\
			iter( _X, FROM_CANVAS.size.w )\
			{\
				temp const pixel _PIXEL = canvas_get_pixel( FROM_CANVAS, _X, _Y );\
				if( _PIXEL.a isnt 0 )\
				{\
					canvas_get_pixel( TO_CANVAS, TLx + _X, TLy + _Y ) = _PIXEL;\
				}\
			}\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_trans_mix( TO_CANVAS, FROM_CANVAS, TLx, TLy )\
	START_DEF\
	{\
		iter( _Y, FROM_CANVAS.size.h )\
		{\
			iter( _X, FROM_CANVAS.size.w )\
			{\
				temp const pixel _PIXEL = canvas_get_pixel( FROM_CANVAS, _X, _Y );\
				if( _PIXEL.a isnt 0 )\
				{\
					canvas_draw_pixel_mix( TO_CANVAS, TLx + _X, TLy + _Y, _PIXEL );\
				}\
			}\
		}\
	}\
	END_DEF

//
#define canvas_draw_canvas_part( TO_CANVAS, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		temp const i2 _tlx = TLx;\
		temp const i2 _tly = TLy;\
		temp const i2 _part_tlx = PART_TLx;\
		temp const i2 _part_tly = PART_TLy;\
		temp const i2 _part_sizew = PART_SIZEw;\
		temp const i2 _part_sizeh = PART_SIZEh;\
		temp const n2 _W = _part_sizew << pixel_bits;\
		iter( _Y, _part_sizeh )\
		{\
			bytes_copy( ref_of( canvas_get_pixel( FROM_CANVAS, _part_tlx, _part_tly + _Y ) ), _W, ref_of( canvas_get_pixel( TO_CANVAS, _tlx, _tly + _Y ) ) );\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_part_safe( TO_CANVAS, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		const i2 _TLx = TLx;\
		temp i2 _X = MAX( 0, _TLx );\
		const i2 _PART_TLx = PART_TLx;\
		skip_if( _PART_TLx + ( _X - _TLx ) >= FROM_CANVAS.size.w );\
		const i2 _TLy = TLy;\
		temp i2 _SY = ( PART_TLy ) + ( MAX( 0, _TLy ) - _TLy );\
		skip_if( _SY >= FROM_CANVAS.size.h );\
		temp i2 _W = i2_min3( TO_CANVAS.size.w - _X, ( PART_SIZEw ) - ( _X - _TLx ), FROM_CANVAS.size.w - ( _PART_TLx + ( _X - _TLx ) ) );\
		skip_if( _W <= 0 );\
		_W <<= pixel_bits;\
		iter( _Y, i2_min( TO_CANVAS.size.h, _TLy + ( PART_SIZEh ) ) - MAX( 0, _TLy ) )\
		{\
			bytes_copy( ref_of( canvas_get_pixel( FROM_CANVAS, _PART_TLx + ( _X - _TLx ), _SY + _Y ) ), _W, ref_of( canvas_get_pixel( TO_CANVAS, _X, MAX( 0, _TLy ) + _Y ) ) );\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_part_trans( TO_CANVAS, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		iter( _Y, PART_SIZEh )\
		{\
			iter( _X, PART_SIZEw )\
			{\
				temp const pixel _PIXEL = canvas_get_pixel( FROM_CANVAS, ( PART_TLx ) + _X, ( PART_TLy ) + _Y );\
				if( _PIXEL.a isnt 0 )\
				{\
					canvas_get_pixel( TO_CANVAS, ( TLx ) + _X, ( TLy ) + _Y ) = _PIXEL;\
				}\
			}\
		}\
	}\
	END_DEF

#define canvas_draw_canvas_part_trans_safe( TO_CANVAS, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		const i2 _TLx = TLx;\
		temp i2 _X = MAX( 0, _TLx );\
		const i2 _PART_TLx = PART_TLx;\
		skip_if( _PART_TLx + ( _X - _TLx ) >= FROM_CANVAS.size.w );\
		const i2 _TLy = TLy;\
		temp i2 _SY = ( PART_TLy ) + ( MAX( 0, _TLy ) - _TLy );\
		skip_if( _SY >= FROM_CANVAS.size.h );\
		temp i2 _W = i2_min3( TO_CANVAS.size.w - _X, ( PART_SIZEw ) - ( _X - _TLx ), FROM_CANVAS.size.w - ( _PART_TLx + ( _X - _TLx ) ) );\
		skip_if( _W <= 0 );\
		temp const i2 _H = i2_min( TO_CANVAS.size.h, _TLy + ( PART_SIZEh ) ) - MAX( 0, _TLy );\
		iter( _Y, _H )\
		{\
			iter( _IX, _W )\
			{\
				temp const pixel _PIXEL = canvas_get_pixel( FROM_CANVAS, _PART_TLx + ( _X - _TLx ) + _IX, _SY + _Y );\
				if( _PIXEL.a isnt 0 )\
				{\
					canvas_get_pixel( TO_CANVAS, _X + _IX, MAX( 0, _TLy ) + _Y ) = _PIXEL;\
				}\
			}\
		}\
	}\
	END_DEF

///////

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

#define canvas_draw_line_mix( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _mix )
#define canvas_draw_line_mix_safe( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _mix_safe )

//

#define _wrap_coord( COORD, SIZE ) ( ( ( COORD ) + ( SIZE ) ) mod ( SIZE ) )
#define canvas_draw_pixel_wrap( CANVAS, X, Y, PIXEL ) canvas_draw_pixel( CANVAS, _wrap_coord( i4( X ), i4( CANVAS.size.w ) ), _wrap_coord( i4( Y ), i4( CANVAS.size.h ) ), PIXEL )
#define canvas_draw_line_wrap( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _wrap )

//

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
#define canvas_draw_box_mix( CANVAS, TLx, TLy, BRx, BRy, PIXEL ) _canvas_draw_box( CANVAS, TLx, TLy, BRx, BRy, PIXEL, _mix )
#define canvas_draw_box_mix_safe( CANVAS, TLx, TLy, BRx, BRy, PIXEL ) _canvas_draw_box( CANVAS, TLx, TLy, BRx, BRy, PIXEL, _mix_safe )

///////

type( font )
{
	canvas pixels;
	n2x2 letter_size;
};

#define font( CANVAS ) make( font, .pixels = CANVAS, .letter_size.w = CANVAS.size.w >> 4, .letter_size.h = CANVAS.size.h >> 4 )

#define canvas_draw_bytes( CANVAS, FONT, BYTES, BYTES_SIZE, POS, ANCHOR, COLOR, BOLD_SHADOW... )\
	START_DEF\
	{\
		temp const n2 _text_len = pick( BYTES_SIZE is 0, bytes_measure( BYTES ), BYTES_SIZE );\
		temp const i2 _text_width = _text_len * FONT.letter_size.x;\
		temp const i2 _text_height = FONT.letter_size.y;\
		temp i2 _offset_x;\
		temp i2 _offset_y;\
		get_anchor_offsets( _offset_x, _offset_y, _text_width, _text_height, ANCHOR );\
		temp i2 _draw_x = POS.x - _offset_x;\
		temp i2 _draw_y = POS.y - _offset_y;\
		temp i2 _letter_x = 0;\
		temp i2 _letter_y = 0;\
		temp byte _letter = 0;\
		temp const flag _is_bold = DEFAULT( no, GET_ARG1( BOLD_SHADOW ) );\
		temp const flag _is_shadow = DEFAULT( no, SKIP_ARG( BOLD_SHADOW ) );\
		temp i2 _w = 0;\
		temp const pixel _color = COLOR;\
		iter( _l, _text_len )\
		{\
			_letter = BYTES[ _l ];\
			_letter_x = ( _letter & 0x0F ) * FONT.letter_size.x;\
			_letter_y = ( _letter >> 4 ) * FONT.letter_size.y;\
			iter( _Y, FONT.letter_size.h )\
			{\
				iter( _X, FONT.letter_size.w )\
				{\
					if( canvas_get_pixel( FONT.pixels, _letter_x + _X, _letter_y + _Y ).a isnt 0 )\
					{\
						canvas_get_pixel( CANVAS, _draw_x + _w + _X, _draw_y + _Y ) = _color;\
						if( _is_bold ) canvas_get_pixel( CANVAS, _draw_x + _w + _X + 1, _draw_y + _Y ) = _color;\
						if( _is_shadow )\
						{\
							temp const i2 _shX = _draw_x + _w + _X + _is_bold;\
							temp const i2 _shY = _draw_y + _Y;\
							canvas_get_pixel( CANVAS, _shX + 1, _shY ) = pixel_black;\
							canvas_get_pixel( CANVAS, _shX + 1, _shY + 1 ) = pixel_black;\
							canvas_get_pixel( CANVAS, _shX, _shY + 1 ) = pixel_black;\
						}\
					}\
				}\
			}\
			_w += FONT.letter_size.x;\
		}\
	}\
	END_DEF

///////

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

///////

type_from( PICK( OS_LINUX, Window, HWND ) ) os_handle;
type_from( PICK( OS_LINUX, Display ref, HDC ) ) os_display;
type_from( PICK( OS_LINUX, XImage ref, BITMAPINFO ) ) os_image;
type_from( PICK( OS_LINUX, XEvent, MSG ) ) os_event;

#if OS_LINUX
	#define INPUTS_MAX 512
#else
	#define INPUTS_MAX 256
#endif

object( window )
{
	os_handle handle;
	os_display display;
	os_image image;
	//
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
	//
	canvas buffer;
	n2x2 size_target;
	n2x2 buffer_max;
	n2 scale;
	anchor buffer_anchor;
	//
	flag visible;
	flag refresh;
	flag close;
	//
	window_fn start_fn;
	window_fn tick_fn;
	window_fn resize_fn;
	window_fn draw_fn;
	window_fn input_fn;
	//
	n8 tick;
	nano start_nano;
	nano past_nano;
	nano target_frame_nano;
	//
	r8 fps_target;
	r8 total_time;
	r8 delta_time;
	//
	byte inputs[ INPUTS_MAX ];
	byte inputs_pressed[ 32 ];
	n1 inputs_pressed_count;
	byte inputs_released[ 32 ];
	n1 inputs_released_count;
	//
	i4 mouse_x;
	i4 mouse_y;
	i2 mouse_delta_x;
	i2 mouse_delta_y;
	d4 mouse_pixel_x;
	d4 mouse_pixel_y;
};

global window current_window = nothing;

global window alive_windows[ 32 ];
global n1 alive_windows_count = 0;

global const byte ref OS_INPUT_MAP = nothing;

#define INPUT_MASK_PRESSED 0x1
#define INPUT_MASK_HELD 0x2
#define INPUT_MASK_RELEASED 0x4

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
			//
		}
	#elif OS_WINDOWS
		ReleaseCapture();

		MSG msg;
		while( PeekMessage( ref_of( msg ), this->handle, 0, 0, PM_REMOVE ) )
		{
			//
		}
	#endif
}

object_fn( window, set_scale, const r8 scale )
{
	out_if_nothing( this );

	this->scale = n2_max( r8_ceil(scale), 1 );

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

	//
	#if OS_LINUX
		this->image->data = to( byte ref, this->buffer.pixels );
		this->image->width = this->buffer.size.w;
		this->image->height = this->buffer.size.h;
		this->image->bytes_per_line = this->buffer.size.w << pixel_bits;

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
	//
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

	//

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

	//

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

//

group( input_type )
{
	input_none,
	//
	input_mouse_left,
	input_mouse_right,
	input_cancel,
	input_mouse_middle,
	//
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
	//
	input_count
};

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
	//
	jump_if_nothing( this ) exit_events;
	//
	temp flag is_input = no;
	//
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
			//
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
			//
			is_input = yes;
			skip;
		}

		when( window_event_close )
		{
			#if OS_WINDOWS
				PostQuitMessage( 0 );
			#endif

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
	//
	if( is_input is yes )
	{
		call( this, input_fn );
	}
	//
	exit_events:
	#if OS_WINDOWS
		out DefWindowProc( h, event, wp, lp );
	#elif OS_LINUX
		out success;
	#endif
}

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
	//
	window_set_fps( out_window, 60 );
	current_window = out_window;
	alive_windows[ alive_windows_count++ ] = current_window;
	//
	out current_window;
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
	#if OS_LINUX
		XClearArea( this->display, this->handle, 0, 0, 0, 0, yes );
		XSync( this->display, no );
	#elif OS_WINDOWS
		InvalidateRect( this->handle, nothing, no );
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

///////

embed const byte const_ref _C7H16_input_map()
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

///////

group( audio_channel )
{
	audio_channel_mono = 1,
	audio_channel_stereo = 2
};

type( audio )
{
	r4 ref data;
	n8 data_size;
	n4 rate;
	audio_channel channel;
};

embed audio load_wav( const byte const_ref wav_path )
{
	temp audio out_audio = { 0 };
	file f = map_file( wav_path );
	out_if_nothing( f.mapped_bytes ) out_audio;
	//
	temp const n2 const_ref fmt = to( n2 ref, f.mapped_bytes + 20 );
	temp const n2 audio_format = fmt[ 0 ];
	temp const n2 channels = fmt[ 1 ];
	temp const n4 sample_rate = val_of( to( n4 ref, f.mapped_bytes + 24 ) );
	temp const n2 bits = val_of( to( n2 ref, f.mapped_bytes + 34 ) );

	temp const byte ref r = f.mapped_bytes + 36;
	temp n4 data_size = 0;
	while( r < f.mapped_bytes + f.size )
	{
		if( bytes_compare( r, "data", 4 ) is 0 )
		{
			data_size = val_of( to( n4 ref, r + 4 ) );
			r += 8;
			skip;
		}
		r += 8 + val_of( to( n4 ref, r + 4 ) );
	}

	out_if( data_size is 0 ) out_audio;

	temp const n4 samples = data_size / ( bits >> 3 );
	out_audio.rate = samples / channels;
	out_audio.channel = to( audio_channel, channels );
	out_audio.data_size = samples << 2;
	out_audio.data = new_bytes( out_audio.data_size );

	if( bits is 16 )
	{
		temp const i2 const_ref src = to( i2 const_ref, r );
		iter( s, samples )
		{
			out_audio.data[ s ] = r4( src[ s ] ) / 32768.0;
		}
	}
	else
	{ // 8 bits
		temp const n1 const_ref src = to( n1 const_ref, r );
		iter( s, samples )
		{
			out_audio.data[ s ] = ( r4( src[ s ] ) - 128.0 ) / 128.0;
		}
	}

	file_unmap( ref_of( f ) );

	out out_audio;
}

type( _audio_raw )
{
	i2 ref data;
	n4 rate;
	n8 samples;
	audio_channel channel;
};

embed _audio_raw load_wav_raw( const byte const_ref wav_path )
{
	temp _audio_raw out_audio = { 0 };
	file f = map_file( wav_path );
	out_if_nothing( f.mapped_bytes ) out_audio;

	temp const n2 const_ref fmt = to( n2 ref, f.mapped_bytes + 20 );
	temp const n2 audio_format = fmt[ 0 ];
	temp const n2 channels = fmt[ 1 ];
	temp const n4 sample_rate = val_of( to( n4 ref, f.mapped_bytes + 24 ) );
	temp const n2 bits = val_of( to( n2 ref, f.mapped_bytes + 34 ) );

	out_if( bits isnt 16 ) out_audio;

	temp byte ref r = f.mapped_bytes + 36;
	temp n4 data_size = 0;
	while( r < f.mapped_bytes + f.size )
	{
		if( bytes_compare( r, "data", 4 ) is 0 )
		{
			data_size = val_of( to( n4 ref, r + 4 ) );
			r += 8;
			skip;
		}
		r += 8 + val_of( to( n4 ref, r + 4 ) );
	}

	out_if( data_size is 0 ) out_audio;

	temp const n8 samples = data_size / 2;

	out_audio.rate = samples / channels;
	out_audio.channel = to( audio_channel, channels );
	out_audio.samples = samples;

	out_audio.data = to( i2 ref, new_bytes( samples * size_of( i2 ) ) );

	temp const i2 const_ref src = to( i2 const_ref, r );
	iter( s, samples )
	{
		out_audio.data[ s ] = src[ s ];
	}

	file_unmap( ref_of( f ) );

	out out_audio;
}

fn delete_audio( audio ref a )
{
	delete_ref( a->data );
}

type( audio_instance )
{
	audio ref audio_ref;
	flag playing;
	n4 position;
	r4 volume;
	r4 pan;
};

#ifndef audio_max_instances
	#define audio_max_instances 32
#endif

#if OS_WINDOWS
	#if COMPILER_TCC
		type( WAVEFORMATEX )
		{
			WORD wFormatTag,
			nChannels;
			DWORD nSamplesPerSec,
			nAvgBytesPerSec;
			WORD nBlockAlign,
			wBitsPerSample;
		};

		type( WAVEHDR )
		{
			LPSTR lpData;
			DWORD dwBufferLength,
			dwBytesRecorded;
			DWORD_PTR dwUser;
			DWORD dwFlags,
			dwLoops;
			anon ref lpNext;
			DWORD_PTR reserved;
		};

		type_from( anon ref ) HWAVEOUT;
	#else
		#include <mmsystem.h>
	#endif
	//
	perm UINT( WINAPI ref waveOpen ) ( HWAVEOUT ref, n4, WAVEFORMATEX ref, DWORD_PTR, DWORD_PTR, DWORD );
	perm UINT( WINAPI ref waveClose ) ( HWAVEOUT );
	perm UINT( WINAPI ref waveWrite ) ( HWAVEOUT, WAVEHDR ref, n4 );
	perm UINT( WINAPI ref wavePrepare ) ( HWAVEOUT, WAVEHDR ref, n4 );
	perm UINT( WINAPI ref waveUnprepare ) ( HWAVEOUT, WAVEHDR ref, n4 );
	perm HMODULE winmm_dll = nothing;
#endif

type( audio_mixer )
{
	audio_instance instances[ audio_max_instances ];
	anon ref device;
	thread_lock lock;
	flag running;
	//
	#if OS_LINUX
		thread process;
	#elif OS_WINDOWS
		WAVEHDR hdr[ 2 ];
	#endif
};

fn audio_mixer_process( audio_mixer ref m, i2 ref output, n4 samples )
{
	perm r4 buffer[ 8192 ];
	perm n2 last_used = 0;

	temp const n4 samples2 = samples << 1;

	if( last_used isnt samples2 )
	{
		bytes_clear( buffer, pick( last_used > samples2, last_used, samples2 ) * size_of( r4 ) );
		last_used = samples2;
	}
	else
	{
		bytes_clear( buffer, samples2 * size_of( r4 ) );
	}

	iter( instance_id, audio_max_instances )
	{
		temp audio_instance const_ref i = ref_of( m->instances[ instance_id ] );
		next_if( i->playing is no );
		temp const i4 rate = pick( samples < ( i->audio_ref->rate - i->position ), samples, i->audio_ref->rate - i->position );
		temp const r4 left_gain = i->volume * ( 1.0 - i->pan ) / 2.0;
		temp const r4 right_gain = i->volume * ( 1.0 + i->pan ) / 2.0;

		iter( f, rate )
		{
			temp const r4 const_ref p = ref_of( i->audio_ref->data[ ( i->position + f ) * n4( i->audio_ref->channel ) ] );
			buffer[ f << 1 ] += p[ 0 ] * left_gain;
			buffer[ ( f << 1 ) + 1 ] += p[ i->audio_ref->channel - 1 ] * right_gain;
		}
		if( ( i->position += rate ) >= i->audio_ref->rate ) i->playing = no;
	}

	iter( sample, samples2 )
	{
		temp const r4 s = buffer[ sample ];
		output[ sample ] = pick( s > 1, max_i2, pick( s < -1, -max_i2, s * max_i2 ) );
	}
}

#if OS_LINUX
	fn audio_mixer_thread_fn( anon ref p )
#elif OS_WINDOWS
	fn CALLBACK audio_mixer_thread_fn( HWAVEOUT h, UINT msg, DWORD_PTR i, DWORD_PTR p1, DWORD_PTR p2 )
#endif
{
	#if OS_LINUX
		audio_mixer ref m = to( audio_mixer ref, p );
		i2 buffer[ 4096 ];

		while( m->running )
		{
			lock_thread( m->lock );
			audio_mixer_process( m, buffer, 2048 );
			unlock_thread( m->lock );
			snd_pcm_writei( m->device, buffer, 2048 );
		}
	#elif OS_WINDOWS
		if( msg is 0x3BD )
		{
			audio_mixer ref m = to( audio_mixer ref, i );
			WAVEHDR ref hdr = to( WAVEHDR ref, p1 );

			if( m->running )
			{
				lock_thread( m->lock );
				audio_mixer_process( m, to( i2 ref, hdr->lpData ), 2048 );
				unlock_thread( m->lock );
				waveWrite( m->device, hdr, size_of( WAVEHDR ) );
			}
		}
	#endif

	out;
}

embed out_state audio_mixer_start( audio_mixer ref m )
{
	bytes_clear( m, size_of( audio_mixer ) );
	thread_add_lock( m->lock );
	m->running = yes;

	#if OS_LINUX
		if( snd_pcm_open( to( snd_pcm_t ref ref, ref_of( m->device ) ), "default", 0, 0 ) < 0 )
		{
			out failure;
		}
		snd_pcm_set_params( m->device, 2, 3, 2, 44100, 1, 100000 );
		m->process = start_thread( audio_mixer_thread_fn, m );

	#elif OS_WINDOWS
		if_nothing( winmm_dll )
		{
			winmm_dll = LoadLibrary( "winmm.dll" );
			if_nothing( winmm_dll ) out failure;
			//
			waveOpen = to( type_of( waveOpen ), GetProcAddress( winmm_dll, "waveOutOpen" ) );
			waveClose = to( type_of( waveClose ), GetProcAddress( winmm_dll, "waveOutClose" ) );
			waveWrite = to( type_of( waveWrite ), GetProcAddress( winmm_dll, "waveOutWrite" ) );
			wavePrepare = to( type_of( wavePrepare ), GetProcAddress( winmm_dll, "waveOutPrepareHeader" ) );
			waveUnprepare = to( type_of( waveUnprepare ), GetProcAddress( winmm_dll, "waveOutUnprepareHeader" ) );
		}

		WAVEFORMATEX fmt = { 1, 2, 44100, 176400, 4, 16 };
		if( waveOpen( to( HWAVEOUT ref, ref_of( m->device ) ), -1, ref_of( fmt ), to( DWORD_PTR, audio_mixer_thread_fn ), to( DWORD_PTR, m ), 0x00030000 ) )
		{
			out failure;
		}

		iter( i, 2 )
		{
			m->hdr[ i ].lpData = new_bytes( 8192 );
			m->hdr[ i ].dwBufferLength = 8192;
			wavePrepare( m->device, ref_of( m->hdr[ i ] ), size_of( WAVEHDR ) );

			lock_thread( m->lock );
			audio_mixer_process( m, to( i2 ref, m->hdr[ i ].lpData ), 2048 );
			unlock_thread( m->lock );

			waveWrite( m->device, ref_of( m->hdr[ i ] ), size_of( WAVEHDR ) );
		}
	#endif

	out success;
}

fn audio_mixer_stop( audio_mixer ref m )
{
	m->running = no;

	#if OS_LINUX
		wait_for_thread( m->process );
		snd_pcm_close( m->device );
	#elif OS_WINDOWS
		Sleep( 100 );
		waveClose( m->device );
		iter( i, 2 )
		{
			delete_ref( m->hdr[ i ].lpData );
			waveUnprepare( m->device, ref_of( m->hdr[ i ] ), size_of( WAVEHDR ) );
		}
	#endif

	thread_remove_lock( m->lock );
}

type_from( i4 ) audio_id;

embed audio_id audio_play( audio_mixer const_ref mixer, audio const_ref a, const r4 volume, const r4 pan )
{
	lock_thread( mixer->lock );
	iter( id, audio_max_instances )
	{
		next_if( mixer->instances[ id ].playing is yes );
		//
		mixer->instances[ id ] = make( audio_instance, .audio_ref = a, .position = 0, .playing = yes, .volume = volume, .pan = pan );
		unlock_thread( mixer->lock );
		out id;
	}
	//
	unlock_thread( mixer->lock );
	out -1;
}

fn audio_stop( audio_mixer const_ref mixer, audio_id id )
{
	if( id >= 0 and id < audio_max_instances )
	{
		mixer->instances[ id ].playing = no;
	}
}

fn audio_set( audio_mixer const_ref mixer, audio_id id, const r4 volume, const r4 pan )
{
	if_all( id >= 0, id < audio_max_instances, mixer->instances[ id ].playing is yes )
	{
		lock_thread( mixer->lock );
		mixer->instances[ id ].volume = volume;
		mixer->instances[ id ].pan = pan;
		unlock_thread( mixer->lock );
	}
}

///////

type( compressed_wave )
{
	byte ref data;
	n4 data_size;
	n4 orig_size;
	n4 header_size;
	n1 k_param;
};

embed compressed_wave wav_to_compressed_wave( const byte const_ref in_wav, n8 size )
{
	compressed_wave out_cw = make( compressed_wave, .orig_size = size );

	temp const byte ref r = in_wav + 36;
	temp n4 data_off = 36;
	temp n4 data_sz = 0;

	while( r < in_wav + size )
	{
		if( bytes_compare( r, "data", 4 ) is 0 )
		{
			data_sz = val_of( to( n4 ref, r + 4 ) );
			data_off = r + 8 - in_wav;
			skip;
		}
		r += 8 + val_of( to( n4 ref, r + 4 ) );
	}

	out_cw.header_size = data_off;
	temp n2 bits = val_of( to( n2 ref, in_wav + 34 ) );
	temp n2 ch = val_of( to( n2 ref, in_wav + 22 ) );
	temp n8 samples = data_sz / ( bits >> 3 );
	temp byte ref comp = new_bytes( data_off + data_sz );
	temp n8 pos = 0;
	temp n8 bit_pos = 0;

	bytes_copy( in_wav, data_off, comp );
	pos = data_off;

	temp n1 k = 4;
	temp n8 sum = 0;

	if( bits is 16 )
	{
		temp const i2 const_ref src = to( i2 const_ref, in_wav + data_off );
		temp i4 p1 = 0,
		p2 = 0;

		if( ch is 2 )
		{
			iter( s, samples >> 1 )
			{
				temp i4 l = src[ s << 1 ];
				temp i4 r = src[ ( s << 1 ) + 1 ];
				temp i4 mid = ( l + r ) >> 1;
				temp i4 side = l - r;

				temp i4 pred_m = ( p1 << 1 ) - p2;
				temp i4 res_m = mid - pred_m;
				p2 = p1;
				p1 = mid;

				sum += pick( res_m < 0, -res_m, res_m );

				temp n4 rice = pick( res_m < 0, ( -res_m << 1 ) - 1, res_m << 1 );
				temp n4 q = rice >> k;
				temp n4 r2 = rice & ( ( 1 << k ) - 1 );

				while( q-- > 0 )
				{
					comp[ pos + ( bit_pos >> 3 ) ] |= 1 << ( bit_pos & 7 );
					++bit_pos;
				}
				++bit_pos;

				temp n1 b = 0;
				while( b < k )
				{
					if( r2 & ( 1 << b ) ) comp[ pos + ( bit_pos >> 3 ) ] |= 1 << ( bit_pos & 7 );
					++bit_pos;
					++b;
				}

				comp[ pos + ( bit_pos >> 3 ) ] |= ( side & 0xFF ) << ( bit_pos & 7 );
				bit_pos += 8;
				comp[ pos + ( bit_pos >> 3 ) ] |= ( ( side >> 8 ) & 0xFF ) << ( bit_pos & 7 );
				bit_pos += 8;
			}
		}
		else
		{
			iter( s, samples )
			{
				temp i2 pred = ( p1 << 1 ) - p2;
				temp i2 res = src[ s ] - pred;
				p2 = p1;
				p1 = src[ s ];

				sum += pick( res < 0, -res, res );

				temp n4 rice = pick( res < 0, ( -res << 1 ) - 1, res << 1 );
				temp n4 q = rice >> k;
				temp n4 r2 = rice & ( ( 1 << k ) - 1 );

				while( q-- > 0 )
				{
					comp[ pos + ( bit_pos >> 3 ) ] |= 1 << ( bit_pos & 7 );
					++bit_pos;
				}
				++bit_pos;

				temp n1 b = 0;
				while( b < k )
				{
					if( r2 & ( 1 << b ) ) comp[ pos + ( bit_pos >> 3 ) ] |= 1 << ( bit_pos & 7 );
					++bit_pos;
					++b;
				}
			}
		}
	}
	else
	{
		temp const n1 const_ref src = to( n1 const_ref, in_wav + data_off );
		temp n1 p1 = 128,
		p2 = 128;

		iter( s, samples )
		{
			temp n1 pred = ( p1 << 1 ) - p2;
			temp i1 res = src[ s ] - pred;
			p2 = p1;
			p1 = src[ s ];

			sum += pick( res < 0, -res, res );

			temp n2 rice = pick( res < 0, ( -res << 1 ) - 1, res << 1 );
			temp n2 q = rice >> k;
			temp n2 r = rice & ( ( 1 << k ) - 1 );

			while( q-- > 0 )
			{
				comp[ pos + ( bit_pos >> 3 ) ] |= 1 << ( bit_pos & 7 );
				++bit_pos;
			}
			++bit_pos;

			temp n1 b = 0;
			while( b < k )
			{
				if( r & ( 1 << b ) ) comp[ pos + ( bit_pos >> 3 ) ] |= 1 << ( bit_pos & 7 );
				++bit_pos;
				++b;
			}
		}
	}

	while( sum > ( samples << ( k + 1 ) ) and k < 15 ) ++k;
	while( sum < ( samples << k ) and k > 0 ) --k;
	out_cw.k_param = k;

	pos += ( bit_pos + 7 ) >> 3;
	out_cw.data = bytes_resize( comp, pos );
	out_cw.data_size = pos;

	out out_cw;
}

embed byte ref compressed_wave_to_wav( const compressed_wave const_ref in_cw, n8 ref out_size )
{
	byte ref out_wav = new_bytes( in_cw->orig_size );
	val_of( out_size ) = in_cw->orig_size;

	bytes_copy( in_cw->data, in_cw->header_size, out_wav );

	temp n2 bits = val_of( to( n2 ref, out_wav + 34 ) );
	temp n2 ch = val_of( to( n2 ref, out_wav + 22 ) );
	temp n4 samples = ( in_cw->orig_size - in_cw->header_size ) / ( bits >> 3 );
	temp n8 pos = in_cw->header_size;
	temp n4 bit_pos = 0;
	temp n1 k = in_cw->k_param;

	if( bits is 16 )
	{
		temp i2 ref dst = to( i2 ref, out_wav + in_cw->header_size );
		temp i2 p1 = 0,
		p2 = 0;

		if( ch is 2 )
		{
			iter( s, samples >> 1 )
			{
				temp n4 rice = 0;
				temp n4 q = 0;

				while( in_cw->data[ pos + ( bit_pos >> 3 ) ] & ( 1 << ( bit_pos & 7 ) ) )
				{
					++q;
					++bit_pos;
				}
				++bit_pos;

				rice = q << k;
				temp n1 b = 0;
				while( b < k )
				{
					if( in_cw->data[ pos + ( bit_pos >> 3 ) ] & ( 1 << ( bit_pos & 7 ) ) ) rice |= 1 << b;
					++bit_pos;
					++b;
				}

				temp i2 res = pick( rice & 1, -( ( rice + 1 ) >> 1 ), rice >> 1 );
				temp i2 pred = ( p1 << 1 ) - p2;
				temp i2 mid = res + pred;
				p2 = p1;
				p1 = mid;

				temp i2 side = 0;
				side |= in_cw->data[ pos + ( bit_pos >> 3 ) ] >> ( bit_pos & 7 );
				side |= in_cw->data[ pos + ( ( bit_pos + 8 ) >> 3 ) ] << ( 8 - ( bit_pos & 7 ) );
				bit_pos += 16;

				dst[ s << 1 ] = mid + ( side >> 1 );
				dst[ ( s << 1 ) + 1 ] = mid - ( side >> 1 );
			}
		}
		else
		{
			iter( s, samples )
			{
				temp n4 rice = 0;
				temp n4 q = 0;

				while( in_cw->data[ pos + ( bit_pos >> 3 ) ] & ( 1 << ( bit_pos & 7 ) ) )
				{
					++q;
					++bit_pos;
				}
				++bit_pos;

				rice = q << k;
				temp n1 b = 0;
				while( b < k )
				{
					if( in_cw->data[ pos + ( bit_pos >> 3 ) ] & ( 1 << ( bit_pos & 7 ) ) ) rice |= 1 << b;
					++bit_pos;
					++b;
				}

				temp i2 res = pick( rice & 1, -( ( rice + 1 ) >> 1 ), rice >> 1 );
				temp i2 pred = ( p1 << 1 ) - p2;
				p2 = p1;
				p1 = res + pred;
				dst[ s ] = p1;
			}
		}
	}
	else
	{
		temp n1 ref dst = to( n1 ref, out_wav + in_cw->header_size );
		temp n1 p1 = 128,
		p2 = 128;

		iter( s, samples )
		{
			temp n2 rice = 0;
			temp n2 q = 0;

			while( in_cw->data[ pos + ( bit_pos >> 3 ) ] & ( 1 << ( bit_pos & 7 ) ) )
			{
				++q;
				++bit_pos;
			}
			++bit_pos;

			rice = q << k;
			temp n1 b = 0;
			while( b < k )
			{
				if( in_cw->data[ pos + ( bit_pos >> 3 ) ] & ( 1 << ( bit_pos & 7 ) ) ) rice |= 1 << b;
				++bit_pos;
				++b;
			}

			temp i1 res = pick( rice & 1, -( ( rice + 1 ) >> 1 ), rice >> 1 );
			temp n1 pred = ( p1 << 1 ) - p2;
			p2 = p1;
			p1 = res + pred;
			dst[ s ] = p1;
		}
	}

	out out_wav;
}

///////

embed canvas bmp_to_canvas( byte ref bmp_bytes, n4 bmp_bytes_size )
{
	temp canvas c = { 0 };
	out_if_nothing( bmp_bytes ) c;
	out_if( bmp_bytes_size < 54 ) c;

	temp const n2 type = val_of( to( n2 ref, bmp_bytes + 0 ) );
	temp const n4 file_size = val_of( to( n4 ref, bmp_bytes + 2 ) );
	temp const n4 data_offset = val_of( to( n4 ref, bmp_bytes + 10 ) );
	temp const n4 dib_header_size = val_of( to( n4 ref, bmp_bytes + 14 ) );
	temp const i4 width = val_of( to( i4 ref, bmp_bytes + 18 ) );
	temp const i4 height = val_of( to( i4 ref, bmp_bytes + 22 ) );
	temp const n2 planes = val_of( to( n2 ref, bmp_bytes + 26 ) );
	temp const n2 bit_count = val_of( to( n2 ref, bmp_bytes + 28 ) );
	temp const n4 compression = val_of( to( n4 ref, bmp_bytes + 30 ) );
	temp const n4 image_size_field = val_of( to( n4 ref, bmp_bytes + 34 ) );
	temp const n4 colors_used = val_of( to( n4 ref, bmp_bytes + 46 ) );

	out_if( type isnt 0x4d42 ) c;
	out_if( width <= 0 ) c;
	out_if( planes isnt 1 ) c;
	out_if( compression isnt 0 ) c;
	out_if( bit_count isnt 1 and bit_count isnt 4 and bit_count isnt 8 and bit_count isnt 24 and bit_count isnt 32 ) c;
	out_if( dib_header_size < 12 ) c;

	c.size.w = width;
	c.size.h = i4_abs( height );

	temp const i8 row_size = ( ( width * bit_count + 31 ) >> 5 ) << pixel_bits;
	temp const n8 calculated_image_size = row_size * c.size.h;

	out_if( data_offset > bmp_bytes_size ) c;
	out_if( data_offset + calculated_image_size > bmp_bytes_size ) c;

	c.pixels = new_ref( pixel, x2_area( c.size ) );
	temp const byte ref pixel_data = bmp_bytes + data_offset;

	pixel palette[ 256 ] = { 0 };
	if( bit_count <= 8 )
	{
		temp const n4 palette_size = pick( colors_used, colors_used, 1 << bit_count );
		if( palette_size > 256 )
		{
			delete_ref( c.pixels );
			out c;
		}

		temp const n4 palette_offset = 14 + dib_header_size;
		temp const n4 palette_bytes = palette_size << pixel_bits;
		if( palette_offset + palette_bytes > data_offset )
		{
			delete_ref( c.pixels );
			out c;
		}

		temp const byte ref palette_data = bmp_bytes + palette_offset;

		iter( i, palette_size )
		{
			temp const n4 pal_offset = i << pixel_bits;
			/*palette[ i ].b = palette_data[ pal_offset ];
			palette[ i ].g = palette_data[ pal_offset + 1 ];
			palette[ i ].r = palette_data[ pal_offset + 2 ];
			palette[ i ].a = 255;*/
			byte C1 = palette_data[ pal_offset ];
			byte C2 = palette_data[ pal_offset + 1 ];
			byte C3 = palette_data[ pal_offset + 2 ];
			byte C4 = palette_data[ pal_offset + 3 ];

			palette[ i ] = pixel( palette_data[ pal_offset + 2 ], palette_data[ pal_offset + 1 ], palette_data[ pal_offset ], 0xff );
		}
	}

	iter( y, c.size.h )
	{
		temp const i8 src_y = pick( height > 0, c.size.h - 1 - y, y );
		temp const byte ref row_data = pixel_data + ( src_y * row_size );

		iter( x, c.size.w )
		{
			temp const i8 dst_index = y * c.size.w + x;

			with( bit_count )
			{
				when( 1 )
				{
					temp const i4 byte_index = x >> 3;
					temp const i4 bit_index = 7 - ( x % 8 );
					temp const n1 palette_index = ( row_data[ byte_index ] >> bit_index ) & 1;
					c.pixels[ dst_index ] = ( palette[ palette_index ] );
					skip;
				}

				when( 4 )
				{
					temp const i4 byte_index = x >> 1;
					temp const n1 palette_index = pick( x & 1, row_data[ byte_index ] & 15, ( row_data[ byte_index ] >> 4 ) & 15 );
					c.pixels[ dst_index ] = ( palette[ palette_index ] );
					skip;
				}

				when( 8 )
				{
					temp const n1 palette_index = row_data[ x ];
					c.pixels[ dst_index ] = ( palette[ palette_index ] );
					skip;
				}

				when( 24 )
				{
					temp const i4 pixel_offset = x * 3;
					c.pixels[ dst_index ] = pixel( row_data[ pixel_offset ], row_data[ pixel_offset + 1 ], row_data[ pixel_offset + 2 ], 0xff );
					/*c.pixels[ dst_index ].b = row_data[ pixel_offset ];
					c.pixels[ dst_index ].g = row_data[ pixel_offset + 1 ];
					c.pixels[ dst_index ].r = row_data[ pixel_offset + 2 ];
					c.pixels[ dst_index ].a = 255;*/
					skip;
				}

				when( 32 )
				{
					temp const i4 pixel_offset = x << pixel_bits;
					c.pixels[ dst_index ] = pixel( row_data[ pixel_offset ], row_data[ pixel_offset + 1 ], row_data[ pixel_offset + 2 ], row_data[ pixel_offset + 3 ] );
					/*c.pixels[ dst_index ].b = row_data[ pixel_offset ];
					c.pixels[ dst_index ].g = row_data[ pixel_offset + 1 ];
					c.pixels[ dst_index ].r = row_data[ pixel_offset + 2 ];
					c.pixels[ dst_index ].a = row_data[ pixel_offset + 3 ];*/
					skip;
				}

				other
				{
					delete_ref( c.pixels );
					out c;
				}
			}
		}
	}

	out c;
}

///////
#if 0
	type( compressed_pixels )
	{
		byte ref data;
		n8 data_size;
		n2x2 size;
		color palette[ 32 ];
		n1 palette_size;
		flag uses_lzss;
		n8 pre_lzss_size;
	};

	embed compressed_pixels canvas_to_compressed_pixels( const canvas const_ref in_canvas )
	{
		temp n8 area = n8( in_canvas->size.w ) * n8( in_canvas->size.h );
		compressed_pixels out_cpixels = make( compressed_pixels, .data = new_bytes( area ), .size = in_canvas->size );
		temp const pixel ref p = in_canvas->pixels;
		temp const pixel const_ref p_end = p + area;
		temp n8 data_size = 0;

		temp pixel this_p = val_of( p );
		temp pixel last_p = this_p;

		find_palette:
		{
			jump_if_all( p > in_canvas->pixels, this_p.r is last_p.r, this_p.g is last_p.g, this_p.b is last_p.b, this_p.a is last_p.a ) skip_pixel;

			temp n1 n = 0;
			check_palette:
			{
				if( n is 0 and out_cpixels.palette_size > 0 )
				{
					jump_if_all( this_p.r is out_cpixels.palette[ 0 ].r, this_p.g is out_cpixels.palette[ 0 ].g, this_p.b is out_cpixels.palette[ 0 ].b ) found_palette;
				}
				else jump_if_all( this_p.r is out_cpixels.palette[ n ].r, this_p.g is out_cpixels.palette[ n ].g, this_p.b is out_cpixels.palette[ n ].b, this_p.a is out_cpixels.palette[ n ].a ) found_palette;
				jump_if( ++n < out_cpixels.palette_size ) check_palette;
			}
			found_palette:

			if( n >= out_cpixels.palette_size and n < 32 )
			{
				if( out_cpixels.palette_size is 0 ) this_p.a = 0;
				out_cpixels.palette[ out_cpixels.palette_size++ ] = pixel_to_color( this_p );
			}

			skip_pixel:
			last_p = this_p;
			if( ++p < p_end )
			{
				this_p = val_of( p );
				jump find_palette;
			}
		}

		//

		temp n1 bits_per_index = n_to_bits( out_cpixels.palette_size );
		temp n1 indices_per_byte = 8 / bits_per_index;
		temp n1 index_mask = ( 1 << bits_per_index ) - 1;

		p = in_canvas->pixels;
		temp byte current_byte = 0;
		temp n1 indices_in_byte = 0;

		encode_pixels:
		{
			temp const pixel color = val_of( p );
			temp n1 index = 0;
			find_index:
			{
				if( index is 0 )
				{
					jump_if_all( color.r is out_cpixels.palette[ 0 ].r, color.g is out_cpixels.palette[ 0 ].g, color.b is out_cpixels.palette[ 0 ].b ) found_index;
				}
				else jump_if_all( color.r is out_cpixels.palette[ index ].r, color.g is out_cpixels.palette[ index ].g, color.b is out_cpixels.palette[ index ].b, color.a is out_cpixels.palette[ index ].a ) found_index;
				++index;
				jump find_index;
			}
			found_index:

			current_byte |= ( index << ( indices_in_byte * bits_per_index ) );
			++indices_in_byte;

			if( indices_in_byte >= indices_per_byte )
			{
				out_cpixels.data[ data_size++ ] = current_byte;
				current_byte = 0;
				indices_in_byte = 0;
			}

			++p;
			jump_if( p < p_end ) encode_pixels;
		}

		if( indices_in_byte > 0 ) out_cpixels.data[ data_size++ ] = current_byte;

		temp byte ref lzss_bytes = new_bytes( ( ( data_size << 1 ) + data_size ) );
		temp n8 lzss_size = bytes_compress( out_cpixels.data, data_size, lzss_bytes );
		if( lzss_size < data_size )
		{
			delete_ref( out_cpixels.data );
			out_cpixels.data = bytes_resize( lzss_bytes, lzss_size );
			out_cpixels.data_size = lzss_size;
			out_cpixels.pre_lzss_size = data_size;
			out_cpixels.uses_lzss = yes;
		}
		else
		{
			delete_ref( lzss_bytes );
			out_cpixels.data = bytes_resize( out_cpixels.data, data_size );
			out_cpixels.data_size = data_size;
			out_cpixels.uses_lzss = no;
		}
		out out_cpixels;
	}

	embed canvas compressed_pixels_to_canvas( const compressed_pixels const_ref in_cpixels )
	{
		temp byte ref data = in_cpixels->data;
		temp n8 data_size = in_cpixels->data_size;
		if( in_cpixels->uses_lzss )
		{
			data = new_bytes( in_cpixels->pre_lzss_size );
			data_size = bytes_uncompress( in_cpixels->data, in_cpixels->data_size, data );
		}

		canvas out_canvas = canvas( in_cpixels->size.w, in_cpixels->size.h );
		temp n8 area = in_cpixels->size.w * in_cpixels->size.h;
		temp n8 pos = 0;
		temp n8 data_idx = 0;

		// Calculate bit unpacking parameters
		temp n1 bits_per_index = n_to_bits( in_cpixels->palette_size );
		temp n1 indices_per_byte = 8 / bits_per_index;
		temp n1 index_mask = ( 1 << bits_per_index ) - 1;

		while( data_idx < data_size and pos < area )
		{
			temp const byte current_byte = data[ data_idx++ ];
			temp n1 indices_in_byte = 0;

			while( indices_in_byte < indices_per_byte and pos < area )
			{
				temp const pixel p = color_to_pixel( in_cpixels->palette[ ( current_byte >> ( indices_in_byte * bits_per_index ) ) & index_mask ] );
				if( p.a isnt 0 )
				{
					out_canvas.pixels[ pos ] = p;
				}
				++pos;
				++indices_in_byte;
			}
		}

		if( in_cpixels->uses_lzss ) delete_ref( data );
		out out_canvas;
	}

	//

	fn compressed_pixels_to_file( const compressed_pixels cpixels, const byte const_ref name )
	{
		byte ref output = new_bytes( cpixels.data_size * 2 + 1024 );
		byte ref r = output;

		bytes_paste_move( "global canvas ", r );
		bytes_paste_move( name, r );
		bytes_paste_move( ";\nglobal perm const compressed_pixels cpixels_", r );
		bytes_paste_move( name, r );
		bytes_paste_move( "={\"", r );

		iter( i, cpixels.data_size )
		{
			byte b = cpixels.data[ i ];

			with( b )
			{
				when( 0 )
				{
					if_all( i + 1 < cpixels.data_size, cpixels.data[ i + 1 ] >= '0', cpixels.data[ i + 1 ] <= '9' )
					{
						bytes_paste_move( "\\000", r );
					}
					else
					{
						bytes_paste_move( "\\0", r );
					}
					skip;
				}

				when( 0x1A )
				{
					if_all( i + 1 < cpixels.data_size, cpixels.data[ i + 1 ] >= '0', cpixels.data[ i + 1 ] <= '7' )
					{
						bytes_paste_move( "\\032", r );
					}
					else
					{
						bytes_paste_move( "\\32", r );
					}
					skip;
				}

				when( '"' )
				{
					bytes_paste_move( "\\\"", r );
					skip;
				}

				when( '\\' )
				{
					bytes_paste_move( "\\\\", r );
					skip;
				}

				when( '\n' )
				{
					bytes_paste_move( "\\n", r );
					skip;
				}

				when( '\r' )
				{
					bytes_paste_move( "\\r", r );
					skip;
				}

				other
				{
					bytes_add( r, b );
				}
			}

			if( ( ( i + 1 ) mod 4000 ) is 0 and i + 1 < cpixels.data_size )
			{
				bytes_paste_move( "\"\n\"", r );
			}
		}

		bytes_paste_move( "\",\n", r );
		bytes_add_n4( r, cpixels.data_size );

		bytes_paste_move( ",{", r );
		bytes_add_n2( r, cpixels.size.w );
		bytes_add( r, ',' );
		bytes_add_n2( r, cpixels.size.h );
		bytes_paste_move( "},\n", r );

		bytes_add( r, '{' );
		iter( p, cpixels.palette_size )
		{
			color c = cpixels.palette[ p ];
			bytes_paste_move( "0x", r );
			bytes_add_hex_n4( r, c.rgba );
			if( p < cpixels.palette_size - 1 ) bytes_add( r, ',' );
		}
		bytes_paste_move( "},\n", r );

		bytes_add_n1( r, cpixels.palette_size );

		bytes_add( r, ',' );
		bytes_add_n1( r, cpixels.uses_lzss ? 1 : 0 );

		bytes_add( r, ',' );
		bytes_add_n4( r, cpixels.pre_lzss_size );

		bytes_paste_move( "};\n", r );

		byte filename[ 256 ] = { 0 };
		byte ref fname_ptr = filename;
		bytes_paste_move( name, fname_ptr );
		bytes_paste_move( ".h", fname_ptr );

		file f = new_file( filename );
		file_save( ref_of( f ), output, r - output );

		delete_ref( output );
	}

	//

	///////
	// Prediction-Encoded Pixels

	type( pep )
	{
		byte ref data;
		n4 data_size;
		n4 decompressed_size;
		n2x2 dimensions;
		color palette[ 256 ];
		n1 palette_size;
		flag is_4bit;
		n1 max_symbol;
	};

	#define PEP_FREQ_N 257
	#define PEP_FREQ_END ( PEP_FREQ_N - 1 )

	#define PEP_CONTEXTS_MAX_MASK 0xffu

	#define PEP_ARITH_MAX 0x7fffffffffffffffu
	#define PEP_ARITH_LOW 0x2000000000000000u
	#define PEP_ARITH_MID 0x4000000000000000u
	#define PEP_ARITH_HIGH 0x6000000000000000u

	type( _pep_context )
	{
		n2 freq[ PEP_FREQ_N ];
		n4 sum;
	};

	#define PEP_FREQ_MAX( AREA ) ( n8_max( PEP_FREQ_END, AREA / 16 ) + PEP_FREQ_END )

	#define PEP_ACCUM( FREQ_REF, SYMBOL ) iter( f_a, SYMBOL ) accum += FREQ_REF[ f_a ]

	#define PEP_ENCODE( FREQ, TOTAL )\
		START_DEF\
		{\
			temp const n8 delta = high - low + 1;\
			if( delta < TOTAL )\
			{\
				high = low + ( accum + FREQ ) - 1;\
				low = low + accum;\
			}\
			else\
			{\
				high = low + ( delta / TOTAL ) * ( accum + FREQ ) + ( ( delta mod TOTAL ) * ( accum + FREQ ) ) / TOTAL - 1;\
				low = low + ( delta / TOTAL ) * accum + ( ( delta mod TOTAL ) * accum ) / TOTAL;\
			}\
		}\
		END_DEF

	#define PEP_UPDATE( CONTEXT, SYMBOL )\
		START_DEF\
		{\
			CONTEXT->freq[ SYMBOL ] ++;\
			CONTEXT->sum++;\
			if( CONTEXT->sum > freq_max )\
			{\
				CONTEXT->sum = 0;\
				iter( f, PEP_FREQ_N )\
				{\
					CONTEXT->freq[ f ] = ( CONTEXT->freq[ f ] + 1 ) >> 1;\
					CONTEXT->sum += CONTEXT->freq[ f ];\
				}\
			}\
		}\
		END_DEF

	#define PEP_TARGET( VALUE, TOTAL ) pick( high - low + 1 < TOTAL, VALUE - low, ( ( VALUE - low ) / ( ( high - low + 1 ) / TOTAL ) ) + ( ( ( VALUE - low ) mod ( ( high - low + 1 ) / TOTAL ) ) * TOTAL ) / ( high - low + 1 ) )

	#define PEP_BIT_OUT( BIT )\
		START_DEF\
		{\
			buffer = ( buffer >> 1 ) | pick( BIT, 0x80u, 0 );\
			if( --bits_left is 0 )\
			{\
				val_of( pep_data_ref++ ) = buffer;\
				bits_left = 8;\
				buffer = 0;\
			}\
		}\
		END_DEF

	#define PEP_BIT_IN( VAR )\
		START_DEF\
		{\
			if( bits_left is 0 )\
			{\
				buffer = val_of( pep_data_ref++ );\
				bits_left = 8;\
			}\
			VAR = ( VAR << 1 ) | ( buffer & 1 );\
			buffer >>= 1;\
			bits_left--;\
		}\
		END_DEF

	#define PEP_ADJUST_RANGE( BOUNDARY )\
		START_DEF\
		{\
			low = ( low - BOUNDARY ) << 1;\
			high = ( ( high - BOUNDARY ) << 1 ) | 1;\
		}\
		END_DEF

	#define PEP_OUTPUT_UNDERFLOW( BIT, OPPOSITE_BIT )\
		START_DEF\
		{\
			PEP_BIT_OUT( BIT );\
			while( underflow > 0 )\
			{\
				PEP_BIT_OUT( OPPOSITE_BIT );\
				underflow--;\
			}\
		}\
		END_DEF

	#define PEP_COMPRESS_RENORM()\
		START_DEF\
		{\
			loop\
			{\
				if( high < PEP_ARITH_MID )\
				{\
					PEP_OUTPUT_UNDERFLOW( 0, 1 );\
					low <<= 1;\
					high = ( high << 1 ) | 1;\
				}\
				else if( low >= PEP_ARITH_MID )\
				{\
					PEP_OUTPUT_UNDERFLOW( 1, 0 );\
					PEP_ADJUST_RANGE( PEP_ARITH_MID );\
				}\
				else if( low >= PEP_ARITH_LOW and high < PEP_ARITH_HIGH )\
				{\
					underflow++;\
					PEP_ADJUST_RANGE( PEP_ARITH_LOW );\
				}\
				else skip;\
			}\
		}\
		END_DEF

	#define PEP_DECOMPRESS_RENORM( VALUE )\
		START_DEF\
		{\
			loop\
			{\
				if( high < PEP_ARITH_MID )\
				{\
					low <<= 1;\
					high = ( high << 1 ) | 1;\
					PEP_BIT_IN( VALUE );\
				}\
				else if( low >= PEP_ARITH_MID )\
				{\
					PEP_ADJUST_RANGE( PEP_ARITH_MID );\
					VALUE = ( VALUE - PEP_ARITH_MID );\
					PEP_BIT_IN( VALUE );\
				}\
				else if( low >= PEP_ARITH_LOW and high < PEP_ARITH_HIGH )\
				{\
					PEP_ADJUST_RANGE( PEP_ARITH_LOW );\
					VALUE = ( VALUE - PEP_ARITH_LOW );\
					PEP_BIT_IN( VALUE );\
				}\
				else skip;\
			}\
		}\
		END_DEF

	embed pep canvas_to_pep( const canvas const_ref in_canvas )
	{
		temp const n8 area = n8( in_canvas->size.w ) * n8( in_canvas->size.h );
		pep out_pep = make( pep, .data = nothing, .dimensions = in_canvas->size );
		temp const pixel ref p = in_canvas->pixels;
		temp const pixel const_ref p_end = p + area;

		///////
		// palette construction

		temp pixel this_p = val_of( p );
		temp pixel last_p = this_p;

		find_palette:
		{
			jump_if_all( p > in_canvas->pixels, this_p.r is last_p.r, this_p.g is last_p.g, this_p.b is last_p.b, this_p.a is last_p.a ) skip_pixel;

			temp n2 n = 0;
			check_palette:
			{
				if( n is 0 and out_pep.palette_size > 0 )
				{
					jump_if_all( this_p.r is out_pep.palette[ 0 ].r, this_p.g is out_pep.palette[ 0 ].g, this_p.b is out_pep.palette[ 0 ].b ) found_palette;
				}
				else jump_if_all( this_p.r is out_pep.palette[ n ].r, this_p.g is out_pep.palette[ n ].g, this_p.b is out_pep.palette[ n ].b, this_p.a is out_pep.palette[ n ].a ) found_palette;
				jump_if( ++n < out_pep.palette_size ) check_palette;
			}
			found_palette:

			if( n >= out_pep.palette_size and n < 256 )
			{
				if( out_pep.palette_size is 0 ) this_p.a = 0;
				out_pep.palette[ out_pep.palette_size++ ] = pixel_to_color( this_p );
			}

			skip_pixel:
			last_p = this_p;
			if( ++p < p_end )
			{
				this_p = val_of( p );
				jump find_palette;
			}
		}

		///////
		// pixels to packed-palette-indices, then PPM order-2 compression

		temp const n1 bits_per_index = n_to_bits( out_pep.palette_size );
		temp const n1 indices_per_byte = 8 / bits_per_index;
		temp const n1 index_mask = ( 1 << bits_per_index ) - 1;

		temp byte const_ref pep_data = new_bytes( area );
		temp byte ref pep_data_ref = pep_data;

		perm _pep_context contexts[ PEP_CONTEXTS_MAX_MASK + 2 ];
		bytes_clear( contexts, size_of( _pep_context ) * ( PEP_CONTEXTS_MAX_MASK + 2 ) );

		_pep_context ref order0 = ref_of( contexts[ PEP_CONTEXTS_MAX_MASK + 1 ] );
		iter( i, PEP_FREQ_N ) order0->freq[ i ] = 1;
		order0->sum = PEP_FREQ_N;

		temp n8 low = 0;
		temp n8 high = PEP_ARITH_MAX;
		temp n8 underflow = 0;
		temp n4 context_id = 0;
		temp n1 buffer = 0;
		temp n1 bits_left = 8;
		temp n8 freq_max = PEP_FREQ_MAX( area );
		temp n8 data_size = 0;

		p = in_canvas->pixels;
		temp byte current_byte = 0;
		temp n1 indices_in_byte = 0;

		while( p < p_end or indices_in_byte > 0 )
		{
			if( p < p_end )
			{
				temp const pixel color = val_of( p );
				temp n1 index = 0;
				find_index:
				{
					if( index is 0 )
					{
						jump_if_all( color.r is out_pep.palette[ 0 ].r, color.g is out_pep.palette[ 0 ].g, color.b is out_pep.palette[ 0 ].b ) found_index;
					}
					else jump_if_all( color.r is out_pep.palette[ index ].r, color.g is out_pep.palette[ index ].g, color.b is out_pep.palette[ index ].b, color.a is out_pep.palette[ index ].a ) found_index;
					++index;
					jump find_index;
				}
				found_index:

				current_byte |= ( index << ( indices_in_byte * bits_per_index ) );
				++indices_in_byte;
			}

			if( indices_in_byte >= indices_per_byte or ( p >= p_end and indices_in_byte > 0 ) )
			{
				temp n8 accum = 0;
				temp n1 symbol = current_byte;
				if( symbol > out_pep.max_symbol ) out_pep.max_symbol = symbol;
				temp _pep_context const_ref context_ref = ref_of( contexts[ context_id % ( PEP_CONTEXTS_MAX_MASK + 1 ) ] );
				temp const n4 context_sum = context_ref->sum;

				if( context_sum isnt 0 and context_ref->freq[ symbol ] isnt 0 )
				{
					PEP_ACCUM( context_ref->freq, symbol );
					PEP_ENCODE( context_ref->freq[ symbol ], context_sum );
					PEP_UPDATE( context_ref, symbol );
				}
				else
				{
					if( context_sum isnt 0 )
					{
						accum = 0;
						PEP_ACCUM( context_ref->freq, PEP_FREQ_END );
						PEP_ENCODE( context_ref->freq[ PEP_FREQ_END ], context_sum );
						PEP_COMPRESS_RENORM();
					}

					accum = 0;
					PEP_ACCUM( order0->freq, symbol );
					PEP_ENCODE( order0->freq[ symbol ], order0->sum );

					if( context_sum is 0 )
					{
						context_ref->freq[ PEP_FREQ_END ] = 1;
						context_ref->sum = 1;
					}
					context_ref->freq[ symbol ] = 1;
					context_ref->sum++;
					PEP_UPDATE( order0, symbol );
				}
				PEP_COMPRESS_RENORM();
				context_id = ( ( context_id << 8 ) | symbol );
				++data_size;

				current_byte = 0;
				indices_in_byte = 0;
			}

			if( p < p_end )
			{
				++p;
			}
		}

		++underflow;
		if( low < PEP_ARITH_MID )
		{
			PEP_BIT_OUT( 0 );
			while( underflow > 0 )
			{
				PEP_BIT_OUT( 1 );
				underflow--;
			}
		}
		else
		{
			PEP_BIT_OUT( 1 );
			while( underflow > 0 )
			{
				PEP_BIT_OUT( 0 );
				underflow--;
			}
		}

		if( bits_left < 8 ) val_of( pep_data_ref++ ) = buffer >> bits_left;

		out_pep.decompressed_size = data_size;
		out_pep.data_size = pep_data_ref - pep_data;
		out_pep.data = bytes_resize( pep_data, out_pep.data_size );

		out out_pep;
	}

	embed canvas pep_to_canvas( const pep const_ref in_pep )
	{
		temp byte ref pep_data_ref = in_pep->data;
		temp const n8 data_size = in_pep->decompressed_size;

		canvas out_canvas = canvas( in_pep->dimensions.w, in_pep->dimensions.h );
		temp const n8 area = n8( in_pep->dimensions.w ) * n8( in_pep->dimensions.h );
		temp n8 canvas_pos = 0;

		temp const n1 bits_per_index = n_to_bits( in_pep->palette_size );
		temp const n1 indices_per_byte = 8 / bits_per_index;
		temp const n1 index_mask = ( 1 << bits_per_index ) - 1;

		perm _pep_context contexts[ PEP_CONTEXTS_MAX_MASK + 2 ];
		bytes_clear( contexts, size_of( _pep_context ) * ( PEP_CONTEXTS_MAX_MASK + 2 ) );

		_pep_context ref order0 = ref_of( contexts[ PEP_CONTEXTS_MAX_MASK + 1 ] );
		iter( i, PEP_FREQ_N ) order0->freq[ i ] = 1;
		order0->sum = PEP_FREQ_N;

		temp n1 buffer = 0;
		temp n1 bits_left = 0;
		temp n8 value = 0;

		repeat( 63 )
		{
			PEP_BIT_IN( value );
		}

		///////
		// decompress PPM order-2 structure into packed-palette-indices

		temp n8 low = 0;
		temp n8 high = PEP_ARITH_MAX;
		temp n4 context_id = 0;
		temp const n2 max_symbol = in_pep->max_symbol + 1;
		temp n8 freq_max = PEP_FREQ_MAX( x2_area( in_pep->dimensions ) );

		temp const color const_ref palette = in_pep->palette;
		temp pixel const_ref canvas_pixels = out_canvas.pixels;

		iter( b, data_size )
		{
			temp _pep_context const_ref context_ref = ref_of( contexts[ context_id % ( PEP_CONTEXTS_MAX_MASK + 1 ) ] );
			temp const n4 context_sum = context_ref->sum;
			temp n8 target = PEP_TARGET( value, pick( context_sum isnt 0, context_sum, 1 ) );
			temp n8 accum = 0;
			temp n1 symbol = 0;

			if( context_sum isnt 0 )
			{
				iter( f, max_symbol )
				{
					temp n2 freq = context_ref->freq[ f ];
					if( freq )
					{
						if( accum + freq > target )
						{
							symbol = f;
							PEP_ENCODE( freq, context_sum );
							PEP_UPDATE( context_ref, f );
							goto done_decode;
						}
						accum += freq;
					}
				}

				if( context_ref->freq[ PEP_FREQ_END ] )
				{
					if( accum + context_ref->freq[ PEP_FREQ_END ] > target )
					{
						PEP_ENCODE( context_ref->freq[ PEP_FREQ_END ], context_sum );
						PEP_DECOMPRESS_RENORM( value );
					}
				}
			}

			target = PEP_TARGET( value, order0->sum );
			accum = 0;

			iter( j, max_symbol )
			{
				accum += order0->freq[ j ];
				if( accum > target )
				{
					symbol = j;
					accum -= order0->freq[ j ];
					PEP_ENCODE( order0->freq[ j ], order0->sum );

					if( context_sum is 0 )
					{
						context_ref->freq[ PEP_FREQ_END ] = 1;
						context_ref->sum = 1;
					}
					context_ref->freq[ symbol ] = 1;
					context_ref->sum++;
					PEP_UPDATE( order0, symbol );
					skip;
				}
			}

			done_decode:
			PEP_DECOMPRESS_RENORM( value );

			///////
			// convert packed-palette-indices to pixels

			if( indices_per_byte > 1 )
			{
				temp n1 indices_in_byte = 0;
				while( indices_in_byte < indices_per_byte and canvas_pos < area )
				{
					temp const n1 palette_idx = ( symbol >> ( indices_in_byte * bits_per_index ) ) & index_mask;
					temp const pixel p = color_to_pixel( in_pep->palette[ palette_idx ] );
					canvas_pixels[ canvas_pos ] = p;
					++canvas_pos;
					++indices_in_byte;
				}
			}
			else
			{
				if( canvas_pos < area )
				{
					temp const pixel p = color_to_pixel( in_pep->palette[ symbol ] );
					canvas_pixels[ canvas_pos ] = p;
					++canvas_pos;
				}
			}

			context_id = ( ( context_id << 8 ) | symbol );
		}

		out out_canvas;
	}

	embed byte ref pep_to_bytes( const pep const_ref in_pep, n4 const_ref out_size )
	{
		temp n8 palette_bytes = pick( in_pep->is_4bit, ( in_pep->palette_size * size_of( color ) ) >> 1, size_of( color ) * in_pep->palette_size );
		temp n8 size = size_of( n4 ) + ( size_of( n2 ) << 1 ) + ( size_of( n1 ) << 1 ) + palette_bytes + in_pep->data_size;
		temp byte const_ref out_bytes = new_bytes( size );
		temp byte ref bytes_ref = out_bytes;

		val_of( to( n4 ref, bytes_ref ) ) = in_pep->data_size | ( in_pep->is_4bit << 31 );
		bytes_ref += size_of( n4 );
		val_of( to( n2 ref, bytes_ref ) ) = in_pep->dimensions.w;
		bytes_ref += size_of( n2 );
		val_of( to( n2 ref, bytes_ref ) ) = in_pep->dimensions.h;
		bytes_ref += size_of( n2 );
		val_of( bytes_ref++ ) = in_pep->palette_size;

		if( in_pep->palette_size )
		{
			if( in_pep->is_4bit )
			{
				iter( i, in_pep->palette_size )
				{
					temp color c = in_pep->palette[ i ];
					val_of( bytes_ref++ ) = ( ( c.r & 0xF0 ) >> 4 ) | ( c.g & 0xF0 );
					val_of( bytes_ref++ ) = ( ( c.b & 0xF0 ) >> 4 ) | ( c.a & 0xF0 );
				}
			}
			else
			{
				bytes_copy( ref_of( in_pep->palette[ 0 ] ), size_of( color ) * in_pep->palette_size, bytes_ref );
				bytes_ref += size_of( color ) * in_pep->palette_size;
			}
		}

		val_of( bytes_ref++ ) = in_pep->max_symbol;

		if( in_pep->data_size )
		{
			bytes_copy( in_pep->data, in_pep->data_size, bytes_ref );
		}

		val_of( out_size ) = size;
		out out_bytes;
	}

	embed pep bytes_to_pep( const byte const_ref in_bytes )
	{
		pep out_pep = { 0 };
		temp const byte ref bytes_ref = in_bytes;

		temp n4 packed_data_size = val_of( to( n4 const_ref, bytes_ref ) );
		out_pep.is_4bit = ( packed_data_size >> 31 ) & 1;
		out_pep.data_size = packed_data_size & 0x7FFFFFFF;
		bytes_ref += size_of( n4 );

		out_pep.dimensions.w = val_of( to( n2 const_ref, bytes_ref ) );
		bytes_ref += size_of( n2 );
		out_pep.dimensions.h = val_of( to( n2 const_ref, bytes_ref ) );
		bytes_ref += size_of( n2 );
		out_pep.palette_size = val_of( bytes_ref++ );

		bytes_clear( out_pep.palette, size_of( color ) * 256 );

		if( out_pep.palette_size )
		{
			if( out_pep.is_4bit )
			{
				iter( i, out_pep.palette_size )
				{
					temp n1 b1 = val_of( bytes_ref++ );
					temp n1 b2 = val_of( bytes_ref++ );
					out_pep.palette[ i ].r = ( b1 & 0x0F ) | ( ( b1 & 0x0F ) << 4 );
					out_pep.palette[ i ].g = ( b1 & 0xF0 ) | ( ( b1 & 0xF0 ) >> 4 );
					out_pep.palette[ i ].b = ( b2 & 0x0F ) | ( ( b2 & 0x0F ) << 4 );
					out_pep.palette[ i ].a = ( b2 & 0xF0 ) | ( ( b2 & 0xF0 ) >> 4 );
				}
			}
			else
			{
				bytes_copy( bytes_ref, size_of( color ) * out_pep.palette_size, ref_of( out_pep.palette[ 0 ] ) );
				bytes_ref += size_of( color ) * out_pep.palette_size;
			}
		}

		out_pep.max_symbol = val_of( bytes_ref++ );

		temp const n1 bits_per_index = n_to_bits( out_pep.palette_size );
		temp const n1 indices_per_byte = 8 / bits_per_index;
		temp const n8 area = n8( out_pep.dimensions.w ) * n8( out_pep.dimensions.h );
		out_pep.decompressed_size = ( area + indices_per_byte - 1 ) / indices_per_byte;

		out_pep.data = pick( out_pep.data_size isnt 0, new_bytes( out_pep.data_size ), nothing );
		if( out_pep.data_size )
		{
			bytes_copy( bytes_ref, out_pep.data_size, out_pep.data );
		}

		out out_pep;
	}

	fn pep_to_file( const pep const_ref in_pep, const byte const_ref name )
	{
		n4 pep_bytes_size = 0;
		temp const byte const_ref pep_bytes = pep_to_bytes( in_pep, ref_of( pep_bytes_size ) );

		temp byte ref output = new_bytes( ( pep_bytes_size << 1 ) + 256 );
		temp byte ref out_ref = output;

		bytes_paste_move( "global canvas ", out_ref );
		bytes_paste_move( name, out_ref );
		bytes_paste_move( ";global const byte ", out_ref );
		bytes_paste_move( name, out_ref );
		bytes_paste_move( "_pep_bytes[]=\"", out_ref );

		iter( b, pep_bytes_size )
		{
			temp const byte pbyte = pep_bytes[ b ];
			with( pbyte )
			{
				when( '\0' )
				{
					if_all( b + 1 < pep_bytes_size, pep_bytes[ b + 1 ] >= '0', pep_bytes[ b + 1 ] <= '9' )
					{
						bytes_paste_move( "\\000", out_ref );
					}
					else
					{
						bytes_paste_move( "\\0", out_ref );
					}
					skip;
				}

				when( 0x1A )
				{
					if_all( b + 1 < pep_bytes_size, pep_bytes[ b + 1 ] >= '0', pep_bytes[ b + 1 ] <= '7' )
					{
						bytes_paste_move( "\\032", out_ref );
					}
					else
					{
						bytes_paste_move( "\\32", out_ref );
					}
					skip;
				}

				when( '"' )
				{
					bytes_paste_move( "\\\"", out_ref );
					skip;
				}

				when( '\\' )
				{
					bytes_paste_move( "\\\\", out_ref );
					skip;
				}

				when( '\r' )
				{
					bytes_paste_move( "\\r", out_ref );
					skip;
				}

				when( '\n' )
				{
					bytes_paste_move( "\\n", out_ref );
					skip;
				}

				other
				{
					bytes_add( out_ref, pbyte );
				}
			}

			if( ( ( b + 1 ) mod 4000 ) is 0 and b + 1 < pep_bytes_size )
			{
				bytes_paste_move( "\"\n\"", out_ref );
			}
		}

		bytes_paste_move( "\";\n", out_ref );

		byte filename[ 256 ] = { 0 };
		byte ref fname_ptr = filename;
		bytes_paste_move( name, fname_ptr );
		bytes_paste_move( ".h", fname_ptr );

		file f = new_file( filename );
		file_save( ref_of( f ), output, out_ref - output );

		delete_ref( output );
	}
#endif

///////

fn _C7H16_init()
{
	OS_INPUT_MAP = _C7H16_input_map();
	//_C7H16_();
	//SET_OS_INPUT();
	//window_list = new_list(window);
}

fn _C7H16_loop()
{
	temp flag close = no;
	loop
	{
		iter( window_id, alive_windows_count )
		{
			temp window this_window = alive_windows[ window_id ];
			//
			window_process( this_window );
			if( this_window->close )
			{
				close = yes;
				skip;
			}
		}
		skip_if( close );
	}
}

fn _C7H16_close()
{
	//
}

#undef start
#define start\
	fn _C7H16_main();\
	_main_fn\
	{\
		_C7H16_init();\
		_C7H16_main();\
		_C7H16_loop();\
		_C7H16_close();\
		out success;\
	}\
	fn _C7H16_main()
