#define debug_flag 0 // For debugging purpose enable debug_flag to '1'
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include<SoftwareSerial.h>
SoftwareSerial serial1(14, 12); // D5,D6 - rx,tx :- From Slave NodeMCU to Master NodeMCU
SoftwareSerial serial2 (0, 2); // D3,D4 - rx,tx :- From Master NodeMCU to TTL

uint8_t MoDeRe = 12; // D7 :- To Driver enable and Receiver enable the TTL convertor

int C_tot, C_avg, sample = 50;
String str = "";
String str2 = "";
String str3 = "";

void temp_monitor_master() {
  for (int i = 1; i <= sample ; i++) {
    if (debug_flag) {
      Serial.print("Ambient = ");
      Serial.print(mlx.readAmbientTempC());
      Serial.print("*C\tObject = ");
      Serial.print(mlx.readObjectTempC());
      Serial.println("*C");
    }
    C_tot = C_tot + mlx.readObjectTempC();
    //    delay(100);
  }
  C_avg = C_tot / sample;
  if (debug_flag) {
    Serial.print("Samples: ");
    Serial.println(sample);
    Serial.print("Average Celsius = ");
    Serial.print(C_avg);
    Serial.println("*C");
  }
  if ((sample > 5 && sample < 100) && (C_avg > 20 && C_avg < 80) ) {
    if (debug_flag) {
      Serial.println("Controller 1 (Master):");
    }
    {
      digitalWrite(MoDeRe, HIGH);
      str = String("<0") + String(C_avg) + String(" 0") +  String (sample) + String("> ");
      str2 = serial1.readStringUntil('\n');
      str3 = str + str2;
      if (debug_flag) {
        Serial.println(str);
        Serial.println(str2);
        Serial.println(str3);
      }
      serial2.println(str3);
      if (debug_flag) {
        Serial.println(str3);
      }
      digitalWrite(MoDeRe, LOW);
    }
    C_avg = 0;
    C_tot = 0;
  }
}

void setup() {
  Serial.begin(9600);
  serial1.begin(9600);
  serial2.begin(9600);
  mlx.begin();
  if (debug_flag) {
    Serial.println("Setup is running");
  }
  pinMode(MoDeRe, OUTPUT);
}

void loop() {
  temp_monitor_master();
}
