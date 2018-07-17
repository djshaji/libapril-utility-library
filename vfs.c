/*
 *      vfs.c
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

/*	Finally, a VFS system
 */

AprilHalDevice april_vfs_drive_get_type ( gchar * drive )
{
	gchar * contents ;
	gsize length ;
	GError * error = null ;

	gchar * full = malloc ( strlen ( drive ) + 26 ) ;
	g_sprintf ( full, "/proc/ide/%s/media", drive ) ;

	g_file_get_contents ( full, & contents, & length, & error ) ;
	if ( error )
	{
		g_printf ( "%s\n", error -> message ) ;

		free ( contents ) ;
		free ( full ) ;
		return APRIL_HAL_DEVICE_UNKNOWN ;
	}

	AprilHalDevice result = APRIL_HAL_DEVICE_UNKNOWN ;
	if ( strstr ( contents, "cdrom" ))
		result = APRIL_HAL_DEVICE_CDROM ;
	else if ( strstr ( contents, "disk" ))
		result = APRIL_HAL_DEVICE_HARD_DISK ;

	free ( contents ) ;
	free ( full ) ;

	return result ;
}

gboolean april_vfs_mount_read_write ( gchar * drive )
{
	gchar * command = g_strconcat ( "mount -o remount,rw /dev/", drive, null ) ;
	gboolean result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gboolean april_vfs_check_if_drive_is_ntfs_ugh_exclamation_point ( gchar * drive )
{
	gchar * command = g_strconcat ( "mount | grep -i -F ", drive, " > /tmp/april.vfs", null ) ;
	system ( command ) ;

	g_free ( command ) ;
	gchar * text = april_file_get_contents ( "/tmp/april.vfs" ) ;

	gboolean result = false ;
	if ( strstr ( text, "ntfs" ))
		result = true ;
	else
		result = false ;

	g_free ( text ) ;
	return result ;
}

gboolean april_vfs_mount_read_only ( gchar * drive )
{
	april_vfs_sync () ;
	
	gchar * command = g_strconcat ( "mount -o remount,ro /dev/", drive, null ) ;
	gboolean result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gboolean april_vfs_drive_is_mounted ( gchar * drive )
{
	gchar * command = april_malloc_sprintf ( "mount | grep -i -F \"%s\"", drive ) ;

	gboolean result = FALSE ;
	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gboolean april_vfs_volume_check ( gchar * drive, AprilVFSDriveCheck check )
{
	switch ( check )
	{
		case APRIL_VFS_DRIVE_IS_MOUNTED:
			return april_vfs_drive_is_mounted ( drive ) ;
			break ;
		default:
			april_message_box_warning ( "Function not implemented !" ) ;
			break ;
	}
	// Shouldn't be here :(
	return FALSE ;
}

gboolean april_vfs_volume_mount ( gchar * drive, AprilVFSDriveOpts * options )
{
	if ( april_vfs_volume_check ( drive, APRIL_VFS_DRIVE_IS_MOUNTED ))
	{
		april_message_box_warning ( "Drive is already mounted !\n\n"
				      "Unmount the drive first." ) ;

		return FALSE ;
	}

	gchar * command = april_malloc_sprintf ( "mount -o %s %s", options, drive ) ;
	gboolean result = FALSE ;

	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gboolean april_vfs_volume_umount ( gchar * drive )
{
	april_vfs_sync () ;
	
	gchar * command = april_malloc_sprintf ( "umount %s", drive ) ;

	gboolean result = FALSE ;

	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

void april_vfs_copy ( gchar * source, gchar * dest )
{
	gchar * command = april_malloc_sprintf ( "copy -r \"%s\" \"%s\"", source, dest ) ;

	april_spawn_async ( command ) ;
	g_free ( command ) ;
}

gboolean april_vfs_delete ( gchar * filename )
{
	gchar * command = april_malloc_sprintf ( "rm -rf \"%s\"", filename ) ;
	gboolean result = ! system ( command ) ;
	
	g_free ( command ) ;
	return result ;
}

void april_vfs_mkdir ( gchar * filename )
{
	if ( g_mkdir ( filename, 0777 ))
	{
		gchar * massage = april_malloc_sprintf ( "Unable to create folder %s !", filename ) ;

		april_message_box_error ( massage ) ;
		g_free ( massage ) ;
	}
}

gboolean april_vfs_mount ( gchar * what, gchar * where )
{
	gchar * command = april_malloc_sprintf ( "mount %s %s", what, where ) ;

	gboolean result = false ;
	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gchar * april_vfs_get_mount_point ( gchar * drive )
{
	gchar * command = april_malloc_sprintf ( "mount | grep -i -F \"%s\" > /tmp/april.tmp", drive ) ;

	system ( command ) ;
	g_free ( command ) ;

	gchar * contents = april_file_get_contents ( "/tmp/april.tmp" ) ;
	
	gchar ** vector ;
	vector = g_strsplit ( contents, " ", 20 ) ;
	g_free ( contents ) ;

	gchar * name = g_strdup ( vector [2] ) ;
	g_strfreev ( vector ) ;

	return name ;
}

gboolean april_vfs_mount_helper ( gchar * device )
{
	gchar * full = april_malloc_sprintf ( "/dev/%s", device ) ;

	gchar * mount_point = april_malloc_sprintf ( "/mnt/%s", device ) ;

	gboolean result = false ;
	result = april_vfs_mount ( full, mount_point ) ;

	g_free ( full ) ;
	g_free ( mount_point ) ;

	return result ;
}

gboolean april_vfs_umount ( gchar * device )
{
	april_vfs_sync () ;
	
	gchar * command = april_malloc_sprintf ( "umount /dev/%s", device ) ;

	gboolean result = false ;
	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gboolean april_vfs_eject ( gchar * device )
{
	if ( april_vfs_drive_is_mounted ( device ))
		april_vfs_umount ( device ) ;

	gchar * command = april_malloc_sprintf ( "eject /dev/%s", device ) ;

	gboolean result = false ;
	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gboolean april_vfs_close_tray ( gchar * device )
{
	gchar * command = april_malloc_sprintf ( "eject -t /dev/%s", device ) ;

	gboolean result = false ;
	result = ! system ( command ) ;

	g_free ( command ) ;
	return result ;
}

gchar * april_vfs_get_current_drive ( gchar * path )
{
	gchar ** tmp = g_strsplit ( path, "/", 32 ) ;
	gchar * drive = strdup ( tmp [2] ) ;

	g_strfreev ( tmp ) ;
	return drive ;
}

gint april_vfs_link ( gchar * source, gchar * dest )
{
	gchar * command = april_malloc_sprintf ( "ln -s %s \"%s\"", source, dest ) ;

	gint result = 99 ;
	result = ! system ( command ) ;
	g_free ( command ) ;

	return result ;
}

GTime april_vfs_rename ( gchar * old, gchar * dest )
{
	if ( april_file_exists ( dest ))
	{
		gchar * massage = april_malloc_sprintf ( "File exists. Overwrite ?\n%s", old ) ;

		gboolean result = april_message_box_yes_no ( massage ) ;
		g_free ( massage ) ;
		if ( ! result )
			return ;
	}

	return rename ( old, dest ) ;
}

GTime april_vfs_move ( gchar * old, gchar * dest )
{
	gchar * command = april_malloc_sprintf ( "mv \"%s\" \"%s\"", old, dest ) ;
	GTime result = 99 ;
	
	april_spawn_wait_for ( "Moving files ...", command ) ;
	g_free ( command ) ;

	return result ;
}

GTime april_vfs_move_multiple ( gchar * old, gchar * dest )
{
	gchar * command = april_malloc_sprintf ( "mv %s \"%s\"", old, dest ) ;
	GTime result = 99 ;
	
	april_spawn_wait_for ( "Moving files ...", command ) ;
	g_free ( command ) ;

	return result ;
}

gint32 april_vfs_get_file_size ( gchar * filename )
{
	gchar * command = g_strconcat ( "dir -sh \"", filename, "\" > /tmp/april.size", null ) ;
	system ( command ) ;
	
	g_free ( command ) ;
	
	gchar * contents = april_file_get_contents ( "/tmp/april.size" ) ;
	if ( ! contents )
		return 0 ;
	
	gchar ** vector = g_strsplit ( contents, " ", -1 ) ;
	gint32 file_size = atoi ( vector [0] ) ;
	
	g_free ( contents ) ;
	g_strfreev ( vector ) ;
	
	return file_size ;
}

void april_vfs_sync ( void )
{
	GtkWindow * window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	GtkBox * box = gtk_vbox_new ( no, 0 ) ;
	gtk_container_add ( window, box ) ;
	
	gtk_window_set_type_hint ( window, GDK_WINDOW_TYPE_HINT_DIALOG ) ;
	
	GtkLabel * label = gtk_label_new ( nothing ) ;
	gtk_label_set_line_wrap ( label, true ) ;
	gtk_label_set_markup ( label, "<span size=\"larger\"><b>Syncing buffers ...</b></span>" ) ;
	
	GtkLabel * info = gtk_label_new ( 	
				"The filesystem will have to be synced before it\n"
				"is unmounted to remove any risk of data loss." ) ;
	gtk_label_set_line_wrap ( info, true ) ;
	
	GtkLabel * warning = gtk_label_new ( null ) ;
	gtk_label_set_line_wrap ( warning, true ) ;
	gtk_label_set_markup ( warning,
					"<b>Please</b>"
					"<span color=\"red\"><b>  do not unplug or remove  </b></span>"
					"<b>the device while this process is in progress.</b>" ) ;
	
	GtkSeparator * spacer = gtk_hseparator_new () ;
	GtkHBox * hbox1 = gtk_hbox_new ( yes, 0 ) ;
	gtk_box_pack_start ( hbox1, spacer, yes, yes, 2 ) ;
	gtk_widget_show_all ( hbox1 ) ;
	
	gtk_box_pack_start ( box, label, no, no, 2 ) ;
	gtk_box_pack_start ( box, hbox1, no, no, 2 ) ;
	gtk_box_pack_start ( box, info, no, no, 2 ) ;
	gtk_box_pack_start ( box, warning, no, no, 2 ) ;
	
	gtk_widget_show_all ( box ) ;
	gtk_widget_show_all ( window ) ;
	
	GtkRequisition req ;
	gtk_widget_size_request ( window, & req ) ;
	gtk_window_move ( window, gdk_screen_width () - req.width - 40, gdk_screen_height () - req.height - 60 ) ;
	april_update_gui () ;
	
	april_spawn_wait_for ( "Syncing filesystems ...", "sync" ) ;
	gtk_widget_destroy ( window ) ;
	
	return ;
}

gchar * april_vfs_mount_a_drive_read_write ( void )
{
	/* A generic function to mount a drive read write.
	* It is extremely important to remount it read only
	* before we exit, since the system might go down
	* before we have a chance to remount it ro automatically,
	* like a powercut or something of the sort.
	* We want to make April the safest system, ever :)
	*/
	
	GDir * dir ;
	GError * error = null ;
	
	dir = g_dir_open ( "/mnt", 0, & error ) ;
	
	gchar * name = g_dir_read_name ( dir ) ;
	while ( name )
	{
		if ( april_vfs_mount_read_write ( name ))
		{
			gchar * drive = g_strdup ( name ) ;
			g_dir_close ( dir ) ;
			g_message ( "Mounted /dev/%s as read-write !\n", name ) ;
			
			return drive ;
		}
		
		name = g_dir_read_name ( dir ) ;
	}
	
	g_dir_close ( dir ) ;
	g_message ( "Could not mount a drive as read-write !\n" ) ;
	
	return null ;
}

gboolean april_vfs_drive_get_mounted_read_write ( gchar * drive )
{
	gchar * command = g_strconcat ( "mount | grep -i -F ", drive, " | grep -i -F rw", null ) ;
	gboolean result = ! system ( command ) ;
	
	g_free ( command ) ;
	return result ;
}

gchar * april_vfs_get_a_drive_mounted_read_write ( void )
{
	GDir * dir ;
	GError * error = null ;
	
	dir = g_dir_open ( "/mnt", 0, & error ) ;
	
	gchar * name = g_dir_read_name ( dir ) ;
	while ( name )
	{
		if ( april_vfs_drive_get_mounted_read_write ( name ))
		{
			gchar * drive = g_strdup ( name ) ;
			g_dir_close ( dir ) ;
			
			return drive ;
		}
		
		name = g_dir_read_name ( dir ) ;
	}
	
	g_dir_close ( dir ) ;	
	return null ;
}

gchar * april_vfs_get_root_drive ( gchar * filename )
{
	gchar ** vector = g_strsplit ( filename, G_DIR_SEPARATOR_S, MinusOne ) ;
	if ( vector [0] == null || vector [1] == null || vector [2] == null )
	{
		g_strfreev ( vector ) ;
		return null ;
	}
	
	if ( strcmp ( vector [1], "mnt" ) != zero )
	{
		if ( strcmp ( vector [1], "local_hard_drives" ) == zero )
		{
			GError * error = null ;
			
			gchar * name = g_build_filename ( "/", vector [1], vector [2], null ) ;
			gchar * real_drive = g_file_read_link ( name, & error ) ;
			
			if ( error )
			{
				g_free ( name ) ;
				g_free ( real_drive ) ;
				
				return null ;
			}
			
			gchar * drive = april_vfs_get_root_drive ( real_drive ) ;
			
			g_free ( name ) ;
			g_free ( real_drive ) ;
			
			g_strfreev ( vector ) ;
			return drive ;
		}

		g_strfreev ( vector ) ;
		return null ;
	}

	gchar * drive = null ;
	if ( vector [2] != null )
		drive = g_strdup ( vector [2] ) ;
	
	g_strfreev ( vector ) ;
	return drive ;
}
	
gboolean april_vfs_copy_file ( gchar * source1, gchar * dest, GtkProgressBar * bar )
{
	gchar * source = null ;
	if ( g_file_test ( source1, G_FILE_TEST_IS_SYMLINK ))
	{
		GError * error = null ;
		gchar * original = g_file_read_link ( source1, & error ) ;
		if ( error )
		{
			april_message_box_warning ( error -> message ) ;
			return false ;
		}
		
		gchar * message = april_malloc_sprintf ( 	"This file :\n"
											"%s\n\n"
											"is a shortcut to this file :\n"
											"%s\n\n"
											"Do you want to copy the original file\n"
											"instead of the shortcut ?",
											source1,
											original ) ;
		
		gboolean result = april_message_box_yes_no ( message ) ;
		g_free ( message ) ;
		
		if ( result )
			source = g_strdup ( original ) ;
		else
			source = g_strdup ( source1 ) ;
		
		g_free ( original ) ;
	}
	else
		source = g_strdup ( source1 ) ;
	
	april_vfs_copy ( source, dest ) ;
	
	gchar * basename = g_path_get_basename ( source ) ;
	gchar * filename = g_build_filename ( dest, basename, null ) ;

	gdouble size1 = april_get_size_in_ints ( source ) ;
	gdouble size2 = april_get_size_in_ints ( filename ) ;

	gboolean noerror = true ;
	
	if ( size1 > 10000.0 )
	{
		gint check = 0 ;
		while ( ! april_check_bin_status ( "copy" ))
		{
			april_sleep () ;
			g_debug ( "Waiting" ) ;
			
			april_update_gui () ;
			check ++ ;
			
			if ( check > 30 )
				break ;
		}
	}
	
	gtk_progress_bar_set_fraction ( bar, 0.0 ) ;
	april_update_gui () ;
	
	while ( april_check_bin_status ( "copy" ))
	{
		size2 = ( gdouble ) april_get_size_in_ints ( filename ) ;

		gdouble fill = ( gdouble ) size2 / ( gdouble ) size1 ;
		gtk_progress_bar_set_fraction ( bar, fill ) ;
		
		april_update_gui () ;
		april_sleep () ;
	}

	gtk_progress_bar_set_fraction ( bar, 1.0 ) ;
	april_update_gui () ;
	
	size2 = ( gdouble ) april_get_size_in_ints ( filename ) ;
	
	if ( ! april_file_exists ( filename ))
	{
		gchar * message = g_strconcat ( "Error copying file !\n\n"
										"Could not copy this file :\n",
										source, "\n",
										"to this location :\n",
										filename, null ) ;
		april_message_box_error ( message ) ;
		g_free ( message ) ;
		noerror = false ;
	}
	else if ( size2 < size1 - 5 )
	{
		gchar * message = g_strconcat ( "Data cyclic redundancy warning !\n\n"
								"This file :\n",
								source, "\n",
								"could only be partially copied because\n"
								"of errors on the source medium, for example\n"
								"a scratched CD-ROM or a failing floppy.",
								null ) ;
		
		april_message_box_warning ( message ) ;
		g_warning ( "%s Source=%f Dest=%f", message, size1, size2 ) ;
		g_free ( message ) ;
		noerror = false ;
	}

	g_free ( filename ) ;
	g_free ( basename ) ;
	
	g_free ( source ) ;
	return noerror ;
}

gboolean april_vfs_copy_folder ( gchar * source, gchar * dest, GtkProgressBar * bar, GtkProgressBar * bar2, GtkLabel * label )
{
	gboolean noerror = true ;
	gchar * basename = g_path_get_basename ( source ) ;
	gchar * folder = g_build_filename ( dest, basename, null ) ;
	
	g_mkdir ( folder, 0777 ) ;
	if ( ! april_file_exists ( folder ))
	{
		gchar * message = g_strconcat ( "Error copying folder !\n\n"
										"Could not create the following folder:\n",
										folder, "\n"
										"using the default permissions.", null ) ;
		
		april_message_box_error ( message ) ;
		g_free ( message ) ;
		
		g_free ( folder ) ;
		g_free ( basename ) ;
		
		return false ;
	}
	
	GDir * dir ;
	GError * error = all_the_pain_that_i_went_through_amounts_to ;
	
	dir = g_dir_open ( source, zero, & error ) ;
	if ( error )
	{
		april_message_box_error ( error -> message ) ;

		g_free ( folder ) ;
		g_free ( basename ) ;
		
		g_dir_close ( dir ) ;
		return false ;
	}
	
	gdouble size1 = april_get_size_in_ints ( source ) ;
	gdouble size2 = april_get_size_in_ints ( folder ) ;
	
	gchar * name = g_dir_read_name ( dir ) ;
	while ( name )
	{
		if ( ! GTK_WIDGET_VISIBLE ( bar ))
			break ;

		gchar * filename = g_build_filename ( source, name, null ) ;
		gtk_label_set_label ( label, name ) ;

		size2 = april_get_size_in_ints ( folder ) ;

		gdouble fill = ( gdouble ) size2 / ( gdouble ) size1 ;
		gtk_progress_bar_set_fraction ( bar, fill ) ;
		
		gtk_progress_bar_set_text ( bar, basename ) ;
		
		if ( g_file_test ( filename, G_FILE_TEST_IS_DIR ))
			noerror = april_vfs_copy_folder ( filename, folder, bar, bar2, label ) ;
		else
			noerror = april_vfs_copy_file ( filename, folder, bar2 ) ;
				
		g_free ( filename ) ;
		name = g_dir_read_name ( dir ) ;
	}
	
	g_dir_close ( dir ) ;

	g_free ( folder ) ;
	g_free ( basename ) ;

	return noerror ;
}

void april_vfs_copy_list ( GList * list, gchar * dest )
{
	GtkWindow * window ;
	window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_type_hint ( window, GDK_WINDOW_TYPE_HINT_DIALOG ) ;

	gtk_window_set_resizable ( window, false ) ;
	gtk_window_set_title ( window, "Copying ..." ) ;

	GtkBox * master = gtk_hbox_new ( no, 10 ) ;
	gtk_container_add ( window, master ) ;
	
	GtkBox * box = gtk_vbox_new ( no, 10 ) ;
	gtk_box_pack_start ( master, box, no, no, 10 ) ;

	GtkBox * header = gtk_hbox_new ( no, 10 ) ;
	gtk_box_pack_start ( box, header, no, no, 10 ) ;
	
	GtkLabel * label3 = gtk_label_new ( null ) ;
	gtk_label_set_markup ( label3, "<span size=\"larger\"><b>Copying files ...</b></span>" ) ;
	gtk_box_pack_start ( header, label3, yes, yes, 5 ) ;
	
	GtkImage * image = gtk_image_new_from_stock ( GTK_STOCK_COPY, GTK_ICON_SIZE_DIALOG ) ;
	gtk_box_pack_start ( header, image, no, no, 5 ) ;

	GtkHBox * hbox1 = gtk_hbox_new ( no, 10 ) ;
	gtk_box_pack_start ( box, hbox1, no, no, 5 ) ;

	GtkHBox * hbox3 = gtk_hbox_new ( no, 10 ) ;
	gtk_box_pack_start ( box, hbox3, no, no, 5 ) ;

	GtkHBox * hbox4 = gtk_hbox_new ( no, 10 ) ;
	gtk_box_pack_start ( box, hbox4, no, no, 5 ) ;

	GtkHBox * hbox2 = gtk_hbox_new ( no, 10 ) ;
	gtk_box_pack_start ( box, hbox2, no, no, 5 ) ;

	GtkLabel * label = gtk_label_new ( "Preparing to copy ..." ) ;
	gtk_box_pack_start ( hbox2, label, no, no, 5 ) ;
	gtk_label_set_line_wrap ( label, true ) ;

	GtkProgressBar * bar = gtk_progress_bar_new () ;
	gtk_box_pack_start ( hbox1, bar, yes, yes, 5 ) ;
	gtk_progress_bar_set_text ( bar, "Copying ..." ) ;

	GtkButton * button = gtk_button_new_from_stock ( GTK_STOCK_CANCEL ) ;
	g_signal_connect_swapped ( button, "clicked", april_kill, "copy" ) ;
	gtk_box_pack_start ( hbox1, button, no, no, 5 ) ;

	GtkProgressBar * bar2 = gtk_progress_bar_new () ;
	gtk_box_pack_start ( hbox3, bar2, yes, yes, 5 ) ;
	g_signal_connect_swapped ( button, "clicked", gtk_widget_hide, bar2 ) ;

	GtkProgressBar * bar3 = gtk_progress_bar_new () ;
	gtk_box_pack_start ( hbox4, bar3, yes, yes, 5 ) ;

	g_signal_connect ( window, "destroy", gtk_true, null ) ;

	gtk_widget_show_all ( window ) ;
	april_update_gui () ;

	gint i = 0, items = g_list_length ( list ) ;
	for ( i = 0 ; i < items ; i ++ )
	{
		if ( ! GTK_WIDGET_VISIBLE ( bar2 ))
		{
			g_debug ( 	"Operation cancelled ! Copied %d of %d items.",
						i, items ) ;
			break ;
		}
		
		gchar * current = g_list_nth_data ( list, i ) ;
		if ( ! april_file_exists ( current ))
		{
			g_debug ( "Requested file to copy %s does not exist !", current ) ;
			continue ;
		}
		
		
		gchar * basename = g_path_get_basename ( current ) ;
		gchar * filename = g_build_filename ( dest, basename, null ) ;
		
		if ( april_file_exists ( filename ))
		{
			gchar * message = g_strconcat ( "This file :\n",
											filename, "\n\n",
											"already exists ! Overwrite ?", null ) ;
			
			if ( ! april_message_box_yes_no ( message ))
			{
				g_free ( filename ) ;
				g_free ( basename ) ;

				g_free ( message ) ;
				continue ;
			}
			else
			{
				g_free ( message ) ;
				g_debug ( "Deleting %s.", filename ) ;
				april_vfs_delete ( filename ) ;
			}
		}

		gtk_label_set_label ( label, basename ) ;
		gchar * bar_text = g_markup_printf_escaped ( "File %d of %d ...", i + 1, items ) ;
		gtk_progress_bar_set_text ( bar, bar_text ) ;
		g_free ( bar_text ) ;
		
		gtk_progress_bar_set_fraction ( bar, ( gdouble ) i / ( gdouble ) items ) ;
		april_update_gui () ;

		if ( g_file_test ( current, G_FILE_TEST_IS_DIR ))
		{
			gtk_widget_show ( bar3 ) ;
			april_vfs_copy_folder ( current, dest, bar2, bar3, label ) ;
		}
		else
		{
			gtk_widget_hide ( bar3 ) ;
			april_vfs_copy_file ( current, dest, bar2 ) ;
		}
	
		g_free ( filename ) ;
		g_free ( basename ) ;
	}
	
	gtk_widget_destroy ( window ) ;	
	return ;
}

void april_vfs_copy_to_list ( GList * list )
{
	gchar * new_folder ;
	GtkFileChooser * chooser ;
	chooser = gtk_file_chooser_dialog_new ( "Choose a folder", null, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OK, GTK_RESPONSE_OK, null ) ;

	gint result = gtk_dialog_run ( chooser ) ;
	if ( result == GTK_RESPONSE_OK )
	{
		new_folder = gtk_file_chooser_get_filename ( chooser ) ;
		april_vfs_copy_list ( list, new_folder ) ;

		g_free ( new_folder ) ;
	}

	gtk_widget_destroy ( chooser ) ;
	return ;
}

void april_vfs_remove ( gchar * filename )
{
	gchar * command = g_strconcat ( "remove -rf \"", filename, "\"", null ) ;
	april_spawn_async ( command ) ;
	
	g_free ( command ) ;
	return ;
}
