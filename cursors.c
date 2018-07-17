/*
 *      cursors.c
 *
 *      Copyright 2008 DJ Shaji <djshaji@gmail.com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */


void april_cursors_new ( AprilCursors * cursors )
{
	cursors -> left_ptr = gdk_cursor_new ( GDK_LEFT_PTR ) ;
	cursors -> watch = gdk_cursor_new ( GDK_WATCH ) ;
	cursors -> left_ptr_watch = gdk_cursor_new ( GDK_EXCHANGE ) ;
	cursors -> hand = gdk_cursor_new ( GDK_HAND2 ) ;
	cursors -> coffee_mug = gdk_cursor_new ( GDK_COFFEE_MUG ) ;
	cursors -> clock = gdk_cursor_new ( GDK_CLOCK ) ;
	cursors -> gobbler = gdk_cursor_new ( GDK_GOBBLER ) ;
	cursors -> man = gdk_cursor_new ( GDK_MAN ) ;
	cursors -> mouse = gdk_cursor_new ( GDK_MOUSE ) ;
	cursors -> sail_boat = gdk_cursor_new ( GDK_SAILBOAT ) ;

	cursors -> cursors_inited = true ;
}

void april_cursors_destroy ( AprilCursors * cursors )
{
	gdk_cursor_unref ( cursors -> left_ptr ) ;
	gdk_cursor_unref ( cursors -> watch ) ;
	gdk_cursor_unref ( cursors -> left_ptr_watch ) ;
	gdk_cursor_unref ( cursors -> hand ) ;
	gdk_cursor_unref ( cursors -> coffee_mug ) ;
	gdk_cursor_unref ( cursors -> clock ) ;
	gdk_cursor_unref ( cursors -> gobbler ) ;
	gdk_cursor_unref ( cursors -> man ) ;
	gdk_cursor_unref ( cursors -> mouse ) ;
	gdk_cursor_unref ( cursors -> sail_boat ) ;
	
	cursors -> cursors_inited = false ;
}

void april_cursors_set_cursor ( GtkWidget * widget, AprilCursors * cursors, AprilCursorsType type )
{
	if ( GTK_WIDGET_NO_WINDOW ( widget ))
	{
		g_critical ( "AprilCursors: Widget does not have it\'s own window !\n" ) ;
		return ;
	}

	GdkWindow * window = gtk_widget_get_root_window ( widget ) ;
	if ( ! window )
	{
		g_critical ( "AprilCursors: Reference to (null) window passed as argument!\n" ) ;
		return ;
	}

	switch ( type )
	{
		case APRIL_CURSOR_HAND:
			gdk_window_set_cursor ( window, cursors -> hand ) ;
			break ;
		case APRIL_CURSOR_LEFT_PTR:
			gdk_window_set_cursor ( window, cursors -> left_ptr ) ;
			break ;
		case APRIL_CURSOR_LEFT_PTR_WATCH:
			gdk_window_set_cursor ( window, cursors -> left_ptr_watch ) ;
			break ;
		case APRIL_CURSOR_WATCH:
			gdk_window_set_cursor ( window, cursors -> watch ) ;
			break ;
		case APRIL_CURSOR_CLOCK:
			gdk_window_set_cursor ( window, cursors -> clock ) ;
			break ;
		case APRIL_CURSOR_COFFEE_MUG:
			gdk_window_set_cursor ( window, cursors -> coffee_mug ) ;
			break ;
		case APRIL_CURSOR_GOBBLER:
			gdk_window_set_cursor ( window, cursors -> gobbler ) ;
			break ;
		case APRIL_CURSOR_MAN:
			gdk_window_set_cursor ( window, cursors -> man ) ;
			break ;
		case APRIL_CURSOR_MOUSE:
			gdk_window_set_cursor ( window, cursors -> mouse ) ;
			break ;
		case APRIL_CURSOR_SAIL_BOAT:
			gdk_window_set_cursor ( window, cursors -> sail_boat ) ;
			break ;
		default:
			g_debug ( "AprilCursors: Unknown AprilCursorsType requested !" ) ;
			break ;
	}
}

GVoidFunc april_cursors_reset ( void )
{
	GtkWidget * widget = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_decorated ( widget, no ) ;
	GtkBox * box = gtk_hbox_new ( on, 10 ) ;
	gtk_container_add ( widget, box ) ;
	
	GtkLabel * label = gtk_label_new ( null ) ;	
	gtk_box_pack_start ( box, label, on, on, 0 ) ;
	
	AprilCursors cursors ;
	april_cursors_new ( & cursors ) ;
	april_cursors_set_cursor ( widget, & cursors, APRIL_CURSOR_LEFT_PTR ) ;
	
	gtk_widget_show_all ( widget ) ;
	april_update_gui () ;
	
	gtk_widget_destroy ( widget ) ;
	april_cursors_destroy ( & cursors ) ;
}

