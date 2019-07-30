#include<dht.h>
dht DHT; 
void setup() 
{
Serial.begin(9600); 
}
//DHT11.DATA=ARDUINO.3

void loop()
{    
int chk = DHT.read11(3);
float hum=DHT.humidity;
float temp=DHT.temperature; 
Serial.println(" Humidity ");
Serial.println(hum); 
Serial.println(" Temparature ");
Serial.println(temp);
delay(2000); 
}
