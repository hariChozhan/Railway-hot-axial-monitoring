#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include<SoftwareSerial.h>
SoftwareSerial serial1(14, 12); // d5,d6 rx,tx

const char* ssid = "ESPWebServer";
const char* password = "setme3210";

const char* STA_ssid = "IRobotix_AP";
const char* STA_password = "rifanSifan1";

int startAdress = 0; int endAdress = 70;
byte read_eeprom_value = 0;
String message = " ";
String web_server_input = "";
String web_server_input1 = "";
String web_server_input_actual = "";

uint8_t ESP8266_D8 = D0;
uint8_t MoDeRe = 2;//D4

bool access_mode_flag = 0;
bool memory_read_flag = 0;

ESP8266WebServer server(80); 

const char PAGE_Temperaturemonitor[] PROGMEM = R"=====(
<html>
  
<body>
<h1>RAILWAY WHEEL TEMPERATURE MONITOR</h1>


<form name "myForm" action="http://192.168.4.1/submit" method="GET">
<h2>Select the Master and Slave </h2>
  <h2>Master</h2>
   <select name="Master">
  <option value="nodemcu1">NODEMCU 1</option>
  <option value="nodemcu2">NODEMCU 2</option>
    </select>    
      <h2>Slave</h2>
    <select name="Slave">
  <option value="nodemcu1">NODEMCU 1</option>
  <option value="nodemcu2">NODEMCU 2</option>
    </select><br><br>
  <h2>Error Correction:</h2>
  <input name="error" type="text">
  <br><br>
      <input type="submit" value="Submit">
</form>


</body>
</html>
)=====";

void handleRoot() {
  server.send(200, "text/plain", "HOT AXIAL TEMPERATURE MONITOR!");
}
void handleRoot1() {
  String axial_temperature_input_values = PAGE_Temperaturemonitor;
  server.send (200, "text/html", axial_temperature_input_values );
}

void Clear_Eeprom() {
  Serial.println("Clearing EEPROM");
  for ( int i=0; i < 512; ++i) {
       EEPROM.write(i , 0);
      }
}

void Eeprom_write() {
if (message.length() > 1 ) {
    for ( read_eeprom_value=0; read_eeprom_value < message.length(); ++read_eeprom_value ) {
        char eeprom_char = message[read_eeprom_value];
        EEPROM.write(read_eeprom_value, message[read_eeprom_value]);
        Serial.println("EEPROM Write inside....");
        EEPROM.commit();
       }
    Serial.println("EEPROM Write process has been completed....\n");
    Serial.println(read_eeprom_value);
  }
}

void Eeprom_read() { 
  if (message.length() > 1) {
    for ( int j =1; j < 40 ; ++j ) {
          web_server_input += char(EEPROM.read(j));
          Serial.println("EEPROM Read inside 0 to 40....");
          //delay(10);
    }
   for ( int j=40; j < 80 ; ++j ) {
          web_server_input1 += char(EEPROM.read(j));
          Serial.println("EEPROM Read inside 40 to 80....");
          //delay(10);
    }
    web_server_input_actual = web_server_input + web_server_input1;
    Serial.println(web_server_input_actual);
//    eeprom_/rd_flag = 1;
  }
}
String handleRoot2() {
  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
   }
  }
  Serial.println(message);
  return message;
}
void handleRoot3() {
    if (message.length() > 1 ) {
   }
}

void handleRoot4() {
    }

void handleRoot5() {  
   Serial.println("entered in to flag");
}

void handleRoot6() {  
}


void memory_mode_config() {
    Serial.println("Running mode : Access Point mem");
    Serial.println("Read input from EEPROM");
    handleRoot5();
    server.begin();             
    Serial.println("HTTP server started");
  
}
int C_tot;
int C_avg, temp;
int input, sample=20, a;
String string_Cavg;

void temp_monitor_master(){
    for(int i=1; i<=20 ; i++){
//      Serial.print("Ambient = "); 
//      Serial.print(mlx.readAmbientTempC()); 
//      Serial.print("*C\tObject = "); 
//      Serial.print(mlx.readObjectTempC()); 
        C_tot=C_tot+mlx.readObjectTempC();
//      Serial.println("*C");
      delay(100);
    }
    C_avg=C_tot/20;
//    Serial.print("\n/Average Celsius = ");
//    Serial.print(C_avg);
//    Serial.println("*C");
    C_avg = 60;
    if((sample>5 && sample <100) && (C_avg>20 && C_avg<100) ){
//    string_Cavg=String(C_avg,1);
//    Serial.println(string_Cavg);
//    Serial.println("Controller 1 (Master)");
//  if (Serial.available()>10) {
    digitalWrite(MoDeRe, HIGH);
    Serial.print("<0"); Serial.print(sample);
    Serial.print(" 0"); Serial.print(C_avg);
    Serial.print(">");
    Serial.println(serial1.readStringUntil('\n'));
    digitalWrite(MoDeRe, LOW);
//  }
    C_avg=0;
    C_tot=0;
    }
}

void normal_mode_config() {
//     Serial.println("Running mode : Normal Mode config");
//     Serial.println("Temperature Monitoring");
     temp_monitor_master();
     
}

void access_mode_config() {
    access_mode_flag = 1;
    memory_read_flag = 1;
//    Serial.println("Run/ning mode : Access Point access");
    WiFi.mode(WIFI_AP_STA); 
    WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
    
    IPAddress myIP = WiFi.softAPIP(); //Get IP address
    Serial.print("HotSpt IP:");
    Serial.println(myIP);
    //delay(100);
    
    server.on("/", handleRoot1);      //Which routine to handle at user input root location
    server.on("/submit", handleRoot2); //Which routine to handle at submit the form  root location
    server.on("/c", Clear_Eeprom);
    server.on("/w", handleRoot3);
    server.on("/r", handleRoot4);
    server.on("/v", handleRoot5);
    server.on("/m", handleRoot6);
    server.begin();               //Start server
    Serial.println("HTTP server started");
}


//===============================================================
//                  SETUP
//===============================================================

void setup(){
    Serial.begin(115200);  
    serial1.begin(115200); 
    EEPROM.begin(512);
    mlx.begin(); 
//    /Serial.println("setup is running");
    pinMode(ESP8266_D8, INPUT);
    attachInterrupt(digitalPinToInterrupt(ESP8266_D8), access_mode_config, FALLING);
//    Serial.println("OK");
    
}
//===============================================================
//                     LOOP
//===============================================================
void loop(){
//  Serial.println(memory_read_flag);
    if(memory_read_flag) {
      memory_mode_config();
    }
    if(!memory_read_flag) {
      normal_mode_config();
    }
  server.handleClient();          //Handle client requests
}
