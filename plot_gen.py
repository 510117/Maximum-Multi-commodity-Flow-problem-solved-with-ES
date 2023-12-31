import matplotlib
import matplotlib.pyplot as plt

# 10 21558 21562
# 40 25340 24400
# 70 35864 35176
# 100 51945 51408

x = ["10", "$10^2$", "$10^3$", "$10^4$", "$10^5$"]
y1 = [4862, 12429, 17905, 18156, 18156]
y2 = [4265, 8309, 12034, 15150, 17721]
y3 = [18156, 18156, 18156, 18156, 18156]


fig, ax = plt.subplots(figsize = (7, 6), dpi = 600)
fontsize = 22


ax.plot(x, y1, linewidth=2.0)
ax.plot(x, y2, linewidth=2.0)
ax.plot(x, y3, linewidth=2.0)
AlgoName = ["(1+1)-ES, mutate a path", "(1+1)-ES, mutate all edges", "Greedy"]

plt.xticks(fontsize = fontsize)
plt.yticks(fontsize = fontsize)
plt.xlabel(fontsize = fontsize, xlabel = "Number of Generarion for ES")
plt.ylabel(fontsize = fontsize, ylabel = "Fitness")

andy_theme = {
    "xtick.labelsize": 20,
    "ytick.labelsize": 20,
    "axes.labelsize": 20,
    "axes.titlesize": 20,
    # "font.family": "Times New Roman",
    "mathtext.it": "Times New Roman:italic",
}
matplotlib.rcParams.update(andy_theme)

plt.subplots_adjust(top = 0.97)
plt.subplots_adjust(left = 0.2)
plt.subplots_adjust(right = 0.97)
plt.subplots_adjust(bottom = 0.13)

plt.legend(
    AlgoName,
    # loc = 10,
    # bbox_to_anchor = (0.4, 1.25),
    prop = {"size": fontsize, "family": "Times New Roman"},
    frameon = "False",
    labelspacing = 0.2,
    handletextpad = 0.2,
    handlelength = 1,
    columnspacing = 0.2,
    ncol = 1,
    facecolor = "None",
)

plt.savefig("Fig_Gen.eps")
plt.savefig("Fig_Gen.jpg")
