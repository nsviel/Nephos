import sys
import os
import pynephos
from pynput import keyboard

#Nephos stuff
nephos = pynephos.App()

if 0:
    nephos.run()
    nephos.add_cloud()

    #Main loop
    def on_press(key):
        try:
            if key == keyboard.Key.esc:
                print("Esc key pressed. Exiting loop...")
                return False  # This will stop the listener
        except AttributeError:
            pass

    # Start listening for keyboard input
    with keyboard.Listener(on_press=on_press) as listener:
        listener.join()

    #Nephos close
    nephos.close()
