#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "bb3ab6d5dc2441e0a0b8c602cb70ba6f"; //auth token of Blynk

char ssid[] = "abcd"; //ssid of WiFi network
char pass[] = "12345678"; //password of WiFi network

#define DHTPIN D1 //pin of DHT11
#define an A0  //analog pin for air quality and dust sensor
#define ll D6

#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float an = analogRead(A0);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V0, an);
}


void setup()
{

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(ll,OUTPUT);
  
  dht.begin();

  timer.setInterval(1000L, sendSensor);
}

void loop()
{ Blynk.run();
  if (an>500){
    digitalWrite(ll, HIGH); //led for alert of bad air quality
  }
  timer.run();
}
