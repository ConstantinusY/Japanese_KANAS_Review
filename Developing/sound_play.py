import psutil
import sys
from pygame import mixer
mixer.init()
mixer.music.load('BGM.wav')
while True:
    Pl = psutil.pids()
    for processes in Pl:
        if psutil.Process(processes).name() == 'Launcher.exe':
            if not mixer.music.get_busy():
                mixer.music.play()
            break
        else:
            pass
    else:
        exit()
