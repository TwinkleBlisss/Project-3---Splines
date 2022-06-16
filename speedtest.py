import matplotlib.pyplot as plt
import numpy as np


def Arrays(func):
    mas = [float(line.strip()) for line in func]
    X = mas[:int(len(mas) / 2)]
    Y = mas[int(len(mas) / 2):len(mas)]
    return X, Y


func1 = open('C:\\Users\\honor\\Desktop\\func1.txt', 'r')
X1, Y1 = Arrays(func1)
func1.close()
func2 = open('C:\\Users\\honor\\Desktop\\func2.txt', 'r')
X2, Y2 = Arrays(func2)
func2.close()


fig = plt.figure()

ax1 = fig.add_subplot(121)
plt.plot(X1, Y1, color='orange', label='func1')
plt.plot(X2, Y2, color='blue', label='func2')
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.grid()


spline1 = open('C:\\Users\\honor\\Desktop\\spline1.txt', 'r')
X_spline1, Y_spline1 = Arrays(spline1)
spline1.close()
spline2 = open('C:\\Users\\honor\\Desktop\\spline2.txt', 'r')
X_spline2, Y_spline2 = Arrays(spline2)
spline2.close()
point = open('C:\\Users\\honor\\Desktop\\intersection_point.txt', 'r')
intersection_point = [float(line.strip()) for line in point]
point.close()


ax2 = fig.add_subplot(122)
plt.plot(X1, Y1, color='red', label='spline1')
plt.plot(X2, Y2, color='green', label='spline2')
plt.scatter(intersection_point[0], intersection_point[1], linewidth=3, marker='x', color='purple')
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.grid()

plt.show()
