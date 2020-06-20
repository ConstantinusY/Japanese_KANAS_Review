import multiprocessing
from multiprocessing import Process
import os


def processA():
    os.system("kanas_review.exe")


def processB():
    os.system("sound_play.exe")


if __name__ == '__main__':
    multiprocessing.freeze_support()
    p = Process(target=processA)
    q = Process(target=processB)
    p.start()
    q.start()
    p.join()
    q.join()

