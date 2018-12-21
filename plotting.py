


import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from scipy import stats


# Data for plotting


absc = []
ordo = []

f = open("example.txt", "r")
for line in f:
  buff = ""
  for l in line:
      if l=="/":
          n=int(buff)
          buff=""
      else:
          buff += l
  absc.append(n)
  ordo.append(float(buff))
          

fig, ax = plt.subplots()
ax.plot(absc, ordo)


slope, intercept, r_value, p_value, std_err = stats.linregress(absc,ordo)

ax.plot(absc,[intercept+slope*x for x in absc])

ax.set(xlabel='Graph Size', ylabel='Time (s)',
       title='Time taken by the greedy algorithm')
ax.grid()


fig.savefig("test.png")
plt.show()