dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.
#
# Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010 FSF, Inc.
# This file is part of GNU Make.
# Copyright (C) 2008, 2011 rocky@gnu.org
#
# GNU Make is free software; you can redistribute it and/or modify it under
# the terms of the GNU GPL as published by the Free Software
# Foundation; either version 3 of the License, or (at your option) any
# later version.
#
# GNU Make is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU GPL for more
# details.
#
# You should have received a copy of the GNU GPL along with
# this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([remake],[3.82+dbg0.9],[https://github.com/rocky/remake/issues])dnl

AC_PREREQ([2.69])
AC_REVISION([[$Id: configure.ac,v 1.156 2010/07/28 05:39:50 psmith Exp $]])dnl

# Autoconf setup
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AC_CONFIG_SRCDIR([vpath.c])
AC_CONFIG_HEADERS([config.h])dnl

# Specialized system macros
AC_CANONICAL_TARGET
AC_USE_SYSTEM_EXTENSIONS
AC_SEARCH_LIBS([strerror],[cposix]) dnl# used to be AC\_ISC\_POSIX

# Automake setup
AM_INIT_AUTOMAKE([1.9 dist-bzip2 check-news gnu dejagnu info-in-builddir subdir-objects])
AM_MAINTAINER_MODE
AC_REQUIRE_AUX_FILE([test_driver.pl])dnl
AM_MISSING_PROG([GIT2CL],[git2cl],[${missing_dir}])dnl
AM_MISSING_PROG([TEST_DRIVER_DOT_PL],[test_driver.pl],[${missing_dir}])
if test -z "${datarootdir}"; then
  export datarootdir=${prefix}/share
  AC_SUBST([datarootdir])
fi

# Checks for programs.
if test "x${CC}" = "x"; then
  test -z "${CC}"
  AC_PROG_CC
else
  test -n "${CC}" && export CC
  AC_SUBST([CC])
fi
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_CPP
AC_PROG_LN_S
m4_ifdef([AM_PROG_AR],[
AM_PROG_AR
],[
AC_CHECK_PROG([AR],[ar],[ar],[ar])
])
# Perl is needed for the test suite (only)
AC_CHECK_PROG([PERL],[perl],[perl],[perl])dnl

# Ruby 1.9 and RSPec are needed for the debugger test suite (only)
AC_CHECK_PROG([RUBY],[ruby],[ruby],[none])
AC_CHECK_PROG([RSPEC],[rspec],[rspec],[none])dnl

# Enable gettext, in "external" mode.

AM_GNU_GETTEXT_VERSION([0.21])
AM_GNU_GETTEXT([external])dnl

# This test must come as early as possible after the compiler configuration
# tests, because the choice of the file model can (in principle) affect
# whether functions and headers are available, whether they work, etc.
AC_SYS_LARGEFILE

# Checks for libraries.
AC_CHECK_LIB([c],[printf])
AC_SEARCH_LIBS([getpwnam],[sun])dnl

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STAT
AC_HEADER_STDBOOL dnl# also "_CHECK"s it
AC_HEADER_TIME
AC_CHECK_HEADERS([builtins.h ctype.h errno.h features.h fcntl.h fnmatch.h \
                  gettext.h glob.h gnu-versions.h libintl.h limits.h \
                  locale.h malloc.h malloc/malloc.h netdb.h perror.h \
                  pwd.h setjmp.h signal.h stddef.h stdio.h sys/file.h \
                  sys/param.h sys/resource.h sys/socket.h \
                  sys/time.h sys/timeb.h sys/vfork.h time.h types.h \
                  unixio.h unixlib.h wchar.h wctype.h windows.h])dnl

if test "x${ac_cv_header_inttypes_h}" = "x"; then
  test -z "${ac_cv_header_inttypes_h}"
  AC_CHECK_HEADERS([inttypes.h])
fi
if test "x${ac_cv_header_stdint_h}" = "x"; then
  test -z "${ac_cv_header_stdint_h}"
  AC_CHECK_HEADERS([stdint.h])
fi
if test "x${ac_cv_header_strings_h}" = "x"; then
  test -z "${ac_cv_header_strings_h}"
  AC_CHECK_HEADERS([strings.h])
