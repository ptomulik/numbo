HOWTO: Create new source file
`````````````````````````````

If you wish to create fully-equipped C++ class module, see 
``HOWTO/addclass.md``

If you wish to create a new source file, do your best to use one of the
templates stored under ``template/`` directory. For example, to create new
C++ header do::

    cp template/unit.hpp src/lib/numbo/myheader.hpp

If there is no template available for the source file type you wish to create,
consider creating new one in ``template/`` directory and put documentation to
``template/README.md``.

.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
