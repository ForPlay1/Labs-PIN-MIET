import matplotlib.pyplot as plt
from scipy.optimize import minimize
import sympy as sp
import numpy as np
x,y = sp.symbols('x y')
f_expr = x**2 + 12*x*y + 2*y**2
phi_expr = 4*x**2+y**2-25
title = "Задача (1С): $z = x^2 + 12xy + 2y^2$, $4x^2 + y^2 = 25$"
x_range = np.linspace(-5, 5, 100)
y_range = np.linspace(-5, 5, 100)

f_grad = [sp.diff(f_expr, var) for var in (x, y)]
uncond_pts = sp.solve(f_grad, (x, y), dict=True)
types = []
f_xx = sp.diff(f_expr, x, 2)
f_yy = sp.diff(f_expr, y, 2)
f_xy = sp.diff(f_expr, x, y)

H = sp.Matrix([[f_xx, f_xy], [f_xy, f_yy]])
det_H = H.det()
for pt in uncond_pts:
    A_val = float(f_xx.subs(pt))
    det_val = float(det_H.subs(pt))
    z_val = float(f_expr.subs(pt))
    
    if det_val > 0:
        res_type = "min" if A_val > 0 else "max"
    elif det_val < 0:
        res_type = "Saddle point"
    else:
        res_type = "undefined"
    types.append(res_type)

lam = sp.symbols('lam')
L = f_expr + lam * phi_expr
L_grad = [sp.diff(L, var) for var in (x, y, lam)]
cond_pts = sp.solve(L_grad, (x, y, lam), dict=True)
types = []
for pt in cond_pts:
    subss = {x: pt[x], y: pt[y], lam: pt[lam]}
    matr = sp.Matrix([[0, sp.diff(phi_expr, x).subs(subss), sp.diff(phi_expr, y).subs(subss)],
                      [sp.diff(phi_expr, x).subs(subss), sp.diff(L, x, x).subs(subss), sp.diff(L, x, y).subs(subss)],
                      [sp.diff(phi_expr, y).subs(subss), sp.diff(L, x, y).subs(subss), sp.diff(L, y, y).subs(subss)]])
    det = -matr.det()
    if det > 0:
        types.append("min")
        print(f"Точка (x={pt[x]}, y={pt[y]}) - условный минимум.")
    elif det < 0:
        types.append("max")
        print(f"Точка (x={pt[x]}, y={pt[y]}) - условный максимум.")
    else:
        types.append("indeterminate")
        print(f"Точка (x={pt[x]}, y={pt[y]}) - неопределенный тип экстремума.")

X, Y = np.meshgrid(x_range, y_range)
f_func = sp.lambdify((x, y), f_expr, 'numpy')
Z = f_func(X, Y)

fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.6, antialiased=True)

x_c = np.linspace(-2.5, 2.5, 10000)
y_c = np.sqrt(25 - 4*x_c**2)

z_c = f_func(x_c, y_c)
ax.plot(x_c, y_c, z_c, color='red', lw=3, label=r'Кривая ограничения $\phi(x,y)=0$')
ax.plot(x_c, -y_c, f_func(x_c, -y_c), color='red', lw=3)

for pt in uncond_pts:
    zv = float(f_expr.subs(pt))
    color = 'blue' if types[uncond_pts.index(pt)] == "min" else 'magenta' if types[uncond_pts.index(pt)] == "max" else 'yellow' if types[uncond_pts.index(pt)] == "Saddle point" else 'gray'
    ax.scatter(float(pt[x]), float(pt[y]), zv, color=color, s=100, label='Безусл. экстремум')

for pt in cond_pts:
    zv = float(f_expr.subs({x: pt[x], y: pt[y]}))
    color = 'magenta' if types[cond_pts.index(pt)] == "max" else 'cyan' if types[cond_pts.index(pt)] == "min" else 'yellow'
    ax.scatter(float(pt[x]), float(pt[y]), zv, color=color, s=100, marker='*', label='Усл. экстремум')

ax.set_title(title)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.view_init(elev=25, azim=40)

handles, labels = ax.get_legend_handles_labels()
by_label = dict(zip(labels, handles))
ax.legend(by_label.values(), by_label.keys())

plt.show()