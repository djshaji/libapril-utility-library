/*
 *      notifier.c
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


void april_notifier ( GdkPixbuf * pixbuf, gchar * header, gchar * message, gchar * footer )
{
	GtkWidget * window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_type_hint ( window, GDK_WINDOW_TYPE_HINT_DIALOG ) ;
	gtk_window_set_decorated ( window, false ) ;
	
	gtk_window_set_accept_focus ( window, false ) ;
	
	GdkColor color ;
	color.red = 0 ;
	color.green = 43900 ;
	color.blue = 4700 ;
	
	gtk_widget_modify_bg ( window, GTK_STATE_NORMAL, & color ) ;
	
	GtkBox * box = gtk_hbox_new ( false, 5 ) ;
	gtk_container_add ( window, box ) ;
	
	GtkWidget * spacer1 = gtk_hseparator_new () ;
	GtkWidget * spacer2 = gtk_hseparator_new () ;
	GtkWidget * spacer3 = gtk_vseparator_new () ;
	GtkWidget * spacer4 = gtk_vseparator_new () ;	

	color.red = 65535 ;
	color.green = 65535 ;
	color.blue = 65535 ;

	gtk_widget_modify_bg ( spacer1, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer2, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer3, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer4, GTK_STATE_NORMAL, & color ) ;

	gtk_box_pack_start ( box, spacer3, no, no, 0 ) ;
	
	GtkImage * Image = gtk_image_new_from_pixbuf ( pixbuf ) ;
	gtk_box_pack_start ( box, Image, true, true, 5 ) ;
	
	GtkBox * align = gtk_hbox_new ( no, 0 ) ;
	gtk_box_pack_start ( box, align, no, no, 5 ) ;
	gtk_box_pack_start ( box, spacer4, no, no, 0 ) ;
	
	GtkLayout * cl = gtk_layout_new ( null, null ) ;
	GtkButton * close = gtk_button_new_with_label ( "x" ) ;
	g_signal_connect_swapped ( close, "clicked", gtk_widget_hide, box ) ;
	
	gtk_layout_put ( cl, close, 16, 10 ) ;
	gtk_widget_show_all ( cl ) ;
	gtk_widget_set_size_request ( cl, 34, 20 ) ;
	gtk_box_pack_end ( align, cl, no, no, 0 ) ;

	color.red = 0 ;
	color.green = 43900 ;
	color.blue = 4700 ;
	
	gtk_widget_modify_bg ( cl, GTK_STATE_NORMAL, & color ) ;
	
	GtkBox * vbox1 = gtk_vbox_new ( false, 0 ) ;
	gtk_box_pack_start ( align, vbox1, false, false, 2 ) ;
	gtk_box_pack_start ( vbox1, spacer1, no, no, 0 ) ;

	if ( header )
	{
		GtkLabel * label1 = gtk_label_new ( null ) ;
		GtkBox * lb1 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb1, label1, false, false, 5 ) ;
		gchar * mark1 = g_markup_printf_escaped ( "<span foreground=\"white\" size=\"larger\"><b>%s</b></span>", header ) ;
	
		gtk_box_pack_start ( vbox1, lb1, no, no, 2 ) ;
		gtk_box_pack_start ( vbox1, spacer2, no, no, 0 ) ;
		gtk_label_set_markup ( label1, mark1 ) ;
		g_free ( mark1 ) ;
	}
	
	if ( message )	
	{
		GtkLabel * label2 = gtk_label_new ( null ) ;
		GtkBox * lb2 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb2, label2, false, false, 5 ) ;

		gchar * mark2 = g_markup_printf_escaped ( "<span foreground=\"white\">%s</span>", message ) ;
		gtk_label_set_markup ( label2, mark2 ) ;
		g_free ( mark2 ) ;
		
		gtk_box_pack_start ( vbox1, lb2, no, no, 0 ) ;
	}
	
	if ( footer )
	{
		GtkLabel * label3 = gtk_label_new ( null ) ;
		GtkBox * lb3 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb3, label3, no, no, 5 ) ;
		gtk_box_pack_start ( vbox1, lb3, no, no, 0 ) ;
		
		gchar * mark3 = g_markup_printf_escaped ( "<span foreground=\"white\" size=\"small\"><b>%s</b></span>", footer ) ;
		gtk_label_set_markup ( label3, mark3 ) ;
		g_free ( mark3 ) ;
	}
	
	GtkRequisition req2 ;
	gtk_widget_size_request ( spacer1, & req2 ) ;
	gtk_widget_set_size_request ( spacer1, req2.width, 10 ) ;
	gtk_widget_set_size_request ( spacer2, req2.width, 10 ) ;
	
	gtk_widget_size_request ( spacer3, & req2 ) ;
	gtk_widget_set_size_request ( spacer3, 10, req2.height ) ;
	gtk_widget_set_size_request ( spacer4, 10, req2.height ) ;	

	gtk_widget_show_all ( vbox1 ) ;
	gtk_widget_show_all ( box ) ;
	gtk_widget_show_all ( window ) ;
	
	gint i ;
	
	GtkRequisition req ;
	gtk_widget_size_request ( window, & req ) ;
	gtk_widget_hide ( box ) ;
	
	gtk_window_move ( window, gdk_screen_width () - req.width - 20, gdk_screen_height () - req.height - 40 ) ;
	
	for ( i = 1 ; i < req.width ; i = i + 9 )
	{
		gtk_window_resize ( window, i, 2 ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	for ( i = 2 ; i < req.height ; i = i + 3 )
	{
		gtk_window_resize ( window, req.width, i ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	gtk_widget_show ( box ) ;
	april_update_gui () ;
	
	for ( i = 0 ; i < 50 ; i ++ )
	{
		if ( ! GTK_WIDGET_VISIBLE ( box ))
			i = 50 ;
	
		april_sleep () ;
		april_update_gui () ;
	}
	
	gtk_widget_hide ( box ) ;
	april_update_gui () ;
	
	for ( i = req.height ; i > 4 ; i = i - 3 )
	{
		gtk_window_resize ( window, req.width, i ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	for ( i = req.width ; i > 10 ; i = i - 9 )
	{
		gtk_window_resize ( window, i, 2 ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	gtk_widget_destroy ( window ) ;
	return ;
}

void april_notifier_with_image ( GtkImage * image, gchar * header, gchar * message, gchar * footer )
{
	GtkWidget * window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_type_hint ( window, GDK_WINDOW_TYPE_HINT_DIALOG ) ;
	gtk_window_set_decorated ( window, false ) ;
	gtk_window_set_keep_above ( window, true ) ;
	
	gtk_window_set_accept_focus ( window, false ) ;
	gtk_window_resize ( window, 1, 2 ) ;
	april_update_gui () ;
	
	GdkColor color ;
	color.red = 0 ;
	color.green = 43900 ;
	color.blue = 4700 ;
	
	gtk_widget_modify_bg ( window, GTK_STATE_NORMAL, & color ) ;
	
	GtkBox * box = gtk_hbox_new ( false, 5 ) ;
	gtk_container_add ( window, box ) ;
	
	GtkWidget * spacer1 = gtk_hseparator_new () ;
	GtkWidget * spacer2 = gtk_hseparator_new () ;
	GtkWidget * spacer3 = gtk_vseparator_new () ;
	GtkWidget * spacer4 = gtk_vseparator_new () ;	

	color.red = 65535 ;
	color.green = 65535 ;
	color.blue = 65535 ;

	gtk_widget_modify_bg ( spacer1, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer2, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer3, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer4, GTK_STATE_NORMAL, & color ) ;

	gtk_box_pack_start ( box, spacer3, no, no, 0 ) ;	
	gtk_box_pack_start ( box, image, true, true, 5 ) ;
	
	GtkBox * align = gtk_hbox_new ( no, 0 ) ;
	gtk_box_pack_start ( box, align, no, no, 5 ) ;
	gtk_box_pack_start ( box, spacer4, no, no, 0 ) ;
	
	GtkLayout * cl = gtk_layout_new ( null, null ) ;
	GtkButton * close = gtk_button_new_with_label ( "x" ) ;
	g_signal_connect_swapped ( close, "clicked", gtk_widget_hide, box ) ;
	
	gtk_layout_put ( cl, close, 16, 10 ) ;
	gtk_widget_show_all ( cl ) ;
	gtk_widget_set_size_request ( cl, 34, 20 ) ;
	gtk_box_pack_end ( align, cl, no, no, 0 ) ;

	color.red = 0 ;
	color.green = 43900 ;
	color.blue = 4700 ;
	
	gtk_widget_modify_bg ( cl, GTK_STATE_NORMAL, & color ) ;
	
	GtkBox * vbox1 = gtk_vbox_new ( false, 0 ) ;
	gtk_box_pack_start ( align, vbox1, false, false, 2 ) ;
	gtk_box_pack_start ( vbox1, spacer1, no, no, 0 ) ;

	if ( header )
	{
		GtkLabel * label1 = gtk_label_new ( null ) ;
		gtk_label_set_line_wrap ( label1, true ) ;
		GtkBox * lb1 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb1, label1, false, false, 5 ) ;
		gchar * mark1 = g_markup_printf_escaped ( "<span foreground=\"white\" size=\"larger\"><b>%s</b></span>", header ) ;
	
		gtk_box_pack_start ( vbox1, lb1, no, no, 2 ) ;
		gtk_box_pack_start ( vbox1, spacer2, no, no, 0 ) ;
		gtk_label_set_markup ( label1, mark1 ) ;
		g_free ( mark1 ) ;
	}
	
	if ( message )	
	{
		GtkLabel * label2 = gtk_label_new ( null ) ;
		gtk_label_set_line_wrap ( label2, true ) ;
		GtkBox * lb2 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb2, label2, false, false, 5 ) ;

		gchar * mark2 = g_markup_printf_escaped ( "<span foreground=\"white\">%s</span>", message ) ;
		gtk_label_set_markup ( label2, mark2 ) ;
		g_free ( mark2 ) ;
		
		gtk_box_pack_start ( vbox1, lb2, no, no, 0 ) ;
	}
	
	if ( footer )
	{
		GtkLabel * label3 = gtk_label_new ( null ) ;
		gtk_label_set_line_wrap ( label3, true ) ;
		GtkBox * lb3 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb3, label3, no, no, 5 ) ;
		gtk_box_pack_start ( vbox1, lb3, no, no, 0 ) ;
		
		gchar * mark3 = g_markup_printf_escaped ( "<span foreground=\"white\" size=\"small\"><b>%s</b></span>", footer ) ;
		gtk_label_set_markup ( label3, mark3 ) ;
		g_free ( mark3 ) ;
	}
	
	GtkRequisition req2 ;
	gtk_widget_size_request ( spacer1, & req2 ) ;
	gtk_widget_set_size_request ( spacer1, req2.width, 10 ) ;
	gtk_widget_set_size_request ( spacer2, req2.width, 10 ) ;
	
	gtk_widget_size_request ( spacer3, & req2 ) ;
	gtk_widget_set_size_request ( spacer3, 10, req2.height ) ;
	gtk_widget_set_size_request ( spacer4, 10, req2.height ) ;	

	gtk_widget_show_all ( vbox1 ) ;
	gtk_widget_show_all ( box ) ;
	
	gint i ;
	
	GtkRequisition req ;
	gtk_widget_size_request ( window, & req ) ;
	gtk_widget_hide ( box ) ;
	
	gtk_window_move ( window, gdk_screen_width () - req.width - 20, gdk_screen_height () - req.height - 40 ) ;
	
	for ( i = 1 ; i < req.width ; i = i + 9 )
	{
		gtk_window_resize ( window, i, 2 ) ;
		if ( ! GTK_WIDGET_VISIBLE ( window ))
			gtk_widget_show ( window ) ;
			
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	for ( i = 2 ; i < req.height ; i = i + 3 )
	{
		gtk_window_resize ( window, req.width, i ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	gtk_widget_show ( box ) ;
	april_update_gui () ;
	
	for ( i = 0 ; i < 50 ; i ++ )
	{
		if ( ! GTK_WIDGET_VISIBLE ( box ))
			i = 50 ;
	
		april_sleep () ;
		april_update_gui () ;
	}
	
	gtk_widget_hide ( box ) ;
	april_update_gui () ;
	
	for ( i = req.height ; i > 4 ; i = i - 3 )
	{
		gtk_window_resize ( window, req.width, i ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	for ( i = req.width ; i > 10 ; i = i - 9 )
	{
		gtk_window_resize ( window, i, 2 ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	gtk_widget_destroy ( window ) ;
	return ;
}

void april_notifier_with_stock ( gchar * stock_id, gchar * header, gchar * message, gchar * footer )
{
	GtkImage * image = gtk_image_new_from_stock ( stock_id, GTK_ICON_SIZE_DIALOG ) ;
	april_notifier_with_image ( image, header, message, footer ) ;
}


void april_notifier_with_image_alt ( GtkImage * image, gchar * header, gchar * message, gchar * footer )
{
	GtkWidget * window = gtk_window_new ( GTK_WINDOW_TOPLEVEL ) ;
	gtk_window_set_type_hint ( window, GDK_WINDOW_TYPE_HINT_DIALOG ) ;
	gtk_window_set_decorated ( window, false ) ;
		
	gtk_window_set_accept_focus ( window, false ) ;
	gtk_window_resize ( window, 1, 2 ) ;
	april_update_gui () ;
	
	GdkColor color ;
	color.red = 65535 ;
	color.green = 65535 ;
	color.blue = 65535 ;
	
	gtk_widget_modify_bg ( window, GTK_STATE_NORMAL, & color ) ;
	
	GtkBox * box = gtk_hbox_new ( false, 5 ) ;
	gtk_container_add ( window, box ) ;
	
	GtkWidget * spacer1 = gtk_hseparator_new () ;
	GtkWidget * spacer2 = gtk_hseparator_new () ;
	GtkWidget * spacer3 = gtk_vseparator_new () ;
	GtkWidget * spacer4 = gtk_vseparator_new () ;	

	color.red = 0 ;
	color.green = 43900 ;
	color.blue = 4700 ;

	gtk_widget_modify_bg ( spacer1, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer2, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer3, GTK_STATE_NORMAL, & color ) ;
	gtk_widget_modify_bg ( spacer4, GTK_STATE_NORMAL, & color ) ;

	gtk_box_pack_start ( box, spacer3, no, no, 0 ) ;	
	gtk_box_pack_start ( box, image, true, true, 5 ) ;
	
	GtkBox * align = gtk_hbox_new ( no, 0 ) ;
	gtk_box_pack_start ( box, align, no, no, 5 ) ;
	gtk_box_pack_start ( box, spacer4, no, no, 0 ) ;
	
	GtkLayout * cl = gtk_layout_new ( null, null ) ;
	GtkButton * close = gtk_button_new_with_label ( "x" ) ;
	g_signal_connect_swapped ( close, "clicked", gtk_widget_hide, box ) ;
	
	gtk_layout_put ( cl, close, 16, 10 ) ;
	gtk_widget_show_all ( cl ) ;
	gtk_widget_set_size_request ( cl, 34, 20 ) ;
	gtk_box_pack_end ( align, cl, no, no, 0 ) ;

	color.red = 65535 ;
	color.green = 65535 ;
	color.blue = 65535 ;
	
	gtk_widget_modify_bg ( cl, GTK_STATE_NORMAL, & color ) ;
	//gtk_widget_modify_bg ( close, GTK_STATE_NORMAL, & color ) ;	
	
	GtkBox * vbox1 = gtk_vbox_new ( false, 0 ) ;
	gtk_box_pack_start ( align, vbox1, false, false, 2 ) ;
	gtk_box_pack_start ( vbox1, spacer1, no, no, 0 ) ;

	if ( header )
	{
		GtkLabel * label1 = gtk_label_new ( null ) ;
		gtk_label_set_line_wrap ( label1, true ) ;
		GtkBox * lb1 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb1, label1, false, false, 5 ) ;
		gchar * mark1 = g_markup_printf_escaped ( "<span foreground=\"black\" size=\"larger\"><b>%s</b></span>", header ) ;
	
		gtk_box_pack_start ( vbox1, lb1, no, no, 2 ) ;
		gtk_box_pack_start ( vbox1, spacer2, no, no, 0 ) ;
		gtk_label_set_markup ( label1, mark1 ) ;
		g_free ( mark1 ) ;
	}
	
	if ( message )	
	{
		GtkLabel * label2 = gtk_label_new ( null ) ;
		gtk_label_set_line_wrap ( label2, true ) ;
		GtkBox * lb2 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb2, label2, false, false, 5 ) ;

		gchar * mark2 = g_markup_printf_escaped ( "<span foreground=\"black\">%s</span>", message ) ;
		gtk_label_set_markup ( label2, mark2 ) ;
		g_free ( mark2 ) ;
		
		gtk_box_pack_start ( vbox1, lb2, no, no, 0 ) ;
	}
	
	if ( footer )
	{
		GtkLabel * label3 = gtk_label_new ( null ) ;
		gtk_label_set_line_wrap ( label3, true ) ;
		GtkBox * lb3 = gtk_hbox_new ( no, 0 ) ;
		gtk_box_pack_start ( lb3, label3, no, no, 5 ) ;
		gtk_box_pack_start ( vbox1, lb3, no, no, 0 ) ;
		
		gchar * mark3 = g_markup_printf_escaped ( "<span foreground=\"black\" size=\"small\"><b>%s</b></span>", footer ) ;
		gtk_label_set_markup ( label3, mark3 ) ;
		g_free ( mark3 ) ;
	}
	
	GtkRequisition req2 ;
	gtk_widget_size_request ( spacer1, & req2 ) ;
	gtk_widget_set_size_request ( spacer1, req2.width, 10 ) ;
	gtk_widget_set_size_request ( spacer2, req2.width, 10 ) ;
	
	gtk_widget_size_request ( spacer3, & req2 ) ;
	gtk_widget_set_size_request ( spacer3, 10, req2.height ) ;
	gtk_widget_set_size_request ( spacer4, 10, req2.height ) ;	

	gtk_widget_show_all ( vbox1 ) ;
	gtk_widget_show_all ( box ) ;
	
	gint i ;
	
	GtkRequisition req ;
	gtk_widget_size_request ( window, & req ) ;
	gtk_widget_hide ( box ) ;
	
	gtk_window_move ( window, gdk_screen_width () - req.width - 20, gdk_screen_height () - req.height - 40 ) ;
	
	for ( i = 1 ; i < req.width ; i = i + 9 )
	{
		gtk_window_resize ( window, i, 2 ) ;
		if ( ! GTK_WIDGET_VISIBLE ( window ))
			gtk_widget_show ( window ) ;
			
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	for ( i = 2 ; i < req.height ; i = i + 3 )
	{
		gtk_window_resize ( window, req.width, i ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	gtk_widget_show ( box ) ;
	april_update_gui () ;
	
	for ( i = 0 ; i < 50 ; i ++ )
	{
		if ( ! GTK_WIDGET_VISIBLE ( box ))
			i = 50 ;
	
		april_sleep () ;
		april_update_gui () ;
	}
	
	gtk_widget_hide ( box ) ;
	april_update_gui () ;
	
	for ( i = req.height ; i > 4 ; i = i - 3 )
	{
		gtk_window_resize ( window, req.width, i ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	for ( i = req.width ; i > 10 ; i = i - 9 )
	{
		gtk_window_resize ( window, i, 2 ) ;
		
		april_update_gui () ;
		g_usleep ( 10000 ) ;
	}

	gtk_widget_destroy ( window ) ;
	return ;
}

