import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.font import BOLD
import util.generic as utl

class Admin:
    
    def registrar_datos(self):
        pass

    def ver_lista(self):
        pass

    def ver_arbolB(self):
        pass

    def __init__(self):        
        self.ventana = tk.Tk()
        self.ventana.title('Admin')
        self.ventana.geometry('800x600')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)
        utl.centrar_ventana(self.ventana,1000,600)

        frame_form = tk.Frame(self.ventana, bd=0, relief=tk.SOLID, bg = '#fcfcfc')
        frame_form.pack(side=tk.LEFT,expand= tk.YES, fill = tk.BOTH)

        frame_form_top = tk.Frame(frame_form, height=50, bd=0, relief=tk.SOLID, bg='black')
        frame_form_top.pack(side=tk.TOP, fill=tk.X)
        title = tk.Label(frame_form_top, text="Bienvenido: Admin", font=('Optima', 30), fg="#666a88", bg='#fcfcfc', pady=50)
        title.pack(expand=tk.YES, fill=tk.BOTH)


        # frame_form_fill
        frame_form_fill = tk.Frame(frame_form, height=50,  bd=0, relief=tk.SOLID, bg='#fcfcfc')
        frame_form_fill.pack(side="bottom", expand=tk.YES, fill=tk.BOTH)

        etiqueta_password = tk.Label(frame_form_fill, text="Registrar Datos", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_password.pack(padx=20, pady=5)
        btn_registro = tk.Button(frame_form_fill, text="Registre aquí", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.registrar_datos)
        btn_registro.pack(padx=20, pady=20)
        btn_registro.bind("<Return>", (lambda event: self.registrar_datos()))
        
        etiqueta_usuario = tk.Label(frame_form_fill, text="Visualizar lista de usuarios: ", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_usuario.pack(padx=20, pady=5)
        self.usuario = ttk.Combobox(frame_form_fill, font=('Optima', 14), value="Ascendente Descendente")
        self.usuario.pack( padx=20, pady=10)
        btn_ver_lista = tk.Button(frame_form_fill, text="Ver Lista", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.ver_lista)
        btn_ver_lista.pack(padx=20, pady=20)
        btn_ver_lista.bind("<Return>", (lambda event: self.ver_lista()))

        etiqueta_ver_arbol = tk.Label(frame_form_fill, text="Ver Arbol B", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_ver_arbol.pack(padx=20, pady=5)
        btn_ver_arbol = tk.Button(frame_form_fill, text="Ver", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.ver_arbolB)
        btn_ver_arbol.pack(padx=20, pady=20)
        btn_ver_arbol.bind("<Return>", (lambda event: self.ver_arbolB()))

        self.ventana.mainloop()