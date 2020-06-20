import multiprocessing  # 用这个库实现并行
import atexit

from multiprocessing import Process
import os  # 用这个库打开Exe并在结束时杀死进程


@atexit.register  # 这个装饰器是用来在程序结束后杀死进程，解决背景音乐在后台播放的问题
def clean():
    os.system("taskkill /im sound_play.exe /f")  # 使用os杀死进程
    os.system("taskkill /im Launcher.exe /f")


def processA():  # 准备好A进程
    os.system("kanas_review.exe")


def processB():  # 准备好B进程
    os.system("sound_play.exe")


if __name__ == '__main__':
    multiprocessing.freeze_support()  # 防止压制的exe运行异常
    # 以下是任务并行的实现
    p = Process(target=processA)
    q = Process(target=processB)
    p.start()
    q.start()
    p.join()
    q.join()
