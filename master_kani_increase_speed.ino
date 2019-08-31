#define SerialTxControl 12
#define Tx HIGH
#define Rx LOW
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

SoftwareSerial ttl(12, 13);
SoftwareSerial slave(14, 1);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

String test = "starting data transmission";

void setup()
{
  Serial.begin(9600);
  ttl.begin(9600);
  slave.begin(9600);
  mlx.begin();
  pinMode(SerialTxControl, OUTPUT);

  digitalWrite(SerialTxControl, Tx);
  ttl.print(test);
  ttl.println();
  delay(100);
  digitalWrite(SerialTxControl, Rx);
}

int reading = 20;
int C_tot;
int C_avg;
String str;
String str1 = "";
int count = 0;

void temp_monitor() {
  for (int i = 1; i <= 20 ; i++) {
    C_tot = C_tot + mlx.readObjectTempC();
  }
  C_avg = C_tot / reading;
  Serial.println("infunction");
  Serial.println(C_avg);

  if ((reading > 5 && reading < 100) && (C_avg > 20 && C_avg < 100)) {
    Serial.println("inif");
    digitalWrite(SerialTxControl, Tx);
    str = "(0";
    str.concat(C_avg);
    str.concat(" 0");
    str.concat(reading);
    str.concat(") ");

    str1.concat(slave.readStringUntil('\n'));
    Serial.println(str + str1);
    ttl.print(str + str1);
    digitalWrite(SerialTxControl, Rx);
  }
  count++;
  C_tot = 0;
  C_avg = 0;
}

void loop()
{
  temp_monitor();
}
