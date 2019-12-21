import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import copy

fig = plt.figure(figsize=[8,8], facecolor=(1,1,.8))
ax = fig.add_subplot(111, xticks=range(19), yticks=range(19), axis_bgcolor='none', position=[.1,.1,.8,.8])
ax.grid(color='k', linestyle='-', linewidth=1)
ax.xaxis.set_tick_params(bottom='off', top='off', labelbottom='off')
ax.yaxis.set_tick_params(left='off', right='off', labelleft='off')

black_stone = mpatches.Circle((0,0), .45, facecolor='k', edgecolor=(.8,.8,.8, 1), linewidth = 2, clip_on=False, zorder=10)
white_stone = copy.copy(black_stone)
white_stone.set_facecolor((.9, .9, .9))
white_stone.set_edgecolor((.5, .5, .5))

s1 = copy.copy(black_stone)
s1.center = (18,18)
ax.add_patch(s1)

s2 = copy.copy(white_stone)
s2.center = (6,10)
ax.add_patch(s2)
