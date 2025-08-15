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

type_from( n1x4 ) pixel;

#define pixel( R, G, B, A ) make( pixel, .r = B, .g = G, .b = R, .a = A )

//

#define index_2d( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

type( canvas )
{
	pixel ref pixels;
	n2x2 size;
};

global perm canvas ref current_canvas_ref = nothing;

#define _canvas( W, H ) make( canvas, .pixels = to( pixel ref, new_ref( pixel, W * H ) ), .size = make( n2x2, .w = W, .h = H ) )
#define _eval_canvas( WIDTH_HEIGHT... ) _canvas( WIDTH_HEIGHT )
#define canvas( WIDTH_HEIGHT... ) _eval_canvas( DEFAULTS( ( 1, 1 ), WIDTH_HEIGHT ) )

fn canvas_resize( canvas const_ref c, const n2 width, const n2 height )
{
	out_if( c->size.w is width and c->size.h is height );
	c->pixels = ref_resize( c->pixels, ( c->size.w * c->size.h ) << 2, ( width * height ) << 2 );
	c->size.w = width;
	c->size.h = height;
}

fn canvas_fill( canvas const_ref c, const pixel color )
{
	if_all( color.r is color.g, color.g is color.b, color.b is color.a )
	{
		bytes_fill( c->pixels, color.r, i4( c->size.w ) * i4( c->size.h ) * 4 );
	}
	else
	{
		iter( i, i4( c->size.w ) * i4( c->size.h ) )
		{
			c->pixels[ i ] = color;
		}
	}
}

fn canvas_clear( canvas const_ref c )
{
	bytes_clear( c->pixels, i4( c->size.w ) * i4( c->size.h ) * 4 );
}

//

#define _if_canvas_pixel_safe( CANVAS, X, Y ) if( point_in_size( X, Y, CANVAS.size.w, CANVAS.size.h ) )
#define _canvas_get_pixel_index( CANVAS, INDEX ) CANVAS.pixels[ ( INDEX ) ]

#define canvas_get_pixel_row( CANVAS, X, ROW ) _canvas_get_pixel_index( CANVAS, i4( X ) + ( ROW ) )
#define canvas_get_pixel( CANVAS, X, Y ) canvas_get_pixel_row( CANVAS, X, i4( Y ) * i4( CANVAS.size.w ) )
#define canvas_get_pixel_safe( CANVAS, X, Y ) _if_canvas_pixel_safe( CANVAS, X, Y ) canvas_get_pixel( CANVAS, X, Y )

#define get_pixel( X, Y ) canvas_get_pixel( current_canvas_ref, X, Y )
#define get_pixel_safe( X, Y ) canvas_get_pixel_safe( current_canvas_ref, X, Y )

//

#define _canvas_draw_pixel_index( CANVAS, INDEX, PIXEL ) ( _canvas_get_pixel_index( CANVAS, INDEX ) ) = ( PIXEL )

#define canvas_draw_pixel_row( CANVAS, X, ROW, PIXEL ) ( canvas_get_pixel_row( CANVAS, X, ROW ) ) = ( PIXEL )
#define canvas_draw_pixel( CANVAS, X, Y, PIXEL ) ( canvas_get_pixel( CANVAS, X, Y ) ) = ( PIXEL )
#define canvas_draw_pixel_safe( CANVAS, X, Y, PIXEL ) canvas_get_pixel_safe( CANVAS, X, Y ) = ( PIXEL )

#define draw_pixel( X, Y, PIXEL ) canvas_draw_pixel( val_of( current_canvas_ref ), X, Y, PIXEL )
#define draw_pixel_safe( X, Y, PIXEL ) canvas_draw_pixel_safe( val_of( current_canvas_ref ), X, Y, PIXEL )

///////

#define fn_line( Ax, Ay, Bx, By, CODE )\
	START_DEF\
	{\
		temp i2 _x = i2( Ax );\
		temp i2 _y = i2( Ay );\
		temp i2 _x2 = i2( Bx );\
		temp i2 _y2 = i2( By );\
		temp i2 dx = i2_abs( _x2 - _x );\
		temp i2 sx = pick( _x < _x2, 1, -1 );\
		temp i2 dy = -i2_abs( _y2 - _y );\
		temp i2 sy = pick( _y < _y2, 1, -1 );\
		temp i2 err = dx + dy;\
		temp i2 e2;\
		loop\
		{\
			skip_if( _x is _x2 and _y is _y2 );\
			CODE;\
			e2 = err << 1;\
			if( e2 >= dy )\
			{\
				skip_if( _x is _x2 );\
				err += dy;\
				_x += sx;\
			}\
			if( e2 <= dx )\
			{\
				skip_if( _y is _y2 );\
				err += dx;\
				_y += sy;\
			}\
		}\
	}\
	END_DEF

