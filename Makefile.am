# This is a -*-Makefile-*-, or close enough
#
# Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
# 2007, 2008, 2009, 2010 Free Software Foundation, Inc.
# This file is part of GNU Make.
#
# GNU Make is free software; you can redistribute it and/or modify it under
# the terms of the GNU GPL as published by the Free Software
# Foundation; either ver. 3 of the License, or (at your option) any later
# version.
#
# GNUMake is distributed in the hope that it can be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU GPL along with
# this program. If not, see <http://www.gnu.org/licenses/>.

AUTOMAKE_OPTIONS = 1.8 dist-bzip2 check-news gnu dejagnu subdir-objects
ACLOCAL_AMFLAGS	=  -I config --install

transform = s,make,@MAKE_NAME@,

MAKE_HOST =	@MAKE_HOST@

# Only process if target is MS-Windows
if WINDOWSENV
  MAYBE_W32 =	w32
  W32INC =	-I $(top_srcdir)/w32/include
  W32LIB =	-Lw32 -lw32
endif

SUBDIRS =	glob config po doc $(MAYBE_W32)

bin_PROGRAMS =	make

# PROGRAMS = @MAKE_NAME@$(EXEEXT) $(bin_PROGRAMS)

if USE_CUSTOMS
  remote =	remote-cstms.c
else
  remote =	remote-stub.c
endif

DEBUGGER_SRC = 	\
		debugger/break.c \
		debugger/cmd.c 	\
		debugger/fns.c 	\
		debugger/file2line.c 	\
		debugger/msg.c 	\
		debugger/stack.c

DEBUGGER_H = \
		debugger/break.h 		\
		debugger/cmd.h 			\
		debugger/fns.h 			\
		debugger/msg.h 			\
		debugger/command/break.h 	\
		debugger/command/chdir.h  	\
		debugger/command/comment.h 	\
		debugger/command/continue.h	\
		debugger/command/delete.h 	\
		debugger/command/down.h 	\
		debugger/command/edit.h 	\
		debugger/command/eval.h 	\
		debugger/command/expand.h	\
		debugger/command/finish.h	\
		debugger/command/frame.h	\
		debugger/command/help.h		\
		debugger/command/info.h		\
		debugger/command/list.h		\
		debugger/command/next.h		\
		debugger/command/print.h	\
		debugger/command/pwd.h		\
		debugger/command/quit.h		\
		debugger/command/run.h		\
		debugger/command/set.h		\
		debugger/command/setq.h		\
		debugger/command/shell.h	\
		debugger/command/show.h		\
		debugger/command/skip.h		\
		debugger/command/source.h	\
		debugger/command/step.h		\
		debugger/command/target.h	\
		debugger/command/up.h		\
		debugger/command/where.h	\
		debugger/command/write.h	\
		debugger/file2line.h 	        \
		debugger/fns.h 			\
		debugger/info.h			\
		debugger/stack.h		\
		debugger/subcmd.h

make_SOURCES =	ar.c arscan.c commands.c default.c dir.c expand.c file.c \
		function.c getopt.c getopt1.c implicit.c job.c main.c \
		misc.c read.c remake.c $(remote) rule.c signame.c \
		strcache.c variable.c version.c vpath.c hash.c \
		buildargv.c debug.c print.c trace.c \
	 	$(DEBUGGER_SRC)

EXTRA_make_SOURCES = vmsjobs.c remote-stub.c remote-cstms.c

noinst_HEADERS = commands.h dep.h filedef.h job.h main.h make.h rule.h \
	        variable.h implicit.h \
		debug.h getopt.h gettext.h hash.h implicit.h \
		buildargv.h expand.h file.h function.h read.h vpath.h \
		print.h trace.h types.h \
		$(DEBUGGER_H)

make_LDADD =	@LIBOBJS@ @ALLOCA@ $(GLOBLIB) @GETLOADAVG_LIBS@ @LIBINTL@
# Only process if target is MS-Windows
if WINDOWSENV
    make_LDADD += $(W32LIB)
endif

