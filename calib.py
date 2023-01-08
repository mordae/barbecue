#!/usr/bin/env python

from scipy.optimize import curve_fit
import numpy


def curve(x, a, b, c, d):
    return (x * x * x * a) + (x * x * b) + (x * c) + d


xs = [3.108,  2.988,  2.793,   1.600,   0.900,   0.450]
ys = [3.000, 20.200, 36.500, 100.000, 200.000, 300.000]

er = [0.100,  0.100,  0.100,   1.000,   5.000,   5.000]


popt, pcov = curve_fit(curve, xs, ys, sigma=er, absolute_sigma=True)

for x, y1 in zip(xs, ys):
    y2 = curve(x, *popt)
    print('%7.3f %7.3f %7.3f %7.3f' % (x, y1, round(y2, 3), round(y2 - y1, 3)))

print()
print('double a = %.3f;' % popt[0])
print('double b = %.3f;' % popt[1])
print('double c = %.3f;' % popt[2])
print('double d = %.3f;' % popt[3])
print('return (v * v * v * a) + (v * v * b) + (v * c) + d;')


# vim:set sw=4 ts=4 et:
