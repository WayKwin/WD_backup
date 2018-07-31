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
f = open("txt/test.txt", 'w')
# f.write("next stage\n")
# f.writelines(['aaa\n', 'bbb\n', 'ccc\n'])
f.writelines(['aaa', 'bbb', 'ccc'])
f.close()
