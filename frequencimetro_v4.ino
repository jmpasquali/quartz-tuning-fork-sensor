#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Oscillator signals  
int Htime;                // integer for high signal
int Ltime;                // integer for low signal
float Ttime;              // integer for storing total time of a cycle
float frequency;          // frequency

// Moving Average
double readings[15];      // the readings from the input
int index = 0;            // the index of the current reading
double total = 0;         // total 
double average = 0;       // average 

int signalPin = 10;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  Serial.begin(9600);
  pinMode(signalPin, INPUT);
  lcd.begin(16, 2);
  for (int i = 0; i < 15; i++) { 
  readings[i] = 0; }

}

void loop() {

  Htime=pulseIn(signalPin,HIGH);      
  Ltime=pulseIn(signalPin,LOW);        
  Ttime = Htime+Ltime;
  
  // getting frequency with Ttime in Micro seconds
  frequency = 1000000/Ttime;    

  // read the signal input
  int signal = digitalRead(signalPin);

  // subtract the last reading:
  total = total - readings[index];  
  readings[index] =  frequency;
  
  // add current reading
  total = total + readings[index];
   
  index++; 
  if (index >= 15) { index = 0;  }  

  // calculate the moving average
  average = total / 15.0; 
  uint16_t int_avg = int(average);
  delay(50);    

  // Display average frequency 
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("FREQUENCIA:");
  lcd.print(" ");
  lcd.setCursor(3, 1);
  lcd.print(" ");
  lcd.print(int_avg);
  lcd.print(" Hz ");
 
  // You can print the frequency to the serial monitor instead
  // Serial.println(int_avg);

  delay(150);
   
}
