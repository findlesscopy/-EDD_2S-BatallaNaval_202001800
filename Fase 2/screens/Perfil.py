import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.font import BOLD
import util.generic as utl


class Perfil:

    def editar(self):
        pass

    def eliminar(self):
        pass

    def __init__(self, usuario):
        self.ventana = tk.Tk()
        self.ventana.title('Perfil')
        self.ventana.geometry('500x500')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)
        utl.centrar_ventana(self.ventana,500,500)
        

        frame_form = tk.Frame(self.ventana, bd=0, relief=tk.SOLID, bg = '#fcfcfc')
        frame_form.pack(side=tk.LEFT,expand= tk.YES, fill = tk.BOTH)
        

        frame_form_top = tk.Frame(frame_form, height=50, bd=0, relief=tk.SOLID, bg='#fcfcfc')
        frame_form_top.pack(side=tk.TOP, fill=tk.X)
        title = tk.Label(frame_form_top, text="Usuario: "+usuario, font=('Optima', 20), fg="#666a88", bg='#fcfcfc', pady=20)
        title.pack(expand=tk.YES, fill=tk.BOTH)


        etiqueta_nick = tk.Label(frame_form_top, text="Nick", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_nick.pack(fill=tk.X, padx=20, pady=5)
        self.nick = ttk.Entry(frame_form_top, font=('Optima', 14))
        self.nick.pack(fill=tk.X, padx=20, pady=10)

        etiqueta_password = tk.Label(frame_form_top, text="Password", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_password.pack(fill=tk.X, padx=20, pady=5)
        self.password = ttk.Entry(frame_form_top, font=('Optima', 14))
        self.password.pack(fill=tk.X, padx=20, pady=10)

        etiqueta_edad = tk.Label(frame_form_top, text="Edad", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_edad.pack(fill=tk.X, padx=20, pady=5)
        self.edad = ttk.Entry(frame_form_top, font=('Optima', 14))
        self.edad.pack(fill=tk.X, padx=20, pady=10)

        btn_editar = tk.Button(frame_form_top, text="Editar", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.editar)
        btn_editar.pack(fill=tk.X, padx=20, pady=20)
        btn_editar.bind("<Return>", (lambda event: self.editar()))

        btn_eliminar = tk.Button(frame_form_top, text="Eliminar Cuenta", font=('Optima', 15), bg='#E64D2C', bd=0, fg="#fff", command=self.eliminar)
        btn_eliminar.pack(fill=tk.X, padx=20, pady=20)
        btn_eliminar.bind("<Return>", (lambda event: self.eliminar()))
        # end frame_form_fill
        self.ventana.mainloop()