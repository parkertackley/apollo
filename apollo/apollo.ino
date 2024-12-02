#include <Wire.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

// sets lcd and mpu
LiquidCrystal_I2C lcd(0x27, 20, 4);
MPU6050 mpu;

// components to proper pins
int redLed = 11, greenLed = 10, blueLed = 9;
int pauseButton = 7, stateButton = 6, endButton = 5;
int buzzer = 12;

// global variables
int maxY = 0.0, yforce = 0.0;
enum state {START, PLAY, RESULTS, WAIT, PAUSE, END};
state currentState = START;

// Initializes all components to either input or output
// turns on LCD, and begins serial monitor
void setup() 
{

  Wire.begin();
  mpu.initialize();
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  pinMode(buzzer, OUTPUT);

  lightColor(255, 255, 0);

  pinMode(pauseButton, INPUT_PULLUP);
  pinMode(stateButton, INPUT_PULLUP);

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

// main loop
void loop() 
{
  // displays the max score when not in the start state
  if(currentState != START)
    lcdMaxScore();

  // if pause button is pressed, change state
  if(digitalRead(pauseButton) == 0 && currentState != PAUSE)
  {
    delay(200);
    currentState = PAUSE;
  }

  // state machine
  switch(currentState) 
  { 
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

    case START:
      startState();
      break;

    default:
      waitState();
      break;

  }
}

// -------------------------------
// --------State Functions--------
// -------------------------------

// Initial state before start up
// allows for user to start the game at any time
void startState() 
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press button 2");
  lcd.setCursor(0, 1);
  lcd.print("to begin!");

  lightColor(255, 255, 255);

  while(digitalRead(stateButton) == 1);

  delay(200);
  lcd.clear();

  currentState = PLAY;

}

// State that measures the "throwing" force of the current player
// prints attempt to the screen
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

// State to calculate the score and changes light if high score is achieved or not
void resultsState() 
  {
  if(abs(yforce) > abs(maxY)) 
    {
    maxY = yforce;
    tone(buzzer, 1000);
    for(int i = 0; i < 5; ++i)
    {
      lightColor(0, 255, 0);
      delay(500);
      lightColor(0, 0, 0);
      delay(250);
    }
    delay(250);
    noTone(buzzer);

    lcdMaxScore();
  } 
  else 
  {
    lightColor(255, 225, 0);
    delay(4000);
    lightColor(0, 0, 0);
    
  }

  currentState = WAIT;

}

// State after the results state that waits for the user input to initialize another play loop
void waitState() 
{

  yforce = 0.0;
  lightColor(255, 0, 0);

  // waits for user to press the state button to play the game
  while(digitalRead(stateButton) == 1)
  {
    if(digitalRead(pauseButton) == 0)
    {
      pauseState();
    }
  }
  delay(200);
  lcd.clear();
  delay(1000);
  currentState = PLAY;

}

void pauseState()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Game paused.");
  lcd.setCursor(0, 1);
  lcd.print("Btn 1: Continue!");
  lightColor(170, 0, 255);
  delay(5000);

  while(digitalRead(pauseButton) == 1);
  delay(200);

  lcd.clear();
  lcdMaxScore();
  currentState = WAIT;

}

// -------------------------------
// -------Helper Functions--------
// -------------------------------

// helper function to change rgb values of LED easily
void lightColor(int r, int g, int b)
{
  analogWrite(redLed, r);
  analogWrite(greenLed, g);
  analogWrite(blueLed, b);
}

// helper function to print the high score to the screen
void lcdMaxScore() 
{
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 0);
  lcd.print("High: " + String(maxY));
}

// -------------------------------
// ------------Tests--------------
// -------------------------------

// Used to ensure LED is displaying all colors
// for the "Timed LEDs" test in phase 2 documentation
void testLED()
{

  lightColor(0, 0, 255);
  delay(500);
  lightColor(255, 0, 0);
  delay(500);
  lightColor(255, 255, 255);
  delay(500);
  lightColor(0, 255, 0);
  delay(500);

}

// Used to test that when a high score is achieved
// lights are flashed.
// For the "Accelerometer High Score" test in phase 2 documentation
void testHighScoreLED() 
{
  if(abs(yForce) > abs(maxY))
  {
    for(int i = 0; i < 5; ++i)
    {
      lightColor(0, 255, 0);
      delay(500);
      lightColor(0, 0, 0);
      delay(250);
    }
  }
}

// Test to display the current high score
// For the "LCD Scores" test in phase 2 documentation
void testHighScoreLCD()
{
  if(abs(yForce) > abs(maxY))
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("High Score: " + maxY);
  }
}

// Test for making sure all axes of accelerometer are working
// For "Accelerometer Test" test in phase 2 documentation
void testAxes() 
{
  int16_t ax, ay, az, gx, gy, gz;
  int time = 2500;

  while(--time)
  {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    Serial.println("Accel X: " + ax + " Accel Y: " + ay + " Accel Z: " + az + " Gyro X: " + gx + " Gyro Y: " + gy + " Gyro Z: " + gz);
    // delay to allow for easier reading
    delay(50);
  }
}

// Used to test the buttons properly change the state
// For "State Buttons" test in phase 2 documentation
void testStateButtons()
{
  while(stateButton == 1);
  delay(200);
  Serial.println("State button pressed");
  while(pauseButton == 1);
  delay(200);
  Serial.println("Pause button pressed");
  while(endButton == 1);
  delay(200);
  Serial.println("End button pressed");
}
 
// TODO: get endstate to work when button 3 is pressed
// -------------------------------
// --------Broken code------------
// -------------------------------
// end the game
// void endState() 
// {
//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("Game over.");
//   lcd.setCursor(0, 1);
//   lcd.print("Winner: " + maxY);

//   delay(5000);

//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("Press Button 3");
//   lcd.setCursor(0, 1);
//   lcd.print("to restart.");

//   while(digitalRead(endButton) == 1);
//   delay(200);

//   lcd.clear();
//   lcd.setCursor(0, 0);
//   lcd.print("resetting...");

//   maxY = 0.0;
//   yforce = 0.0;

//   currentState = START;

// }