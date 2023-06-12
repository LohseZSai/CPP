from .constants import RotationType, Axis
from .auxiliary_methods import intersect, set2Decimal
import numpy as np
# required to plot a representation of Bin and contained items 绘制
from matplotlib.patches import Rectangle,Circle
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.art3d as art3d#3d图绘制
from collections import Counter
DEFAULT_NUMBER_OF_DECIMALS = 0#默认小数位数
START_POSITION = [0, 0, 0]#起始位置
Gap=set2Decimal(20)#货物虚拟延长长度（为留出货物间隙）



class Item:#货物类
    def __init__(self, partno,name,typeof, WHD, weight, level, loadbear, updown, color):
        ''' '''
        self.partno = partno#货号
        self.name = name# # type of item货物类型
        self.typeof = typeof#cube or cylinder
        self.width = WHD[0]#WHD[0]
        self.height = WHD[1]#WHD[1]
        self.depth = WHD[2]
        self.weight = weight
        # Packing Priority level ,choose 1-3装载优先级
        self.level = level
        # loadbear
        self.loadbear = loadbear#用优先级对承载能力较高的项目进行排序。数字越大，优先级越高。
        # Upside down? True or False能否倒置
        #self.updown = updown if typeof == 'cube' else False#（其他不规则几何体货箱不可倒置）
        self.updown = updown
        # Draw item color
        self.color = color
        self.rotation_type = 0#旋转类型（摆放方式）
        self.position = START_POSITION#货物位置
        self.number_of_decimals = DEFAULT_NUMBER_OF_DECIMALS

    def formatNumbers(self, number_of_decimals):
        ''' '''
        self.width = set2Decimal(self.width, number_of_decimals)
        self.height = set2Decimal(self.height, number_of_decimals)
        self.depth = set2Decimal(self.depth, number_of_decimals)
        self.weight = set2Decimal(self.weight, number_of_decimals)
        self.number_of_decimals = number_of_decimals

    def string(self):
        ''' '''
        return "%s(%sx%sx%s, weight: %s) pos(%s) rt(%s) vol(%s)" % (
            self.partno, self.width, self.height, self.depth, self.weight,
            self.position, self.rotation_type, self.getVolume()
        )

    def getVolume(self):#计算体积
        ''' '''
        return set2Decimal(self.width * self.height * self.depth, self.number_of_decimals)

    def getMaxArea(self):#获得最大面（长宽高进行排序，降序，前两个棱长相乘）
        ''' '''
        a = sorted([self.width,self.height,self.depth],reverse=True) if self.updown == True else [self.width,self.height,self.depth]
    
        return set2Decimal(a[0] * a[1] , self.number_of_decimals)

    def getDimension(self):#根据具体旋转方式确定在xyz坐标轴上对应的具体摆放长度
        ''' rotation type '''
        if self.rotation_type == RotationType.RT_WHD:
            dimension = [self.width+Gap, self.height+Gap, self.depth]
        elif self.rotation_type == RotationType.RT_HWD:
            dimension = [self.height+Gap, self.width+Gap, self.depth]
        elif self.rotation_type == RotationType.RT_HDW:
            dimension = [self.height+Gap, self.depth+Gap, self.width]
        elif self.rotation_type == RotationType.RT_DHW:
            dimension = [self.depth+Gap, self.height+Gap, self.width]
        elif self.rotation_type == RotationType.RT_DWH:
            dimension = [self.depth+Gap, self.width+Gap, self.height]
        elif self.rotation_type == RotationType.RT_WDH:
            dimension = [self.width+Gap, self.depth+Gap, self.height]
        else:
            dimension = []

        return dimension

