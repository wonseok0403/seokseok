#include <MS561101BA.h>
// coded wonseok start
#include<SPI.h>
#include<SD.h>
File myFile; 
//

/*
 * GY-86 
 *
 * GY-86�� MPU6050 媛��냽�룄 �옄�씠濡� �꽱�꽌, HMC5883L 吏��옄湲� �꽱�꽌 洹몃━怨�
 * MS561101BA 湲곗븬 �꽱�꽌瑜� 議곌렇留� 蹂대뱶�뿉 紐⑤몢 媛뽰텣 10 DOF(Degrees Of
 * Freedom)瑜� 吏��썝�븯�뒗 湲곌린�엯�땲�떎.
 *
 * �씠 �뒪耳�移섎뒗 
 *
 * - MPU6050�쑝濡쒕��꽣 媛�怨듯븯吏� �븡�� 媛��냽�룄, �옄�씠濡� �꽱�꽌�쓽 16鍮꾪듃
 *   �뜲�씠�꽣�뱾�씤 ax, ay, az, gx, gy, gz �벑�쓣 �씫�뼱�궡怨�,
 * 
 * - 吏��옄湲� �꽱�꽌 �뜲�씠�꽣�뒗 MPU6050�쓣 �넻�븯�뿬 HMC5883L濡쒕��꽣 16鍮꾪듃
 *   �뜲�씠�꽣 mx, my, mz瑜� �씫�뼱 �깄�땲�떎
 *
 * - 湲곗븬 �꽱�꽌 MS561101BA瑜� �넻�븯�뿬 �삩�룄, 湲곗븬 洹몃━怨� �빐硫� �넂�씠瑜�
 *   �씠�슜�븯�뿬 �넂�씠瑜� 痢≪젙�빀�땲�떎.
 * 
 */
 
/*
 * I2Cdev�� MPU6050 �씪�씠釉뚮윭由щ뱾�씠 �꽕移섎릺 �엳�뼱�빞 �븯硫�, I2Cdev媛� 
 * �븘�몢�씠�끂�쓽 Wire 湲곕컲�쑝濡� 媛쒕컻�릺�뼱 �엳�떎硫�, Wire �씪�씠釉뚮윭由ш�
 * �븘�슂�빀�땲�떎.
 */
#include "I2Cdev.h"
#include "MPU6050.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include <Wire.h>
#endif

/*
 * MS561101BA 湲곗븬怨꾨�� �쐞�븳 �씪�씠釉뚮윭由ш� �꽕移섎릺 �엳�뼱�빞 �빀�땲�떎.
 */
#include <MS561101BA.h>

#define HMC5883L_DEFAULT_ADDRESS    0x1E
#define HMC5883L_RA_DATAX_H         0x03
#define HMC5883L_RA_DATAZ_H         0x05
#define HMC5883L_RA_DATAY_H         0x07

// MPU6050 I2C 二쇱냼�뒗 湲곕낯�쟻�쑝濡� 0x68�씠硫�, AD0瑜� HIGH濡� �넃�쑝硫�
// 二쇱냼瑜� 0x69濡� �궗�슜�븷 �닔 �엳�뒿�땲�떎. 
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- AD0媛� HIGH濡� 二쇱냼瑜� 0x69瑜� �궗�슜�븷 寃쎌슦

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;

float heading;

/* Note:
 * ====
 * �젙�솗�븳 �넂�씠瑜� 痢≪젙�븯湲� �쐞�빐�꽌�뒗 �빐硫� 湲곗븬 �젙蹂대�� �궗�슜�븯�뿬�빞 �빀�땲�떎.
 * http://www.kma.go.kr/weather/observation/aws_table_popup.jsp 濡쒕��꽣
 * 湲곗븬 �젙蹂대�� �뼸�뼱 sea_press�뿉 �꽔�뿀�뒿�땲�떎.
 */
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
 
  
  // I2C 踰꾩뒪瑜� �궗�슜�븯湲� �쐞�븯�뿬 Wire.begin()瑜� �떎�뻾�빀�땲�떎. (I2Cdev
  // �씪�씠釉뚮윭由ъ뿉�꽌 �씠瑜� �옄�룞�쑝濡� �떎�뻾移� �븡湲� �븣臾몄엯�땲�떎)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 12; // 400kHz I2C clock (200kHz if CPU is 8MHz)

