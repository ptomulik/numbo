#! /usr/bin/python

# @COPYRIGHT@
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE

# bin/addclass.py: add new class unit (header, source and possibly others)

import argparse

def add_cli_args(argparser):
    from os import path
    # Default values
    prefix = path.join('src', 'lib')
    proto_infix = 'Protobuf'
    default_namespace = 'Numbo'
    hpp_ext = '.hpp'
    cpp_ext = '.cpp'
    unit_test_ext = '.t.h'
    proto_ext = '.proto'
    proto_h_ext = '.pb.h'
    proto_wrapper_h_ext = '.hpp'
    proto_wrapper_c_ext = '.cpp'
    swig_prefix = 'swig'
    unit_test_prefix = path.join('src', 'test')
    swig_ext = '.swg'
    # Options
    argparser.add_argument('-q','--quiet', action = "store_false",
        dest = 'verbose', help = "don't print status messages to stdout")
    argparser.add_argument('--no-cpp', action = 'store_false',
        dest = 'generate_cpp', default = True,
        help = 'do not generate C++ source file')
    argparser.add_argument('--no-hpp', action = 'store_false',
        dest = 'generate_hpp', default = True,
        help = 'do not generate C++ header file')
    argparser.add_argument('--no-unit-test', action = 'store_false',
        dest = 'generate_unit_test', default = True,
        help = 'do not generate unit test file')
    argparser.add_argument('--no-proto', action = 'store_false',
        dest = 'generate_proto', default = True,
        help = 'do not generate proto file')
    argparser.add_argument('--no-swig', action = 'store_false',
        dest = 'generate_swig', default = True,
        help = 'do not generate swig file')
    argparser.add_argument('--default-namespace', type = str, metavar = 'ns',
        action = 'store', dest = 'default_namespace',
        help = "default namespace for generated class (%s)" % default_namespace,
        default = default_namespace)
    argparser.add_argument('--prefix', type = str, metavar = 'dir',
        action = 'store', dest = 'prefix',
        help = "prefix prepended to output directory (%s)" % prefix,
        default = prefix)
    argparser.add_argument('--proto-infix', type = str, metavar = 'Infix',
        action = 'store', dest = 'proto_infix',
        help = "additional part added to protobuf class name (%s)" % proto_infix,
        default = proto_infix)
    argparser.add_argument('--unit-test-prefix', type = str, metavar = 'dir',
        action = 'store', dest = 'unit_test_prefix',
        help = "prefix prepended to output directory of unit test (%s)" % unit_test_prefix,
        default = unit_test_prefix)
    argparser.add_argument('--swig-prefix', type = str, metavar = 'infix',
        action = 'store', dest = 'swig_prefix',
        help = "additional prefix added to swig file path (%s)" % swig_prefix,
        default = swig_prefix)
    argparser.add_argument('--hpp-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'hpp_ext',
        help = "extension used for header file (%s)" % hpp_ext,
        default = hpp_ext)
    argparser.add_argument('--cpp-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'cpp_ext',
        help = "extension used for source file (%s)" % cpp_ext,
        default = cpp_ext)
    argparser.add_argument('--unit-test-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'unit_test_ext',
        help = "extension used for source file (%s)" % unit_test_ext,
        default = unit_test_ext)
    argparser.add_argument('--proto-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'proto_ext',
        help = "extension used for proto file (%s)" % proto_ext,
        default = proto_ext)
    argparser.add_argument('--proto-h-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'proto_h_ext',
        help = "extension used for output protobuf headers (%s)" % proto_h_ext,
        default = proto_h_ext)
    argparser.add_argument('--proto-wrapper-h-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'proto_wrapper_h_ext',
        help = "extension used for protobuf wrapper header file (%s)" % proto_wrapper_h_ext,
        default = proto_wrapper_h_ext)
    argparser.add_argument('--proto-wrapper-c-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'proto_wrapper_c_ext',
        help = "extension used for protobuf wrapper source file (%s)" % proto_wrapper_c_ext,
        default = proto_wrapper_c_ext)
    argparser.add_argument('--swig-ext', type = str, metavar = 'dir',
        action = 'store', dest = 'swig_ext',
        help = "extension used for swig file (%s)" % swig_ext,
        default = swig_ext)
    # Positioal arguments
    argparser.add_argument('class_name', metavar = 'class', action = 'store',
                            help = "Fully::Qualified::Class_Name")

