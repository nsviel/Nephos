from setuptools import setup, find_packages

setup(
    name='pynephos',
    version='0.1',
    packages=find_packages(where='../../build/pynephos'),  # Specify the build folder
    package_dir={'': '../../build/pynephos'},  # Map root package to the build directory
    include_package_data=True,  # Include shader and media files
    package_data={
        "": ["shader/*", "media/*"]  # Include these directories
    },
    py_modules=['pynephos'],  # Main module (the .so file)
)
