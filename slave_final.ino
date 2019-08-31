#define debug_flag 0 // For debugging purpose enable debug_flag to '1'
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include<SoftwareSerial.h>
SoftwareSerial serial1(14, 12); // D5,D6 - rx,tx :- From Slave NodeMCU to Master NodeMCU

int C_tot, C_avg = 0, sample = 50;
String str = " ";

void temp_monitor_slave() {
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
    str = String("(0") + String(C_avg) + String(" 0") +  String (sample) + String(")");
    if (debug_flag) {
      Serial.println("Controller 2 (Slave):");
    }
    Serial.println(str);
    serial1.print(str);
    delay(1500);
    C_avg = 0;
    C_tot = 0;
  }
}

void setup() {
  Serial.begin(9600);
  serial1.begin(9600);
  mlx.begin();
  if (debug_flag) {
    Serial.println("Setup is running");
  }
}

void loop() {
  temp_monitor_slave();
  if (debug_flag) {
    Serial.println("\nSlave Temperature Monitoring");
  }
}
