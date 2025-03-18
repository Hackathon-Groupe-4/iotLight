#include "mqtt_client.h"
#include <WiFiClient.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

void connectMQTT()
{
    if (!client.connected())
    {
        digitalWrite(PIN_LED_Connect, HIGH);
        client.setServer(MQTT_SERVER, 1883);
        client.setCallback(callbackLight);
        while (!client.connected())
        {
            Serial.print("Connexion MQTT...");
            String clientID = ID_CLIENT_MQTT + String(random(0xFFFF), HEX);
            if (client.connect(clientID.c_str()))
            {
                Serial.println("Connecté !");
                String fullTopic = String(TOPIC_ROOT) + "/" + String(ID_CLIENT_MQTT);
                client.subscribe(fullTopic.c_str());  // Abonnement au topic MQTT
                String texte = "Abonné à " + fullTopic;
                Serial.println(texte);
            }
            else
            {
                Serial.print("Échec, code erreur : ");
                Serial.println(client.state());
                delay(5000);
            }
        }
        publishMessage("Devices", ID_CLIENT_MQTT);
        digitalWrite(PIN_LED_Connect, LOW);
    }
}


void publishMessage(const char *topic, const char *payload)
{
    String fullTopic = String(TOPIC_ROOT) + "/" + String(topic);
    client.publish(fullTopic.c_str(), payload);
    Serial.print("Send :");
    Serial.print(fullTopic);
    Serial.print(" :");
    Serial.println(payload);
}

void callbackLight(char* topic, byte* payload, unsigned int length) {
    std::string payloadStr((char*)payload, length);
    std::string topicStr(topic);
    
    if(payloadStr == "ON"){
        digitalWrite(PIN_LED, HIGH);
    }
    else if(payloadStr == "OFF"){
        digitalWrite(PIN_LED, LOW);
    }
}