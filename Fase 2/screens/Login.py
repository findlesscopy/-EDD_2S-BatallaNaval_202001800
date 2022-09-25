import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.font import BOLD
import util.generic as utl
from screens.Admin import Admin


class Login:

    def verificar(self):
        username = self.usuario.get()
        password = self.password.get()
        if(username == "EDD" and password == "edd123"):
            self.ventana.destroy()
            Admin(username)
        else:
            messagebox.showerror(message="Invalid username or password", title="Error")



    def __init__(self):
        self.ventana = tk.Tk()
        self.ventana.title('Inicio de sesión')
        self.ventana.geometry('500x500')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)
        utl.centrar_ventana(self.ventana,500,500)
        

        frame_form = tk.Frame(self.ventana, bd=0, relief=tk.SOLID, bg = '#fcfcfc')
        frame_form.pack(side=tk.LEFT,expand= tk.YES, fill = tk.BOTH)
        

        frame_form_top = tk.Frame(frame_form, height=50, bd=0, relief=tk.SOLID, bg='black')
        frame_form_top.pack(side=tk.TOP, fill=tk.X)
        title = tk.Label(frame_form_top, text="Inicio de sesion", font=('Optima', 30), fg="#666a88", bg='#fcfcfc', pady=50)
        title.pack(expand=tk.YES, fill=tk.BOTH)

         # frame_form_fill
        frame_form_fill = tk.Frame(frame_form, height=50,  bd=0, relief=tk.SOLID, bg='#fcfcfc')
        frame_form_fill.pack(side="bottom", expand=tk.YES, fill=tk.BOTH)

        etiqueta_usuario = tk.Label(frame_form_fill, text="Usuario", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_usuario.pack(fill=tk.X, padx=20, pady=5)
        self.usuario = ttk.Entry(frame_form_fill, font=('Optima', 14))
        self.usuario.pack(fill=tk.X, padx=20, pady=10)

        etiqueta_password = tk.Label(frame_form_fill, text="Contraseña", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_password.pack(fill=tk.X, padx=20, pady=5)
        self.password = ttk.Entry(frame_form_fill, font=('Optima', 14))
        self.password.pack(fill=tk.X, padx=20, pady=10)
        self.password.config(show="*")

        inicio = tk.Button(frame_form_fill, text="Iniciar sesion", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.verificar)
        inicio.pack(fill=tk.X, padx=20, pady=20)
        inicio.bind("<Return>", (lambda event: self.verificar()))
        # end frame_form_fill
        self.ventana.mainloop()