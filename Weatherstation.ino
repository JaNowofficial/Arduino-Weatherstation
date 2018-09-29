//by JaNow_official
//Check out my Instagram @JaNow_official!
//Connect the data pin off the DHT11 to D5 and connect D0 to RST!
//When you have questions ask me on Instagram!

#include <dht11.h>
#include <Wire.h>

dht11 DHT11;
#define DHT11PIN D5

// Wifi and ThingSpeak settings
#include <ESP8266WiFi.h>


const char* ssid = "Wifi_Name";
const char* password = "Wifi_Password";

const char* server = "api.thingspeak.com";
const char* api_key = ""; //put in your api key from Thingspeak

WiFiClient client;


  void setup() {
  Wire.begin();
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(10);
  Serial.println("Connecting to wifi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

      //Blink LED when connecting to wifi
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
  Serial.println("WiFi connected");


}


void goToBed (int minutes) {
    Serial.print("Going back to bed for ");
    Serial.print(minutes);
    Serial.print(" minutes.");
    ESP.deepSleep(minutes * 60 * 1000000);
}
void postData() {
  // Send data to ThingSpeak
  float chk = DHT11.read(DHT11PIN);
  float temp, humidity;
  char buffer[80];

  temp      = DHT11.temperature;
  humidity  = DHT11.humidity;
  temp = temp - 2;

  Serial.print("Temperature: ");
  Serial.print(temp, DEC);
  Serial.println();

  Serial.print("Humidity: ");
  Serial.print(humidity, DEC);
  Serial.println();
  
  if (client.connect(server, 80)) {
    Serial.println("Connected to ThingSpeak");

    String dataToThingSpeak = "";
    dataToThingSpeak += "GET /update?api_key=";
    dataToThingSpeak += api_key;

    dataToThingSpeak += "&field1=";
    dataToThingSpeak += String(temp);

    dataToThingSpeak += "&field2=";
    dataToThingSpeak += String(humidity);

    dataToThingSpeak += " HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
    dataToThingSpeak += "";
    client.print(dataToThingSpeak);
      }
}

void loop() {
postData();
digitalWrite(LED_BUILTIN,HIGH);
delay(100);
digitalWrite(LED_BUILTIN,LOW);
delay(100);
digitalWrite(LED_BUILTIN,HIGH);
delay(100);
digitalWrite(LED_BUILTIN,LOW);
goToBed(15);
}
