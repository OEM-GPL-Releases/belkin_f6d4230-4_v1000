/* ====================================================================
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Apache" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

#ifndef AP_CONFIG_LAYOUT_H
#define AP_CONFIG_LAYOUT_H

/* Configured Apache directory layout */
#define DEFAULT_PREFIX "/etc/httpd"
#define DEFAULT_EXP_EXEC_PREFIX "/usr"
#define DEFAULT_REL_EXEC_PREFIX "/usr"
#define DEFAULT_EXP_BINDIR "/usr/bin"
#define DEFAULT_REL_BINDIR "/usr/bin"
#define DEFAULT_EXP_SBINDIR "/usr/sbin"
#define DEFAULT_REL_SBINDIR "/usr/sbin"
#define DEFAULT_EXP_LIBEXECDIR "/usr/lib/httpd/modules"
#define DEFAULT_REL_LIBEXECDIR "/usr/lib/httpd/modules"
#define DEFAULT_EXP_MANDIR "/usr/share/man"
#define DEFAULT_REL_MANDIR "/usr/share/man"
#define DEFAULT_EXP_SYSCONFDIR "/etc/httpd/conf"
#define DEFAULT_REL_SYSCONFDIR "conf"
#define DEFAULT_EXP_DATADIR "/var/www"
#define DEFAULT_REL_DATADIR "/var/www"
#define DEFAULT_EXP_INSTALLBUILDDIR "/var/www/build"
#define DEFAULT_REL_INSTALLBUILDDIR "/var/www/build"
#define DEFAULT_EXP_ERRORDIR "/var/www/error"
#define DEFAULT_REL_ERRORDIR "/var/www/error"
#define DEFAULT_EXP_ICONSDIR "/var/www/icons"
#define DEFAULT_REL_ICONSDIR "/var/www/icons"
#define DEFAULT_EXP_HTDOCSDIR "/var/www/htdocs"
#define DEFAULT_REL_HTDOCSDIR "/var/www/htdocs"
#define DEFAULT_EXP_MANUALDIR "/var/www/manual"
#define DEFAULT_REL_MANUALDIR "/var/www/manual"
#define DEFAULT_EXP_CGIDIR "/var/www/cgi-bin"
#define DEFAULT_REL_CGIDIR "/var/www/cgi-bin"
#define DEFAULT_EXP_INCLUDEDIR "/usr/include/httpd"
#define DEFAULT_REL_INCLUDEDIR "/usr/include/httpd"
#define DEFAULT_EXP_LOCALSTATEDIR "/etc/httpd"
#define DEFAULT_REL_LOCALSTATEDIR ""
#define DEFAULT_EXP_RUNTIMEDIR "/etc/httpd/logs"
#define DEFAULT_REL_RUNTIMEDIR "logs"
#define DEFAULT_EXP_LOGFILEDIR "/etc/httpd/logs"
#define DEFAULT_REL_LOGFILEDIR "logs"
#define DEFAULT_EXP_PROXYCACHEDIR "/etc/httpd/proxy"
#define DEFAULT_REL_PROXYCACHEDIR "proxy"

#endif /* AP_CONFIG_LAYOUT_H */
