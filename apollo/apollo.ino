#include <Wire.h>

int neg2 = 10;
int level = 11;
int pos2 = 12;
int pos1 = 13;

int gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
bool set_gyro_angles;

long acc_x, acc_y, acc_z, acc_total_vector;
float angle_roll_acc, angle_pitch_acc;

float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
float angle_pitch_output, angle_roll_output;

long loop_timer;
int temp;

void setup() {

  // set the registers of the data
  setup_mpu_6050_registers();

  // calibrate the accelerometer for current environment, takes a few seconds
  for(int cal_int = 0; i < 100; ++i) {
    read_mpu_6050_data();

    gyro_x_cal += gyro_x;
    gyro_y_cal += gyro_y;
    gyro_z_cal += gyro_z;
    delay(3);

  }

  // divide to get average, 1000 for the amount of measurements we read above ^^
  gyro_x_cal /= 1000;
  gyro_y_cal /= 1000;
  gyro_z_cal /= 1000;

  // start serial monitor
  // Serial.begin(115200);

  // init timer
  long_timer = mircos();

}

void loop() {

  // get data
  read_mpu_6050_data();

  // subtracting offsets from the raw values
  gyro_x -= gyro_x_cal;
  gyro_y -= gyro_y_cal;
  gyro_z -= gyro_z_cal;

  // note from video: gyro angles calculations 0.0000611 = 1 / (250Hz x 65.5)
  
  // calculate traveled pitch value and add to angle pitch variable
  angle_pitch += gyro_x * 0.0000611;
  // calculate traveled roll value and add to angle roll variable
  angle_roll += gyro_y * 0.0000611;

  // another note: 0.000001066 = 0.000061 * (3.14(PI) / 180degr) the arduino sin function is in radians

  // if IMU has yawed then transfer the roll angle to the pitch angle
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);
  // visa versa
  angle_roll += angle_pitch * sin(gyro_z * 0.000001066);

  // accel angle calculations

  // calc total accel vector
  acc_total_vector = sqrt((acc_x * acc_x) + (acc_y * acc_y) + (acc_z * acc_z));

  // 57.296 = 1 / (3.142 / 180 ) asin function is in radians
  // calc pitch angle
  angle_pitch_acc = asin((float)acc_y / acc_total_vector * 57.296);
  // calc roll angle
  angle_roll_acc = asin((float)acc_x / acc_total_vector * -57.296);

  // accel calibration value for pitch
  angle_pitch_acc += 0.0;
  // accel calibration value for roll
  angle_roll_acc += 0.0;

  

}

// activates the mpu
void setup_mpu_registers() {
  // start communication with mpu6050
  Wire.beginTransmission(0x68);
  // send requested start register
  Wire.write(0x6B);
  // set requested start reg
  Wire.write(0x00);
  // end transmission
  Wire.endTransmission();

  // configure accelerometer to +/-8g

  // start communication with mpu6050
  Wire.beginTransmission(0x68);
  // send requested start register
  Wire.write(0x1C);
  // set requested start reg
  Wire.write(0x10);
  // end transmission
  Wire.endTransmission();

  // configure gryo to 500 dps full scale

  // start communication with mpu6050
  Wire.beginTransmission(0x68);
  // send requested start register
  Wire.write(0x1B);
  // set requested start reg
  Wire.write(0x08);
  // end transmission
  Wire.endTransmission();

}

void read_mpu_6050_data() {
  // read raw accel and gyro values

  // start communication with mpu6050
  Wire.beginTransmission(0x68);
  // send requested start register
  Wire.write(0x3B);
  // end transmission
  Wire.endTransmission();
  // get 14 bytes from mpu 6050
  Wire.requestFrom(0x68, 14);
  // wait until all bytes are received
  while(Wire.available() < 14);

  // leftshift bitwise, then or
  // turns two 8 bit values into a 16 bit value
  acc_x = Wire.read()<<8|Wire.read();
  acc_y = Wire.read()<<8|Wire.read();
  acc_z = Wire.read()<<8|Wire.read();
  temp = Wire.read()<<8|Wire.read();
  gyro_x = Wire.read()<<8|Wire.read();
  gyro_y = Wire.read()<<8|Wire.read();
  gyro_z = Wire.read()<<8|Wire.read();

}
