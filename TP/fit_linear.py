import re
import numpy as np
from sklearn.linear_model import LinearRegression


calls, cmp, move, time = [], [], [], []

with open("results.txt") as f:
    for line in f:
        #
        m = re.findall(r'calls,(\d+),cmp,(\d+),move,(\d+),time,([0-9.eE+-]+)', line)
        if m:
            c, cp, mv, t = m[0]
            calls.append(int(c))
            cmp.append(int(cp))
            move.append(int(mv))
            time.append(float(t))


X = np.column_stack([calls, cmp, move])
y = np.array(time)

reg = LinearRegression(fit_intercept=False)
reg.fit(X, y)

print("Regression coefficients (time ≈ a*calls + b*cmp + c*moves):")
print(f"a (calls): {reg.coef_[0]}")
print(f"b (cmp):   {reg.coef_[1]}")
print(f"c (move):  {reg.coef_[2]}")
