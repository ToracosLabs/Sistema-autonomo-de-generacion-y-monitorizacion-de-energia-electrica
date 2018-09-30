
/**
 * PI (maestro) solicita 3 bytes a un Arduino (esclavo)
 * [pi] bytes = bus.read_i2c_block_data(address,0,3) -> Wire.onRequest(handler);
 * Suponemos un sensor analógico en el pin 0
 */
 
#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
 
const int SENSORPIN = 0;
 
void setup(){
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onRequest(sendData);
    Wire.onReceive(receiveData);
    Serial.println("Ready!");
}
 
void loop(){
    delay(100);
}
 
void sendData(){
  
      float tension_baterias = analogRead(0); //Lee la tension del puente del banco de baterias.
      tension_baterias = (tension_baterias * 40) / 1023;

      Serial.print("tensión baterias: ");
      Serial.print(tension_baterias);
      Serial.print("\n");
      
      float tension_placas = analogRead(1); //Lee la tension del puente de las placas fotovoltaicas.
      tension_placas = (tension_placas * 40) / 1023;

      Serial.print("tension_placas: ");
      Serial.print(tension_placas);
      Serial.print("\n");
      
      float tension_aerogenerador = analogRead(2); //Lee la tension del puente del aerogenerador.
      tension_aerogenerador = (tension_aerogenerador * 40) / 1023;

      Serial.print("tension_aerogenerador: ");
      Serial.print(tension_aerogenerador);
      Serial.print("\n");

      byte tbs,tb1,tb2,tps,tp1,tp2,tas,ta1,ta2;
      
      if(tension_baterias >= 0){
         tbs = (int) 0;
         tb1 = (int) tension_baterias;
         tb2 = (int)((tension_baterias - tb1) * 100);
      }else{
         tbs = (int) 1;
         tb1 = (int) -tension_baterias;
         tb2 = (int)-((tension_baterias - tb1) * 100);
      }

      if(tension_placas >= 0){
         tps = (int) 0;
         tp1 = (int) tension_placas;
         tp2 = (int)((tension_placas - tp1) * 100);
      }else{
         tps = (int) 1;
         tp1 = (int) - tension_placas;
         tp2 = (int)-((tension_placas - tp1) * 100);
      }
     
      if(tension_aerogenerador >= 0){
         tas = (int) 0;
         ta1 = (int) tension_aerogenerador;
         ta2 = (int)((tension_aerogenerador - ta1) * 100);
      }else{
         tas = (int) 1;
         ta1 = (int) - tension_aerogenerador;
         ta2 = (int)-((tension_aerogenerador - ta1) * 100);
      }

      Serial.print(tbs);
      Serial.print("\n");
      Serial.print(tb1);
      Serial.print("\n");
      Serial.print(tb2);
      Serial.print("\n");
      Serial.print(tps);
      Serial.print("\n");
      Serial.print(tp1);
      Serial.print("\n");
      Serial.print(tp2);
      Serial.print("\n");
      Serial.print(tas);
      Serial.print("\n");
      Serial.print(ta1);
      Serial.print("\n");
      Serial.print(ta2);
      Serial.print("\n");
  
  byte dataSend[] = {tbs,tb1,tb2,tps,tp1,tp2,tas,ta1,ta2}; //1 y 2 son bytes arbitrarios
  Wire.write(dataSend, 9);        
}

void receiveData(int byteCount){
    int accion = 0;
    int id_rele = 0 ;
    int cont = 0;
    int number = 0;
    while(Wire.available()) {
        number = Wire.read();
        if(cont == 0){
          
        }
        if(cont == 1){
          accion = number;
        }
        if(cont == 2){
          id_rele = number;
        }
        Serial.print(number);
        cont++;
     }

     if(accion == 0){
        if(id_rele == 0){
             digitalWrite(7, HIGH); 
        }
        if(id_rele == 1){
             digitalWrite(8, HIGH); 
        }
     }
     if(accion == 1){
        if(id_rele == 0){
            digitalWrite(7, LOW); 
        }
        if(id_rele == 1){
            digitalWrite(8, LOW); 
        }
     }
}
