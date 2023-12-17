#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#include <Wire.h>
#include "Adafruit_AS726x.h"
#include "Adafruit_SHT31.h"


  #define TFT_CS        10
  #define TFT_CS1        9
  #define TFT_CS2        15
  #define TFT_CS3        16


  //#define TFT_CS1       7
  //#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8

#define WHITE           0x0000
#define BLACK           0xFFFF

#define SENSOR_MAX 5000

#define BLACK   0x0000
#define GRAY    0x8410
#define WHITE   0xFFFF
#define RED     0xF800
#define ORANGE  0xFA60
#define YELLOW  0xFFE0  
#define LIME    0x07FF
#define GREEN   0x07E0
#define CYAN    0x07FF
#define AQUA    0x04FF
#define BLUE    0x001F
#define MAGENTA 0xF81F
#define PINK    0xF8FF
#define SHOCKING_PINK    0xF897	
#define TANGERINE_ORANGE    0xEC20	
#define IVORY     0xFFFD
#define AMBER    0xFDE0
#define CHINA_ROSE    0xA28D
#define DEEP_PINK   0xF8B2
#define ELECTRIC_GREEN    0x07E0

#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(4, 5);

uint16_t colors[] = {
  MAGENTA,
  BLUE,
  GREEN,
  YELLOW,
  ORANGE,
  RED
};

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, -1);
Adafruit_ST7735 tft1 = Adafruit_ST7735(TFT_CS1, TFT_DC, -1);
Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT_CS2, TFT_DC, -1);
Adafruit_ST7735 tft3 = Adafruit_ST7735(TFT_CS3, TFT_DC, -1);



 int inputPin = 2;               // choose the input pin (for PIR sensor)
 int pirState = LOW;             // we start, assuming no motion detected
 int val = 0;                    // variable for reading the pin status
 int randVal = 0; //random value for the motion sensed
 int filler = 0; //this is just to fill an if
 char randMot = ' '; //to send to Max
 int height1 = 0;
 int height2 = 0;
 int height3 = 0;
 int height4 = 0;
 int height5 = 0;
 int height6 = 0;
 int magentaValue = 0;
 int blueValue = 0;
 int greenValue = 0;
 int yellowValue = 0;
 int orangeValue = 0;
 int redValue = 0;
 int airQuality = 0;
//create the object
Adafruit_AS726x ams;

float calibratedValues[AS726x_NUM_CHANNELS];
uint16_t barWidth;

  bool enableHeater = false;
  uint8_t loopCnt = 0;

  Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
      // sensor baud rate is 9600
  pmsSerial.begin(9600);
  
  // Serial.print("Hello! ST77xx TFT Test");
  tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
  tft1.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
  tft2.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
  tft3.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display

  //tft1.initR(INITR_MINI160x80);  // Init ST7735S mini display
  // Serial.println(" Initialized");
  pinMode(inputPin, INPUT);     // declare sensor as input
  //pinMode(inputPin, OUTPUT); //I think this is sending it to max? LOL
  tft.setRotation(1); // rotate 90 degrees
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.setTextWrap(30);

  tft2.setRotation(1); // rotate 90 degrees
  tft2.setTextSize(2);
  tft2.setTextColor(BLACK);
  tft2.setTextWrap(30);

  tft3.setRotation(1); // rotate 90 degrees
  tft3.setTextSize(2);
  tft3.setTextColor(BLACK);
  tft3.setTextWrap(30);



  uint16_t width();
  uint16_t height();


  tft1.setRotation(1);

  tft1.fillScreen(ST7735_BLACK);

  barWidth = tft1.width() / AS726x_NUM_CHANNELS;
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin()){
    // Serial.println("could not connect to sensor! Please check your wiring.");
    while(1);
  }
  else {
    // Serial.println("yay");
  }
  
  ams.setConversionType(MODE_2);

  //uncomment this if you want to use the driver LED (off by default)
  //ams.drvOn();

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  // Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    // Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }

  // Serial.print("Heater Enabled State: ");
  // if (sht31.isHeaterEnabled())
  //   // Serial.println("ENABLED");
  // else
    // Serial.println("DISABLED");

}

  struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
  struct pms5003data data;