fi
if test "x${ac_cv_header_unistd_h}" = "x"; then
  test -z "${ac_cv_header_unistd_h}"
  AC_CHECK_HEADERS([unistd.h])
fi

# Set a flag if we have an ANSI C compiler
if test "x${ac_cv_prog_cc_stdc}" != "xno"; then
  AC_DEFINE([HAVE_ANSI_COMPILER],[1],
	    [Define to 1 if your compiler conforms to the ANSI C standard.])
fi


# Determine what kind of variadic function calls we support
AC_CHECK_HEADERS([stdarg.h varargs.h],[break])dnl

# Checks for typedefs, structures, and compiler characteristics.
AM_PROG_CC_C_O
AC_C_BIGENDIAN
AC_C_CONST
AC_C_INLINE
AC_C_PROTOTYPES
dnl# Begin of what used to be AC\_TYPE\_SIGNAL
AC_CACHE_CHECK([return type of signal handlers],[ac_cv_type_signal],[AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([[#include <sys/types.h>
#include <signal.h>
]],
		 [[return *(signal (0, 0)) (0) == 1;]])],
		   [ac_cv_type_signal=int],
		   [ac_cv_type_signal=void])])
AC_DEFINE_UNQUOTED([RETSIGTYPE],[${ac_cv_type_signal}],[Define as the return type of signal handlers
		    (`int' or `void').])
dnl# End of what used to be AC\_TYPE\_SIGNAL
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_UID_T
AC_TYPE_UINT8_T

AC_CHECK_MEMBERS([struct rlimit.rlim_cur, struct rlimit.rlim_max],[],[],[
#if defined(HAVE_SYS_RESOURCE_H)
# include <sys/resource.h>
#else
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "This conftest expects <sys/resource.h> to be included."
# endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* HAVE_SYS_RESOURCE_H */
])dnl

# Find some definition for uintmax_t

AC_CHECK_TYPE([uintmax_t],[],[
  uintmax_t="unsigned long"
  AC_CHECK_TYPE([unsigned long long],[uintmax_t="unsigned long long"])
  AC_DEFINE_UNQUOTED([uintmax_t],[${uintmax_t}],
    [Define uintmax_t if not defined in <stdint.h> or <inttypes.h>.])])dnl

# Find out whether our struct stat returns nanosecond resolution
# timestamps.

AC_STRUCT_ST_MTIM_NSEC
AC_MSG_CHECKING([whether to use high resolution file timestamps])
AC_CACHE_VAL([make_cv_file_timestamp_hi_res],[
  make_cv_file_timestamp_hi_res=no
  if test "${ac_cv_struct_st_mtim_nsec}" != no; then
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#	if defined(HAVE_INTTYPES_H)
#	 include <inttypes.h>
#	else
#	 if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#	  warning "This conftest expects <inttypes.h> to be included."
#	 endif /* __GNUC__ && !__STRICT_ANSI__ */
#	endif /* HAVE_INTTYPES_H */
	]],[[char a[0x7fffffff < (uintmax_t)-1 >> 30 ? 1 : -1];]])],
      [make_cv_file_timestamp_hi_res=yes],
      [])
  fi])
AC_MSG_RESULT([${make_cv_file_timestamp_hi_res}])
if test "${make_cv_file_timestamp_hi_res}" = yes; then
  val=1
else
  val=0
fi
AC_DEFINE_UNQUOTED([FILE_TIMESTAMP_HI_RES],[${val}],
		   [Use high resolution file timestamps if nonzero.])dnl

if test "${make_cv_file_timestamp_hi_res}" = yes; then
  # Solaris 2.5.1 needs -lposix4 to get the clock_gettime function.
  # Solaris 7 prefers the library name -lrt to the obsolete name -lposix4.
  AC_SEARCH_LIBS([clock_gettime],[rt posix4])
  if test "${ac_cv_search_clock_gettime}" != no; then
    AC_DEFINE([HAVE_CLOCK_GETTIME],[1],
	      [Define to 1 if you have the clock_gettime function.])
  fi
fi

