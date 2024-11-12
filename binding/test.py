import sys
import os

# Add the directory containing the shared object to the Python path
sys.path.append(os.path.join(os.path.dirname(__file__), '../build'))


import pynephos

pynephos.run()
pynephos.add_cloud()
