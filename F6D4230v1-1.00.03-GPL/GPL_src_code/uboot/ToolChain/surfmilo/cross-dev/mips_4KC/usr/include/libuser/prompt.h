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

#ifndef libuser_prompt_h
#define libuser_prompt_h

#include <sys/types.h>
#include <glib.h>

G_BEGIN_DECLS

/* The type of data passed to a prompter function.  The library uses these
 * when it needs to prompt the user for information. */
struct lu_prompt {
	/* An invariant string of the form "module/name", which describes the
	 * information being prompted for.  The calling application may use
	 * this value as an index into a hash table used to cache answers to
	 * particular queries. */
	const char *key;
	/* The text of a prompt to display.  This *may* be translated for the
	 * current locale by a module. */
	const char *prompt;
	/* The text domain which contains this prompt's translations.  This
	 * may be the default libuser domain, or a module-specific text domain
	 * which the module which provided this prompt bound for gettext when
	 * it was loaded. */
	const char *domain;
	/* Whether or not the user's response should be echoed to the screen
	 * (in a console app) or visible in an entry field (in a GUI app).*/
	gboolean visible;
	/* A default value, given as a string.  This will only contain a
	 * value if the string is visible, but the reverse won't necessarily
	 * be true (default_value -> visible). */
	const char *default_value;
	/* The user's response.  This is set by the prompter function. */
	char *value;
	/* A function which can free the user's response.  This is set by the
	 * prompter function.  If NULL, the response will not be freed, ever. */
	void (*free_value) (void *);
};

/* A prompter function. */
typedef gboolean (lu_prompt_fn)(struct lu_prompt * prompts,
				int count,
				gpointer callback_data,
				struct lu_error ** error);

/* Built-in prompter functions. */
gboolean lu_prompt_console(struct lu_prompt *prompts,
			   int count,
			   gpointer callback_data,
			   struct lu_error **error);
gboolean lu_prompt_console_quiet(struct lu_prompt *prompts,
				 int count,
				 gpointer callback_data,
				 struct lu_error **error);

G_END_DECLS

#endif
