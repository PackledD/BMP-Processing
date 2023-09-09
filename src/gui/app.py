import tkinter as tk
import tkinter.simpledialog as sd
import tkinter.filedialog as fd
import tkinter.messagebox as box
import tkinter.font as font
from PIL import ImageTk, Image
from bmp_image import BMP


class App(tk.Tk):

    def __init__(self, width, height):
        super(App, self).__init__()
        self.geometry(f"{width}x{height}")
        self.resizable(width=0, height=0)
        self.title("BMP processing")
        self.font = font.Font(family="Arial", size=14)
        self.file = None
        self.work_bmp = None
        self.image = None
        self.area_picture = tk.Frame(self, width=800, height=580)
        self.area_choose = tk.Frame(self, width=200, height=580, bg="pink")
        self.btn_open = tk.Button(self.area_choose, text="Open image", width=15, font=self.font, command=self.ask_and_open)
        self.btn_apply = tk.Button(self.area_choose, text="Apply action", width=15, font=self.font, command=self.apply_action)
        self.btn_save = tk.Button(self.area_choose, text="Save image", width=15, font=self.font, command=self.save_result)
        self.action = tk.IntVar(value=0)

    def build_app(self):
        self.area_picture.place(x=10, y=10)
        self.area_choose.place(x=820, y=10)
        self.btn_open.place(x=10, y=450)
        self.btn_apply.place(x=10, y=490)
        self.btn_save.place(x=10, y=530)
        text = [
            "No action",
            "Grayscale",
            "Sobelian X",
            "Sobelian Y",
            "Sobelian",
            "Laplasian positive",
            "Laplasian negative",
            "Laplasian diagonal",
            "Gaussian",
            "Border highlight",
            "Median filter"
        ]
        for i in range(len(text)):
            rbtn = tk.Radiobutton(self.area_choose, text=text[i], value=i, font=self.font, variable=self.action)
            rbtn.place(x=10, y=15 + 30 * i)

    def ask_file(self):
        self.file = fd.askopenfilename(
            initialdir=".",
            title="Choose bmp image",
            filetypes=(("BMP image", "*.bmp"),)
        )

    def open_file(self, filename):
        if not self.file:
            return
        self.work_bmp = BMP(filename)
        if not self.work_bmp.read():
            pass
        else:
            self.work_bmp.write(".temp_bmp")
            self.show_image()

    def ask_and_open(self):
        self.ask_file()
        self.open_file(self.file)

    def show_image(self):
        self.area_picture.destroy()
        self.area_picture = tk.Frame(self, width=800, height=580)
        img = Image.open(".temp_bmp")
        img = ImageTk.PhotoImage(img)
        width = img.width() if img.width() < 800 else 800
        height = img.height() if img.height() < 580 else 580
        draw = ScrollableImage(self.area_picture, image=img, width=width, height=height)
        draw.pack()
        self.area_picture.place(x=10, y=10)

    def apply_action(self):
        state = self.action.get()
        self.open_file(self.file)
        if not self.work_bmp:
            box.showerror(message="Image is not opened, nothing to process")
            return
        if state == 1:
            self.work_bmp.grayscale()
        elif state == 2:
            self.work_bmp.sobelian_x()
        elif state == 3:
            self.work_bmp.sobelian_y()
        elif state == 4:
            self.work_bmp.sobelian()
        elif state == 5:
            self.work_bmp.laplasian_pos()
        elif state == 6:
            self.work_bmp.laplasian_neg()
        elif state == 7:
            self.work_bmp.laplasian_diag()
        elif state == 8:
            radius = sd.askinteger(title="Radius", prompt="Enter radius in px:")
            if (radius < 0):
                box.showerror(message="Radius can not be negative")
                return
            deviation = sd.askfloat(title="Deviation", prompt="Enter deviation:")
            if (deviation < 0):
                box.showerror(message="Deviation can not be negative")
                return
            self.work_bmp.gaussian(radius, deviation)
        elif state == 9:
            treshold = sd.askinteger(title="Treshold", prompt="Enter treshold:")
            self.work_bmp.border_highlight(treshold)
        elif state == 10:
            radius = sd.askinteger(title="Radius", prompt="Enter radius in px:")
            if (radius < 0):
                box.showerror(message="Radius can not be negative")
                return
            self.work_bmp.median_filter(radius)
        self.work_bmp.write(".temp_bmp")
        self.show_image()

    def save_result(self):
        if self.work_bmp:
            to_write = fd.asksaveasfilename(
                initialdir=".",
                title="Choose bmp image",
                filetypes=(("BMP image", "*.bmp"),)
            )
            self.work_bmp.write(to_write)
        else:
            box.showerror(message="Image is not opened, nothing to save")


class ScrollableImage(tk.Frame):
    def __init__(self, master=None, **kw):
        self.image = kw.pop('image', None)
        sw = kw.pop('scrollbarwidth', 10)
        super(ScrollableImage, self).__init__(master=master, **kw)
        self.cnvs = tk.Canvas(self, highlightthickness=0, **kw)
        self.cnvs.create_image(0, 0, anchor='nw', image=self.image)
        self.v_scroll = tk.Scrollbar(self, orient='vertical', width=sw)
        self.h_scroll = tk.Scrollbar(self, orient='horizontal', width=sw)
        self.cnvs.grid(row=0, column=0, sticky='nsew')
        self.h_scroll.grid(row=1, column=0, sticky='ew')
        self.v_scroll.grid(row=0, column=1, sticky='ns')
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)
        self.cnvs.config(xscrollcommand=self.h_scroll.set, yscrollcommand=self.v_scroll.set)
        self.v_scroll.config(command=self.cnvs.yview)
        self.h_scroll.config(command=self.cnvs.xview)
        self.cnvs.config(scrollregion=self.cnvs.bbox('all'))


app = App(1030, 600)
app.build_app()
app.mainloop()
