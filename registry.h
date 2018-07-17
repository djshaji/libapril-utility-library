/*
 *      registry.h
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


#ifndef __APRIL_REGISTRY_H
#define __APRIL_REGISTRY_H

/* Default registry is stored here */
#define april_registry "/usr/etc/registry"
#define april_registry_version 1.0

/* Public API */
gchar * april_registry_get_string ( gchar * root, gchar * group, gchar * key ) ;
gint april_registry_get_int ( gchar * root, gchar * group, gchar * key ) ;
gdouble april_registry_get_double ( gchar * root, gchar * group, gchar * key ) ;

gboolean april_registry_is_writable ( void ) ;

void april_registry_set_string ( gchar * root, gchar * group, gchar * key, gchar * value ) ;
void april_registry_set_int ( gchar * root, gchar * group, gchar * key, gint value ) ;
void april_registry_set_double ( gchar * root, gchar * group, gchar * key, gdouble value ) ;

void april_registry_set_boolean ( gchar * root, gchar * group, gchar * key, gboolean value ) ;
gboolean april_registry_get_boolean ( gchar * root, gchar * group, gchar * key ) ;

void april_registry_remove_key ( gchar * root ) ;
void april_registry_remove_entry ( gchar * root, gchar * group, gchar * value ) ;

#endif
