# Process this file with autoconf to produce a configure script.

AC_INIT(remake,3.80+dbg-0.1,rocky@panix.com)

AM_PATH_LISPDIR

AC_PREREQ(2.54)

AC_REVISION([[$Id: configure.ac,v 1.4 2004/06/12 03:22:41 rockyb Exp $]])

# Autoconf setup
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR(src/vpath.c)
AM_CONFIG_HEADER(config.h)

# Automake setup
AM_INIT_AUTOMAKE
AC_PROG_MAKE_SET

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_CPP
AC_CHECK_PROG(AR, ar, ar, ar)
# Perl is needed for the test suite (only)
AC_CHECK_PROG(PERL, perl, perl, perl)

AC_PATH_PROG(EMACS, emacs, no)
if test x$EMACS = xno ; then
  emacs_lisp=no
else 
  $EMACS -batch -q -no-site-file -eval \
  '(if (not (and (= emacs-major-version 21) (<= emacs-minor-version 3))) (error "This gud is for Emacs 21.0 to 21.3."))'
  if test $? -ne 0 ; then
    emacs_lisp=no
  fi
fi

# Specialized system macros
AC_CANONICAL_HOST
AC_AIX
AC_ISC_POSIX
AC_MINIX

# Enable gettext, in "external" mode.

AM_GNU_GETTEXT_VERSION(0.11.5)
AM_GNU_GETTEXT([external])

# This test must come as early as possible after the compiler configuration
# tests, because the choice of the file model can (in principle) affect
# whether functions and headers are available, whether they work, etc.
AC_SYS_LARGEFILE

# Checks for libraries.
AC_SEARCH_LIBS(getpwnam, [sun])

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_DIRENT
AC_HEADER_STAT
AC_HEADER_TIME
AC_CHECK_HEADERS(locale.h limits.h fcntl.h sys/param.h sys/time.h sys/timeb.h)

AM_PROG_CC_C_O
AM_PROG_CC_STDC
AC_C_CONST
AC_TYPE_SIGNAL
AC_TYPE_UID_T
AC_TYPE_PID_T

# Find some definition for uintmax_t

AC_CHECK_TYPE(uintmax_t,,[
  uintmax_t="unsigned long"
  AC_CHECK_TYPE(unsigned long long,[uintmax_t="unsigned long long"])
  AC_DEFINE_UNQUOTED(uintmax_t,$uintmax_t,
    [Define uintmax_t if not defined in <stdint.h> or <inttypes.h>.])])

# Find out whether our struct stat returns nanosecond resolution timestamps.

AC_STRUCT_ST_MTIM_NSEC
AC_MSG_CHECKING([whether to use high resolution file timestamps])
AC_CACHE_VAL(make_cv_file_timestamp_hi_res, [
  make_cv_file_timestamp_hi_res=no
  if test "$ac_cv_struct_st_mtim_nsec" != no; then
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[
#	if HAVE_INTTYPES_H
#	 include <inttypes.h>
#	endif]],
	              [[char a[0x7fffffff < (uintmax_t)-1 >> 30 ? 1 : -1];]])],
      [make_cv_file_timestamp_hi_res=yes],
      [])
  fi])
AC_MSG_RESULT($make_cv_file_timestamp_hi_res)
if test "$make_cv_file_timestamp_hi_res" = yes; then
  val=1
else
  val=0
fi
AC_DEFINE_UNQUOTED(FILE_TIMESTAMP_HI_RES, $val,
		   [Use high resolution file timestamps if nonzero.])

if test "$make_cv_file_timestamp_hi_res" = yes; then
  # Solaris 2.5.1 needs -lposix4 to get the clock_gettime function.
  # Solaris 7 prefers the library name -lrt to the obsolescent name -lposix4.
  AC_SEARCH_LIBS(clock_gettime, [rt posix4])
  if test "$ac_cv_search_clock_gettime" != no; then
    AC_DEFINE(HAVE_CLOCK_GETTIME, 1,
	      [Define if you have the clock_gettime function.])
  fi
fi


