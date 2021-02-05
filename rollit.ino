#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int pin1 = 2;
int pin2 = 3;
int pin3 = 5;
int AnalogPin=A5;

int Nticks = 0; 
int State;
int LastState; 
int counter=0; 
int counter_state;
int prestate=0;

const float pi = 3.14;
const float R = 3.45;
float batAnalog=0;
int   bat=0;
const int N = 40;

float distance = 0;
float distance1=0;
float distance2=0;
String thisString;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
  

  
void setup() {
  Serial.begin(9600);
 pinMode (pin1 ,INPUT_PULLUP);
  pinMode (pin2 ,INPUT_PULLUP);
  pinMode(pin3,INPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
 
   

  
}

void loop() {

     counter_state=digitalRead(pin3);
   
     
     if(counter_state==HIGH && prestate==0)
     {
      if(counter<=3)
      {
        counter++;
        prestate=1;
      }
     }
     else if(counter_state==LOW)
     {
      prestate=0;
     }
     
     if(counter>3)
     {
      counter=0;
     }
     Serial.print("count");
     Serial.println(counter);
     
    State = digitalRead(pin1);
   if (State != LastState){     
     if (digitalRead(pin2) != State) { 
       Nticks ++;
     } 
     
     else {
       Nticks --;
     }
   } 

  distance = ((2*pi*R)/N) * Nticks ;
  distance=distance*-1;
  thisString = String(distance);
   
  
  LastState = State;

  if (counter==0)
  {
  display.setCursor(10,10);
  display.print(distance);
  display.print(" Cm");
  display.display();
  Serial.println(distance);
  display.clearDisplay();
  }
  if (counter==1)
  {
  distance1=(distance/100);
  display.setCursor(10,10);
  display.print(distance1);
  display.print(" M");
  display.display();
  Serial.println(distance);
  display.clearDisplay();
    
  }
  if (counter==2)
  {
  distance2=(distance*10);
  display.setCursor(10,10);
  display.print(distance2);
  display.print(" mm");
  display.display();
  Serial.println(distance);
  display.clearDisplay();
  }
 if(counter==3)
  {
    batAnalog=analogRead(A5);
    {
      batAnalog=(batAnalog*5.0)/1024.0;
      delay(500);
      bat=((batAnalog/5.0)*100);
      display.setCursor(10,10);
      display.print("Battery aval ");
      display.print(bat);
      display.print("%");
      display.display();
      Serial.println(bat);
      display.clearDisplay();
      
    }
  }
}
  
    
  
  
