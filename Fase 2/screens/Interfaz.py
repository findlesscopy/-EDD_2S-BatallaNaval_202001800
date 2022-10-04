
from statistics import variance
import tkinter as tk
from tkinter import ttk, messagebox
from tkinter.font import BOLD
import json

from requests import post
import util.generic as utl
from Cliente import getLogin, getUsuariosAscendente, getUsuariosDescendente, getGrafoB, getArticulos, postCompra
from helpers.helpers import Cargar_Archivos
from PIL import Image, ImageTk

class Login:
    
    def verificar(self):
        username = self.usuario.get()
        password = self.password.get()
        global usuario_global 
        if(username == "EDD" and password == "edd123"):
            self.ventana.destroy()
            Admin()
        elif(username != "EDD" and password !="edd123"):
            respuesta = getLogin(username,password)
            if(respuesta == "Si"):
                usuario_global = username
                self.ventana.destroy()
                
                Usuario(username)
            else:
                messagebox.showerror(message="Invalid username or password", title="Error")

    def nombre_global(self):
        usuario_global = self.usuario.get()
        return usuario_global


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


class Admin:
    
    def registrar_datos(self):
        Cargar_Archivos()


    def ver_lista(self):
        modo = self.usuario.get()
        if(modo == "Ascendente"):
            #print("asc")
            Listado("Ascendente")
            #listado = getUsuariosAscendente()

        if(modo == "Descendente"):
            #print("desc")
            Listado("Descendente")
            #listado = getUsuariosDescendente()
            

    def ver_arbolB(self):
        getGrafoB()

    def regresar(self):
        self.ventana.destroy()
        Login()
        

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

        btn_salir = tk.Button(frame_form_fill, text="Cerrar Sesión", font=('Optima', 15), bg='#E64D2C', bd=0, fg="#fff", command=self.regresar)
        btn_salir.pack(padx=20, pady=20)
        btn_salir.bind("<Return>", (lambda event: self.regresar()))
        self.ventana.mainloop()


class Usuario:
    
    def ver_datos(self):
        print(usuario_global)
        Perfil(usuario_global)

    def tienda(self):
        
        Tienda()

    def iniciar_juego(self):
        pass

    def regresar(self):
        self.ventana.destroy()
        Login()

    def __init__(self, usuario):   
        print(usuario_global)     
        self.ventana = tk.Tk()
        self.ventana.title('Usuario')
        self.ventana.geometry('800x600')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)
        #print(usuario)
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

        btn_salir = tk.Button(frame_form_fill, text="Cerrar Sesión", font=('Optima', 15), bg='#E64D2C', bd=0, fg="#fff", command=self.regresar)
        btn_salir.pack(padx=20, pady=20)
        btn_salir.bind("<Return>", (lambda event: self.regresar()))

        self.ventana.mainloop()

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
        
        print(usuario_global)
        utl.centrar_ventana(self.ventana,500,500)
        

        frame_form = tk.Frame(self.ventana, bd=0, relief=tk.SOLID, bg = '#fcfcfc')
        frame_form.pack(side=tk.LEFT,expand= tk.YES, fill = tk.BOTH)
        

        frame_form_top = tk.Frame(frame_form, height=50, bd=0, relief=tk.SOLID, bg='#fcfcfc')
        frame_form_top.pack(side=tk.TOP, fill=tk.X)
        title = tk.Label(frame_form_top, text=f'Usuario : {usuario}', font=('Optima', 20), fg="#666a88", bg='#fcfcfc', pady=20)
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

class Listado:

    def __init__(self, modo):
        
        self.ventana = tk.Tk()
        self.ventana.title('Listado')
        self.ventana.geometry('500x500')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)

        utl.centrar_ventana(self.ventana,500,500)
        

        frame_form = tk.Frame(self.ventana, bd=0, relief=tk.SOLID, bg = '#fcfcfc')
        frame_form.pack(side=tk.LEFT,expand= tk.YES, fill = tk.BOTH)
        

        frame_form_top = tk.Frame(frame_form, height=50, bd=0, relief=tk.SOLID, bg='#fcfcfc')
        frame_form_top.pack(side=tk.TOP, fill=tk.X)
        title = tk.Label(frame_form_top, text=f'Listado : {modo}', font=('Optima', 20), fg="#666a88", bg='#fcfcfc', pady=20)
        title.pack(expand=tk.YES, fill=tk.BOTH)


        ta_listado = tk.Text(frame_form_top, font=('Optima', 14), fg="#666a88", bg='#fcfcfc')
        ta_listado.pack(fill=tk.X, padx=20, pady=5)
        if(modo == "Ascendente"):
            ta_listado.insert(tk.INSERT,getUsuariosAscendente())
        elif(modo =="Descendente"):
            ta_listado.insert(tk.INSERT,getUsuariosDescendente())
        
        self.ventana.mainloop()

