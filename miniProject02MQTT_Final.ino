#include <WiFi.h>
#include <MQTT.h>
#include <ESP32Servo.h>

const char ssid[] = "IndihomeMawar";
const char pass[] = "rahasiadong123";

WiFiClient net;
MQTTClient client;
Servo servo;

#define servoPin 13
#define ldrPin 36

int posisiServo = 0;
String LDR_value;
String pesan;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.print("ip add : ");
  Serial.println(WiFi.localIP());

  Serial.println("\nconnecting to Broker...");
  while (!client.connect("esp32KadekLED", "tugasiotmqtt", "Te9jxeASqRg3tO2R")) {
    Serial.println("try to connect mqtt!");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/perintah");
  client.subscribe("/servo");
}

void messageReceiveServo(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(topic == "/servo"){
    //region LDR
    LDR_value=analogRead(36);
    pesan = LDR_value;
    Serial.print("Cahaya: ");
    Serial.println(LDR_value);
    client.publish("lux",pesan);

    //region Servo
    int valueInput = payload.toInt();
    
    if (valueInput > posisiServo ) {
      for (int i = posisiServo ; i < valueInput; i++) {
        servo.write(i);
        delay(15);
      }
      posisiServo = valueInput;
      Serial.println("Posisi Servo: ");
      Serial.println(posisiServo);
    } else if (valueInput < posisiServo && valueInput >= 0) {
      for (int j = posisiServo ; j >= valueInput ; j--) {
        servo.write(j);
        delay(15);
      }
      posisiServo = valueInput; 
      Serial.println("Posisi: ");
      Serial.println(posisiServo);
    } else if (posisiServo == valueInput) {
      servo.write(valueInput); //stand still
    }  
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  servo.attach(servoPin);
  client.begin("public.cloud.shiftr.io", net);
  client.onMessage(messageReceiveServo);

  connect();
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
}
