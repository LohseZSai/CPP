import numpy as np
from scipy.integrate import quad
import matplotlib.pyplot as plt

def integrand(t):
    return (1/(2*np.pi)**0.5)*np.exp(-(t**2/2))

def function(x):
    result, _ = quad(integrand, -np.inf, x)
    return result

x = np.linspace(-5, 5, 1000)
y = [function(i) for i in x]

plt.plot(x, y)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Function')
plt.show()