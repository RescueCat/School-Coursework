from tkinter import *
from tkinter import filedialog
import os
import KNearestNeighbor
import randomforest
import MultinominalLogisticRegression


# TODO: Make another frame that shows results
# TODO: Figure out exe stuff

def start_command(fileNam, algo):
    print(fileNam)
    print(algo)


class dmGUI:
    def browse_file(self):
        currdir = os.getcwd()
        self.filename = filedialog.askopenfilename(initialdir=currdir, filetypes=(
            ("Data files", "*.data"), ("CSV files", "*.csv"), ("All files", "*")))

    def start_algo(self):
        if self.algorithm.get() == "K-Nearest Neighbor":
            window = Toplevel(root)

            # Text Area
            T = Text(window, height=30, width=100)
            T.pack()

            # Close Button
            close_button2 = Button(window, text="Close", command=lambda: window.destroy())
            close_button2.pack()

            KNearestNeighbor.print_function_name(self.algorithm.get())
            KNearestNeighbor.execute_Algo(self.filename, T)
        if self.algorithm.get() == "Random Forests":
            randomforest.print_function_name(self.algorithm.get())
            window = Toplevel(root)

            # Text Area
            T = Text(window, height=30, width=100)
            T.pack()

            # Close Button
            close_button2 = Button(window, text="Close", command=lambda: window.destroy())
            close_button2.pack()
            randomforest.execute_Algo(self.filename, T)
        if self.algorithm.get() == "Multinominal Logistic Regression":
            window = Toplevel(root)

            # Text Area
            T = Text(window, height=30, width=100)
            T.pack()

            # Close Button
            close_button2 = Button(window, text="Close", command=lambda: window.destroy())
            close_button2.pack()
            MultinominalLogisticRegression.print_function_name(self.algorithm.get())
            MultinominalLogisticRegression.execute_Algo(self.filename, T)
        # print(self.filename)
        # print(self.algorithm.get())

    def __init__(self, master):
        self.master = master

        # Title
        master.title("GUI for Data Mining Project")

        # Frame Size
        # You can set the geometry attribute to change the root windows size
        root.geometry("500x150")  # You want the size of the app to be 500x500
        root.resizable(0, 0)  # Don't allow resizing in the x or y direction

        self.back = Frame(master=root)
        self.back.pack_propagate(0)  # Don't allow the widgets inside to determine the frame's width / height
        self.back.pack(fill=BOTH, expand=1)  # Expand the frame to fill the root window

        # Select Algorithm
        self.label = Label(self.back, text="Please Select Algorithm")
        self.label.pack()

        self.algorithm = StringVar(master)
        self.algorithm.set("K-Nearest Neighbor")  # default value

        self.w = OptionMenu(self.back, self.algorithm, "K-Nearest Neighbor", "Random Forests",
                            "Multinominal Logistic Regression")
        self.w.pack()

        # Select Dataset
        self.label2 = Label(self.back, text="Please Select Data Set")
        self.label2.pack()

        # Browse Button
        self.broButton = Button(self.back, text='Browse', command=lambda: self.browse_file())
        self.broButton.pack()

        # StartButton
        self.start_button = Button(self.back, text="Start", command=lambda: self.start_algo())
        self.start_button.pack()

        # Close
        self.close_button = Button(self.back, text="Close", command=master.quit)
        self.close_button.pack()


root = Tk()
my_gui = dmGUI(root)
root.mainloop()
