#include <Arduino.h>
#include "wifi_setup/wifi_setup.h"
#include "mqtt_client/mqtt_client.h"
#include "config.h"

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_LED_Connect,OUTPUT);
}

void loop() {
  connectWiFi();
  connectMQTT();
    
  client.loop();
}