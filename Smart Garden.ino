#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define TempSensor 5
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(TempSensor);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int val = 0;
int TempPin = A0;
int moisturePin1 = A1;
int moisturePin2 = A2;
int Moisture1 = 3;
int Moisture2 = 4;
int output;
int motorPin1 = 12;
int motorPin2 = 13;

void setup() 
{
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  Serial.begin(9600);   // open serial over USB
  pinMode(Moisture1, OUTPUT);
  digitalWrite(Moisture1, LOW);
  pinMode(Moisture2, OUTPUT);
  digitalWrite(Moisture2, LOW);
}

void loop() 
{
delay(5000);
Serial.println(tempsensor());
Serial.print("Water In Sector 1 = ");    
Serial.println(readMoisture1());
Serial.print("Water In Sector 2 = ");    
Serial.println(readMoisture2());
delay(5000);

tempsensor();
moisture1();
moisture2();

}
//This is a function used to get the soil moisture content

int readMoisture1()
{
    output = analogRead(moisturePin1);
    output = map(output,0,1024,100,0);
    Serial.print(output);
    Serial.println("%.\n");
    delay(1000);
}

int readMoisture2()
{
    output = analogRead(moisturePin2);
    output = map(output,0,1024,100,0);
    Serial.print(output);
    Serial.println("%.\n");
    delay(1000);
}

void moisture1()
       {
      if(analogRead(moisturePin1) >= 512)     
     {
      Serial.print("Watering Sector 1");
      digitalWrite(motorPin1,HIGH);   //set pin high
      delay(2000);  
     }
     else
     {
       digitalWrite(motorPin1,LOW);   //set pin low
     }
       }

void moisture2()
      {
      if(analogRead(moisturePin2) >= 512)
     {
      Serial.print("Water Sector 2");
      digitalWrite(motorPin1,HIGH);   //set pin high
      delay(2000);  
     }
     else
     {
      digitalWrite(motorPin2,LOW);   //set pin low 
     }
      }
  
void tempsensor()
     {
       // Send the command to get temperatures
  sensors.requestTemperatures();  
  Serial.print("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  //Update value every 1 sec.
  delay(1000);
     }