#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  // �떆由ъ뼹 �넻�떊�쓣 115200bps濡� 珥덇린�솕�빀�땲�떎
  Serial.begin(115200);
  
  // I2C 踰꾩뒪�뿉 �뿰寃곕릺�뼱 �엳�뒗 湲곌린�뱾�쓣 珥덇린�솕�빀�땲�떎
  Serial.println(F("I2C 湲곌린�뱾 珥덇린�솕 以�..."));
  mpu.initialize();

  // �뿰寃곗쓣 寃�利앺빀�땲�떎.
  Serial.println(F("湲곌린 �뿰寃� �떆�뿕 以�..."));
  Serial.print(F("MPU6050 �뿰寃� "));
  Serial.println(mpu.testConnection() ? F("�젙�긽") : F("�삤瑜�"));

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
   * 吏��옄湲� �꽱�꽌 HMC5883L�� MPU6050�쓽 蹂댁“ I2C 踰꾩뒪�뿉 �뿰寃곕릺�뼱 �엳�뼱,
   * MPU6050�쓣 �넻�븯�뿬 吏��옄湲� �꽱�꽌瑜� �씫�뼱 �궪 �닔 �엳�뒿�땲�떎. �씠瑜� �쐞�븳
   * �솚寃� 援ъ꽦�쓣 吏꾪뻾�빀�땲�떎.
   *
   * 1. MPU6050�쓽 蹂댁“ I2C 踰꾩뒪瑜� 吏곸젒 R/W�븯湲� �쐞�븯�뿬 留덉뒪�꽣 紐⑤뱶瑜�
   *    以묒��븯怨�, 諛붿씠�뙣�뒪 紐⑤뱶瑜� �솢�꽦�솕�빀�땲�떎.
   *
   * 2. HMC5883L 紐⑤뱶瑜� �뿰�냽 痢≪젙 紐⑤뱶濡� 痢≪젙 媛꾧꺽�쓣 75Hz濡� �꽕�젙�빀�땲�떎
   *
   * 3. 諛붿씠�뙣�뒪 紐⑤뱶瑜� 鍮꾪솢�꽦�솕(以묒�)�빀�땲�떎
   *
   * 4. MPU6050�뿉寃� mx, my, mz瑜� �씫�뼱�뱾�씠湲� �쐞�븳 HMC5883L �젅吏��뒪�꽣 二쇱냼
   *    洹몃━怨� �씫�뼱�뱾�씤 �뜲�씠�꽣�쓽 MSB�� LSB瑜� 諛붽퓭�빞 �븯�뒗吏�, �뜲�씠�꽣 �겕湲�
   *    �벑�쓣 �꽕�젙�빀�땲�떎.
   *
   * 5. 理쒖쥌�쟻�쑝濡� HMC5883L濡쒕��꽣 吏��옄湲� �꽱�꽌 �뜲�씠�꽣�뒗 MPU6050�쓣 �넻�븯�뿬
   *    �씫�뼱�뱾�씤�떎怨� 留덉뒪�꽣 紐⑤뱶瑜� �솢�꽦�솕�빀�땲�떎. 
   * 
   */ 
  mpu.setI2CMasterModeEnabled(0);
  mpu.setI2CBypassEnabled(1);

  Wire.beginTransmission(HMC5883L_DEFAULT_ADDRESS);
  Wire.write(0x02); 
  Wire.write(0x00);  // �뿰�냽 �씫湲� 紐⑤뱶濡� �꽕�젙
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(HMC5883L_DEFAULT_ADDRESS);
  Wire.write(0x00);
  Wire.write(B00011000);  // 75Hz
  Wire.endTransmission();
  delay(5);

  mpu.setI2CBypassEnabled(0);

  // X 異� WORD 
  /* 0x80�� 7踰덉㎏ 鍮꾪듃瑜� 1濡� 留뚮벊�땲�떎. MPU6050 �뜲�씠�꽣 �옄猷뚯뿉 �씫湲� 紐⑤뱶
   * �꽕�젙�� '1'濡� �벐湲� 紐⑤뱶 �꽕�젙�� '0'濡� �븯�뿬�빞 �븳�떎怨� �굹�� �엳�뒿�땲�떎. */
  mpu.setSlaveAddress(0, HMC5883L_DEFAULT_ADDRESS | 0x80);
  mpu.setSlaveRegister(0, HMC5883L_RA_DATAX_H);
  mpu.setSlaveEnabled(0, true);
  mpu.setSlaveWordByteSwap(0, false);
  mpu.setSlaveWriteMode(0, false);
  mpu.setSlaveWordGroupOffset(0, false);
  mpu.setSlaveDataLength(0, 2);

  // Y 異� WORD
  mpu.setSlaveAddress(1, HMC5883L_DEFAULT_ADDRESS | 0x80);
  mpu.setSlaveRegister(1, HMC5883L_RA_DATAY_H);
  mpu.setSlaveEnabled(1, true);
  mpu.setSlaveWordByteSwap(1, false);
  mpu.setSlaveWriteMode(1, false);
  mpu.setSlaveWordGroupOffset(1, false);
  mpu.setSlaveDataLength(1, 2);

  // Z 異� WORD
  mpu.setSlaveAddress(2, HMC5883L_DEFAULT_ADDRESS | 0x80);
  mpu.setSlaveRegister(2, HMC5883L_RA_DATAZ_H);
  mpu.setSlaveEnabled(2, true);
  mpu.setSlaveWordByteSwap(2, false);
  mpu.setSlaveWriteMode(2, false);
  mpu.setSlaveWordGroupOffset(2, false);
  mpu.setSlaveDataLength(2, 2);

  // HMC5883L�� MPU6050�쓣 �넻�븯�뿬 �씫�쓣 �닔 �엳�뼱, 留덉뒪�꽣 紐⑤뱶瑜� ON�빀�땲�떎
  mpu.setI2CMasterModeEnabled(1);

  // 湲곗븬怨꾨�� 珥덇린�솕�빀�땲�떎
  
  baro.init();
  delay(100);
  
  // �룊洹� �븬�젰 �젙蹂대�� �뼸湲� �쐞�븯�뿬 誘몃━ 媛믪쓣 珥덇린�솕 �빀�땲�떎
  for(int i=0; i<MOVAVG_SIZE; i++) {
    float p = baro.getPressure();
    if(p == NULL)
      p = STANDARD_SEA_PRESSURE;
      
    movavg_buff[i] = p;    
  }
    
  // �떆由ъ뼹 紐⑤땲�꽣濡쒕��꽣 �떆�옉 �뜲�씠�꽣瑜� 湲곕떎由쎈땲�떎
  /*
  Serial.println(F("\n以�鍮꾨릺�뿀�쑝硫� �뜲�씠�꽣瑜� 蹂대궡�꽭�슂: "));
  while (Serial.available() && Serial.read()); // 踰꾪띁瑜� 鍮꾩썎�땲�떎
  while (!Serial.available());                 // �뜲�씠�꽣瑜� 湲곕떎由쎈땲�떎
  while (Serial.available() && Serial.read()); // 踰꾪띁瑜� �떎�떆 吏��썎�땲�떎
  
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
  // MPU6050�쑝濡쒕��꽣 媛��냽�룄 �옄�씠濡� �꽱�꽌�쓽 媛�怨듯븯吏� �븡�� �뜲�씠�꽣瑜� �씫�뼱
  // �뱾�엯�땲�떎
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  // MPU6050�쓣 �넻�븯�뿬 HMC5883L 吏��옄湲� �꽱�꽌 �뜲�씠�꽣 媛믪쓣 �씫�뼱 �뱾�엯�땲�떎
  mx=mpu.getExternalSensorWord(0);
  my=mpu.getExternalSensorWord(2);
  mz=mpu.getExternalSensorWord(4);
 
  // �뼱�뵒瑜� �뼢�븯怨� �엳�뒗 heading 媛믪쓣 援ы빀�땲�떎. 留뚯빟 - 媛믪씠硫� �씠瑜� +
  // 媛믪쑝濡� 諛붽퓠�땲�떎 
  heading = atan2(my, mx);
  if(heading < 0) heading += 2 * M_PI;

  // �넂�씠瑜� 痢≪젙�븯�뿬 altitude�뿉 ���옣�빀�땲�떎.
  altitude = getAltitude();
  
  // 媛��냽�룄/�옄�씠濡�/吏��옄湲� x/y/z 媛믩뱾�쓣 �떆由ъ뼹 紐⑤땲�꽣濡� 異쒕젰�빀�땲�떎
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
  // Processing Compass �뒪耳�移섏� �룞�옉�떆�궎湲� �쐞�븳 heading �뜲�씠�꽣瑜�
  // 異쒕젰�빀�땲�떎.
  Serial.print('@');
  Serial.println(heading, 6);
  
  // �삩�룄�� 湲곗븬 洹몃━怨� �넂�씠瑜� 異쒕젰�빀�땲�떎
  Serial.print(temperature);
  Serial.print(F(" �꼦 湲곗븬: "));
  Serial.print(pressure);
  Serial.print(F(" mbar 怨좊룄: "));
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

