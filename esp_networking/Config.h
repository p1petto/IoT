String ssidAP = "Hello stranger"; // имя контроллера и точки доступа
String passwordAP = "ESP8266123"; // пароль точки доступа


char* ssidCLI = ""; // имя контроллера и точки доступа
char* passwordCLI = ""; // пароль точки доступа

char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;

bool wifi_was_conn = false;

const int led = 2;
