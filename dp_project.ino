#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;
#include <Arduino.h>;
#include "E:\DP\model (1).h" ;//the classifier model
#include <Wire.h>; //I2C protocol


//#include <Adafruit_MPU6050.h> ;//to use the MPU6050 accelerometer
//#include <Adafruit_Sensor.h>; //to use the adafruit sensors


//Adafruit_MPU6050 accelerometer; //instanciate the accelerometer object 
Eloquent::ML::Port::SVM classifier;//instanciate the classifier object 

const char* ssid = "Quality_Sensing 1.0";
const char* password = "12345678";
AsyncWebServer server(80);

double TDS=450.0;
double pH=7.5;
double Status=1.0;



//const int potPin=A0;
float ph;
float Value=0;
unsigned long int avgValue;  //Store the average value of the sensor feedback

float b;

float buf[10];
int temp;


// CODE FOR TDS SENSOR
#define phSensorPin A0
#define TdsSensorPin D4
#define VREF 3.3              // analog reference voltage(Volt) of the ADC
#define SCOUNT  30            // sum of sample point

int analogBuffer[SCOUNT];     // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 23;       // current temperature for compensation

// median filtering algorithm
int getMedianNum(int bArray[], int iFilterLen){
  int bTab[iFilterLen];
  for (byte i = 0; i<iFilterLen; i++)
  bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0){
    bTemp = bTab[(iFilterLen - 1) / 2];
  }
  else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}



//TDS SENSOR JUGAAD
String check(float tds, float ph)
{
  String b;
  if(tds>100.0 && tds<300.0 && ph>0.5 && ph<2.0)
  {
    b="true";
  }
  else if((tds<100.0 && ph<0.5)|| (tds>300.0 && ph>2.0))
  {
    b="HARMFUL";
  }
  else
  {
    b="medium";
  }
  return b;
}

//JUGAAD 2 ML MODEL
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   Wire.begin(); //begin the I2C communication
  //pinMode(potPin,INPUT);
  //model.begin();
  WiFi.softAP(ssid, password);
  Serial.println("AP IP Address: ");
  Serial.println(WiFi.softAPIP());
  // Add handlers for incoming HTTP requests
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    double myArray[3] = {TDS, pH, Status}; // example array of size 3
    String response = String(myArray[0]) + "," + String(myArray[1]) + "," + String(myArray[2]);
    request->send(200, "text/plain", response);
  });
  
  // Start the server
  server.begin();
  pinMode(D5,HIGH);
  pinMode(D6,HIGH);
  pinMode(D7,HIGH);
  ads.setGain(GAIN_ONE);
  ads.begin();
  
   //delay(1000);
   //Serial.begin(115200);
 // pinMode(TdsSensorPin,INPUT);
  //pinMode(phSensorPin,INPUT);
}
 void loop(){
 
    //Value= analogRead(potPin);
    //Serial.print(Value);
    //Serial.print(" | ");
    //float ph = 7- ((Value/1024.0)*5.0);
    //float ph=3.82;
    //Serial.println("ph value");
    //Serial.println(ph);
    int16_t adc0,adc1;
    for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value

  {
    //Serial.print("DONE");
   adc0=ads.readADC_SingleEnded(1);
   //Serial.println(adc0);
   if(adc0<0)
       {
        adc0=-1*adc0;
       }
   
    buf[i]=(adc0*0.125);
    //Serial.println(buf[i]);

    delay(10);

  }
  

  for(int i=0;i<9;i++)        //sort the analog from small to large

  {

    for(int j=i+1;j<10;j++)

    {

      if(buf[i]>buf[j])

      {

        temp=buf[i];

        buf[i]=buf[j];

        buf[j]=temp;

      }

    }

  }

  avgValue=0;

  for(int i=2;i<8;i++)                      //take the average value of 6 center sample

    avgValue+=buf[i];

  pH=5.0+(float)avgValue*5.0/1024/6; //convert the analog into millivolt

  //phValue=3*phValue;                      //convert the millivolt into pH value
  Serial.print("    pH:");  
  Serial.print(pH,2);
  Serial.println(" ");
    delay(1000);
    /*
    float voltage=Value*(5.0/1023);
    Serial.println(voltage);
    ph=(5*voltage);
    Serial.println(ph);
    */

    /*
 
     static unsigned long analogSampleTimepoint = millis();
  if(millis()-analogSampleTimepoint > 40U){     //every 40 milliseconds,read the analog value from the ADC
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    analogBufferIndex++;
    if(analogBufferIndex == SCOUNT){ 
      analogBufferIndex = 0;
    }
  }   
  */
  /*
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 800U){
    printTimepoint = millis();
    for(copyIndex=0; copyIndex<SCOUNT; copyIndex++){
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
      
      // read the analog value more stable by the median filtering algorithm, and convert to voltage value

 */
       
       adc1=ads.readADC_SingleEnded(0);
       Serial.println(adc1);
       if(adc1<0)
       {
        adc1=-1*adc1;
       }
       TDS= adc1*0.125 ;
       TDS=TDS+300;
       //Serial.print("fibal");
       Serial.println(TDS);     
      //averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0;
      
      //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
      //float compensationCoefficient = 1.0+0.02*(temperature-25.0);
      //temperature compensation
      //float compensationVoltage=averageVoltage/compensationCoefficient;

      //convert voltage value to tds value
      //tdsValue=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
      
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      //Serial.print("TDS Value:");
      //Serial.print(analogre,2);
      //Serial.println("ppm");
    

     // TDS SENSOR JUGAAD
     //tdsValue=130.0;
     float ke=0.7;
     float cond=TDS/ke;
     Serial.println("CONDUCTIVITY");
     Serial.println(cond);
     //String b1=check(tds_value,ph);
     //sensors_event_t g; //instanciate the sensors's reading object 
     //accelerometer.getEvent(&g);//register the read values to the object declared before
     float features[] = {pH,cond}; //create the array containing the read values size is : 1x3 same as defined in google colab
     int output_str = classifier.predict(features); //run inference
     Serial.println(output_str);//print the resulting orientation
     Status=double(output_str);
     Serial.println(Status);
     if(output_str==2)
     {
      Serial.println("SAFE TO DRINK----GREEN LIGHT");
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D5,HIGH);
      
     }
     else if(output_str==1)
     {
      Serial.println("COULD BE USED FOR WASHING PURPOSES-------YELLOW LIGHT");
      digitalWrite(D5,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D6,HIGH);
      
     }
     else
     {
      Serial.println("VERY DANGEROUS-------RED LIGHT");
      digitalWrite(D6,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D7,HIGH);
     }
  
    delay(1600);
    
 }
