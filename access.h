/*
 *      acess.h
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


/* A VERY simple API to use festival and ESD for adding ( at least )
 * minimal accessibility capabilities to applications.
 * 
 * Even though most functions are terribly slow at doing their job,
 * ALL of them work. If nothing else, they might serve to help
 * a blind user navigate through programs a little easily.
 * 
 * Developers are encouraged to use this API as much as possible,
 * and develop the parts they may think to be too childish.
 * 
 * Does this count towards my community service yet ?
 */

#ifndef __APRIL_ACCESS_H
#define __APRIL_ACCESS_H

/* Is ESD running ? If not, attempt to run it. */
gboolean april_access_esd_status ( void ) ;

/* Elementary filesystem interface */
void april_access_say_file ( gchar * filename ) ;
void april_access_say_directory ( gchar * folder ) ;

/* The below are considered most useful for basic applications */
void april_access_say_text ( gchar * text ) ;
void april_access_say_text_async ( gchar * text ) ;

/* If ESD is ***not*** available */
void april_access_say_text_async_adrenaline ( gchar * text ) ;

/* Turn off all voices */
void april_access_shut_up () ;

/* Some interesting uses of the above */
void april_access_say_time ( void ) ;
void april_access_say_fortune ( void ) ;
void april_access_say_date ( void ) ;

/* Kill MPlayer, audacious and gmplayer. Not really useful,
 * but left here anyway */
void april_access_sak ( void ) ;
void april_access_reset_to_sane_stage ( void ) ;

#endif /* __APRIL_ACCESS_H */
