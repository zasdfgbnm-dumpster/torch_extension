from setuptools import setup
from torch.utils.cpp_extension import BuildExtension, CUDAExtension

setup(
    name='test',
    ext_modules=[
        CUDAExtension('test', [
            'test.cpp',
        ]),
    ],
    cmdclass={
        'build_ext': BuildExtension
    })