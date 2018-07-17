/*
 *      rcfile.c
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

/*	Like everybody else, we have out own little key file parser :) */

/*		05.17.2010 Modified to use glib-2.0 instead of libaudacious. Silly
 * 		dependency for something so small. */

#include "rcfile.h"

void april_key_file_set_string ( gchar * filename, gchar * section, gchar * key, gchar * string )
{
	if ( ! april_file_exists ( filename ))
		return ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	g_key_file_set_string ( key_file, section, key, string ) ;
	april_key_file_write ( filename, key_file ) ;
	
	g_key_file_free ( key_file ) ;
}

gchar * april_key_file_get_string ( gchar * filename, gchar * section, gchar * key )
{
	if ( ! april_file_exists ( filename ))
		return null ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	gchar * string = g_key_file_get_string ( key_file, section, key, null ) ;
	g_key_file_free ( key_file ) ;
	
	return string ;
}

void april_key_file_set_int ( gchar * filename, gchar * section, gchar * key, guint32 value )
{
	if ( ! april_file_exists ( filename ))
		return ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	g_key_file_set_integer ( key_file, section, key, value ) ;
	april_key_file_write ( filename, key_file ) ;
	
	g_key_file_free ( key_file ) ;
	return ;
}

guint32 april_key_file_get_int ( gchar * filename, gchar * section, gchar * key )
{
	if ( ! april_file_exists ( filename ))
		return -1 ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	gint value = g_key_file_get_integer ( key_file, section, key, & error ) ;
	g_key_file_free ( key_file ) ;
	
	if ( error == null )
		return value ;
	else
		return -1 ;
}

void april_key_file_set_boolean ( gchar * filename, gchar * section, gchar * key, gboolean value )
{
	if ( ! april_file_exists ( filename ))
		return ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	g_key_file_set_boolean ( key_file, section, key, value ) ;
	april_key_file_write ( filename, key_file ) ;
	
	g_key_file_free ( key_file ) ;
	return ;
}

gboolean april_key_file_get_boolean ( gchar * filename, gchar * section, gchar * key )
{
	if ( ! april_file_exists ( filename ))
		return false ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	gboolean value = g_key_file_get_boolean ( key_file, section, key, & error ) ;
	g_key_file_free ( key_file ) ;
	
	if ( error == null )
		return value ;
	else
		return -1 ;
}

gfloat april_key_file_get_float ( gchar * filename, gchar * section, gchar * key )
{
	if ( ! april_file_exists ( filename ))
		return -1 ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	gchar * string = g_key_file_get_string ( key_file, section, key, null ) ;
	g_key_file_free ( key_file ) ;
	
	if ( string == null )
		return -1 ;
	else
	{
		gfloat f = atof ( string ) ;
		g_free ( string ) ;
		
		return f ;
	}
}

void april_key_file_remove_key ( gchar * filename, gchar * section, gchar * key )
{
	if ( ! april_file_exists ( filename ))
		return ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	g_key_file_remove_key ( key_file, section, key, null ) ;
	g_key_file_free ( key_file ) ;
}

void april_key_file_set_float ( gchar * filename, gchar * section, gchar * key, gfloat value )
{
	if ( ! april_file_exists ( filename ))
		return ;

	GKeyFile * key_file = g_key_file_new () ;
	GError * error = null ;
	
	if ( ! g_key_file_load_from_file ( key_file, filename, G_KEY_FILE_NONE, & error ))
	{
		g_warning ( "Cannot open rcfile: %s",error -> message ) ;
		g_key_file_free ( key_file ) ;
		
		return ;
	
	}
	
	gchar * string = g_strdup_printf ( "%f", value ) ;
	
	g_key_file_set_string ( key_file, section, key, string ) ;
	april_key_file_write ( filename, key_file ) ;
	
	g_key_file_free ( key_file ) ;
	g_free ( string ) ;
	
	return ;
}

void april_key_file_write ( gchar * filename, GKeyFile * file )
{
	gchar * data = g_key_file_to_data ( file, null, null ) ;
	FILE * fp = fopen ( filename, "w" ) ;
	
	if ( fp == null )
	{
		g_warning ( "Cannot open file: %s", strerror ( errno )) ;
		g_free ( data ) ;
		
		return ;
	}
	
	fprintf ( fp, "%s\n", data ) ;
	g_free ( data ) ;
	
	fclose ( fp ) ;
}
