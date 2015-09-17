from distutils.core import setup, Extension

test_mpi = Extension('testmpi', libraries = ['mpi', 'mpi_cxx'],
                     sources = ['mpi_test.cpp'],
                     include_dirs = ['/usr/local/include', '/pds/opt/openmpi/include'],
                     library_dirs = ['/usr/local/lib', '/pds/opt/openmpi/lib64'],
                     runtime_library_dirs = ['/pds/opt/openmpi/lib64'])

setup (name = 'test_mpi',
       version = '0.1',
       description = '',
       author = 'Joel Hermanns',
       author_email = 'joel.hermanns@rwth-aachen.de',
       url = '',
       long_description = '''''',
       ext_modules = [test_mpi])
