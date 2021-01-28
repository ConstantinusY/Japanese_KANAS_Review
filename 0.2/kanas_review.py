#!/usr/bin/python
# -*- coding: utf-8 -*-
import json  # 导入库
import random

"""
函数声明：
cutA() :大分割线
cutB() :小分割线
invert_dict(d) :反转字典        d:要进行操作的字典
dictValue_list(d, list) ：提取字典的值,作为列表输出 d:输入的字典 list:输出的列表
ListGetAll(l):从一个嵌套混乱的大列表中取出所有的值，作为一个新列表输出    l:输入列表 
"""


def cutA():  # 定义大分割线
    """
    变量声明：
    Ji:while 循环计数器，控制分割线输出次数
    """
    print()  # 输出空行达到分割目的
    Ji = 0  # 初始化计数器
    while Ji <= 7:  # 重复七次-_
        print('-_', end='')  # 运用结束符达到“线”的目的
        Ji += 1  # 计数器控制
    print(' 日本語 ', end='')  # 输出不同内容保证输出美观性
    Ji = 0  # 初始化计数器
    while Ji <= 7:  # 重复七次-_
        print('-_', end='')  # 运用结束符达到“线”的目的
        Ji += 1  # 计数器控制
    print(' Japanese ', end='')  # 输出不同内容保证输出美观性
    Ji = 0  # 初始化计数器
    while Ji <= 7:  # 重复七次-_
        print('-_', end='')  # 运用结束符达到“线”的目的
        Ji += 1  # 计数器控制
    print()  # 输出一个空的结束符，换行一下
    print()  # 输出空行，分割


def cutB():  # 定义小分割线
    """
    变量声明：
    Ji:while 循环计数器，控制分割线输出次数
    """
    print()  # 输出空行达到分割目的
    Ji = 0  # 初始化计数器
    while not Ji > 25:  # 当J不大于（<=）25时，条件成立。 # B分割线长度为五十个-
        print('--', end='')  # 运用结束符达到“线”的目的。
        Ji += 1  # 计数器控制
    print()  # 输出一个空的结束符，换行一下
    print()  # 输出空行，分割


def invert_dict(d):  # 定义颠倒字典函数
    inverse_d = dict()  # 创建准备返回的空列表
    for K in d:  # 对字典使用for循环，遍历字典的所有键
        if d[K] not in inverse_d:  # 如果输入字典的第K项不在空列表，颠倒加入返回列表中
            inverse_d[d[K]] = [K]
        elif d[K] in inverse_d:
            inverse_d[d[K]].append(K)  # 将原字典的key直接加入list中
    return inverse_d  # 定义函数返回值


def dictValue_list(d, list):  # 提取字典中所有值的函数
    for ii in d.keys():  # 通过.keys()函数获取所有键，并遍历它们
        list.append(d[ii])  # 通过遍历的键查找罗马音，并加入到列表中
    return list  # 将列表作为函数返回值


def ListGetAll(l):  # 用暴力方法解决列表嵌套混乱问题的函数，不要跟我说什么取项方法优美，我选择暴力。 # l = testlist
    l_str = str(l)  # 将整个列表看作字符串
    listA = []  # 准备一个空列表，我将字符串的所有字符全部拆分以便处理

    listA.extend(l_str)  # 使用extend把字符串中的每一个字符单独拆分出来

    for bi in range(listA.count('[')):  # 删除全部的"[",统计出现的次数，再全部删除
        listA.remove('[')
    for bi in range(listA.count(']')):  # 删除全部的"]"，统计出现的次数，再全部删除
        listA.remove(']')
    bi = 0  # 初始化计数器
    while bi < len(listA):  # 遍历listA的所有项
        if (listA[bi] == ',') and (listA[bi + 1] == ','):  # 如果两个逗号再一起，那么删除后一个，这在多个逗号时也能达到作用
            listA.remove(listA[bi + 1])
        bi += 1  # 计数器控制
    del bi  # 使用while循环后删除计数器避免变量混乱

    for bi in range(listA.count(' ')):  # 删除全部的空格，统计出现的次数，再全部删除
        listA.remove(' ')

    returnList = str(''.join(listA))  # 使用Join函数把刚刚拆分后处理好的列表重新合并成一个字符串
    returnList = returnList.split(',')  # 使用split把字符串中各项提取出来再转换成列表
    return returnList  # 设定函数返回值


