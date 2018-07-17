/*
 *      misc.h
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

#ifndef __APRIL_MISC_H
#define __APRIL_MISC_H

/* Simple API to create message boxes */
void april_message_box_error ( gchar * message ) ;
void april_message_box_warning ( gchar * message ) ;
void april_message_box_info ( gchar * message ) ;
gboolean april_message_box_yes_no ( gchar * message ) ;

typedef enum _AprilMessageBox {
	APRIL_MESSAGE_BOX_YES_NO,
	APRIL_MESSAGE_BOX_ERROR,
	APRIL_MESSAGE_BOX_INFO,
	APRIL_MESSAGE_BOX_WARNING,
	APRIL_MESSAGE_BOX_NONE
} AprilMessageBox ;

/* This is the preferred way to use the message_box API, as we can
 * change the private functions to use features such as accessibility,
 * among others
 */
gboolean april_message_box ( gchar * message, AprilMessageBox type ) ;

/* Miscelleneous useful stuff */
void april_spawn_async ( gchar * command ) ;

typedef struct {
	GtkWindow * window ;
	gchar * filename ;
} AprilSpawnAsyncSexyObject ;

gboolean april_check_bin_status ( gchar * filename ) ;
gboolean april_check_bin_status_case_sensitive ( gchar * filename ) ;

gchar * april_file_get_contents ( gchar * filename ) ;
guint32 april_get_size_in_ints ( gchar * folder ) ;

gboolean april_hotkeys ( GtkWidget * widget, GdkEventKey * event, gpointer user_data ) ;
void april_connect_default_signals ( GtkWindow * window ) ;

gboolean april_kill ( gchar * program ) ;
gboolean april_trap ( gchar * program ) ;

void april_update_gui ( void ) ;
gboolean april_file_exists ( gchar * filename ) ;

void april_purge_folder ( gchar * folder ) ;

void april_spawn_wait_for ( gchar * message, gchar * command ) ;
inline void april_sleep ( void ) ;

#endif /* __APRIL_MISC_H */
