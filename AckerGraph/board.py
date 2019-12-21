import matplotlib.pyplot as plt

# create a 8" x 8" board
fig = plt.figure(figsize=[8,8])
fig.patch.set_facecolor((.8,1,1))

ax = fig.add_subplot(111)

# draw the grid
for x in range(15):
    ax.plot([x, x], [0,14], 'k')
for y in range(15):
    ax.plot([0, 14], [y,y], 'k')

# scale the axis area to fill the whole figure
ax.set_position([0,0,1,1])

# get rid of axes and everything (the figure background will show through)
ax.set_axis_off()

# scale the plot area conveniently (the board is in 0,0..18,18)
ax.set_xlim(-1,15)
ax.set_ylim(-1,15)

# draw Go stones at (10,10) and (13,16)
s1, = ax.plot(7,7,'o',markersize=12, markeredgecolor=(1,1,1), markerfacecolor='k', markeredgewidth=2)
s2, = ax.plot(3,3,'o',markersize=12, markeredgecolor=(1,1,1), markerfacecolor='k', markeredgewidth=2)
s2, = ax.plot(3,11,'o',markersize=12, markeredgecolor=(1,1,1), markerfacecolor='k', markeredgewidth=2)
s2, = ax.plot(11,3,'o',markersize=12, markeredgecolor=(1,1,1), markerfacecolor='k', markeredgewidth=2)
s2, = ax.plot(11,11,'o',markersize=12, markeredgecolor=(1,1,1), markerfacecolor='k', markeredgewidth=2)

for i in range(15):
	plt.text(i - 0.15, -0.4, chr(i + 65), fontsize=12, \
            style='italic',color='royalblue')

for i in range(15):
	plt.text(-0.6, i - 0.15, i + 1, fontsize=12, \
            style='italic',color='royalblue')
plt.savefig("board1.png", format = "png", bbox_inches = "tight", transparent = True, dpi = 1200)
plt.show()
