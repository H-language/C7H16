////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  C7H16 (heptane)
//
//  author(s):
//  ENDESGA - https://x.com/ENDESGA | https://bsky.app/profile/endesga.bsky.social
//
//  https://github.com/H-language/C7H16
//  2026 - CC0 - FOSS forever
//

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - dependencies

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

#pragma endregion dependencies
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - defaults

#define C7H16_NAME "C7H16"

////////////////////////////////////////////////////////////////
#pragma region version

#define C7H16_VERSION_MAJOR 0
#define C7H16_VERSION_MINOR 1
#define C7H16_VERSION_PATCH 0
#define C7H16_VERSION AS_BYTES( C7H16_VERSION_MAJOR ) "." AS_BYTES( C7H16_VERSION_MINOR ) "." AS_BYTES( C7H16_VERSION_PATCH )

#pragma endregion version
//

#pragma endregion defaults
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - declarations

////////////////////////////////////////////////////////////////
#pragma region dimensional

#define _type_x2( TYPE )\
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

#define _type_x3( TYPE )\
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

#define _type_x4( TYPE )\
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

#define _TYPEx( TYPE ) _type_x2( TYPE ); _type_x3( TYPE ); _type_x4( TYPE )

_TYPEx( n1 );
_TYPEx( i1 );

_TYPEx( n2 );
_TYPEx( i2 );

_TYPEx( n4 );
_TYPEx( i4 );
_TYPEx( r4 );

_TYPEx( n8 );
_TYPEx( i8 );
_TYPEx( r8 );

#pragma endregion dimensional
//

////////////////////////////////////////////////////////////////
#pragma region anchor

group( anchor )
{
	anchor_left_top = 0x00, // 0000 0000
	anchor_left_middle = 0x01, // 0000 0001
	anchor_left_bottom = 0x02, // 0000 0010
	anchor_center_top = 0x10, // 0001 0000
	anchor_center_middle = 0x11, // 0001 0001
	anchor_center_bottom = 0x12, // 0001 0010
	anchor_right_top = 0x20, // 0010 0000
	anchor_right_middle = 0x21, // 0010 0001
	anchor_right_bottom = 0x22 // 0010 0010
};

#pragma endregion anchor
//

////////////////////////////////////////////////////////////////
#pragma region pixel

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

#define pixel_bytes_shift 2

#pragma endregion pixel
//

////////////////////////////////////////////////////////////////
#pragma region canvas

type( canvas )
{
	pixel ref pixels;
	n2x2 size;
	n4 area;
};

#pragma endregion canvas
//

////////////////////////////////////////////////////////////////
#pragma region font

type( font )
{
	canvas canvas;
	n2x2 letter_size;
};

#pragma endregion font
//

////////////////////////////////////////////////////////////////
#pragma region view

type( view );
type_fn( anon, view ref const ) view_ref_fn;

group( view_state )
{
	view_state_unknown,
	view_state_visible,
	view_state_hidden,
	//
	view_states_count
};

type( view )
{
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

	r4x2 mouse;

	view_ref_fn fn_draw;
	anon ref draw_ref;

	view_state state bits( view_states_count );
	flag update bits_flag;
	flag clip bits_flag;
	flag clear bits_flag;
};

#pragma endregion view
//

////////////////////////////////////////////////////////////////
#pragma region inputs

#ifdef C7H16_INPUT_NO_KEYBOARD
	#define C7H16_INPUT_NO_LETTERS
	#define C7H16_INPUT_NO_NUMBERS
	#define C7H16_INPUT_NO_SYMBOLS
	#define C7H16_INPUT_NO_FUNCTIONS
	#define C7H16_INPUT_NO_MODIFIERS
	#define C7H16_INPUT_NO_ARROWS
	#define C7H16_INPUT_NO_CONTROLS
#elif defined( C7H16_INPUT_NO_LETTERS ) and defined( C7H16_INPUT_NO_NUMBERS ) and defined( C7H16_INPUT_NO_SYMBOLS ) and defined( C7H16_INPUT_NO_FUNCTIONS ) and defined( C7H16_INPUT_NO_MODIFIERS ) and defined( C7H16_INPUT_NO_ARROWS ) and defined( C7H16_INPUT_NO_CONTROLS )
	#define C7H16_INPUT_NO_KEYBOARD
#endif

group( input_type )
{
	input_none,

	#ifndef C7H16_INPUT_NO_MOUSE
		input_mouse_left,
		input_mouse_middle,
		input_mouse_right,
		input_scroll_up,
		input_scroll_down,
		input_scroll_left,
		input_scroll_right,
	#endif

	#ifndef C7H16_INPUT_NO_LETTERS
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
	#endif

	#ifndef C7H16_INPUT_NO_NUMBERS
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
	#endif

	#ifndef C7H16_INPUT_NO_SYMBOLS
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
		input_space,
		input_tab,
	#endif

	#ifndef C7H16_INPUT_NO_FUNCTIONS
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
	#endif

	#ifndef C7H16_INPUT_NO_MODIFIERS
		input_shift,
		input_ctrl,
		input_alt,
		input_super,
	#endif

	#ifndef C7H16_INPUT_NO_ARROWS
		input_up,
		input_down,
		input_left,
		input_right,
	#endif

	#ifndef C7H16_INPUT_NO_CONTROLS
		input_escape,
		input_capslock,
		input_enter,
		input_backspace,
		input_insert,
		input_delete,
		input_home,
		input_end,
		input_pageup,
		input_pagedown,
		input_menu,
	#endif

	inputs_count
};

