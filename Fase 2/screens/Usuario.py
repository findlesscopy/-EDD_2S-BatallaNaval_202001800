import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.font import BOLD
import util.generic as utl

class Usuario:
    
    def ver_datos(self):
        pass

    def tienda(self):
        pass

    def iniciar_juego(self):
        pass

    def __init__(self, usuario):        
        self.ventana = tk.Tk()
        self.ventana.title('Usuario')
        self.ventana.geometry('800x600')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)
        utl.centrar_ventana(self.ventana,600,600)

        frame_form = tk.Frame(self.ventana, bd=0, relief=tk.SOLID, bg = '#fcfcfc')
        frame_form.pack(side=tk.LEFT,expand= tk.YES, fill = tk.BOTH)

        frame_form_top = tk.Frame(frame_form, height=50, bd=0, relief=tk.SOLID, bg='black')
        frame_form_top.pack(side=tk.TOP, fill=tk.X)
        title = tk.Label(frame_form_top, text="Bienvenido: "+usuario, font=('Optima', 30), fg="#666a88", bg='#fcfcfc', pady=50)
        title.pack(expand=tk.YES, fill=tk.BOTH)


        # frame_form_fill
        frame_form_fill = tk.Frame(frame_form, height=50,  bd=0, relief=tk.SOLID, bg='#fcfcfc')
        frame_form_fill.pack(side="bottom", expand=tk.YES, fill=tk.BOTH)

        label_ver_perfil = tk.Label(frame_form_fill, text="Ver Perfil", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        label_ver_perfil.pack(padx=20, pady=5)
        btn_ver_perfil = tk.Button(frame_form_fill, text="Ir", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.ver_datos)
        btn_ver_perfil.pack(padx=20, pady=20)
        btn_ver_perfil.bind("<Return>", (lambda event: self.ver_datos()))

        etiqueta_tienda = tk.Label(frame_form_fill, text="Ir a Tienda", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_tienda.pack(padx=20, pady=5)
        btn_tienda = tk.Button(frame_form_fill, text="Tienda", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.tienda)
        btn_tienda.pack(padx=20, pady=20)
        btn_tienda.bind("<Return>", (lambda event: self.tienda()))

        etiqueta_juego = tk.Label(frame_form_fill, text="Iniciar Partida", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_juego.pack(padx=20, pady=5)
        self.tamanio = ttk.Entry(frame_form_fill, font=('Optima', 14))
        self.tamanio.pack(padx=20, pady=10)
        btn_juego = tk.Button(frame_form_fill, text="Play!", font=('Optima', 15), bg='#3a7ff6', bd=0, fg="#fff", command=self.iniciar_juego)
        btn_juego.pack(padx=20, pady=20)
        btn_juego.bind("<Return>", (lambda event: self.iniciar_juego()))

        self.ventana.mainloop()