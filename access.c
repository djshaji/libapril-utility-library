/*
 *      access.c
 *
 *      Copyright 2007 Shaji <djshaji@gmail.com>
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

gboolean april_access_esd_status ( void )
{
	if ( ! april_esd_check_status ())
	{
		/* We try to start esd if it's unavailable */
		april_esd_init () ;
		if ( ! april_esd_check_status ())
		{
			april_message_box_warning ( "Cannot connect to the ESound Daemon !\n\n"
										"The accessibility mode may not work without\n"
										"a running ESounD Daemon. If you want to use\n"
										"the accessibility features a lot, consider\n"
										"always running the ESD Server with ALSA. It\n"
										"won\'t block your device, and most audio\n"
										"applications offer native esd support." ) ;
		
			return false;
		}
	}
	
	return true ;
}

void april_access_say_file ( gchar * filename )
{
	if ( ! april_access_esd_status ())
		return ;

	april_access_shut_up () ;
	gdk_beep () ;
	
	gchar * command = april_malloc_sprintf ( "text2wave \"%s\" -scale 2 | esdcat -r 16000 -m", filename ) ;

	april_spawn_async ( command ) ;
	g_free ( command ) ;
}

void april_access_say_text_async ( gchar * text )
{
	if ( ! april_access_esd_status ())
		return ;

	april_access_shut_up () ;
	gdk_beep () ;

	gchar * command = april_malloc_sprintf (  "echo \"%s\" | text2wave - -scale 2 | esdcat -r 16000 -m", text ) ;
	april_spawn_async ( command ) ;

	g_free ( command ) ;
}

void april_access_say_text ( gchar * text )
{
	if ( ! april_access_esd_status ())
		return ;

	april_access_shut_up () ;
	gdk_beep () ;

	gchar * command = april_malloc_sprintf ( "echo \"%s\" | text2wave - -scale 2 | esdcat -r 16000 -m", text ) ;

	system ( command ) ;
	g_free ( command ) ;
}

void april_access_shut_up ()
{
	if ( ! system ( "ps -A | grep -F esdcat" ))
		system ( "killall esdcat" ) ;

}

void april_access_say_time ( void )
{
	april_access_shut_up () ;
	gdk_beep () ;

	system ( "date +\%r | text2wave - -scale 2 | esdcat -r 16000 -m &" ) ;
}

void april_access_sak ( void )
{
	/* This is really a susie specific function, but I reckon
	*  it will probably be useful elsewhere as well :)
	* 
	*  This is NOT a real SAK !!! This will ONLY kill a persistent
	*  audacious and MPlayer.
	*  NOT a real SAK !!!
	*/

	april_access_shut_up () ;
	gdk_beep () ;
	
	april_access_say_text ( "Trapping stuck programs ..." ) ;
	
	april_trap ( "audacious" ) ;
	april_trap ( "mplayer" ) ;
	april_trap ( "gmplayer" ) ;
}

void april_access_reset_to_sane_stage ( void )
{
	april_access_shut_up () ;
	gdk_beep () ;
	
	april_access_say_text ( "Resetting april to a sane state." ) ;
	april_access_sak () ;

	/* ESD */
	if ( april_esd_check_status ())
		april_esd_resume () ;
	else
		april_access_esd_status () ;

	system ( "aumix -v 85 -w 75" ) ;
}

void april_access_say_fortune ( void )
{
	april_access_shut_up () ;
	gdk_beep () ;

	system ( "fortune | text2wave - -scale 2 | esdcat -r 16000 -m &" ) ;
}

void april_access_say_date ( void )
{
	april_access_shut_up ();
	gdk_beep () ;

	system ( "date -R | text2wave - -scale 2 | esdcat -r 16000 -m &" ) ;
}

void april_access_say_text_async_adrenaline ( gchar * text )
{
	gchar * command = april_malloc_sprintf ( "echo \"%s\" | text2wave - -scale 2 > /dev/dsp", text ) ;

	april_access_shut_up () ;
	gdk_beep () ;
	
	april_spawn_async ( command ) ;
	g_free ( command ) ;
}

void april_access_say_directory ( gchar * folder )
{
	GDir * dir = null ;
	GError * error = null ;
	
	dir = g_dir_open ( folder, zero, & error ) ;
	if ( error != null )
	{
		april_message_box_warning ( error -> message ) ;
		
		if ( dir == null )
			return ;
	}
	
	april_access_shut_up () ;
	gdk_beep () ;	

	gchar * filename = g_dir_read_name ( dir ) ;
	while ( filename )
	{
		april_access_say_text ( filename ) ;
		filename = g_dir_read_name ( dir ) ;
	}
	
	g_dir_close ( dir ) ;
	return ;
}