#define INPUT_MASK_PRESSED 0x1
#define INPUT_MASK_HELD 0x2
#define INPUT_MASK_RELEASED 0x4

#define _INPUT_SET( NAME, LINUX_KEY, WINDOWS_KEY )[ OS_PICK( LINUX_KEY, WINDOWS_KEY ) ] = input_##NAME
#define _INPUT_SET_MASKED( NAME, LINUX_KEY, WINDOWS_KEY )[ OS_PICK( LINUX_KEY & 0x1ff, WINDOWS_KEY ) ] = input_##NAME

#ifndef C7H16_INPUT_NO_KEYBOARD
	perm byte const _INPUT_MAP[] =
		{
			#ifndef C7H16_INPUT_NO_LETTERS
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
			#endif

			#ifndef C7H16_INPUT_NO_NUMBERS
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
			#endif

			#ifndef C7H16_INPUT_NO_SYMBOLS
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
				_INPUT_SET( space, XK_space, VK_SPACE ),
				_INPUT_SET_MASKED( tab, XK_Tab, VK_TAB ),
			#endif

			#ifndef C7H16_INPUT_NO_FUNCTIONS
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
			#endif

			#ifndef C7H16_INPUT_NO_MODIFIERS
				_INPUT_SET_MASKED( shift, XK_Shift_L, VK_SHIFT ),
				_INPUT_SET_MASKED( ctrl, XK_Control_L, VK_CONTROL ),
				_INPUT_SET_MASKED( alt, XK_Alt_L, VK_MENU ),
				_INPUT_SET_MASKED( super, XK_Super_L, VK_LWIN ),
			#endif

			#ifndef C7H16_INPUT_NO_ARROWS
				_INPUT_SET_MASKED( up, XK_Up, VK_UP ),
				_INPUT_SET_MASKED( down, XK_Down, VK_DOWN ),
				_INPUT_SET_MASKED( left, XK_Left, VK_LEFT ),
				_INPUT_SET_MASKED( right, XK_Right, VK_RIGHT ),
			#endif

			#ifndef C7H16_INPUT_NO_CONTROLS
				_INPUT_SET_MASKED( escape, XK_Escape, VK_ESCAPE ),
				_INPUT_SET_MASKED( capslock, XK_Caps_Lock, VK_CAPITAL ),
				_INPUT_SET_MASKED( enter, XK_Return, VK_RETURN ),
				_INPUT_SET_MASKED( backspace, XK_BackSpace, VK_BACK ),
				_INPUT_SET_MASKED( insert, XK_Insert, VK_INSERT ),
				_INPUT_SET_MASKED( delete, XK_Delete, VK_DELETE ),
				_INPUT_SET_MASKED( home, XK_Home, VK_HOME ),
				_INPUT_SET_MASKED( end, XK_End, VK_END ),
				_INPUT_SET_MASKED( pageup, XK_Page_Up, VK_PRIOR ),
				_INPUT_SET_MASKED( pagedown, XK_Page_Down, VK_NEXT ),
				_INPUT_SET_MASKED( menu, XK_Menu, VK_APPS ),
			#endif
		};
#endif

#pragma endregion inputs
//

////////////////////////////////////////////////////////////////
#pragma region window

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
	window_state_closing,
	//
	window_states_count
};

type( window )
{
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

	window_state state bits( window_states_count );
	flag visible bits_flag;
};

#pragma endregion window
//

////////////////////////////////////////////////////////////////
#pragma region program

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

	canvas const ref canvas_ref;

	window windows[ program_max_windows ];

	n1 windows_count bits( program_max_windows );
}
program;

#pragma endregion program
//

#pragma endregion declarations
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - definitions

#define grid_index( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

////////////////////////////////////////////////////////////////
#pragma region dimensional

////////////////////////////////
// hidden

#define _xx2( TYPE, NAME, SYMBOL ) embed TYPE##x2 TYPE##x2_##NAME( TYPE##x2 const A, TYPE##x2 const B ) { out make( TYPE##x2, .x = A.x SYMBOL B.x, .y = A.y SYMBOL B.y ); }
#define _xx3( TYPE, NAME, SYMBOL ) embed TYPE##x3 TYPE##x3_##NAME( TYPE##x3 const A, TYPE##x3 const B ) { out make( TYPE##x3, .x = A.x SYMBOL B.x, .y = A.y SYMBOL B.y, .z = A.z SYMBOL B.z ); }
#define _xx4( TYPE, NAME, SYMBOL ) embed TYPE##x4 TYPE##x4_##NAME( TYPE##x4 const A, TYPE##x4 const B ) { out make( TYPE##x4, .x = A.x SYMBOL B.x, .y = A.y SYMBOL B.y, .z = A.z SYMBOL B.z, .w = A.w SYMBOL B.w ); }
#define _xt2( TYPE, NAME, SYMBOL ) embed TYPE##x2 TYPE##x2_##NAME##_##TYPE( TYPE##x2 const A, const TYPE V ) { out make( TYPE##x2, .x = A.x SYMBOL V, .y = A.y SYMBOL V ); }
#define _xt3( TYPE, NAME, SYMBOL ) embed TYPE##x3 TYPE##x3_##NAME##_##TYPE( TYPE##x3 const A, const TYPE V ) { out make( TYPE##x3, .x = A.x SYMBOL V, .y = A.y SYMBOL V, .z = A.z SYMBOL V ); }
#define _xt4( TYPE, NAME, SYMBOL ) embed TYPE##x4 TYPE##x4_##NAME##_##TYPE( TYPE##x4 const A, const TYPE V ) { out make( TYPE##x4, .x = A.x SYMBOL V, .y = A.y SYMBOL V, .z = A.z SYMBOL V, .w = A.w SYMBOL V ); }

