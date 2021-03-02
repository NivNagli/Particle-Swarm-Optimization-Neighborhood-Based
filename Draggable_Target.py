"""
Author: Niv Nagli
Project: Drone_Rescue
File: Draggable_Target.py
Contact Information: itsniv@gmail.com
Sources I used:
https://stackoverflow.com/questions/21654008/matplotlib-drag-overlapping-points-interactively
https://pyshine.com/
https://stackoverflow.com/questions/29379502/how-get-a-x-y-position-pointing-with-mouse-in-a-interactive-plot-python
"""

import matplotlib.pyplot as plt
import matplotlib.patches as patches
import matplotlib

matplotlib.use('TKAgg')  # needed only on mac environment

container = plt.figure(figsize=(4, 4))
plt.xlim([-500, 500])
plt.ylim([-500, 500])
ax = container.add_subplot(111)


class Draggable_Target:
    lock = None

    def __init__(self, point):  # Builder
        self.background = None
        self.ID = None
        self.point = point
        self.press = None

    def getID(self):
        return self.ID

    def setID(self, ID):
        self.ID = ID

    def connect(self):
        # connect the event listeners
        self.in_release = self.point.figure.canvas.mpl_connect('button_release_event', self.on_release)
        self.in_motion = self.point.figure.canvas.mpl_connect('motion_notify_event', self.on_motion)
        self.in_press = self.point.figure.canvas.mpl_connect('button_press_event', self.on_press)

    def on_release(self, event):
        # on release will reset the data
        if Draggable_Target.lock is not self:
            return

        self.press = None
        Draggable_Target.lock = None
        self.point.set_animated(False)
        self.background = None
        self.point.figure.canvas.draw()

    def on_motion(self, event):
        if Draggable_Target.lock is not self:
            return
        if event.inaxes != self.point.axes: return
        self.point.center, xpress, ypress = self.press
        dx = event.xdata - xpress
        dy = event.ydata - ypress
        self.point.center = (self.point.center[0] + dx, self.point.center[1] + dy)
        file = open("target.csv", 'w')
        x = self.point.center[0]
        y = self.point.center[1]
        # Borders check:
        if x < -500 or x > 500:
            if x < 0:
                x = -500
            else:
                x = 500
        if y < -500 or y > 500:
            if y < 0:
                x = -500
            else:
                y = 500
        file.write(str(x) + ',' + str(y)) # update the new Target

        canvas = self.point.figure.canvas
        axes = self.point.axes
        matplotlib.use('TkAgg')
        canvas.restore_region(self.background)
        axes.draw_artist(self.point)
        canvas.blit(axes.bbox)
        canvas.blit(False)

    def on_press(self, event):
        if event.inaxes != self.point.axes: return
        if Draggable_Target.lock is not None: return
        contains, attrd = self.point.contains(event)
        if not contains: return
        self.press = self.point.center, event.xdata, event.ydata
        Draggable_Target.lock = self
        canvas = self.point.figure.canvas
        axes = self.point.axes
        self.point.set_animated(True)
        canvas.draw()
        self.background = canvas.copy_from_bbox(self.point.axes.bbox)
        axes.draw_artist(self.point)
        canvas.blit(axes.bbox)

    def disconnect(self):
        # 'disconnect all the stored connection ids'
        self.point.figure.canvas.mpl_disconnect(self.in_press)
        self.point.figure.canvas.mpl_disconnect(self.in_release)
        self.point.figure.canvas.mpl_disconnect(self.in_motion)


drs = []
circles = [patches.Circle((10, -10), 20, label='Move the target by click ', fc='k', color='k', alpha=1)]
cnt = 0
for circ in circles:
    ax.add_patch(circ)
    dr = Draggable_Target(circ)
    dr.setID(cnt)
    dr.connect()
    drs.append(dr)
    cnt += 1
plt.legend()
plt.show()
