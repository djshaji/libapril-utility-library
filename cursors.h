/*
 *      cursors.h
 *
 *      Copyright 2008 Shaji <djshaji@gmail.com>
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


#ifndef __APRIL_CURSORS_H
#define __APRIL_CURSORS_H

typedef struct _AprilCursors {
	GdkCursor * left_ptr ;
	GdkCursor * hand ;
	GdkCursor * watch ;
	GdkCursor * left_ptr_watch ;
	GdkCursor * clock ;
	GdkCursor * coffee_mug ;
	GdkCursor * gobbler ;
	GdkCursor * man ;
	GdkCursor * mouse ;
	GdkCursor * sail_boat ;
	gboolean cursors_inited ;
} AprilCursors ;
	
typedef enum _AprilCursorsType {
	APRIL_CURSOR_LEFT_PTR,
	APRIL_CURSOR_WATCH,
	APRIL_CURSOR_LEFT_PTR_WATCH,
	APRIL_CURSOR_HAND,
	APRIL_CURSOR_CLOCK,
	APRIL_CURSOR_COFFEE_MUG,
	APRIL_CURSOR_GOBBLER,
	APRIL_CURSOR_MAN,
	APRIL_CURSOR_MOUSE,
	APRIL_CURSOR_SAIL_BOAT,
	APRIL_CURSOR_UNKNOWN
} AprilCursorsType ;

/* Public API */
void april_cursors_new ( AprilCursors * cursors ) ;
void april_cursors_destroy ( AprilCursors * cursors ) ;
void april_cursors_set_cursor ( GtkWidget * widget, AprilCursors * cursor, AprilCursorsType type ) ;

/* This is only useful if put in a function like g_atexit */
GVoidFunc april_cursors_reset ( void ) ;

#endif /* __APRIL_CURSORS_H */
