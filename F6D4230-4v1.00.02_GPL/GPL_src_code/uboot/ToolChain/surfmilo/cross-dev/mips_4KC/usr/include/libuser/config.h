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

#ifndef libuser_config_h
#define libuser_config_h

#include <sys/types.h>
#include <glib.h>

G_BEGIN_DECLS

struct lu_context;

/* Read a list of values (usually just one) for a given key. */
GList *lu_cfg_read(struct lu_context *context,
		   const char *key, const char *default_value);

/* Read a single value for a given key.  Additional values will be discarded. */
const char *lu_cfg_read_single(struct lu_context *context,
			       const char *key, const char *default_value);

/* Read the list of keys below a given key which has children.  This is
 * primarily used for iterating over a part of the configuration tree. */
GList *lu_cfg_read_keys(struct lu_context *context,
			const char *parent_key);

G_END_DECLS

#endif
