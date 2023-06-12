import cvxpy as cp
import numpy as np

class point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    #规定坐标之间的减法
    def __sub__(self, other):
        return point(self.x - other.x, self.y - other.y)

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

    # Calculate distances between each point
    distances = one_To_Another(points)

    # Define problem variables
    n = len(points)
    stations = cp.Variable(n, boolean=True)

    # Define problem constraints
    constraints = []
    for i in range(n):
        # Each point is covered by at least one station
        constraints.append(cp.sum(stations * distances[i, :]) >= 1)
        # Each station covers at most 5 points
        constraints.append(cp.sum(stations) <= 5)

    # Define problem objective
    obj = cp.sum(stations)

    # Define and solve optimization problem
    problem = cp.Problem(cp.Minimize(obj), constraints)
    problem.solve()

    # Extract solution
    station = []
    for i in range(n):
        if stations.value[i] > 0.5:
            station.append(i)

    # Print results
    print("最小供应站的个数：", len(station))
    for i, s in enumerate(station):
        print(f"第{i+1}个供应站的位置：({points[s].x}, {points[s].y})")