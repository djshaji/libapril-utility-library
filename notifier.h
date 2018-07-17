/*
 *      no
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

#ifndef __APRIL_NOTIFIER_H
#define __APRIL_NOTIFIER_H

void april_notifier ( GdkPixbuf * pixbuf, gchar * header, gchar * message, gchar * footer ) ;
void april_notifier_with_image ( GtkImage * image, gchar * header, gchar * message, gchar * footer ) ;

void april_notifier_with_stock ( gchar * stock_id, gchar * header, gchar * message, gchar * footer ) ;
void april_notifier_with_image_alt ( GtkImage * image, gchar * header, gchar * message, gchar * footer ) ;

#endif /* __APRIL_NOTIFIER_H */
