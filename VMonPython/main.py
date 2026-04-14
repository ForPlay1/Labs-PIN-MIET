import numpy as np
import matplotlib.pyplot as plt

# Создаем сетку
x = np.linspace(0, 1, 30)
y = np.linspace(0, 1, 30)
X, Y = np.meshgrid(x, y)

# Поверхности
Z_roof = X * Y      # Крыша: z = xy
Z_floor = np.zeros_like(X) # Пол: z = 0

fig = plt.figure(figsize=(12, 8))
ax = fig.add_subplot(111, projection='3d')

# 1. Рисуем пол (z=0) и крышу (z=xy) с прозрачностью
ax.plot_surface(X, Y, Z_floor, color='gray', alpha=0.3, label='z = 0')
ax.plot_surface(X, Y, Z_roof, color='blue', alpha=0.4, label='z = xy')

# 2. Рисуем цилиндры (стены) x = y^2 и y = x^2
# Для y = x^2 (зеленая стена)
z_vals = np.linspace(0, 1, 30)
X_c1, Z_c1 = np.meshgrid(x, z_vals)
Y_c1 = X_c1**2
ax.plot_surface(X_c1, Y_c1, Z_c1, color='green', alpha=0.3)

# Для x = y^2 (красная стена)
Y_c2, Z_c2 = np.meshgrid(y, z_vals)
X_c2 = Y_c2**2
ax.plot_surface(X_c2, Y_c2, Z_c2, color='red', alpha=0.3)

# Оформление
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Объем V: Пол, Крыша и две боковые стенки-цилиндра')

# Угол обзора
ax.view_init(elev=30, azim=45)

plt.show()