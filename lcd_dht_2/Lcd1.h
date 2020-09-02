#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define BACKLIGHT_PIN   7

class Lcd1{
  private:
    int line_w;
    int line_h;

  public:
    Lcd1(int _line_w, int _line_h){
          line_w = _line_w;
          line_h = _line_h;
      }

    void setup(void){
        pinMode ( BACKLIGHT_PIN, OUTPUT );
        digitalWrite ( BACKLIGHT_PIN, HIGH );
        
        lcd.begin(line_w,line_h);               // initialize the lcd 
      
        lcd.home ();                   // go home
 
        displayData("Welcome!","",0);
        displayData("Loading...", "", 1);
      }
    void loop(void){
      }

    void displayData(String info, String value, int line){
          
          lcd.setCursor(0,line);
          lcd.print(info);
          if(value[0] != '\0'){
            if(info[0] != '\0'){
              lcd.print(": ");
            }
            lcd.print(value);
          }

          return;
      }
  };
