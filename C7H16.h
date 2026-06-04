////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Heptane Renderer (C7H16)
//
//  author(s):
//  ENDESGA - https://twitter.com/ENDESGA | https://bsky.app/profile/endesga.bsky.social
//
//  https://github.com/H-language/C7H16
//  2026 - CC0 - FOSS forever
//

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - DEPENDENCIES
//

#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#if __linux__
	#include <poll.h>
	#include <malloc.h>
	#include <time.h>
	#include <X11/extensions/Xrender.h>
	#include <X11/XKBlib.h>
	#include <X11/cursorfont.h>
#endif

#include <H.h>

#if OS_WINDOWS and not defined( _TIMERAPI_H_ ) and not defined( _INC_MMSYSTEM )
	__declspec( dllimport ) n4 __stdcall timeBeginPeriod( n4 uPeriod );
#endif

#pragma endregion dependencies

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - MACROS
//

////////////////////////////////////////////////////////////////
#pragma region - input config

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

#pragma endregion input config

#pragma endregion macros

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - CONSTANTS
//

#define C7H16_NAME "C7H16"

////////////////////////////////////////////////////////////////
#pragma region - version

#define C7H16_VERSION_MAJOR 0
#define C7H16_VERSION_MINOR 1
#define C7H16_VERSION_PATCH 0
#define C7H16_VERSION_COMMIT 0
#define C7H16_VERSION AS_BYTES( C7H16_VERSION_MAJOR ) "." AS_BYTES( C7H16_VERSION_MINOR ) "." AS_BYTES( C7H16_VERSION_PATCH ) "-" AS_BYTES( C7H16_VERSION_COMMIT )

#pragma endregion version

////////////////////////////////////////////////////////////////
#pragma region - program

#ifndef program_max_windows
	#define program_max_windows 1
#endif

#pragma endregion program

////////////////////////////////////////////////////////////////
#pragma region - window

#ifndef window_max_name_size
	#define window_max_name_size path_max_size
#endif

#ifndef window_max_views
	#define window_max_views 1
#endif

#ifndef window_max_inputs
	#define window_max_inputs 8
#endif

#pragma endregion window

#pragma endregion constants

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - DECLARATIONS
//

////////////////////////////////////////////////////////////////
#pragma region - dimensional

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
			TYPE##x2 xy;\
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
			TYPE##x3 xyz;\
		};\
		variant\
		{\
			TYPE##x2 xy;\
			TYPE##x2 zw;\
		};\
		variant\
		{\
			TYPE r;\
			TYPE g;\
			TYPE b;\
			TYPE a;\
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

////////////////////////////////////////////////////////////////
#pragma region - anchor

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

////////////////////////////////////////////////////////////////
#pragma region - pixel

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

#define pixel_channel_bits 8
#define pixel_bytes_shift 2

#pragma endregion pixel

////////////////////////////////////////////////////////////////
#pragma region - canvas

type( canvas )
{
	pixel ref pixels;
	n2x2 size;
	n4 area;
};

#pragma endregion canvas

////////////////////////////////////////////////////////////////
#pragma region - font

type( font )
{
	canvas canvas;
	n2x2 letter_size;
};

#pragma endregion font

////////////////////////////////////////////////////////////////
#pragma region - nano

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

#pragma endregion nano

////////////////////////////////////////////////////////////////
#pragma region - inputs

group( input_type )
{
	input_none,

	#ifndef C7H16_INPUT_NO_MOUSE
		mouse_left,
		mouse_middle,
		mouse_right,
		mouse_wheel_up,
		mouse_wheel_down,
		mouse_wheel_left,
		mouse_wheel_right,
	#endif

	#ifndef C7H16_INPUT_NO_LETTERS
		keyboard_a,
		keyboard_b,
		keyboard_c,
		keyboard_d,
		keyboard_e,
		keyboard_f,
		keyboard_g,
		keyboard_h,
		keyboard_i,
		keyboard_j,
		keyboard_k,
		keyboard_l,
		keyboard_m,
		keyboard_n,
		keyboard_o,
		keyboard_p,
		keyboard_q,
		keyboard_r,
		keyboard_s,
		keyboard_t,
		keyboard_u,
		keyboard_v,
		keyboard_w,
		keyboard_x,
		keyboard_y,
		keyboard_z,
	#endif

	#ifndef C7H16_INPUT_NO_NUMBERS
		keyboard_0,
		keyboard_1,
		keyboard_2,
		keyboard_3,
		keyboard_4,
		keyboard_5,
		keyboard_6,
		keyboard_7,
		keyboard_8,
		keyboard_9,
	#endif

	#ifndef C7H16_INPUT_NO_SYMBOLS
		keyboard_backtick,
		keyboard_minus,
		keyboard_equals,
		keyboard_leftbracket,
		keyboard_rightbracket,
		keyboard_backslash,
		keyboard_semicolon,
		keyboard_apostrophe,
		keyboard_comma,
		keyboard_period,
		keyboard_slash,
		keyboard_space,
		keyboard_tab,
	#endif

	#ifndef C7H16_INPUT_NO_FUNCTIONS
		keyboard_f1,
		keyboard_f2,
		keyboard_f3,
		keyboard_f4,
		keyboard_f5,
		keyboard_f6,
		keyboard_f7,
		keyboard_f8,
		keyboard_f9,
		keyboard_f10,
		keyboard_f11,
		keyboard_f12,
	#endif

	#ifndef C7H16_INPUT_NO_MODIFIERS
		keyboard_shift,
		keyboard_ctrl,
		keyboard_alt,
		keyboard_super,
	#endif

	#ifndef C7H16_INPUT_NO_ARROWS
		keyboard_up,
		keyboard_down,
		keyboard_left,
		keyboard_right,
	#endif

	#ifndef C7H16_INPUT_NO_CONTROLS
		keyboard_escape,
		keyboard_capslock,
		keyboard_enter,
		keyboard_backspace,
		keyboard_insert,
		keyboard_delete,
		keyboard_home,
		keyboard_end,
		keyboard_pageup,
		keyboard_pagedown,
		keyboard_menu,
	#endif

	inputs_count
};

#define INPUT_MASK_PRESSED 0x1
#define INPUT_MASK_HELD 0x2
#define INPUT_MASK_RELEASED 0x4

#pragma endregion inputs

////////////////////////////////////////////////////////////////
#pragma region - view

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

////////////////////////////////////////////////////////////////
#pragma region - window

type_from( OS_PICK( Window, HWND ) ) window_handle;
type_from( OS_PICK( XImage ref, BITMAPINFO ) ) window_image;
type_from( OS_PICK( XEvent, MSG ) ) window_event;

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
		WINDOWPLACEMENT prev_placement;
	#endif

	window_ref_fn fn_resize;
	window_ref_fn fn_tick;

	view views[ window_max_views ];

	n1 inputs[ inputs_count ];
	n1 inputs_pressed[ window_max_inputs ];
	n1 inputs_released[ window_max_inputs ];
	byte input_bytes[ window_max_inputs ];
	i4x2 mouse;

	window_state state bits( window_states_count );
	n1 views_count bits( window_max_views );
	n1 inputs_pressed_count bits( window_max_inputs );
	n1 inputs_released_count bits( window_max_inputs );
	n1 input_bytes_count bits( window_max_inputs );
	flag visible bits_flag;
	flag fullscreen bits_flag;
	flag call_tick bits_flag;
	flag changed_cursor bits_flag;
};

////////////////////////////////
#pragma region | window / cursor

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

#pragma endregion cursor

#pragma endregion window

////////////////////////////////////////////////////////////////
#pragma region - program

global
{
	byte path[ path_max_size ];

	#if OS_LINUX
		Display ref display;
		Visual ref visual;
		XRenderPictFormat ref format;
	#elif OS_WINDOWS
		HINSTANCE instance;
		HICON icon;
	#endif

	window windows[ program_max_windows ];

	canvas ref current_canvas_ref;
	window ref current_window_ref;

	r8 fps;
	nano next_tick;
	nano epoch;
	n8 tick_count;

	n1 windows_count bits( program_max_windows );
	n1 resizing bits( 3 );
	flag tick_events bits_flag;
}
program;

#pragma endregion program

#pragma endregion declarations

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - DEFINITIONS
//

////////////////////////////////////////////////////////////////
#pragma region - dimensional

////////////////////////////////
#pragma region | dimensional / hidden

////////////////
#pragma region | - creation

#define _x2( TYPE, X_Y... ) make( TYPE##x2, DEFAULTS( ( 0, 0 ), X_Y ) )
#define _x3( TYPE, X_Y_Z... ) make( TYPE##x3, DEFAULTS( ( 0, 0, 0 ), X_Y_Z ) )
#define _x4( TYPE, X_Y_Z_W... ) make( TYPE##x4, DEFAULTS( ( 0, 0, 0, 0 ), X_Y_Z_W ) )

#pragma endregion

////////////////
#pragma region | - operations

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

#pragma endregion

#pragma endregion hidden

////////////////////////////////
#pragma region | dimensional / visible

////////////////
#pragma region | - creation

#define n1x2( X_Y... ) _x2( n1, X_Y )
#define n1x3( X_Y_Z... ) _x3( n1, X_Y_Z )
#define n1x4( X_Y_Z_W... ) _x4( n1, X_Y_Z_W )
#define to_n1x2( X2 ) n1x2( X2.x, X2.y )
#define to_n1x3( X3 ) n1x3( X3.x, X3.y, X3.z )
#define to_n1x4( X4 ) n1x4( X4.x, X4.y, X4.z, X4.w )

#define i1x2( X_Y... ) _x2( i1, X_Y )
#define i1x3( X_Y_Z... ) _x3( i1, X_Y_Z )
#define i1x4( X_Y_Z_W... ) _x4( i1, X_Y_Z_W )
#define to_i1x2( X2 ) i1x2( X2.x, X2.y )
#define to_i1x3( X3 ) i1x3( X3.x, X3.y, X3.z )
#define to_i1x4( X4 ) i1x4( X4.x, X4.y, X4.z, X4.w )

#define n2x2( X_Y... ) _x2( n2, X_Y )
#define n2x3( X_Y_Z... ) _x3( n2, X_Y_Z )
#define n2x4( X_Y_Z_W... ) _x4( n2, X_Y_Z_W )
#define to_n2x2( X2 ) n2x2( X2.x, X2.y )
#define to_n2x3( X3 ) n2x3( X3.x, X3.y, X3.z )
#define to_n2x4( X4 ) n2x4( X4.x, X4.y, X4.z, X4.w )

#define i2x2( X_Y... ) _x2( i2, X_Y )
#define i2x3( X_Y_Z... ) _x3( i2, X_Y_Z )
#define i2x4( X_Y_Z_W... ) _x4( i2, X_Y_Z_W )
#define to_i2x2( X2 ) i2x2( X2.x, X2.y )
#define to_i2x3( X3 ) i2x3( X3.x, X3.y, X3.z )
#define to_i2x4( X4 ) i2x4( X4.x, X4.y, X4.z, X4.w )

#define n4x2( X_Y... ) _x2( n4, X_Y )
#define n4x3( X_Y_Z... ) _x3( n4, X_Y_Z )
#define n4x4( X_Y_Z_W... ) _x4( n4, X_Y_Z_W )
#define to_n4x2( X2 ) n4x2( X2.x, X2.y )
#define to_n4x3( X3 ) n4x3( X3.x, X3.y, X3.z )
#define to_n4x4( X4 ) n4x4( X4.x, X4.y, X4.z, X4.w )

#define i4x2( X_Y... ) _x2( i4, X_Y )
#define i4x3( X_Y_Z... ) _x3( i4, X_Y_Z )
#define i4x4( X_Y_Z_W... ) _x4( i4, X_Y_Z_W )
#define to_i4x2( X2 ) i4x2( X2.x, X2.y )
#define to_i4x3( X3 ) i4x3( X3.x, X3.y, X3.z )
#define to_i4x4( X4 ) i4x4( X4.x, X4.y, X4.z, X4.w )

#define r4x2( X_Y... ) _x2( r4, X_Y )
#define r4x3( X_Y_Z... ) _x3( r4, X_Y_Z )
#define r4x4( X_Y_Z_W... ) _x4( r4, X_Y_Z_W )
#define to_r4x2( X2 ) r4x2( X2.x, X2.y )
#define to_r4x3( X3 ) r4x3( X3.x, X3.y, X3.z )
#define to_r4x4( X4 ) r4x4( X4.x, X4.y, X4.z, X4.w )

#define n8x2( X_Y... ) _x2( n8, X_Y )
#define n8x3( X_Y_Z... ) _x3( n8, X_Y_Z )
#define n8x4( X_Y_Z_W... ) _x4( n8, X_Y_Z_W )
#define to_n8x2( X2 ) n8x2( X2.x, X2.y )
#define to_n8x3( X3 ) n8x3( X3.x, X3.y, X3.z )
#define to_n8x4( X4 ) n8x4( X4.x, X4.y, X4.z, X4.w )

#define i8x2( X_Y... ) _x2( i8, X_Y )
#define i8x3( X_Y_Z... ) _x3( i8, X_Y_Z )
#define i8x4( X_Y_Z_W... ) _x4( i8, X_Y_Z_W )
#define to_i8x2( X2 ) i8x2( X2.x, X2.y )
#define to_i8x3( X3 ) i8x3( X3.x, X3.y, X3.z )
#define to_i8x4( X4 ) i8x4( X4.x, X4.y, X4.z, X4.w )

#define r8x2( X_Y... ) _x2( r8, X_Y )
#define r8x3( X_Y_Z... ) _x3( r8, X_Y_Z )
#define r8x4( X_Y_Z_W... ) _x4( r8, X_Y_Z_W )
#define to_r8x2( X2 ) r8x2( X2.x, X2.y )
#define to_r8x3( X3 ) r8x3( X3.x, X3.y, X3.z )
#define to_r8x4( X4 ) r8x4( X4.x, X4.y, X4.z, X4.w )

