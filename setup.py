from distutils.core import setup, Extension

module1 = Extension('darknet',
                    sources = ['src/py_darknet.c'])

setup (name = 'DarkNet Python',
       version = '1.0',
       description = 'Python binding for darknet',
       ext_modules = [module1])