#define _fn_x2( TYPE )\
	_xx2( TYPE, add, + ) _xt2( TYPE, add, + ) _xx2( TYPE, sub, - ) _xt2( TYPE, sub, - ) _xx2( TYPE, mul, * ) _xt2( TYPE, mul, * ) _xx2( TYPE, div, / ) _xt2( TYPE, div, / );\
	embed TYPE##x2 TYPE##x2_min( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out make( TYPE##x2, MIN( A.x, B.x ), MIN( A.y, B.y ) );\
	}\
	embed TYPE##x2 TYPE##x2_max( TYPE##x2 const A, TYPE##x2 const B )\
	{\
		out make( TYPE##x2, MAX( A.x, B.x ), MAX( A.y, B.y ) );\
	}\
	embed TYPE##x2 TYPE##x2_invert( TYPE##x2 const V )\
	{\
		out make( TYPE##x2, .x = -V.x, .y = -V.y );\
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

#define _fn_x3( TYPE )\
	_xx3( TYPE, add, + ) _xt3( TYPE, add, + ) _xx3( TYPE, sub, - ) _xt3( TYPE, sub, - ) _xx3( TYPE, mul, * ) _xt3( TYPE, mul, * ) _xx3( TYPE, div, / ) _xt3( TYPE, div, / );\
	embed TYPE##x3 TYPE##x3_min( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, MIN( A.x, B.x ), MIN( A.y, B.y ), MIN( A.z, B.z ) );\
	}\
	embed TYPE##x3 TYPE##x3_max( TYPE##x3 const A, TYPE##x3 const B )\
	{\
		out make( TYPE##x3, MAX( A.x, B.x ), MAX( A.y, B.y ), MAX( A.z, B.z ) );\
	}\
	embed TYPE##x3 TYPE##x3_invert( TYPE##x3 const V )\
	{\
		out make( TYPE##x3, .x = -V.x, .y = -V.y, .z = -V.z );\
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

#define _fn_x4( TYPE )\
	_xx4( TYPE, add, + ) _xt4( TYPE, add, + ) _xx4( TYPE, sub, - ) _xt4( TYPE, sub, - ) _xx4( TYPE, mul, * ) _xt4( TYPE, mul, * ) _xx4( TYPE, div, / ) _xt4( TYPE, div, / );\
	embed TYPE##x4 TYPE##x4_min( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out make( TYPE##x4, MIN( A.x, B.x ), MIN( A.y, B.y ), MIN( A.z, B.z ), MIN( A.w, B.w ) );\
	}\
	embed TYPE##x4 TYPE##x4_max( TYPE##x4 const A, TYPE##x4 const B )\
	{\
		out make( TYPE##x4, MAX( A.x, B.x ), MAX( A.y, B.y ), MAX( A.z, B.z ), MAX( A.w, B.w ) );\
	}\
	embed TYPE##x4 TYPE##x4_invert( TYPE##x4 const V )\
	{\
		out make( TYPE##x4, .x = -V.x, .y = -V.y, .z = -V.z, .w = -V.w );\
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

#define _fn_rNxX( N, X )\
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
	}

#define _fn_TYPEx( TYPE ) _fn_x2( TYPE ) _fn_x3( TYPE ) _fn_x4( TYPE )
#define _fn_rNx( N ) _fn_rNxX( N, 2 ); _fn_rNxX( N, 3 ); _fn_rNxX( N, 4 )

#define _x2( TYPE, X_Y... ) make( TYPE##x2, DEFAULTS( ( 0, 0 ), X_Y ) )
#define _x3( TYPE, X_Y_Z... ) make( TYPE##x3, DEFAULTS( ( 0, 0, 0 ), X_Y_Z ) )
#define _x4( TYPE, X_Y_Z_W... ) make( TYPE##x4, DEFAULTS( ( 0, 0, 0, 0 ), X_Y_Z_W ) )

////////////////////////////////
// visible

_fn_TYPEx( n1 );
#define n1x2( X_Y... ) _x2( n1, X_Y )
#define n1x3( X_Y_Z... ) _x3( n1, X_Y_Z )
#define n1x4( X_Y_Z_W... ) _x4( n1, X_Y_Z_W )
#define to_n1x2( X2 ) n1x2( X2.x, X2.y )
#define to_n1x3( X3 ) n1x3( X3.x, X3.y, X3.z )
#define to_n1x4( X4 ) n1x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( i1 );
#define i1x2( X_Y... ) _x2( i1, X_Y )
#define i1x3( X_Y_Z... ) _x3( i1, X_Y_Z )
#define i1x4( X_Y_Z_W... ) _x4( i1, X_Y_Z_W )
#define to_i1x2( X2 ) i1x2( X2.x, X2.y )
#define to_i1x3( X3 ) i1x3( X3.x, X3.y, X3.z )
#define to_i1x4( X4 ) i1x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( n2 );
#define n2x2( X_Y... ) _x2( n2, X_Y )
#define n2x3( X_Y_Z... ) _x3( n2, X_Y_Z )
#define n2x4( X_Y_Z_W... ) _x4( n2, X_Y_Z_W )
#define to_n2x2( X2 ) n2x2( X2.x, X2.y )
#define to_n2x3( X3 ) n2x3( X3.x, X3.y, X3.z )
#define to_n2x4( X4 ) n2x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( i2 );
#define i2x2( X_Y... ) _x2( i2, X_Y )
#define i2x3( X_Y_Z... ) _x3( i2, X_Y_Z )
#define i2x4( X_Y_Z_W... ) _x4( i2, X_Y_Z_W )
#define to_i2x2( X2 ) i2x2( X2.x, X2.y )
#define to_i2x3( X3 ) i2x3( X3.x, X3.y, X3.z )
#define to_i2x4( X4 ) i2x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( n4 );
#define n4x2( X_Y... ) _x2( n4, X_Y )
#define n4x3( X_Y_Z... ) _x3( n4, X_Y_Z )
#define n4x4( X_Y_Z_W... ) _x4( n4, X_Y_Z_W )
#define to_n4x2( X2 ) n4x2( X2.x, X2.y )
#define to_n4x3( X3 ) n4x3( X3.x, X3.y, X3.z )
#define to_n4x4( X4 ) n4x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( i4 );
#define i4x2( X_Y... ) _x2( i4, X_Y )
#define i4x3( X_Y_Z... ) _x3( i4, X_Y_Z )
#define i4x4( X_Y_Z_W... ) _x4( i4, X_Y_Z_W )
#define to_i4x2( X2 ) i4x2( X2.x, X2.y )
#define to_i4x3( X3 ) i4x3( X3.x, X3.y, X3.z )
#define to_i4x4( X4 ) i4x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( r4 );
_fn_rNx( 4 );
#define r4x2( X_Y... ) _x2( r4, X_Y )
#define r4x3( X_Y_Z... ) _x3( r4, X_Y_Z )
#define r4x4( X_Y_Z_W... ) _x4( r4, X_Y_Z_W )
#define to_r4x2( X2 ) r4x2( X2.x, X2.y )
#define to_r4x3( X3 ) r4x3( X3.x, X3.y, X3.z )
#define to_r4x4( X4 ) r4x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( n8 );
#define n8x2( X_Y... ) _x2( n8, X_Y )
#define n8x3( X_Y_Z... ) _x3( n8, X_Y_Z )
#define n8x4( X_Y_Z_W... ) _x4( n8, X_Y_Z_W )
#define to_n8x2( X2 ) n8x2( X2.x, X2.y )
#define to_n8x3( X3 ) n8x3( X3.x, X3.y, X3.z )
#define to_n8x4( X4 ) n8x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( i8 );
#define i8x2( X_Y... ) _x2( i8, X_Y )
#define i8x3( X_Y_Z... ) _x3( i8, X_Y_Z )
#define i8x4( X_Y_Z_W... ) _x4( i8, X_Y_Z_W )
#define to_i8x2( X2 ) i8x2( X2.x, X2.y )
#define to_i8x3( X3 ) i8x3( X3.x, X3.y, X3.z )
#define to_i8x4( X4 ) i8x4( X4.x, X4.y, X4.z, X4.w )

_fn_TYPEx( r8 );
_fn_rNx( 8 );
#define r8x2( X_Y... ) _x2( r8, X_Y )
#define r8x3( X_Y_Z... ) _x3( r8, X_Y_Z )
#define r8x4( X_Y_Z_W... ) _x4( r8, X_Y_Z_W )
#define to_r8x2( X2 ) r8x2( X2.x, X2.y )
#define to_r8x3( X3 ) r8x3( X3.x, X3.y, X3.z )
#define to_r8x4( X4 ) r8x4( X4.x, X4.y, X4.z, X4.w )

#pragma endregion dimensional
//

////////////////////////////////////////////////////////////////
#pragma region anchor

////////////////////////////////
// hidden

////////////////////////////////
// visible

embed i2 anchor_get_x( anchor const anchor, n2 const region_width, n2 const object_width, n2 const padding )
{
	temp n1 const h_align = anchor >> 4;
	temp i2 const offset = region_width - object_width;
	out pick( h_align is 1, offset >> 1, pick( h_align is 2, offset - padding, padding ) );
}

embed i2 anchor_get_y( anchor const anchor, n2 const region_height, n2 const object_height, n2 const padding )
{
	temp const n1 v_align = anchor & 0x0F;
	temp i2 const offset = region_height - object_height;
	out pick( v_align is 1, offset >> 1, pick( v_align is 2, offset - padding, padding ) );
}

#pragma endregion anchor
//

////////////////////////////////////////////////////////////////
#pragma region pixel

////////////////////////////////
// hidden

////////////////////////////////
// visible

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

#pragma endregion pixel
//

////////////////////////////////////////////////////////////////
#pragma region canvas

////////////////////////////////
// hidden

////////////////////////////////
// visible

perm flag const _MAKE_CANVAS_NEW_REF_FLAG;
perm pixel ref const _MAKE_CANVAS_NEW_REF = to( pixel ref const, ref_of( _MAKE_CANVAS_NEW_REF_FLAG ) );

embed canvas _make_canvas( n2 const width, n2 const height, pixel ref const pixels )
{
	temp n4 const area = n4( width ) * n4( height );
	temp pixel ref pixel_ref = pixels;
	if( pixels is _MAKE_CANVAS_NEW_REF )
	{
		pixel_ref = new_ref( pixel, area );
	}

	out make( canvas, .size = n2x2( width, height ), .area = area, .pixels = to( pixel ref, pixel_ref ) );
}
#define make_canvas( WIDTH, HEIGHT, PIXELS... ) _make_canvas( WIDTH, HEIGHT, DEFAULT( _MAKE_CANVAS_NEW_REF, PIXELS ) )

fn canvas_ref_wipe( canvas ref const canvas_ref )
{
	delete_ref( canvas_ref->pixels );
	val_of( canvas_ref ) = make( canvas );
}

fn _canvas_ref_resize( canvas ref const canvas_ref, n2 const width, n2 const height, flag const preserve )
{
	out_if( canvas_ref->size.w is width and canvas_ref->size.h is height );

	temp const n2x2 size_old = canvas_ref->size;
	temp n4 const area_old = canvas_ref->area;
	canvas_ref->size = n2x2( width, height );
	canvas_ref->area = n4( canvas_ref->size.w ) * n4( canvas_ref->size.h );

	out_if_nothing( canvas_ref->pixels );

	canvas_ref->pixels = ref_resize( canvas_ref->pixels, canvas_ref->area << pixel_bytes_shift, preserve );
}
#define canvas_ref_resize( CANVAS_REF, WIDTH, HEIGHT, PRESERVE... ) _canvas_ref_resize( CANVAS_REF, WIDTH, HEIGHT, DEFAULT( no, PRESERVE ) )

////////////////
// draw

fn canvas_ref_fill( canvas const ref const canvas_ref, pixel const color )
{
	if_all( color.r is color.g, color.g is color.b, color.b is color.a )
	{
		bytes_fill( canvas_ref->pixels, color.r, canvas_ref->area << pixel_bytes_shift );
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
			bytes_copy( ref_of( canvas_ref->pixels[ filled ] ), ref_of( canvas_ref->pixels[ 0 ] ), count << pixel_bytes_shift );
			filled += count;
			remaining -= count;
		}
		while( remaining );
	}
}

#define canvas_ref_clear( CANVAS ) bytes_clear( CANVAS->pixels, CANVAS->area << pixel_bytes_shift )

#define canvas_ref_check_pixel( CANVAS_REF, X, Y ) ( point_in_size( X, Y, CANVAS_REF->size.w, CANVAS_REF->size.h ) )
#define canvas_ref_check_pixel_index( CANVAS_REF, INDEX ) ( INDEX >= 0 and INDEX < CANVAS_REF->area )

#define canvas_ref_get_pixel_index( CANVAS_REF, INDEX ) CANVAS_REF->pixels[ ( INDEX ) ]
#define canvas_ref_get_pixel_index_safe( CANVAS_REF, INDEX ) pick( canvas_ref_check_pixel_index( CANVAS_REF, INDEX ), canvas_ref_get_pixel_index( CANVAS_REF, INDEX ), pixel_invalid )
#define canvas_ref_get_pixel( CANVAS_REF, X, Y ) canvas_ref_get_pixel_index( CANVAS_REF, grid_index( X, Y, CANVAS_REF->size.w ) )
#define canvas_ref_get_pixel_safe( CANVAS_REF, X, Y ) pick( canvas_ref_check_pixel( CANVAS_REF, X, Y ), canvas_ref_get_pixel( CANVAS_REF, X, Y ), pixel_invalid )

#define canvas_ref_draw_pixel_index( CANVAS_REF, INDEX, PIXEL ) ( canvas_ref_get_pixel_index( CANVAS_REF, INDEX ) ) = ( PIXEL )
#define canvas_ref_draw_pixel_index_safe( CANVAS_REF, INDEX, PIXEL ) if( canvas_ref_check_pixel_index( CANVAS_REF, INDEX ) ) canvas_ref_draw_pixel_index( CANVAS_REF, INDEX, PIXEL )
#define canvas_ref_draw_pixel( CANVAS_REF, X, Y, PIXEL ) ( canvas_ref_get_pixel( CANVAS_REF, X, Y ) ) = ( PIXEL )
#define canvas_ref_draw_pixel_safe( CANVAS_REF, X, Y, PIXEL ) if( canvas_ref_check_pixel( CANVAS_REF, X, Y ) ) canvas_ref_draw_pixel( CANVAS_REF, X, Y, PIXEL )

////////////////
// program canvas

#define draw_set_canvas_ref( CANVAS_REF ) program.canvas_ref = ( CANVAS_REF )

#define draw_fill( PIXEL ) canvas_ref_fill( program.canvas_ref, PIXEL )
#define draw_clear() canvas_ref_clear( program.canvas_ref )

#define check_pixel( X, Y ) canvas_ref_check_pixel( program.canvas_ref, X, Y )
#define check_pixel_index( INDEX ) canvas_ref_check_pixel_index( program.canvas_ref, INDEX )

#define get_pixel_index( INDEX ) canvas_ref_get_pixel_index( program.canvas_ref, INDEX )
#define get_pixel_index_safe( INDEX ) canvas_ref_get_pixel_index_safe( program.canvas_ref, INDEX )
#define get_pixel( X, Y ) canvas_ref_get_pixel( program.canvas_ref, X, Y )
#define get_pixel_safe( X, Y ) canvas_ref_get_pixel_safe( program.canvas_ref, X, Y )

#define draw_pixel_index( INDEX, PIXEL ) canvas_ref_draw_pixel_index( program.canvas_ref, INDEX, PIXEL )
#define draw_pixel_index_safe( INDEX, PIXEL ) canvas_ref_draw_pixel_index_safe( program.canvas_ref, INDEX, PIXEL )
#define draw_pixel( X, Y, PIXEL ) canvas_ref_draw_pixel( program.canvas_ref, X, Y, PIXEL )
#define draw_pixel_safe( X, Y, PIXEL ) canvas_ref_draw_pixel_safe( program.canvas_ref, X, Y, PIXEL )

#pragma endregion canvas
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region font

////////////////////////////////
// hidden

////////////////////////////////
// visible

embed font make_font( canvas const canvas )
{
	temp font this = { 0 };
	this.canvas = canvas;
	this.letter_size = n2x2( canvas.size.w >> 4, canvas.size.h >> 3 );
	out this;
}

#define _canvas_ref_blit_letter( CANVAS_REF, FONT, BYTE )\
	{\
		temp const byte _letter = ( BYTE ) - ' ';\
		temp const i2 _letter_x = ( _letter & 0x0F ) * _letter_w;\
		temp const i2 _letter_y = ( _letter >> 4 ) * _letter_h;\
		temp pixel ref _to_ref = CANVAS_REF->pixels + _draw_y * CANVAS_REF->size.w + _draw_x;\
		temp const pixel ref _from_ref = FONT.canvas.pixels + _letter_y * FONT.canvas.size.w + _letter_x;\
		temp i2 _h = _letter_h;\
		do\
		{\
			temp i2 _w = _letter_w;\
			do\
			{\
				if( _from_ref->a )\
				{\
					val_of( _to_ref ) = _color;\
				}\
				++_to_ref;\
				++_from_ref;\
			}\
			while( --_w );\
			_to_ref += _to_step;\
			_from_ref += _from_step;\
		}\
		while( --_h );\
	}

#define canvas_ref_draw_byte( CANVAS_REF, FONT, BYTE, POS, ANCHOR, COLOR )\
	START_DEF\
	{\
		temp const i2 _letter_w = FONT.letter_size.w;\
		temp const i2 _letter_h = FONT.letter_size.h;\
		temp anchor const _anchor = ANCHOR;\
		temp const i2 _draw_x = POS.x + anchor_get_x( _anchor, 0, _letter_w, 0 );\
		temp const i2 _draw_y = POS.y + anchor_get_y( _anchor, 0, _letter_h, 0 );\
		temp const pixel _color = COLOR;\
		temp const i4 _to_step = CANVAS_REF->size.w - _letter_w;\
		temp const i4 _from_step = FONT.canvas.size.w - _letter_w;\
		_canvas_ref_blit_letter( CANVAS_REF, FONT, BYTE )\
	}\
	END_DEF

#define canvas_ref_draw_bytes( CANVAS_REF, FONT, BYTES, BYTES_SIZE, POS, ANCHOR, COLOR )\
	START_DEF\
	{\
		temp const n2 _text_len = pick( BYTES_SIZE is 0, bytes_measure( BYTES ), BYTES_SIZE );\
		temp const i2 _letter_w = FONT.letter_size.w;\
		temp const i2 _letter_h = FONT.letter_size.h;\
		temp const i2 _text_width = _text_len * _letter_w;\
		temp anchor const _anchor = ANCHOR;\
		temp i2 _draw_x = POS.x + anchor_get_x( _anchor, 0, _text_width, 0 );\
		temp const i2 _draw_y = POS.y + anchor_get_y( _anchor, 0, _letter_h, 0 );\
		temp const pixel _color = COLOR;\
		temp const i4 _to_step = CANVAS_REF->size.w - _letter_w;\
		temp const i4 _from_step = FONT.canvas.size.w - _letter_w;\
		iter( _l, _text_len )\
		{\
			_canvas_ref_blit_letter( CANVAS_REF, FONT, BYTES[ _l ] ) _draw_x += _letter_w;\
		}\
	}\
	END_DEF

#define draw_byte( FONT_REF, BYTE, POS, ANCHOR, COLOR ) canvas_ref_draw_byte( program.canvas_ref, FONT_REF, BYTE, POS, ANCHOR, COLOR )
#define draw_bytes( FONT_REF, BYTES, BYTES_SIZE, POS, ANCHOR, COLOR ) canvas_ref_draw_bytes( program.canvas_ref, FONT_REF, BYTES, BYTES_SIZE, POS, ANCHOR, COLOR )

#pragma endregion font
//

////////////////////////////////////////////////////////////////
#pragma region view

////////////////////////////////
// hidden

fn _view_ref_setup( view ref const view_ref )
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

#define view_ref_get_scaled_size( VIEW_REF ) r4x2( r4( VIEW_REF->canvas.size.w ) * VIEW_REF->scale.w, r4( VIEW_REF->canvas.size.h ) * VIEW_REF->scale.h )

fn view_ref_zoom( view ref const view_ref, i4 const x, i4 const y, r4 const factor )
{
	temp r4 const new_scale = r4_clamp( view_ref->scale.w * factor, 0.1, 1000.0 );
	temp r4 const actual_factor = new_scale / view_ref->scale.w;
	view_ref->pos.x = r4( x ) - r4( x - view_ref->pos.x ) * actual_factor;
	view_ref->pos.y = r4( y ) - r4( y - view_ref->pos.y ) * actual_factor;
	view_ref->scale = r4x2( new_scale, new_scale );
}

fn view_ref_resize( view ref const view_ref, n2x2 const size, flag const preserve )
{
	out_if_any( view_ref is nothing, size.w is 0, size.h is 0 );

	if( view_ref->canvas.pixels is nothing )
	{
		view_ref->canvas = make_canvas( size.w, size.h );
	}
	else if( view_ref->canvas.size.w isnt size.w or view_ref->canvas.size.h isnt size.h )
	{
		canvas_ref_resize( ref_of( view_ref->canvas ), size.w, size.h, preserve );
	}

	#if OS_LINUX
		if( view_ref->pixmap )
		{
			XRenderFreePicture( program.display, view_ref->picture );
			XFreePixmap( program.display, view_ref->pixmap );
		}
	#endif

	_view_ref_setup( view_ref );
}

fn view_ref_center( view ref const view_ref, i2x2 const center_position )
{
	out_if_nothing( view_ref->canvas.pixels );
	view_ref->pos.x = r4( center_position.x ) - ( r4( view_ref->canvas.size.w ) * view_ref->scale.w * 0.5 );
	view_ref->pos.y = r4( center_position.y ) - ( r4( view_ref->canvas.size.h ) * view_ref->scale.h * 0.5 );
}

#pragma endregion view
//

////////////////////////////////////////////////////////////////
#pragma region display

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

#pragma endregion display
//

////////////////////////////////////////////////////////////////
#pragma region inputs

////////////////////////////////
// hidden

////////////////////////////////
// visible

#define input_to_byte( INPUT ) ( ( INPUT ) - input_a + 'A' )

#define key_pressed( WINDOW_REF, KEY ) ( ( ( WINDOW_REF )->inputs[ input_##KEY ] & INPUT_MASK_PRESSED ) isnt 0 )
#define key_held( WINDOW_REF, KEY ) ( ( ( WINDOW_REF )->inputs[ input_##KEY ] & INPUT_MASK_HELD ) isnt 0 )
#define key_released( WINDOW_REF, KEY ) ( ( ( WINDOW_REF )->inputs[ input_##KEY ] & INPUT_MASK_RELEASED ) isnt 0 )

#define mouse_pressed( WINDOW_REF, BUTTON ) key_pressed( WINDOW_REF, mouse_##BUTTON )
#define mouse_held( WINDOW_REF, BUTTON ) key_held( WINDOW_REF, mouse_##BUTTON )
#define mouse_released( WINDOW_REF, BUTTON ) key_released( WINDOW_REF, mouse_##BUTTON )

#define mouse_scroll( WINDOW_REF, DIRECTION ) key_pressed( WINDOW_REF, scroll_##DIRECTION )

#pragma endregion inputs
//

////////////////////////////////////////////////////////////////
#pragma region window

////////////////////////////////
// hidden

fn _window_ref_get_mouse_position( window ref const window_ref, i4 ref const out_x, i4 ref const out_y )
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

fn _window_ref_tick( window ref const window_ref )
{
	_window_ref_get_mouse_position( window_ref, ref_of( window_ref->mouse.x ), ref_of( window_ref->mouse.y ) );

	iter( view_index, window_ref->views_count )
	{
		temp view ref const this_view = ref_of( window_ref->views[ view_index ] );

		r4x2 new_mouse = r4x2( r4( window_ref->mouse.x - this_view->pos.x ) / this_view->scale.w, r4( window_ref->mouse.y - this_view->pos.y ) / this_view->scale.h );
		//this_view->mouse_prev = pick( window_ref->tick > 1, this_view->mouse, new_mouse );
		this_view->mouse = new_mouse;
	}

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

fn _window_ref_draw( window ref const window_ref )
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

		temp r4x2 const scaled_size = view_ref_get_scaled_size( view_ref );
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
				SetStretchBltMode( wdc, COLORONCOLOR ); //pick( scale_w <= 1.0 or scale_h <= 1.0, HALFTONE, COLORONCOLOR ) );
				SetBrushOrgEx( wdc, 0, 0, NULL );
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
	embed out_state _window_ref_process_event( window ref const window_ref, i4 const event, window_event const ref e )
#elif OS_WINDOWS
	embed LRESULT CALLBACK _window_ref_process_event( window_handle const h, i4 const event, WPARAM const wp, LPARAM const lp )
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
			_window_ref_draw( window_ref );

			#if OS_WINDOWS
				ValidateRect( h, nothing );
				out 0;
			#endif

			skip;
		}

		when( _window_event_focus_lost )
		{
			#if OS_LINUX
				malloc_trim( 0 );
			#elif OS_WINDOWS
				SetProcessWorkingSetSize( GetCurrentProcess(), to( SIZE_T, -1 ), to( SIZE_T, -1 ) );
			#endif

			iter( input_index, inputs_count )
			{
				if( window_ref->inputs[ input_index ] & INPUT_MASK_HELD )
				{
					_window_add_input_released( input_index );
				}
			}
			skip;
		}

		// inputs

		#ifndef C7H16_INPUT_NO_KEYBOARD
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
		#endif

		#ifndef C7H16_INPUT_NO_MOUSE
			when( _window_event_mouse_move )
			{
				#if OS_LINUX
					window_event next_move;
					while( XCheckTypedWindowEvent( program.display, window_ref->handle, MotionNotify, ref_of( next_move ) ) );
				#endif
				is_input = yes;
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
		_window_ref_tick( window_ref );
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

fn window_ref_update( window ref const window_ref )
{
	#if OS_LINUX
		XClearArea( program.display, window_ref->handle, 0, 0, 0, 0, yes );
	#elif OS_WINDOWS
		InvalidateRect( window_ref->handle, nothing, no );
	#endif
}

fn window_ref_show( window ref const window_ref )
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

embed view ref const window_ref_make_view_ref( window ref const window_ref, canvas const canvas, view_ref_fn const fn_draw )
{
	iter( view_id, window_max_views )
	{
		temp view ref const view_ref = ref_of( window_ref->views[ view_id ] );
		if( view_ref->state is view_state_unknown )
		{
			view_ref->scale = r4x2( 1.0, 1.0 );
			view_ref->state = view_state_visible;
			view_ref->canvas = canvas;
			view_ref->fn_draw = fn_draw;
			_view_ref_setup( view_ref );

			window_ref->views_count += 1;

			out view_ref;
		}
	}

	out nothing;
}

fn window_ref_capture_mouse( window ref const window_ref )
{
	#if OS_LINUX
		XGrabPointer( program.display, window_ref->handle, no, ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime );
	#elif OS_WINDOWS
		SetCapture( window_ref->handle );
	#endif
}

fn window_ref_release_mouse()
{
	#if OS_LINUX
		XUngrabPointer( program.display, CurrentTime );
	#elif OS_WINDOWS
		ReleaseCapture();
	#endif
}

fn window_ref_center( window ref const window_ref )
{
	#if OS_LINUX
		XMoveWindow( windows_display, window_ref->handle, ( display_get_width() - window_ref->size.w ) >> 1, ( display_get_height() - window_ref->size.h ) >> 1 );
		XSync( windows_display, no );
	#elif OS_WINDOWS
		SetWindowPos( window_ref->handle, nothing, ( display_get_width() - window_ref->size.w ) >> 1, ( display_get_height() - window_ref->size.h ) >> 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
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

fn window_ref_set_cursor( window ref const window_ref, cursor_type const cursor )
{
	//window_ref->changed_cursor = yes;
	#if OS_LINUX
		perm Cursor cache[ 256 ] = { 0 };
		if( not cache[ cursor ] )
		{
			cache[ cursor ] = XCreateFontCursor( windows_display, cursor );
		}
		XDefineCursor( windows_display, window_ref->handle, cache[ cursor ] );
	#elif OS_WINDOWS
		SetCursor( LoadCursor( NULL, MAKEINTRESOURCE( cursor ) ) );
	#endif
}

#pragma endregion window
//

////////////////////////////////////////////////////////////////
#pragma region program

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

		iter( window_id, program_max_windows )
		{
			temp window ref const window_ref = ref_of( program.windows[ window_id ] );

			if( window_ref->state is window_state_unknown ) next;

			with( window_ref->state )
			{
				when( window_state_preparing )
				{
					window_ref_center( window_ref );
					call( window_ref->fn_start, window_ref );
					window_ref->state = window_state_opening;
					ready = no;
					skip;
				}

				when( window_state_opening )
				{
					window_ref_show( window_ref );
					window_ref->state = window_state_ready;
					skip;
				}

				when( window_state_closing )
				{
					program.windows_count -= 1;
					window_ref->state = window_state_unknown;
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

fn program_set_canvas_ref( canvas const ref const canvas_ref )
{
	program.canvas_ref = canvas_ref;
}

embed window ref const program_make_window_ref( byte const ref const name, n2x2 const size, window_ref_fn const fn_start, window_ref_fn const fn_resize, window_ref_fn const fn_tick )
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
	window_ref->fn_start = fn_start;
	window_ref->fn_resize = fn_resize;
	window_ref->fn_tick = fn_tick;

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
		wclass.lpfnWndProc = to( type_of( wclass.lpfnWndProc ), _window_ref_process_event );
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

#pragma endregion program
//

#pragma endregion definitions
///

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
