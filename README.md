## justleft - Left Justify a String

This is a little utility created a very long time
ago for systems without sed.  All it does is Left
Justify all records in a Text File.

To build, execute build.sh to generate a Makefile from
Makefile.template on most BSD/Linux systems and IBM AIX.  For MS-DOS,
it should be rather easy to create a Makefile.  I know it does compile
under MS-DOS using Microsoft c.

This requires [j\_lib2](https://github.com/jmcunx/j_lib2) to build.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, so I came up with my own method which
is a real hack.  But works for me.
