def divided_difference(x_data, y_data):
    """计算牛顿插值法中的差商"""
    n = len(x_data)
    f = []
    for i in range(n):
        f.append(y_data[i])
    for j in range(1, n):
        for i in range(n-1, j-1, -1):
            f[i] = (f[i] - f[i-1]) / (x_data[i] - x_data[i-j])
    return f


def newton_interpolation(x_data, y_data, x):
    """计算牛顿插值多项式在 x 处的值"""
    n = len(x_data)
    f = divided_difference(x_data, y_data)
    newton_poly = f[0]
    for i in range(1, n):
        term = f[i]
        for j in range(i):
            term *= (x - x_data[j])
        newton_poly += term
    return newton_poly


if __name__ == "main":
    x_data = [0, 0.1, 0.2, 0.3, 0.4]
    y_data = [0.5, 0.5398, 0.5793, 0.6179, 0.6554]

    # 待插值的 x 值
    x = 0.13

    # 调用牛顿插值函数计算插值结果
    result = newton_interpolation(x_data, y_data, x)
    print("在 x = {:.2f} 处的牛顿插值结果为: {:.4f}".format(x, result))