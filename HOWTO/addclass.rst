HOWTO: Add class to src/lib hierarchy
`````````````````````````````````````

A new class unit (``.hpp`` + ``.cpp`` + ``.proto`` + ``.swg`` + unit test)
might be added as follows::


    ./bin/addclass "Fully::Qualified::Class::Name"

The above command shall create following files:

- ``src/lib/fully/qualified/class/name.hpp`` (C++ header),
- ``src/lib/fully/qualified/class/name.cpp`` (C++ source),
- ``src/lib/fully/test/unit/fully/qualified/class/name.t.h`` (Unit test).
- ``src/lib/fully/protobuf/qualified/class/name.proto`` (Google Protobuf),
- ``src/lib/fully/swig/fully/qualified/class/name.swg`` (SWIG interface).

These files are generated from templates:

- ``template/class.hpp.in``,
- ``template/class.cpp.in``,
- ``template/class.t.h.in``,
- ``template/class.proto.in``,
- ``template/class.swg.in``.

There are also additional options to the addclass script. Type::

    ./bin/addclass --help

to see them.

.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
