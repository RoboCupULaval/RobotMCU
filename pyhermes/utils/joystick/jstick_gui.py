#!/usr/bin/python
from jstick import Joystick
import tkinter as tk
import numpy as np


class StickCanvas(tk.Canvas):
    def update(self, coords):
        coords = np.copy(coords)
        norm = np.linalg.norm(coords)
        if norm > 1:
            coords = coords / norm
        coords *= 50
        self.delete("all")
        width = self.winfo_width() * 0.95
        height = self.winfo_height() * 0.95
        lwidth = self.winfo_width() - width
        lheight = self.winfo_height() - height
        self.create_oval(0 + lwidth/2, 0 + lheight/2,
                         width + lwidth/2, height + lheight/2)
        self.create_oval(coords[0] - 5 + width/2 + lwidth/2,
                         coords[1] - 5 + width/2 + lwidth/2,
                         coords[0] + 5 + height/2 + lheight/2,
                         coords[1] + 5 + height/2 + lheight/2,
                         fill='black')


class ButtonCanvas(tk.Canvas):

    def __init__(self, *args, **kwargs):
        super(ButtonCanvas, self).__init__(*args, **kwargs)
        self.color = 'white'

    def update(self, value):
        self.delete("all")
        width = self.winfo_width() * 0.9
        height = self.winfo_height() * 0.9
        lwidth = self.winfo_width() - width
        lheight = self.winfo_height() - height

        if value == 1:
            color = self.color
        else:
            color = None

        self.create_oval(0 + lwidth/2, 0 + lheight/2,
                         width + lwidth/2, height + lheight/2,
                         outline=self.color, fill=color, width=5)


class Application(tk.Frame):

    def createWidgets(self):
        self.lstick_canvas = StickCanvas(self, width=100, height=100)
        self.lstick_canvas.grid(row=0, column=0, columnspan=2, rowspan=2)
        self.rstick_canvas = StickCanvas(self, width=100, height=100)
        self.rstick_canvas.grid(row=0, column=2, columnspan=2, rowspan=2)
        self.xbutton_canvas = ButtonCanvas(self, width=50, height=50)
        self.xbutton_canvas.grid(row=0, column=4, columnspan=1, rowspan=2)
        self.xbutton_canvas.color = 'blue'
        self.abutton_canvas = ButtonCanvas(self, width=50, height=50)
        self.abutton_canvas.grid(row=1, column=5, columnspan=1, rowspan=1)
        self.abutton_canvas.color = 'green'
        self.ybutton_canvas = ButtonCanvas(self, width=50, height=50)
        self.ybutton_canvas.grid(row=0, column=5, columnspan=1, rowspan=1)
        self.ybutton_canvas.color = 'yellow'
        self.bbutton_canvas = ButtonCanvas(self, width=50, height=50)
        self.bbutton_canvas.grid(row=0, column=6, columnspan=1, rowspan=2)
        self.bbutton_canvas.color = 'red'
        self.ltrigger_canvas = ButtonCanvas(self, width=50, height=100)
        self.ltrigger_canvas.grid(row=0, column=7, columnspan=1, rowspan=2)
        self.rtrigger_canvas = ButtonCanvas(self, width=50, height=100)
        self.rtrigger_canvas.grid(row=0, column=8, columnspan=1, rowspan=2)

    def update(self):
        self.lstick_canvas.update(self.joystick.buttons['stick1'].coords)
        self.rstick_canvas.update(self.joystick.buttons['stick2'].coords)
        self.xbutton_canvas.update(self.joystick.buttons['x'].value)
        self.abutton_canvas.update(self.joystick.buttons['a'].value)
        self.ybutton_canvas.update(self.joystick.buttons['y'].value)
        self.bbutton_canvas.update(self.joystick.buttons['b'].value)
        self.ltrigger_canvas.update(self.joystick.buttons['l'].value)
        self.rtrigger_canvas.update(self.joystick.buttons['r'].value)
        self.after(10, self.update)

    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.pack()
        self.createWidgets()
        self.joystick = Joystick()
        self.after(10, self.update)

root = tk.Tk()
app = Application(master=root)
app.mainloop()
root.destroy()
