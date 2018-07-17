/*
 *      misc.c
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


void april_message_box_error ( gchar * message )
{
	GtkDialog * dialog ;
	dialog = gtk_message_dialog_new ( NULL,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_ERROR,
                                  GTK_BUTTONS_CLOSE,
                                  message );

	gdk_beep () ;
	gtk_dialog_run (GTK_DIALOG (dialog));
	
	gtk_widget_destroy (dialog);
	return ;
}

void april_message_box_warning ( gchar * message )
{
	GtkDialog * dialog ;
	dialog = gtk_message_dialog_new ( NULL,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_WARNING,
                                  GTK_BUTTONS_OK,
                                  message );

	gdk_beep () ;
	gtk_dialog_run (GTK_DIALOG (dialog));

	gtk_widget_destroy (dialog);
	return ;
}

void april_message_box_info ( gchar * message )
{
	GtkDialog * dialog ;
	dialog = gtk_message_dialog_new ( NULL,
                                  GTK_DIALOG_DESTROY_WITH_PARENT,
                                  GTK_MESSAGE_INFO,
                                  GTK_BUTTONS_OK,
                                  message );

	gdk_beep () ;
	gtk_dialog_run (GTK_DIALOG (dialog));

	gtk_widget_destroy (dialog);
	return ;
}

gboolean april_message_box_yes_no ( gchar * message )
{
	GtkDialog * dialog ;
	dialog = gtk_dialog_new_with_buttons ( "Question",
						NULL,
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_STOCK_YES,
						TRUE,
						GTK_STOCK_NO,
						FALSE,
						NULL ) ;

	
	GtkLabel * label = gtk_label_new ( message ) ;
	GtkWidget * box = gtk_hbox_new ( no, 10 ) ;

	GtkImage * image = gtk_image_new_from_stock ( GTK_STOCK_DIALOG_QUESTION, GTK_ICON_SIZE_DIALOG ) ;

	gtk_box_pack_start ( dialog -> vbox, box, no, no, 10 ) ;
	gtk_box_pack_start ( box, image, no, no, 10 ) ;
	gtk_box_pack_start ( box, label, no, no, 2 ) ;
	
	gtk_widget_show_all ( box ) ;

	gtk_label_set_line_wrap ( label, true ) ;
	gtk_widget_show ( label ) ;

	gdk_beep () ;
	gboolean result = gtk_dialog_run ( dialog ) ;

	gtk_widget_destroy ( dialog ) ;
	return result ;
}

gboolean april_message_box ( gchar * message, AprilMessageBox type )
{
	gboolean result = false ;
	switch ( type )
	{
		case APRIL_MESSAGE_BOX_ERROR:
			april_message_box_error ( message ) ;
			break ;
		case APRIL_MESSAGE_BOX_INFO:
			april_message_box_info ( message ) ;
			break ;
		case APRIL_MESSAGE_BOX_WARNING:
			april_message_box_warning ( message ) ;
			break ;
		case APRIL_MESSAGE_BOX_YES_NO:
			result = april_message_box_yes_no ( message ) ;
			break ;
		case APRIL_MESSAGE_BOX_NONE:
		default:
			g_debug ( "AprilMessageBox called with type NONE and the following message : %s", message ) ;
			break ;
	}
	
	return result ;
}

void april_spawn_async ( gchar * command )
{
	gchar ** vector = g_strsplit ( command, " ", MinusOne ) ;
	
	gchar * full_path_to_executable = g_find_program_in_path ( vector [0] ) ;
	if ( full_path_to_executable == null )
	{
		gchar * message = g_strconcat ( "Cannot find executable program ", vector [0], " !", null ) ;
		april_message_box_warning ( message ) ;
		
		g_free ( message ) ;
	}
	
	g_free ( full_path_to_executable ) ;
	g_strfreev ( vector ) ;
	
	gchar * run = g_strconcat ( command, " &", null ) ;
	system ( run ) ;
	
	g_free ( run ) ;
	return ;
}

gboolean april_check_bin_status ( gchar * filename )
{
	gchar * command = g_strconcat ( "ps -A | grep -i -F ", filename, null ) ;

	gboolean result = false ;
	result = system ( command ) ;

	if ( result )
	{
		usleep ( 1000 ) ;
		result = system ( command ) ;
		if ( result )
		{
			usleep ( 1000 ) ;
			result = system ( command ) ;
			if ( result )
			{
				usleep ( 1000 ) ;
				result = system ( command ) ;
			}
		}
	}

	g_free ( command ) ;
	return ! result ;
}

gchar * april_file_get_contents ( gchar * filename )
{
	gchar * contents ;
	gsize length ;
	GError * error = null ;

	g_file_get_contents ( filename, & contents, & length, & error ) ;
	if ( error )
		april_message_box_error ( error -> message ) ;

	return contents ;
}

gboolean april_hotkeys ( GtkWidget * widget, GdkEventKey * event, gpointer user_data )
{
	switch ( event -> keyval )
	{
		case 'q':
		case GDK_Escape:
			gtk_widget_destroy ( widget ) ;
			break ;
		default:
			break ;
	}

	return true ;
}

void april_connect_default_signals ( GtkWindow * window )
{
	g_signal_connect ( window, "destroy", gtk_main_quit, null ) ;
	g_signal_connect_after ( window, "key-press-event", april_hotkeys, window ) ;
}

gboolean april_kill ( gchar * program )
{
	/* Note: This function forces a running program to terminate.
	*  This has nothing to do with killing or harming anybody
	*  in any manner whatsoever !
	*/
	
	gchar * command = april_malloc_sprintf ( "killall %s", program ) ;
	gboolean result = ! system ( command ) ;
	
	g_free ( command ) ;
	return result ;
}

