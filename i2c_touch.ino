#include <defs.h>
#include <i2c.h>
#include <i2c_touch_sensor.h>
#include <mpr121.h>
#include <types.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

/* GroveI2CTouchTest.pde - Sample code for the SeeedStudio Grove I2C Touch Sensor
http://seeedstudio.com/wiki/index.php?title=Twig_-_I2C_Touch_Sensor_v0.93b  
Prerequisite: A modification of the Grove I2C Touch sensor is needed Solder a pin to
the INT terminal in the I2C sensor to connect it to one pin in Arduino  Created by
Wendell A. Capili, August 27, 2011. http://wendellinfinity.wordpress.com  
Released into the public domain.*/

// include our Grove I2C touch sensor library
// initialize the Grove I2C touch sensor
// IMPORTANT: in this case, INT pin was connected to pin7 of the Arduino 
// (this is the interrupt pin)
i2ctouchsensor touchsensor; // keep track of 4 pads' states
boolean padTouched[4];
int color[][3] = {{255,255,0}, {51, 153, 255} ,{102, 0, 102} , {0, 153, 0}};
String messages[4] = {"curious?   ", "sad?       ", "irritated?", "laugh?       "};
long previousMillis = 0;
long interval = 100;
int last=0;
void setup() 
  {    
    Serial.begin(9600); // for debugging   
      
    Wire.begin(); // needed by the GroveMultiTouch lib     
    touchsensor.initialize(); // initialize the feelers     // initialize the containers     
    
    for(int i=0; i<=3; i++) 
    {          
    padTouched[i]=false;
    lcd.begin(16, 2);
    lcd.print("What made you:");
    }
	
  }
void loop()
{     
   unsigned char MPR_Query=0;
   unsigned long currentMillis = millis();
 if(currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    touchsensor.getTouchState();
  }
 for (int i=0;i<12;i++)
 {
 if (touchsensor.touched&(1<<i)&& i!=last)
 	{
 	//Serial.print("pin ");
        last = i;
        Serial.println(i);
        //Serial.println(" was  touched");
        setColor(i-8);
         }
 }

}
void setColor(int mode){
  int r = color[mode][0];
  int g = color[mode][1];
  int b = color[mode][2];
  lcd.setRGB(r,g,b);
  lcd.setCursor(0,1);
  lcd.print(messages[mode]);
  } 


/*
  touchsensor.readTouchInputs(); // test read the touch sensors     
// loop through our touch sensors 1 to 4    
  for(int i=0; i<=3; i++)
  {          
// get the touch state based on pin #         
    //if(feelers.getTouchState(i)) 
    //{              
      if(!padTouched[i]) 
        {                    // print in serial that it was touched             
        Serial.print("Pad ");                   
        Serial.print(i);                               
        Serial.println(" was touched");             
        //}              
// flag the touch sensor state              
    padTouched[i]=true;         
     }          
  	else 
  	//{             
  	//if(padTouched[i]) 
    {                    
      // print in serial that it was released                                      
      Serial.print("Pad ");                  
      Serial.print(i);                               
      Serial.println(" was released");            
    }               // reset the touch sensor state                      
    padTouched[i]=false;        
   // }    
  }*/


