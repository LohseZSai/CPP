##力扣的求矩阵距离的题
""" 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。"""
##对于这个题我的想法是，根据输入的单词顺序遍历，然后每个字母获得其相邻的值（也就是横一格和竖一格是否与下一个字母相同来判断）
import numpy as np
board,word= np.array(eval(input())),input()
v = np.where(board == 'f')
a = [list(enumerate(i)) for i in board]
print(v,str(v[1]))