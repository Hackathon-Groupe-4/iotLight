#include "wifi_setup.h"
#include <WiFi.h>
#include "config.h"

void connectWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(SSID, PASSWORD);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWiFi connecté");
    }
    
}