#include "WiCo.h"

void WiCo::connectMQTT()
{
    PubSubClient client(espClient);
}

void WiCo::handleInMQTT(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void WiCo::reconnectMQTT()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            // Once connected, publish an announcement...
            client.publish("4hs1/vlceka/wemos/hello", "hello world");
            // ... and resubscribe
            client.subscribe("4hs1/vlceka/wemos/led");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void WiCo::setupMQTT()
{
    client.setServer(mqtt_server, 1883);
    client.setCallback(WiCo::handleInMQTT);
}

void WiCo::runMQTT()
{

    if (!client.connected())
    {
        reconnectMQTT();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000)
    {
        lastMsg = now;
        ++value;
        snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("4hs1/vlceka/wemos/hello", msg);
    }
}
