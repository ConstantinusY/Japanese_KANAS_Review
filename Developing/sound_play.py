from pygame import mixer  # ����Pygame���ű�������

mixer.init()  # ��ʼ������
mixer.music.load('BGM.wav')  # ��������

# ����ѭ������
while True:
    if not mixer.music.get_busy():  # �������û�ڲ���
        mixer.music.play()  # ���¿�ʼ����
