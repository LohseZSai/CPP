import cvxpy as cp

# 年业务量和一次性费用
sales_volume = [400, 500, 600, 700, 800]
setup_cost = [100, 80, 90, 70]
max_sales = [350, 250, 300, 200]
operating_cost = [7.5, 4.0, 6.5, 3.0]

# 临时中断和重新恢复代理关系的费用
suspend_cost = [5, 3, 4, 2]
restore_cost = [5, 4, 1, 9]

# 建立代理关系的变量
setup = cp.Variable((4,), boolean=True)

# 每个代理关系每年的销售量
sales = cp.Variable((5, 4), nonneg=True)

# 每个代理关系每年是否处于中断状态的变量
suspend = cp.Variable((5, 4), boolean=True)

# 模型目标: 最小化代理关系的建立费用和运行费用，以及临时中断和重新恢复代理关系的费用
objective = cp.Minimize(
    cp.sum(setup_cost * setup) + cp.sum(operating_cost * sales.sum(axis=0)) + 
    cp.sum(suspend_cost * suspend) + cp.sum(restore_cost * (1 - suspend))
)

# 添加约束条件
constraints = [
    # 每年的销售量不超过每个代理关系的最大销售量
    sales <= max_sales,
    
    # 每年的销售量不超过代理关系已经建立的情况下的最大销售量
    sales <= cp.reshape(sales_volume, (5, 1)),
    
    # 如果代理关系没有建立，销售量应该为0
    sales <= cp.reshape(setup * max_sales, (1, 4)),
    
    # 如果代理关系已经中断，销售量应该为0
    sales <= cp.reshape((1 - suspend) * max_sales, (5, 4)),
    
    # 每年的销售量应该等于该年代理关系建立的情况下的销售量
    sales.sum(axis=1) == sales_volume,
    
    # 如果代理关系已经中断，每年的销售量应该为0
    cp.sum(sales * suspend, axis=0) == 0,
    
    # 建立代理关系的数量不能超过3个
    cp.sum(setup) <= 3,
]

# 求解问题
prob = cp.Problem(objective, constraints)
prob.solve()

# 输出结果
print("最小成本: ", prob.value)
print("代理关系的建立情况: ", setup.value.astype(int))
print("销售量: ", sales.value.astype(int))
print("是否中断代理关系: ", suspend.value.astype(int))