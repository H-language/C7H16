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

#define make_pixel( R, G, B, A ) make( pixel, .r = B, .g = G, .b = R, .a = A )

//

#define index_2d( X, Y, WIDTH ) ( ( X ) + ( ( Y ) * ( WIDTH ) ) )

type( canvas )
{
	pixel ref pixels;
	n2x2 size;
};

#define _make_canvas( W, H ) make( canvas, .pixels = to( pixel ref, new_ref( pixel, W * H ) ), .size = make( n2x2, .w = W, .h = H ) )
#define _eval_make_canvas( WIDTH_HEIGHT... ) _make_canvas( WIDTH_HEIGHT )
#define make_canvas( WIDTH_HEIGHT... ) _eval_make_canvas( DEFAULTS( ( 1, 1 ), WIDTH_HEIGHT ) )

fn canvas_resize( canvas const_ref c, const n2 width, const n2 height )
{
	out_if( c->size.w is width and c->size.h is height );
	c->pixels = ref_resize( c->pixels, ( c->size.w * c->size.h ) << 2, ( width * height ) << 2 );
	c->size.w = width;
	c->size.h = height;
}

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
	#endif
	//
	canvas buffer;
	n2x2 size_target;
	n2x2 buffer_max;
	n2 scale;
	anchor buffer_anchor;
	//
	flag visible;
	flag can_resize;
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

object_fn( window, resize, const n2 width, const n2 height )
{
	out_if_any( this is nothing, width <= 1, height <= 1 );

	if( this->size_target.w isnt width or this->size_target.h isnt height )
	{
		this->size_target.w = width;
		this->size_target.h = height;

		window_update_scale( this );
	}

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

object_fn( window, refresh )
{
	out_if_any( this is nothing, this->buffer.size.w <= 1, this->buffer.size.h <= 1 );
	//
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
		XFlush( this->display );
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
	out_if_nothing( w ) failure;
	//
	with( event )
	{
		when( window_event_resize )
		{
			#if OS_LINUX
				skip_if( w->can_resize is no );
				window_resize( w, e->xconfigure.width, e->xconfigure.height );
			#elif OS_WINDOWS
				window_resize( w, LOWORD( lp ), HIWORD( lp ) );
			#endif

			w->can_resize = no;
		} // fall through

		when( window_event_refresh )
		{
			call( w, draw_fn );

			window_refresh( w );

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
	out_window->buffer = make_canvas( width, height );
	out_window->can_resize = yes;
	out_window->buffer_anchor = anchor_middle_center;

	byte ref name = "test";

	#if OS_LINUX
		out_window->display = XOpenDisplay( 0 );
		temp i4 screen = DefaultScreen( out_window->display );

		out_window->handle = XCreateSimpleWindow( out_window->display, RootWindow( out_window->display, screen ), 0, 0, width, height, 0, 0, 0 );

		XSetWindowBackgroundPixmap( out_window->display, out_window->handle, None );
		XSetWindowAttributes attr;
		attr.backing_store = Always;
		attr.bit_gravity = NorthWestGravity;
		XChangeWindowAttributes( out_window->display, out_window->handle, CWBackingStore | CWBitGravity, ref_of( attr ) );

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
		XFlush( this->display );
	#elif OS_WINDOWS
		ShowWindow( this->handle, SW_SHOWNOACTIVATE );
		SetForegroundWindow( this->handle );
		SetFocus( this->handle );
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

object_fn( window, process )
{
	++this->tick;
	if( this->tick is 1 )
	{
		call( this, start_fn );
		out;
	}
	else if( this->tick is 2 )
	{
		window_show( this );
		out;
	}

	//

	this->can_resize = yes;

	//

	os_event e;

	#if OS_LINUX
		while( XPending( this->display ) )
	#elif OS_WINDOWS
		while( PeekMessage( ref_of( e ), 0, 0, 0, PM_REMOVE ) )
	#endif
	{
		#if OS_LINUX
			XNextEvent( this->display, ref_of( e ) );
			window_process_event( this, e.type, ref_of( e ) );
		#elif OS_WINDOWS
			TranslateMessage( ref_of( e ) );
			DispatchMessage( ref_of( e ) );
		#endif
		out_if( this->close is yes );
	}
}

///////

fn _C7H16_init()
{
	#if OS_WINDOWS
		//timeBeginPeriod( 1 );
	#endif
	//SET_OS_KEYMAP();
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
	#if OS_WINDOWS
		//timeEndPeriod( 1 );
	#endif
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
