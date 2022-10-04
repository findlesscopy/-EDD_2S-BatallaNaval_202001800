from re import I
from tkinter import *
from tkinter import filedialog
from tkinter.filedialog import askopenfilename
import json
from Cliente import postDatos


def Lector_Archivos():
    Tk().withdraw()
    filedir = filedialog.askopenfilename(filetypes=[("Archivo data","*.json")])
    #print(filedir)
    return filedir

def Cargar_Archivos():
    with open(Lector_Archivos()) as contenido:
        datos = json.load(contenido)
        postDatos(datos)
        #print(datos)