gboolean april_trap ( gchar * program )
{
	gchar * command = april_malloc_sprintf ( "killall -TRAP %s", program ) ;
	gboolean result = ! system ( command ) ;
	
	g_free ( command ) ;
	return result ;
}

void april_update_gui ( void )
{
	while ( gtk_events_pending ())
		gtk_main_iteration () ;

	return ;
}

gboolean april_file_exists ( gchar * filename )
{
	return g_file_test ( filename, G_FILE_TEST_EXISTS ) ;
}

guint32 april_get_size_in_ints ( gchar * folder )
{
	gchar * command = g_strconcat ( "du -scL \"", folder, "\" > /tmp/april.cdrecorder", null ) ;
	system ( command ) ;

	g_free ( command ) ;

	gchar * text = april_file_get_contents ( "/tmp/april.cdrecorder" ) ;
	if ( text == null )
		return 0 ;

	gchar ** vector ;
	vector = g_strsplit ( text, "/", MinusOne ) ;
	guint32 size = atoi ( vector [0] ) ;

	g_free ( text ) ;
	g_strfreev ( vector ) ;

	return size ;
}

void april_purge_folder ( gchar * folder )
{
	GDir * dir ;
	GError * error = null ;
	dir = g_dir_open ( folder, 0, & error ) ;
	if ( error )
		april_message_box_error ( error -> message ) ;

	gchar * filename = g_dir_read_name ( dir ) ;
	while ( filename )
	{
		gchar * full_filename = g_build_filename ( folder, filename, null ) ;

		/* Really sexy !!! Delete folders recursively */
		if (( g_file_test ( full_filename, G_FILE_TEST_IS_DIR )) && ( ! g_file_test ( full_filename, G_FILE_TEST_IS_SYMLINK )))
			april_purge_folder ( full_filename ) ;

		if ( ! g_remove ( full_filename ) == 0 )
		{
			gchar * message = g_strconcat ( "Could not delete ", full_filename, " !", null ) ;
			april_message_box_error ( message ) ;

			g_free ( message ) ;
		}

		g_printf ( "Removed %s.\n", full_filename ) ;
		g_free ( full_filename ) ;
		filename = g_dir_read_name ( dir ) ;
	}

	g_dir_close ( dir ) ;
	return ;
}

gboolean april_spawn_wait_for_cancel ( GtkWidget * widget, gchar * data )
{
	if ( april_check_bin_status ( data ))
		april_kill ( data ) ;
}

