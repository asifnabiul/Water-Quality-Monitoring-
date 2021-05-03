
//Serial.print("|");
/*TDS*/

#define SERIAL Serial
//#include "GravityTDS.h"
#define TdsSensorPin A2
//GravityTDS gravityTds;
#include <SoftwareSerial.h>
const int adcPin = A4;
const float m = -5.436; 
SoftwareSerial bt(10,11); // RX, TX
float tdsValue = 0;
float sensorValueTUR = 0;
float gravityTds = 0 ;
float Voltage = 0;
float tempc;
float turValue;

 
void setup() {
  gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();
    SERIAL.begin(9600);
     bt.begin(9600); 

}
void loop() {
   if (bt.available())  /* If data is available on serial port */
    {
     Serial.write(bt.read()); /* Print character received on to the serial monitor */
    }
  
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    delay(1000);
    
sensorValue = analogRead(sensorPin);
    Voltage = sensorValue*5/1024.0; //Convert analog reading to Voltage
    tdsValue=(133.42/Voltage*Voltage*Voltage - 255.86*Voltage*Voltage + 857.39*Voltage)*0.5; //Convert voltage value to TDS value
    SERIAL.print("TDS Value = "); 
    Serial.print("\t");
    SERIAL.print(tdsValue);
    delay(1000); 

    int sensorValue = analogRead(A3);
  float turValue = sensorValue * (5.0 / 1024.0);

  Serial.println ("Sensor Output (V):");
  Serial.println (turValue);
  Serial.println();
  delay(1000);


float Po = analogRead(adcPin) * 5.0 / 1024;
  float phValue = 7 - (2.5 - Po) * m;
  Serial.print("ph value = "); 
  Serial.println(phValue);

delay(500);

const float sensor=A5; // Assigning analog pin A1 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading

vout=analogRead(sensor);
vout=(vout*500)/2047;
tempc=vout; // Storing value in Degree Celsius
tempf=(vout*1.8)+32; // Converting to Fahrenheit 
Serial.print("in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();

delay(1000); //Delay of 1 second for ease of viewing 

bt.print(tempc); //send to MIT App
 bt.print(";");
  bt.print(phValue); //send to MIT App 
 bt.println(";");
bt.println(tdsValue);
 bt.println(",");
 bt.println(turValue);
 bt.println(",");
 
  
  delay(1000);
}
