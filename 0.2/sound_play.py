from pygame import mixer  # 基于Pygame播放背景音乐

mixer.init()  # 初始化对象
mixer.music.load('BGM.wav')  # 加载音乐

# 无限循环播放
while True:
    if not mixer.music.get_busy():  # 如果音乐没在播放
        mixer.music.play()  # 重新开始播放
