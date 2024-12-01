#include <Wire.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
MPU6050 mpu;

int redLed = 11, greenLed = 10, blueLed = 9;
int pauseButton = 7, stateButton = 6, endButton = 5;

int maxY = 0.0, yforce = 0.0;

enum state {START, PLAY, RESULTS, WAIT, END, PAUSE};

state currentState = PLAY;

void setup() 
{

  Wire.begin();
  mpu.initialize();
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  lightColor(255, 255, 0);

  pinMode(pauseButton, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("Starting");

}

void loop() 
{

  lcdMaxScore();
  Serial.println(digitalRead(pauseButton));

  if(digitalRead(pauseButton) == 0 && currentState != PAUSE)
  {
    currentState = PAUSE;
  }

  switch(currentState) 
  { 
    case START:
      startState();
      break;

    case PLAY:
      playState();
      break;

    case RESULTS:
      resultsState();
      break;

    case WAIT:
      waitState();
      break;

    case PAUSE:
      pauseState();
      break;

    case END:
      endState();
      break;

  }
}

void lightColor(int r, int g, int b)
{
  analogWrite(redLed, r);
  analogWrite(greenLed, g);
  analogWrite(blueLed, b);
}

// Initial power on
void startState() 
{
  currentState = PLAY;
  return;

}

// Player can throw
void playState() 
{
  int16_t ax, ay, az, gx, gy, gz;

  int time = 1000;

  while(time != 0) 
  {
    lightColor(0, 0, 255);

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    if(abs(gy) > abs(yforce)) {
      yforce = abs(gy);
    }

    time--;
    delay(1);

  }

  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("Attempt: " + String(yforce));

  lightColor(0, 0, 0);

  currentState = RESULTS;
    
  return;

}

// calculating + displaying results
void resultsState() 
  {
  if(abs(yforce) > abs(maxY)) 
    {
    maxY = yforce;
    lightColor(0, 255, 0);
    lcdMaxScore();
    delay(5000);
    lightColor(0, 0, 0);

  } 
  else 
  {
    lightColor(255, 225, 0);
    delay(4000);
    lightColor(0, 0, 0);
    
  }

  currentState = WAIT;

}

// in between state for passing to other player(s)
void waitState() 
{
  yforce = 0.0;
  lightColor(255, 0, 0);
  delay(3500);
  lightColor(0, 0, 0);

  currentState = PLAY;

}

// end the game
void endState() 
{
  // add end state functionality
  // if user decides to end the game, turn off arduino
  // if user wants to restart the game, set everything back to original values
}

void lcdMaxScore() 
{
  // lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("High: " + String(maxY));
}

void pauseState()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game paused.");
  lightColor(170, 0, 255);
  delay(5000);

  while(digitalRead(pauseButton) == 1);
  delay(200);

  lcd.clear();
  lcdMaxScore();
  currentState = WAIT;

}
