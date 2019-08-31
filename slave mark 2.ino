/*
   Hello world web server
   configure ESP device as Accesspoint
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include<SoftwareSerial.h>
SoftwareSerial serial1(14,12); // d5,d6 rx,tx
int a;


//SSID and Password to your ESP Access Point
//const char* ssid = "ESPWebServer";
//const char* password = "setme3210";
//
//const char* STA_ssid = "IRobotix_AP";
//const char* STA_password = "rifanSifan1";

//int startAdress = 0; int endAdress = 70;
//byte read_eeprom_value = 0;
//String message = " ";
//String web_server_input = "";
//String web_server_input1 = "";
//String web_server_input_actual = "";
//int eeprom_write_complete = 0;
//
//int eeprom_rd_flag = 0;
//int dryrun_off_flag = 0;
//int dryrun_on_flag = 0;
//int Sump_off_flag = 0;
//int Sump_on_flag = 0;
//
//int transmitter_mode_flag = 0;
//int receiver_mode_flag = 0;
//int normal_mode_flag = 0;
//
//int mono_controlerType_flag = 0;
//int singleSub_controlerType_flag = 0;
//int ThreeSub_controlerType_flag = 0;
//
//
//bool dryrun_check_flag = 0;
//bool sump_check_flag = 0;
//bool phase_flag = 0;
////default values of controller motor
//
//String def_mode = "Normal";
//String def_cont_type = "mono";
//String def_DryRun = "ON";
//String def_Sump = "ON";
//
//
//uint8_t ESP8266_D8 = D0;
//
//
////normal mode, access mode , memory_read_mode
//
//bool access_mode_flag = 0;
bool memory_read_flag = 0;

//ESP8266WebServer server(80); //Server on port 80
//
//const char PAGE_Temperaturemonitor[] PROGMEM = R"=====(
//<html>
//  
//<body>
//<h1>RAILWAY WHEEL TEMPERATURE MONITOR</h1>
//
//
//<form name "myForm" action="http://192.168.4.1/submit" method="GET">
//<h2>Select the Master and Slave </h2>
//  <h2>Master</h2>
//   <select name="Master">
//  <option value="nodemcu1">NODEMCU 1</option>
//  <option value="nodemcu2">NODEMCU 2</option>
//    </select>    
//      <h2>Slave</h2>
//    <select name="Slave">
//  <option value="nodemcu1">NODEMCU 1</option>
//  <option value="nodemcu2">NODEMCU 2</option>
//    </select><br><br>
//  <h2>Error Correction:</h2>
//  <input name="error" type="text">
//  <br><br>
//      <input type="submit" value="Submit">
//</form>
//
//
//</body>
//</html>
//)=====";
//
//
////==============================================================
////     This rutine is exicuted when you open its IP in browser
////==============================================================
//void handleRoot() {
//  server.send(200, "text/plain", "HOT AXIAL TEMPERATURE MONITOR!");
//}
//void handleRoot1() {
//  String axial_temperature_input_values = PAGE_Temperaturemonitor;
//  server.send (200, "text/html", axial_temperature_input_values );
//}
//
//void Clear_Eeprom() {
//  Serial.println("Clearing EEPROM");
//  for ( int i=0; i < 512; ++i) {
//       EEPROM.write(i , 0);
//       //EEPROM.commit();
//  }
//}
//
//void Eeprom_write() {
//if (message.length() > 1 ) {
//    for ( read_eeprom_value=0; read_eeprom_value < message.length(); ++read_eeprom_value ) {
//        char eeprom_char = message[read_eeprom_value];
//        EEPROM.write(read_eeprom_value, message[read_eeprom_value]);
//        Serial.println("EEPROM Write inside....");
//        EEPROM.commit();
//        //delay(10);
//    }
//    Serial.println("EEPROM Write process has been completed....\n");
//    Serial.println(read_eeprom_value);
//  }
//}
//
//void Eeprom_read() { 
//  if (message.length() > 1) {
//    for ( int j =1; j < 40 ; ++j ) {
//          web_server_input += char(EEPROM.read(j));
//          Serial.println("EEPROM Read inside 0 to 40....");
//          //delay(10);
//    }
//   for ( int j=40; j < 80 ; ++j ) {
//          web_server_input1 += char(EEPROM.read(j));
//          Serial.println("EEPROM Read inside 40 to 80....");
//          //delay(10);
//    }
//    web_server_input_actual = web_server_input + web_server_input1;
//    Serial.println(web_server_input_actual);
//    eeprom_rd_flag = 1;
//  }
//}
//String handleRoot2() {
//  if (server.args() > 0 ) {
//    for ( uint8_t i = 0; i < server.args(); i++ ) {
//      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//   }
//  }
//  Serial.println(message);
//  return message;
//}
//void handleRoot3() {
//    if (message.length() > 1 ) {
//    //Eeprom_write();
//    //EEPROM.commit();
//   }
//}
//
//void handleRoot4() {
//    //Eeprom_read();
//}
//
//void handleRoot5() {
//  
//   Serial.println("entered in to flag");
//
//   int transmitter_check_index = web_server_input_actual.indexOf("Transmitter");
//   int receiver_check_index = web_server_input_actual.indexOf("Receiver");
//   int normal_check_index = web_server_input_actual.indexOf("Normal");
//
//   int mono_check_index = web_server_input_actual.indexOf("mono");
//   int singlesub_check_index = web_server_input_actual.indexOf("Single phase sub");
//   int ThreephaseSub_check_index = web_server_input_actual.indexOf("Three phase sub");
//
//   int Dryrun_check_index = web_server_input_actual.indexOf("DryRun");
//   int Sump_check_index = web_server_input_actual.indexOf("Sump");
//
//  Serial.println(transmitter_check_index);
//  Serial.println(receiver_check_index);
//  Serial.println(normal_check_index);
//
//  Serial.println(mono_check_index);
//  Serial.println(Dryrun_check_index);
//  Serial.println(Sump_check_index);
//
//    if(transmitter_check_index != -1) {
//      Serial.println("Transmitter mode is inprogress selected from user");
//    transmitter_mode_flag = 1;
//    }
//    if(receiver_check_index != -1) {
//      Serial.println("Receiver mode is inprogress selected from user");
//    receiver_mode_flag = 1;
//    }
//    if(normal_check_index != -1) {
//      Serial.println("Normal mode is processed selecetd from user");
//    normal_mode_flag = 1;
//    }
//
//     if(mono_check_index != -1) {
//      Serial.println("controller type is mono selected from user");
//    mono_controlerType_flag =1;
//    }
//    if(singlesub_check_index != -1) {
//      Serial.println("controller type is singlephase selected from user");
//    singleSub_controlerType_flag = 1;
//    }
//    if(ThreephaseSub_check_index != -1) {
//      Serial.println("controller type is Threephase selecetd from user");
//    ThreeSub_controlerType_flag = 1;
//    }
//    if(Dryrun_check_index != -1) {
//      if(web_server_input_actual.substring(Dryrun_check_index, Dryrun_check_index+10) == "DryRun: OFF") {
//        dryrun_off_flag = 1;
//         Serial.println("Dryrun check is OFF");
//      }
//      if(web_server_input_actual.substring(Dryrun_check_index, Dryrun_check_index+10) == "DryRun: ON") {
//        dryrun_on_flag = 1;
//        Serial.println("Dryrun check is ON");
//      }
//    }
//    if(Sump_check_index != -1) {
//      if(web_server_input_actual.substring(Sump_check_index, Sump_check_index+8) == "Sump: OFF") {
//        Sump_off_flag = 1;
//        Serial.println("Sump check is OFF");
//      } 
//      if(web_server_input_actual.substring(Sump_check_index, Sump_check_index+8) == "Sump: ON") {
//        Sump_on_flag = 1;
//        Serial.println("Sump check is ON");
//      }
//    }
//    //delay(20);
//}
//
//bool motor_start(bool phase_check_flag){
////  digitalWrite(ESP8266_D1, HIGH); //led_motor
//  if ( phase_check_flag == 1 ) {
////    digitalWrite(ESP8266_D7, HIGH);   //motor_start
//    //delay(15000);
////    digitalWrite(ESP8266_D7, LOW);
//  } else {
////        digitalWrite(ESP8266_D7, HIGH);   //motor
//  }
//  //motor_curr_state = 1;
//  Serial.println("Motor_Started");
//}
//
//bool motor_stop(bool phase_check_flag) {
////    digitalWrite(ESP8266_D1, LOW); //led_motor
//  if ( phase_check_flag == 1 ) {
////    digitalWrite(ESP8266_D2, HIGH);   //motor_stop
//    //delay(15000);
////    digitalWrite(ESP8266_D2, LOW);
//  } else {
////        digitalWrite(ESP8266_D2, LOW);   //motor
//  }
// // motor_curr_state = 0;
//  Serial.println("Motor_getting_Stop");   
//}
//
//bool operation_motor( int dryrun_check_flag1, int sump_check_flag1, int phase_flag) {
//  motor_start(phase_flag);
//  if (dryrun_check_flag1 == 1) { 
//      Serial.print("Dry run check flag is activated");
//   
////    digitalWrite(ESP8266_D3, LOW);
//    }
//  if ( sump_check_flag1 == 1 ) {
//      Serial.print("Sump check flag is activated");
//
////    digitalWrite(ESP8266_D5, LOW);        
//  }
//  motor_stop(phase_flag);
//}
//
//
//void handleRoot6() {
//  operation_motor(dryrun_on_flag, Sump_on_flag, ThreeSub_controlerType_flag);
//}
//
//
//void memory_mode_config() {
//   // Serial.begin(9600);
//    //EEPROM.begin(512);
//    Serial.println("Running mode : Access Point mem");
//    //WiFi.mode(WIFI_STA);
//    //Wifi.begin(STA_ssid, STA_password);
//    //Eeprom_read();
//    Serial.println("Read input from EEPROM");
//    handleRoot5();
//    operation_motor(dryrun_on_flag, Sump_on_flag, ThreeSub_controlerType_flag);
//    server.begin();               //Start server
//    Serial.println("HTTP server started");
//  
//}
int C_tot;
int C_avg, temp;
int input, sample=20;
String str;

void temp_monitor_slave(){
  
    for(int i=1; i<=20 ; i++){
//      Serial.print("Ambient = "); 
//      Serial.print(mlx.readAmbientTempC()); 
//      Serial.print("*C\tObject = "); 
//      Serial.print(mlx.readObjectTempC()); 
      C_tot=C_tot+mlx.readObjectTempC();
//      Serial.println("*C");
//      Serial.print("Ambient = "); 
//      Serial.print(mlx.readAmbientTempF()); 
//      Serial.print("*F\tObject = "); 
//      Serial.print(mlx.readObjectTempF()); 
//      Serial.println("*F");
//      Serial.println();
      delay(100);
    }
       C_avg=C_tot/20;
//    Serial.print("\nAv/erage Celsius = ");
//    Serial.print(C_avg);
//    Serial.println("*C");
 
    sample = 20;   
    if((sample>5 && sample <100) && (C_avg>20 && C_avg<100) ){
    str = String("(0") + String (sample) + String(" 0") +  String(C_avg) + String(")");
    Serial.println(str);
    serial1.print(str);
    delay(1000);
    C_avg=0;
    C_tot=0;
    }
}

void normal_mode_config() {
//     Serial.println("Runnin/g mode : Normal Mode config");
//     Serial.println("Temper/ature Monitoring");
     temp_monitor_slave();
     
}

//void access_mode_config() {
//    access_mode_flag = 1;
//    memory_read_flag = 1;
//    Serial.println("Running mode : Access Point access");
//    WiFi.mode(WIFI_AP_STA); 
//    WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
//    
//    IPAddress myIP = WiFi.softAPIP(); //Get IP address
//    Serial.print("HotSpt IP:");
//    Serial.println(myIP);
//    //delay(100);
//    
//    server.on("/", handleRoot1);      //Which routine to handle at user input root location
//    server.on("/submit", handleRoot2); //Which routine to handle at submit the form  root location
//    server.on("/c", Clear_Eeprom);
//    server.on("/w", handleRoot3);
//    server.on("/r", handleRoot4);
//    server.on("/v", handleRoot5);
//    server.on("/m", handleRoot6);
//    server.begin();               //Start server
//    Serial.println("HTTP server started");
//}


//===============================================================
//                  SETUP
//===============================================================

void setup(){
    Serial.begin(115200);  
    serial1.begin(115200); 
    EEPROM.begin(512);
    mlx.begin(); 
//    Serial.println("setup is/ running");
//    pinMode(ESP8266_D8, INPUT);
//    attachInterrupt(digitalPinToInterrupt(ESP8266_D8), access_mode_config, FALLING);
//    Serial.println("OK");
//    Serial.println(memory_read_flag);
//    if(memory_read_flag) {
//      memory_mode_config();
//    }
//    if(!memory_read_flag) {
//      normal_mode_config();
//    }
}
//===============================================================
//                     LOOP
//===============================================================
void loop(){
//  Serial.println("OK");
//    Serial.println(memory_read_flag);
    if(memory_read_flag) {
//      memory_mode_config();
    }
    if(!memory_read_flag) {
      normal_mode_config();
    }
//  server.handleClient();          //Handle client requests
}
