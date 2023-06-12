def lagrange_basis(x_data, i, x):
    """计算第 i 个拉格朗日基函数在 x 处的值"""
    basis = 1.0
    for j in range(len(x_data)):
        if j != i:
            basis *= (x - x_data[j]) / (x_data[i] - x_data[j])
    return basis


def lagrange_interpolation(x_data, y_data, x):
    """计算拉格朗日插值多项式在 x 处的值"""
    n = len(x_data)
    lagrange_poly = 0.0
    for i in range(n):
        basis = lagrange_basis(x_data, i, x)
        lagrange_poly += y_data[i] * basis
    return lagrange_poly
# 示例数据点



if __name__ == "__main__":
    print("请输入待输入数据组的个数,输入完成后点击回车：")
    n = int(input())
    print("请输入x和y的数据，x输入完后点击回车进行y的输入，以空格作为分隔符：")
    x_data = list(map(float, input().split()))
    y_data = list(map(float, input().split()))
    print("请输入待插值的x的值：")
    # 待插值的 x 值
    x = eval(input())

    # 调用拉格朗日插值函数计算插值结果
    result = lagrange_interpolation(x_data, y_data, x)
    print("在 x = {:.2f} 处的拉格朗日插值结果为: {:.4f}".format(x, result))