# Check for DOS-style pathnames.
pds_AC_DOS_PATHS

# See if we have a standard version of gettimeofday(). Since actual
# implementations can differ, just make sure we have the most common
# one.
AC_CACHE_CHECK([for standard gettimeofday],[ac_cv_func_gettimeofday],
  [ac_cv_func_gettimeofday=no
   AC_RUN_IFELSE([AC_LANG_SOURCE([[#include <sys/time.h>
                  int main(void)
	          {
		    struct timeval t; t.tv_sec = -1; t.tv_usec = -1;
		    exit (gettimeofday (&t, 0) != 0
		          || t.tv_sec < 0 || t.tv_usec < 0);
	          }]])],
		  [ac_cv_func_gettimeofday=yes],
		  [ac_cv_func_gettimeofday=no],
		  [ac_cv_func_gettimeofday="no (cross-compiling)"])])
if test "x${ac_cv_func_gettimeofday}" = "xyes"; then
  AC_DEFINE([HAVE_GETTIMEOFDAY],[1],
	    [Define to 1 if you have a standard gettimeofday function])
fi

AC_CHECK_FUNCS([alarm atexit bzero clock_gettime dup2 fdopen fileno \
                getcwd getgroups gethostbyaddr getrlimit gettimeofday \
                inet_ntoa memmove mempcpy memset mkstemp mktemp pathconf \
                pipe putenv qsort readlink realpath setegid seteuid \
                setlinebuf setregid setreuid setrlimit setvbuf sigaction \
                sigsetmask strchr strdup strerror strndup strpbrk \
                strrchr strsignal strstr strtol])
AC_CHECK_FUNCS_ONCE([__alloca __iswctype __btowc __stat])dnl

# We need to check declarations, not just existence, because on Tru64 this
# function is not declared without special flags, which themselves cause
# other problems. We will just use our own.
AC_CHECK_DECLS([bsd_signal],[],[],[[#include <signal.h>]])dnl

AC_FUNC_SETVBUF_REVERSED

if test "x${ac_cv_func_setlocale}" = "x"; then
  test -z "${ac_cv_func_setlocale}"
  AC_CHECK_FUNCS([setlocale])
fi

# Rumor has it that strcasecmp lives in -lresolv on some odd systems.
# It does NOT hurt much to use our own if we cannot find it so I do NOT
# make the effort here.
AC_CHECK_FUNCS([strcasecmp strncasecmp strcmpi strncmpi stricmp strnicmp])dnl

# strcoll() is used by the GNU glob library
AC_FUNC_STRCOLL

AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK([])
AC_FUNC_LSTAT dnl# also checks whether it "_FOLLOWS_SLASHED_SYMLINK"
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_FUNC_STRERROR_R
AC_FUNC_VPRINTF
AC_FUNC_WAIT3
AC_FUNC_CLOSEDIR_VOID

if test "x${ac_cv_func_stat}" = "x"; then
  test -z "${ac_cv_func_stat}" || unset ac_cv_func_stat
  AC_CHECK_FUNCS([stat])
fi

AC_FUNC_GETLOADAVG

# AC_FUNC_GETLOADAVG is documented to set the NLIST_STRUCT value, but it
# does NOT do so. So, we will.
AC_CHECK_HEADERS_ONCE([nlist.h])
if test "${ac_cv_header_nlist_h}" = yes; then
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <nlist.h>]],
	[[struct nlist nl;
          nl.n_name = "string";
          return 0;]])],
	[make_cv_nlist_struct=yes],
	[make_cv_nlist_struct=no])
  if test "${make_cv_nlist_struct}" = yes; then
    AC_DEFINE([NLIST_STRUCT],[1],
       [Define to 1 if struct nlist.n_name is a pointer rather than an array.])
  fi
fi

AC_CHECK_DECLS([sys_siglist, _sys_siglist, __sys_siglist],[],[],
  [AC_INCLUDES_DEFAULT
#include <signal.h>
/* NetBSD declares sys_siglist in unistd.h.  */
#if defined(HAVE_UNISTD_H)
# include <unistd.h>
#else
# if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#  warning "This conftest for sys_siglist expects <unistd.h> to be included."
# endif /* __GNUC__ && !__STRICT_ANSI__ */
#endif /* HAVE_UNISTD_H */
])dnl