void april_spawn_wait_for ( gchar * message, gchar * command )
{
	GtkWidget * window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	GtkBox * hbox1 = gtk_hbox_new ( on, 2 ) ;
	GtkVBox * box = gtk_vbox_new ( on, 2 ) ;
	gtk_container_add ( window, hbox1 ) ;
	
	gtk_window_set_type_hint ( window, GDK_WINDOW_TYPE_HINT_DIALOG ) ;
	
	GtkLabel * label = gtk_label_new ( null ) ;
	gchar * markup = g_markup_printf_escaped ( "<span size=\"larger\"><b><i>%s</i></b></span>", message ) ;
	gtk_label_set_markup ( label, markup ) ;
	g_free ( markup ) ;
	
	gtk_box_pack_start ( hbox1, label, on, on, 2 ) ;
	gtk_box_pack_start ( hbox1, box, on, on, 2 ) ;
	
	GtkProgressBar * bar = gtk_progress_bar_new () ;
	gtk_box_pack_start ( box, bar, yes, yes, 2 ) ;
	
	GtkButton * button = gtk_button_new_from_stock ( GTK_STOCK_CANCEL ) ;
	gtk_box_pack_start ( box, button, no, no, 2 ) ;
	gtk_widget_set_sensitive ( button, false ) ;
	
	gtk_widget_show_all ( box ) ;
	gtk_widget_show_all ( hbox1 ) ;
	gtk_widget_show ( window ) ;
	
	gchar ** vector = g_strsplit ( command, " ", -1 ) ;
	gchar * app_name = g_strdup ( vector [0] ) ;
	g_strfreev ( vector ) ;
	
	april_spawn_async ( command ) ;

	g_signal_connect ( window, "destroy", april_spawn_wait_for_cancel, app_name ) ;
	g_signal_connect ( button, "clicked", april_spawn_wait_for_cancel, app_name ) ;
	g_signal_connect ( window, "destroy", gtk_widget_destroy, null ) ;	

	gint i = 0 ;
	for ( i = 0 ; i < 10 ; i ++ )
	{
		gtk_progress_bar_set_fraction ( bar, ( gdouble ) i / 10.0 ) ;
		april_update_gui () ;

		if ( april_check_bin_status_case_sensitive ( app_name ))
			i = 9 ;

		usleep ( 100000 ) ;
	}

	gtk_widget_set_sensitive ( button, true ) ;
	while ( april_check_bin_status_case_sensitive ( app_name ))
	{
		gtk_progress_bar_pulse ( bar ) ;
		april_update_gui () ;
		
		april_sleep () ;
	}
	
	g_free ( app_name ) ;
	gtk_widget_destroy ( window ) ;
	
	return ;
}

inline void april_sleep ( void )
{
	usleep ( 100000 ) ;
}

gboolean april_check_bin_status_case_sensitive ( gchar * filename )
{
	gchar * command = g_strconcat ( "ps -A | grep -F ", filename, null ) ;
	gboolean result = FALSE ;
	
	result = system ( command ) ;
	if ( result )
	{
		usleep ( 1000 ) ;
		result = system ( command ) ;
		if ( result )
		{
			usleep ( 1000 ) ;
			result = system ( command ) ;
			if ( result )
			{
				usleep ( 1000 ) ;
				result = system ( command ) ;
			}
		}
	}

	g_free ( command ) ;
	return ! result ;
}

void april_spawn_async_sexy_cancel ( GtkWidget * widget, AprilSpawnAsyncSexyObject * user_data )
{
	gtk_widget_destroy ( user_data -> window ) ;

	if ( april_check_bin_status ( user_data -> filename ))
		april_kill ( user_data -> filename ) ;
}

gboolean april_spawn_async_sexy ( gchar * filename )
{
	/* Because the command might have app_name as well as arguments */
	gchar ** vector = g_strsplit ( filename, " ", MinusOne ) ;
	gchar * app_name = g_strdup ( vector [0] ) ;

	GtkWindow * bindow ;
	bindow = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_type_hint ( bindow, GDK_WINDOW_TYPE_HINT_DIALOG ) ;
	gtk_widget_set_size_request ( bindow, 250, 28 ) ;
	gtk_window_set_resizable ( bindow, false ) ;
	gtk_window_set_title ( bindow, "Spawning child process ..." ) ;

	GtkLayout * lt = gtk_layout_new ( null, null ) ;

	GtkProgressBar * bar = gtk_progress_bar_new () ;
	gtk_container_add ( bindow, lt ) ;
	gtk_widget_set_size_request ( bar, 166, 24 ) ;
	gtk_layout_put ( lt, bar, 2, 2 ) ;
	gtk_progress_bar_set_text ( bar, "Spawning process ..." ) ;

	AprilSpawnAsyncSexyObject spawn ;
	spawn.window = bindow ;
	spawn.filename = app_name ;

	GtkButton * button = gtk_button_new_from_stock ( GTK_STOCK_CANCEL ) ;
	g_signal_connect ( button, "clicked", april_spawn_async_sexy_cancel, & spawn ) ;
	gtk_widget_set_size_request ( button, 76, 24 ) ;
	gtk_layout_put ( lt, button, 172, 2 ) ;

	gtk_widget_show_all ( bindow ) ;
	april_update_gui () ;

	april_spawn_async ( filename ) ;

	gint i = 10 ;

	gtk_progress_bar_set_text ( bar, "Spawning process ..." ) ;
	april_update_gui () ;
	for ( i = 0 ; i < 60 ; i ++ )
	{
		if ( ! GTK_IS_WINDOW ( bindow ))
			return ;

		gtk_progress_bar_set_fraction ( bar, ( gdouble ) i / 60.0 ) ;
		april_update_gui () ;

		if ( april_check_bin_status ( app_name ))
			i = 59 ;

		usleep ( 100000 ) ;
	}

	gtk_widget_destroy ( bindow ) ;

	g_free ( app_name ) ;
	g_strfreev ( vector ) ;
	return true ;
}
