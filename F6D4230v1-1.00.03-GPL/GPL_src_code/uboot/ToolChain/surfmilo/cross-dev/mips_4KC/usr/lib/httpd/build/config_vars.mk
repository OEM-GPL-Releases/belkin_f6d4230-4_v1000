exp_exec_prefix = /usr
rel_exec_prefix = /usr
exp_bindir = /usr/bin
rel_bindir = /usr/bin
exp_sbindir = /usr/sbin
rel_sbindir = /usr/sbin
exp_libdir = /usr/lib
rel_libdir = /usr/lib
exp_libexecdir = /usr/lib/httpd/modules
rel_libexecdir = /usr/lib/httpd/modules
exp_mandir = /usr/share/man
rel_mandir = /usr/share/man
exp_sysconfdir = /etc/httpd/conf
rel_sysconfdir = conf
exp_datadir = /var/www
rel_datadir = /var/www
exp_installbuilddir = /usr/lib/httpd/build
rel_installbuilddir = /usr/lib/httpd/build
exp_errordir = /var/www/error
rel_errordir = /var/www/error
exp_iconsdir = /var/www/icons
rel_iconsdir = /var/www/icons
exp_htdocsdir = /var/www/htdocs
rel_htdocsdir = /var/www/htdocs
exp_manualdir = /var/www/manual
rel_manualdir = /var/www/manual
exp_cgidir = /var/www/cgi-bin
rel_cgidir = /var/www/cgi-bin
exp_includedir = /usr/include/httpd
rel_includedir = /usr/include/httpd
exp_localstatedir = /etc/httpd
rel_localstatedir =
exp_runtimedir = /etc/httpd/logs
rel_runtimedir = logs
exp_logfiledir = /etc/httpd/logs
rel_logfiledir = logs
exp_proxycachedir = /etc/httpd/proxy
rel_proxycachedir = proxy
SHLTCFLAGS = -prefer-pic
LTCFLAGS = -prefer-non-pic -static
MPM_NAME = prefork
MPM_SUBDIR_NAME = prefork
htpasswd_LTFLAGS =
htdigest_LTFLAGS =
rotatelogs_LTFLAGS =
logresolve_LTFLAGS =
htdbm_LTFLAGS =
ab_LTFLAGS =
checkgid_LTFLAGS =
APACHECTL_ULIMIT = ulimit -S -n `ulimit -H -n`
progname = httpd
MPM_LIB = server/mpm/prefork/libprefork.la
OS = unix
OS_DIR = unix
BUILTIN_LIBS = modules/http/mod_http.la modules/mappers/mod_so.la
SHLIBPATH_VAR = LD_LIBRARY_PATH
OS_SPECIFIC_VARS =
PRE_SHARED_CMDS = echo ""
POST_SHARED_CMDS = echo ""
shared_build = shared-build
KRBDIR = /opt/eldk/build/mips-2005-03-06/work/mips_4KC/usr/kerberos
AP_BUILD_SRCLIB_DIRS = apr apr-util
AP_CLEAN_SRCLIB_DIRS = apr-util apr
bindir = /usr/bin
sbindir = /usr/sbin
cgidir = ${datadir}/cgi-bin
logfiledir = ${localstatedir}/logs
exec_prefix = /usr
datadir = /var/www
localstatedir = ${prefix}
mandir = /usr/share/man
libdir = /usr/lib
libexecdir = /usr/lib/httpd/modules
htdocsdir = ${datadir}/htdocs
manualdir = ${datadir}/manual
includedir = /usr/include/httpd
errordir = ${datadir}/error
iconsdir = ${datadir}/icons
sysconfdir = /etc/httpd/conf
installbuilddir = ${datadir}/build
runtimedir = ${localstatedir}/logs
proxycachedir = ${localstatedir}/proxy
other_targets = suexec
progname = httpd
prefix = /etc/httpd
AWK = gawk
CC = gcc
CPP = gcc -E
CXX =
CPPFLAGS =
CFLAGS = -O2 -g
CXXFLAGS =
LTFLAGS = --silent
LDFLAGS =
LT_LDFLAGS = -export-dynamic
SH_LDFLAGS =
HTTPD_LDFLAGS =
UTIL_LDFLAGS =
LIBS =
SSL_LIBS = -lssl -lcrypto
DEFS =
INCLUDES =
NOTEST_CPPFLAGS = -DAP_HAVE_DESIGNATED_INITIALIZER
NOTEST_CFLAGS =
NOTEST_CXXFLAGS =
NOTEST_LDFLAGS =
NOTEST_LIBS =
EXTRA_CPPFLAGS = -DLINUX=2 -D_REENTRANT -D_GNU_SOURCE
EXTRA_CFLAGS = -DNO_DBM_REWRITEMAP
EXTRA_CXXFLAGS =
EXTRA_LDFLAGS = -L/opt/eldk/build/mips-2005-03-06/work/mips_4KC/usr/lib
EXTRA_LIBS = -lz
EXTRA_INCLUDES = -I/opt/eldk/build/mips-2005-03-06/work/mips_4KC/usr/include -I. -I$(srcdir) -I$(top_builddir)/os/$(OS_DIR) -I$(top_srcdir)/os/$(OS_DIR) -I$(top_builddir)/server/mpm/$(MPM_SUBDIR_NAME) -I$(top_srcdir)/server/mpm/$(MPM_SUBDIR_NAME) -I$(top_builddir)/modules/http -I$(top_srcdir)/modules/http -I$(top_builddir)/modules/proxy -I$(top_srcdir)/modules/proxy -I$(top_builddir)/modules/filters -I$(top_srcdir)/modules/filters -I$(top_builddir)/include -I$(top_srcdir)/include -I/usr/include/openssl -I$(top_srcdir)/modules/dav/main
LIBTOOL = /bin/sh /usr/bin/libtool $(LTFLAGS)
SHELL = /bin/sh
MODULE_DIRS = aaa filters loggers metadata proxy ssl http dav/main generators dav/fs mappers
MODULE_CLEANDIRS = arch/win32 cache echo experimental test
PORT = 80
CORE_IMPLIB_FILE =
CORE_IMPLIB =
SH_LIBS =
SH_LIBTOOL = $(LIBTOOL)
MK_IMPLIB =
INSTALL_PROG_FLAGS =
DSO_MODULES = access auth auth_anon auth_dbm auth_digest include deflate log_config env mime_magic cern_meta expires headers usertrack unique_id setenvif proxy proxy_connect proxy_ftp proxy_http ssl mime dav status autoindex asis info suexec cgi cgid dav_fs vhost_alias negotiation dir imap actions speling userdir alias rewrite
