HOWTO: Compile NUMBO project
````````````````````````````

To compile NUMBO project go to the top-level source directory and type::

    scons

The above command creates all libraries, executables and external language
bindings under ``build/`` directory. Note, that it does not create the API
documentation.

HOWTO: Change compilation flags
```````````````````````````````

You may set several command-line variables to change compilator, compilation
flags and other options. For example, you may change flags for C and C++
compiler::

    scons CCFLAGS='-g -O2' CXXFLAGS='-std=c++11' CFLAGS=''

HOWTO: Compile with clang compiler
``````````````````````````````````

You may use clang_ compiler instead of the default one (gcc)::

    scons CC=clang CXX=clang++

HOWTO: Clean NUMBO project
``````````````````````````

To clean-out source tree go to the top-level source directory and type::

    scons -c

You may also wish to delete ``build/`` directory and scons cache files::

    rm -r build/

HOWTO: Compile API documentation
````````````````````````````````

To compile API documentation, go to the top level source directory and type::

    scons api-doc

This creates HTML docs in several places, for example under
``build/lib/numbo/doc``.

HOWTO: Clean API documentation
``````````````````````````````

To clean API documentation files created with ``scons api-doc``, go to the top
level source directory and type::

    scons -c api-doc

.. _clang: http://clang.llvm.org/

.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
