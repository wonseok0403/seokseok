#include <MS561101BA.h>
// coded wonseok start
#include<SPI.h>
#include<SD.h>
File myFile; 
//

/*==================================================================================================================================
 * Wonseok Arduino Rocekt System log.
 * You must check your gylo sensor system is GY-86 and SD Moudle is DFRobot MicroSD for Arduino.
 * This ardino system can excute Rocket parachute system.
 * The system named 'RELAY' will make your system excute variously and effectively.
 * 
 * MICRO SD MODULE -
 * MISO 12
 * SCK 13
 * SS 4
 * MOSI 11
 * ==================================================================================================================================
 */
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include <Wire.h>
#endif

/*
 * MS561101BA header file will be needed
 */
#include <MS561101BA.h>

#define HMC5883L_DEFAULT_ADDRESS    0x1E
#define HMC5883L_RA_DATAX_H         0x03
#define HMC5883L_RA_DATAZ_H         0x05
#define HMC5883L_RA_DATAY_H         0x07

// I don't know this logs because this file is made by other programmer

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

float heading;
MS561101BA baro = MS561101BA();

#define MOVAVG_SIZE             32
#define STANDARD_SEA_PRESSURE  1013.25
/* Wonseok Edited */
#define Para_delay A3


const float sea_press = 1014.0;
float altitude, temperature, pressure;
float movavg_buff[MOVAVG_SIZE];
int movavg_i=0;

void setup() {
 
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 12; // 400kHz I2C clock (200kHz if CPU is 8MHz) - other programmer

#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(115200);
  
  Serial.println(F("I2C MPU initalizing starts ..."));
  mpu.initialize();

  Serial.println(F("Ready to system checking ..."));
  Serial.print(F("MPU6050 connection starts "));
  Serial.println(mpu.testConnection() ? F("Connection completed") : F("Connection failed"));

   /* Wonseok Source */
  pinMode(Para_delay, OUTPUT);
  if(!SD.begin(4)){
    Serial.println("initalization failed");
    return ;
  }
  Serial.println("initalization Succeed!");
  myFile = SD.open("test.txt", FILE_WRITE);

  if(myFile){
    Serial.print("Writing to Report.txt ... ");
    myFile.println("Testing .. done!");
    myFile.close();
    Serial.println("Done!");
  }
  else{
    Serial.println("Error opening test.txt");
  }

  ///
  
  /*
   * log by wonseok
   * If you want to make system add other equipments or finialzie or confirm other system, You need to understand how to activate
   * and your arduino source will be boombed by "No header file"
   * So you need to be updated and download other headerfiles.
   * And this system was excuted in ARDUINO UNO, ARDUINO NANO but your system has to be set UNO MODE or NANO MODE
   * other mode is not sured
   */ 
  mpu.setI2CMasterModeEnabled(0);
  mpu.setI2CBypassEnabled(1);

  Wire.beginTransmission(HMC5883L_DEFAULT_ADDRESS);
  Wire.write(0x02); 
  Wire.write(0x00);  
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(HMC5883L_DEFAULT_ADDRESS);
  Wire.write(0x00);
  Wire.write(B00011000);  // 75Hz
  Wire.endTransmission();
  delay(5);

  mpu.setI2CBypassEnabled(0);

  mpu.setSlaveAddress(0, HMC5883L_DEFAULT_ADDRESS | 0x80);
  mpu.setSlaveRegister(0, HMC5883L_RA_DATAX_H);
  mpu.setSlaveEnabled(0, true);
  mpu.setSlaveWordByteSwap(0, false);
  mpu.setSlaveWriteMode(0, false);
  mpu.setSlaveWordGroupOffset(0, false);
  mpu.setSlaveDataLength(0, 2);

  // Y �빊占� WORD
  mpu.setSlaveAddress(1, HMC5883L_DEFAULT_ADDRESS | 0x80);
  mpu.setSlaveRegister(1, HMC5883L_RA_DATAY_H);
  mpu.setSlaveEnabled(1, true);
  mpu.setSlaveWordByteSwap(1, false);
  mpu.setSlaveWriteMode(1, false);
  mpu.setSlaveWordGroupOffset(1, false);
  mpu.setSlaveDataLength(1, 2);

  // Z �빊占� WORD
  mpu.setSlaveAddress(2, HMC5883L_DEFAULT_ADDRESS | 0x80);
  mpu.setSlaveRegister(2, HMC5883L_RA_DATAZ_H);
  mpu.setSlaveEnabled(2, true);
  mpu.setSlaveWordByteSwap(2, false);
  mpu.setSlaveWriteMode(2, false);
  mpu.setSlaveWordGroupOffset(2, false);
  mpu.setSlaveDataLength(2, 2);

  mpu.setI2CMasterModeEnabled(1);

  
  baro.init();
  delay(100);
  
  for(int i=0; i<MOVAVG_SIZE; i++) {
    float p = baro.getPressure();
    if(p == NULL)
      p = STANDARD_SEA_PRESSURE;
      
    movavg_buff[i] = p;    
  }
    
  /*
  Serial.println(F("\n ?? : "));
  while (Serial.available() && Serial.read()); 
  while (!Serial.available());              
  while (Serial.available() && Serial.read()); 
  
  */
  myFile.close();
}

