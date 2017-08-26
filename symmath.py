from sympy import *
from sympy.solvers import solve

g, m1, m2, l1, l2, t = symbols('g m_1 m_2 l_1 l_2 t')
theta1 = Function('theta_1')(t)
theta2 = Function('theta_2')(t)
vel1 = Derivative(theta1, t)
vel2 = Derivative(theta2, t)
acc1 = Derivative(vel1, t)
acc2 = Derivative(vel2, t)

#Coordinates of CoM's
x1 = Rational(1, 2)*l1*sin(theta1)
y1 = Rational(-1, 2)*l1*cos(theta1)
x2 = l1*sin(theta1) + Rational(1, 2)*l2*sin(theta2)
y2 = -l1*cos(theta1) - Rational(1, 2)*l2*cos(theta2)

#v^2 for the CoM of the free stick
freevsquared = simplify(Derivative(x2, t).doit()**S(2) + Derivative(y2, t).doit()**S(2))
freelinearK = Rational(1, 2)*m2*freevsquared

#Rotational KE for anchored stick
anchoredK = Rational(1, 6)*m1*l1**Rational(2)*vel1**Rational(2)

#Rotational KE for free stick
freeK = Rational(1, 24)*m2*l2**Rational(2)*vel2**Rational(2)

anchoredU = m1*g*y1
freeU = m2*g*y2

lagrangian = simplify(freelinearK + freeK + anchoredK - anchoredU - freeU)

print("Here's the lagrangian:")
print(latex(lagrangian))
print('\n'*5)

solution = solve([
    Derivative(Derivative(lagrangian, vel1).doit(), t).doit() - Derivative(lagrangian, theta1).doit(),
    Derivative(Derivative(lagrangian, vel2).doit(), t).doit() - Derivative(lagrangian, theta2).doit()
], acc1, acc2)
solution1 = simplify(solution[acc1])
solution2 = simplify(solution[acc2])
print(latex(solution1))
print()
print(solution1)
print('\n'*2)
print(latex(solution2))
print()
print(solution2)
