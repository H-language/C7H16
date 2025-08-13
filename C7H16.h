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
		temp i2 _x = Ax;\
		temp i2 _y = Ay;\
		temp i2 _x2 = Bx;\
		temp i2 _y2 = By;\
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

#define _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, SAFE... ) fn_line( Ax, Ay, Bx, By, canvas_draw_pixel##SAFE( CANVAS, _x, _y, PIXEL ) );
#define canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL )
#define canvas_draw_line_safe( CANVAS, Ax, Ay, Bx, By, PIXEL ) _canvas_draw_line( CANVAS, Ax, Ay, Bx, By, PIXEL, _safe )

#define draw_line( Ax, Ay, Bx, By, PIXEL ) canvas_draw_line( val_of( current_canvas_ref ), Ax, Ay, Bx, By, PIXEL )
#define draw_line_safe( Ax, Ay, Bx, By, PIXEL ) canvas_draw_line_safe( val_of( current_canvas_ref ), Ax, Ay, Bx, By, PIXEL )

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
};

global perm window current_window = nothing;

global perm window alive_windows[ 32 ];
global perm n1 alive_windows_count = 0;

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
	window_event_close = PICK( OS_LINUX, ClientMessage, WM_DESTROY )
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
		XSelectInput( out_window->display, out_window->handle, ExposureMask | StructureNotifyMask );

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
	if( this->tick is 0 )
	{
		this->fps_target = 60;
		this->target_frame_nano = to( nano, r8( nano_per_sec ) / this->fps_target );
		this->start_nano = get_nano();
		this->past_nano = this->start_nano;
		call( this, start_fn );
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

	input_grave,
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

global perm byte OS_INPUT[ 256 ];

fn _C7H16_set_keymap()
{
	#if OS_LINUX
		#define XK_COMPRESS( xk ) ( ( ( xk ) ^ ( ( xk ) >> 8 ) ) & 0xFF )

		range( c, 'a', 'z' )
		{
			OS_INPUT[ XK_COMPRESS( XK_a + c - 'a' ) ] = ( c - 'a' ) + input_a;
		}

		range( c, '0', '9' )
		{
			OS_INPUT[ XK_COMPRESS( XK_0 + c - '0' ) ] = ( c - '0' ) + input_0;
		}

		range( c, 0, 12 )
		{
			OS_INPUT[ XK_COMPRESS( XK_F1 + c ) ] = c + input_f1;
		}

		OS_INPUT[ XK_COMPRESS( XK_space ) ] = input_space;
		OS_INPUT[ XK_COMPRESS( XK_grave ) ] = input_grave;
		OS_INPUT[ XK_COMPRESS( XK_minus ) ] = input_minus;
		OS_INPUT[ XK_COMPRESS( XK_equal ) ] = input_equals;
		OS_INPUT[ XK_COMPRESS( XK_bracketleft ) ] = input_leftbracket;
		OS_INPUT[ XK_COMPRESS( XK_bracketright ) ] = input_rightbracket;
		OS_INPUT[ XK_COMPRESS( XK_backslash ) ] = input_backslash;
		OS_INPUT[ XK_COMPRESS( XK_semicolon ) ] = input_semicolon;
		OS_INPUT[ XK_COMPRESS( XK_apostrophe ) ] = input_apostrophe;
		OS_INPUT[ XK_COMPRESS( XK_comma ) ] = input_comma;
		OS_INPUT[ XK_COMPRESS( XK_period ) ] = input_period;
		OS_INPUT[ XK_COMPRESS( XK_slash ) ] = input_slash;

		OS_INPUT[ XK_COMPRESS( XK_BackSpace ) ] = input_backspace;
		OS_INPUT[ XK_COMPRESS( XK_Tab ) ] = input_tab;
		OS_INPUT[ XK_COMPRESS( XK_Return ) ] = input_enter;
		OS_INPUT[ XK_COMPRESS( XK_Escape ) ] = input_escape;
		OS_INPUT[ XK_COMPRESS( XK_Delete ) ] = input_delete;
		OS_INPUT[ XK_COMPRESS( XK_Insert ) ] = input_insert;

		OS_INPUT[ XK_COMPRESS( XK_Home ) ] = input_home;
		OS_INPUT[ XK_COMPRESS( XK_End ) ] = input_end;
		OS_INPUT[ XK_COMPRESS( XK_Page_Up ) ] = input_pageup;
		OS_INPUT[ XK_COMPRESS( XK_Page_Down ) ] = input_pagedown;
		OS_INPUT[ XK_COMPRESS( XK_Left ) ] = input_left;
		OS_INPUT[ XK_COMPRESS( XK_Up ) ] = input_up;
		OS_INPUT[ XK_COMPRESS( XK_Right ) ] = input_right;
		OS_INPUT[ XK_COMPRESS( XK_Down ) ] = input_down;

		OS_INPUT[ XK_COMPRESS( XK_Shift_L ) ] = input_shift;
		OS_INPUT[ XK_COMPRESS( XK_Shift_R ) ] = input_shift;
		OS_INPUT[ XK_COMPRESS( XK_Control_L ) ] = input_ctrl;
		OS_INPUT[ XK_COMPRESS( XK_Control_R ) ] = input_ctrl;
		OS_INPUT[ XK_COMPRESS( XK_Caps_Lock ) ] = input_capslock;
		OS_INPUT[ XK_COMPRESS( XK_Alt_L ) ] = input_alt;
		OS_INPUT[ XK_COMPRESS( XK_Alt_R ) ] = input_alt;
		OS_INPUT[ XK_COMPRESS( XK_Super_L ) ] = input_super;
		OS_INPUT[ XK_COMPRESS( XK_Super_R ) ] = input_super;
		OS_INPUT[ XK_COMPRESS( XK_Menu ) ] = input_menu;
	#elif OS_WINDOWS
		range( c, 'A', 'Z' )
		{
			OS_INPUT[ c ] = ( c - 'A' ) + input_a;
		}

		range( c, '0', '9' )
		{
			OS_INPUT[ c ] = ( c - '0' ) + input_0;
		}

		range( c, 0, 12 )
		{
			OS_INPUT[ VK_F1 + c ] = c + input_f1;
		}

		OS_INPUT[ VK_SPACE ] = input_space;
		OS_INPUT[ VK_ESCAPE ] = input_escape;
		OS_INPUT[ VK_TAB ] = input_tab;
		OS_INPUT[ VK_CAPITAL ] = input_capslock;
		OS_INPUT[ VK_SHIFT ] = input_shift;
		OS_INPUT[ VK_CONTROL ] = input_ctrl;
		OS_INPUT[ VK_MENU ] = input_alt;
		OS_INPUT[ VK_RETURN ] = input_enter;
		OS_INPUT[ VK_BACK ] = input_backspace;
		OS_INPUT[ VK_INSERT ] = input_insert;
		OS_INPUT[ VK_DELETE ] = input_delete;
		OS_INPUT[ VK_HOME ] = input_home;
		OS_INPUT[ VK_END ] = input_end;
		OS_INPUT[ VK_PRIOR ] = input_pageup;
		OS_INPUT[ VK_NEXT ] = input_pagedown;

		OS_INPUT[ VK_UP ] = input_up;
		OS_INPUT[ VK_DOWN ] = input_down;
		OS_INPUT[ VK_LEFT ] = input_left;
		OS_INPUT[ VK_RIGHT ] = input_right;

		OS_INPUT[ VK_OEM_3 ] = input_grave;
		OS_INPUT[ VK_OEM_MINUS ] = input_minus;
		OS_INPUT[ VK_OEM_PLUS ] = input_equals;
		OS_INPUT[ VK_OEM_4 ] = input_leftbracket;
		OS_INPUT[ VK_OEM_6 ] = input_rightbracket;
		OS_INPUT[ VK_OEM_5 ] = input_backslash;
		OS_INPUT[ VK_OEM_1 ] = input_semicolon;
		OS_INPUT[ VK_OEM_7 ] = input_apostrophe;
		OS_INPUT[ VK_OEM_COMMA ] = input_comma;
		OS_INPUT[ VK_OEM_PERIOD ] = input_period;
		OS_INPUT[ VK_OEM_2 ] = input_slash;

		OS_INPUT[ VK_LWIN ] = input_super;
		OS_INPUT[ VK_RWIN ] = input_super;
		OS_INPUT[ VK_APPS ] = input_menu;
	#endif
}

///////

fn _C7H16_init()
{
	_C7H16_set_keymap();
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