man_MANS =	make.1

DEFS =		-DLOCALEDIR=\"$(localedir)\" -DLIBDIR=\"$(libdir)\" -DINCLUDEDIR=\"$(includedir)\" @DEFS@

AM_CPPFLAGS =	$(GLOBINC)
# Only process if target is MS-Windows
if WINDOWSENV
    AM_CPPFLAGS +=	$(W32INC)
endif


# Extra stuff to include in the distribution.

EXTRA_DIST =	README build.sh.in $(man_MANS) \
		README.customs  \
		SCOPTIONS SMakefile \
		 make.lnk amiga.c amiga.h \
		NMakefile  \
		make_msvc_net2003.sln make_msvc_net2003.vcproj \
		vmsdir.h vmsfunctions.c vmsify.c \
	        debugger/Makefile \
		NEWS.remake README.remake REMAKE.todo Rakefile

# This is built during configure, but behind configure's back

DISTCLEANFILES = build.sh *.dSYM autoscan.log *~ config/*~ po/*~

MOSTLYCLEANFILES = *.orig *.rej @MAKE_NAME@

# Forward targets

html-local:
	cd doc && $(MAKE) $(AM_MAKEFLAGS) $@

make$(EXEEXT): $(make_OBJECTS) $(make_DEPENDENCIES) 
	@rm -f make$(EXEEXT) @MAKE_NAME@$(EXEEXT)
	$(LINK) $(make_OBJECTS) $(make_LDADD) $(LIBS)
	$(LN_S) make$(EXEEXT) @MAKE_NAME@$(EXEEXT)

.PHONY: html-local

# --------------- Internationalization Section

localedir =	$(datadir)/locale

# --------------- Local INSTALL Section

# If necessary, change the gid of the app and turn on the setgid flag.
#

# Whether or not make needs to be installed setgid.
# The value should be either `true' or `false'.
# On many systems, the getloadavg function (used to implement the `-l'
# switch) will not work unless make is installed setgid kmem.
#
inst_setgid = @NEED_SETGID@

# Install make setgid to this group so it can get the load average.
#
inst_group = @KMEM_GROUP@

#: install executables (e.g. remake)
install-exec-local:
	@if $(inst_setgid); then \
	   app=$(DESTDIR)$(bindir)/`echo $(bin_PROGRAMS)|sed '$(transform)'`; \
	   if chgrp $(inst_group) $$app && chmod g+s $$app; then \
	     echo "chgrp $(inst_group) $$app && chmod g+s $$app"; \
	   else \
	     echo "$$app needs to be owned by group $(inst_group) and setgid;"; \
	     echo "otherwise the \`-l' option will probably not work."; \
	     echo "You may need special privileges to complete the installation"; \
	     echo "of $$app."; \
	   fi; \
	 else true; fi

# --------------- Local DIST Section

#: Include the entire w32 and tests subdirectories in distribution
dist-hook:
	(cd $(srcdir); \
	 sub=`find w32 tests -follow \( -name CVS -prune -o -name .cvsignore -o -name work -prune \) -o \( -name \*.orig -o -name \*.rej -o -name \*~ -prune \) -o -type f -print`; \
	 tar chf - $$sub) \
	| (cd $(distdir); tar xfBp -)

distclean-local:
	-rm -rfv autom4te.cache || rmdir autom4te.cache
	-rm -rfv .deps || rmdir .deps
	-rm -rfv debugger/.deps || rmdir debugger/.deps
	-rm -rfv glob/.deps || rmdir glob/.deps
	-rm -rfv w32/.deps || rmdir w32/.deps
	-rm -rfv w32/subproc/.deps || rmdir w32/subproc/.deps
	-rm -rfv *.dSYM || rmdir *.dSYM


# --------------- Local CHECK Section

check-local: check-regression check-loadavg
	@banner=" Regression PASSED: GNU Make $(VERSION) ($(MAKE_HOST)) built with $(CC) "; \
	dashes=`echo "$$banner" | sed s/./=/g`; \
	echo ""; \
	echo "$$dashes"; \
	echo "$$banner"; \
	echo "$$dashes"; \
	echo ""

.PHONY: check-loadavg check-regression

#: Check internal load average routine against 'uptime'
check-loadavg: loadavg$(EXEEXT)
	@echo The system uptime program believes the load average to be:
	-uptime
	@echo The GNU load average checking code thinks:
	-./loadavg$(EXEEXT)

# FIXME: does NOT work.
##: Run remake-specific tests using Ruby rspec
check-rspec-broken: 
	$(SHELL) -c 'ruby tests/spec/run-tests.rb' || \
	(echo "failed" >&2 && $(SHELL) -c 'ruby -cwv tests/spec/run-tests.rb')
.PHONY: check-rspec-broken

# The loadavg function is invoked during "make check" to test getloadavg.
check_PROGRAMS = loadavg
nodist_loadavg_SOURCES = getloadavg.c
loadavg_CPPFLAGS = -DTEST
loadavg_LDADD = @GETLOADAVG_LIBS@

# > check-regression
#
# Look for the make test suite, and run it if found and we can find perl.
# If we are building out-of-tree, we use symlinks to make a local copy of
# the test suite. Unfortunately the test suite itself is NOT localized yet.
#
MAKETESTFLAGS =

#: run regression tests in tests/scripts
check-regression:
	@if test -f "$(srcdir)/tests/run_make_tests"; then \
	  if $(PERL) -v >/dev/null 2>&1; then \
	    case `cd $(srcdir); pwd` in \
	      `pwd`) echo "already in srcdir; skipping symlinks" ;; \
	      *) test -d tests || mkdir tests; \
		 rm -f srctests; \
		 if ln -s "$(srcdir)/tests" srctests; then \
		   for f in run_make_tests run_make_tests.pl test_driver.pl scripts; do \
		     rm -f tests/$$f; ln -s ../srctests/$$f tests; \
		   done; \
		 elif test -e srctests; then stat srctests; \
		 else echo "nothing to do for srctests"; fi ;; \
	    esac; \
	    echo "cd tests && $(PERL) ./run_make_tests.pl -make ../make$(EXEEXT) $(MAKETESTFLAGS)"; \
	    cd tests && $(PERL) ./run_make_tests.pl -make ../make$(EXEEXT) $(MAKETESTFLAGS); \
	  else \
	    echo "Cannot find a working Perl ($(PERL)); the test suite requires Perl."; \
	  fi; \
	 else \
	  echo "Cannot find the GNU Make test suite ($(srcdir)/tests)."; \
	 fi

%.short:
	$(MAKE) $(@:.short=) 2>&1 >/dev/null

# --------------- Maintainer's Section

# Tell automake that I have NOT forgotten about this file and it will be
# created before we build a distribution (see maintMakefile in the CVS
# distribution).

if MAINTAINER_MODE

#: create ChangeLog for distribution from 'git log'
ChangeLog:
	git log --pretty --numstat --summary | $(GIT2CL) > $@

# another way of doing it:
PHONY: update-ChangeLog
update-ChangeLog:
	    if test -d $(srcdir)/.git; then                         \
	       $(srcdir)/config/gitlog-to-changelog                 \
	          --format='%s%n%n%b%n' --no-cluster                \
	          --strip-tab --strip-cherry-pick                   \
	          -- $$(cat $(srcdir)/.last-cl-gen)..               \
	        >ChangeLog.tmp                                      \
	      && git rev-list -n 1 HEAD >.last-cl-gen.tmp           \
	      && (echo; cat $(srcdir)/ChangeLog) >>ChangeLog.tmp    \
	      && mv -f ChangeLog.tmp $(srcdir)/ChangeLog            \
	      && mv -f .last-cl-gen.tmp $(srcdir)/.last-cl-gen      \
	      && rm -f ChangeLog.tmp;                               \
	    fi

EXTRA_DIST += .last-cl-gen

endif

README:

## from the maintMakefile in this same directory:
@MAINT_MAKEFILE@
