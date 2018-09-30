
/**
 * PI (maestro) solicita 3 bytes a un Arduino (esclavo)
 * [pi] bytes = bus.read_i2c_block_data(address,0,3) -> Wire.onRequest(handler);
 * Suponemos un sensor analógico en el pin 0
 */
 
#include <Wire.h>
 
#define SLAVE_ADDRESS 0x08
 
const int SENSORPIN = 0;
 
void setup(){
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onRequest(sendData);
    Serial.println("Ready!");
}
 
void loop(){
    delay(100);
}
 
void sendData(){

      float intensidad_baterias = analogRead(0); //Lee la intensidad del puente del banco de baterias.
      intensidad_baterias = (intensidad_baterias * (5 / 1023));
      intensidad_baterias = (intensidad_baterias - 2.5) /0.185;

      Serial.print("intensidad baterias: ");
      Serial.print(intensidad_baterias);
      Serial.print("\n");
      
      float intensidad_placas = analogRead(1); //Lee la intensidad del puente de las placas fotovoltaicas.
      intensidad_placas = (intensidad_placas * 5) / 1023;
      intensidad_placas = (intensidad_placas - 2.5) /0.185;
      
      Serial.print("intensidad_placas: ");
      Serial.print(intensidad_placas);
      Serial.print("\n");
      
      float intensidad_aerogenerador = analogRead(2); //Lee la intensidad del puente del aerogenerador.
      intensidad_aerogenerador = (intensidad_aerogenerador * 5) / 1023;
      intensidad_aerogenerador = (intensidad_aerogenerador - 2.5) /0.185;

      Serial.print("intensidad_aerogenerador: ");
      Serial.print(intensidad_aerogenerador);
      Serial.print("\n");

      byte ibs,ib1,ib2,ips,ip1,ip2,ias,ia1,ia2;
      
      if(intensidad_baterias >= 0){
         ibs = (int) 0;
         ib1 = (int) intensidad_baterias;
         ib2 = (int)((intensidad_baterias - ib1) * 100);
      }else{
         ibs = (int) 1;
         ib1 = (int) -intensidad_baterias;
         ib2 = (int)-((intensidad_baterias - ib1) * 100);
      }

      if(intensidad_placas >= 0){
         ips = (int) 0;
         ip1 = (int) intensidad_placas;
         ip2 = (int)((intensidad_placas - ip1) * 100);
      }else{
         ips = (int) 1;
         ip1 = (int) - intensidad_placas;
         ip2 = (int)-((intensidad_placas - ip1) * 100);
      }
     
      if(intensidad_aerogenerador >= 0){
         ias = (int) 0;
         ia1 = (int) intensidad_aerogenerador;
         ia2 = (int)((intensidad_aerogenerador - ia1) * 100);
      }else{
         ias = (int) 1;
         ia1 = (int) - intensidad_aerogenerador;
         ia2 = (int)-((intensidad_aerogenerador - ia1) * 100);
      }

      Serial.print(ibs);
      Serial.print("\n");
      Serial.print(ib1);
      Serial.print("\n");
      Serial.print(ib2);
      Serial.print("\n");
      Serial.print(ips);
      Serial.print("\n");
      Serial.print(ip1);
      Serial.print("\n");
      Serial.print(ip2);
      Serial.print("\n");
      Serial.print(ias);
      Serial.print("\n");
      Serial.print(ia1);
      Serial.print("\n");
      Serial.print(ia2);
      Serial.print("\n");
  
  byte dataSend[] = {ibs,ib1,ib2,ips,ip1,ip2,ias,ia1,ia2}; //1 y 2 son bytes arbitrarios
  Wire.write(dataSend, 9);        
}
