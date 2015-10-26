#ifndef PAM_MACROS_H
#define PAM_MACROS_H

#include <sys/types.h>
#include <string.h>        /* string functions */
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

/*
 * All kind of macros used by PAM, but usable in some other
 * programs too.
 * Organized by Cristian Gafton <gafton@redhat.com>
 */

/* a 'safe' version of strdup */
#define  x_strdup(s)  ( (s) ? strdup(s):NULL )

/* Good policy to strike out passwords with some characters not just
   free the memory */

#define _pam_overwrite(x)        \
do {                             \
     register char *__xx__;      \
     if ((__xx__=(x)))           \
          while (*__xx__)        \
               *__xx__++ = '\0'; \
} while (0)

/*
 * Don't just free it, forget it too.
 */

#define _pam_drop(X) \
do {                 \
    if (X) {         \
        free(X);     \
        X=NULL;      \
    }                \
} while (0)

#define _pam_drop_reply(/* struct pam_response * */ reply, /* int */ replies) \
do {                                              \
    int reply_i;                                  \
                                                  \
    for (reply_i=0; reply_i<replies; ++reply_i) { \
	if (reply[reply_i].resp) {                \
	    _pam_overwrite(reply[reply_i].resp);  \
	    free(reply[reply_i].resp);            \
	}                                         \
    }                                             \
    if (reply)                                    \
	free(reply);                              \
} while (0)

#ifdef PAM_USER_MATCH
#ifndef PAM_USER_IN_GROUP
#define PAM_USER_IN_GROUP
#endif
#ifndef PAM_USER_IN_NETGROUP
#define PAM_USER_IN_NETGROUP
#endif
#endif

#ifdef PAM_USER_IN_GROUP
#ifndef PAM_GETPWNAM_R
#define PAM_GETPWNAM_R
#endif
#ifndef PAM_GETGRNAM_R
#define PAM_GETGRNAM_R
#endif
#endif

/* Wrappers for Unix98's getpwXXX and getgrXXX _r variants, for handling
 * ERANGE error conditions and other weirdness. */
#define DEFINE_PAM_GETENT(fn,qtype,type) \
static int \
_pam_##fn(qtype q, type *result, char **buf, size_t *buf_len, type **res) \
{ \
    size_t length; \
    char *buffer, *tmp; \
    int i; \
 \
    memset(result, 0, sizeof(*result)); \
    *res = NULL; \
 \
    *buf_len = length = 0; \
    *buf = buffer = NULL; \
 \
    do { \
        length += BUFSIZ; /* tune this for speed/memory tradeoffs */ \
        tmp = realloc(buffer, length); \
        if(tmp == NULL) { \
            free(buffer); \
            return ENOMEM; \
        } \
        buffer = tmp; \
 \
        i = fn(q, result, buffer, length, res); \
        if(i != 0) { \
            *res = NULL; \
        } else { \
            break; \
        } \
    } while(i == ERANGE); \
 \
    if((i == 0) && (*res != NULL)) { \
        *buf = buffer; \
        *buf_len = length; \
        *res = result; \
    } else { \
        *buf = NULL; \
        *buf_len = 0; \
        *res = NULL; \
    } \
 \
    return i; \
}
/* Some pre-built definitions, not actually used unless the including module
 * defines PAM_<fn>, similar to PAM_SM_xxx function declarations work. */
#ifdef PAM_GETPWNAM_R
DEFINE_PAM_GETENT(getpwnam_r,const char *,struct passwd);
#endif
#ifdef PAM_GETPWUID_R
DEFINE_PAM_GETENT(getpwuid_r,uid_t,struct passwd);
#endif
#ifdef PAM_GETGRNAM_R
DEFINE_PAM_GETENT(getgrnam_r,const char *,struct group);
#endif
#ifdef PAM_GETGRGID_R
DEFINE_PAM_GETENT(getgrgid_r,gid_t,struct group);
#endif
#ifdef PAM_GETSPNAM_R
DEFINE_PAM_GETENT(getspnam_r,const char *,struct spwd);
#endif