# 开始的引导性输出
print('info:\n设计的五十音练习，可以通过输出问卷或交互式练习帮助学习者更好地掌握五十音。\n'
      '练习形式是对照假名输入对应的罗马音。\n'
      '程序开始之前将设定练习轮数以及模式。\n请注意：输入数字或罗马音时如果在结尾输入空格，将会导致程序运行异常：例：\n'
      '合理输入：tsu，错误输入：tsu 。\n'
      'updates：\n'
      '相比于不够成熟的0.1版本，这是相对成熟的0.2版本，相比于0.1发生了较大的改变。\n'
      '1.修复0.1版本中会输出空组，练习重复的问题。\n'
      '2.相比于0.1，增加了不同难度的复习，适合各阶段的学习者\n'
      '3.问卷输出模式增加罗马音——假名模式，提供形式更多变的练习')
cutA()

TURNs = int(input('设定练习轮数（问卷张数）'))  # 设定轮数
LEVEL = str(input('我们来设定一下练习的难度级别。[请输出“:”前面的“字母＋数字”形式的表达式，\n并只能选择给出的难度，使用其他字母或输入空格都会导致程序'
                  '运行异常。]'
                  '\nA1：只包含平假名五十音基本部分。\tA2：包含平假名清音和浊音部分。\tA3：包含平假名清音、浊音、拗音部分\n'
                  'B1:只包含片假名清音部分\tB2：包含片假名清音和浊音部分\tB3：包含片假名清音、浊音、拗音部分。\n'
                  'S：包含片假名和平假名的清音、浊音、拗音部分（即一次练到爽）'))  # 引导用户设定难度

"""
这是读取、转换数据、初始化基本数据部分的代码。
变量＆列表＆字典声明：
Items1：读取出的假名（会被删除）
Items：处理后数据类型正确的假名
Keys1：读取出的答案（会被删除）
Keys：处理后数据类型正确的答案
KEYs:存储所有答案的字典
itemsX：打乱后的全部假名
itemsY：打乱后的全部罗马音
"""
Items1 = open(f"{LEVEL}_Items.txt", 'r', encoding='UTF-8')  # 按照选择的难度打开储存数据的txt，r只读模式，使用UTF-8已达到支持日语的效果
Items = "".join(Items1.read().splitlines())  # 将分行的文档各行合并起来变成字符串以便于之后的数据类型转换操作
Items = Items.encode('utf8')[3:].decode('utf8')  # 习惯性转换编码，防止操作出现问题
Items = Items.split(',')  # 通过','将str数据分割为列表数据
if Items.count('') != 0:  # 删除列表中的所有空数据
    Items.remove('')
Keys1 = open(f"{LEVEL}_Keys.txt", 'r', encoding='UTF-8')  # 同样滴，r只读模式，使用UTF-8已达到支持日语的效果
Keys = str("".join(Keys1.read().splitlines()))  # 将分行的文档各行合并起来变成字符串以便于之后的数据类型转换操作
if Keys.startswith(u'\ufeff'):
    Keys = Keys.encode('utf8')[3:].decode('utf8')  # 改变文件编码解决json转换时的报错问题
Keys = json.loads(Keys)  # 使用万能滴json转换为字典~
del Keys1  # 删除不必要的数据以免产生不必要的麻烦
del Items1

items = list(Items)  # 这是所有的假名列表
KEYs = dict(Keys)  # 这是答案字典
itemsX = []  # 打乱的items列表，以便练习使用

cutA()

mode = int(input('选择模式：\n输出问卷：0，进入交互式练习：1    '))  # 模式设定

cutA()