#define _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, SUFFIX... ) fn_line( Ax, Ay, Bx, By, canvas_draw_pixel##SUFFIX( CANVAS, _x, _y, PIXEL ) );
#define canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL )
#define canvas_draw_line_safe( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _safe )

#define draw_line( Ax, Ay, Bx, By, PIXEL ) canvas_draw_line( val_of( current_canvas_ref ), Ax, Ay, Bx, By, PIXEL )
#define draw_line_safe( Ax, Ay, Bx, By, PIXEL ) canvas_draw_line_safe( val_of( current_canvas_ref ), Ax, Ay, Bx, By, PIXEL )

//

#define _wrap_coord( COORD, SIZE ) ( ( ( COORD ) + ( SIZE ) ) mod ( SIZE ) )
#define canvas_draw_pixel_wrap( CANVAS, X, Y, PIXEL ) canvas_draw_pixel( CANVAS, _wrap_coord( i4( X ), i4( CANVAS.size.w ) ), _wrap_coord( i4( Y ), i4( CANVAS.size.h ) ), PIXEL )
#define canvas_draw_line_wrap( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _wrap )
#define draw_line_wrap( Ax, Ay, Bx, By, PIXEL ) canvas_draw_line_wrap( val_of( current_canvas_ref ), Ax, Ay, Bx, By, PIXEL )

///////

group( anchor )
{
	anchor_top_left,
	anchor_top_center,
	anchor_top_right,
	anchor_middle_left,
	anchor_middle_center,
	anchor_middle_right,
	anchor_bottom_left,
	anchor_bottom_center,
	anchor_bottom_right
};

///////

type_from( PICK( OS_LINUX, Window, HWND ) ) os_handle;
type_from( PICK( OS_LINUX, Display ref, HDC ) ) os_display;
type_from( PICK( OS_LINUX, XImage ref, BITMAPINFO ) ) os_image;
type_from( PICK( OS_LINUX, XEvent, MSG ) ) os_event;

object( window )
{
	os_handle handle;
	os_display display;
	os_image image;
	//
	#if OS_LINUX
		GC gc;
		Picture pic;
		Picture pic_target;
		Pixmap pixmap;
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
	byte inputs[ PICK( OS_LINUX, 512, 256 ) ];
	byte inputs_pressed[ 32 ];
	n1 inputs_pressed_count;
	byte inputs_released[ 32 ];
	n1 inputs_released_count;
};

global perm window current_window = nothing;

global perm window alive_windows[ 32 ];
global perm n1 alive_windows_count = 0;

global perm const byte ref OS_INPUT_MAP = nothing;

#define INPUT_MASK_PRESSED 0x1
#define INPUT_MASK_HELD 0x2
#define INPUT_MASK_RELEASED 0x4

#define key_pressed( KEY ) ( current_window->inputs[ input_##KEY ] &INPUT_MASK_PRESSED )
#define key_held( KEY ) ( current_window->inputs[ input_##KEY ] &INPUT_MASK_HELD )
#define key_released( KEY ) ( current_window->inputs[ input_##KEY ] &INPUT_MASK_RELEASED )

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

	this->scale = n2_max( scale, 1 );

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

