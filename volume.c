/*
 *      volume.c
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


gint april_volume_get_volume ( void )
{
	system ( "aumix -q | grep -i -F pcm > /tmp/april.volume" ) ;
	gchar * contents = april_file_get_contents ( "/tmp/april.volume" ) ;

	if ( ! contents )
		return 0 ;
	
	gchar ** vec = g_strsplit ( contents, "\n", -1 ) ;
	gchar ** vector = g_strsplit ( vec[0], " ", MinusOne ) ;
	gint vol = atoi ( vector [2] ) ;
	
	g_free ( contents ) ;
	g_strfreev ( vector ) ;
	g_strfreev ( vec ) ;
	
	return vol ;
}

void april_volume_set_volume ( gdouble volume )
{
	gchar * command = april_malloc_sprintf ( "aumix -w %f", volume ) ;
	
	system ( command ) ;
	g_free ( command ) ;
	
	return ;
}

void april_volume_mute ( gdouble volume )
{
	system ( "aumix -v 0" ) ;
	return ;
}
