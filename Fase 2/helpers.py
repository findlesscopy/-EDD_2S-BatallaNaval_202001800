from tkinter import *
from tkinter import filedialog
from tkinter.filedialog import askopenfilename
import json

def Lector_Archivos():
    Tk().withdraw()
    filedir = filedialog.askopenfilename(filetypes=[("Archivo data","*.json")])
    #print(filedir)
    return filedir

def Cargar_Archivos():
    with open(Lector_Archivos()) as contenido:
        data = json.load(contenido)

        for usuarios in data['usuarios']:
            print(usuarios)

        for articulos in data['articulos']:
            print(articulos)

        for movimientos in data['tutorial']['movimientos']:
            print(movimientos)
        #print(lista)

if __name__ == "__main__":
    Cargar_Archivos()