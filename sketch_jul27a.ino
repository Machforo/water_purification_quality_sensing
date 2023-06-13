const int potPin=A0;
float ph;
float Value=0;

// CODE FOR TDS SENSOR
/*
#define TdsSensorPin A0
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

*/

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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(potPin,INPUT);
  delay(1000);
  pinMode(D5,HIGH);
  pinMode(D6,HIGH);
  pinMode(D7,HIGH);
  /*
   Serial.begin(115200);
  pinMode(TdsSensorPin,INPUT);
   */
}
 void loop(){
 
    Value= analogRead(potPin);
    //Serial.print(Value);
    //Serial.print(" | ");
    float voltage=Value*(3.3/4095.0);
    ph=(3.3*voltage);
    Serial.println(ph);
    /*
     * static unsigned long analogSampleTimepoint = millis();
  if(millis()-analogSampleTimepoint > 40U){     //every 40 milliseconds,read the analog value from the ADC
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    analogBufferIndex++;
    if(analogBufferIndex == SCOUNT){ 
      analogBufferIndex = 0;
    }
  }   
  
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 800U){
    printTimepoint = millis();
    for(copyIndex=0; copyIndex<SCOUNT; copyIndex++){
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
      
      // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0;
      
      //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
      float compensationCoefficient = 1.0+0.02*(temperature-25.0);
      //temperature compensation
      float compensationVoltage=averageVoltage/compensationCoefficient;
      
      //convert voltage value to tds value
      tdsValue=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
      
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      Serial.print("TDS Value:");
      Serial.print(tdsValue,0);
      Serial.println("ppm");
    }
  }
     */

     // TDS SENSOR JUGAAD
     float tds_value=130.0;
     String b1=check(tds_value,ph);
     if(b1.equals("true"))
     {
      Serial.println("SAFE TO DRINK----GREEN LIGHT");
      
     }
     else if(b1.equals("medium"))
     {
      Serial.println("COULD BE USED FOR WASHING PURPOSES-------YELLOW LIGHT");
     }
     else
     {
      Serial.println("VERY DANGEROUS-------RED LIGHT");
     }
     
    delay(500);
    
 }
