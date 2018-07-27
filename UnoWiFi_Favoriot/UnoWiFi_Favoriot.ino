#include <SPI.h>
#include <ESP8266WiFi.h>
#include <dht.h>
dht DHT;
#define DHT22_PIN 2

char ssid[] = "your_network_SSID";      // change it!
char pass[] = "your_network_password";  // change it!
const String yourDevice = "deviceDefault@your_Username"; // change it!
int status = WL_IDLE_STATUS;
char server[] = "api.favoriot.com";
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(2,INPUT);
  WiFi.disconnect();
  Serial.println("Mulai menghubungkan");
  WiFi.begin(ssid,pass);
  while((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("...");
  }
  Serial.println(WiFi.status());
  Serial.println("Terhubung");
  Serial.println("");
}

void loop() {
  int chk = DHT.read22(DHT22_PIN);
  String suhu = String(DHT.temperature, 1);
  String lembab = String(DHT.humidity, 1);
  String gas = String(map(analogRead(A0),0,1024,100,0));
  
  String json = "{\"device_developer_id\":\""+yourDevice+"\",\"data\":{\"Suhu\":\""+suhu+"\",\"Kelembaban\":\""+lembab+"\",\"Gas\":\""+gas+"\"}}";
  Serial.println(json);
  if (client.connect(server, 80)) {
    client.println("POST /v1/streams HTTP/1.1");
    client.println("Host: api.favoriot.com");
    client.println(F("apikey: your_API_key"));  // change it!
    client.println("Content-Type: application/json");
    client.println("cache-control: no-cache");
    client.print("Content-Length: ");
    int thisLength = json.length();
    client.println(thisLength);
    client.println("Connection: close");
    client.println();
    client.println(json);
  }

  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (!client.connected()) {
    client.stop();
  }

  delay(5000);
}