/*
 *      esd.h
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

#ifndef __APRIL_ESD_H
#define __APRIL_ESD_H

void april_esd_init ( void ) ;
gboolean april_esd_status ( void ) ;
gboolean april_esd_is_standby ( void ) ;
gboolean april_esd_check_status ( void ) ;
gchar * april_esd_get_info ( void ) ;

/* Private */
void april_esd_set_status ( GtkWidget * widget, shagpointer user_data ) ;

/* A simple dialog for ESD's standby / resume */
void april_esd_config ( void ) ;

gboolean april_esd_resume ( void ) ;
gboolean april_esd_standby ( void ) ;

#endif /* __APRIL_ESD_H */
