### DIRECTORY: template/

This is ``template/`` directory which contains several template files used to
create new source files from. See ``HOWTO/create-source.md`` to read more about
source file creation.

#### Important remarks:

Files within subdirectories are usually used by maintainer scripts. For example,
files from ``template/addclass/`` are used by ``bin/addclass`` script. Don't
use them to create sources by hand.

Other files are used to create new sources by hand (by copying the file to a
desired location and changing its name). There is a list of such templates:

  - ``Doxyfile.in`` - template of ``Doxyfile.in``'s used by SCons scripts to
    create ``Doxyfile``'s from,
  - ``file.md`` - to create new markdown documents, such as ``README.md``,
  - ``LICENSE`` - plain template of license text,
  - ``license.cpp`` - license text as a C++ comment,
  - ``license.py`` - license text as a python comment,
  - ``unit.cpp`` - template of C++ source file,
  - ``unit.hpp`` - template of C++ header file,
  - ``unit.i`` - template of SWIG interface file (module),
  - ``Unit.py`` - template of python module file,
  - ``unit.swg`` - template of SWIG interface file (for inclusion),

.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
