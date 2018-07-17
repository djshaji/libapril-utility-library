/*
 *      rcfile.h
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

#ifndef __APRIL_RCFILE_H
#define __APRIL_RCFILE_H

#include <errno.h>

void april_key_file_set_string ( gchar * filename, gchar * section, gchar * key, gchar * string ) ;
gchar * april_key_file_get_string ( gchar * filename, gchar * section, gchar * key ) ;

void april_key_file_set_int ( gchar * filename, gchar * section, gchar * key, guint32 value ) ;
guint32 april_key_file_get_int ( gchar * filename, gchar * section, gchar * key ) ;

void april_key_file_set_boolean ( gchar * filename, gchar * section, gchar * key, gboolean value ) ;
gboolean april_key_file_get_boolean ( gchar * filename, gchar * section, gchar * key ) ;

gfloat april_key_file_get_float ( gchar * filename, gchar * section, gchar * key ) ;
void april_key_file_set_float ( gchar * filename, gchar * section, gchar * key, gfloat value ) ;

void april_key_file_remove_key ( gchar * filename, gchar * section, gchar * key ) ;
void april_key_file_write ( gchar * filename, GKeyFile * file ) ;
#endif /* __APRIL_RCFILE_H */
