#define BLYNK_PRINT Serial 
#define BLYNK_TEMPLATE_ID "TMPL3AyrDaxNk"
#define BLYNK_TEMPLATE_NAME "Ecycle"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "4RPO6yjWFZ0l5Evg0r7bMuYAW8hyoO_r "; //Enter the Auth code which was send by Blink
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jaks";  //Enter your WIFI Name
char pass[] = "jatin2002";


int analogPin = A0; // Current sensor output


long int sensorValue = 0;  

float on_voltage = 12.0;

float off_voltage = 11.5;


// refresh interval

uint32_t delayMS = 1000;




int Vsensor = D0; // voltage sensor




// voltage sensor

float correctionfactor = 0; // adjust this for calibration

float vout = 0.0;

float vin = 0.0;


// two resistors 30k and 7.5k ohms

float R1 = 30000;  //  

float R2 = 7500; //  

int value = 0;


char data[80];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
   pinMode(Vsensor, INPUT);
   pinMode(analogPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 sensorValue = analogRead(analogPin);

    // wait 2 milliseconds before the next loop
    delay(200);


 
  Serial.println("ADC Value: ");
  Serial.println(sensorValue);
  Blynk.virtualWrite(V1, sensorValue);

 float vtot = 0.0;

  int loops = 10; // number of samples


  // loop multiple times and get average reading

  for (int i=0; i < loops; i++) {

    vtot = vtot + analogRead(Vsensor);

  }

  value = vtot/loops;


  // voltage calculation

  vout = (value * 3.3) / 1024.0; // 3.3V

  vin = vout / (R2/(R1+R2));

 

  vin = vin - correctionfactor;

 

  Serial.print("Voltage: ");

  Serial.print(vin, 4);

  Serial.println("V");


  // Virtual pin 0 (V0) has voltage value

  sprintf(data, "%.1f", vin);
  Blynk.virtualWrite(V0, vin);
  
   
}
