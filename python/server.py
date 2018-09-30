from flask import Flask, request
from flask_restful import Resource, Api
from sqlalchemy import create_engine
from json import dumps

import smbus2
import time

app = Flask(__name__)
api = Api(app)
bus = smbus2.SMBus(1)



class ObtenerMedidas(Resource):
    def get(self):
        address = 0x04
        bytes_tension = bus.read_i2c_block_data(address,0,9)
        time.sleep(3)
        address = 0x08
        bytes_intensidad = bus.read_i2c_block_data(address,0,9)
        return {
            "tension_baterias_signo": bytes_tension[0], 
            "tension_baterias_entero": bytes_tension[1], 
            "tension_baterias_decimal": bytes_tension[2],
            "tension_placas_signo": bytes_tension[3], 
            "tension_placas_entero": bytes_tension[4], 
            "tension_placas_decimal": bytes_tension[5],
            "tension_aerogenerador_signo": bytes_tension[6], 
            "tension_aerogenerador_entero": bytes_tension[7], 
            "tension_aerogenerador_decimal": bytes_tension[8],

            "intensidad_baterias_signo": bytes_intensidad[0], 
            "intensidad_baterias_entero": bytes_intensidad[1], 
            "intensidad_baterias_decimal": bytes_intensidad[2],
            "intensidad_placas_signo": bytes_intensidad[3], 
            "intensidad_placas_entero": bytes_intensidad[4], 
            "intensidad_placas_decimal": bytes_intensidad[5],
            "intensidad_aerogenerador_signo": bytes_intensidad[6], 
            "intensidad_aerogenerador_entero": bytes_intensidad[7], 
            "intensidad_aerogenerador_decimal": bytes_intensidad[8]
        }


class CerrarRele(Resource):
    def get(self):
        address = 0x04
        id_rele = request.args.get('id')
        if id_rele == "0":
            b = [0x00,0x00]
            bus.write_i2c_block_data(address, 0, b)    
            return {'reles': "circuito BANCO DE BATERIAS cerrado correctamente"}
        elif id_rele == "1": 
            b = [0x00,0x01]
            bus.write_i2c_block_data(address, 0, b)    
            return {'reles': "circuito PLACA FOTOVOLTAICA cerrado correctamente"}
        elif id_rele == "2": 
            b = [0x00,0x02]
            bus.write_i2c_block_data(address, 0, b)    
            return {'reles': "circuito AEROGENERADOR cerrado correctamente"}
        else:
            return {'reles': "No existe rele con dicha id"}

class AbrirRele(Resource):
    def get(self):
        address = 0x04
        id_rele = request.args.get('id')
        if id_rele == "0":
            b = [0x01,0x00]
            bus.write_i2c_block_data(address, 1, b)    
            return {'reles': "circuito BANCO DE BATERIAS abierto correctamente"}
        elif id_rele == "1": 
            b = [0x01,0x01]
            bus.write_i2c_block_data(address, 1, b)    
            return {'reles': "circuito PLACA FOTOVOLTAICA abierto correctamente"}
        elif id_rele == "2": 
            b = [0x01,0x02]
            bus.write_i2c_block_data(address, 1, b)    
            return {'reles': "circuito AEROGENERADOR abierto correctamente"}
        else:
            return {'reles': "No existe rele con dicha id"}

api.add_resource(ObtenerMedidas, '/realizar_medida') 
api.add_resource(CerrarRele, '/rele/cerrar_rele')
api.add_resource(AbrirRele, '/rele/abrir_rele')

if __name__ == '__main__':
     app.run(port='8000')