class Tienda:
    
    def realizar_compra(self):
        usuario = str(self.usuario_nombre)
        id_compra = str(self.usuario.get())
        cantidad = str(self.cantidad.get())
        #data = "{'id':'{}','nombre': '{}','cantidad':'{}'}".format(id_compra,usuario,cantidad)
        postCompra(id_compra,usuario,cantidad)
        print(id_compra,usuario,cantidad)


    def ver_lista(self):
        pass


    def __init__(self, user):        
        self.ventana=tk.Tk()
        self.ventana.title('Tienda')
        self.ventana.geometry('800x600')
        self.ventana.config(bg="#3a7ff6")
        self.ventana.resizable(width=0, height=0)
        self.usuario_nombre = user

        data = getArticulos()
        data_json = json.loads(data)
        #print(type(data_json))


        mainframe=tk.Frame(self.ventana,bg="#3a7ff6")
        mainframe.pack(fill="both",expand=True)

        label=tk.Label(mainframe,text="Tienda",bg="black",fg="white",padx=5,pady=5)
        label.config(font=("Arial",18))
        label.pack(fill="x")

        #top frame
        


        #vertical layout with data
        verticalFrame=tk.Frame(mainframe,bg="blue")

        my_canvas = tk.Canvas(mainframe, bg="#3a7ff6")
        my_canvas.pack(side=tk.LEFT,fill=tk.BOTH,expand=True)


        scrollbar = ttk.Scrollbar(mainframe, orient=tk.VERTICAL, command=my_canvas.yview)
        scrollbar.pack(side=tk.RIGHT,fill="y")

        my_canvas.config(yscrollcommand=scrollbar.set)
        my_canvas.bind("<Configure>",lambda e: my_canvas.configure(scrollregion = my_canvas.bbox("all")))

        second_frame = tk.Frame(my_canvas)

        my_canvas.create_window((0,0), window=second_frame, anchor="nw")

        values = ""
        for articulo in data_json.values():
            for dentro in articulo:
                values += "{} ".format(dentro["id"])
                
               #py_imagen = ImageTk.PhotoImage(Image.open('/home/edd/Escritorio/imagenes/{}'.format(dentro["src"])).resize((300,200),Image.ANTIALIAS))
                exec('self.lbl{} = tk.Label(second_frame, text="{} {}",padx=10, pady= 10, fg="white", bg="black")'.format(dentro["id"],dentro["nombre"],dentro["id"]))
                exec('self.lbl{}.pack(fill="x",padx=10,pady=10)'.format(dentro["id"]))
                exec('hola{} = ImageTk.PhotoImage(Image.open("/home/edd/Escritorio/imagenes/{}").resize((300,200),Image.ANTIALIAS))'.format(dentro["id"],dentro["src"]))
                
                exec('self.item{} = tk.Label(second_frame, text="{}", image = hola{}, padx=10, pady= 10, fg="white", bg="black")'.format(dentro["id"],dentro["nombre"],dentro["id"]))
                exec('self.item{}.pack(fill="x",padx=10,pady=10)'.format(dentro["id"]))
        
        etiqueta_usuario = tk.Label(verticalFrame, text="Realizar Compras: ", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_usuario.pack(padx=20, pady=5)
        self.usuario = ttk.Combobox(verticalFrame, font=('Optima', 14), value=values)
        self.usuario.pack( padx=20, pady=10)
        etiqueta_nick = tk.Label(verticalFrame, text="Cantidad", font=('Optima', 14), fg="#666a88", bg='#fcfcfc', anchor="w")
        etiqueta_nick.pack(fill=tk.X, padx=20, pady=5)
        self.cantidad = ttk.Entry(verticalFrame, font=('Optima', 14))
        self.cantidad.pack(fill=tk.X, padx=20, pady=10)

        btn_ver_lista = tk.Button(verticalFrame, text="Compra", font=('Optima', 15), bg='#309F3B', bd=0, fg="#fff", command=self.realizar_compra)
        btn_ver_lista.pack(padx=20, pady=20)
        btn_ver_lista.bind("<Return>", (lambda event: self.realizar_compra()))
        
        verticalFrame.pack(fill="x", pady=40)
        #end vertical

        self.ventana.mainloop()