#ifdef PAM_USER_IN_GROUP
static int
_pam_user_in_group(const char *username, const char *groupname)
{
    char *ubuf = NULL, *gbuf = NULL;
    size_t ubuflen, gbuflen;
    struct passwd passwd, *pwd;
    struct group group, *grp;
    int ret = 0;

    if(_pam_getpwnam_r(username, &passwd, &ubuf, &ubuflen, &pwd) != 0) {
        pwd = NULL;
    }
    if(_pam_getgrnam_r(groupname, &group, &gbuf, &gbuflen, &grp) != 0) {
        grp = NULL;
    }

    if((pwd != NULL) && (grp != NULL) && (ret == 0)) {
        if(pwd->pw_gid == grp->gr_gid) {
            ret = 2;
        }
    }
#ifdef HAVE_GETGROUPLIST
    if((pwd != NULL) && (grp != NULL) && (ret == 0)) {
        gid_t grouplist[64]; /* fixme: use sysconf here */
        int ngroups, i;
        ngroups = sizeof(grouplist) / sizeof(grouplist[0]);
        if(getgrouplist(username, pwd->pw_gid, grouplist, &ngroups) != -1) {
            for(i = 0; i < ngroups; i++) {
                if(grouplist[i] == grp->gr_gid) {
                    ret = 1;
                    break;
                }
            }
        }
    }
#endif
    if((pwd != NULL) && (grp != NULL) && (ret == 0)) {
        int i;
        for(i = 0; (grp->gr_mem != NULL) && (grp->gr_mem[i] != NULL); i++) {
            if(strcmp(grp->gr_mem[i], pwd->pw_name) == 0) {
                ret = 1;
                break;
            }
        }
    }
    if(ubuf) {
        free(ubuf);
    }
    if(gbuf) {
        free(gbuf);
    }

    return ret;
}
#endif

#ifdef PAM_USER_IN_NETGROUP

#ifdef HAVE_YP_GET_DEFAULT_DOMAIN
#include <rpcsvc/ypclnt.h>
#endif

static int
_pam_user_in_netgroup(const char *username, const char *netgroupname)
{
    int ret = 0;
#if defined(HAVE_GETNETGRENT) && defined(HAVE_YP_GET_DEFAULT_DOMAIN)
    char *hostp = NULL, *userp = NULL, *domainp = NULL, *domain = NULL;
    char hostname[256];
    int i;

    if((yp_get_default_domain(&domain) != 0) || (domain == NULL)) {
        return 0;
    }

    if(setnetgrent(netgroupname) != 0) {
        return 0;
    }

    memset(hostname, 0, sizeof(hostname));
    i = gethostname(hostname, sizeof(hostname) - 1);
    if((i == 0) || (i == sizeof(hostname) - 1)) {
        return 0;
    }

    while(getnetgrent(&hostp, &userp, &domainp) == 0) {
        if((hostp == NULL) || (strcmp(hostp, hostname) == 0))
        if((userp == NULL) || (strcmp(userp, username) == 0))
        if((domainp == NULL) || (strcmp(domainp, domain) == 0)) {
                ret = 1;
                break;
        }
    }
    endnetgrent();
#endif
    return ret;
}
#endif

#ifdef PAM_USER_MATCH
static int
_pam_user_match(const char *username, const char *spec)
{
    int ret = 0;
    if(strcmp(username, spec) == 0) {
        ret = 3;
    }
    if((ret == 0) && (spec[0] == '@')) {
        ret = _pam_user_in_group(username, spec + 1);
    }
    if((ret == 0) && (spec[0] == '@')) {
        ret = _pam_user_in_netgroup(username, spec + 1);
    }
    return ret;
}
#endif

/* some debugging code */

#ifdef DEBUG

/*
 * This provides the necessary function to do debugging in PAM.
 * Cristian Gafton <gafton@redhat.com>
 */