object_fn( window, set_buffer_max, const n2 width, const n2 height )
{
	out_if_nothing( this );

	if( this->buffer_max.w isnt width or this->buffer_max.h isnt height )
	{
		this->buffer_max.w = width;
		this->buffer_max.h = height;

		window_update_scale( this );
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

	out_if( this->buffer.size.w is buffer_w and this->buffer.size.h is buffer_h );
	//
	canvas_resize( ref_of( this->buffer ), buffer_w, buffer_h );
	//
	#if OS_LINUX
		this->image->data = to( byte ref, this->buffer.pixels );
		this->image->width = this->buffer.size.w;
		this->image->height = this->buffer.size.h;
		this->image->bytes_per_line = this->buffer.size.w * 4;

		XFreePixmap( this->display, this->pixmap );
		this->pixmap = XCreatePixmap( this->display, this->handle, this->buffer.size.w, this->buffer.size.h, DefaultDepth( this->display, DefaultScreen( this->display ) ) );

		XRenderFreePicture( this->display, this->pic );
		this->pic = XRenderCreatePicture( this->display, this->pixmap, XRenderFindVisualFormat( this->display, DefaultVisual( this->display, DefaultScreen( this->display ) ) ), 0, 0 );
		XRenderSetPictureTransform( this->display, this->pic, ref_of( this->transform ) );
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

fn _window_update( const window this )
{
	out_if_any( this is nothing, this->buffer.size.w <= 1, this->buffer.size.h <= 1 );

	temp nano now = get_nano();
	this->delta_time = r8( now - this->past_nano ) / r8( nano_per_sec );
	this->total_time += this->delta_time;
	this->past_nano = now;
	++this->tick;
	call( this, tick_fn );

	if( this->refresh )
	{
		this->refresh = no;
		call( this, draw_fn );

		temp const n2 scaled_width = this->buffer.size.w * this->scale;
		temp const n2 scaled_height = this->buffer.size.h * this->scale;

		temp const i4 overflow_w = i4( this->size_target.w ) - i4( scaled_width );
		temp const i4 overflow_h = i4( this->size_target.h ) - i4( scaled_height );

		temp i4 x = 0;
		temp i4 y = 0;

		with( this->buffer_anchor )
		{
			when( anchor_top_center )
			{
				x = overflow_w / 2;
				skip;
			}

			when( anchor_top_right )
			{
				x = overflow_w;
				skip;
			}

			when( anchor_middle_left )
			{
				y = overflow_h / 2;
				skip;
			}

			when( anchor_middle_center )
			{
				x = overflow_w / 2;
				y = overflow_h / 2;
				skip;
			}

			when( anchor_middle_right )
			{
				x = overflow_w;
				y = overflow_h / 2;
				skip;
			}

			when( anchor_bottom_left )
			{
				y = overflow_h;
				skip;
			}

			when( anchor_bottom_center )
			{
				x = overflow_w / 2;
				y = overflow_h;
				skip;
			}

			when( anchor_bottom_right )
			{
				x = overflow_w;
				y = overflow_h;
				skip;
			}
		}

		#if OS_LINUX
			if( this->scale > 1 )
			{
				XPutImage( this->display, this->pixmap, this->gc, this->image, 0, 0, 0, 0, this->buffer.size.w, this->buffer.size.h );
				XRenderComposite( this->display, PictOpSrc, this->pic, None, this->pic_target, 0, 0, 0, 0, x, y, scaled_width, scaled_height );
			}
			else
			{
				XPutImage( this->display, this->handle, this->gc, this->image, 0, 0, x, y, this->buffer.size.w, this->buffer.size.h );
			}
			XSync( this->display, no );
		#elif OS_WINDOWS
			if( this->scale > 1 )
			{
				SetStretchBltMode( this->display, COLORONCOLOR );
				StretchDIBits( this->display, x, y, scaled_width, scaled_height, 0, 0, this->buffer.size.w, this->buffer.size.h, this->buffer.pixels, ref_of( this->image ), DIB_RGB_COLORS, SRCCOPY );
			}
			else
			{
				SetDIBitsToDevice( this->display, x, y, this->buffer.size.w, this->buffer.size.h, 0, 0, 0, this->buffer.size.h, this->buffer.pixels, ref_of( this->image ), DIB_RGB_COLORS );
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

group( window_event_type, n2 )
{
	window_event_resize = PICK( OS_LINUX, ConfigureNotify, WM_SIZE ),
	window_event_refresh = PICK( OS_LINUX, Expose, WM_PAINT ),
	window_event_close = PICK( OS_LINUX, ClientMessage, WM_DESTROY ),
	window_event_key_activate = PICK( OS_LINUX, KeyPress, WM_KEYDOWN ),
	window_event_key_deactivate = PICK( OS_LINUX, KeyRelease, WM_KEYUP )
};

#if OS_LINUX
	embed out_state window_process_event( const window w, const window_event_type event, const os_event ref e )
#elif OS_WINDOWS
	embed LRESULT CALLBACK window_process_event( const os_handle h, const window_event_type event, const WPARAM wp, const LPARAM lp )
#endif
{
	#if OS_WINDOWS
		temp window w = to( window, GetWindowLongPtr( h, GWLP_USERDATA ) );
	#endif
	//
	jump_if_nothing( w ) exit_events;
	//
	temp flag is_input = no;
	//
	with( event )
	{
		#if OS_WINDOWS
			when( WM_ENTERSIZEMOVE )
			{
				w->wm_timer = yes;
				SetTimer( h, 1, 0, nothing );
				skip;
			}

			when( WM_EXITSIZEMOVE )
			{
				KillTimer( h, 1 );
				w->wm_resize = no;
				w->wm_timer = no;
				skip;
			}

			when( WM_TIMER )
			{
				if( wp is 1 )
				{
					if( w->wm_resize is yes )
					{
						_window_resize( w );
						w->wm_resize = no;
					}

					_window_update( w );
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

		when( window_event_resize )
		{
			w->refresh = yes;
			#if OS_WINDOWS
				w->wm_resize = yes;
				_window_set_size( w, LOWORD( lp ), HIWORD( lp ) );
				if( w->wm_timer is no )
				{
					_window_resize( w );
				}
			#elif OS_LINUX
				_window_set_size( w, e->xconfigure.width, e->xconfigure.height );
				_window_resize( w );
			#endif
			skip;
		}

		when( window_event_refresh )
		{
			w->refresh = yes;
			skip;
		}

		when( window_event_key_activate )
		{
			temp const byte key = OS_INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( w->display, e->xkey.keycode, 0, 0 ) & 0x1FF, wp & 0xff ) ];
			if( key isnt 0 and not( w->inputs[ key ] &INPUT_MASK_HELD ) )
			{
				w->inputs[ key ] |= INPUT_MASK_PRESSED | INPUT_MASK_HELD;
				w->inputs_pressed[ w->inputs_pressed_count++ ] = key;
			}
			//
			is_input = yes;
			skip;
		}

		when( window_event_key_deactivate )
		{
			temp const byte key = OS_INPUT_MAP[ PICK( OS_LINUX, XkbKeycodeToKeysym( w->display, e->xkey.keycode, 0, 0 ) & 0x1FF, wp & 0xff ) ];
			if( key isnt 0 )
			{
				w->inputs[ key ] = INPUT_MASK_RELEASED;
				w->inputs_released[ w->inputs_released_count++ ] = key;
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

		other skip;
	}
	//
	if( is_input is yes )
	{
		call( w, input_fn );
	}
	//
	exit_events:
	#if OS_WINDOWS
		out DefWindowProc( h, event, wp, lp );
	#elif OS_LINUX
		out success;
	#endif
}

embed window new_window( const n2 width, const n2 height )
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
		XSelectInput( out_window->display, out_window->handle, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask );
		XkbSetDetectableAutoRepeat( out_window->display, yes, nothing );

		out_window->image = XCreateImage( out_window->display, DefaultVisual( out_window->display, screen ), DefaultDepth( out_window->display, screen ), ZPixmap, 0, to( byte ref, out_window->buffer.pixels ), width, height, 32, 0 );
		out_window->gc = XCreateGC( out_window->display, out_window->handle, 0, 0 );

		out_window->pixmap = XCreatePixmap( out_window->display, out_window->handle, width, height, DefaultDepth( out_window->display, screen ) );
		XRenderPictFormat ref fmt = XRenderFindVisualFormat( out_window->display, DefaultVisual( out_window->display, screen ) );
		out_window->pic = XRenderCreatePicture( out_window->display, out_window->pixmap, fmt, 0, 0 );
		out_window->pic_target = XRenderCreatePicture( out_window->display, out_window->handle, fmt, 0, 0 );

		XRenderSetPictureFilter( out_window->display, out_window->pic, "nearest", 0, 0 );

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
		XMoveWindow( this->display, this->handle, ( DisplayWidth( this->display, DefaultScreen( this->display ) ) - this->size_target.w ) / 2, ( DisplayHeight( this->display, DefaultScreen( this->display ) ) - this->size_target.h ) / 2 );
		XSync( this->display, no );
	#elif OS_WINDOWS
		SetWindowPos( this->handle, NULL, ( GetSystemMetrics( SM_CXSCREEN ) - this->size_target.w ) / 2, ( GetSystemMetrics( SM_CYSCREEN ) - this->size_target.h ) / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
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
	current_canvas_ref = ref_of( this->buffer );

	if( this->tick is 0 )
	{
		this->fps_target = 120;
		this->target_frame_nano = to( nano, r8( nano_per_sec ) / this->fps_target );
		this->start_nano = get_nano();
		this->past_nano = this->start_nano;
		call( this, start_fn );
		_window_resize( this );
	}
	else if( this->tick is 1 )
	{
		this->refresh = yes;
		window_center( this );
		window_show( this );
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
	n4 frames;
	audio_channel channel;
};

embed audio load_audio( const byte const_ref wav_path )
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

	temp const byte ref ptr = f.mapped_bytes + 36;
	temp n4 data_size = 0;
	while( ptr < f.mapped_bytes + f.size )
	{
		if( bytes_compare( ptr, "data", 4 ) is 0 )
		{
			data_size = val_of( to( n4 ref, ptr + 4 ) );
			ptr += 8;
			skip;
		}
		ptr += 8 + val_of( to( n4 ref, ptr + 4 ) );
	}

	out_if( data_size is 0 ) out_audio;

	temp const n4 samples = data_size / ( bits / 8 );
	out_audio.frames = samples / channels;
	out_audio.channel = to( audio_channel, channels );
	out_audio.data = new_bytes( samples * 4 );

	if( bits is 16 )
	{
		temp const i2 const_ref src = to( i2 const_ref, ptr );
		iter( s, samples )
		{
			out_audio.data[ s ] = r4( src[ s ] ) / 32768.0;
		}
	}
	else
	{ // 8 bits
		temp const n1 const_ref src = to( n1 const_ref, ptr );
		iter( s, samples )
		{
			out_audio.data[ s ] = ( r4( src[ s ] ) - 128.0 ) / 128.0;
		}
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
	thread process;
	thread_lock lock;
	flag running;
	//
	#if OS_WINDOWS
		anon ref hdr[ 2 ];
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
		temp const i4 frames = pick( samples < ( i->audio_ref->frames - i->position ), samples, i->audio_ref->frames - i->position );
		temp const r4 left_gain = i->volume * ( 1.0 - i->pan ) / 2.0;
		temp const r4 right_gain = i->volume * ( 1.0 + i->pan ) / 2.0;

		iter( f, frames )
		{
			temp const r4 const_ref p = ref_of( i->audio_ref->data[ ( i->position + f ) * n4( i->audio_ref->channel ) ] );
			buffer[ f << 1 ] += p[ 0 ] * left_gain;
			buffer[ ( f << 1 ) + 1 ] += p[ i->audio_ref->channel - 1 ] * right_gain;
		}
		if( ( i->position += frames ) >= i->audio_ref->frames ) i->playing = no;
	}

	iter( sample, samples2 )
	{
		temp const r4 s = buffer[ sample ];
		output[ sample ] = pick( s > 1, max_i2, pick( s < -1, -max_i2, s * max_i2 ) );
	}
}

embed anon ref audio_mixer_thread_fn( anon ref p )
{
	audio_mixer ref m = to( audio_mixer ref, p );

	#if OS_WINDOWS
		i2 buffer1[ 4096 ];
		i2 buffer2[ 4096 ];
		WAVEHDR hdr1 = { to( byte ref, buffer1 ), 8192, 0, 0, 0, 0, 0, 0 };
		WAVEHDR hdr2 = { to( byte ref, buffer2 ), 8192, 0, 0, 0, 0, 0, 0 };

		lock_thread( m->lock );
		audio_mixer_process( m, buffer1, 2048 );
		unlock_thread( m->lock );
		wavePrepare( m->device, ref_of( hdr1 ), size_of( WAVEHDR ) );
		waveWrite( m->device, ref_of( hdr1 ), size_of( WAVEHDR ) );

		i4 current_buffer = 2;
	#else
		i2 buffer[ 4096 ];
	#endif

	while( m->running )
	{
		#if OS_LINUX
			lock_thread( m->lock );
			audio_mixer_process( m, buffer, 2048 );
			unlock_thread( m->lock );
			snd_pcm_writei( m->device, buffer, 2048 );
		#elif OS_WINDOWS
			i2 ref current_buf = ( current_buffer == 1 ) ? buffer1 : buffer2;
			WAVEHDR ref current_hdr = ( current_buffer == 1 ) ? ref_of( hdr1 ) : ref_of( hdr2 );
			WAVEHDR ref prev_hdr = ( current_buffer == 1 ) ? ref_of( hdr2 ) : ref_of( hdr1 );

			lock_thread( m->lock );
			audio_mixer_process( m, current_buf, 2048 );
			unlock_thread( m->lock );

			wavePrepare( m->device, current_hdr, size_of( WAVEHDR ) );
			waveWrite( m->device, current_hdr, size_of( WAVEHDR ) );

			if( ( prev_hdr->dwFlags & 1 ) is 0 )
			{
				while( not( prev_hdr->dwFlags & 1 ) ) Sleep( 1 );
				waveUnprepare( m->device, prev_hdr, size_of( WAVEHDR ) );
			}

			current_buffer = ( current_buffer is 1 ) ? 2 : 1;
		#endif
	}
	out nothing;
}

embed out_state audio_mixer_start( audio_mixer ref m )
{
	bytes_clear( m, size_of( audio_mixer ) );
	thread_add_lock( m->lock );

	#if OS_LINUX
		if( snd_pcm_open( to( snd_pcm_t ref ref, ref_of( m->device ) ), "default", 0, 0 ) < 0 )
		{
			out failure;
		}
		snd_pcm_set_params( m->device, 2, 3, 2, 44100, 1, 100000 );
	#elif OS_WINDOWS
		if_nothing( winmm_dll )
		{
			winmm_dll = LoadLibrary( "winmm.dll" );
			if_nothing( winmm_dll ) out failure;
			waveOpen = to( type_of( waveOpen ), GetProcAddress( winmm_dll, "waveOutOpen" ) );
			waveClose = to( type_of( waveClose ), GetProcAddress( winmm_dll, "waveOutClose" ) );
			waveWrite = to( type_of( waveWrite ), GetProcAddress( winmm_dll, "waveOutWrite" ) );
			wavePrepare = to( type_of( wavePrepare ), GetProcAddress( winmm_dll, "waveOutPrepareHeader" ) );
			waveUnprepare = to( type_of( waveUnprepare ), GetProcAddress( winmm_dll, "waveOutUnprepareHeader" ) );
		}

		WAVEFORMATEX fmt = { 1, 2, 44100, 176400, 4, 16 };
		if( waveOpen( to( HWAVEOUT ref, ref_of( m->device ) ), -1, ref_of( fmt ), 0, 0, 0 ) )
		{
			out failure;
		}

		iter( i, 2 )
		{
			WAVEHDR ref h = new_ref( WAVEHDR );
			h->lpData = new_bytes( 8192 );
			h->dwBufferLength = 8192;
			wavePrepare( m->device, h, size_of( WAVEHDR ) );
			m->hdr[ i ] = h;
		}
	#endif

	m->running = yes;
	m->process = new_cpu_thread( audio_mixer_thread_fn, m );
	out success;
}

fn audio_mixer_stop( audio_mixer ref m )
{
	m->running = no;
	thread_join( m->process );

	#if OS_LINUX
		snd_pcm_close( m->device );
	#elif OS_WINDOWS
		waveClose( m->device );
		iter( i, 2 )
		{
			WAVEHDR ref h = m->hdr[ i ];
			if( h )
			{
				delete_ref( h->lpData );
				delete_ref( h );
			}
		}
	#endif

	thread_remove_lock( m->lock );
}

type_from( i4 ) audio_id;

embed audio_id audio_play( audio_mixer const_ref mixer, const audio const_ref a, const r4 volume, const r4 pan )
{
	lock_thread( mixer->lock );
	iter( id, audio_max_instances )
	{
		next_if( mixer->instances[ id ] .playing is yes );
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
		mixer->instances[ id ] .playing = no;
	}
}

fn audio_set( audio_mixer const_ref mixer, audio_id id, const r4 volume, const r4 pan )
{
	if_all( id >= 0, id < audio_max_instances, mixer->instances[ id ] .playing is yes )
	{
		lock_thread( mixer->lock );
		mixer->instances[ id ] .volume = volume;
		mixer->instances[ id ] .pan = pan;
		unlock_thread( mixer->lock );
	}
}

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
	fn _C7H16_main()\
