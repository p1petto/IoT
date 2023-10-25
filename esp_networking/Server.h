#include <ESP8266WebServer.h>
ESP8266WebServer server(80);    

void handleRoot() {         
  server.send(200, 
              "text/html", 
              "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");                
}
void handleRegistry(){
  server.send(200, 
              "text/html", 
              "<form action=\"/REGI\" method=\"GET\"><input type=\"text\" name=\"name\"><input type=\"text\" name=\"password\"><input type=\"submit\" value=\"SendWifi\"></form>");
}

void handleLED() {                          
  digitalWrite(led, !digitalRead(led));
  server.sendHeader("Location","/"); // redirection to keep button on the screen
  server.send(303);
}
void handleREGI() {
  // // 
  // serial.Println()
  // server.sendHeader("Location","/"); // redirection to keep button on the screen
  // server.send(303);
  String message = "Number of args received:";
  message += server.args();            //Get number of parameters
  message += "\n";                            //Add a new line
  

  // String arg0 = server.arg(0);
  // char char_array(arg0.length());
  // arg0.toCharArray(char_array, arg0.length());

  ssidCLI = const_cast<char*>(server.arg(0).c_str());
  passwordCLI = const_cast<char*>(server.arg(1).c_str());
  
  WiFi.softAPdisconnect(true);
  WIFI_init(false);

  server.send(200, "text/plain", message);       //Response to the HTTP request
}

void handleSENSOR() {                          
  int data = analogRead(A0);
  //server.sendHeader("Location","/");
  server.send(200, "text/html", String(data));
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

void server_init() {
  server.on("/", HTTP_GET, handleRoot);     
  server.on("/LED", HTTP_POST, handleLED);
  server.on("/REG", HTTP_GET, handleRegistry);
  server.on("/REGI", HTTP_GET, handleREGI);
  server.on("/SENSOR", HTTP_GET, handleSENSOR);  
  server.onNotFound(handleNotFound);        

  server.begin();                          
  Serial.println("HTTP server started");    
}
