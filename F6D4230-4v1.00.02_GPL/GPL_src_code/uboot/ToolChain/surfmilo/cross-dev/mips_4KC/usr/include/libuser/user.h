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

#ifndef libuser_user_h
#define libuser_user_h

#include <sys/types.h>
#include <glib.h>
#include "config.h"
#include "entity.h"
#include "error.h"
#include "prompt.h"

G_BEGIN_DECLS

/* An opaque structure manipulated by the library. */
typedef struct lu_context lu_context_t;

/* An enumeration which decides whether we want to modify information about
 * users or groups.  We don't support both simultaneously.  */
typedef enum lu_entity_type { lu_invalid, lu_user, lu_group } lu_entity_type_t;

lu_context_t *lu_start(const char *authname,
		       lu_entity_type_t auth_type,
		       const char *modules, const char *create_modules,
		       lu_prompt_fn *prompter,
		       gpointer callback_data,
		       lu_error_t **error);
void lu_end(lu_context_t *context);

void lu_set_prompter(lu_context_t *context,
		     lu_prompt_fn *prompter, gpointer callback_data);
void lu_get_prompter(lu_context_t *context,
		     lu_prompt_fn ** prompter, gpointer *callback_data);

gboolean lu_set_modules(lu_context_t *context,
			const char *list, lu_error_t **error);
const char *lu_get_modules(lu_context_t *context);
gboolean lu_uses_elevated_privileges (lu_context_t *context);

gboolean lu_user_default(lu_context_t *ctx, const char *name,
			 gboolean system, struct lu_ent *ent);
gboolean lu_group_default(lu_context_t *ctx, const char *name,
			  gboolean system, struct lu_ent *ent);

gboolean lu_user_lookup_name(lu_context_t *context,
			     const char *name, struct lu_ent *ent,
			     lu_error_t **error);
gboolean lu_group_lookup_name(lu_context_t *context,
			      const char *name, struct lu_ent *ent,
			      lu_error_t **error);
gboolean lu_user_lookup_id(lu_context_t *context, uid_t uid,
			   struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_lookup_id(lu_context_t *context, gid_t gid,
			    struct lu_ent *ent, lu_error_t **error);
gboolean lu_user_add(lu_context_t *context,
		     struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_add(lu_context_t *context,
		      struct lu_ent *ent, lu_error_t **error);
gboolean lu_user_modify(lu_context_t *context,
			struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_modify(lu_context_t *context,
			 struct lu_ent *ent, lu_error_t **error);
gboolean lu_user_delete(lu_context_t *context,
			struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_delete(lu_context_t *context,
			 struct lu_ent *ent, lu_error_t **error);

gboolean lu_user_lock(lu_context_t *context,
		      struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_lock(lu_context_t *context,
		       struct lu_ent *ent, lu_error_t **error);
gboolean lu_user_unlock(lu_context_t *context,
			struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_unlock(lu_context_t *context,
			 struct lu_ent *ent, lu_error_t **error);

gboolean lu_user_islocked(lu_context_t *context,
			  struct lu_ent *ent, lu_error_t **error);
gboolean lu_group_islocked(lu_context_t *context,
			   struct lu_ent *ent, lu_error_t **error);

gboolean lu_user_setpass(lu_context_t *context,
			 struct lu_ent *ent, const char *newpass,
			 gboolean crypted,
			 lu_error_t **error);
gboolean lu_group_setpass(lu_context_t *context,
			  struct lu_ent *ent, const char *newpass,
			  gboolean crypted,
			  lu_error_t **error);
gboolean lu_user_removepass(lu_context_t *context,
			    struct lu_ent *ent,
			    lu_error_t **error);
gboolean lu_group_removepass(lu_context_t *context,
			     struct lu_ent *ent,
			     lu_error_t **error);

GValueArray *lu_users_enumerate(lu_context_t *context,
				const char *pattern,
				lu_error_t **error);
GValueArray *lu_groups_enumerate(lu_context_t *context,
				 const char *pattern,
				 lu_error_t **error);
GValueArray *lu_users_enumerate_by_group(lu_context_t *context,
					 const char *group,
					 lu_error_t **error);
GValueArray *lu_groups_enumerate_by_user(lu_context_t *context,
					 const char *user,
					 lu_error_t **error);

GPtrArray *lu_users_enumerate_full(lu_context_t *context,
			           const char *pattern,
			           lu_error_t **error);
GPtrArray *lu_groups_enumerate_full(lu_context_t *context,
			            const char *pattern,
			            lu_error_t **error);

G_END_DECLS
#endif
