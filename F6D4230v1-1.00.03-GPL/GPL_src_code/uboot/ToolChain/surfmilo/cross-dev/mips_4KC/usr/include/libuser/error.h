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

#ifndef libuser_error_h
#define libuser_error_h

#include <sys/types.h>
#include <errno.h>
#include <glib.h>

G_BEGIN_DECLS

typedef enum lu_status {
	/* Non-fatal. */
	lu_success = 0,
	lu_warning_config_disabled,

	/* Fatal. */
	lu_error_generic,
	lu_error_privilege,
	lu_error_access_denied,

	/* Data validation errors. */
	lu_error_name_bad,
	lu_error_id_bad,
	lu_error_name_used,
	lu_error_id_used,

	/* Terminal manipulation errors. */
	lu_error_terminal,

	/* File I/O errors. */
	lu_error_open,
	lu_error_lock,
	lu_error_stat,
	lu_error_read,
	lu_error_write,
	lu_error_search,

	/* Initialization or module-loading errors. */
	lu_error_init,
	lu_error_module_load,
	lu_error_module_sym,
	lu_error_module_version,
} lu_status_t;

typedef struct lu_error {
	enum lu_status code;
	char *string;
} lu_error_t;

/* Checks that a passed-in error pointer is not already populated, and calls
   abort() if it is. */
#define LU_ERROR_CHECK(err_p_p) \
do { \
	struct lu_error **__err = (err_p_p); \
	if ((__err == NULL) || (*__err != NULL)) { \
		if(__err == NULL) { \
			fprintf(stderr, "libuser fatal error: %s() called with NULL " #err_p_p "\n", __FUNCTION__); \
		} else \
		if(*__err != NULL) { \
			fprintf(stderr, "libuser fatal error: %s() called with non-NULL *" #err_p_p, __FUNCTION__); \
		} \
		abort(); \
	} \
} while(0)

/* Functions for allocating and freeing error objects. */
void lu_error_new(lu_error_t **error, lu_status_t code,
		  const char *fmt, ...);
const char *lu_strerror(lu_error_t *error);
gboolean lu_error_is_success(lu_status_t status);
gboolean lu_error_is_warning(lu_status_t status);
gboolean lu_error_is_error(lu_status_t status);
void lu_error_free(lu_error_t **error);

G_END_DECLS

#endif
