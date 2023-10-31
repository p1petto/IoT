#include <PubSubClient.h>

int led_pin = 13;

PubSubClient mqtt_cli(wifiClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
    if ((char) payload[0] == 'u'){
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("led on");
    }
    if ((char) payload[0] == 'd'){
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("led off");
    }
}

void MQTT_init(){
  mqtt_cli.setServer(mqtt_broker, mqtt_port);
  mqtt_cli.setCallback(callback);

}
void MQTT_connect(){
    while (!mqtt_cli.connected()) {
      String client_id = "esp8266-" + String(WiFi.macAddress());
      Serial.print("The client " + client_id);
      Serial.println(" connects to the public mqtt broker\n");
      if (mqtt_cli.connect(client_id.c_str())){
          Serial.println("MQTT Connected");
      } else {
          Serial.print("failed with state ");
          Serial.println(mqtt_cli.state());
          delay(2000);
      }
  }  
}