#pragma endregion

////////////////
#pragma region | - operations

_fn_TYPEx( n1 );
_fn_TYPEx( i1 );

_fn_TYPEx( n2 );
_fn_TYPEx( i2 );

_fn_TYPEx( n4 );
_fn_TYPEx( i4 );
_fn_TYPEx( r4 );
_fn_rNx( 4 );

_fn_TYPEx( n8 );
_fn_TYPEx( i8 );
_fn_TYPEx( r8 );
_fn_rNx( 8 );

#pragma endregion

////////////////
#pragma region | - logic

#define point_in_size( X, Y, W, H ) all( X >= 0, Y >= 0, X < W, Y < H )
#define point_not_in_size( X, Y, W, H ) any( X < 0, Y < 0, X >= W, Y >= H )

#define point_in_range( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) all( X >= TOPLEFT_X, Y >= TOPLEFT_Y, X <= BOTTOMRIGHT_X, Y <= BOTTOMRIGHT_Y )
#define point_not_in_range( X, Y, TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y ) any( X < TOPLEFT_X, Y < TOPLEFT_Y, X > BOTTOMRIGHT_X, Y > BOTTOMRIGHT_Y )

#define range_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) all( point_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )
#define range_not_in_size( TOPLEFT_X, TOPLEFT_Y, BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) any( point_not_in_size( TOPLEFT_X, TOPLEFT_Y, W, H ), point_not_in_size( BOTTOMRIGHT_X, BOTTOMRIGHT_Y, W, H ) )

#define range_in_range( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) all( point_in_range( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_in_range( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )
#define range_not_in_range( TL1_X, TL1_Y, BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) any( point_not_in_range( TL1_X, TL1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ), point_not_in_range( BR1_X, BR1_Y, TL2_X, TL2_Y, BR2_X, BR2_Y ) )

#pragma endregion

#pragma endregion visible

#pragma endregion dimensional

////////////////////////////////////////////////////////////////
#pragma region - anchor

////////////////////////////////
#pragma region | anchor / visible

embed i2 anchor_get_x( anchor const anchor, n2 const region_width, n2 const object_width, n2 const padding )
{
	n1 const h_align = anchor >> 4;
	i2 const offset = region_width - object_width;
	out pick( h_align is 1, offset >> 1, pick( h_align is 2, offset - padding, padding ) );
}

embed i2 anchor_get_y( anchor const anchor, n2 const region_height, n2 const object_height, n2 const padding )
{
	const n1 v_align = anchor & 0x0F;
	i2 const offset = region_height - object_height;
	out pick( v_align is 1, offset >> 1, pick( v_align is 2, offset - padding, padding ) );
}

#pragma endregion visible

#pragma endregion anchor

////////////////////////////////////////////////////////////////
#pragma region - pixel

////////////////////////////////
#pragma region | pixel / hidden

#define _pixel_ref_set( PIXEL_REF, PIXEL ) val_of( PIXEL_REF ) = PIXEL

#define _pixel_bgra_avg( A, B ) ( ( ( ( A ) & 0xfefefefe ) >> 1 ) + ( ( ( B ) & 0xfefefefe ) >> 1 ) )
#define _pixel_channel_blend( TO, FROM, FROM_ALPHA, INV_FROM_ALPHA ) n1( ( n2( FROM ) * ( FROM_ALPHA ) + n2( TO ) * ( INV_FROM_ALPHA ) + 127 ) >> pixel_channel_bits )

#define _pixel_channel_add( TO, FROM ) n1( n2_min( n2( TO ) + n2( FROM ), n1_max_val ) )
#define _pixel_channel_sub( TO, FROM ) pick( ( TO ) <= ( FROM ), n1_min_val, ( TO ) - ( FROM ) )

#define _pixel_channel_mul( TO, FROM ) n1( ( n2( TO ) * n2( FROM ) + 127 ) >> pixel_channel_bits )
#define _pixel_channel_screen( TO, FROM ) n1( n1_max_val - ( ( ( n2( n1_max_val ) - n2( TO ) ) * ( n2( n1_max_val ) - n2( FROM ) ) + 127 ) >> pixel_channel_bits ) )

#define _pixel_channel_lighten( TO, FROM ) pick( ( TO ) >= ( FROM ), TO, FROM )
#define _pixel_channel_darken( TO, FROM ) pick( ( TO ) <= ( FROM ), TO, FROM )

#define _pixel_channel_dodge( TO, FROM ) pick( ( FROM ) >= n1_max_val, n1_max_val, n1( n2_min( ( n2( TO ) * n2( n1_max_val ) + ( ( n2( n1_max_val ) - n2( FROM ) ) >> 1 ) ) / ( n2( n1_max_val ) - n2( FROM ) ), n2( n1_max_val ) ) ) )
#define _pixel_channel_burn( TO, FROM ) pick( ( FROM ) is 0, n1_min_val, n1( n1_max_val - n2_min( ( ( n2( n1_max_val ) - n2( TO ) ) * n2( n1_max_val ) + ( n2( FROM ) >> 1 ) ) / n2( FROM ), n2( n1_max_val ) ) ) )

#define _pixel_channel_inv( TO, FROM ) pick( ( TO ) >= ( FROM ), n1( ( TO ) - ( FROM ) ), n1( ( FROM ) - ( TO ) ) )

#define _pixel_ref_rgb_operation( TO_R, TO_G, TO_B, MODE, PIXEL_REF, PIXEL )\
	TO_R = _pixel_channel_##MODE( PIXEL_REF->r, PIXEL.r );\
	TO_G = _pixel_channel_##MODE( PIXEL_REF->g, PIXEL.g );\
	TO_B = _pixel_channel_##MODE( PIXEL_REF->b, PIXEL.b )

#define _pixel_ref_operation( PIXEL_REF, PIXEL, MODE )\
	START_DEF\
	{\
		_pixel_ref_rgb_operation( PIXEL_REF->r, PIXEL_REF->g, PIXEL_REF->b, MODE, PIXEL_REF, PIXEL );\
	}\
	END_DEF

#define _pixel_ref_alpha_blend( PIXEL_REF, R, G, B, A )\
	n2 const _inv_alpha = n1_max_val - A;\
	PIXEL_REF->r = _pixel_channel_blend( PIXEL_REF->r, R, A, _inv_alpha );\
	PIXEL_REF->g = _pixel_channel_blend( PIXEL_REF->g, G, A, _inv_alpha );\
	PIXEL_REF->b = _pixel_channel_blend( PIXEL_REF->b, B, A, _inv_alpha );\
	PIXEL_REF->a = n1( A + ( ( n2( PIXEL_REF->a ) * _inv_alpha + 127 ) >> pixel_channel_bits ) )

#define _pixel_ref_blend( PIXEL_REF, PIXEL )\
	START_DEF\
	{\
		n2 const _PIXEL_a = PIXEL.a;\
		skip_if( _PIXEL_a is 0 );\
		if( _PIXEL_a is n1_max_val or PIXEL_REF->a is 0 )\
		{\
			_pixel_ref_set( PIXEL_REF, PIXEL );\
		}\
		else\
		{\
			_pixel_ref_alpha_blend( PIXEL_REF, PIXEL.r, PIXEL.g, PIXEL.b, _PIXEL_a );\
		}\
	}\
	END_DEF

#define _pixel_ref_behind( PIXEL_REF, PIXEL )\
	START_DEF\
	{\
		skip_if( PIXEL.a is 0 or PIXEL_REF->a is n1_max_val );\
		if( PIXEL_REF->a is 0 )\
		{\
			_pixel_ref_set( PIXEL_REF, PIXEL );\
		}\
		else\
		{\
			n2 const _DST_a = PIXEL_REF->a;\
			n2 const _inv = n1_max_val - _DST_a;\
			PIXEL_REF->r = _pixel_channel_blend( PIXEL.r, PIXEL_REF->r, _DST_a, _inv );\
			PIXEL_REF->g = _pixel_channel_blend( PIXEL.g, PIXEL_REF->g, _DST_a, _inv );\
			PIXEL_REF->b = _pixel_channel_blend( PIXEL.b, PIXEL_REF->b, _DST_a, _inv );\
			PIXEL_REF->a = n1( _DST_a + ( ( n2( PIXEL.a ) * _inv + 127 ) >> pixel_channel_bits ) );\
		}\
	}\
	END_DEF

#define _pixel_ref_avg( PIXEL_REF, PIXEL )\
	START_DEF\
	{\
		PIXEL_REF->bgra = _pixel_bgra_avg( PIXEL_REF->bgra, PIXEL.bgra );\
	}\
	END_DEF

#define _pixel_ref_add( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, add )
#define _pixel_ref_sub( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, sub )

#define _pixel_ref_mul( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, mul )
#define _pixel_ref_screen( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, screen )

#define _pixel_ref_lighten( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, lighten )
#define _pixel_ref_darken( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, darken )

#define _pixel_ref_dodge( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, dodge )
#define _pixel_ref_burn( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, burn )

#define _pixel_ref_inv( PIXEL_REF, PIXEL ) _pixel_ref_operation( PIXEL_REF, PIXEL, inv )

#define _pixel_ref_mask( PIXEL_REF, PIXEL )\
	START_DEF\
	{\
		n2 const _SRC_a = PIXEL.a;\
		n2 const _DST_a = PIXEL_REF->a;\
		skip_if( _SRC_a is 0 or _DST_a is 0 );\
		if( _DST_a is n1_max_val and _SRC_a is n1_max_val )\
		{\
			PIXEL_REF->r = PIXEL.r;\
			PIXEL_REF->g = PIXEL.g;\
			PIXEL_REF->b = PIXEL.b;\
		}\
		else\
		{\
			n2 const _eff_a = ( _SRC_a * _DST_a + 127 ) >> pixel_channel_bits;\
			n2 const _inv = n1_max_val - _eff_a;\
			PIXEL_REF->r = _pixel_channel_blend( PIXEL_REF->r, PIXEL.r, _eff_a, _inv );\
			PIXEL_REF->g = _pixel_channel_blend( PIXEL_REF->g, PIXEL.g, _eff_a, _inv );\
			PIXEL_REF->b = _pixel_channel_blend( PIXEL_REF->b, PIXEL.b, _eff_a, _inv );\
		}\
	}\
	END_DEF

#define _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, MODE )\
	START_DEF\
	{\
		n2 const _PIXEL_a = PIXEL.a;\
		skip_if( _PIXEL_a is 0 );\
		if( PIXEL_REF->a is 0 )\
		{\
			_pixel_ref_set( PIXEL_REF, PIXEL );\
		}\
		else if( _PIXEL_a is n1_max_val )\
		{\
			_pixel_ref_##MODE( PIXEL_REF, PIXEL );\
			PIXEL_REF->a = n1_max_val;\
		}\
		else\
		{\
			_pixel_ref_rgb_operation( n1 const _r, n1 const _g, n1 const _b, MODE, PIXEL_REF, PIXEL );\
			_pixel_ref_alpha_blend( PIXEL_REF, _r, _g, _b, _PIXEL_a );\
		}\
	}\
	END_DEF

#define _pixel_ref_avg_alpha( PIXEL_REF, PIXEL )\
	START_DEF\
	{\
		n2 const _PIXEL_a = PIXEL.a;\
		skip_if( _PIXEL_a is 0 );\
		if( PIXEL_REF->a is 0 )\
		{\
			_pixel_ref_set( PIXEL_REF, PIXEL );\
		}\
		else if( _PIXEL_a is n1_max_val )\
		{\
			PIXEL_REF->bgra = _pixel_bgra_avg( PIXEL_REF->bgra, PIXEL.bgra );\
		}\
		else\
		{\
			pixel const _avg = make( pixel, .bgra = _pixel_bgra_avg( PIXEL_REF->bgra, PIXEL.bgra ) );\
			_pixel_ref_alpha_blend( PIXEL_REF, _avg.r, _avg.g, _avg.b, _PIXEL_a );\
		}\
	}\
	END_DEF

#define _pixel_ref_add_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, add )
#define _pixel_ref_sub_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, sub )

#define _pixel_ref_mul_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, mul )
#define _pixel_ref_screen_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, screen )

#define _pixel_ref_lighten_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, lighten )
#define _pixel_ref_darken_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, darken )

#define _pixel_ref_dodge_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, dodge )
#define _pixel_ref_burn_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, burn )

#define _pixel_ref_inv_alpha( PIXEL_REF, PIXEL ) _pixel_ref_operation_alpha( PIXEL_REF, PIXEL, inv )

#pragma endregion hidden

////////////////////////////////
#pragma region | pixel / visible

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

#pragma endregion visible

#pragma endregion pixel

////////////////////////////////////////////////////////////////
#pragma region - canvas

////////////////////////////////
#pragma region | canvas / hidden

////////////////
#pragma region | - utility

#define array_index( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

#pragma endregion

////////////////
#pragma region | - creation

perm flag const _MAKE_CANVAS_NEW_REF_FLAG;
perm pixel ref const _MAKE_CANVAS_NEW_REF = to( pixel ref const, ref_of( _MAKE_CANVAS_NEW_REF_FLAG ) );

embed canvas _make_canvas( n2 const width, n2 const height, pixel ref const pixels )
{
	n4 const area = n4( width ) * n4( height );
	pixel ref pixel_ref = pixels;
	if( pixels is _MAKE_CANVAS_NEW_REF )
	{
		pixel_ref = os_create_ref( pixel, area );
	}

	out make( canvas, .size = n2x2( width, height ), .area = area, .pixels = to( pixel ref, pixel_ref ) );
}

#pragma endregion

////////////////
#pragma region | - operations

