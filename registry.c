/*
 *      registry.c
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

/*		April Registry.
 * 		Eat my dust, Mycrotchissoft !!!
 * 		Saturday, December 20 2008
 */


gchar * april_registry_get_string ( gchar * root, gchar * group, gchar * key )
{
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
		return null ;
	
	gchar * value = april_key_file_get_string ( filename, group, key ) ;
	g_free ( filename ) ;
	
	return value ;
}

gint april_registry_get_int ( gchar * root, gchar * group, gchar * key )
{
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
		return -1 ;
	
	gint value = april_key_file_get_int ( filename, group, key ) ;
	g_free ( filename ) ;
	
	return value ;
}

gdouble april_registry_get_double ( gchar * root, gchar * group, gchar * key )
{
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
		return -1.0 ;
	
	gdouble value = april_key_file_get_float ( filename, group, key ) ;
	g_free ( filename ) ;
	
	return value ;
}

gboolean april_registry_is_writable ( void )
{
	if ( g_getenv ( "FORCE_APRIL_REGISTRY" ))
		return true ;
	else
		return g_file_test ( "/usr", G_FILE_TEST_IS_SYMLINK ) ;
}

void april_registry_set_string ( gchar * root, gchar * group, gchar * key, gchar * value )
{
	if ( ! april_registry_is_writable ())
	{
		april_message_box_warning ( "Cannot write registry entry ! The "
									"registry is not writable. This is probably "
									"an older version of April. Please "
									"upgrade." ) ;
		return ;
	}
	
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
	{
		gchar * dirname = g_path_get_dirname ( filename ) ;
		if ( ! g_file_test ( dirname, G_FILE_TEST_EXISTS ))
		{
			gchar * command = g_strdup_printf ( "mkdir -p \"%s\"", dirname ) ;
			system ( command ) ;
			
			g_free ( command ) ;
		}
		
		g_free ( dirname ) ;
		
		gchar * command = g_strdup_printf ( "touch \"%s\"", filename ) ;
		system ( command ) ;
		
		g_free ( command ) ;
	}
	
	april_key_file_set_string ( filename, group, key, value ) ;
	g_free ( filename ) ;
}


void april_registry_set_int ( gchar * root, gchar * group, gchar * key, gint value )
{
	if ( ! april_registry_is_writable ())
	{
		april_message_box_warning ( "Cannot write registry entry ! The "
									"registry is not writable. This is probably "
									"an older version of April. Please "
									"upgrade." ) ;
		return ;
	}
	
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
	{
		gchar * dirname = g_path_get_dirname ( filename ) ;
		if ( ! g_file_test ( dirname, G_FILE_TEST_EXISTS ))
		{
			gchar * command = g_strdup_printf ( "mkdir -p \"%s\"", dirname ) ;
			system ( command ) ;
			
			g_free ( command ) ;
		}
		
		g_free ( dirname ) ;
		gchar * command = g_strdup_printf ( "touch \"%s\"", filename ) ;
		system ( command ) ;
		
		g_free ( command ) ;
	}
	
	april_key_file_set_int ( filename, group, key, value ) ;
	g_free ( filename ) ;
}

void april_registry_set_double ( gchar * root, gchar * group, gchar * key, gdouble value )
{
	if ( ! april_registry_is_writable ())
	{
		april_message_box_warning ( "Cannot write registry entry ! The "
									"registry is not writable. This is probably "
									"an older version of April. Please "
									"upgrade." ) ;
		return ;
	}
	
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
	{
		gchar * dirname = g_path_get_dirname ( filename ) ;
		if ( ! g_file_test ( dirname, G_FILE_TEST_EXISTS ))
		{
			gchar * command = g_strdup_printf ( "mkdir -p \"%s\"", dirname ) ;
			system ( command ) ;
			
			g_free ( command ) ;
		}
		
		g_free ( dirname ) ;
		gchar * command = g_strdup_printf ( "touch \"%s\"", filename ) ;
		system ( command ) ;
		
		g_free ( command ) ;
	}
	
	april_key_file_set_float ( filename, group, key, value ) ;
	g_free ( filename ) ;
}

gboolean april_registry_get_boolean ( gchar * root, gchar * group, gchar * key )
{
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
		return false ;
	
	gdouble value = april_key_file_get_boolean ( filename, group, key ) ;
	g_free ( filename ) ;
	
	return value ;
}

void april_registry_set_boolean ( gchar * root, gchar * group, gchar * key, gboolean value )
{
	if ( ! april_registry_is_writable ())
	{
		april_message_box_warning ( "Cannot write registry entry ! The "
									"registry is not writable. This is probably "
									"an older version of April. Please "
									"upgrade." ) ;
		return ;
	}
	
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
	{
		gchar * dirname = g_path_get_dirname ( filename ) ;
		if ( ! g_file_test ( dirname, G_FILE_TEST_EXISTS ))
		{
			gchar * command = g_strdup_printf ( "mkdir -p \"%s\"", dirname ) ;
			system ( command ) ;
			
			g_free ( command ) ;
		}
		
		g_free ( dirname ) ;
		gchar * command = g_strdup_printf ( "touch \"%s\"", filename ) ;
		system ( command ) ;
		
		g_free ( command ) ;
	}
	
	april_key_file_set_boolean ( filename, group, key, value ) ;
	g_free ( filename ) ;
}

void april_registry_remove_key ( gchar * root )
{
	if ( root == null )
		return ;
	
	if ( ! april_registry_is_writable ())
	{
		april_message_box_warning ( "Cannot write registry entry ! The "
									"registry is not writable. This is probably "
									"an older version of April. Please "
									"upgrade." ) ;
		return ;
	}
	
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
	{
		g_warning ( "Registry key %s does not exist ! And, therefore, "
					"I cannot delete it.", filename ) ;
		
		g_free ( filename ) ;
		return ;
	}
	
	gchar * command = g_strdup_printf ( "remove -rfv \"%s\"", filename ) ;
	if ( system ( command ) != 0 )
	{
		april_message_box_error ( "Cannot delete registry key !" ) ;
	}
	
	g_free ( command ) ;
	g_free ( filename ) ;
}

void april_registry_remove_entry ( gchar * root, gchar * group, gchar * value )
{
	if ( ! april_registry_is_writable ())
	{
		april_message_box_warning ( "Cannot write registry entry ! The "
									"registry is not writable. This is probably "
									"an older version of April. Please "
									"upgrade." ) ;
		return ;
	}
	
	gchar * filename = g_build_filename ( april_registry, root, null ) ;
	if ( ! g_file_test ( filename, G_FILE_TEST_EXISTS ))
	{
		g_warning ( "Registry key %s does not exist ! And, therefore, "
					"I cannot delete it.", filename ) ;
		
		g_free ( filename ) ;
		return ;
	}
	
	april_key_file_remove_key ( filename, group, value ) ;
	g_free ( filename ) ;
}
