import sys
import os

# Add the directory containing the shared object to the Python path
sys.path.append(os.path.join(os.path.dirname(__file__), '../build'))


import pynephos

app = pynephos.App()
app.init()
app.add_cloud()
app.run()
