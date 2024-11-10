#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int redLed = 13;
int yellowLed = 12;
int greenLed = 11;
int blueLed = 10;

float maxY = 0;
float yforce = 0.0;

void setup() {
  Wire.begin();
  mpu.initialize();
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  Serial.begin(1);
  Serial.println("Starting");

}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;

  int time = 1000;
  
  while(time != 0) {
    digitalWrite(blueLed, HIGH);
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    if((abs(ay / 163854.0) > abs(yforce))) {
      yforce = ay / 163854.0;
    }

    time--;
    delay(1);
  }

  digitalWrite(blueLed, LOW);

  if(abs(yforce) > abs(maxY)) {
    maxY = yforce;
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    delay(5000);
    digitalWrite(greenLed, LOW);

  } else {
    digitalWrite(yellowLed, HIGH);
    delay(1000);
    digitalWrite(yellowLed, LOW);
    
  }

  digitalWrite(redLed, HIGH);
  delay(2500);
  digitalWrite(redLed, LOW);

}
