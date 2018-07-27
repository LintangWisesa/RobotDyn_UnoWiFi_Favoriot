#

![favoriot](https://www.favoriot.com/wp-content/uploads/2017/03/favoriot-1.png)

# RobotDyn Uno+WiFi & Favoriot

### **[Favoriot](https://www.favoriot.com/home/iotplatform)** offers an IoT platform specifically designed for any Internet of Things (IoT) projects. The platform is developed to support the integration of data from sensors and actuators on the internet. Collecting and storing data from IoT devices become much easier. Moreover, the platform also helps developers in building vertical applications without worry about the hosting. 

### This article will present a step by step example how to upload gas, temperature & humidity sensor's value from RobotDyn Uno+WiFi to Favoriot IoT platform. Watch video below (or [click here](https://www.youtube.com/watch?v=sfttFMhgwxA)) for its demonstration, then follow these instructions to start building your project with RobotDyn Uno+WiFi & Favoriot.

#

[![Video UnoWiFi & Favoriot](https://img.youtube.com/vi/sfttFMhgwxA/0.jpg)](https://www.youtube.com/watch?v=sfttFMhgwxA)

#

### **1. What You Need** :gift:
To build this project, you need the following items:
- 1 RobotDyn Uno+WiFi board
- 1 breadboard
- 1 MQ-2 gas sensor
- 1 DHT22 temperature & humidity sensor
- some jumper wires
- Arduino IDE ([download here](https://www.arduino.cc/en/Main/Software))

#

### **2. Schematics** :wrench::hammer:

Gather your parts then follow the schematics below.

![UnoWiFi schema](https://raw.githubusercontent.com/LintangWisesa/RobotDyn_UnoWiFi_Favoriot/master/UnoWiFi_Favoriot.png)

#

### **3. Favoriot Setup** :purple_heart:

- __Device Developer ID__

  Signup & login to [Favoriot](https://platform.favoriot.com/login). If you are registered in Favoriot, you have a default device already created for you. Go to right platform on https://platform.favoriot.com and see the device panel to see the devices that are present. Basically you need the ```device_developer_id``` that might be something like ```defaultDevice@myusername```. But if you want, you can create a new device and use it in this example.

- __API Key__

  Now, go to your Favoriot *Account Setting* which is available on the top right corner in the dropdown and check your API key. You need this API key to complete this example. It's a big alphanumeric token like:
  ```c++
  '986673a6377ef1fde2357ebdcb0da582lintang150b00cabcd5a0d83045425407ab4'
  ```

#

### **4. Arduino Sketch** :clipboard:

First you need to install ESP8266 platform on Arduino IDE, follow these instructions: [click here](https://github.com/esp8266/Arduino). Copy sketch below to your Arduino IDE. Make sure you have chosen the right option for **_Board_** and **_Port_** under **_Tools_** menu, then upload to your Arduino board.

```c++
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
```

#

### **5. Have Fun!** :sunglasses:
Now you can monitor your MQ-2 & DHT22 every 5 seconds on Favoriot dashboard. For more information about Favoriot, read its full documentation: [click here](https://platform.favoriot.com/tutorial/).

__*My other tutorials on Favoriot:*__
- [ESP8266 & Favoriot](https://github.com/LintangWisesa/ESP8266_Favoriot)
- [ESP32 & Favoriot](https://github.com/LintangWisesa/ESP32_Favoriot)
- [RobotDyn Uno+WiFi & Favoriot](https://github.com/LintangWisesa/RobotDyn_UnoWiFi_Favoriot)
- [Arduino MKR1000 & Favoriot](https://github.com/LintangWisesa/Arduino_MKR1000_Favoriot)

#

#### Lintang Wisesa :love_letter: _lintangwisesa@ymail.com_

[Facebook](https://www.facebook.com/lintangbagus) | 
[Twitter](https://twitter.com/Lintang_Wisesa) |
[Google+](https://plus.google.com/u/0/+LintangWisesa1) |
[Youtube](https://www.youtube.com/user/lintangbagus) | 
:octocat: [GitHub](https://github.com/LintangWisesa) |
[Hackster](https://www.hackster.io/lintangwisesa)

