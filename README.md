[![Build Status](https://travis-ci.org/cooljeanius/remake.png)](https://travis-ci.org/cooljeanius/remake)

Patched GNU Make 3.82 sources to add improved error reporting, tracing,
and a debugger.

Although there is a full debugger here, most of the time I can get by
using no options since normal output is a little more verbose and detailed.
When that is not enough, I use the --trace or -x option, e.g

    remake -x <other make options>

But if you want the full debugger, use --debugger or -X:

    remake -X <other make options>

Also, if there is project and you want a list of "interesting" targets, try:

    remake --tasks

If the project has commented its Makefile using remake-friendly comments you may get output like this:

    ChangeLog	# create ChangeLog fom git log via git2cl
    build	# Do what it takes to build software locally
    check	# Run all tests
    clean	# Remove OS- and platform-specific derived files.
    dist	# Create source and binary distribution
    distclean	# Remove all derived files. Like "clean" on steroids.
    install	# Install package
    test	# Same as check


To build:

    $ ./configure
    $ make update
    $ make && make check && sudo make install
    
Optionally you can regenerate the build system first with:

    $ autoreconf -fvi -Wall

See README.cvs for more detail regarding the above and for
GNU Make CVS source instructions.

See also https://github.com/rocky/remake/wiki

*Author for debugger portion:* Rocky Bernstein <rocky@gnu.org><br>
[![endorse](https://api.coderwall.com/rocky/endorsecount.png)](https://coderwall.com/rocky)