void loop() {

  tft.setCursor(10, 10);
  tft.setTextSize(3);

  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    if (pirState == LOW) {
      // we have just turned on
      // Serial.println("Motion detected!");
      // tft.print("Motion detected!");
      tft.drawRect( 0,  0,  200,  100,  IVORY); //drawing the background
      tft.fillRect( 0,  0,  200,  100,  IVORY); //drawing the background
      tft.setTextColor(TANGERINE_ORANGE);
      tft.print("Motion \n Sensed!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      randVal = random(1000);
      //Serial.print(randVal);
      // Serial.print(" ");
      // Serial.print("r");
    }
  } else {
    if (pirState == HIGH){
      // we have just turned of
      // Serial.println("Motion ended!");
      tft.drawRect( 0,  0,  200,  100,  IVORY); //drawing the background
      tft.fillRect( 0,  0,  200,  100,  IVORY); //drawing the background
      tft.setTextColor(SHOCKING_PINK);
      tft.print("Motion \n Ended!");

      // We only want to print on the output change, not state
      pirState = LOW;
    }
      // Serial.print(randVal); //print motion
      if(ams.dataReady()){
    
    //read the values!
    //ams.readRawValues(sensorValues);
    ams.readCalibratedValues(calibratedValues);
    
    for(int i=0; i<AS726x_NUM_CHANNELS; i++){
      uint16_t height = map(calibratedValues[i], 0, SENSOR_MAX, 0, tft1.height());
      uint16_t height1 = map(calibratedValues[0], 0, SENSOR_MAX, 0, tft1.height());
       magentaValue = map(height1, 0, 854, 0, 100);
      uint16_t height2 = map(calibratedValues[1], 0, SENSOR_MAX, 0, tft1.height());
       blueValue = map(height2, 0, 854, 0, 100);
      uint16_t height3 = map(calibratedValues[2], 0, SENSOR_MAX, 0, tft1.height());
       greenValue = map(height3, 0, 854, 0, 100);
      uint16_t height4 = map(calibratedValues[3], 0, SENSOR_MAX, 0, tft1.height());
       yellowValue = map(height4, 0, 854, 0, 100);
      uint16_t height5 = map(calibratedValues[4], 0, SENSOR_MAX, 0, tft1.height());
       orangeValue = map(height5, 0, 854, 0, 100);
      uint16_t height6 = map(calibratedValues[5], 0, SENSOR_MAX, 0, tft1.height());
       redValue = map(height6, 0, 854, 0, 100);
          //Serial.print(magentaValue);
      // // Serial.print(" ");
      // // Serial.print(blueValue); //blue
      // // Serial.print(" ");
      // // Serial.print(greenValue); //green
      // // Serial.print(" ");
      // // Serial.print(yellowValue); //yellow
      // // Serial.print(" ");
      // // Serial.print(orangeValue); //orange
      // // Serial.print(" ");
      // // Serial.print(redValue); //magenta
      // // Serial.print(" ");
      // // Serial.print("Magenta \n");
      // Serial.print(calibratedValues[1]); //blue
      // Serial.print("Blue \n");
      // Serial.print(calibratedValues[2]); //green
      // Serial.print("Green \n");
      // Serial.print(calibratedValues[3]); //yellow
      // Serial.print("Yellow \n");
      // Serial.print(calibratedValues[4]); //orange
      // Serial.print("Orange \n");
      // Serial.print(calibratedValues[5]); //red
      // Serial.print("Red \n");
      tft1.fillRect(barWidth * i, 0, barWidth, tft1.height() - height, ST7735_BLACK);
      tft1.fillRect(barWidth * i, tft1.height() - height, barWidth, height, colors[i]);
      //Serial.print(colors[i]);
    }
      //Serial.print(redValue);

  }
  
}
  if (readPMSdata(&pmsSerial)) {
    // reading data was successful!
    // Serial.println();
    // Serial.println("---------------------------------------");
    // Serial.println("Concentration Units (standard)");
    // Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);
    // Serial.print("\t\tPM 2.5: "); Serial.print(data.pm25_standard);
    // Serial.print("\t\tPM 10: "); Serial.println(data.pm100_standard);
    // Serial.println("---------------------------------------");
    // Serial.println("Concentration Units (environmental)");
    // Serial.print("PM 1.0: "); Serial.print(data.pm10_env);
    // Serial.print("\t\tPM 2.5: "); Serial.print(data.pm25_env);
    // Serial.print("\t\tPM 10: "); Serial.println(data.pm100_env);
    // Serial.println("---------------------------------------");
    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
    // // string1 = '';
    // Serial.println("---------------------------------------");
    //string1 = String(data.particles_100um);
    tft2.setCursor(10, 10);
    tft2.setTextSize(2);
    tft2.drawRect( 0,  0,  160,  80,  WHITE); //drawing the background
    tft2.fillRect( 0,  0,  160,  80,  WHITE); //drawing the background
    tft2.setTextColor(BLACK);
    tft2.drawRect( 0,  0,  200,  100,  IVORY); //drawing the background
    tft2.fillRect( 0,  0,  200,  100,  IVORY); //drawing the background
    tft2.setTextColor(CHINA_ROSE);
    tft2.print("0.3 um \n Particles \n " + String(data.particles_03um)) + "\n";

  }
  float t = sht31.readTemperature();
  float h = sht31.readHumidity();
  // Serial.print(" ");
  // Serial.print(" ");
  // Serial.print(h);
  // Serial.print("r");

  // if (! isnan(t)) {  // check if 'is not a number'
  //   Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  // } else { 
  //   Serial.println("Failed to read temperature");
  // }
  
  // if (! isnan(h)) {  // check if 'is not a number'
  //   Serial.print("Hum. % = \n") + Serial.println(h) + "\n";
  // } else { 
  //   Serial.println("Failed to read humidity");
  // }

  delay(1000);

  // Toggle heater enabled state every 30 seconds
  // An ~3.0 degC temperature increase can be noted when heater is enabled
  if (loopCnt >= 30) {
    enableHeater = !enableHeater;
    sht31.heater(enableHeater);
    // Serial.print("Heater Enabled State: ");
    // if (sht31.isHeaterEnabled())
    //   Serial.println("ENABLED");
    // else
    //   Serial.println("DISABLED");

    loopCnt = 0;
  }
  loopCnt++;

  tft3.setCursor(10, 10);
  tft3.setTextSize(2);
  tft3.drawRect( 0,  0,  160,  80,  IVORY); //drawing the background
  tft3.fillRect( 0,  0,  160,  80,  IVORY); //drawing the background
  tft3.setTextColor(ELECTRIC_GREEN);
  tft3.print(("Temp *C = \n " + String(t) + "\n Hum. % = \n " + String(h)));


  //Serial.print(magentaValue); //magenta
  Serial.print(randVal); //print motion
  Serial.print(" ");
  Serial.print(String(airQuality)); //print air particles
  Serial.print(" ");
  Serial.print(t); //print temperature
  Serial.print(" ");
  Serial.print(h); //print humidity
  
  Serial.print(" ");
  Serial.print(magentaValue);
  Serial.print(" ");
  Serial.print(blueValue);
  Serial.print(" ");
  Serial.print(greenValue);
  Serial.print(" ");
  Serial.print(yellowValue);
  Serial.print(" ");
  Serial.print(orangeValue);
  Serial.print(" ");
  Serial.print(redValue);
  
  // Serial.print(redValue);

  Serial.print("r"); //end statement
}
 
