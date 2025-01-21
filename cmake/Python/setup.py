from setuptools import setup
import os
from setuptools.command.install import install

class CustomInstall(install):
    def run(self):
        # Call the standard install process
        install.run(self)

        # Copy the .so file into the appropriate place
        # Ensure the target directory is the site-packages directory
        target_dir = os.path.join(self.install_lib, 'pynephos')
        os.makedirs(target_dir, exist_ok=True)
        os.rename(
            '../../build/pynephos.cpython-312-x86_64-linux-gnu.so', 
            os.path.join(target_dir, 'pynephos.cpython-312-x86_64-linux-gnu.so')
        )

setup(
    name='pynephos',
    version='0.1',
    cmdclass={'install': CustomInstall},
)
