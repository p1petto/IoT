#include "Config.h"
#include "WIFI.h"
#include "Server.h"
#include "MQTT.h"
unsigned long previousMillis = 0;
unsigned long interval = 30000;

void setup(void){
  Serial.begin(115200);
  WIFI_init(true);
  server_init();
  pinMode(led, OUTPUT);
  mqtt_cli.publish("esp8266/state", "hello emqx");
  mqtt_cli.subscribe("esp8266-fc6f10/command");

}

void loop(void){
  server.handleClient();                   
  mqtt_cli.loop();
  unsigned long currentMillis = millis();
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.println("wifi restarts");
    WIFI_init(true);
    server_init();
    previousMillis = currentMillis;
  }
  if (WiFi.status() = WL_CONNECTED){
    
  }
}
