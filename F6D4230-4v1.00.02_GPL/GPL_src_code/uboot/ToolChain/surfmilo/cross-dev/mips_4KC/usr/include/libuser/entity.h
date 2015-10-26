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

#ifndef libuser_entity_h
#define libuser_entity_h

#include <sys/types.h>
#include <stdio.h>
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/* Opaque data type. */
typedef struct lu_ent lu_ent_t;

/* Attributes carried by all user structures. */
#define LU_USERNAME		"pw_name"
#define LU_USERPASSWORD		"pw_passwd"
#define LU_UIDNUMBER		"pw_uid"
#define LU_GIDNUMBER		"pw_gid"
#define LU_GECOS		"pw_gecos"
#define LU_HOMEDIRECTORY	"pw_dir"
#define LU_LOGINSHELL		"pw_shell"

/* Attributes carried by group structures. */
#define LU_GROUPNAME		"gr_name"
#define LU_GROUPPASSWORD	"gr_passwd"
/* #define LU_GIDNUMBER		"gr_gid" */
#define LU_MEMBERNAME		"gr_mem"
#define LU_ADMINISTRATORNAME	"gr_adm"

/* Attributes carried by shadow user structures. */
#define LU_SHADOWNAME		LU_USERNAME
#define LU_SHADOWPASSWORD	"sp_pwdp"
#define LU_SHADOWLASTCHANGE	"sp_lstchg"
#define LU_SHADOWMIN		"sp_min"
#define LU_SHADOWMAX		"sp_max"
#define LU_SHADOWWARNING	"sp_warn"
#define LU_SHADOWINACTIVE	"sp_inact"
#define LU_SHADOWEXPIRE		"sp_expire"
#define LU_SHADOWFLAG		"sp_flag"

/* Additional fields carried by some structures.  If they have them,
 * it's safe to change them. */
#define LU_COMMONNAME		"cn"
#define LU_GIVENNAME		"givenName"
#define LU_SN			"sn"
#define LU_ROOMNUMBER		"roomNumber"
#define LU_TELEPHONENUMBER	"telephoneNumber"
#define LU_HOMEPHONE		"homePhone"
#define LU_EMAIL		"mail"

/* Function to allocate a new entity structure, or destroy one. */
lu_ent_t *lu_ent_new(void);
void lu_ent_free(lu_ent_t *ent);

/* Deep-copy the contents of one entity structure into another. */
void lu_ent_copy(lu_ent_t *source, lu_ent_t *dest);

/* Entity structures have a limited form of version-control, and that gives
 * us the ability to roll back changes. */
void lu_ent_revert(lu_ent_t *ent);

/* This function rolls changes forward. */
void lu_ent_commit(lu_ent_t *ent);

/* These functions are used to set and query "current" data attributes, the
 * values the library itself usually sets. */
GValueArray *lu_ent_get_current(lu_ent_t *ent, const char *attribute);
gboolean lu_ent_has_current(lu_ent_t *ent, const char *attribute);
void lu_ent_set_current(lu_ent_t *ent, const char *attr,
			const GValueArray *values);
void lu_ent_add_current(lu_ent_t *ent, const char *attr,
			const GValue *value);
void lu_ent_clear_current(lu_ent_t *ent, const char *attr);
void lu_ent_clear_all_current(lu_ent_t *ent);
void lu_ent_del_current(lu_ent_t *ent, const char *attr,
			const GValue *value);
GList *lu_ent_get_attributes_current(lu_ent_t *ent);

/* These functions are used to set and query "pending" data attributes, which
 * will take effect when we write this entry back out. */
GValueArray *lu_ent_get(lu_ent_t *ent, const char *attribute);
gboolean lu_ent_has(lu_ent_t *ent, const char *attribute);
void lu_ent_set(lu_ent_t *ent, const char *attr,
		const GValueArray *values);
void lu_ent_add(lu_ent_t *ent, const char *attr,
		const GValue *value);
void lu_ent_clear(lu_ent_t *ent, const char *attr);
void lu_ent_clear_all(lu_ent_t *ent);
void lu_ent_del(lu_ent_t *ent, const char *attr, const GValue *value);
GList *lu_ent_get_attributes(lu_ent_t *ent);

void lu_ent_dump(lu_ent_t *ent, FILE *fp);

G_END_DECLS

#endif