def generate_class(args):
    import re
    import string
    from os import path, makedirs
    from sys import stderr, stdout


    if args.verbose:
        stdout.write("info: preparing to generate class %r\n" % args.class_name)

    error = 0

    if args.class_name.find('::') == -1:
        class_name_full = args.default_namespace + '::' + args.class_name
        if args.verbose:
            stdout.write('info: %r not within a namespace, assuming %r\n'
                        % (args.class_name, class_name_full))
    else:
        class_name_full =  args.class_name
    class_name_parts = class_name_full.split('::')
    re_id = re.compile(r'^[a-zA-Z_][a-zA-Z0-9_]*$')
    class_name_correct_parts = [ p for p in class_name_parts if re_id.match(p) ]
    if len(class_name_parts) != len(class_name_correct_parts) \
    or len(class_name_parts) < 1:
        stderr.write('error: malformed class name: %r\n' % args.class_name)
        error = 1

    class_name = class_name_parts[-1]
    class_header_guard = '_'.join([p.upper() for p in class_name_parts]) + '_HPP_INCLUDED'
    namespaces = class_name_parts[:-1]

    if namespaces:
        open_namespaces = '\n'.join(
          ['namespace ' + p + ' {' for p in namespaces ]
        )
        close_namespaces = '\n'.join(
          [ '} /* namespace ' + p + ' */' for p in reversed(namespaces) ]
        )
        unit_test_open_namespaces = ' '.join(
          ['namespace ' + p + ' {' for p in namespaces ]
        )
        unit_test_close_namespaces = ' '.join(
          [ '}' for p in reversed(namespaces) ]
        )
    else:
        open_namespaces = ''
        close_namespaces = ''
        unit_test_open_namespaces = ''
        unit_test_close_namespaces = ''

    if args.proto_infix:
        proto_class_name_parts = [ class_name_parts[0], args.proto_infix ] \
                               + class_name_parts[1:]
    else:
        proto_class_name_parts = class_name_parts
    proto_class_name = '::'.join(proto_class_name_parts)
    proto_namespaces = proto_class_name_parts[:-1]

    if args.swig_prefix:
        swig_file_name_parts = [p.lower() for p in [ class_name_parts[0], \
                                                     args.swig_prefix ] \
                                                   + class_name_parts]

    else:
        swig_file_name_parts = [p.lower() for p in class_name_parts ]
    swig_module_parts = class_name_parts
    swig_package_parts = swig_module_parts[:-1]