#corner :container coner 集装箱角 设置容器角大小 cm
#put_type put_type=0 or 1 (0 : general & 1 : open top) Added the order of placing items. There are two placement methods. Set the bin to open top or general, and the returned results are sorted according to this method.
class Bin:#集装箱类
    def __init__(self, partno, WHD, max_weight,corner=0,put_type=0):
        ''' '''
        self.partno = partno
        self.width = WHD[0]-200#门口剩余20cm
        self.height = WHD[1]-20#角落剩余2cm
        self.depth = WHD[2]
        self.max_weight = max_weight#最大承重
        self.corner = corner#集装箱角件，不需则可默认0
        self.items = []#放置具体货物
        self.fit_items = np.array([[0,WHD[0],0,WHD[1],0,0]])#在x、y、z轴上，各轴上的起始点以放置平面xoy为参考
        self.unfitted_items = []#未放置的不合适货物，
        self.number_of_decimals = DEFAULT_NUMBER_OF_DECIMALS
        self.fix_point = False#固定点摆放
        self.put_type = put_type#（默认通用）针对开顶、通用两种集装箱类型：put_type=0 or 1 (0 : general & 1 : open top)添加了放置项目的顺序。有两种放置方法。将 bin 设置为开顶或通用，返回结果按照此方法排序。
        # used to put gravity distribution
        self.gravity = []#放置重力分布

    def formatNumbers(self, number_of_decimals):#数字格式
        ''' '''
        self.width = set2Decimal(self.width, number_of_decimals)
        self.height = set2Decimal(self.height, number_of_decimals)
        self.depth = set2Decimal(self.depth, number_of_decimals)
        self.max_weight = set2Decimal(self.max_weight, number_of_decimals)
        self.number_of_decimals = number_of_decimals

    def string(self):#输出string信息格式
        ''' '''
        return "%s(%sx%sx%s, max_weight:%s) vol(%s)" % (
            self.partno, self.width, self.height, self.depth, self.max_weight,
            self.getVolume()
        )

    def getVolume(self):#计算体积
        ''' '''
        return set2Decimal(
            self.width * self.height * self.depth, self.number_of_decimals
        )

    def getTotalWeight(self):#计算放入Bin中的总重量
        ''' '''
        total_weight = 0

        for item in self.items:
            total_weight += item.weight

        return set2Decimal(total_weight, self.number_of_decimals)

    def putItem(self, item, pivot,axis=None):#放置货物
        ''' put item in bin '''
        fit = False
        valid_item_position = item.position
        item.position = pivot#放置点
        rotate = RotationType.ALL if item.updown == True else RotationType.Notupdown#根据放置方式，能否倒置
        '''
        针对放置方向要求，还没改完
         def getupdown(self)
            if item.updown==[1,0,0]:
                rotate=RotationType.updown1
            elif item.updown==[0,1,0]:
                rotate=RotationType.updown2
            elif item.updown==[0,0,1]:
                rotate=RotationType.updown3
            elif item.updown==[1,1,0]:
                rotate=RotationType.updown4
            elif item.updown==[1,0,1]:
                rotate=RotationType.updown5
            elif item.updown==[0,1,1]:
                rotate=RotationType.updown6
            elif item.updown==[1,1,1]:
                rotate=RotationType.updown7
            else:
                rotate=[]
                
            return rotate
        
        '''



        
        
        
        
        






        for i in range(0, len(rotate)):#针对不同的摆放方式
            item.rotation_type = i
            dimension = item.getDimension()
            # rotatate旋转
            if (
                self.width < pivot[0] + dimension[0] or#长宽高限制
                self.height< pivot[1] + dimension[1] or
                self.depth < pivot[2] + dimension[2]
            ):
                continue

            fit = True

            for current_item_in_bin in self.items:
                if intersect(current_item_in_bin, item):
                    fit = False
                    break

            if fit:
                # cal total weight总重量
                if self.getTotalWeight() + item.weight > self.max_weight and item.weight<3000:#重量约束
                    fit = False
                    return fit

                if item.partno == 'Dyson DC34 Animal8':#货号可忽略
                    print(123)
                    # self.fix_point = False

                if self.fix_point == True :#通过使用固定点解决有物品漂浮在空中，

                    [w,h,d] = dimension#对应至x、y、z轴的长度
                    [x,y,z] = [float(pivot[0]),float(pivot[1]),float(pivot[2])]#放置点坐标

                    for i in range(3):
                        # fix height
                        y = self.checkHeight([x,x+float(w),y,y+float(h),z,z+float(d)])#三轴方向的起始点
                        # fix width
                        x = self.checkWidth([x,x+float(w),y,y+float(h),z,z+float(d)])
                        # fix depth
                        z = self.checkDepth([x,x+float(w),y,y+float(h),z,z+float(d)])

                    self.fit_items = np.append(self.fit_items,np.array([[x,x+float(w),y,y+float(h),z,z+float(d)]]),axis=0)#按行
                    item.position = [set2Decimal(x),set2Decimal(y),set2Decimal(z)]
                    
                self.items.append(item)
