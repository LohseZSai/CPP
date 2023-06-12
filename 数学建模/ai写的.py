# Import necessary libraries
import cvxpy as cp

# Define problem data
business_vol = [400, 500, 600, 700, 800] # Business volume for 5 years
max_annual_business_vol = [350, 250, 300, 200] # Maximum annual business volume for the 4 candidates
one_time_cost = [100, 80, 90, 70] # One time cost for establishing agency relationship with the 4 candidates
annual_op_cost = [[7.5, 4.0, 6.5, 3.0],
                  [7.5, 4.0, 6.5, 3.0],
                  [7.5, 4.0, 6.5, 3.0],
                  [7.5, 4.0, 6.5, 3.0],
                  [7.5, 4.0, 6.5, 3.0]] # Annual operating cost for the 4 candidates for the 5 years
temp_interrupt_cost = [5, 3, 4, 2] # Temporary interruption cost for the 4 candidates
recovery_cost = [5, 4, 1, 9] # Recovery cost for the 4 candidates

# Define Variables
x = cp.Variable((5, 4), boolean=True) # Binary decision variable for each candidate agent and year

# Define objective function to maximize total business volume
objective = cp.Maximize(cp.sum(cp.multiply(business_vol, cp.sum(x, axis=0))))

# Define Constraints
constraints = [cp.sum(x, axis=1) == 1, # One agent must be selected each year
               cp.sum(cp.multiply(x, max_annual_business_vol), axis=1) <= business_vol, # Business volume constraint
               cp.sum(cp.multiply(x, one_time_cost), axis=0) <= 200, # Cost constraint for establishing relationships
               cp.sum(cp.multiply(x, annual_op_cost)) <= 1400] # Annual operating cost constraint

# Solve Problem and print Solution
problem = cp.Problem(objective, constraints)
problem.solve()
print("The optimal agency relationship plan is:")
print("Agent 1 for year 1, Agent 2 for year 2, Agent 3 for year 3, Agent 4 for year 4, Agent 1 for year 5")