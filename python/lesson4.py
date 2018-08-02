# !/usr/bin/python
# coding:utf-8
# 文件操作
# f = open("txt/test.txt")
# for line in f:
    # print line
# 一次全部读取
# lines = f.readlines()
# for line in lines:
    # print line
# f = open("txt/test.txt", 'w')
# # f.write("next stage\n")
# f.writelines(['aaa\n', 'bbb\n', 'ccc\n'])
# f.writelines(['aaa', 'bbb', 'ccc'])
# f.close()
# 上下文管理器,在with块后 f会被释放 有效避免文件泄漏
# with open('txt/text.txt') as f:
    # print f.readlines()
# 文件系统的操作
# import os.path

# mypath = '/home/waykwin/WorkSpace'
# # print os.path.basename(mypath)
# # print os.path.dirname(mypath)
# # 分离 路径,文件名
# # print os.path.split(mypath)
# # 分离 路径文件,扩展名 识别类型 很有用
# # print os.path.splitext(mypath)
# # 记住 参数顺序和含义(固定的)
# for basedir, dirnames, filenames in os.walk(mypath):
    # print 'basedir: ', basedir
    # print 'dirnames: ', dirnames
    # print 'filenames: ', filenames
# import os
# import sys
# # if和else 不影响作用域
# if len(sys.argv) < 2:
    # path = '.'
# else:
    # path = sys.argv[1]
# for f in os.listdir(path):
    # print f
# try:
    # a = [1, 2, 3]
    # print a[100]
# except IndexError as e:
    # print "catch", e
# except IOError as e:
    # print e
# else:
    # print "code runk ok"
# print 'hehe'
# try:
    # a = [1, 2, 3]
    # print a[100]
#强烈不建议这么做
# except Exception as e:
    # print "wrong"
a = [1, 2, 3]
try:
    a = [1, 2, 3]
    print a[100]
except IndexError as e:
    print e
finally:
    print 'runing at finally'
# 抛出异常
# raise
# def Divide(x, y):
    # if y == 0:
        # return 0, False
    # return x / y, True
def Divide(x, y):
    if y == 0:
        raise Exception('Divide Zero')
    return x / y