void loop() {
  
  File myFile = SD.open("Report.txt", FILE_WRITE);
  if( !myFile ){
    Serial.println("Something problem");
  }
  else{
    Serial.println("Succed Report.txt");
  }
   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  mx=mpu.getExternalSensorWord(0);
  my=mpu.getExternalSensorWord(2);
  mz=mpu.getExternalSensorWord(4);
  heading = atan2(my, mx);
  if(heading < 0) heading += 2 * M_PI;
 altitude = getAltitude();
  
  Serial.println(F("a/g/m:\tax\tay\taz\tgx\tgy\tgz\tmx\tmy\tmz"));
  Serial.print(F("a/g/m:\t"));
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.print(gz); Serial.print("\t");
  Serial.print(mx); Serial.print("\t");
  Serial.print(my); Serial.print("\t");
  Serial.print(mz); Serial.print("\n");

  /////////////////////
  myFile.println(F("a/g/m:\tax\tay\taz\tgx\tgy\tgz\tmx\tmy\tmz"));
  myFile.print(F("a/g/m:\t"));
  myFile.print(ax); myFile.print("\t");
  myFile.print(ay); myFile.print("\t");
  myFile.print(az); myFile.print("\t");
  myFile.print(gx); myFile.print("\t");
  myFile.print(gy); myFile.print("\t");
  myFile.print(gz); myFile.print("\t");
  myFile.print(mx); myFile.print("\t");
  myFile.print(my); myFile.print("\t");
  myFile.print(mz); myFile.print("\n");
  myFile.close();
  ////////////////////////

  if( mz > -150 ){
    digitalWrite(Para_delay, HIGH);
  }
    else digitalWrite(Para_delay, LOW);
  Serial.print('@');
  Serial.println(heading, 6);
  
  Serial.print(temperature);
  Serial.print(F(" 占쎄샷 疫꿸퀣釉�: "));
  Serial.print(pressure);
  Serial.print(F(" mbar �⑥쥓猷�: "));
  Serial.print(altitude);
  Serial.println(F("m"));
  
}

float getAltitude() {
  float temp;
  temp = baro.getTemperature();
  if(temp) {
    temperature =temp;
  }
  delay(100);
  
  pressure = baro.getPressure();
  
  if(pressure != NULL) {
    pushAvg(pressure);
  }
  
  pressure = getAvg(movavg_buff, MOVAVG_SIZE);
  
  return ((pow((sea_press / pressure), 1/5.257) - 1.0) * (temperature + 273.15)) / 0.0065;
}

void pushAvg(float val) {
  movavg_buff[movavg_i] = val;
  movavg_i = (movavg_i + 1) % MOVAVG_SIZE;
}

float getAvg(float * buff, int size) {
  float sum = 0.0;
  for(int i=0; i<size; i++) {
    sum += buff[i];
  }
  return sum / size;
}

