# -*-Makefile-*-, or close enough
# Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
# 2010 Free Software Foundation, Inc.
# This file is part of GNU Make.
#
# GNU Make is free software; you can redistribute it and/or modify it under
# the terms of the GNU GPL as published by the Free Software
# Foundation; either ver. 3 of the License, or (at your option) any later
# version.
#
# GNUMake is distributed in the hope that it will be useful, but W/OUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License with
# this program.  If not, see <http://www.gnu.org/licenses/>.

TEXI2HTML = texi2html
TEXI2HTML_FLAGS = -split_chapter
MY_TEXI2PDF = texi2dvi --pdf

EXTRA_DIST = test1.mk test2.mk version-remake.texi

FAKE_info_old_TEXINFOS_COMMENTED_OUT = make.texi remake.texi
info_TEXINFOS =	remake.texi
make_TEXINFOS = fdl.texi make-stds.texi

MOSTLYCLEANFILES = make.tgs make.pdf make.html remake.cps rmake.kys remake.html remake.fns remake.ps.gz remake.pdf 

CLEANFILES = make*.html make*.info remake.html remake*.info

## ----------------------------- ##
## Other documentation formats.  ##
## ----------------------------- ##

html-local: remake_1.html

remake_1.html: $(info_TEXINFOS) $(make_TEXINFOS)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) $(srcdir)/remake.texi --output remake.html

.PHONY: html-local
