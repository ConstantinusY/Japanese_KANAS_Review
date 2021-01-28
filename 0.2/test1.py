import psutil
for x in psutil.process_iter():
    print(x)
