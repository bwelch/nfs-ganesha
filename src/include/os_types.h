/*
 *
 *
 * Copyright Panasas, Inc (2012)
 * contributeur : Brent Welch welch@panasas.com
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * ---------------------------------------
 */

/**
 * \file    os_types.h
 * \author  $Author: welch $
 * \date    $Date: 2006/02/08 12:45:27 $
 * \version $Revision: 1.19 $
 * \brief   OS Portability Layer types and constants.
 *
 *
 *
 */

#ifndef _OS_TYPES_H
#define _OS_TYPES_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "fsal_types.h"

/*
 * Iterating over the mount table uses platform-specific APIs.
 * The os_mntent famliy defined here hides those differences
 *
 * os_mntent_setup allocates and initializes a handle.
 *
 * os_mntent_next returns the next mount table entry.
 *    The len parameter is the size of the caller's buffers that
 *    they must pass in to take a copy of the mntdir (where it is mounted)
 *    the type of the mount, and the fsname (what is being mounted)
 *
 * os_mntent_done deallocates the handle and internal buffers.
 */

typedef void *os_mnt_iter_t;

fsal_status_t os_mntent_setup(os_mnt_iter_t *mnt_handle);
int os_mntent_next(os_mnt_iter_t mnt_handle, int len, char *mntdir,
        char *type, char *fsname);
int os_mntent_done(os_mnt_iter_t mnt_handle);

/*
 * Linux and FreeBSD dirent structures are slightly different.
 * There is an OS-specific datatype returned from getdents.
 * The following type is FSAL-generic, and the vfsfsal_get_dirent API
 * converts from the OS-specific type to the generic type.
 */
typedef struct
{
  uint64_t d_ino;
  uint32_t d_reclen;
  uint32_t d_type;
  char     d_name[256];         /* Well known dirent name size */
} os_dirent_t;

/*
 * os_convert_dirent converts from platform specific dirent structure
 * to the os_dirent_t type.
 * The addr is the pointer into the array of dirents returned by the syscall
 * The dp pointer is the result.
 */

void os_convert_dirent(char *addr, os_dirent_t *dp);

#endif /* _OS_TYPES_H */
