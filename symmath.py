from re import sub as resub
from sympy import *
from sympy.solvers import solve

def fixLatex(bad_latex):
    good_latex = bad_latex
    good_latex = good_latex.replace(r"{1}", "1")
    good_latex = good_latex.replace(r"{2}", "2")
    good_latex = good_latex.replace(r"\left", "")
    good_latex = good_latex.replace(r"\right", "")
    good_latex = good_latex.replace(r"\theta_1{ (t  )}", r"\theta_1")
    good_latex = good_latex.replace(r"\theta_2{ (t  )}", r"\theta_2")
    good_latex = good_latex.replace(r"\frac{d^2}{d t^2}  \theta_1", r"\ddot{\theta_1}")
    good_latex = good_latex.replace(r"\frac{d^2}{d t^2}  \theta_2", r"\ddot{\theta_2}")
    good_latex = good_latex.replace(r"\frac{d}{d t} \theta_1", r"\dot{\theta_1}")
    good_latex = good_latex.replace(r"\frac{d}{d t} \theta_2", r"\dot{\theta_2}")
    good_latex = resub(r'\\frac\{(.*?)}\{?(\d+?)}?', r'\\frac{1}{\2}\1 ', good_latex)
    return good_latex

def makeCplusplus(python_math):
    #substitute variables names
    python_math = python_math.replace("m_1", "mass(0)")
    python_math = python_math.replace("m_2", "mass(1)")
    python_math = python_math.replace("l_1", "length(0)")
    python_math = python_math.replace("l_2", "length(0)")
    python_math = python_math.replace("m_1", "mass(0)")
    #substitute values of theta/thetadot
    python_math = python_math.replace("Derivative(theta_1(t), t)", "velocity(0)")
    python_math = python_math.replace("Derivative(theta_2(t), t)", "velocity(1)")
    python_math = python_math.replace("theta_1(t)", "position(0)")
    python_math = python_math.replace("theta_2(t)", "position(1)")
    #fix exponents
    python_math = python_math.replace("velocity(0)**2", "pow(velocity(0), 2.0)")
    python_math = python_math.replace("velocity(1)**2", "pow(velocity(1), 2.0)")
    python_math = python_math.replace("cos(position(0) - position(1))**2", "pow(cos(position(0) - position(1)), 2.0)")
    return python_math

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
print("Linear v^2 for the free stick:")
print(fixLatex(latex(freevsquared)))
freelinearK = Rational(1, 2)*m2*freevsquared
print("Linear kinetic energy for the free stick:")
print(fixLatex(latex(freelinearK)))

#Rotational KE for anchored stick
anchoredK = Rational(1, 6)*m1*l1**Rational(2)*vel1**Rational(2)

#Rotational KE for free stick
freeK = Rational(1, 24)*m2*l2**Rational(2)*vel2**Rational(2)

anchoredU = m1*g*y1
freeU = m2*g*y2

lagrangian = simplify(freelinearK + freeK + anchoredK - anchoredU - freeU)

print("Here's the lagrangian:")
print(fixLatex(latex(lagrangian)))
print('\n'*5)

solution = solve([
    Derivative(Derivative(lagrangian, vel1).doit(), t).doit() - Derivative(lagrangian, theta1).doit(),
    Derivative(Derivative(lagrangian, vel2).doit(), t).doit() - Derivative(lagrangian, theta2).doit()
], acc1, acc2)
solution1 = simplify(solution[acc1])
solution2 = simplify(solution[acc2])
print(fixLatex(latex(solution1)))
print()
print(makeCplusplus(solution1))
print('\n'*2)
print(fixLatex(latex(solution2)))
print()
print(makeCplusplus(solution2))
