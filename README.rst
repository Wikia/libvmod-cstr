============
vmod_cstr
============

----------------------
Varnish cstr Module
----------------------

:Author: Lukasz Jagiello
:Date: 2017-12-21
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

::

	import cstr;
	cstr.escape(<string>);

DESCRIPTION
===========

Varnish Module (vmod) to escape characters unsafe for printing from a string. 

Based on:
* https://github.com/fastly/libvmod-urlcode
* https://github.com/varnishcache/libvmod-example

FUNCTIONS
=========

escape
-----

Prototype
        ::

                escape(STRING_LIST input)
Return value
	STRING
Description
  Returns characters safe for printing from a string. 
Example
        ::

                set resp.http.escaped = cstr.escape("Hello\\World");

INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the ``varnishtest`` tool.

Building requires the Varnish header files and uses pkg-config to find
the necessary paths.

Pre-requisites::

 sudo apt-get install -y autotools-dev make automake libtool pkg-config libvarnishapi1 libvarnishapi-dev

Usage::

 ./autogen.sh
 ./configure

If you have installed Varnish to a non-standard directory, call
``autogen.sh`` and ``configure`` with ``PKG_CONFIG_PATH`` pointing to
the appropriate path. For cstr, when varnishd configure was called
with ``--prefix=$PREFIX``, use

 PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
 export PKG_CONFIG_PATH

Make targets:

* make - builds the vmod.
* make install - installs your vmod.
* make check - runs the unit tests in ``src/tests/*.vtc``
* make distcheck - run check and prepare a tarball of the vmod.

Installation directories
------------------------

By default, the vmod ``configure`` script installs the built vmod in
the same directory as Varnish, determined via ``pkg-config(1)``. The
vmod installation directory can be overridden by passing the
``VMOD_DIR`` variable to ``configure``.

Other files like man-pages and documentation are installed in the
locations determined by ``configure``, which inherits its default
``--prefix`` setting from Varnish.

USAGE EXAMPLE
=============

In your VCL you could then use this vmod along the following lines::

        import cstr;

        sub vcl_deliver {
                # This sets resp.http.escaped to "Hello\\World"
                set resp.http.escaped = cstr.escape("Hello\World");
        }

COMMON PROBLEMS
===============

* configure: error: Need varnish.m4 -- see README.rst

  Check if ``PKG_CONFIG_PATH`` has been set correctly before calling
  ``autogen.sh`` and ``configure``

* Incompatibilities with different Varnish Cache versions

  Make sure you build this vmod against its correspondent Varnish Cache version.
  For cstr, to build against Varnish Cache 4.0, this vmod must be built from branch 4.0.
