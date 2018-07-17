/*
 *      vfs.h
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

#ifndef __APRIL_VFS_H
#define __APRIL_VFS_H

typedef enum _AprilHalDevice {
	APRIL_HAL_DEVICE_CDROM,
	APRIL_HAL_DEVICE_HARD_DISK,
	APRIL_HAL_DEVICE_USB_DRIVE,
	APRIL_HAL_DEVICE_FLOPPY,
	APRIL_HAL_DEVICE_UNKNOWN
} AprilHalDevice ;

typedef enum _AprilVFSDriveCheck {
	APRIL_VFS_DRIVE_IS_MOUNTED,
	APRIL_VFS_DRIVE_IS_HARDDISK,
	APRIL_VFS_DRIVE_IS_CDROM
} AprilVFSDriveCheck ;

typedef gchar AprilVFSDriveOpts ;

/* Public API */
AprilHalDevice april_vfs_drive_get_type ( gchar * drive ) ;

/* Filesystems */
gboolean april_vfs_mount_read_write ( gchar * drive ) ;
gboolean april_vfs_mount_read_only ( gchar * drive ) ;

gboolean april_vfs_check_if_drive_is_ntfs_ugh_exclamation_point ( gchar * drive ) ;

gboolean april_vfs_drive_is_mounted ( gchar * drive ) ;
gboolean april_vfs_volume_check ( gchar * drive, AprilVFSDriveCheck check ) ;

gboolean april_vfs_volume_mount ( gchar * drive, AprilVFSDriveOpts * options ) ;
gboolean april_vfs_volume_umount ( gchar * drive ) ;

void april_vfs_sync ( void ) ;
gchar * april_vfs_mount_a_drive_read_write ( void ) ;

gboolean april_vfs_drive_get_mounted_read_write ( gchar * drive ) ;
gchar * april_vfs_get_a_drive_mounted_read_write ( void ) ;

gchar * april_vfs_get_root_drive ( gchar * filename ) ;

gboolean april_vfs_mount ( gchar * what, gchar * where ) ;
gboolean april_vfs_mount_helper ( gchar * device ) ;

gboolean april_vfs_umount ( gchar * device ) ;
gboolean april_vfs_eject ( gchar * device ) ;
gboolean april_vfs_close_tray ( gchar * device ) ;

gchar * april_vfs_get_mount_point ( gchar * drive ) ;
gchar * april_vfs_get_current_drive ( gchar * path ) ;

/* Copy / Paste */
void april_vfs_copy ( gchar * source, gchar * dest ) ;
gboolean april_vfs_delete ( gchar * filename ) ;

gint april_vfs_link ( gchar * source, gchar * dest ) ;
void april_vfs_mkdir ( gchar * filename ) ;

GTime april_vfs_rename ( gchar * old, gchar * dest ) ;
GTime april_vfs_move ( gchar * old, gchar * dest ) ;
GTime april_vfs_move_multiple ( gchar * old, gchar * dest ) ;
void april_vfs_remove ( gchar * filename ) ;

gint32 april_vfs_get_file_size ( gchar * filename ) ;

/* GUI versions ( move a progress bar to show amount of file copied */
gboolean april_vfs_copy_file ( gchar * source1, gchar * dest, GtkProgressBar * bar ) ;
gboolean april_vfs_copy_folder ( gchar * source, gchar * dest, GtkProgressBar * bar, GtkProgressBar * bar2, GtkLabel * label ) ;

void april_vfs_copy_list ( GList * list, gchar * dest ) ;
void april_vfs_copy_to_list ( GList * list ) ;

#endif /* __APRIL_VFS_H */