#这是审查了货物是否悬空？
            if not fit:
                item.position = valid_item_position

            return fit

        if not fit:
            item.position = valid_item_position#若不放，仍valid_item_position有效可放货物位置

        return fit

    def checkDepth(self,unfix_point):
        ''' fix item position z '''#确定货物位置z
        z_ = [[0,0],[float(self.depth),float(self.depth)]]
        for j in self.fit_items:
            # creat x set
            x_bottom = set([i for i in range(int(j[0]),int(j[1]))])#self.fit_items = np.array([[0,WHD[0],0,WHD[1],0,0]])#set无序性、确定性、不重复性；集合（set）是一个无序的不重复元素的集，基本功能包括关系测试和消除重复元素。是可变的数据类型。集合数据类型的核心在于自动去重。
            x_top = set([i for i in range(int(unfix_point[0]),int(unfix_point[1]))])
            # creat y set
            y_bottom = set([i for i in range(int(j[2]),int(j[3]))])
            y_top = set([i for i in range(int(unfix_point[2]),int(unfix_point[3]))])
            # find intersection on x set and y set.求x轴和y轴的交点？

            if len(x_bottom & x_top) != 0 and len(y_bottom & y_top) != 0 :
                z_.append([float(j[4]),float(j[5])])
        top_depth = unfix_point[5] - unfix_point[4]
        # find diff set on z_.#查找z轴上的差异
        z_ = sorted(z_, key = lambda z_ : z_[1])#将z_按z_第1维度进行排序
        for j in range(len(z_)-1):
            if z_[j+1][0] -z_[j][1] >= top_depth:
                return z_[j][1]
        return unfix_point[4]

    def checkWidth(self,unfix_point):
        ''' fix item position x ''' #确定货物位置x
        x_ = [[0,0],[float(self.width),float(self.width)]]
        for j in self.fit_items:
            # creat z set
            z_bottom = set([i for i in range(int(j[4]),int(j[5]))])
            z_top = set([i for i in range(int(unfix_point[4]),int(unfix_point[5]))])
            # creat y set
            y_bottom = set([i for i in range(int(j[2]),int(j[3]))])
            y_top = set([i for i in range(int(unfix_point[2]),int(unfix_point[3]))])
            # find intersection on z set and y set.
            if len(z_bottom & z_top) != 0 and len(y_bottom & y_top) != 0 :
                x_.append([float(j[0]),float(j[1])])
        top_width = unfix_point[1] - unfix_point[0]
        # find diff set on x_bottom and x_top.
        x_ = sorted(x_,key = lambda x_ : x_[1])#sort() 和sorted() 函数中，key=lambda x:x[] 即表示待排序对象按第几维度进行排序。其中 x 可以为任意字母，方括号 [] 内为维数，根据需要设置。
        for j in range(len(x_)-1):
            if x_[j+1][0] -x_[j][1] >= top_width:
                return x_[j][1]
        return unfix_point[0]
    
    def checkHeight(self,unfix_point):
        '''fix item position y '''
        y_ = [[0,0],[float(self.height),float(self.height)]]
        for j in self.fit_items:
            # creat x set
            x_bottom = set([i for i in range(int(j[0]),int(j[1]))])
            x_top = set([i for i in range(int(unfix_point[0]),int(unfix_point[1]))])
            # creat z set
            z_bottom = set([i for i in range(int(j[4]),int(j[5]))])
            z_top = set([i for i in range(int(unfix_point[4]),int(unfix_point[5]))])
            # find intersection on x set and z set.
            if len(x_bottom & x_top) != 0 and len(z_bottom & z_top) != 0 :
                y_.append([float(j[2]),float(j[3])])
        top_height = unfix_point[3] - unfix_point[2]
        # find diff set on y_bottom and y_top.
        y_ = sorted(y_,key = lambda y_ : y_[1])
        for j in range(len(y_)-1):
            if y_[j+1][0] -y_[j][1] >= top_height:
                return y_[j][1]

        return unfix_point[2]

    def addCorner(self):#添加集装箱角件
        '''add container coner '''#添加集装箱角件（容器角） 相当于将集装箱角件也看成货物item ，类比Item类传入相关参数
        if self.corner != 0 :
            corner = set2Decimal(self.corner)
            corner_list = []
            for i in range(8):#0,1,2,3,4,5,6,7
                a = Item(
                    partno='corner{}'.format(i),#将i传入corner{}中 共8个角件，第i个
                    name='corner', 
                    typeof='cube',
                    WHD=(corner,corner,corner), #正方体
                    weight=0, #零重量
                    level=0, #优先级数字越小，优先级越高。
                    loadbear=0, 
                    updown=True, 
                    color='#000000')

                corner_list.append(a)
            return corner_list

    def putCorner(self,info,item):#放置角件
        '''put coner in bin '''#将角件放入货箱中
        fit = False
        x = set2Decimal(self.width - self.corner)
        y = set2Decimal(self.height - self.corner)
        z = set2Decimal(self.depth - self.corner)
        pos = [[0,0,0],[0,0,z],[0,y,z],[0,y,0],[x,y,0],[x,0,0],[x,0,z],[x,y,z]]#八个集装箱角件的放置点（左下角），0基准面+箱体长宽高-corner基准面
        item.position = pos[info]
        self.items.append(item)#将其添至货箱items[]中

        corner = [float(item.position[0]),float(item.position[0])+float(self.corner),float(item.position[1]),float(item.position[1])+float(self.corner),float(item.position[2]),float(item.position[2])+float(self.corner)]#在三个坐标轴方向的正方体六点(以左下角为基准的六个范围)对应坐标数值

        self.fit_items = np.append(self.fit_items,np.array([corner]),axis=0)
        return

    def clearBin(self):
        ''' clear item which in bin '''#清除bin中的货物
        self.items = []
        self.fit_items = np.array([[0,self.width,0,self.height,0,0]])#回到初始设置
        return


