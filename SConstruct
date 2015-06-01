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

import os

# gettext tool is available on 2.2 and later.
EnsureSConsVersion(2,2)

#############################################################################
# initialize new environment.
env = Environment( )
#############################################################################

#############################################################################
# Define variant directory
#############################################################################
AddOption('--variant-dir', type='string', default='build', metavar='DIR',
          help='SCons variant directory (a.k.a build dir)')
variant = { 'variant_dir' : env.GetOption('variant_dir'),
            'src_dir' : 'src',
            'duplicate' : 0,
            'exports' : { 'env' : env } }
# Sconsign file goes to variant directory
env.SConsignFile(os.path.join(variant['variant_dir'], '.sconsign'))
#############################################################################

#############################################################################
# Tools used by both, SConscript and SConscript.i18
env.Tool('gettext')
#############################################################################

#############################################################################
# Build in variant directory
SConscript( 'src/SConscript', **variant )
#############################################################################

#############################################################################
# Build in source directory
SConscript( 'src/SConscript.i18n', exports = ['env'] )
#############################################################################

#############################################################################
# Global targets
#
# API Documentation
api_doc = env.AlwaysBuild(env.Alias('api-doc'))
env.Depends(api_doc, env.Glob('bin/doxy*'))
# The check target (CxxTest)
env.AlwaysBuild(env.Alias('check'))
#############################################################################

# Local Variables:
# # tab-width:4
# # indent-tabs-mode:nil
# # End:
# vim: set syntax=scons expandtab tabstop=4 shiftwidth=4:
