/*
 * Copyright (C) 2000-2002 Red Hat, Inc.
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ident "$Id: userquota.h,v 1.2 2002/01/24 21:05:30 nalin Exp $"

#ifndef libuser_quota_h
#define libuser_quota_h

#include <sys/types.h>
#include <glib.h>

G_BEGIN_DECLS

int quota_on(void);
int quota_off(void);

char **quota_get_specials_user(void);
char **quota_get_specials_group(void);
void quota_free_specials(char **specials);

int quota_get_user(uid_t uid, const char *special,
		   int32_t * inode_usage, int32_t * inode_soft,
		   int32_t * inode_hard, int32_t * inode_grace,
		   int32_t * block_usage, int32_t * block_soft,
		   int32_t * block_hard, int32_t * block_grace);
int quota_set_user(uid_t uid, const char *special,
		   int32_t inode_soft, int32_t inode_hard,
		   int32_t inode_grace, int32_t block_soft,
		   int32_t block_hard, int32_t block_grace);

int quota_get_group(gid_t gid, const char *special,
		    int32_t * inode_usage, int32_t * inode_soft,
		    int32_t * inode_hard, int32_t * inode_grace,
		    int32_t * block_usage, int32_t * block_soft,
		    int32_t * block_hard, int32_t * block_grace);
int quota_set_group(gid_t gid, const char *special,
		    int32_t inode_soft, int32_t inode_hard,
		    int32_t inode_grace, int32_t block_soft,
		    int32_t block_hard, int32_t block_grace);

G_END_DECLS

#endif
