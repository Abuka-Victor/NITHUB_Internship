#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTTYPE DHT22
#define DHTPIN 4 

const char *mqtt_broker = "broker.emqx.io";
const char *topic = "sensorData/esp32";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 8883;

WiFiClient espClient;

PubSubClient mqtt_client(espClient);


void connectToMQTT();
void mqttCallback(char *topic, byte *payload, unsigned int length);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin("Star-boys5G", "ydou472bmt");
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setKeepAlive(60);
  mqtt_client.setCallback(mqttCallback);
  connectToMQTT();

  dht.begin();
}

void connectToMQTT() {
  while (!mqtt_client.connected()) {
    // String client_id = "esp32-client-" + String(WiFi.macAddress());
    // Serial.print("Connecting to MQTT Broker as " + client_id.c_str() + " \n");
    // if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
    if (mqtt_client.connect("gdg356gbd7v27gdb6345f", mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
      mqtt_client.subscribe(topic);
      mqtt_client.publish(topic, "Hi EMQX I'm an ESP32 ^^ Victor's Nithub project This is a greeting message");  // Publish message upon connection
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" Retrying in 5 seconds.");
      delay(5000);
    }
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println("\n-----------------------");
}

void loop() {
  if (!mqtt_client.connected()) {
          connectToMQTT();
      }
      mqtt_client.loop();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  String sensorData = "Temperature Data: " + String(t) + " \n Humidity Data " + String(h);
  mqtt_client.publish(topic, sensorData.c_str());
  delay(2000);
}