fn _canvas_ref_resize( canvas ref const canvas_ref, n2 const width, n2 const height, flag const preserve )
{
	out_if( canvas_ref->size.w is width and canvas_ref->size.h is height );

	canvas_ref->size = n2x2( width, height );
	canvas_ref->area = n4( canvas_ref->size.w ) * n4( canvas_ref->size.h );

	out_if_nothing( canvas_ref->pixels );

	canvas_ref->pixels = os_resize_ref( canvas_ref->pixels, canvas_ref->area << pixel_bytes_shift, preserve );
}

#pragma endregion

////////////////
#pragma region | - get pixel

#define _canvas_ref_get_pixel_index( CANVAS_REF, INDEX ) CANVAS_REF->pixels[ ( INDEX ) ]
#define _canvas_ref_get_pixel( CANVAS_REF, X, Y ) _canvas_ref_get_pixel_index( CANVAS_REF, array_index( X, Y, CANVAS_REF->size.w ) )

#pragma endregion

////////////////
#pragma region | - draw pixel

#define _canvas_ref_draw_pixel_index( CANVAS_REF, INDEX, PIXEL, MODE... )\
	START_DEF\
	{\
		pixel const _PIXEL = PIXEL;\
		pixel ref const _p = ref_of( _canvas_ref_get_pixel_index( CANVAS_REF, INDEX ) );\
		_pixel_ref_##MODE( _p, _PIXEL );\
	}\
	END_DEF

#define _canvas_ref_draw_pixel( CANVAS_REF, X, Y, PIXEL, MODE... )\
	START_DEF\
	{\
		pixel const _PIXEL = PIXEL;\
		pixel ref const _p = ref_of( _canvas_ref_get_pixel( CANVAS_REF, X, Y ) );\
		_pixel_ref_##MODE( _p, _PIXEL );\
	}\
	END_DEF

#pragma endregion

////////////////
#pragma region | - set canvas

#define _canvas_ref_to_setup( TO_REF, TLx, TLy, W, H )\
	i2 const _to_x = ( TLx );\
	i2 const _to_y = ( TLy );\
	i2 const _W = ( W );\
	i2 const _H = ( H );\
	pixel ref _to_ref = TO_REF->pixels + _to_y * TO_REF->size.w + _to_x

#define _canvas_ref_copy_loop( TO_REF, FROM_STEP, COUNT )\
	n4 const _bytes_per_row = _W << pixel_bytes_shift;\
	i4 const _to_step = TO_REF->size.w;\
	i4 const _from_step = ( FROM_STEP );\
	i2 _h = ( COUNT );\
	if( _h ) do\
	{\
		bytes_copy( _to_ref, _from_ref, _bytes_per_row );\
		_to_ref += _to_step;\
		_from_ref += _from_step;\
	}\
	while( --_h )

#define _canvas_ref_set_canvas_setup( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	i4 const _from_w = FROM.size.w;\
	_canvas_ref_to_setup( TO_REF, TLx, TLy, PART_SIZEw, PART_SIZEh );\
	pixel const ref _from_ref = FROM.pixels + ( PART_TLy ) * _from_w + ( PART_TLx )

#define _canvas_ref_set_canvas_setup_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	i4 const _from_w = FROM.size.w;\
	i2 const _TLx = ( TLx );\
	i2 const _to_x = MAX( 0, _TLx );\
	i2 const _offset_x = _to_x - _TLx;\
	i2 const _from_x = ( PART_TLx ) + _offset_x;\
	i2 const _W = i2_min3( TO_REF->size.w - _to_x, _from_w - _from_x, ( PART_SIZEw ) - _offset_x );\
	skip_if( _W <= 0 );\
	i2 const _TLy = ( TLy );\
	i2 const _to_y = MAX( 0, _TLy );\
	i2 const _offset_y = _to_y - _TLy;\
	i2 const _from_y = ( PART_TLy ) + _offset_y;\
	i2 const _H = i2_min3( TO_REF->size.h - _to_y, FROM.size.h - _from_y, ( PART_SIZEh ) - _offset_y );\
	skip_if( _H <= 0 );\
	pixel ref _to_ref = TO_REF->pixels + _to_y * TO_REF->size.w + _to_x;\
	pixel const ref _from_ref = FROM.pixels + _from_y * _from_w + _from_x

#define _canvas_ref_set_canvas_loop_per( TO_REF, CODE... )\
	i4 const _to_step = TO_REF->size.w - _W;\
	i4 const _from_step = _from_w - _W;\
	i2 _h = _H;\
	do\
	{\
		i2 _w = _W;\
		do\
		{\
			CODE;\
			++_to_ref;\
			++_from_ref;\
		}\
		while( --_w );\
		_to_ref += _to_step;\
		_from_ref += _from_step;\
	}\
	while( --_h )

#define _canvas_ref_set_canvas_loop_trans( TO_REF ) _canvas_ref_set_canvas_loop_per( TO_REF, if( _from_ref->a ) val_of( _to_ref ) = val_of( _from_ref ); )

#pragma endregion

////////////////
#pragma region | - fill canvas

#define _canvas_ref_fill_area_setup( TO_REF, TLx, TLy, BRx, BRy )\
	_canvas_ref_to_setup( TO_REF, TLx, TLy, ( BRx ) - ( TLx ) + 1, ( BRy ) - ( TLy ) + 1 )

#define _canvas_ref_fill_area_setup_safe( TO_REF, TLx, TLy, BRx, BRy )\
	i2 const _to_x = MAX( 0, ( TLx ) );\
	i2 const _W = i2_min2( TO_REF->size.w - _to_x, ( BRx ) - _to_x + 1 );\
	skip_if( _W <= 0 );\
	i2 const _to_y = MAX( 0, ( TLy ) );\
	i2 const _H = i2_min2( TO_REF->size.h - _to_y, ( BRy ) - _to_y + 1 );\
	skip_if( _H <= 0 );\
	pixel ref _to_ref = TO_REF->pixels + _to_y * TO_REF->size.w + _to_x

#define _canvas_ref_fill_area_loop( TO_REF, COLOR )\
	pixel const _color = ( COLOR );\
	if_all( _color.r is _color.g, _color.g is _color.b, _color.b is _color.a )\
	{\
		n4 const _bytes_per_row = _W << pixel_bytes_shift;\
		i4 const _to_step = TO_REF->size.w;\
		i2 _h = _H;\
		do\
		{\
			bytes_fill( _to_ref, _color.r, _bytes_per_row );\
			_to_ref += _to_step;\
		}\
		while( --_h );\
	}\
	else\
	{\
		pixel const ref _from_ref = _to_ref;\
		iter( _x, _W )\
		{\
			_to_ref[ _x ] = _color;\
		}\
		_to_ref += TO_REF->size.w;\
		_canvas_ref_copy_loop( TO_REF, 0, _H - 1 );\
	}

#pragma endregion

////////////////
#pragma region | - draw canvas

