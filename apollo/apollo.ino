#include <Wire.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
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
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");

  Serial.begin(1);
  Serial.println("Starting");

}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;

  int time = 1000;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(maxY));

  while(time != 0) {
    digitalWrite(blueLed, HIGH);
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    if(abs(gy) > abs(yforce)) {
      yforce = abs(gy);
    }

    time--;
    delay(1);
  }

  lcd.setCursor(0, 1);
  lcd.print(String(yforce));

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

  yforce = 0.0;
  digitalWrite(redLed, HIGH);
  delay(2500);
  digitalWrite(redLed, LOW);

}