if mode == 0:  # 输出问卷模式的代码：
    '''
    这一部分是输出问卷的代码。
    变量声明：
    b：为了简便使用for循环，此临时变量无意义。
    Qmode:输出问卷的模式
    '''
    for b in range(TURNs):  # 根据设定的轮数输出问卷（张数）
        Qmode = int(input('你要输出什么样的问卷？\n 1：假名——罗马音 2：罗马音——假名(请输入1或2)'))

        """
        每一轮练习开始都要重新打乱一次items。
        """
        items = list(Items)
        itemsX = []
        while not (items == []):  # 打乱items的过程
            position = random.randint(0, (len(items) - 1))  # 通过random库随机选出items中的一项，将它加入itemsX（打乱的列表）中，
            # (len(items) - 1)可以保证一直属于正确的覆盖全部范围的状态
            itemsX.append(items[position])
            items.pop(position)  # 加入过后删除items中的这一项，这样才可以避免重复。

        if Qmode == 1:
            """
            输出假名——罗马音问卷：
            变量声明：
            b：为了简便使用for循环，此临时变量无意义。
            i：控制while循环的计数器
            j：控制while循环的计数器
            """
            i = 0  # 计数器控制
            while i <= len(itemsX):  # 覆盖打乱后的假名列表的每一项
                j = 0  # 计数器控制
                print('假名：', end='')  # 通过结束符保证将要到来的题目同行输出
                while j <= 4:  # 控制每行只输出四个假名
                    if i <= len(itemsX):  # 如果假名还够用，那么开始输出（当i>长度时候，就说明假名不够力）
                        print(f'「{itemsX[i - 1]}」', end=' ')  # 格式化输出使问卷更加美观
                        i += 1  # 计数器控制
                        j += 1  # 计数器控制
                    else:
                        break  # 假名不够用了，就停止循环
                print()  # 换行操作
                print('罗马音：')  # 提问罗马音
            del i, j

        elif Qmode == 2:

            """
            每一轮练习开始都要重新打乱一次items。
            """
            items1 = []
            itemsY = []
            itemsY = dictValue_list(KEYs, itemsY)
            while not (itemsY == []):  # 打乱items的过程
                # 将所有的罗马音取出来打乱，以便输出问卷使用
                position = random.randint(0, (len(itemsY) - 1))  # 通过random库随机选出items中的一项，将它加入itemsY（打乱的列表）中，
                # (len(itemsY) - 1)可以保证一直属于正确的覆盖全部范围的状态
                items1.append(itemsY[position])
                itemsY.pop(position)  # 加入过后删除itemsY中的这一项，这样才可以避免重复。
            itemsY = items1
            del items1
            """
            输出罗马音——假名问卷：
            i：控制while循环的计数器
            j：控制while循环的计数器
            """
            print()
            i = 0  # 计数器控制
            while i <= len(itemsY):  # 覆盖打乱后的假名列表的每一项
                j = 0  # 计数器控制
                print('罗马音：', end='')  # 通过结束符保证将要到来的题目同行输出
                while j <= 4:  # 控制每行只输出四个假名
                    if i <= len(itemsY):  # 如果假名还够用，那么开始输出（当i>长度时候，就说明假名不够力）
                        print(f'「{itemsY[i - 1]}」', end=' ')  # 格式化输出使问卷更加美观
                        i += 1  # 计数器控制
                        j += 1  # 计数器控制
                    else:
                        break  # 假名不够用了，就停止循环
                print()  # 换行操作
                print('假名：')  # 提问罗马音
            del i, j

        if TURNs > 1:
            cutB()

