from decimal import Decimal
from .constants import Axis


def rectIntersect(item1, item2, x, y):#平面矩形相交
    d1 = item1.getDimension()
    d2 = item2.getDimension()

    cx1 = item1.position[x] + d1[x]/2
    cy1 = item1.position[y] + d1[y]/2
    cx2 = item2.position[x] + d2[x]/2
    cy2 = item2.position[y] + d2[y]/2

    ix = max(cx1, cx2) - min(cx1, cx2)
    iy = max(cy1, cy2) - min(cy1, cy2)

    return ix < (d1[x]+d2[x])/2 and iy < (d1[y]+d2[y])/2#至少两个维度发生重叠（矩形平面相交）


def intersect(item1, item2):#货物空间重叠（两货物三个维度均有rectintersect现象）
    return (
        rectIntersect(item1, item2, Axis.WIDTH, Axis.HEIGHT) and
        rectIntersect(item1, item2, Axis.HEIGHT, Axis.DEPTH) and
        rectIntersect(item1, item2, Axis.WIDTH, Axis.DEPTH)
    )


def getLimitNumberOfDecimals(number_of_decimals):#小数位数限制
    return Decimal('1.{}'.format('0' * number_of_decimals))


def set2Decimal(value, number_of_decimals=0):
    number_of_decimals = getLimitNumberOfDecimals(number_of_decimals)#得到小数数量限制

    return Decimal(value).quantize(number_of_decimals)#十进制 针对具体数值量化小数位数