boolean readPMSdata(Stream *s) {
  if (! s->available()) {
    return false;
  }
  
  // Read a byte at a time until we get to the special '0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }
 
  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;
  }
    
  uint8_t buffer[32];    
  uint16_t sum = 0;
  s->readBytes(buffer, 32);
 
  // get checksum ready
  for (uint8_t i=0; i<30; i++) {
    sum += buffer[i];
  }
 
  /* debugging
  for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
  }
  Serial.println();
  */
  
  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }
 
  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);
 
  if (sum != data.checksum) {
    //Serial.println("Checksum failure");
    //airQuality = data.particles_03um;
    return false;
  }
  // success!
      airQuality = data.particles_03um;
  return true;

  float t = sht31.readTemperature();
  float h = sht31.readHumidity();

  // if (! isnan(t)) {  // check if 'is not a number'
  //   Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  // } else { 
  //   Serial.println("Failed to read temperature");
  // }
  
  // if (! isnan(h)) {  // check if 'is not a number'
  //   Serial.print("Hum. % = "); Serial.println(h);
  // } else { 
  //   Serial.println("Failed to read humidity");
  // }

  delay(1000);

  // Toggle heater enabled state every 30 seconds
  // An ~3.0 degC temperature increase can be noted when heater is enabled
  if (loopCnt >= 30) {
    enableHeater = !enableHeater;
    sht31.heater(enableHeater);
    // Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      // Serial.println("ENABLED");
      filler = 0;

    else
      // Serial.println("DISABLED");

    loopCnt = 0;
  }
  loopCnt++;

  }

  //String sensorVal = String(analogRead(A0));

  //sensorVal.toCharArray(sensorPrintout, 4);
