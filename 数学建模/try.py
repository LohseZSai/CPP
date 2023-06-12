import cvxpy as cp
import numpy as np
from itertools import combinations



class point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __sub__(self, other):
        return point(self.x - other.x, self.y - other.y)
    
    def __str__(self):
        return f"({self.x}, {self.y})"

# 计算任意两点间的距离
def Distance_Calculate(point1,point2):
    dis = ((point1.x - point2.x)**2 + (point1.y - point2.y)**2)**(1/2)
    return dis

#计算每个点和其他点之间的距离
def one_To_Another(points):
    #用二维数组存储距离数据
    distance = np.zeros((len(points), len(points)))
    for ind1,i in enumerate(points):
        for ind2,j in enumerate(points):
            realdis = Distance_Calculate(i,j)
            distance[ind1][ind2] = realdis
    return distance


if __name__ == "__main__":
    # Define the points
    points = [point(9.4888,5.6817), point(8.7928,10.3868), point(11.5960,3.9294), point(11.5643,4.4325), point(5.6756,9.9658), point(9.8497,17.6632), point(9.1756,6.1517), point(13.1385,11.8569), point(15.4663,8.8721), point(15.5464,15.5868)]
    combinations = list(combinations(points, 2))
    for c in combinations:
        count = 0
        for i in points:
            if Distance_Calculate(i,c[0]) > 10: count += 1
            if Distance_Calculate(i,c[1]) > 10: count += 1 
        print(f"组合: {c[0]}和{c[1]},超出个数为{count}")