# See if we have a standard version of gettimeofday().  Since actual
# implementations can differ, just make sure we have the most common
# one.
AC_CACHE_CHECK([for standard gettimeofday], ac_cv_func_gettimeofday,
  [ac_cv_func_gettimeofday=no
   AC_RUN_IFELSE([AC_LANG_SOURCE([[#include <sys/time.h>
                  int main ()
	          {
		    struct timeval t; t.tv_sec = -1; t.tv_usec = -1;
		    exit (gettimeofday (&t, 0) != 0
		          || t.tv_sec < 0 || t.tv_usec < 0);
	          }]])],
		  [ac_cv_func_gettimeofday=yes],
		  [ac_cv_func_gettimeofday=no],
		  [ac_cv_func_gettimeofday="no (cross-compiling)"])])
if test "$ac_cv_func_gettimeofday" = yes; then
  AC_DEFINE(HAVE_GETTIMEOFDAY, 1,
	    [Define if you have a standard gettimeofday function])
fi

AC_CHECK_FUNCS(	memcpy memmove strchr strdup mkstemp mktemp fdopen \
	        bsd_signal dup2 getcwd sigsetmask sigaction getgroups \
		seteuid setegid setlinebuf setreuid setregid setvbuf pipe \
		strerror strsignal)

make_FUNC_SETVBUF_REVERSED

# strcoll() is used by the GNU glob library
AC_FUNC_STRCOLL

AC_FUNC_ALLOCA
AC_FUNC_FORK([])
AC_FUNC_VPRINTF
AC_FUNC_CLOSEDIR_VOID

AC_FUNC_GETLOADAVG

# AC_FUNC_GETLOADAVG is documented to set the NLIST_STRUCT value, but it
# doesn't.  So, we will.

if test "$ac_cv_header_nlist_h" = yes; then
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <nlist.h>]],
	[[struct nlist nl;
          nl.n_name = "string";
          return 0;]])],
	[make_cv_nlist_struct=yes],
	[make_cv_nlist_struct=no])
  if test "$make_cv_nlist_struct" = yes; then
    AC_DEFINE(NLIST_STRUCT, 1,
       [Define if struct nlist.n_name is a pointer rather than an array.])
  fi
fi

AC_CHECK_DECLS([sys_siglist])


# Check out the wait reality.
AC_CHECK_HEADERS(sys/wait.h)
AC_CHECK_FUNCS(waitpid wait3)
AC_MSG_CHECKING(for union wait)
AC_CACHE_VAL(make_cv_union_wait, [dnl
    AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <sys/types.h>
#include <sys/wait.h>]],
     [[union wait status; int pid; pid = wait (&status);
#ifdef WEXITSTATUS
/* Some POSIXoid systems have both the new-style macros and the old
   union wait type, and they do not work together.  If union wait
   conflicts with WEXITSTATUS et al, we don't want to use it at all.  */
        if (WEXITSTATUS (status) != 0) pid = -1;
#ifdef WTERMSIG
        /* If we have WEXITSTATUS and WTERMSIG, just use them on ints.  */
        -- blow chunks here --
#endif
#endif
#ifdef HAVE_WAITPID
        /* Make sure union wait works with waitpid.  */
        pid = waitpid (-1, &status, 0);
#endif
      ]])],
    [make_cv_union_wait=yes],
    [make_cv_union_wait=no])])
