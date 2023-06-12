class RotationType:#六个旋转类型（摆放方式）
    RT_WHD = 0
    RT_HWD = 1
    RT_HDW = 2
    RT_DHW = 3
    RT_DWH = 4
    RT_WDH = 5

    ALL = [RT_WHD, RT_HWD, RT_HDW, RT_DHW, RT_DWH, RT_WDH]
    # un upright or un updown
    Notupdown = [RT_WHD,RT_HWD]#不可翻转（WH面平行于XOY面）
    '''
    
     #NotSideLay=
    #Noterect=
    #放置方式要求
    updown1=[RT_WHD,RT_HWD]#0,1  (0,1)
    updown2=[RT_WDH,RT_DWH]#5,4  (4,5)
    updown3=[RT_HDW,RT_DHW]#2,3  (2,3)
    updown4=[RT_WHD,RT_HWD,RT_WDH,RT_DWH]#0,1,5,4 (0,1,4,5)
    updown5=[RT_WHD,RT_HWD,RT_HDW,RT_DHW]#0,1,2,3 (0,1,2,3)
    updown6=[RT_WDH,RT_DWH,RT_HDW,RT_DHW]#5,4,2,3 (2,3,4,5)
    updown7=[RT_WHD,RT_HWD,RT_HDW,RT_DHW,RT_DWH,RT_WDH]#(0,1,2,3,4,5)
    '''

 #可立放1：RT_WHD,RT_HWD
 #可侧放2：RT_WDH,RT_DWH
 #可倒放3：RT_HDW,RT_DHW
 #合并：1 2 3 12 13 23 123  分别对应输入参数updown=1 2 3 4 5 6 7

class Axis:#三个轴方向
    WIDTH = 0
    HEIGHT = 1
    DEPTH = 2

    ALL = [WIDTH, HEIGHT, DEPTH]

