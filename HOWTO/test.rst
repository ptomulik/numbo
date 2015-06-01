HOWTO: Compile NUMBO project
````````````````````````````

To test NUMBO project go to the top-level source directory and type::

    scons check

The above command creates all test runners (unit tests) and executes them.

HOWTO: Code coverage
``````````````````````````

Code coverage needs code instrumentation. We use gcov_ for that. By default the
code is compiled with gcov_ disabled. To enable it, set the command-line
variable ``NUMBO_ENABLE_GCOV``::

    scons check NUMBO_ENABLE_GCOV=YES 

This adds extra flags to ``CCFLAGS``, ``LDFLAGS`` and modifies ``LIBS`` SCons
construction variables.


.. _gcov: http://gcc.gnu.org/onlinedocs/gcc/Gcov.html

.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