elif mode == 1:  # 交互式练习的代码部分

    for JP in range(TURNs):
        cutA()
        print(f'进入第{JP + 1}轮复习！')  # 还是因为JP从0开始qwq
        cutB()
        """
        每一轮练习开始都要重新打乱一次items。并重新定义列表。
        """
        itemsX = []
        items = list(Items)
        while not (items == []):  # 打乱items的过程
            position = random.randint(0, (len(items) - 1))  # 通过random库随机选出items中的一项，将它加入itemsX（打乱的列表）中，
            # (len(items) - 1)可以保证一直属于正确的覆盖全部范围的状态
            itemsX.append(items[position])
            items.pop(position)  # 加入过后删除items中的这一项，这样才可以避免重复。
        AllFalseAnswers = []  # 列表初始化操作
        AllFalseAnswersKeys = []
        KEYsX = invert_dict(KEYs)  # 通过自定义的函数翻转KEYs字典
        """
        这一部分是将打乱的假名分组。
        变量＆列表声明：
        g:打乱后假名的个数
        o:随机的单组假名的个数
        m:单组开始位置（切片开始下标）
        n:单组结束位置（切片结束下标）
        p:当前操作的组
        itemsText：存储分组后的假名以供练习使用
        """
        itemsText = []  # 将假名分组，每组3~5个
        p = 0  # 当前操作的组
        m = 0  # 单组开始位置（切片开始下标）
        n = 0  # 单组结束位置（切片结束下标）
        g = len(itemsX)  # 存储打乱后假名的个数
        o = random.randint(3, 5)  # 初始化随机的单组假名的个数(单组长度)
        n += o  # 更新结束位置
        while not (g - 5 <= 0):  # 当(g-5) > 0时，才能保证分组正常，因为分组中最多五项
            itemsText.append(list())  # 在大列表中嵌套一个小列表，这便是单个组
            for i in itemsX[m:n:1]:  # 根据设定好的起始＆终止位置对列表进行切片操作，并遍历这切片部分中的所有值。
                itemsText[p].append(i)  # 将遍历到的这一项加入到输出列表的第p项（第p组）中
            p += 1  # p加上1，处理下一组
            m = n  # 上一次的结束位置变成这次的开始位置
            g -= o  # 打乱后的假名已经放到第p组里o个了，所以把总数减去o
            o = random.randint(3, 5)  # 重新随机单组假名数量
            n += o  # 更新结束位置
        itemsText.append(list())  # 这是最后一组，先添加一个空列表存储最后一组假名
        for i in itemsX[n: len(itemsX): 1]:  # 上面已经定义了n，而因为是最后一组所以结束位置直接len(itemsX)。
            itemsText[p].append(i)  # 将i添加进组里面
        if not itemsText[len(itemsText) - 1]:  # 如果items最后一项是空项
            itemsText.pop(len(itemsText) - 1)  # 就删除这一项
            # 这样可以避免出现多输出一组的问题
        del p, m, n, g, o  # 删除使用的变量，避免变量混乱出现的问题。

        """
        这是练习部分
        变量＆列表声明：
        i:存储当前的组数
        p:控制输出的组数的计数器
        j:输出的假名
        II:（临时变量）正在练习（输出）的组
        b：（临时变量）控制输出时“这组的第...个假名”的变量
        Count：计数器，存储当前组中使用的假名的位置（第……个假名）
        answers：存储用户输入的答案
        FalseAnswersKey：存储当组错误回答的正确答案
        AllFalseAnswers：存储所有回答错误的假名以便最后输出
        pa:（临时变量）遍历用户所有回答时使用的临时变量
        ct: 输出错误答案改正时控制“第……个错误答案”，同时也是while循环的计数器
        AS：错题复习改正时存储回答
        zz：（临时变量）输出全部错误答案时存储遍历位置的临时变量
        """
        i = 0  # 初始化i
        p = 1  # 初始化p
        for II in itemsText:  # 遍历分好组的假名，获取当前需要的分组（II）
            print(f'第{p}组：', end='')  # 输出组数
            for j in II:  # 遍历获取的组，依次输出假名
                print(f'「{j}」', end=' ')  # 通过格式化输出使输出更美观
            print()  # 输出空行以换行
            answers = []  # 初始化回答列表
            for b in range(len(itemsText[p - 1])):  # 获取这一分组中的假名数，并根据假名数引导用户输入答案
                print(f'请输入这组的第{b + 1}个假名的罗马音：', end='')  # 引导输入
                answers.append(str(input()))  # 将用户输入的答案转换数据类型后加入回答列表
            cutB()
            p += 1  # 计数器控制
            Count = 0  # 初始化Count
            FalseAnswersKey = []  # 初始化错误回答的的正确答案列表
            for pa in answers:  # 遍历用户的所有回答
                # 通过KEYs[str(itemsText[i][Count])]查找这一项得到正确答案，因为在重新分组的时候只是分割，而并没有进一步打乱顺序，
                # 所以可以直接从itemsText中查找该项，并将其作为键在KEYs字典中查找正确答案
                if pa == KEYs[str(itemsText[i][Count])]:  # 如果答案匹配
                    print(f'第{Count + 1}个答案正确 ', end='\t')  # 输出“回答正确”，并使用Count控制计数
                    Count += 1  # Count计数器控制
                else:  # 如果答案不匹配
                    print(f'第{Count + 1}个答案错误 ', end='\t')  # 先输出“答案错误，并使用Count控制计数
                    FalseAnswersKey.append(KEYs[str(itemsText[i][Count])])  # 通过键查找此项正确答案，并加入列表，查找原理同上
                    # noinspection PyUnboundLocalVariable
                    AllFalseAnswers.append(KEYsX[str(KEYs[str(itemsText[i][Count])])])  # 同理，只不过这里运用了一个反向查找
                    Count += 1  # Count计数器控制
            cutB()
            i += 1  # i计数器控制

            if not FalseAnswersKey:  # not FalseAnswersKey相当于FalseAnswersKey == [],如果此条件为True,那说明全部回答正确，直接略过错题更正部分
                continue
            else:  # 如果有错题：
                ct = 0  # 初始化ct计数器
                while ct < len(FalseAnswersKey):  # 根据错误答案的个数进行错误改正
                    ct += 1  # 计数器控制骑脸（滑稽）
                    print(f'请输入第{ct}个错误答案的改正:', end='\t')  # 输出~
                    AS = input()  # 用AS存储回答
                    if AS == FalseAnswersKey[ct - 1]:  # 我们之前已经把错误回答的正确答案存储好了，所以这里可以很方便地直接调用啦~
                        print('  正确\n')
                        continue
                    else:
                        print(f'  错误,正确答案：{FalseAnswersKey[ct - 1]}\n')  # 回答错误就直接输出正确答案
                        continue
            cutB()

        print('错题:\n回答错误的假名：')  # 一轮结束之后的总输出，输出全部回答错误的假名
        AllFalseAnswers = ListGetAll(AllFalseAnswers)  # 使用之前定义好的函数解决AllFalseAnswers嵌套混乱的问题
        p = 0  # 这是用来控制换行的计数器
        for i in AllFalseAnswers:  # 遍历输出AllFalseAnswers的所有项
            if p < 5:
                p += 1
                print(f"「{str(i)}」", end='\t')
            elif p == 5:
                p = 0
                print()
                print(f"「{str(i)}」", end='\t')
                p += 1
        del p  # 习惯性删除计数器

        cutB()

cutA()
print('是不是该去背日语了（滑稽）')
