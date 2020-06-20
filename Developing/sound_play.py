
from pygame import mixer
mixer.init()
mixer.music.load('BGM.wav')
while True:
    if not mixer.music.get_busy():
        mixer.music.play()