# Check out the wait reality.
AC_CHECK_HEADERS([sys/wait.h],[],[],[[#include <sys/types.h>]])
AC_CHECK_FUNCS([waitpid wait3])
AC_MSG_CHECKING([for union wait])
AC_CACHE_VAL([make_cv_union_wait],[dnl
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <sys/types.h>
#include <sys/wait.h>]],
     [[union wait status; int pid; pid = wait (&status);
#ifdef WEXITSTATUS
/* Some POSIXoid systems have both the new-style macros and the old
   union wait type, and they do not work together. If union wait
   conflicts with WEXITSTATUS et al, we do NOT want to use it at all.  */
        if (WEXITSTATUS (status) != 0) pid = -1;
# ifdef WTERMSIG
        /* If we have WEXITSTATUS and WTERMSIG, just use them on ints.  */
        -- blow chunks here --
# endif /* WTERMSIG */
#endif /* WEXITSTATUS */
#ifdef HAVE_WAITPID
        /* Make sure union wait works with waitpid.  */
        pid = waitpid (-1, &status, 0);
#endif /* HAVE_WAITPID */
      ]])],
    [make_cv_union_wait=yes],
    [make_cv_union_wait=no])])
if test "${make_cv_union_wait}" = yes; then
  AC_DEFINE([HAVE_UNION_WAIT],[1],
            [Define to 1 if you have the \`union wait' type in <sys/wait.h>.])
fi
AC_MSG_RESULT([${make_cv_union_wait}])dnl


AC_ARG_WITH([make_name],
[AS_HELP_STRING([--with-make-name],
                [name to use as the program name (default remake)])],
[make_name="${withval}"],[make_name="remake"])
MAKE_NAME="${make_name}"
AC_SUBST([MAKE_NAME])
MAKE_NAME_UPPER=`echo ${make_name} | tr a-z A-Z`
AC_SUBST([MAKE_NAME_UPPER])
if test "x${make_name}" != "x"; then
  test -n "${make_name}" && echo "make_name is ${make_name}"
  AC_DEFINE_UNQUOTED([program_name],["${make_name}"],[
The calling program should define program_name and set it to the name
of the executing program.])
else
  test -z "${make_name}"
  AC_MSG_WARN([make_name is empty])
fi

AC_ARG_WITH([default_shell],
[AS_HELP_STRING([--with-default-shell],[program to use for SHELL])],
[default_shell="${withval}"],[default_shell="/bin/sh"])
DEFAULT_SHELL="${default_shell}"

AC_ARG_WITH([shell_trace],
[AS_HELP_STRING([--with-shell-trace],
                [option to pass to shell to have it trace commands (default -x)])],
[shell_trace="${withval}"],[shell_trace="-x"])dnl

## Set OS-specific default shell.
case ${host_os} in
    cygwin*|mingw*) ;;
    solaris*)
      ## The System V Release 4 /bin/sh cannot handle
      ## -x -c in that order.
      for sh in /bin/bash /usr/xpg4/bin/sh; do
        if test -x "${sh}" ; then
          default_shell=${sh}
	  break
        fi
      done
      ;;

     *) ;;
esac

AC_MSG_CHECKING([if ${default_shell} can be used to trace commands using ${shell_trace}])
sh_is_ok=`${default_shell} ${shell_trace} -c ':' 2>&1`
if test "+ :" != "${sh_is_ok}" ; then
   AC_MSG_RESULT([no])
   AC_MSG_WARN([Disabling shell tracing. Run again using --with-default_shell])
   AC_MSG_WARN([or using --with-shell_trace if you know of a shell that])
   AC_MSG_WARN([supports tracing with *sh* *shell_option* -c (in that order)"])
else
   AC_MSG_RESULT([yes])
fi

AC_DEFINE_UNQUOTED([SHELL_TRACE],["${shell_trace}"], 
     [Define this to be what you need to add to turn on shell tracing])dnl

AC_DEFINE_UNQUOTED([DEFAULT_SHELL],["${default_shell}"],
     [Define this to the default to be used $(SHELL)])dnl

#
# Check for readline to see if we can add debugging support.
#
AC_CHECK_HEADER([readline/readline.h],[have_readline=yes], [have_readline=no])

if test "${have_readline}" != yes; then
   AC_MSG_ERROR([GNU Readline and its headers files are needed. See http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html])
fi

VL_LIB_READLINE
AC_MSG_CHECKING([for tilde_expand() in <readline/readline.h>])
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <stdio.h>
#include <readline/readline.h>

int main(int argc, char **argv) {
  char *s = tilde_expand ("~");
  return 0;
}]])],[AC_MSG_RESULT([yes]); ac_have_tilde_expand=yes; 
     AC_DEFINE([HAVE_TILDE_EXPAND],[1], 
     [Define this to 1 if <readline/readline.h> defines tilde_expand()])],
     [AC_MSG_RESULT([no]); ac_have_tilde_expand=no],
     [AC_MSG_RESULT([no]); ac_have_tilde_expand=no])dnl

AC_CHECK_LIB([readline],[readline])
AC_MSG_CHECKING([for history_list() in <readline/readline.h>])
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv) {
  HIST_ENTRY **hist_list;

      rl_initialize ();
   hist_list = history_list();
  return 0;
}]])],[AC_MSG_RESULT([yes]); ac_have_history_list=yes; 
     AC_DEFINE([HAVE_HISTORY_LIST],[1], 
     [Define this to 1 if <readline/readline.h> defines history_list()])],
     [AC_MSG_RESULT([no]); ac_have_history_list=no],
     [AC_MSG_RESULT([no]); ac_have_history_list=no])dnl

if test "x${ac_have_history_list}" = "xno"; then
  AC_CHECK_HEADERS([readline/history.h])
fi

AC_SUBST([HAVE_READLINE])
REMAKE_SOURCE_PATH="`pwd`"
AC_DEFINE_UNQUOTED([REMAKE_SOURCE_PATH],["${REMAKE_SOURCE_PATH}"],
	[Full path to remake top_sourcedir.])
AC_SUBST([REMAKE_SOURCE_PATH])dnl

# If we are building on Windows/DOS/OS/2, add support for DOS drive specs.
if test "${PATH_SEPARATOR}" = ';'; then
  AC_DEFINE([HAVE_DOS_PATHS],[1],
            [Define this if your system requires backslashes or drive specs in pathnames.])
fi


# See if user wants to use pmake's "customs" distributed build capability

AC_SUBST([REMOTE]) REMOTE=stub
use_customs=false
AC_ARG_WITH([customs],
  [AS_HELP_STRING([--with-customs=DIR],
		 [enable remote jobs via Customs--see README.customs])],
  [case ${withval} in
    n|no) : ;;
    *) make_cppflags="${CPPFLAGS}"
       case ${withval} in
	 y|ye|yes) : ;;
	 *) CPPFLAGS="${CPPFLAGS} -I${with_customs}/include/customs"
	    make_ldflags="${LDFLAGS} -L${with_customs}/lib" ;;
       esac
       CF_NETLIBS
       AC_CHECK_HEADER([customs.h],
		       [use_customs=true
		         REMOTE=cstms
			 LIBS="${LIBS} -lcustoms" LDFLAGS="${make_ldflags}"],
		       [with_customs=no
			 CPPFLAGS="${make_cppflags}" make_badcust=yes])
       ;;
  esac])
# Tell automake about this, so it can include the right .c files.
AM_CONDITIONAL([USE_CUSTOMS],[test "${use_customs}" = true])dnl

# See if the user asked to handle case insensitive file systems.

AH_TEMPLATE([HAVE_CASE_INSENSITIVE_FS],[Use case insensitive file names])
AC_ARG_ENABLE([case-insensitive-file-system],
  [AS_HELP_STRING([--enable-case-insensitive-file-system],[assume file systems are case insensitive])],
  [case ${enableval} in
     yes) AC_DEFINE([HAVE_CASE_INSENSITIVE_FS],[1],[Define to 1 to use case insensitive file names]) ;;
   esac])dnl

# See if we can handle the job server feature, and if the user wants it.

AC_ARG_ENABLE([job-server],
  [AS_HELP_STRING([--disable-job-server],
                 [disallow recursive make communication during -jN])],
  [make_cv_job_server="${enableval}" user_job_server="${enableval}"],
  [make_cv_job_server="yes"])dnl

has_wait_nohang=yes
case "${ac_cv_func_waitpid}/${ac_cv_func_wait3}" in
  no/no) has_wait_nohang=no ;;
esac

AC_CACHE_CHECK([for SA_RESTART],[make_cv_sa_restart],[
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <signal.h>]],
      [[return SA_RESTART;]])],
    [make_cv_sa_restart=yes],
    [make_cv_sa_restart=no])])dnl

if test "${make_cv_sa_restart}" != no; then
  AC_DEFINE([HAVE_SA_RESTART],[1],
     [Define to 1 if <signal.h> defines the SA_RESTART constant.])
fi

# enable make_cv_sa_restart for OS/2 so that the jobserver will be enabled,
# but do it after HAVE_SA_RESTART has been defined.
case "${host_os}" in
  os2*) make_cv_sa_restart=yes ;;
esac

case "${ac_cv_func_pipe}/${ac_cv_func_sigaction}/${make_cv_sa_restart}/${has_wait_nohang}/${make_cv_job_server}" in
  yes/yes/yes/yes/yes)
    AC_DEFINE([MAKE_JOBSERVER],[1],
              [Define to 1 to enable job server support in GNU make.]);;
esac

# if we have both lstat() and readlink() then we can support symlink
# timechecks.
case "${ac_cv_func_lstat}/${ac_cv_func_readlink}" in
  yes/yes)
    AC_DEFINE([MAKE_SYMLINKS],[1],
              [Define to 1 to enable symbolic link timestamp checking.]);;
esac

# Find the SCCS commands, so we can include them in our default rules.

AC_CACHE_CHECK([for location of SCCS get command],[make_cv_path_sccs_get],[
if test -f /usr/sccs/get; then
  make_cv_path_sccs_get=/usr/sccs/get
else
  make_cv_path_sccs_get=get
fi])
AC_DEFINE_UNQUOTED([SCCS_GET],["${make_cv_path_sccs_get}"],
	           [Define to the name of the SCCS 'get' command.])dnl

ac_clean_files="${ac_clean_files} s.conftest conftoast" # Remove these later.
if ( /usr/sccs/admin -n s.conftest || admin -n s.conftest ) >/dev/null 2>&1 &&
   test -f s.conftest; then
  # We successfully created an SCCS file.
  AC_CACHE_CHECK([if SCCS get command understands -G],[make_cv_sys_get_minus_G],[
    if ${make_cv_path_sccs_get} -Gconftoast s.conftest >/dev/null 2>&1 &&
       test -f conftoast; then
       make_cv_sys_get_minus_G=yes
    else
       make_cv_sys_get_minus_G=no
    fi])
  case "${make_cv_sys_get_minus_G}" in
    yes) AC_DEFINE([SCCS_GET_MINUS_G],[1],
           [Define to 1 if the SCCS 'get' command understands the '-G<file>' option.]);;
  esac
fi
rm -f s.conftest conftoast

# Check the system to see if it provides GNU glob.  If not, use our
# local version.
AC_MSG_CHECKING([if system libc has GNU glob])
AC_CACHE_VAL([make_cv_sys_gnu_glob],[
 AC_EGREP_CPP([gnu glob],[
#include <features.h>
#include <glob.h>
#include <fnmatch.h>

#define GLOB_INTERFACE_VERSION 1
#if !defined _LIBC && defined __GNU_LIBRARY__ && __GNU_LIBRARY__ > 1
# include <gnu-versions.h>
# if _GNU_GLOB_INTERFACE_VERSION == GLOB_INTERFACE_VERSION
   gnu glob
# endif /* _GNU_GLOB == GLOB */
#endif /* !_LIBC && __GNU_LIBRARY__ > 1 */
 ],[AC_MSG_RESULT([yes])
make_cv_sys_gnu_glob=yes],[AC_MSG_RESULT([no; using local copy])
make_cv_sys_gnu_glob=no])])
if test "${make_cv_sys_gnu_glob}" = no; then
  GLOBINC='-I$(srcdir)/glob'
  GLOBLIB=glob/libglob.a
fi
AC_SUBST([GLOBINC])dnl
AC_SUBST([GLOBLIB])dnl

# Tell automake about this, so it can build the right .c files.
AM_CONDITIONAL([USE_LOCAL_GLOB],[test "${make_cv_sys_gnu_glob}" = no])dnl

# Let the makefile know what our build host is

AC_DEFINE_UNQUOTED([MAKE_HOST],["${host}"],[Build host information.])
MAKE_HOST="${host}"
AC_SUBST([MAKE_HOST])dnl

w32_target_env=no
AM_CONDITIONAL([WINDOWSENV],[false])dnl

case "${host}" in
  *-*-mingw32)
    AM_CONDITIONAL([WINDOWSENV],[true])
    w32_target_env=yes
    AC_DEFINE([WINDOWS32],[1],[Use platform specific coding])
    AC_DEFINE([HAVE_DOS_PATHS],[1],[Use platform specific coding])
    ;;
esac

AC_DEFINE_UNQUOTED([PATH_SEPARATOR_CHAR],['${PATH_SEPARATOR}'],
           [Define to the character that separates directories in PATH.])dnl

# Include the Maintainer's Makefile section, if it is here.

MAINT_MAKEFILE=/dev/null
if test -r "${srcdir}/maintMakefile"; then
  MAINT_MAKEFILE="${srcdir}/maintMakefile"
fi
AC_SUBST_FILE([MAINT_MAKEFILE])dnl

# Allow building with dmalloc
AM_WITH_DMALLOC

# Forcibly disable SET_MAKE. If it is set it breaks things like the test
# scripts, etc.
SET_MAKE=""

# Sanity check and inform the user of what we found

case "${make_badcust}" in
  yes) echo ""
       echo "WARNING: --with-customs used but no customs.h could be found;"
       echo "         disabling Customs support."
       echo "" ;;
esac

case "${with_customs}" in
  ""|n|no|y|ye|yes) ;;
  *) if test -f "${with_customs}/lib/libcustoms.a"; then
       echo "${with_customs}/lib/libcustoms.a found."
       stat "${with_customs}/lib/libcustoms.a"
     else
       echo ""
       echo "WARNING: '${with_customs}/lib' does not appear to contain the"
       echo "         Customs library. You must build and install Customs"
       echo "         before compiling GNU make."
       echo ""
     fi ;;
esac

case "${has_wait_nohang}" in
  no) echo ""
      echo "WARNING: Your system has neither waitpid() nor wait3()."
      echo "         Without one of these, signal handling is unreliable."
      echo "         You should be aware that running GNU make with -j"
      echo "         could result in erratic behavior."
      echo "" ;;
esac

case "${make_cv_job_server}/${user_job_server}" in
  no/yes) echo ""
          echo "WARNING: Make job server requires a POSIX-ish system that"
          echo "         supports the pipe(), sigaction(), and either"
          echo "         waitpid() or wait3() funcs. Your system does not"
          echo "         appear to provide one or more of those."
          echo "         Disabling job server support."
          echo "" ;;
esac


# Specify what files are to be created.
AC_CONFIG_FILES([Makefile glob/Makefile po/Makefile.in config/Makefile \
                 doc/Makefile w32/Makefile])dnl

# OK, do it!

AC_OUTPUT

# We only generate the build.sh if we have a build.sh.in; we will NOT have
# one before we have created a distribution.
if test -f "${srcdir}/build.sh.in"; then
  ./config.status --file build.sh
  chmod +x build.sh
fi

AC_MSG_NOTICE([Will install the 'make' binary under the name: ${make_name}])


dnl# Local Variables:
dnl# comment-start: "dnl "
dnl# comment-end: ""
dnl# comment-start-skip: "\\bdnl\\b\\s *"
dnl# compile-command: "make configure config.h.in"
dnl# End:
