#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include <ESP8266AWSImplementations.h>
#include<dht.h>
dht DH; 
Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;
// mq2=esp  vcc=3v3  A0=A0 gnd=gnd
//dht11=esp  vcc=vin  data=d3/gpi0  gnd=gnd  
AmazonIOTClient iotClient;
ActionError actionError;

const char* ssid = "archit";
const char* password = "123456788";

void initWLAN()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}
void initAWS()
{
  iotClient.setAWSRegion("ap-southeast-2");
  iotClient.setAWSEndpoint("amazonaws.com");
    iotClient.setAWSDomain("a35ncatj6ix29q-ats.iot.ap-southeast-2.amazonaws.com");
  iotClient.setAWSPath("/things/IoTTestDevice/shadow");
  iotClient.setAWSKeyID("AKIAY2DV45HYMYTLEFNH");
  iotClient.setAWSSecretKey("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");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  delay(10);
  Serial.println("begin");
  initWLAN();
  Serial.println("wlan initialized");
  initAWS();
  Serial.println("iot initialized");
}

void loop()
{

int analogSensor = analogRead(A0);
int chk = DH.read11(0);
int hum=DH.humidity;
int temp=DH.temperature; 

Serial.print("Temparature,Humidity,Smoke");
Serial.println("\n");  
Serial.print(temp); 
Serial.print(","); 
Serial.print(hum);
Serial.print(",");
Serial.print(analogSensor);
Serial.println("\n");  
 
//delay(2000);
  
  int c=temp;
  int c1=hum;
  int c2=analogSensor;
  char shadow[100];
 
char sc[10], sc1[10],sc2[10];
  dtostrf(c, 6, 2, sc);
  dtostrf(c1, 6, 2, sc1);
 dtostrf(c2, 6, 2, sc2);
 strcpy(shadow, "{\"state\":{\"reported\": {\"Temperature\":");
  strcat(shadow, sc);
  strcat(shadow, ", \"Humidity\":");
  strcat(shadow, sc1);
  strcat(shadow, ", \"Smoke\":");
  strcat(shadow, sc2);
  strcat(shadow, "}}}");
 
  Serial.println("Trying to send data");
  Serial.print(shadow);
  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print(result);
  delay(2000);
}
