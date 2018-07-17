/*
 *      thumbnails.h
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

/*		A simple way to generate video thumbnails using MPlayer */

#ifndef __APRIL_THUMBNAILS_H
#define __APRIL_THUMBNAILS_H

typedef enum _AprilThumbnailSize {
	APRIL_THUMBNAIL_TINY = 24,
	APRIL_THUMBNAIL_SMALL = 32,
	APRIL_THUMBNAIL_MEDIUM = 48,
	APRIL_THUMBNAIL_LARGE = 64,
	APRIL_THUMBNAIL_EXTRA_LARGE = 128,
	APRIL_THUMBNAIL_TEXAS = 160,
	APRIL_THUMBNAIL_GALLERY = 256
} AprilThumbnailSize ;

#define APRIL_THUMBNAIL_DEFAULT APRIL_THUMBNAIL_EXTRA_LARGE

GdkPixbuf * april_thumbnail_video ( gchar * filename ) ;
GdkPixbuf * april_thumbnail_video_mplayer ( gchar * filename ) ;

#endif /*__APRIL_THUMBNAILS_H */