##    if args.unit_test_prefix:
##        unit_test_file_name_parts = [p.lower() for p in [ class_name_parts[0], \
##                                                     args.unit_test_prefix ] \
##                                                   + class_name_parts]
##
##    else:
    unit_test_file_name_parts = [p.lower() for p in class_name_parts ]

    unit_test_header_guard = '_'.join([p.upper() for p in class_name_parts]) + '_T_H_INCLUDED'


    hpp_file_rel = path.join(*class_name_parts).lower() + args.hpp_ext
    hpp_file_full = path.join(args.prefix, hpp_file_rel)
    cpp_file_rel = path.join(*class_name_parts).lower() + args.cpp_ext
    cpp_file_full = path.join(args.prefix, cpp_file_rel)
    unit_test_file_rel = path.join(*unit_test_file_name_parts).lower() + args.unit_test_ext
    unit_test_file_full = path.join(args.unit_test_prefix, unit_test_file_rel)
    proto_file_rel = path.join(*proto_class_name_parts).lower() + args.proto_ext
    proto_h_file_rel = path.join(*proto_class_name_parts).lower() + args.proto_h_ext
    proto_wrapper_h_file_rel = path.join(*proto_class_name_parts).lower() + args.proto_wrapper_h_ext
    proto_wrapper_c_file_rel = path.join(*proto_class_name_parts).lower() + args.proto_wrapper_c_ext
    proto_file_full = path.join(args.prefix, proto_file_rel)
    proto_wrapper_h_file_full = path.join(args.prefix, proto_wrapper_h_file_rel)
    proto_wrapper_c_file_full = path.join(args.prefix, proto_wrapper_c_file_rel)
    swig_file_rel = path.join(*swig_file_name_parts).lower() + args.swig_ext
    swig_file_full = path.join(args.prefix, swig_file_rel)
    swig_moduledecl_perl = '%%module %s' % '::'.join(swig_module_parts)
    proto_wrapper_header_guard = re.sub(r'[/\.]','_', proto_wrapper_h_file_rel).upper() + '_INCLUDED'
    if swig_package_parts:
        swig_moduledecl_python = '%%module (package=%s) %s' \
                               % ('.'.join(swig_package_parts), class_name)
    else:
        swig_moduledecl_python = '%%module %s' % class_name

    # Assure the files to be generated do not exist
    if args.generate_hpp:
        if path.exists(hpp_file_full):
            stderr.write("error: %r already exists, won't override\n"
                         % hpp_file_full)
            error = 1
    if args.generate_cpp:
        if path.exists(cpp_file_full):
            stderr.write("error: %r already exists, won't override\n"
                         % cpp_file_full)
            error = 1
    if args.generate_unit_test:
        if path.exists(unit_test_file_full):
            stderr.write("error: %r already exists, won't override\n"
                        % unit_test_file_full)
            error = 1
    if args.generate_proto:
        if path.exists(proto_file_full):
            stderr.write("error: %r already exists, won't override\n"
                        % proto_file_full)
            error = 1
        if path.exists(proto_wrapper_h_file_full):
            stderr.write("error: %r already exists, won't override\n"
                        % proto_wrapper_h_file_full)
            error = 1
        if path.exists(proto_wrapper_c_file_full):
            stderr.write("error: %r already exists, won't override\n"
                        % proto_wrapper_c_file_full)
            error = 1
    if args.generate_swig:
        if path.exists(swig_file_full):
            stderr.write("error: %r already exists, won't override\n"
                        % swig_file_full)
            error = 1

    # Create directories when necessary
    if not error:
        if args.generate_hpp:
            hpp_dir = path.dirname(hpp_file_full)
            if not path.exists(hpp_dir):
                if args.verbose:
                    stdout.write("info: creating directory %r\n" % hpp_dir)
                makedirs(hpp_dir)
            elif not path.isdir(hpp_dir):
                stderr.write("error: %r is not a directory\n" % hpp_dir)
                error = 1
        if args.generate_cpp:
            cpp_dir = path.dirname(cpp_file_full)
            if not path.exists(cpp_dir):
                if args.verbose:
                    stdout.write("info: creating directory %r\n" % cpp_dir)
                makedirs(cpp_dir)
            elif not path.isdir(cpp_dir):
                stderr.write("error: %r is not a directory\n" % cpp_dir)
                error = 1
        if args.generate_unit_test:
            unit_test_dir = path.dirname(unit_test_file_full)
            if not path.exists(unit_test_dir):
                if args.verbose:
                    stdout.write("info: creating directory %r\n" % unit_test_dir)
                makedirs(unit_test_dir)
            elif not path.isdir(unit_test_dir):
                stderr.write("error: %r is not a directory\n" % unit_test_dir)
                error = 1
        if args.generate_proto:
            proto_dir = path.dirname(proto_file_full)
            if not path.exists(proto_dir):
                if args.verbose:
                    stdout.write("info: creating directory %r\n" % proto_dir)
                makedirs(proto_dir)
            elif not path.isdir(proto_dir):
                stderr.write("error: %r is not a directory\n" % proto_dir)
                error = 1
        if args.generate_swig:
            swig_dir = path.dirname(swig_file_full)
            if not path.exists(swig_dir):
                if args.verbose:
                    stdout.write("info: creating directory %r\n" % swig_dir)
                makedirs(swig_dir)
            elif not path.isdir(swig_dir):
                stderr.write("error: %r is not a directory\n" % swig_dir)
                error = 1

    if not error:
        # FIXME: customize template
        class_hpp_in = path.join("template", "addclass", "class.hpp.in")
        class_cpp_in = path.join("template", "addclass", "class.cpp.in")
        class_proto_in = path.join("template", "addclass", "class.proto.in")
        class_proto_wrapper_h_in = path.join("template", "addclass", "protoc-wrapper.hpp.in")
        class_proto_wrapper_c_in = path.join("template", "addclass", "protoc-wrapper.cpp.in")
        class_unit_test_in = path.join("template", "addclass", "class.t.h.in")
        class_swig_in = path.join("template", "addclass", "class.swg.in")
        class_unit_test = class_name + '_TestSuite'
        class_unit_test_fqdn = '::'.join(namespaces + [class_unit_test])

        substs = {
            'CLASS'                             : class_name,
            'CLASS_NAMESPACES'                  : '::'.join(namespaces),
            'CLASS_FQDN'                        : '::'.join(namespaces + [class_name]),
            'CLASS_HEADER_FILE'                 : hpp_file_rel,
            'CLASS_SOURCE_FILE'                 : cpp_file_rel,
            'CLASS_PROTO_FILE'                  : proto_file_rel,
            'CLASS_PROTO_H_FILE'                : proto_h_file_rel,
            'CLASS_PROTO_PACKAGE'               : '.'.join(proto_namespaces),
            'CLASS_SWIG_FILE'                   : swig_file_rel,
            'CLASS_SWIG_MODULEDECL_PERL'        : swig_moduledecl_perl,
            'CLASS_SWIG_MODULEDECL_PYTHON'      : swig_moduledecl_python,
            'CLASS_HEADER_GUARD'                : class_header_guard,
            'CLASS_OPEN_NAMESPACES'             : open_namespaces,
            'CLASS_CLOSE_NAMESPACES'            : close_namespaces,
            'CLASS_UNIT_TEST'                   : class_unit_test,
            'CLASS_UNIT_TEST_FQDN'              : class_unit_test_fqdn,
            'CLASS_UNIT_TEST_HEADER_FILE'       : unit_test_file_rel,
            'CLASS_UNIT_TEST_HEADER_GUARD'      : unit_test_header_guard,
            'CLASS_UNIT_TEST_OPEN_NAMESPACES'   : unit_test_open_namespaces,
            'CLASS_UNIT_TEST_CLOSE_NAMESPACES'  : unit_test_close_namespaces,
            'PROTO_WRAPPER_HEADER_FILE'         : proto_wrapper_h_file_rel,
            'PROTO_WRAPPER_SOURCE_FILE'         : proto_wrapper_c_file_rel,
            'PROTO_WRAPPER_HEADER_GUARD'        : proto_wrapper_header_guard,
            'CLASS_PROTO_FQDN'                  : '::'.join(proto_namespaces + [class_name]),
        }

        if args.generate_hpp:
            if args.verbose:
                stdout.write("info: reading %r\n" % class_hpp_in)
            if not path.isfile(class_hpp_in):
                stderr.write("error: file %r does not exist\n"
                            % class_hpp_in)
                error = 1
            else:
                hpp_template = string.Template(file(class_hpp_in).read())
        if args.generate_cpp:
            if args.verbose:
                stdout.write("info: reading %r\n" % class_cpp_in)
            if not path.isfile(class_cpp_in):
                stderr.write("error: file %r does not exist\n"
                            % class_cpp_in)
                error = 1
            else:
                cpp_template = string.Template(file(class_cpp_in).read())
        if args.generate_unit_test:
            if args.verbose:
                stdout.write("info: reading %r\n" % class_unit_test_in)
            if not path.isfile(class_unit_test_in):
                stderr.write("error: file %r does not exist\n"
                            % class_unit_test_in)
                error = 1
            else:
                unit_test_template = string.Template(file(class_unit_test_in).read())
        if args.generate_proto:
            if args.verbose:
                stdout.write("info: reading %r\n" % class_proto_in)
            if not path.isfile(class_proto_in):
                stderr.write("error: file %r does not exist\n"
                            % class_proto_in)
                error = 1
            else:
                proto_template = string.Template(file(class_proto_in).read())
            if args.verbose:
                stdout.write("info: reading %r\n" % class_proto_wrapper_h_in)
            if not path.isfile(class_proto_wrapper_h_in):
                stderr.write("error: file %r does not exist\n"
                            % class_proto_wrapper_h_in)
                error = 1
            else:
                proto_wrapper_h_template = string.Template(file(class_proto_wrapper_h_in).read())
            if args.verbose:
                stdout.write("info: reading %r\n" % class_proto_wrapper_c_in)
            if not path.isfile(class_proto_wrapper_c_in):
                stderr.write("error: file %r does not exist\n"
                            % class_proto_wrapper_c_in)
                error = 1
            else:
                proto_wrapper_c_template = string.Template(file(class_proto_wrapper_c_in).read())
        if args.generate_swig:
            if args.verbose:
                stdout.write("info: reading %r\n" % class_swig_in)
            if not path.isfile(class_swig_in):
                stderr.write("error: file %r does not exist\n"
                            % class_swig_in)
                error = 1
            else:
                swig_template = string.Template(file(class_swig_in).read())

    if not error:
        if args.generate_hpp:
            if args.verbose:
                stdout.write("info: generating %r\n" % hpp_file_full)
            file(hpp_file_full, "w").write(hpp_template.substitute(substs))
        if args.generate_cpp:
            if args.verbose:
                stdout.write("info: generating %r\n" % cpp_file_full)
            file(cpp_file_full, "w").write(cpp_template.substitute(substs))
        if args.generate_unit_test:
            if args.verbose:
                stdout.write("info: generating %r\n" % unit_test_file_full)
            file(unit_test_file_full, "w").write(unit_test_template.substitute(substs))
        if args.generate_proto:
            if args.verbose:
                stdout.write("info: generating %r\n" % proto_file_full)
            file(proto_file_full, "w").write(proto_template.substitute(substs))
            if args.verbose:
                stdout.write("info: generating %r\n" % proto_wrapper_h_file_full)
            file(proto_wrapper_h_file_full, "w").write(proto_wrapper_h_template.substitute(substs))
            if args.verbose:
                stdout.write("info: generating %r\n" % proto_wrapper_c_file_full)
            file(proto_wrapper_c_file_full, "w").write(proto_wrapper_c_template.substitute(substs))
        if args.generate_swig:
            if args.verbose:
                stdout.write("info: generating %r\n" % swig_file_full)
            file(swig_file_full, "w").write(swig_template.substitute(substs))

    return error

argparser = argparse.ArgumentParser()
add_cli_args(argparser)
args = argparser.parse_args()
exit(generate_class(args))

# Local Variables:
# # tab-width:4
# # indent-tabs-mode:nil
# # End:
# vim: set syntax=python expandtab tabstop=4 shiftwidth=4:
