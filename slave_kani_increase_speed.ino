#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>

SoftwareSerial slave(1, 14);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{
  Serial.begin(9600);
  slave.begin(9600);
  mlx.begin();
}

int reading = 20;
int C_tot;
int C_avg;
String str;

void temp_monitor() {
  C_tot = 0;
  C_avg = 0;
  for (int i = 1; i <= 20 ; i++) {
    C_tot = C_tot + mlx.readObjectTempC();
  }

  C_avg = C_tot / reading;

  if ((reading > 5 && reading < 100) && (C_avg > 20 && C_avg < 100)) {
    String str = "<0";
    str.concat(C_avg);
    str.concat(" 0");
    str.concat(reading);
    str.concat(">\n");
    slave.print(str);
    Serial.print(str);
  }
}

void loop()
{
  temp_monitor();
}
