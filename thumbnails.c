/*
 *      thumbnails.c
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

GdkPixbuf * april_thumbnail_video ( gchar * filename )
{
	return april_thumbnail_video_mplayer ( filename ) ;
}

GdkPixbuf * april_thumbnail_video_mplayer ( gchar * filename )
{
	gchar * april_boy_screenshot_temp_dir = g_build_filename ( "/tmp", "mplayer.screenshot", null ) ;
	if ( ! april_file_exists ( april_boy_screenshot_temp_dir ))
		g_mkdir ( april_boy_screenshot_temp_dir, 0777 ) ;
	
	gchar * command = april_malloc_sprintf ( "mplayer \"%s\" -vfm ffmpeg -nosound -xy 3 -vf spp=4,framestep=I,scale -frames 1 -vo jpeg:outdir=\"%s\" -endpos 1 > /tmp/april.mplayer", filename, april_boy_screenshot_temp_dir ) ;

	april_purge_folder ( april_boy_screenshot_temp_dir ) ;
	system ( command ) ;

	g_free ( command ) ;

	GDir * dir ;
	GError * error = NULL ;
	dir = g_dir_open ( april_boy_screenshot_temp_dir, 0, & error ) ;
	if ( error )
		g_printf ( "%s\n", error -> message ) ;

	gchar * fold_shot = g_dir_read_name ( dir ) ;
	gchar * old_shot = g_build_filename ( april_boy_screenshot_temp_dir, fold_shot, NULL ) ;

	g_free ( fold_shot ) ;
	g_dir_close ( dir ) ;
	g_free ( april_boy_screenshot_temp_dir ) ;

	error = null ;
	GdkPixbuf * pixbuf = gdk_pixbuf_new_from_file_at_scale ( old_shot, APRIL_THUMBNAIL_DEFAULT, APRIL_THUMBNAIL_DEFAULT, true, & error ) ;
	if ( error )
			g_printf ( "april thumbnailer: %s\n", error -> message ) ;

	if ( pixbuf == null )
	{
		g_printf ( "Unable to load pixmap for %s !\n", filename ) ;
		g_object_unref ( pixbuf ) ;

		g_free ( old_shot ) ;
		return null ;
	}
	
	g_free ( old_shot ) ;
	return pixbuf ;
}
