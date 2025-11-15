"""
   A tk string variable that stores every string.
   But during a get method call the value of the string var will be validated.
   An invalid string value generates a ValueError exceptions.
"""
import tkinter as tk


class MyStringVar(tk.StringVar):
    def __init__(self, check_func, gen_info, value=""):
        self.check = check_func
        self.gen_info = gen_info
        tk.StringVar.__init__(self, value=value)

    def get(self):
        return self.check(tk.StringVar.get(self))

    def get_info(self):
        try:
            return self.gen_info(self.get())
        except ValueError:
            return ""