class Packer:#进行打包·
    def __init__(self):
        ''' '''
        self.bins = []
        self.items = []
        self.unfit_items = []
        self.total_items = 0
        self.binding = []#捆绑型货物
        # self.apex = []顶点顶端

    def addBin(self, bin):#添加货箱
        ''' '''
        return self.bins.append(bin)

    def addItem(self, item):#添加货物
        ''' '''
        self.total_items = len(self.items) + 1

        return self.items.append(item)

    def pack2Bin(self, bin, item,fix_point):#具体打包货物至集装箱
        ''' pack item to bin '''
        fitted = False
        bin.fix_point = fix_point#固定点

        # first put item on (0,0,0) , if corner exist ,first add corner in box. #首先将货物放置在初始位置原点处，如果存在集装箱角件，则先在集装箱中将角件加入
        if bin.corner != 0 and not bin.items:#添加角件
            corner_lst = bin.addCorner()
            for i in range(len(corner_lst)) :
                bin.putCorner(i,corner_lst[i])

        elif not bin.items:
            response = bin.putItem(item, item.position)#货物放置

            if not response:
                bin.unfitted_items.append(item)#未放入的不合适货物
            return

        for axis in range(0, 3):
            items_in_bin = bin.items
            for ib in items_in_bin:
                pivot = [0, 0, 0]
                w, h, d = ib.getDimension()
                if axis == Axis.WIDTH:
                    pivot = [ib.position[0] + w,ib.position[1],ib.position[2]]
                elif axis == Axis.HEIGHT:
                    pivot = [ib.position[0],ib.position[1] + h,ib.position[2]]
                elif axis == Axis.DEPTH:
                    pivot = [ib.position[0],ib.position[1],ib.position[2] + d]
                    
                if bin.putItem(item, pivot, axis):#根据在货物的xyz三个轴方向的哪个方向面进行放置，更新放置坐标
                    fitted = True
                    break
            if fitted:
                break
        if not fitted:
            bin.unfitted_items.append(item)

    def sortBinding(self,bin):#类型绑定  （货物捆绑）
        ''' sorted by binding '''#按绑定排序
        b,front,back = [],[],[]
        for i in range(len(self.binding)):
            b.append([]) 
            for item in self.items:
                if item.name in self.binding[i]:
                    b[i].append(item)
                elif item.name not in self.binding:
                    if len(b[0]) == 0 and item not in front:
                        front.append(item)
                    elif item not in back and item not in front:
                        back.append(item)

        min_c = min([len(i) for i in b])
        
        sort_bind =[]
        for i in range(min_c):
            for j in range(len(b)):
                sort_bind.append(b[j][i])
        
        for i in b:
            for j in i:
                if j not in sort_bind:
                    self.unfit_items.append(j)

        self.items = front + sort_bind + back#一起放入
        return

    def putOrder(self):
        '''Arrange the order of items '''#货物放置顺序安排
        r = []
        for i in self.bins:
            # open top container#开顶集装箱
            if i.put_type == 2:
                i.items.sort(key=lambda item: item.position[0], reverse=False)#按第几个维度进行排序，升序
                i.items.sort(key=lambda item: item.position[1], reverse=False)
                i.items.sort(key=lambda item: item.position[2], reverse=False)
            # general container#普通集装箱 默认put_type=1
            elif i.put_type == 1:
                i.items.sort(key=lambda item: item.position[1], reverse=False)
                i.items.sort(key=lambda item: item.position[2], reverse=False)
                i.items.sort(key=lambda item: item.position[0], reverse=False)
            else :
                pass
        return

    # Deviation Of Cargo gravity distribution重力分布
    def gravityCenter(self):
        ''' 
        Deviation Of Cargo gravity distribution货物重力分布偏差 通过规则划分小区域
        ''' 
        w = int(self.bins[0].width)
        h = int(self.bins[0].height)
        d = int(self.bins[0].depth)

        area1 = [set(range(0,w//2+1)),set(range(0,h//2+1)),0]#除后取整+1
        area2 = [set(range(w//2+1,w+1)),set(range(0,h//2+1)),0]
        area3 = [set(range(0,w//2+1)),set(range(h//2+1,h+1)),0]
        area4 = [set(range(w//2+1,w+1)),set(range(h//2+1,h+1)),0]
        area = [area1,area2,area3,area4]#以xoy平面为基准平均划分出四片区域area[j][2]放对应区域重量
        for i in self.bins[0].items:

            x_st = int(i.position[0])#货物放置起点坐标
            y_st = int(i.position[1])
            if i.rotation_type == 0:#WHD
                x_ed = int(i.position[0] + i.width)#按具体摆放方式放置后的在该方向上的终点坐标
                y_ed = int(i.position[1] + i.height)
            elif i.rotation_type == 1:#HWD
                x_ed = int(i.position[0] + i.height)
                y_ed = int(i.position[1] + i.width)
            elif i.rotation_type == 2:#HDW
                x_ed = int(i.position[0] + i.height)
                y_ed = int(i.position[1] + i.depth)
            elif i.rotation_type == 3:#DHW
                x_ed = int(i.position[0] + i.depth)
                y_ed = int(i.position[1] + i.height)
            elif i.rotation_type == 4:#DWH
                x_ed = int(i.position[0] + i.depth)
                y_ed = int(i.position[1] + i.width)
            elif i.rotation_type == 5:#WDH
                x_ed = int(i.position[0] + i.width)
                y_ed = int(i.position[1] + i.depth)

            x_set = set(range(x_st,int(x_ed)+1))#x起始状态范围集合
            y_set = set(range(y_st,y_ed+1))#y范围集合

            # cal gravity distribution
            for j in range(len(area)):
                if x_set.issubset(area[j][0]) and y_set.issubset(area[j][1]) : #x_set.issubset(area[j][0])：判断x_set中的所有元素是否包含area[j][0]中在#issubset() 方法用于判断集合的所有元素是否都包含在指定集合中，如果是则返回 True，不是则返回 False。
                    area[j][2] += int(i.weight)
                    break
                # include x and !include y
                elif x_set.issubset(area[j][0]) == True and y_set.issubset(area[j][1]) == False and len(y_set & area[j][1]) != 0 : 
                    y = len(y_set & area[j][1]) / (y_ed - y_st) * int(i.weight)#按在该区域的面积比例权重取该区域重量
                    area[j][2] += y
                    if j >= 2 :
                        area[j-2][2] += (int(i.weight) - x)#另俩取补？
                    else :
                        area[j+2][2] += (int(i.weight) - y)
                    break
                # include y and !include x
                elif x_set.issubset(area[j][0]) == False and y_set.issubset(area[j][1]) == True and len(x_set & area[j][0]) != 0 : 
                    x = len(x_set & area[j][0]) / (x_ed - x_st) * int(i.weight)#同理
                    area[j][2] += x
                    if j >= 2 :
                        area[j-2][2] += (int(i.weight) - x)
                    else :
                        area[j+2][2] += (int(i.weight) - x)
                    break
                # !include x and !include y
                elif x_set.issubset(area[j][0])== False and y_set.issubset(area[j][1]) == False and len(y_set & area[j][1]) != 0  and len(x_set & area[j][0]) != 0 :
                    all = (y_ed - y_st) * (x_ed - x_st)
                    y = len(y_set & area[0][1])
                    y_2 = y_ed - y_st - y
                    x = len(x_set & area[0][0])
                    x_2 = x_ed - x_st - x
                    area[0][2] += x * y / all * int(i.weight)#四个区域同样按面积比例权重取重量
                    area[1][2] += x_2 * y / all * int(i.weight)
                    area[2][2] += x * y_2 / all * int(i.weight)
                    area[3][2] += x_2 * y_2 / all * int(i.weight)
                    break
            
        r = [area[0][2],area[1][2],area[2][2],area[3][2]]#四个区域对应区域的重量情况
        result = []
        for i in r :
            result.append(round(i / sum(r) * 100,2))#结果四舍五入保留两位小数，放四个区域的重量占比
        return result

    def pack(self, bigger_first=False,distribute_items=False,fix_point=True,binding=[],number_of_decimals=DEFAULT_NUMBER_OF_DECIMALS):
        '''pack master func '''
        #打包函数 pack为在各种打包优先机制下的打包函数；pack2Bin为具体将货物货物打包至集装箱的方法
        # set decimals设置小数位数
        for bin in self.bins:
            bin.formatNumbers(number_of_decimals)

        for item in self.items:
            item.formatNumbers(number_of_decimals)
        # add binding attribute
        self.binding = binding
        # Bin : sorted by volumn
        self.bins.sort(key=lambda bin: bin.getVolume(), reverse=bigger_first)#按集装箱体积升序排列，---bigger_first=False，reverse=bigger_first---体积大的优先放置
        # Item : sorted by volumn -> sorted by loadbear -> sorted by level -> binding
        self.items.sort(key=lambda item: item.getVolume(), reverse=bigger_first)#按货物体积升序排列
        # self.items.sort(key=lambda item: item.getMaxArea(), reverse=bigger_first)
        self.items.sort(key=lambda item: item.loadbear, reverse=True)#按货物承重升序排列
        self.items.sort(key=lambda item: item.level, reverse=False)#按货物打包优先级进行降序排列（数值越小，打包越优先）
        # sorted by binding按货物捆绑规则
        if binding != []:
            self.sortBinding(bin)

        for bin in self.bins:
            # pack item to bin
            for item in self.items:
                self.pack2Bin(bin, item,fix_point)#按照pack2Bin方法进行打包
            # no used将未使用的item从items中移除
            if distribute_items :
                for item in bin.items:
                    self.items.remove(item)

            for item in self.items.copy():
                if item in bin.unfitted_items:
                    self.items.remove(item)

            if binding != []:
                # resorted
                self.items.sort(key=lambda item: item.getVolume(), reverse=bigger_first)
                self.items.sort(key=lambda item: item.loadbear, reverse=True)
                self.items.sort(key=lambda item: item.level, reverse=False)
                self.items = self.items + bin.unfitted_items
                # clear bin
                bin.items = []
                bin.unfitted_items = self.unfit_items
                bin.fit_items = np.array([[0,bin.width,0,bin.height,0,0]])
                # repacking
                for item in self.items:
                    self.pack2Bin(bin, item,fix_point)
        # put order of items
        self.putOrder()
        # Deviation Of Cargo Gravity Center 
        self.bins[0].gravity = self.gravityCenter()



class Painter:#画图
    def __init__(self,bins):
        ''' '''
        self.items = bins.items
        self.width = bins.width
        self.height = bins.height
        self.depth = bins.depth

    def _plotCube(self, ax, x, y, z, dx, dy, dz, color='red',mode=2):
        """ Auxiliary function to plot a cube. code taken somewhere from the web.  """
        xx = [x, x, x+dx, x+dx, x]
        yy = [y, y+dy, y+dy, y, y]
        
        kwargs = {'alpha': 1, 'color': color,'linewidth':1 }
        if mode == 1 :
            ax.plot3D(xx, yy, [z]*5, **kwargs)
            ax.plot3D(xx, yy, [z+dz]*5, **kwargs)
            ax.plot3D([x, x], [y, y], [z, z+dz], **kwargs)
            ax.plot3D([x, x], [y+dy, y+dy], [z, z+dz], **kwargs)
            ax.plot3D([x+dx, x+dx], [y+dy, y+dy], [z, z+dz], **kwargs)
            ax.plot3D([x+dx, x+dx], [y, y], [z, z+dz], **kwargs)
        else :
            p = Rectangle((x,y),dx,dy,fc=color,ec='black')
            p2 = Rectangle((x,y),dx,dy,fc=color,ec='black')
            p3 = Rectangle((y,z),dy,dz,fc=color,ec='black')
            p4 = Rectangle((y,z),dy,dz,fc=color,ec='black')
            p5 = Rectangle((x,z),dx,dz,fc=color,ec='black')
            p6 = Rectangle((x,z),dx,dz,fc=color,ec='black')
            ax.add_patch(p)
            ax.add_patch(p2)
            ax.add_patch(p3)
            ax.add_patch(p4)
            ax.add_patch(p5)
            ax.add_patch(p6)
            art3d.pathpatch_2d_to_3d(p, z=z, zdir="z")
            art3d.pathpatch_2d_to_3d(p2, z=z+dz, zdir="z")
            art3d.pathpatch_2d_to_3d(p3, z=x, zdir="x")
            art3d.pathpatch_2d_to_3d(p4, z=x + dx, zdir="x")
            art3d.pathpatch_2d_to_3d(p5, z=y, zdir="y")
            art3d.pathpatch_2d_to_3d(p6, z=y + dy, zdir="y")

    def _plotCylinder(self, ax, x, y, z, dx, dy, dz, color='red',mode=2):
        """ Auxiliary function to plot a Cylinder  """
        # plot the two circles above and below the cylinder
        p = Circle((x+dx/2,y+dy/2),radius=dx/2,color=color,ec='black')
        p2 = Circle((x+dx/2,y+dy/2),radius=dx/2,color=color,ec='black')
        ax.add_patch(p)
        ax.add_patch(p2)
        art3d.pathpatch_2d_to_3d(p, z=z, zdir="z")
        art3d.pathpatch_2d_to_3d(p2, z=z+dz, zdir="z")
        # plot a circle in the middle of the cylinder
        center_z = np.linspace(0, dz, 15)
        theta = np.linspace(0, 2*np.pi, 15)
        theta_grid, z_grid=np.meshgrid(theta, center_z)
        x_grid = dx / 2 * np.cos(theta_grid) + x + dx / 2
        y_grid = dy / 2 * np.sin(theta_grid) + y + dy / 2
        z_grid = z_grid + z
        ax.plot_surface(x_grid, y_grid, z_grid,shade=False,fc=color,ec='black',alpha=1,color=color)
        
    def plotBoxAndItems(self,title=""):
        """ side effective. Plot the Bin and the items it contains. """
        fig = plt.figure()
        axGlob = plt.axes(projection='3d')

        counter = 0
        # fit rotation type
        for item in self.items:
            rt = item.rotation_type  
            x,y,z = item.position
            [w,h,d] = item.getDimension()
            color = item.color
            if item.typeof == 'cube':
                 # plot item of cube
                self._plotCube(axGlob, float(x), float(y), float(z), float(w),float(h),float(d),color=color,mode=2)
            elif item.typeof == 'cylinder':
                # plot item of cylinder
                self._plotCylinder(axGlob, float(x), float(y), float(z), float(w),float(h),float(d),color=color,mode=2)
            
            counter = counter + 1  
        # plot bin 
        self._plotCube(axGlob,0, 0, 0, float(self.width), float(self.height), float(self.depth),color='black',mode=1)

        plt.title('result')
        self.setAxesEqual(axGlob)
        plt.show()

    def setAxesEqual(self,ax):
        '''Make axes of 3D plot have equal scale so that spheres appear as spheres,
        cubes as cubes, etc..  This is one possible solution to Matplotlib's
        ax.set_aspect('equal') and ax.axis('equal') not working for 3D.
使三维图形的轴具有相等的比例，使球体呈现为球体，立方体作为立方体等。这是Matplotlib的一个可能的解决方案，ax.set_aspect('equal')和ax.axis('equal')不适用于3D。
        Input
        ax: a matplotlib axis, e.g., as output from plt.gca().'''
        x_limits = ax.get_xlim3d()
        y_limits = ax.get_ylim3d()
        z_limits = ax.get_zlim3d()

        x_range = abs(x_limits[1] - x_limits[0])
        x_middle = np.mean(x_limits)
        y_range = abs(y_limits[1] - y_limits[0])
        y_middle = np.mean(y_limits)
        z_range = abs(z_limits[1] - z_limits[0])
        z_middle = np.mean(z_limits)

        # The plot bounding box is a sphere in the sense of the infinity
        # norm, hence I call half the max range the plot radius.
        plot_radius = 0.5 * max([x_range, y_range, z_range])

        ax.set_xlim3d([x_middle - plot_radius, x_middle + plot_radius])
        ax.set_ylim3d([y_middle - plot_radius, y_middle + plot_radius])
        ax.set_zlim3d([z_middle - plot_radius, z_middle + plot_radius])

