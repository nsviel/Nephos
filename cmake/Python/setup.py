from setuptools import setup
import os
from setuptools.command.install import install

class CustomInstall(install):
    def run(self):
        # Call the standard install process
        install.run(self)

        # Determine the source and target paths
        source_path = os.path.abspath('../../build/pynephos.cpython-312-x86_64-linux-gnu.so')
        target_dir = self.install_lib  # Install directly to site-packages
        print(f"Copying from {source_path} to {target_dir}")

        # Ensure the target directory exists
        os.makedirs(target_dir, exist_ok=True)

        # Move the .so file to the target directory
        os.rename(
            source_path,
            os.path.join(target_dir, 'pynephos.cpython-312-x86_64-linux-gnu.so')
        )

setup(
    name='pynephos',
    version='0.1',
    cmdclass={'install': CustomInstall},
    py_modules=['pynephos'],
)