#define _canvas_ref_draw_canvas_part( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE... )\
	START_DEF\
	{\
		_canvas_ref_set_canvas_setup( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh );\
		_canvas_ref_set_canvas_loop_per( TO_REF, _pixel_ref_##MODE( _to_ref, val_of( _from_ref ) ) );\
	}\
	END_DEF

#define _canvas_ref_draw_canvas_part_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE... )\
	START_DEF\
	{\
		_canvas_ref_set_canvas_setup_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh );\
		_canvas_ref_set_canvas_loop_per( TO_REF, _pixel_ref_##MODE( _to_ref, val_of( _from_ref ) ) );\
	}\
	END_DEF

#pragma endregion

////////////////
#pragma region | - line

#define _LINE_FN_SHIFT 32
#define _LINE_FN_HALF ( ( i8 ) 1 << ( _LINE_FN_SHIFT - 1 ) )
#define _LINE_FN_SCALE ( ( i8 ) 1 << _LINE_FN_SHIFT )

#define _LINE( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, INJECT, CODE... )\
	START_DEF\
	{\
		i4 X_NAME = i4( Ax );\
		i4 Y_NAME = i4( Ay );\
		const i4 _LINE_FN##_x2 = i4( Bx );\
		const i4 _LINE_FN##_y2 = i4( By );\
		const i4 _LINE_FN##_xd = _LINE_FN##_x2 - X_NAME;\
		const i4 _LINE_FN##_yd = _LINE_FN##_y2 - Y_NAME;\
		i8 _LINE_FN##_hs = ( i8( X_NAME ) << _LINE_FN_SHIFT ) + _LINE_FN_HALF;\
		i8 _LINE_FN##_vs = ( i8( Y_NAME ) << _LINE_FN_SHIFT ) + _LINE_FN_HALF;\
		const i4 _LINE_FN##_ax = ABS( _LINE_FN##_xd );\
		const i4 _LINE_FN##_ay = ABS( _LINE_FN##_yd );\
		i4 _LINE_FN##_a = pick( _LINE_FN##_ax > _LINE_FN##_ay, _LINE_FN##_ax, _LINE_FN##_ay );\
		const i8 _LINE_FN##_recip = pick( _LINE_FN##_a, _LINE_FN_SCALE / i8( _LINE_FN##_a ), 0 );\
		const i8 _LINE_FN##_xs = i8( _LINE_FN##_xd ) * _LINE_FN##_recip;\
		const i8 _LINE_FN##_ys = i8( _LINE_FN##_yd ) * _LINE_FN##_recip;\
		const i4 _LINE_FN##_i = 0;\
		INJECT;\
		++_LINE_FN##_a;\
		do\
		{\
			X_NAME = i4( _LINE_FN##_hs >> _LINE_FN_SHIFT );\
			Y_NAME = i4( _LINE_FN##_vs >> _LINE_FN_SHIFT );\
			CODE;\
			_LINE_FN##_hs += _LINE_FN##_xs;\
			_LINE_FN##_vs += _LINE_FN##_ys;\
		}\
		while( --_LINE_FN##_a );\
	}\
	END_DEF

#define _line_fn( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE... ) _LINE( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME,, CODE )
#define _line_fn_eval( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE... ) _line_fn( _LINE_FN, Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )

#define _LINE_SAFE_AXIS( _LINE_FN, POS, DELTA, LIMIT )\
	START_DEF\
	{\
		if( not DELTA )\
		{\
			if( POS < 0 or POS > LIMIT )\
			{\
				_LINE_FN##_ok = no;\
			}\
			skip;\
		}\
		i8 _LINE_FN##_near;\
		i8 _LINE_FN##_far;\
		i8 _LINE_FN##_step;\
		if( DELTA > 0 )\
		{\
			_LINE_FN##_near = -i8( POS );\
			_LINE_FN##_far = i8( LIMIT ) - i8( POS );\
			_LINE_FN##_step = DELTA;\
		}\
		else\
		{\
			_LINE_FN##_near = i8( POS ) - i8( LIMIT );\
			_LINE_FN##_far = i8( POS );\
			_LINE_FN##_step = -DELTA;\
		}\
		i8 _LINE_FN##_low = _LINE_FN##_t0n * _LINE_FN##_step;\
		i8 _LINE_FN##_high = _LINE_FN##_t1n * _LINE_FN##_step;\
		if( _LINE_FN##_near * _LINE_FN##_t1d > _LINE_FN##_high or _LINE_FN##_far * _LINE_FN##_t0d < _LINE_FN##_low )\
		{\
			_LINE_FN##_ok = no;\
			skip;\
		}\
		if( _LINE_FN##_near * _LINE_FN##_t0d > _LINE_FN##_low )\
		{\
			_LINE_FN##_t0n = _LINE_FN##_near;\
			_LINE_FN##_t0d = _LINE_FN##_step;\
		}\
		if( _LINE_FN##_far * _LINE_FN##_t1d < _LINE_FN##_high )\
		{\
			_LINE_FN##_t1n = _LINE_FN##_far;\
			_LINE_FN##_t1d = _LINE_FN##_step;\
		}\
	}\
	END_DEF

#define _line_fn_safe( _LINE_FN, Ax, Ay, Bx, By, W, H, X_NAME, Y_NAME, CODE... )\
	START_DEF\
	{\
		const i4 _LINE_FN##_ax = i4( Ax );\
		const i4 _LINE_FN##_ay = i4( Ay );\
		const i4 _LINE_FN##_dx = i4( Bx ) - _LINE_FN##_ax;\
		const i4 _LINE_FN##_dy = i4( By ) - _LINE_FN##_ay;\
		i8 _LINE_FN##_t0n = 0;\
		i8 _LINE_FN##_t0d = 1;\
		i8 _LINE_FN##_t1n = 1;\
		i8 _LINE_FN##_t1d = 1;\
		flag _LINE_FN##_ok = yes;\
		const i4 _W = ( W ) - 1;\
		_LINE_SAFE_AXIS( _LINE_FN, _LINE_FN##_ax, _LINE_FN##_dx, _W );\
		skip_if( not _LINE_FN##_ok );\
		const i4 _H = ( H ) - 1;\
		_LINE_SAFE_AXIS( _LINE_FN, _LINE_FN##_ay, _LINE_FN##_dy, _H );\
		skip_if( not _LINE_FN##_ok );\
		_LINE( _LINE_FN, _LINE_FN##_ax, _LINE_FN##_ay, Bx, By, X_NAME, Y_NAME, const i4 _LINE_FN##_i0 = i4( ( _LINE_FN##_t0n * i8( _LINE_FN##_a ) + _LINE_FN##_t0d - 1 ) / _LINE_FN##_t0d ); const i4 _LINE_FN##_i1 = i4( ( _LINE_FN##_t1n * i8( _LINE_FN##_a ) ) / _LINE_FN##_t1d ); _LINE_FN##_a = _LINE_FN##_i1 - _LINE_FN##_i0; skip_if( _LINE_FN##_a < 0 ); _LINE_FN##_hs += _LINE_FN##_xs * i8( _LINE_FN##_i0 ); _LINE_FN##_vs += _LINE_FN##_ys * i8( _LINE_FN##_i0 );, X_NAME = pick( X_NAME < 0, 0, pick( X_NAME > _W, _W, X_NAME ) ); Y_NAME = pick( Y_NAME < 0, 0, pick( Y_NAME > _H, _H, Y_NAME ) ); CODE );\
	}\
	END_DEF

#define _line_fn_safe_eval( _LINE_FN, Ax, Ay, Bx, By, W, H, X_NAME, Y_NAME, CODE... ) _line_fn_safe( _LINE_FN, Ax, Ay, Bx, By, W, H, X_NAME, Y_NAME, CODE )

#pragma endregion

////////////////
#pragma region | - circle

#define _CIRCLE( _CIRC_FN, RADIUS, X_NAME, Y_NAME, INJECT, CODE... )\
	START_DEF\
	{\
		i4 X_NAME = i4( RADIUS );\
		i4 Y_NAME = 0;\
		i4 _CIRC_FN##_err = 1 - X_NAME;\
		i4 _CIRC_FN##_mask;\
		INJECT;\
		do\
		{\
			CODE;\
			_CIRC_FN##_mask = ~ ( _CIRC_FN##_err >> 31 );\
			X_NAME += _CIRC_FN##_mask;\
			_CIRC_FN##_err -= ( X_NAME << 1 ) & _CIRC_FN##_mask;\
			_CIRC_FN##_err += ( Y_NAME << 1 ) + 3;\
			Y_NAME++;\
		}\
		while( Y_NAME <= X_NAME );\
	}\
	END_DEF

#define _circle_fn( _CIRC_FN, RADIUS, X_NAME, Y_NAME, CODE... ) _CIRCLE( _CIRC_FN, RADIUS, X_NAME, Y_NAME,, CODE )
#define _circle_fn_eval( _LINE_FN, RADIUS, X_NAME, Y_NAME, CODE... ) _circle_fn( _CIRC_FN, RADIUS, X_NAME, Y_NAME, CODE )

#define _circle_canvas_pixel_fn( FN, CANVAS_REF, Cx, Cy, PIXEL_MODE... ) FN( CANVAS_REF, Cx, Cy, PIXEL_MODE )

#define _circle_canvas_pixel( FN, CANVAS_REF, Cx, Cy, X_NAME, Y_NAME, PIXEL, MODE... )\
	START_DEF\
	{\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx + X_NAME, Cy + Y_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx + X_NAME, Cy - Y_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx - X_NAME, Cy + Y_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx - X_NAME, Cy - Y_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx + Y_NAME, Cy + X_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx + Y_NAME, Cy - X_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx - Y_NAME, Cy + X_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		_circle_canvas_pixel_fn( FN, CANVAS_REF, Cx - Y_NAME, Cy - X_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
	}\
	END_DEF

#define _circle_canvas_pixel_hline_fn( FN, CANVAS_REF, Ax, Bx, Y, PIXEL_MODE... )\
	START_DEF\
	{\
		range( _X, Ax, Bx )\
		{\
			FN( CANVAS_REF, _X, Y, PIXEL_MODE );\
		}\
	}\
	END_DEF

#define _circle_canvas_pixel_hline( FN, CANVAS_REF, Cx, Cy, X_NAME, Y_NAME, PIXEL, MODE... )\
	START_DEF\
	{\
		_circle_canvas_pixel_hline_fn( FN, CANVAS_REF, Cx - X_NAME, Cx + X_NAME, Cy + Y_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		if( Y_NAME isnt 0 ) _circle_canvas_pixel_hline_fn( FN, CANVAS_REF, Cx - X_NAME, Cx + X_NAME, Cy - Y_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		if( _CIRC_FN##_err >= 0 and Y_NAME < X_NAME )\
		{\
			_circle_canvas_pixel_hline_fn( FN, CANVAS_REF, Cx - Y_NAME, Cx + Y_NAME, Cy + X_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
			_circle_canvas_pixel_hline_fn( FN, CANVAS_REF, Cx - Y_NAME, Cx + Y_NAME, Cy - X_NAME, PIXEL COMMA_IF_INPUTS( MODE ) MODE );\
		}\
	}\
	END_DEF

#pragma endregion

#pragma endregion hidden

////////////////////////////////
#pragma region | canvas / visible

////////////////
#pragma region | - creation

#define make_canvas( WIDTH, HEIGHT, PIXELS... ) _make_canvas( WIDTH, HEIGHT, DEFAULT( _MAKE_CANVAS_NEW_REF, PIXELS ) )

#pragma endregion

////////////////
#pragma region | - operations

fn canvas_ref_wipe( canvas ref const canvas_ref )
{
	os_delete_ref( canvas_ref->pixels );
	val_of( canvas_ref ) = make( canvas );
}

#define canvas_ref_resize( CANVAS_REF, WIDTH, HEIGHT, PRESERVE... ) _canvas_ref_resize( CANVAS_REF, WIDTH, HEIGHT, DEFAULT( no, PRESERVE ) )

#pragma endregion

////////////////
#pragma region | - clear

// canvas ref

#define canvas_ref_clear( CANVAS_REF ) bytes_clear( CANVAS_REF->pixels, CANVAS_REF->area << pixel_bytes_shift )

// current

#define clear() canvas_ref_clear( program.current_canvas_ref )

#pragma endregion

////////////////
#pragma region | - check pixel

// canvas ref

#define canvas_ref_check_pixel( CANVAS_REF, X, Y ) ( point_in_size( X, Y, CANVAS_REF->size.w, CANVAS_REF->size.h ) )
#define canvas_ref_check_pixel_index( CANVAS_REF, INDEX ) ( INDEX >= 0 and INDEX < CANVAS_REF->area )

// current

#define check_pixel( X, Y ) canvas_ref_check_pixel( program.current_canvas_ref, X, Y )
#define check_pixel_index( INDEX ) canvas_ref_check_pixel_index( program.current_canvas_ref, INDEX )

#pragma endregion

////////////////
#pragma region | - get pixel

// canvas ref

#define canvas_ref_get_pixel_index( CANVAS_REF, INDEX ) _canvas_ref_get_pixel_index( CANVAS_REF, INDEX )
#define canvas_ref_get_pixel_index_safe( CANVAS_REF, INDEX ) pick( canvas_ref_check_pixel_index( CANVAS_REF, INDEX ), canvas_ref_get_pixel_index( CANVAS_REF, INDEX ), pixel_invalid )
#define canvas_ref_get_pixel( CANVAS_REF, X, Y ) _canvas_ref_get_pixel( CANVAS_REF, X, Y )
#define canvas_ref_get_pixel_safe( CANVAS_REF, X, Y ) pick( canvas_ref_check_pixel( CANVAS_REF, X, Y ), canvas_ref_get_pixel( CANVAS_REF, X, Y ), pixel_invalid )

// current

#define get_pixel_index( INDEX ) canvas_ref_get_pixel_index( program.current_canvas_ref, INDEX )
#define get_pixel_index_safe( INDEX ) canvas_ref_get_pixel_index_safe( program.current_canvas_ref, INDEX )
#define get_pixel( X, Y ) canvas_ref_get_pixel( program.current_canvas_ref, X, Y )
#define get_pixel_safe( X, Y ) canvas_ref_get_pixel_safe( program.current_canvas_ref, X, Y )

#pragma endregion

////////////////
#pragma region | - set pixel

// canvas ref

#define canvas_ref_set_pixel_index( CANVAS_REF, INDEX, PIXEL ) ( canvas_ref_get_pixel_index( CANVAS_REF, INDEX ) ) = ( PIXEL )
#define canvas_ref_set_pixel_index_safe( CANVAS_REF, INDEX, PIXEL ) if( canvas_ref_check_pixel_index( CANVAS_REF, INDEX ) ) canvas_ref_set_pixel_index( CANVAS_REF, INDEX, PIXEL )
#define canvas_ref_set_pixel( CANVAS_REF, X, Y, PIXEL ) ( canvas_ref_get_pixel( CANVAS_REF, X, Y ) ) = ( PIXEL )
#define canvas_ref_set_pixel_safe( CANVAS_REF, X, Y, PIXEL ) if( canvas_ref_check_pixel( CANVAS_REF, X, Y ) ) canvas_ref_set_pixel( CANVAS_REF, X, Y, PIXEL )

// current

#define set_pixel_index( INDEX, PIXEL ) canvas_ref_set_pixel_index( program.current_canvas_ref, INDEX, PIXEL )
#define set_pixel_index_safe( INDEX, PIXEL ) canvas_ref_set_pixel_index_safe( program.current_canvas_ref, INDEX, PIXEL )
#define set_pixel( X, Y, PIXEL ) canvas_ref_set_pixel( program.current_canvas_ref, X, Y, PIXEL )
#define set_pixel_safe( X, Y, PIXEL ) canvas_ref_set_pixel_safe( program.current_canvas_ref, X, Y, PIXEL )

#pragma endregion

////////////////
#pragma region | - draw pixel

// canvas ref

#define canvas_ref_draw_pixel_index( CANVAS_REF, INDEX, PIXEL, MODE... ) _canvas_ref_draw_pixel_index( CANVAS_REF, INDEX, PIXEL, MODE )
#define canvas_ref_draw_pixel_index_safe( CANVAS_REF, INDEX, PIXEL, MODE... ) if( canvas_ref_check_pixel_index( CANVAS_REF, INDEX ) ) canvas_ref_draw_pixel_index( CANVAS_REF, INDEX, PIXEL, MODE )
#define canvas_ref_draw_pixel( CANVAS_REF, X, Y, PIXEL, MODE... ) _canvas_ref_draw_pixel( CANVAS_REF, X, Y, PIXEL, MODE )
#define canvas_ref_draw_pixel_safe( CANVAS_REF, X, Y, PIXEL, MODE... ) if( canvas_ref_check_pixel( CANVAS_REF, X, Y ) ) canvas_ref_draw_pixel( CANVAS_REF, X, Y, PIXEL, MODE )

// current

#define draw_pixel_index( INDEX, PIXEL, MODE... ) canvas_ref_draw_pixel_index( program.current_canvas_ref, INDEX, PIXEL, DEFAULT( blend, MODE ) )
#define draw_pixel_index_safe( INDEX, PIXEL, MODE... ) canvas_ref_draw_pixel_index_safe( program.current_canvas_ref, INDEX, PIXEL, DEFAULT( blend, MODE ) )
#define draw_pixel( X, Y, PIXEL, MODE... ) canvas_ref_draw_pixel( program.current_canvas_ref, X, Y, PIXEL, DEFAULT( blend, MODE ) )
#define draw_pixel_safe( X, Y, PIXEL, MODE... ) canvas_ref_draw_pixel_safe( program.current_canvas_ref, X, Y, PIXEL, DEFAULT( blend, MODE ) )

#pragma endregion

////////////////
#pragma region | - set canvas

// canvas ref

#define canvas_ref_set_canvas_part( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		_canvas_ref_set_canvas_setup( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh );\
		_canvas_ref_copy_loop( TO_REF, _from_w, _H );\
	}\
	END_DEF

#define canvas_ref_set_canvas_part_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		_canvas_ref_set_canvas_setup_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh );\
		_canvas_ref_copy_loop( TO_REF, _from_w, _H );\
	}\
	END_DEF

#define canvas_ref_set_canvas_trans_part( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		_canvas_ref_set_canvas_setup( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh );\
		_canvas_ref_set_canvas_loop_trans( TO_REF );\
	}\
	END_DEF

#define canvas_ref_set_canvas_trans_part_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )\
	START_DEF\
	{\
		_canvas_ref_set_canvas_setup_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh );\
		_canvas_ref_set_canvas_loop_trans( TO_REF );\
	}\
	END_DEF

#define canvas_ref_set_canvas( TO_REF, FROM, TLx, TLy ) canvas_ref_set_canvas_part( TO_REF, FROM, TLx, TLy, 0, 0, FROM.size.w, FROM.size.h )
#define canvas_ref_set_canvas_safe( TO_REF, FROM, TLx, TLy ) canvas_ref_set_canvas_part_safe( TO_REF, FROM, TLx, TLy, 0, 0, FROM.size.w, FROM.size.h )
#define canvas_ref_set_canvas_trans( TO_REF, FROM, TLx, TLy ) canvas_ref_set_canvas_trans_part( TO_REF, FROM, TLx, TLy, 0, 0, FROM.size.w, FROM.size.h )
#define canvas_ref_set_canvas_trans_safe( TO_REF, FROM, TLx, TLy ) canvas_ref_set_canvas_trans_part_safe( TO_REF, FROM, TLx, TLy, 0, 0, FROM.size.w, FROM.size.h )

// current

#define set_canvas_part( FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh ) canvas_ref_set_canvas_part( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )
#define set_canvas_part_safe( FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh ) canvas_ref_set_canvas_part_safe( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )
#define set_canvas_trans_part( FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh ) canvas_ref_set_canvas_trans_part( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )
#define set_canvas_trans_part_safe( FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh ) canvas_ref_set_canvas_trans_part_safe( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh )

#define set_canvas( FROM_CANVAS, TLx, TLy ) canvas_ref_set_canvas( program.current_canvas_ref, FROM_CANVAS, TLx, TLy )
#define set_canvas_safe( FROM_CANVAS, TLx, TLy ) canvas_ref_set_canvas_safe( program.current_canvas_ref, FROM_CANVAS, TLx, TLy )
#define set_canvas_trans( FROM_CANVAS, TLx, TLy ) canvas_ref_set_canvas_trans( program.current_canvas_ref, FROM_CANVAS, TLx, TLy )
#define set_canvas_trans_safe( FROM_CANVAS, TLx, TLy ) canvas_ref_set_canvas_trans_safe( program.current_canvas_ref, FROM_CANVAS, TLx, TLy )

#pragma endregion

////////////////
#pragma region | - fill canvas

// canvas ref

#define canvas_ref_fill( TO_REF, COLOR )\
	START_DEF\
	{\
		pixel const _color = ( COLOR );\
		if_all( _color.r is _color.g, _color.g is _color.b, _color.b is _color.a )\
		{\
			bytes_fill( TO_REF->pixels, _color.r, TO_REF->area << pixel_bytes_shift );\
		}\
		else\
		{\
			pixel ref const _to_ref = TO_REF->pixels;\
			i4 const _W = i4( TO_REF->size.w );\
			iter( _i, _W )\
			{\
				_to_ref[ _i ] = _color;\
			}\
			i4 _filled = _W;\
			i4 _remaining = TO_REF->area - _W;\
			do\
			{\
				i4 const _count = pick( _remaining < _filled, _remaining, _filled );\
				bytes_copy( ref_of( _to_ref[ _filled ] ), _to_ref, _count << pixel_bytes_shift );\
				_filled += _count;\
				_remaining -= _count;\
			}\
			while( _remaining );\
		}\
	}\
	END_DEF

#define canvas_ref_fill_area( TO_REF, TLx, TLy, BRx, BRy, COLOR )\
	START_DEF\
	{\
		_canvas_ref_fill_area_setup( TO_REF, TLx, TLy, BRx, BRy );\
		out_if_any( _W <= 0, _H <= 0 );\
		_canvas_ref_fill_area_loop( TO_REF, COLOR );\
	}\
	END_DEF

#define canvas_ref_fill_area_safe( TO_REF, TLx, TLy, BRx, BRy, COLOR )\
	START_DEF\
	{\
		_canvas_ref_fill_area_setup_safe( TO_REF, TLx, TLy, BRx, BRy );\
		_canvas_ref_fill_area_loop( TO_REF, COLOR );\
	}\
	END_DEF

// current

#define fill( PIXEL ) canvas_ref_fill( program.current_canvas_ref, PIXEL )

#define fill_area( TLx, TLy, BRx, BRy, PIXEL ) canvas_ref_fill_area( program.current_canvas_ref, TLx, TLy, BRx, BRy, PIXEL )
#define fill_area_safe( TLx, TLy, BRx, BRy, PIXEL ) canvas_ref_fill_area_safe( program.current_canvas_ref, TLx, TLy, BRx, BRy, PIXEL )

#pragma endregion

////////////////
#pragma region | - draw canvas

// canvas ref

#define canvas_ref_draw_canvas_part( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE... ) _canvas_ref_draw_canvas_part( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE )
#define canvas_ref_draw_canvas_part_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE... ) _canvas_ref_draw_canvas_part_safe( TO_REF, FROM, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE )

#define canvas_ref_draw_canvas( TO_REF, FROM, TLx, TLy, MODE... ) _canvas_ref_draw_canvas_part( TO_REF, FROM, TLx, TLy, 0, 0, FROM.size.w, FROM.size.h, MODE )
#define canvas_ref_draw_canvas_safe( TO_REF, FROM, TLx, TLy, MODE... ) _canvas_ref_draw_canvas_part_safe( TO_REF, FROM, TLx, TLy, 0, 0, FROM.size.w, FROM.size.h, MODE )

// current

#define draw_canvas_part( FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE... ) canvas_ref_draw_canvas_part( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, DEFAULT( blend, MODE ) )
#define draw_canvas_part_safe( FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, MODE... ) canvas_ref_draw_canvas_part_safe( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, PART_TLx, PART_TLy, PART_SIZEw, PART_SIZEh, DEFAULT( blend, MODE ) )

#define draw_canvas( FROM_CANVAS, TLx, TLy, MODE... ) canvas_ref_draw_canvas( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, DEFAULT( blend, MODE ) )
#define draw_canvas_safe( FROM_CANVAS, TLx, TLy, MODE... ) canvas_ref_draw_canvas_safe( program.current_canvas_ref, FROM_CANVAS, TLx, TLy, DEFAULT( blend, MODE ) )

#pragma endregion

////////////////
#pragma region | - line

#define line_fn( Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE... ) _line_fn_eval( JOIN( _LINE_FN_, __COUNTER__ ), Ax, Ay, Bx, By, X_NAME, Y_NAME, CODE )
#define line_fn_safe( Ax, Ay, Bx, By, W, H, X_NAME, Y_NAME, CODE... ) _line_fn_safe_eval( JOIN( _LINE_FN_, __COUNTER__ ), Ax, Ay, Bx, By, W, H, X_NAME, Y_NAME, CODE )

#pragma endregion

////////////////
#pragma region | - set line

// canvas ref

#define canvas_ref_set_line( CANVAS_REF, Ax, Ay, Bx, By, PIXEL ) line_fn( Ax, Ay, Bx, By, _x, _y, canvas_ref_set_pixel( CANVAS_REF, _x, _y, PIXEL ) )
#define canvas_ref_set_line_safe( CANVAS_REF, Ax, Ay, Bx, By, PIXEL ) line_fn_safe( Ax, Ay, Bx, By, CANVAS_REF->size.w, CANVAS_REF->size.h, _x, _y, canvas_ref_set_pixel( CANVAS_REF, _x, _y, PIXEL ) )

// current

#define set_line( Ax, Ay, Bx, By, PIXEL ) canvas_ref_set_line( program.current_canvas_ref, Ax, Ay, Bx, By, PIXEL )
#define set_line_safe( Ax, Ay, Bx, By, PIXEL ) canvas_ref_set_line_safe( program.current_canvas_ref, Ax, Ay, Bx, By, PIXEL )

#pragma endregion

////////////////
#pragma region | - draw line

// canvas ref

#define canvas_ref_draw_line( CANVAS_REF, Ax, Ay, Bx, By, PIXEL, MODE... ) line_fn( Ax, Ay, Bx, By, _x, _y, canvas_ref_draw_pixel( CANVAS_REF, _x, _y, PIXEL, MODE ) )
#define canvas_ref_draw_line_safe( CANVAS_REF, Ax, Ay, Bx, By, PIXEL, MODE... ) line_fn_safe( Ax, Ay, Bx, By, CANVAS_REF->size.w, CANVAS_REF->size.h, _x, _y, canvas_ref_draw_pixel( CANVAS_REF, _x, _y, PIXEL, MODE ) )

// current

#define draw_line( Ax, Ay, Bx, By, PIXEL, MODE... ) canvas_ref_draw_line( program.current_canvas_ref, Ax, Ay, Bx, By, PIXEL, DEFAULT( blend, MODE ) )
#define draw_line_safe( Ax, Ay, Bx, By, PIXEL, MODE... ) canvas_ref_draw_line_safe( program.current_canvas_ref, Ax, Ay, Bx, By, PIXEL, DEFAULT( blend, MODE ) )

#pragma endregion

////////////////
#pragma region | - circle

#define circle_fn( RADIUS, X_NAME, Y_NAME, CODE... ) _circle_fn_eval( JOIN( _LINE_FN_, __COUNTER__ ), RADIUS, X_NAME, Y_NAME, CODE )

#pragma endregion

////////////////
#pragma region | - set circle

// canvas ref

#define canvas_ref_set_circle( CANVAS_REF, Cx, Cy, RADIUS, PIXEL ) circle_fn( RADIUS, _x, _y, _circle_canvas_pixel( canvas_ref_set_pixel, CANVAS_REF, Cx, Cy, _x, _y, PIXEL ) )
#define canvas_ref_set_circle_fill( CANVAS_REF, Cx, Cy, RADIUS, PIXEL ) circle_fn( RADIUS, _x, _y, _circle_canvas_pixel_hline( canvas_ref_set_pixel, CANVAS_REF, Cx, Cy, _x, _y, PIXEL ) )

// current

#define set_circle( Cx, Cy, RADIUS, PIXEL ) canvas_ref_set_circle( program.current_canvas_ref, Cx, Cy, RADIUS, PIXEL )
#define set_circle_fill( Cx, Cy, RADIUS, PIXEL ) canvas_ref_set_circle_fill( program.current_canvas_ref, Cx, Cy, RADIUS, PIXEL )

#pragma endregion

////////////////
#pragma region | - draw circle

// canvas ref

#define canvas_ref_draw_circle( CANVAS_REF, Cx, Cy, RADIUS, PIXEL, MODE... ) circle_fn( RADIUS, _x, _y, _circle_canvas_pixel( canvas_ref_draw_pixel, CANVAS_REF, Cx, Cy, _x, _y, PIXEL, MODE ) )
#define canvas_ref_draw_circle_fill( CANVAS_REF, Cx, Cy, RADIUS, PIXEL, MODE... ) circle_fn( RADIUS, _x, _y, _circle_canvas_pixel_hline( canvas_ref_draw_pixel, CANVAS_REF, Cx, Cy, _x, _y, PIXEL, MODE ) )

// current

#define draw_circle( Cx, Cy, RADIUS, PIXEL, MODE... ) canvas_ref_draw_circle( program.current_canvas_ref, Cx, Cy, RADIUS, PIXEL, DEFAULT( blend, MODE ) )
#define draw_circle_fill( Cx, Cy, RADIUS, PIXEL, MODE... ) canvas_ref_draw_circle_fill( program.current_canvas_ref, Cx, Cy, RADIUS, PIXEL, DEFAULT( blend, MODE ) )

#pragma endregion

#pragma endregion visible

#pragma endregion canvas

////////////////////////////////////////////////////////////////
#pragma region - font

////////////////////////////////
#pragma region | font / hidden

////////////////
#pragma region | - ref draw

#define _canvas_ref_draw_byte( BYTE, MODE )\
	{\
		byte const _letter = ( BYTE ) - ' ';\
		pixel ref _to_ref = _to_ref_start;\
		pixel const ref _from_ref = _from_base + ( _letter >> 4 ) * _letter_h * _from_w + ( _letter & 0x0F ) * _letter_w;\
		i2 _h = _letter_h;\
		do\
		{\
			i2 _w = _letter_w;\
			do\
			{\
				if( _from_ref->a )\
				{\
					_pixel_ref_##MODE( _to_ref, _color );\
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

#define _canvas_ref_set_setup( CANVAS_REF, FONT, POS_X, POS_Y, ANCHOR, COLOR, ANCHOR_W )\
	i2 const _letter_w = FONT.letter_size.w;\
	i2 const _letter_h = FONT.letter_size.h;\
	anchor const _anchor = ( ANCHOR );\
	pixel const _color = ( COLOR );\
	i2 const _pos_x = ( POS_X );\
	i2 const _pos_y = ( POS_Y );\
	i4 const _to_w = CANVAS_REF->size.w;\
	i4 const _from_w = FONT.canvas.size.w;\
	i4 const _to_step = _to_w - _letter_w;\
	i4 const _from_step = _from_w - _letter_w;\
	pixel const ref _from_base = FONT.canvas.pixels;\
	pixel ref _to_ref_start = ref_of( CANVAS_REF->pixels[ array_index( _pos_x + anchor_get_x( _anchor, 0, ANCHOR_W, 0 ), _pos_y + anchor_get_y( _anchor, 0, _letter_h, 0 ), _to_w ) ] );

#pragma endregion

#pragma endregion hidden

////////////////////////////////
#pragma region | font / visible

////////////////
#pragma region | - creation

embed font make_font( canvas const canvas )
{
	font this = { 0 };
	this.canvas = canvas;
	this.letter_size = n2x2( canvas.size.w >> 4, canvas.size.h >> 3 );
	out this;
}

#pragma endregion

////////////////
#pragma region | - set bytes

// canvas ref

#define canvas_ref_set_byte( CANVAS_REF, FONT, BYTE, POS_X, POS_Y, ANCHOR, COLOR )\
	START_DEF\
	{\
		_canvas_ref_set_setup( CANVAS_REF, FONT, POS_X, POS_Y, ANCHOR, COLOR, _letter_w );\
		_canvas_ref_draw_byte( BYTE, set )\
	}\
	END_DEF

#define canvas_ref_set_bytes( CANVAS_REF, FONT, BYTES, BYTES_SIZE, POS_X, POS_Y, ANCHOR, COLOR )\
	START_DEF\
	{\
		n2 const _text_len = pick( BYTES_SIZE is 0, bytes_measure( BYTES ), BYTES_SIZE );\
		_canvas_ref_set_setup( CANVAS_REF, FONT, POS_X, POS_Y, ANCHOR, COLOR, _text_len * _letter_w );\
		iter( _l, _text_len )\
		{\
			_canvas_ref_draw_byte( BYTES[ _l ], set ) _to_ref_start += _letter_w;\
		}\
	}\
	END_DEF

// current

#define set_byte( FONT, BYTE, POS_X, POS_Y, ANCHOR, COLOR ) canvas_ref_set_byte( program.current_canvas_ref, FONT, BYTE, POS_X, POS_Y, ANCHOR, COLOR )
#define set_bytes( FONT, BYTES, BYTES_SIZE, POS_X, POS_Y, ANCHOR, COLOR ) canvas_ref_set_bytes( program.current_canvas_ref, FONT, BYTES, BYTES_SIZE, POS_X, POS_Y, ANCHOR, COLOR )

#pragma endregion

////////////////
#pragma region | - draw bytes

// canvas ref

#define canvas_ref_draw_byte( CANVAS_REF, FONT, BYTE, POS_X, POS_Y, ANCHOR, COLOR, MODE... )\
	START_DEF\
	{\
		_canvas_ref_set_setup( CANVAS_REF, FONT, POS_X, POS_Y, ANCHOR, COLOR, _letter_w );\
		_canvas_ref_draw_byte( BYTE, MODE )\
	}\
	END_DEF

#define canvas_ref_draw_bytes( CANVAS_REF, FONT, BYTES, BYTES_SIZE, POS_X, POS_Y, ANCHOR, COLOR, MODE... )\
	START_DEF\
	{\
		n2 const _text_len = pick( BYTES_SIZE is 0, bytes_measure( BYTES ), BYTES_SIZE );\
		_canvas_ref_set_setup( CANVAS_REF, FONT, POS_X, POS_Y, ANCHOR, COLOR, _text_len * _letter_w );\
		iter( _l, _text_len )\
		{\
			_canvas_ref_draw_byte( BYTES[ _l ], MODE ) _to_ref_start += _letter_w;\
		}\
	}\
	END_DEF

// current

#define draw_byte( FONT, BYTE, POS_X, POS_Y, ANCHOR, COLOR, MODE... ) canvas_ref_draw_byte( program.current_canvas_ref, FONT, BYTE, POS_X, POS_Y, ANCHOR, COLOR, DEFAULT( blend, MODE ) )
#define draw_bytes( FONT, BYTES, BYTES_SIZE, POS_X, POS_Y, ANCHOR, COLOR, MODE... ) canvas_ref_draw_bytes( program.current_canvas_ref, FONT, BYTES, BYTES_SIZE, POS_X, POS_Y, ANCHOR, COLOR, DEFAULT( blend, MODE ) )

#pragma endregion

#pragma endregion visible

#pragma endregion font

////////////////////////////////////////////////////////////////
#pragma region - nano

////////////////////////////////
#pragma region | nano / hidden

#pragma endregion hidden

////////////////////////////////
#pragma region | nano / visible

embed nano nano_now()
{
	#if OS_WINDOWS
		perm LARGE_INTEGER frequency;
		perm LARGE_INTEGER start_counter;
		once
		{
			QueryPerformanceFrequency( ref_of( frequency ) );
			QueryPerformanceCounter( ref_of( start_counter ) );
		}

		LARGE_INTEGER current;
		QueryPerformanceCounter( ref_of( current ) );

		nano const ticks = current.QuadPart - start_counter.QuadPart;
		out to( nano, ( ( ticks / frequency.QuadPart ) * nano_per_sec ) + ( ( ( ticks mod frequency.QuadPart ) * nano_per_sec ) / frequency.QuadPart ) );
	#else
		perm struct timespec start_time;
		once
		{
			clock_gettime( CLOCK_MONOTONIC, ref_of( start_time ) );
		}

		struct timespec ts;
		clock_gettime( CLOCK_MONOTONIC, ref_of( ts ) );
		out to( nano, ( ts.tv_sec - start_time.tv_sec ) * nano_per_sec + ( ts.tv_nsec - start_time.tv_nsec ) );
	#endif
}

fn nano_sleep_until( nano const deadline )
{
	nano const now = nano_now();
	out_if( deadline <= now );

	#if OS_WINDOWS
		perm HANDLE timer = nothing;
		once
		{
			#ifdef _SYNCHAPI_H_
				timer = CreateWaitableTimerExW( nothing, nothing, 0x2, 0x001F0003L );
			#endif
			if( timer is nothing )
			{
				timer = CreateWaitableTimer( nothing, TRUE, nothing );
			}
		}
		nano const duration = deadline - now;
		LARGE_INTEGER const li = { .QuadPart = -( ( duration + 99 ) / 100 ) };
		SetWaitableTimer( timer, ref_of( li ), 0, nothing, nothing, FALSE );
		WaitForSingleObject( timer, INFINITE );
	#else
		struct timespec const ts =
			{
				.tv_sec = deadline / nano_per_sec,
				.tv_nsec = deadline mod nano_per_sec,
			};
		clock_nanosleep( CLOCK_MONOTONIC, TIMER_ABSTIME, ref_of( ts ), nothing );
	#endif
}

#pragma endregion visible

#pragma endregion nano

////////////////////////////////////////////////////////////////
#pragma region - inputs

////////////////////////////////
#pragma region | inputs / hidden

#define _INPUT_SET( NAME, LINUX_KEY, WINDOWS_KEY )[ OS_PICK( LINUX_KEY, WINDOWS_KEY ) ] = NAME
#define _INPUT_SET_MASKED( NAME, LINUX_KEY, WINDOWS_KEY )[ OS_PICK( LINUX_KEY & 0x1ff, WINDOWS_KEY ) ] = NAME

#ifndef C7H16_INPUT_NO_KEYBOARD
	perm byte const _INPUT_MAP[] =
		{
			#ifndef C7H16_INPUT_NO_LETTERS
				_INPUT_SET( keyboard_a, XK_a, 'A' ),
				_INPUT_SET( keyboard_b, XK_b, 'B' ),
				_INPUT_SET( keyboard_c, XK_c, 'C' ),
				_INPUT_SET( keyboard_d, XK_d, 'D' ),
				_INPUT_SET( keyboard_e, XK_e, 'E' ),
				_INPUT_SET( keyboard_f, XK_f, 'F' ),
				_INPUT_SET( keyboard_g, XK_g, 'G' ),
				_INPUT_SET( keyboard_h, XK_h, 'H' ),
				_INPUT_SET( keyboard_i, XK_i, 'I' ),
				_INPUT_SET( keyboard_j, XK_j, 'J' ),
				_INPUT_SET( keyboard_k, XK_k, 'K' ),
				_INPUT_SET( keyboard_l, XK_l, 'L' ),
				_INPUT_SET( keyboard_m, XK_m, 'M' ),
				_INPUT_SET( keyboard_n, XK_n, 'N' ),
				_INPUT_SET( keyboard_o, XK_o, 'O' ),
				_INPUT_SET( keyboard_p, XK_p, 'P' ),
				_INPUT_SET( keyboard_q, XK_q, 'Q' ),
				_INPUT_SET( keyboard_r, XK_r, 'R' ),
				_INPUT_SET( keyboard_s, XK_s, 'S' ),
				_INPUT_SET( keyboard_t, XK_t, 'T' ),
				_INPUT_SET( keyboard_u, XK_u, 'U' ),
				_INPUT_SET( keyboard_v, XK_v, 'V' ),
				_INPUT_SET( keyboard_w, XK_w, 'W' ),
				_INPUT_SET( keyboard_x, XK_x, 'X' ),
				_INPUT_SET( keyboard_y, XK_y, 'Y' ),
				_INPUT_SET( keyboard_z, XK_z, 'Z' ),
			#endif

			#ifndef C7H16_INPUT_NO_NUMBERS
				_INPUT_SET( keyboard_0, XK_0, '0' ),
				_INPUT_SET( keyboard_1, XK_1, '1' ),
				_INPUT_SET( keyboard_2, XK_2, '2' ),
				_INPUT_SET( keyboard_3, XK_3, '3' ),
				_INPUT_SET( keyboard_4, XK_4, '4' ),
				_INPUT_SET( keyboard_5, XK_5, '5' ),
				_INPUT_SET( keyboard_6, XK_6, '6' ),
				_INPUT_SET( keyboard_7, XK_7, '7' ),
				_INPUT_SET( keyboard_8, XK_8, '8' ),
				_INPUT_SET( keyboard_9, XK_9, '9' ),
			#endif

			#ifndef C7H16_INPUT_NO_SYMBOLS
				_INPUT_SET( keyboard_backtick, XK_grave, VK_OEM_3 ),
				_INPUT_SET( keyboard_minus, XK_minus, VK_OEM_MINUS ),
				_INPUT_SET( keyboard_equals, XK_equal, VK_OEM_PLUS ),
				_INPUT_SET( keyboard_leftbracket, XK_bracketleft, VK_OEM_4 ),
				_INPUT_SET( keyboard_rightbracket, XK_bracketright, VK_OEM_6 ),
				_INPUT_SET( keyboard_backslash, XK_backslash, VK_OEM_5 ),
				_INPUT_SET( keyboard_semicolon, XK_semicolon, VK_OEM_1 ),
				_INPUT_SET( keyboard_apostrophe, XK_apostrophe, VK_OEM_7 ),
				_INPUT_SET( keyboard_comma, XK_comma, VK_OEM_COMMA ),
				_INPUT_SET( keyboard_period, XK_period, VK_OEM_PERIOD ),
				_INPUT_SET( keyboard_slash, XK_slash, VK_OEM_2 ),
				_INPUT_SET( keyboard_space, XK_space, VK_SPACE ),
				_INPUT_SET_MASKED( keyboard_tab, XK_Tab, VK_TAB ),
			#endif

			#ifndef C7H16_INPUT_NO_FUNCTIONS
				_INPUT_SET_MASKED( keyboard_f1, XK_F1, VK_F1 ),
				_INPUT_SET_MASKED( keyboard_f2, XK_F2, VK_F2 ),
				_INPUT_SET_MASKED( keyboard_f3, XK_F3, VK_F3 ),
				_INPUT_SET_MASKED( keyboard_f4, XK_F4, VK_F4 ),
				_INPUT_SET_MASKED( keyboard_f5, XK_F5, VK_F5 ),
				_INPUT_SET_MASKED( keyboard_f6, XK_F6, VK_F6 ),
				_INPUT_SET_MASKED( keyboard_f7, XK_F7, VK_F7 ),
				_INPUT_SET_MASKED( keyboard_f8, XK_F8, VK_F8 ),
				_INPUT_SET_MASKED( keyboard_f9, XK_F9, VK_F9 ),
				_INPUT_SET_MASKED( keyboard_f10, XK_F10, VK_F10 ),
				_INPUT_SET_MASKED( keyboard_f11, XK_F11, VK_F11 ),
				_INPUT_SET_MASKED( keyboard_f12, XK_F12, VK_F12 ),
			#endif

			#ifndef C7H16_INPUT_NO_MODIFIERS
				_INPUT_SET_MASKED( keyboard_shift, XK_Shift_L, VK_SHIFT ),
				_INPUT_SET_MASKED( keyboard_ctrl, XK_Control_L, VK_CONTROL ),
				_INPUT_SET_MASKED( keyboard_alt, XK_Alt_L, VK_MENU ),
				_INPUT_SET_MASKED( keyboard_super, XK_Super_L, VK_LWIN ),
			#endif

			#ifndef C7H16_INPUT_NO_ARROWS
				_INPUT_SET_MASKED( keyboard_up, XK_Up, VK_UP ),
				_INPUT_SET_MASKED( keyboard_down, XK_Down, VK_DOWN ),
				_INPUT_SET_MASKED( keyboard_left, XK_Left, VK_LEFT ),
				_INPUT_SET_MASKED( keyboard_right, XK_Right, VK_RIGHT ),
			#endif

			#ifndef C7H16_INPUT_NO_CONTROLS
				_INPUT_SET_MASKED( keyboard_escape, XK_Escape, VK_ESCAPE ),
				_INPUT_SET_MASKED( keyboard_capslock, XK_Caps_Lock, VK_CAPITAL ),
				_INPUT_SET_MASKED( keyboard_enter, XK_Return, VK_RETURN ),
				_INPUT_SET_MASKED( keyboard_backspace, XK_BackSpace, VK_BACK ),
				_INPUT_SET_MASKED( keyboard_insert, XK_Insert, VK_INSERT ),
				_INPUT_SET_MASKED( keyboard_delete, XK_Delete, VK_DELETE ),
				_INPUT_SET_MASKED( keyboard_home, XK_Home, VK_HOME ),
				_INPUT_SET_MASKED( keyboard_end, XK_End, VK_END ),
				_INPUT_SET_MASKED( keyboard_pageup, XK_Page_Up, VK_PRIOR ),
				_INPUT_SET_MASKED( keyboard_pagedown, XK_Page_Down, VK_NEXT ),
				_INPUT_SET_MASKED( keyboard_menu, XK_Menu, VK_APPS ),
			#endif
		};
#endif

#pragma endregion hidden

////////////////////////////////
#pragma region | inputs / visible

#define input_to_byte( INPUT ) ( ( INPUT ) - input_a + 'A' )

////////////////
#pragma region | - ref check

#define window_ref_input_pressed( WINDOW_REF, INPUT ) ( ( ( WINDOW_REF )->inputs[ INPUT ] & INPUT_MASK_PRESSED ) isnt 0 )
#define window_ref_input_held( WINDOW_REF, INPUT ) ( ( ( WINDOW_REF )->inputs[ INPUT ] & INPUT_MASK_HELD ) isnt 0 )
#define window_ref_input_released( WINDOW_REF, INPUT ) ( ( ( WINDOW_REF )->inputs[ INPUT ] & INPUT_MASK_RELEASED ) isnt 0 )

#define window_ref_scrolled_up( WINDOW_REF ) window_ref_input_pressed( WINDOW_REF, mouse_wheel_up )
#define window_ref_scrolled_down( WINDOW_REF ) window_ref_input_pressed( WINDOW_REF, mouse_wheel_down )
#define window_ref_scrolled_left( WINDOW_REF ) window_ref_input_pressed( WINDOW_REF, mouse_wheel_left )
#define window_ref_scrolled_right( WINDOW_REF ) window_ref_input_pressed( WINDOW_REF, mouse_wheel_right )

#pragma endregion

////////////////
#pragma region | - check

#define input_pressed( INPUT ) window_ref_input_pressed( program.current_window_ref, INPUT )
#define input_held( INPUT ) window_ref_input_held( program.current_window_ref, INPUT )
#define input_released( INPUT ) window_ref_input_released( program.current_window_ref, INPUT )

#define input_scrolled_up window_ref_scrolled_up( program.current_window_ref )
#define input_scrolled_down window_ref_scrolled_down( program.current_window_ref )
#define input_scrolled_left window_ref_scrolled_left( program.current_window_ref )
#define input_scrolled_right window_ref_scrolled_right( program.current_window_ref )

#pragma endregion

#pragma endregion visible

#pragma endregion inputs

////////////////////////////////////////////////////////////////
#pragma region - display

////////////////////////////////
#pragma region | display / visible

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

#pragma endregion visible

#pragma endregion display

////////////////////////////////////////////////////////////////
#pragma region - view

////////////////////////////////
#pragma region | view / hidden

fn _view_ref_setup( view ref const view_ref )
{
	view_ref->update = yes;

	#if OS_LINUX
		i4 const screen = DefaultScreen( program.display );
		i4 const depth = DefaultDepth( program.display, screen );
		view_ref->pixmap = XCreatePixmap( program.display, RootWindow( program.display, screen ), view_ref->canvas.size.w, view_ref->canvas.size.h, depth );
		view_ref->picture = XRenderCreatePicture( program.display, view_ref->pixmap, program.format, 0, nothing );
	#elif OS_WINDOWS
		//
	#endif
}

#pragma endregion hidden

////////////////////////////////
#pragma region | view / visible

#define view_ref_get_scaled_size( VIEW_REF ) r4x2( r4( VIEW_REF->canvas.size.w ) * VIEW_REF->scale.w, r4( VIEW_REF->canvas.size.h ) * VIEW_REF->scale.h )

fn view_ref_zoom( view ref const view_ref, i4 const x, i4 const y, r4 const factor )
{
	r4 const new_scale = r4_clamp( view_ref->scale.w * factor, 0.01, 1000.0 );
	r4 const actual_factor = new_scale / view_ref->scale.w;
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

#pragma endregion visible

#pragma endregion view

////////////////////////////////////////////////////////////////
#pragma region - window

////////////////////////////////
#pragma region | window / hidden

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

////////////////
#pragma region | - tick

fn _window_ref_update( window ref const window_ref )
{
	#if OS_LINUX
		XClearArea( program.display, window_ref->handle, 0, 0, 0, 0, yes );
	#elif OS_WINDOWS
		InvalidateRect( window_ref->handle, nothing, no );
	#endif
}

fn _window_ref_update_now( window ref const window_ref )
{
	#if OS_LINUX
		_window_ref_draw( window_ref );
		XFlush( program.display );
	#elif OS_WINDOWS
		RedrawWindow( window_ref->handle, nothing, nothing, RDW_INVALIDATE | RDW_UPDATENOW );
	#endif
}

fn _window_ref_tick( window ref const window_ref )
{
	program.current_window_ref = window_ref;

	_window_ref_get_mouse_position( window_ref, ref_of( window_ref->mouse.x ), ref_of( window_ref->mouse.y ) );

	iter( view_index, window_ref->views_count )
	{
		view ref const this_view = ref_of( window_ref->views[ view_index ] );

		r4 const epsilon_w = 1.0 / this_view->scale.w;
		r4 const epsilon_h = 1.0 / this_view->scale.h;

		this_view->mouse = r4x2( ( ( r4( window_ref->mouse.x ) - this_view->pos.x ) / this_view->scale.w ) + epsilon_w, ( ( r4( window_ref->mouse.y ) - this_view->pos.y ) / this_view->scale.h ) + epsilon_h );
	}

	// window tick

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

	window_ref->input_bytes_count = 0;

	// update

	if( program.fps > 0 )
	{
		_window_ref_update( window_ref );
	}
}

embed flag _windows_consume_tick()
{
	out_if( program.fps <= 0.0 ) no;

	nano const t = nano_now();

	out_if( t < program.next_tick ) no;

	program.tick_count += 1;
	program.next_tick = program.epoch + n8( ( r8( program.tick_count ) * r8( nano_per_sec ) ) / program.fps );

	out yes;
}

#pragma endregion

////////////////
#pragma region | - draw

fn _window_ref_draw( window ref const window_ref )
{
	n1 count = window_ref->views_count;
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
		HDC const wdc = window_ref->window_dc;
	#endif

	i4 const win_w = window_ref->size.w;
	i4 const win_h = window_ref->size.h;

	iter( view_index, window_max_views )
	{
		view ref const view_ref = ref_of( window_ref->views[ view_index ] );

		if( view_ref->state is view_state_unknown ) next;

		if( view_ref->update is yes )
		{
			call( view_ref->fn_draw, view_ref );
			view_ref->update = no;
		}

		r4x2 const scaled_size = view_ref_get_scaled_size( view_ref );
		skip_if( scaled_size.w is 0 or scaled_size.h is 0 );

		i4 const canvas_w = view_ref->canvas.size.w;
		i4 const canvas_h = view_ref->canvas.size.h;

		flag const clipped = view_ref->clip;

		i4 clip_l = 0;
		i4 clip_t = 0;
		i4 clip_r = 0;
		i4 clip_b = 0;

		if( clipped is yes )
		{
			clip_l = i4( view_ref->clip_region.xy.x );
			clip_t = i4( view_ref->clip_region.xy.y );
			clip_r = i4( view_ref->clip_region.zw.x );
			clip_b = i4( view_ref->clip_region.zw.y );

			skip_if( clip_r <= clip_l or clip_b <= clip_t );
		}

		i4 const view_l = i4( r4_floor( view_ref->pos.x ) );
		i4 const view_t = i4( r4_floor( view_ref->pos.y ) );
		i4 const view_r = i4( r4_ceil( view_ref->pos.x + scaled_size.w ) );
		i4 const view_b = i4( r4_ceil( view_ref->pos.y + scaled_size.h ) );
		r4 const scale_w = view_ref->scale.w;
		r4 const scale_h = view_ref->scale.h;

		#if OS_LINUX
			window_ref->image->data = to( byte ref, view_ref->canvas.pixels );
			window_ref->image->width = canvas_w;
			window_ref->image->height = canvas_h;
			window_ref->image->bytes_per_line = canvas_w << pixel_bytes_shift;

		#elif OS_WINDOWS
			window_ref->image.bmiHeader.biWidth = canvas_w;
			window_ref->image.bmiHeader.biHeight = -canvas_h;

			if( clipped is yes )
			{
				HRGN clip = CreateRectRgn( clip_l, clip_t, clip_r, clip_b );
				SelectClipRgn( wdc, clip );
				DeleteObject( clip );
			}
		#endif

		if( view_ref->clear is yes )
		{
			i4 clear_l;
			i4 clear_t;
			i4 clear_r;
			i4 clear_b;

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

			i4 const inner_l = i4_min( i4_max( view_l, clear_l ), clear_r );
			i4 const inner_t = i4_min( i4_max( view_t, clear_t ), clear_b );
			i4 const inner_r = i4_max( i4_min( view_r, clear_r ), clear_l );
			i4 const inner_b = i4_max( i4_min( view_b, clear_b ), clear_t );

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
			i4 const view_w = view_r - view_l;
			i4 const view_h = view_b - view_t;

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
				SetStretchBltMode( wdc, COLORONCOLOR );
				SetBrushOrgEx( wdc, 0, 0, NULL );

				StretchDIBits( wdc, view_l, view_t, view_w, view_h, 0, 0, canvas_w, canvas_h, view_ref->canvas.pixels, ref_of( window_ref->image ), DIB_RGB_COLORS, to( DWORD, 0x00CC0020 ) );
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

#pragma endregion

////////////////
#pragma region | - events

#define _window_event_resize OS_PICK( ConfigureNotify, WM_SIZE )
#define _window_event_draw OS_PICK( Expose, WM_PAINT )
#define _window_event_close OS_PICK( ClientMessage, WM_DESTROY )
#define _window_event_keyboard_pressed EVAL OS_PICK( ( KeyPress ), ( WM_KEYDOWN, WM_SYSKEYDOWN ) )
#define _window_event_keyboard_released EVAL OS_PICK( ( KeyRelease ), ( WM_KEYUP, WM_SYSKEYUP ) )
#define _window_event_mouse_move OS_PICK( MotionNotify, WM_MOUSEMOVE )
#define _window_event_focus_lost OS_PICK( FocusOut, WM_KILLFOCUS )

#define _window_add_input_pressed( VALUE )\
	if( not( window_ref->inputs[ VALUE ] & INPUT_MASK_HELD ) )\
	{\
		window_ref->inputs[ VALUE ] |= INPUT_MASK_PRESSED | INPUT_MASK_HELD;\
		window_ref->inputs_pressed[ window_ref->inputs_pressed_count++ ] = n1( VALUE );\
		window_ref->call_tick = yes;\
	}

#define _window_add_input_released( VALUE )\
	window_ref->inputs[ VALUE ] |= INPUT_MASK_RELEASED;\
	window_ref->inputs_released[ window_ref->inputs_released_count++ ] = n1( VALUE );\
	window_ref->call_tick = yes

#if OS_LINUX
	embed out_state _window_ref_process_event( window ref const window_ref, i4 const event, window_event const ref e )
#elif OS_WINDOWS
	embed LRESULT CALLBACK _window_ref_process_event( window_handle const h, i4 const event, WPARAM const wp, LPARAM const lp )
#endif
{
	#if OS_WINDOWS
		window ref const window_ref = to( window ref const, GetWindowLongPtr( h, GWLP_USERDATA ) );
	#endif
	jump_if_nothing( window_ref ) exit_events;

	program.current_window_ref = window_ref;

	with( event )
	{
		#if OS_LINUX
			//
		#elif OS_WINDOWS

			when( WM_ENTERSIZEMOVE, WM_ENTERMENULOOP )
			{
				program.resizing = 3;
				InvalidateRect( h, nothing, no );
				//jump _WINDOW_EVENT_DRAW;
				skip;
			}

			when( WM_EXITSIZEMOVE, WM_EXITMENULOOP )
			{
				program.resizing = 2;
				//jump _WINDOW_EVENT_DRAW;
				skip;
			}

			when( WM_ERASEBKGND )
			{
				out yes;
			}

			when( WM_SETCURSOR )
			{
				if( LOWORD( lp ) is HTCLIENT )
				{
					if( window_ref->changed_cursor is no )
					{
						SetCursor( LoadCursor( nothing, IDC_ARROW ) );
					}
					else
					{
						window_ref->changed_cursor = no;
					}
					out yes;
				}
				skip;
			}
		#endif

		when( _window_event_resize )
		{
			#if OS_LINUX
				program.resizing = 2;
			#endif

			n2 w = OS_PICK( e->xconfigure.width, LOWORD( lp ) );
			n2 h = OS_PICK( e->xconfigure.height, HIWORD( lp ) );

			window_ref->size.w = w;
			window_ref->size.h = h;

			call( window_ref->fn_resize, window_ref );
			#if OS_WINDOWS
				out no;
			#endif
		} // fall through

		when( _window_event_draw )
		{
			#if OS_WINDOWS
				ValidateRect( h, nothing );
			#endif

			if( program.resizing > 0 )
			{
				if( program.resizing < 3 )
				{
					program.resizing -= 1;
				}

				if( _windows_consume_tick() )
				{
					_window_ref_tick( window_ref );
				}
				_window_ref_update( window_ref );

				#if OS_WINDOWS
					if( program.resizing > 0 )
					{
						InvalidateRect( h, nothing, no );
					}
				#endif
			}

			_window_ref_draw( window_ref );
			out no;
		}

		when( _window_event_focus_lost )
		{
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
			when( _window_event_keyboard_pressed )
			{
				byte key = _INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( program.display, e->xkey.keycode, 0, 0 ) & 0x1ff, wp & 0xff ) ];
				_window_add_input_pressed( key );

				#if OS_LINUX
					byte char_buffer;
					if( XLookupString( to( XKeyEvent ref, ref_of( e->xkey ) ), ref_of( char_buffer ), 1, nothing, nothing ) is 1 and window_ref->input_bytes_count < window_max_inputs )
					{
						window_ref->input_bytes[ window_ref->input_bytes_count++ ] = char_buffer;
						window_ref->call_tick = yes;
					}
				#endif

				skip;
			}

			when( _window_event_keyboard_released )
			{
				byte key = _INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( program.display, e->xkey.keycode, 0, 0 ) & 0x1ff, wp & 0xff ) ];
				_window_add_input_released( key );
				skip;
			}

			#if OS_WINDOWS
				when( WM_CHAR )
				{
					if( wp <= 0xff and window_ref->input_bytes_count < window_max_inputs )
					{
						window_ref->input_bytes[ window_ref->input_bytes_count++ ] = to( byte, wp );
						window_ref->call_tick = yes;
					}
					skip;
				}
			#endif
		#endif

		#ifndef C7H16_INPUT_NO_MOUSE
			when( _window_event_mouse_move )
			{
				#if OS_LINUX
					window_event next_move;
					while( XCheckTypedWindowEvent( program.display, window_ref->handle, MotionNotify, ref_of( next_move ) ) );
				#endif
				window_ref->call_tick = yes;
				skip;
			}

			#if OS_LINUX
				when( ButtonPress )
				{
					with( e->xbutton.button )
					{
						when( Button1 )
						{
							_window_add_input_pressed( mouse_left );
							skip;
						}

						when( Button2 )
						{
							_window_add_input_pressed( mouse_middle );
							skip;
						}

						when( Button3 )
						{
							_window_add_input_pressed( mouse_right );
							skip;
						}

						when( 4 )
						{
							_window_add_input_pressed( mouse_wheel_up );
							_window_add_input_released( mouse_wheel_up );
							skip;
						}

						when( 5 )
						{
							_window_add_input_pressed( mouse_wheel_down );
							_window_add_input_released( mouse_wheel_down );
							skip;
						}

						when( 6 )
						{
							_window_add_input_pressed( mouse_wheel_right );
							_window_add_input_released( mouse_wheel_right );
							skip;
						}

						when( 7 )
						{
							_window_add_input_pressed( mouse_wheel_left );
							_window_add_input_released( mouse_wheel_left );
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
							_window_add_input_released( mouse_left );
							skip;
						}

						when( Button2 )
						{
							_window_add_input_released( mouse_middle );
							skip;
						}

						when( Button3 )
						{
							_window_add_input_released( mouse_right );
							skip;
						}
					}
					skip;
				}
			#elif OS_WINDOWS
				when( WM_LBUTTONDOWN )
				{
					_window_add_input_pressed( mouse_left );
					skip;
				}

				when( WM_MBUTTONDOWN )
				{
					_window_add_input_pressed( mouse_middle );
					skip;
				}

				when( WM_RBUTTONDOWN )
				{
					_window_add_input_pressed( mouse_right );
					skip;
				}

				when( WM_LBUTTONUP )
				{
					_window_add_input_released( mouse_left );
					skip;
				}

				when( WM_MBUTTONUP )
				{
					_window_add_input_released( mouse_middle );
					skip;
				}

				when( WM_RBUTTONUP )
				{
					_window_add_input_released( mouse_right );
					skip;
				}

				when( WM_MOUSEWHEEL )
				{
					if( GET_WHEEL_DELTA_WPARAM( wp ) > 0 )
					{
						_window_add_input_pressed( mouse_wheel_up );
						_window_add_input_released( mouse_wheel_up );
					}
					else
					{
						_window_add_input_pressed( mouse_wheel_down );
						_window_add_input_released( mouse_wheel_down );
					}
					skip;
				}

				when( WM_MOUSEHWHEEL )
				{
					if( GET_WHEEL_DELTA_WPARAM( wp ) > 0 )
					{
						_window_add_input_pressed( mouse_wheel_right );
						_window_add_input_released( mouse_wheel_right );
					}
					else
					{
						_window_add_input_pressed( mouse_wheel_left );
						_window_add_input_released( mouse_wheel_left );
					}
					skip;
				}
			#endif
		#endif

		when( _window_event_close )
		{
			#if OS_LINUX
				if( to( Atom, e->xclient.data.l[ 0 ] ) is window_ref->event_delete )
				{
					window_ref->state = window_state_closing;
				}
			#elif OS_WINDOWS
				PostQuitMessage( 0 );
				window_ref->state = window_state_closing;
			#endif

			out success;
		}

		other skip;
	}

	exit_events:
	#if OS_WINDOWS
		out DefWindowProc( h, event, wp, lp );
	#elif OS_LINUX
		out success;
	#endif
}

#pragma endregion

#pragma endregion hidden

////////////////////////////////
#pragma region | window / visible

#define window_ref_update( WINDOW_REF ) _window_ref_update( WINDOW_REF )
#define window_ref_update_now( WINDOW_REF ) _window_ref_update_now( WINDOW_REF )

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

fn window_ref_toggle_fullscreen( window ref const window_ref )
{
	#if OS_LINUX
		XEvent event = { 0 };
		event.type = ClientMessage;
		event.xclient.window = window_ref->handle;
		event.xclient.message_type = XInternAtom( program.display, "_NET_WM_STATE", no );
		event.xclient.format = 32;
		event.xclient.data.l[ 0 ] = 2;
		event.xclient.data.l[ 1 ] = XInternAtom( program.display, "_NET_WM_STATE_FULLSCREEN", no );
		event.xclient.data.l[ 3 ] = 1;

		XSendEvent( program.display, DefaultRootWindow( program.display ), no, SubstructureNotifyMask | SubstructureRedirectMask, ref_of( event ) );
	#elif OS_WINDOWS
		DWORD style = GetWindowLong( window_ref->handle, GWL_STYLE );

		if( window_ref->fullscreen is no )
		{
			MONITORINFO mi = { sizeof( mi ) };
			GetWindowPlacement( window_ref->handle, ref_of( window_ref->prev_placement ) );
			GetMonitorInfo( MonitorFromWindow( window_ref->handle, MONITOR_DEFAULTTONEAREST ), ref_of( mi ) );
			SetWindowLong( window_ref->handle, GWL_STYLE, style & ~ WS_OVERLAPPEDWINDOW );
			SetWindowPos( window_ref->handle, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_FRAMECHANGED );
		}
		else
		{
			SetWindowLong( window_ref->handle, GWL_STYLE, style | WS_OVERLAPPEDWINDOW );
			SetWindowPlacement( window_ref->handle, ref_of( window_ref->prev_placement ) );
			SetWindowPos( window_ref->handle, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
		}
	#endif

	window_ref->fullscreen = pick( window_ref->fullscreen is yes, no, yes );
}

embed view ref const window_ref_make_view_ref( window ref const window_ref, canvas const canvas, view_ref_fn const fn_draw )
{
	iter( view_id, window_max_views )
	{
		view ref const view_ref = ref_of( window_ref->views[ view_id ] );
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
		XMoveWindow( program.display, window_ref->handle, ( display_get_width() - window_ref->size.w ) >> 1, ( display_get_height() - window_ref->size.h ) >> 1 );
		XSync( program.display, no );
	#elif OS_WINDOWS
		SetWindowPos( window_ref->handle, nothing, ( display_get_width() - window_ref->size.w ) >> 1, ( display_get_height() - window_ref->size.h ) >> 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
	#endif
}

////////////////
#pragma region | - cursor

fn window_ref_set_cursor( window ref const window_ref, cursor_type const cursor )
{
	window_ref->changed_cursor = yes;
	#if OS_LINUX
		perm Cursor cache[ 256 ] = { 0 };
		if( not cache[ cursor ] )
		{
			cache[ cursor ] = XCreateFontCursor( program.display, cursor );
		}
		XDefineCursor( program.display, window_ref->handle, cache[ cursor ] );
	#elif OS_WINDOWS
		SetCursor( LoadCursor( NULL, MAKEINTRESOURCE( cursor ) ) );
	#endif
}

#pragma endregion

#pragma endregion visible

#pragma endregion window

////////////////////////////////////////////////////////////////
#pragma region - program

#if OS_WINDOWS and not defined( _INC_MMSYSTEM ) and not defined( _INC_TIMEAPI )
	__declspec( dllimport ) n4 __stdcall timeBeginPeriod( n4 uPeriod );
	__declspec( dllimport ) n4 __stdcall timeEndPeriod( n4 uPeriod );
#endif

////////////////////////////////
#pragma region | program / hidden

fn _program_setup()
{
	n2 const program_path_size = program_get_path( program.path );

	byte parent_path[ path_max_size ];
	bytes_copy( parent_path, program.path, program_path_size );
	path_up_folder( parent_path );

	#if OS_LINUX
		chdir( parent_path );

		program.display = XOpenDisplay( nothing );
		if_something( program.display )
		{
			XkbSetDetectableAutoRepeat( program.display, yes, nothing );
			i4 const screen = DefaultScreen( program.display );
			program.visual = DefaultVisual( program.display, screen );
			program.format = XRenderFindVisualFormat( program.display, program.visual );
		}
	#elif OS_WINDOWS
		SetCurrentDirectoryA( parent_path );

		program.icon = LoadIcon( GetModuleHandle( nothing ), MAKEINTRESOURCE( 1 ) );
		timeBeginPeriod( 1 );
		#ifdef DEBUG
			AllocConsole();
			freopen( "CONOUT$", "w", stdout );
		#endif
	#endif
}

fn _program_process_events()
{
	#if OS_LINUX
		XFlush( program.display );
		window_event event;
		while( XPending( program.display ) )
		{
			XNextEvent( program.display, ref_of( event ) );

			iter( window_id, program.windows_count )
			{
				if( program.windows[ window_id ].handle is event.xany.window )
				{
					_window_ref_process_event( ref_of( program.windows[ window_id ] ), event.type, ref_of( event ) );
					skip;
				}
			}
		}
	#elif OS_WINDOWS
		window_event event;
		while( PeekMessage( ref_of( event ), 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( ref_of( event ) );
			DispatchMessage( ref_of( event ) );
		}
	#endif
}

fn _program_wait_until( nano const deadline )
{
	#define _program_wait_max_drift nano_per_milli
	#define _program_wait_spin_headroom ( 100 * nano_per_micro )
	#define _program_wait_chunk ( 2 * nano_per_milli )

	perm nano overhead = _program_wait_max_drift;

	#if OS_LINUX
		XFlush( program.display );
	#endif

	nano now = nano_now();
	loop
	{
		out_if( now >= deadline );

		#if OS_LINUX
			out_if( XPending( program.display ) );
		#elif OS_WINDOWS
			MSG msg;
			out_if( PeekMessageW( ref_of( msg ), nothing, 0, 0, PM_NOREMOVE ) );
		#endif

		nano const remaining = deadline - now;
		if( remaining <= overhead + _program_wait_spin_headroom )
		{
			while( now < deadline )
			{
				now = nano_now();
			}
			out;
		}

		nano const wake_at = deadline - overhead;
		nano sleep_target = wake_at;
		if( wake_at - now > _program_wait_chunk )
		{
			sleep_target = now + _program_wait_chunk;
		}

		nano const sleep_for = sleep_target - now;
		nano_sleep_until( sleep_target );

		nano const after = nano_now();
		nano const elapsed = after - now;
		nano drift = pick( elapsed > sleep_for, elapsed - sleep_for, 0 );

		if( drift > _program_wait_max_drift )
		{
			drift = _program_wait_max_drift;
		}

		overhead = pick( drift > overhead, drift, overhead - ( ( overhead - drift ) >> 5 ) );

		now = after;
	}
}

fn _program_loop()
{
	loop
	{
		_program_process_events();

		n1 count = program.windows_count;
		flag ready = yes;

		iter( window_id, program_max_windows )
		{
			window ref const window_ref = ref_of( program.windows[ window_id ] );

			if( window_ref->state is window_state_unknown ) next;

			with( window_ref->state )
			{
				when( window_state_preparing )
				{
					window_ref_center( window_ref );
					window_ref->state = window_state_opening;
					ready = no;
					skip;
				}

				when( window_state_opening )
				{
					window_ref_show( window_ref );

					#if OS_LINUX
						malloc_trim( 0 );
					#elif OS_WINDOWS
						SetProcessWorkingSetSize( GetCurrentProcess(), to( SIZE_T, -1 ), to( SIZE_T, -1 ) );
					#endif

					window_ref->state = window_state_ready;
					skip;
				}

				when( window_state_closing )
				{
					#if OS_LINUX
						XDestroyWindow( program.display, window_ref->handle );
						XFlush( program.display );
					#elif OS_WINDOWS
						DestroyWindow( window_ref->handle );
					#endif

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

		if( program.fps > 0.0 )
		{
			if( program.epoch is 0 )
			{
				program.epoch = nano_now();
				program.tick_count = 0;
				program.next_tick = program.epoch;
			}

			while( _windows_consume_tick() )
			{
				iter( window_id, program.windows_count )
				{
					window ref const w = ref_of( program.windows[ window_id ] );
					_window_ref_tick( w );
					w->call_tick = no;
				}
			}
		}

		if( program.fps <= 0.0 or program.tick_events is yes )
		{
			iter( window_id, program.windows_count )
			{
				window ref const w = ref_of( program.windows[ window_id ] );
				next_if( w->call_tick isnt yes );
				_window_ref_tick( w );
				w->call_tick = no;
			}
		}

		if( ready )
		{
			if( program.fps > 0.0 and program.tick_events is no )
			{
				_program_wait_until( program.next_tick );
			}
			else
			{
				i4 timeout_ms = -1;
				if( program.fps > 0.0 )
				{
					nano const now = nano_now();
					if( program.next_tick > now )
					{
						nano const remaining = program.next_tick - now;
						timeout_ms = i4( ( remaining + ( nano_per_milli - 1 ) ) / nano_per_milli );
					}
					else
					{
						timeout_ms = 0;
					}
				}

				#if OS_LINUX
					XFlush( program.display );
					if( not XPending( program.display ) )
					{
						struct pollfd pfd = { ConnectionNumber( program.display ), POLLIN, 0 };
						poll( ref_of( pfd ), 1, timeout_ms );
					}
				#elif OS_WINDOWS
					MsgWaitForMultipleObjects( 0, nothing, FALSE, pick( timeout_ms < 0, INFINITE, n4( timeout_ms ) ), QS_ALLINPUT );
				#endif
			}
		}
	}
}

fn _program_close()
{
	#if OS_LINUX
		//
	#elif OS_WINDOWS
		timeEndPeriod( 1 );
	#endif
}

#pragma endregion hidden

////////////////////////////////
#pragma region | program / visible

embed window ref const program_make_window_ref( byte const ref const name, n2x2 const size, window_ref_fn const fn_resize, window_ref_fn const fn_tick )
{
	n2 window_index = 0;

	while( program.windows[ window_index ].state isnt window_state_unknown )
	{
		window_index += 1;
	}

	window ref const window_ref = ref_of( program.windows[ window_index ] );
	program.windows_count += 1;

	bytes_paste( window_ref->name, name );
	window_ref->size = size;
	window_ref->state = window_state_preparing;
	window_ref->fn_resize = fn_resize;
	window_ref->fn_tick = fn_tick;
	window_ref->call_tick = yes;

	#if OS_LINUX
		i4 const screen = DefaultScreen( program.display );
		i4 const depth = DefaultDepth( program.display, screen );

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
		wclass.hIcon = program.icon;
		RegisterClass( ref_of( wclass ) );

		RECT rect = { 0, 0, window_ref->size.w, window_ref->size.h };
		AdjustWindowRect( ref_of( rect ), WS_OVERLAPPEDWINDOW, FALSE );

		window_ref->handle = CreateWindow( window_ref->name, window_ref->name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nothing, nothing, program.instance, nothing );

		window_ref->window_dc = GetDC( window_ref->handle );

		window_ref->image.bmiHeader.biSize = size_of( window_ref->image.bmiHeader );
		window_ref->image.bmiHeader.biPlanes = 1;
		window_ref->image.bmiHeader.biBitCount = 32;
		window_ref->image.bmiHeader.biCompression = BI_RGB;

		SetWindowLongPtr( window_ref->handle, GWLP_USERDATA, to( LONG_PTR, window_ref ) );
	#endif

	out window_ref;
}

#pragma endregion visible

#pragma endregion program

#pragma endregion definitions

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region - START
//

#undef start
#define start\
	fn _program_start( i4 start_inputs_count, byte const ref const ref start_inputs );\
	_start_fn\
	{\
		_program_setup();\
		_program_start( start_inputs_count, start_inputs );\
		_program_loop();\
		_program_close();\
		exit( success );\
	}\
	fn _program_start( i4 start_inputs_count, byte const ref const ref start_inputs )

#pragma endregion start

#pragma endregion start

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
