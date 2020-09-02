
#include "Lcd1.h"
Lcd1 lcd1(32,4);

#include "Dht1.h"
Dht1 dht1(0,0);

#include "Rtc1.h"
;Rtc1 rtc1;

void setup()
{
  //open serial port
  Serial.begin(9600);

  //LCD Display 32x4 setup
  lcd1.setup();

  //DFT11 setup
  //dht1.setup(-0.5,0);

  //RTC Time setup
  rtc1.setup();

  
  delay(2000);
}

void loop()
{
  delay(1000);
  lcd1.loop();
  dht1.loop();
  rtc1.loop();
}
