#include <rgb_lcd.h>

  /******************************************************************************/
    /*macro definitions of Rotary angle sensor and LED pin*/
    #include <Wire.h>
    #include "rgb_lcd.h"
    #define Sensor1 A0
    #define Sensor2 A1
    #define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
                     //board switches to 3V3, the ADC_REF should be 3.3
    #define GROVE_VCC 5//VCC of the grove interface is normally 5v
    #define FULL_ANGLE 300//full value of the rotary angle is 300 degrees
    rgb_lcd lcd;
    int degrees1;
    int degrees2;
    
    void setup() 
    {
        Serial.begin(9600);
        //pinMode(ROTARY_ANGLE_SENSOR, INPUT);
        //pinMode("rgb_lcd.h", OUTPUT);
        lcd.begin(16, 2);
        lcd.setRGB(0,0,0);
       
    }

    void loop() 
    {
        lcd.setCursor(0, 1);

        degrees1 = getDegree1();
        Serial.println(degrees1);
        degrees2 = getDegree2();

        
        int converter = 255/50;

       
        if (degrees1 <= 50){
          changeColor(255, converter*degrees1, 0);
        }

        else if (degrees1 >= 50 and degrees1 <= 100){
          changeColor(255-converter*(degrees1-50), 255, 0);
        }

        else if (degrees1 >= 100 and degrees1 <=150){
          changeColor(0, 255, converter*(degrees1-100));
        }

        else if (degrees1 >= 150 and degrees1 <=200){
          changeColor(0, 255-converter*(degrees1-150), 255);
        }

        else if (degrees1 >= 200 and degrees1 <=250){
          changeColor(converter*(degrees1-200), 0, 255);
        }

        else if (degrees1 >= 250 and degrees1 <=300){
          changeColor(255-converter*(degrees1-250), 0, 255- converter*(degrees1-250));
        }
//////////////////////////////////////////////////////////

         if (degrees2 <= 30){
          lcd.print("energized");
        }

//        else if (degrees2 >= 20 and degrees2 <= 40){
//          lcd.print("excited  ");
//        }

        else if (degrees2 > 30 and degrees2 <=60){
          lcd.print("hopeful   ");
        }

        else if (degrees2 > 30 and degrees2 <=60){
          lcd.print("proud      ");
        }

        else if (degrees2 > 60 and degrees2 <=90){
          lcd.print("relaxed      ");
        }

//        else if (degrees2 >= 100 and degrees2 <=120){
//          lcd.print("thankful   ");
//        }

        else if (degrees2 > 90 and degrees2<= 120){
          lcd.print("loving     ");
        }

        else if (degrees2 > 120 and degrees2 <= 150){
          lcd.print("tired     ");
        }

        else if (degrees2 > 150 and degrees2 <=180){
          lcd.print("bored    ");
        }

        else if (degrees2 > 180 and degrees2 <=210){
          lcd.print("lonely     ");
        }

        else if (degrees2 > 210 and degrees2 <=240){
          lcd.print("frustrated      ");
        }

//        else if (degrees2 >= 240 and degrees2 <=260){
//          lcd.print("irritated     ");
//        }
        
        else if (degrees2 > 240 and degrees2 <=270){
          lcd.print("confused      ");
        }

        else if (degrees2 > 270 and degrees2 <=300){
          lcd.print("anxious    ");
        }
        delay(100);
    }  

    /*PWM control brightness                        */
    /*If brightness is 0,the LED is off.            */
    /*The Greater the brightness, the brighter the LED.*/
    /*The range of brightness is 0~255              */

    void changeColor(int r, int g, int b)
    {
        lcd.setRGB(r,g,b);
    }
    
    /************************************************************************/
    /*Function: Get the angle between the mark and the starting position    */
    /*Parameter:-void                                                       */
    /*Return:   -int,the range of degrees is 0~300                          */
    int getDegree1()
    {
        int sensor_value = analogRead(Sensor1);
        float voltage;
        voltage = (float)sensor_value*ADC_REF/1023;
        float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
        return degrees;
    }

    int getDegree2()
    {
        int sensor_value = analogRead(Sensor2);
        float voltage;
        voltage = (float)sensor_value*ADC_REF/1023;
        float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
        return degrees;
    }