#include <stdio.h>
#include <sys/types.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * This is for debugging purposes ONLY. DO NOT use on live systems !!!
 * You have been warned :-) - CG
 *
 * to get automated debugging to the log file, it must be created manually.
 * _PAM_LOGFILE must exist, mode 666
 */

#ifndef _PAM_LOGFILE
#define _PAM_LOGFILE "/tmp/pam-debug.log"
#endif

static void _pam_output_debug_info(const char *file, const char *fn
				   , const int line)
{
    FILE *logfile;
    int must_close = 1, fd;
   
#ifdef O_NOFOLLOW
    if ((fd = open(_PAM_LOGFILE, O_WRONLY|O_NOFOLLOW|O_APPEND)) != -1) {
#else
    if ((fd = open(_PAM_LOGFILE, O_WRONLY|O_APPEND)) != -1) {
#endif
	if (!(logfile = fdopen(fd,"a"))) {
	    logfile = stderr;
	    must_close = 0;
	    close(fd);
	}
    } else {
        logfile = stderr;
	must_close = 0;
    }
    fprintf(logfile,"[%s:%s(%d)] ",file, fn, line);
    fflush(logfile);
    if (must_close)
        fclose(logfile);
}

static void _pam_output_debug(const char *format, ...)
{
    va_list args;
    FILE *logfile;
    int must_close = 1, fd;
    
    va_start(args, format);

#ifdef O_NOFOLLOW
    if ((fd = open(_PAM_LOGFILE, O_WRONLY|O_NOFOLLOW|O_APPEND)) != -1) {
#else
    if ((fd = open(_PAM_LOGFILE, O_WRONLY|O_APPEND)) != -1) {
#endif
	if (!(logfile = fdopen(fd,"a"))) {
	    logfile = stderr;
	    must_close = 0;
	    close(fd);
	}
    } else {
	logfile = stderr;
	must_close = 0;
    }
    vfprintf(logfile, format, args);
    fprintf(logfile, "\n");
    fflush(logfile);
    if (must_close)
        fclose(logfile);

    va_end(args);
}

#define D(x) do { \
    _pam_output_debug_info(__FILE__, __FUNCTION__, __LINE__); \
    _pam_output_debug x ; \
} while (0)

#define _pam_show_mem(X,XS) do {                                      \
      int i;                                                          \
      register unsigned char *x;                                      \
      x = (unsigned char *)X;                                         \
      fprintf(stderr, "  <start at %p>\n", X);                        \
      for (i = 0; i < XS ; ++x, ++i) {                                \
          fprintf(stderr, "    %02X. <%p:%02X>\n", i, x, *x);         \
      }                                                               \
      fprintf(stderr, "  <end for %p after %d bytes>\n", X, XS);      \
} while (0)

#define _pam_show_reply(/* struct pam_response * */reply, /* int */replies) \
do {                                                                        \
    int reply_i;                                                            \
    setbuf(stderr, NULL);                                                   \
    fprintf(stderr, "array at %p of size %d\n",reply,replies);              \
    fflush(stderr);                                                         \
    if (reply) {                                                            \
	for (reply_i = 0; reply_i < replies; reply_i++) {                   \
	    fprintf(stderr, "  elem# %d at %p: resp = %p, retcode = %d\n",  \
		    reply_i, reply+reply_i, reply[reply_i].resp,            \
		    reply[reply_i].resp, _retcode);                         \
	    fflush(stderr);                                                 \
	    if (reply[reply_i].resp) {                                      \
		fprintf(stderr, "    resp[%d] = '%s'\n",                    \
			strlen(reply[reply_i].resp), reply[reply_i].resp);  \
		fflush(stderr);                                             \
	    }                                                               \
	}                                                                   \
    }                                                                       \
    fprintf(stderr, "done here\n");                                         \
    fflush(stderr);                                                         \
} while (0)

#else

#define D(x)                             do { } while (0)
#define _pam_show_mem(X,XS)              do { } while (0)
#define _pam_show_reply(reply, replies)  do { } while (0)

#endif /* DEBUG */

#endif  /* PAM_MACROS_H */
