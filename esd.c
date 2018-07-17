/*
 *      esd.c
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

/*	ESD related stuff
 */

void april_esd_init ( void )
{
	april_spawn_async ( "esd -r 48000 -nobeeps" ) ;
}

gboolean april_esd_status ( void )
{
	if ( ! system ( "ps -A | grep -F esd -i -" ))
		return TRUE ;
	else
		return FALSE ;
}

gboolean april_esd_is_standby ( void )
{
	gint mesd = esd_open_sound ( null ) ;
	esd_standby_mode_t esd = esd_get_standby_mode ( mesd ) ;
	esd_close ( mesd ) ;

	if ( esd == ESM_ON_STANDBY )
		return true ;
	else
		return false ;
}

gboolean april_esd_check_status ( void )
{
	if ( ! april_esd_status ())
	{
		if ( april_message_box_yes_no (
			"The Sound Server is not running !\n\n"
			"If you want, I can start the sound server now. Do you\n"
			"want me to start up the sound server now ?" ))

			if ( april_message_box_yes_no ( "But is that something you really want ?" ))
				if ( april_message_box_yes_no ( "Really ?" ))
				{
					april_spawn_async_sexy ( "esd -r 48000 -nobeeps" ) ;
					return true ;
				}
				else
				{
					april_message_box_warning (	"The Sound Server is unavailable !\n\n"
											"This is not a fatal problem, but some applications\n"
											"might not make any sound. Two things can be done to\n"
											"rectify the problem:\n\n"
											"1. Change the settings in those applications to use\n"
											"   the ALSA devices instead of ESD.\n"
											"2. Start the Enlightenment Sound Server." ) ;
					return false ;
				}
			else
			{
				april_message_box_warning (	"The Sound Server is unavailable !\n\n"
										"This is not a fatal problem, but some applications\n"
										"might not make any sound. Two things can be done to\n"
										"rectify the problem:\n\n"
										"1. Change the settings in those applications to use\n"
										"   the ALSA devices instead of ESD.\n"
										"2. Start the Enlightenment Sound Server." ) ;
				return false ;
			}
		else
		{
			april_message_box_warning (	"The Sound Server is unavailable !\n\n"
									"This is not a fatal problem, but some applications\n"
									"might not make any sound. Two things can be done to\n"
									"rectify the problem:\n\n"
									"1. Change the settings in those applications to use\n"
									"   the ALSA devices instead of ESD.\n"
									"2. Start the Enlightenment Sound Server." ) ;

			simply return false ;
		}
	}
}

void april_esd_set_status ( GtkWidget * widget, shagpointer user_data )
{
	if ( ! april_esd_check_status ())
		return ;

	if ( gtk_toggle_button_get_active ( widget ))
	{
		system ( "esdctl on" ) ;
	}
	else
	{
		system ( "esdctl off" ) ;
	}

	gchar * info = april_esd_get_info () ;
	gtk_label_set_label ( user_data, info ) ;

	g_free ( info ) ;
}

gchar * april_esd_get_info ( void )
{
	system ( "esdctl standbymode allinfo > /tmp/april.esd" ) ;
	gchar * info = april_file_get_contents ( "/tmp/april.esd" ) ;

	return info ;
}

void april_esd_config ( void )
{
	if ( ! april_esd_check_status ())
		return ;

	GtkWidget * window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_title ( window, "April Sound Server" ) ;

	GtkLayout * lt = gtk_layout_new ( null, null ) ;
	g_signal_connect ( window, "destroy", gtk_main_quit, null ) ;
	g_signal_connect_after ( window, "key-press-event", april_hotkeys, null ) ;
	gtk_container_add ( window, lt ) ;

	GtkHBox * box = gtk_vbox_new ( off, 1 ) ;
	gtk_layout_put ( lt, box, 10, 10 ) ;
	gtk_widget_set_size_request ( window, 484, 428 ) ;

	gchar * message =
		"Configure the April Sound Server:\n\n"
		"The Enlightened Sound Daemon is used by April to both play\n"
		"system sounds and play music. This means that you would\n"
		"hear sounds when you do stuff with the desktop, all the while\n"
		"being able to use the sound device yourself. But you can disable\n"
		"the sound server here if you want to." ;

	GtkLabel * label = gtk_label_new ( message ) ;
	GtkFrame * framed1 = gtk_frame_new ( "Options" ) ;
	gtk_box_pack_start ( box, label, on, on, 5 ) ;

	gchar * info = april_esd_get_info () ;

	GtkScrolledWindow * sw = gtk_scrolled_window_new ( null, null ) ;
	GtkFrame * fame = gtk_frame_new ( "Server Info" ) ;
	GtkLabel * label2 = gtk_label_new ( info ) ;
	gtk_scrolled_window_add_with_viewport ( sw, label2 ) ;
	gtk_box_pack_start ( box, sw, on, on, 5 ) ;
	g_free ( info ) ;
	gtk_widget_set_size_request ( sw, 450, 155 ) ;
	gtk_scrolled_window_set_shadow_type ( sw, GTK_SHADOW_NONE ) ;
	gtk_scrolled_window_set_policy ( sw, GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC ) ;

	GtkCheckButton * check = gtk_check_button_new_with_label ( "Use the Sound Server." ) ;
	gtk_toggle_button_set_active ( check, ! april_esd_is_standby ()) ;
	g_signal_connect ( check, "toggled", april_esd_set_status, label2 ) ;

	gtk_container_add ( framed1, check ) ;
	gtk_box_pack_end ( box, framed1, on, off, 5 ) ;

	GtkButton * button = gtk_button_new_from_stock ( GTK_STOCK_OK ) ;
	gtk_widget_set_size_request ( button, 96, 32 ) ;
	gtk_layout_put ( lt, button, 375, 385 ) ;

	g_signal_connect_swapped ( button, "clicked", gtk_widget_destroy, window ) ;

	gtk_widget_show_all ( window ) ;
	gtk_main () ;
}

gboolean april_esd_standby ( void )
{
	return ! system ( "esdctl off " ) ;
}

gboolean april_esd_resume ( void )
{
	return ! system ( "esdctl on" ) ;
}