if test "$make_cv_union_wait" = yes; then
  AC_DEFINE(HAVE_UNION_WAIT, 1,
            [Define this if you have the \`union wait' type in <sys/wait.h>.])
fi
AC_MSG_RESULT($make_cv_union_wait)


#
# Check for readline to see if we can add debugging support.
#
AC_ARG_WITH(readline, 
	    [  --with-readline         enable readline (for debugger)], 
	    enable_readline=$withval, enable_readline=yes)

AC_CHECK_HEADER(readline/readline.h, [], [enable_readline=no])

if test "$enable_readline" = yes ; then 
  AC_CHECK_LIB(readline, readline, 
              [LIBS="$LIBS -lreadline -ltermcap"], 
	      [enable_readline=no], -ltermcap)
  if test "$enable_readline" = yes ; then 
     AC_DEFINE(ENABLE_READLINE, 1, 
     [Define this if you have libreadline. It is needed for the debugger.])
  fi
fi


# See if the user wants to use pmake's "customs" distributed build capability

AC_SUBST(REMOTE) REMOTE=stub
use_customs=false
AC_ARG_WITH(customs,
  AC_HELP_STRING([--with-customs=DIR],
		 [enable remote jobs via Customs--see README.customs]),
  [case $withval in
    n|no) : ;;
    *) make_cppflags="$CPPFLAGS"
       case $withval in
	 y|ye|yes) : ;;
	 *) CPPFLAGS="$CPPFLAGS -I$with_customs/include/customs"
	    make_ldflags="$LDFLAGS -L$with_customs/lib" ;;
       esac
       CF_NETLIBS
       AC_CHECK_HEADER(customs.h,
		       [use_customs=true
		         REMOTE=cstms
			 LIBS="$LIBS -lcustoms" LDFLAGS="$make_ldflags"],
		       [with_customs=no
			 CPPFLAGS="$make_cppflags" make_badcust=yes])
       ;;
  esac])
# Tell automake about this, so it can include the right .c files.
AM_CONDITIONAL(USE_CUSTOMS, test "$use_customs" = true)

# See if we can handle the job server feature, and if the user wants it.

AC_ARG_ENABLE(job-server,
  AC_HELP_STRING([--disable-job-server],
                 [disallow recursive make communication during -jN]),
  [make_cv_job_server="$enableval" user_job_server="$enableval"],
  [make_cv_job_server="yes"])

has_wait_nohang=yes
case "$ac_cv_func_waitpid/$ac_cv_func_wait3" in
  no/no) has_wait_nohang=no ;;
esac

AC_CACHE_CHECK(for SA_RESTART, make_cv_sa_restart, [
  AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <signal.h>]],
      [[return SA_RESTART;]])],
    [make_cv_sa_restart=yes],
    [make_cv_sa_restart=no])])

if test "$make_cv_sa_restart" != no; then
  AC_DEFINE(HAVE_SA_RESTART, 1,
     [Define if <signal.h> defines the SA_RESTART constant.])
fi

# enable make_cv_sa_restart for OS/2 so that the jobserver will be enabled,
# but do it after HAVE_SA_RESTART has been defined.
case "$host_os" in
  os2*) make_cv_sa_restart=yes ;;
esac

case "$ac_cv_func_pipe/$ac_cv_func_sigaction/$make_cv_sa_restart/$has_wait_nohang/$make_cv_job_server" in
  yes/yes/yes/yes/yes)
    AC_DEFINE(MAKE_JOBSERVER, 1,
              [Define this to enable job server support in GNU make.]);;
esac

# Find the SCCS commands, so we can include them in our default rules.

AC_CACHE_CHECK(for location of SCCS get command, make_cv_path_sccs_get, [
if test -f /usr/sccs/get; then
  make_cv_path_sccs_get=/usr/sccs/get
else
  make_cv_path_sccs_get=get
fi])
AC_DEFINE_UNQUOTED(SCCS_GET, ["$make_cv_path_sccs_get"],
	           [Define to the name of the SCCS 'get' command.])

ac_clean_files="$ac_clean_files s.conftest conftoast" # Remove these later.
if ( /usr/sccs/admin -n s.conftest || admin -n s.conftest ) >/dev/null 2>&1 &&
   test -f s.conftest; then
  # We successfully created an SCCS file.
  AC_CACHE_CHECK(if SCCS get command understands -G, make_cv_sys_get_minus_G, [
    if $make_cv_path_sccs_get -Gconftoast s.conftest >/dev/null 2>&1 &&
       test -f conftoast; then
       make_cv_sys_get_minus_G=yes
    else
       make_cv_sys_get_minus_G=no
    fi])
  case "$make_cv_sys_get_minus_G" in
    yes) AC_DEFINE(SCCS_GET_MINUS_G, 1,
           [Define this if the SCCS 'get' command understands the '-G<file>' option.]);;
  esac
fi
rm -f s.conftest conftoast

# Check the system to see if it provides GNU glob.  If not, use our
# local version.

AC_MSG_CHECKING(if system libc has GNU glob)
AC_CACHE_VAL(make_cv_sys_gnu_glob, [
 AC_EGREP_CPP(gnu glob,[
#include <features.h>
#include <glob.h>
#include <fnmatch.h>

#define GLOB_INTERFACE_VERSION 1
#if !defined _LIBC && defined __GNU_LIBRARY__ && __GNU_LIBRARY__ > 1
# include <gnu-versions.h>
# if _GNU_GLOB_INTERFACE_VERSION == GLOB_INTERFACE_VERSION
   gnu glob
# endif
#endif
 ], [AC_MSG_RESULT(yes)
make_cv_sys_gnu_glob=yes], [AC_MSG_RESULT([no; using local copy])
AC_SUBST(GLOBINC) GLOBINC='-I$(top_srcdir)/glob'
AC_SUBST(GLOBLIB) GLOBLIB='$(top_srcdir)/glob/libglob.a'
make_cv_sys_gnu_glob=no])])
# Tell automake about this, so it can build the right .c files.
AM_CONDITIONAL(USE_LOCAL_GLOB, test "$make_cv_sys_gnu_glob" = no)

# Let the makefile know what our build host is

AC_DEFINE_UNQUOTED(MAKE_HOST,"$host",[Build host information.])
MAKE_HOST="$host"
AC_SUBST(MAKE_HOST)

# Include the Maintainer's Makefile section, if it's here.

MAINT_MAKEFILE=/dev/null
if test -r "$srcdir/maintMakefile"; then
  MAINT_MAKEFILE="$srcdir/maintMakefile"
fi
AC_SUBST_FILE(MAINT_MAKEFILE)

# Allow building with dmalloc
AM_WITH_DMALLOC

# Forcibly disable SET_MAKE.  If it's set it breaks things like the test
# scripts, etc.
SET_MAKE=

# Sanity check and inform the user of what we found

case "$make_badcust" in
  yes) echo
       echo "WARNING: --with-customs specified but no customs.h could be found;"
       echo "         disabling Customs support."
       echo ;;
esac

case "$with_customs" in
  ""|n|no|y|ye|yes) ;;
  *) if test -f "$with_customs/lib/libcustoms.a"; then
       :
     else
       echo
       echo "WARNING: '$with_customs/lib' does not appear to contain the"
       echo "         Customs library.  You must build and install Customs"
       echo "         before compiling GNU make."
       echo
     fi ;;
esac

case "$has_wait_nohang" in
  no) echo
      echo "WARNING: Your system has neither waitpid() nor wait3()."
      echo "         Without one of these, signal handling is unreliable."
      echo "         You should be aware that running GNU make with -j"
      echo "         could result in erratic behavior."
      echo ;;
esac

case "$make_cv_job_server/$user_job_server" in
  no/yes) echo
	  echo "WARNING: Make job server requires a POSIX-ish system that"
	  echo "         supports the pipe(), sigaction(), and either"
          echo "         waitpid() or wait3() functions.  Your system doesn't"
	  echo "         appear to provide one or more of those."
	  echo "         Disabling job server support."
          echo ;;
esac


# Specify what files are to be created.
# We only generate the build.sh if we have a build.sh.in; we won't have
# one before we've created a distribution.

AC_CONFIG_FILES([Makefile        \
                 config/Makefile \
		 doc/Makefile    \
		 emacs/Makefile  \
		 glob/Makefile   \
                 po/Makefile.in  \
		 src/Makefile
		 ])

AM_CONDITIONAL(INSTALL_EMACS_LISP, test "x$lispdir" != "x")

if test -f $srcdir/build.sh.in; then
  AC_CONFIG_FILES(build.sh)
fi


# OK, do it!

AC_OUTPUT


dnl Local Variables:
dnl comment-start: "dnl "
dnl comment-end: ""
dnl comment-start-skip: "\\bdnl\\b\\s *"
dnl compile-command: "make configure config.h.in"
dnl End: