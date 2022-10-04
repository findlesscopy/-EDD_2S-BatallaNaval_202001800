import requests##pip3 install request
import json

from Estructuras.MatrizDispersa import MatrizDispersa

#Login()
#Admin()
#Usuario("Hola")
#Perfil("Hola")
#matriz = MatrizDispersa()
#matriz.insertar(1,1,"A")
#matriz.graficarNeato("A")


base_url = "http://localhost:8080/"



def postDatos(datos):
    respuesta = requests.post(f'{base_url}Datos/', json=datos)
    respuesta_json = respuesta.text 
    print(respuesta_json)

def postCompra(id_compra, usuario, cantidad):
    data = '"id":"{}","nombre":"{}","cantidad":"{}"'.format(id_compra,usuario,cantidad)
    json_data = json.loads(R"{"+data+"}")
    prueba = json_data
    print(prueba)
    respuesta = requests.post(f'{base_url}Compra/', json=json_data)
    respuesta_json = respuesta.text 
    print(respuesta_json)

def getUsuariosAscendente():#obtener listado
    res = requests.get(f'{base_url}/UsuariosAsc/')
    data = res.text#convertimos la respuesta en dict
    return data

def getUsuariosDescendente():#obtener listado
    res = requests.get(f'{base_url}/UsuariosDes/')
    data = res.text#convertimos la respuesta en dict
    return data

def getLogin(user,password):
    
    res = requests.get((f'{base_url}/Login/{user}/{password}'))
    data = res.text
    return data
    
def getGrafoB():
    res = requests.get((f'{base_url}/Grafo/B'))
    data = res.text
    return data

    
def getArticulos():
    res = requests.get((f'{base_url}/Articulos/'))
    data = res.text
    #print(data)
    return data
    