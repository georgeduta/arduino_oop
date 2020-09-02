
// CONNECTIONS:
//#### Default ####
// DS1302 CLK/SCLK --> 5
// DS1302 DAT/IO --> 4
// DS1302 RST/CE --> 2
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

//##### Actual wires ####
// DS1302 CLK/SCLK --> 2
// DS1302 DAT/IO --> 3
// DS1302 RST/CE --> 5
// DS1302 VCC --> 3.3v 
// DS1302 GND --> GND


#include <ThreeWire.h>  
#include <RtcDS1302.h>

//ThreeWire myWire(4,5,2); // IO, SCLK, CE
ThreeWire myWire(3,2,5); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

class Rtc1{

  
public:
void setup () 
{
    Serial.begin(9600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
//        lcd.autoscroll();
//        lcd1.displayData("RTC lost confidence in the DateTime!", "", 3);
//        lcd.noAutoscroll();
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
//        lcd.autoscroll();
//        lcd1.displayData("RTC was write protected, enabling writing now", "", 3);
//        lcd.noAutoscroll();
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
//        lcd.autoscroll();
//        lcd1.displayData("RTC was not actively running, starting now", "", 3);
//        lcd.noAutoscroll();
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
//        lcd.autoscroll();
//        lcd1.displayData("RTC is older than compile time!  (Updating DateTime)", "", 3);
//        lcd.noAutoscroll();
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
//        lcd.autoscroll();
//        lcd1.displayData("RTC is newer than compile time. (this is expected)", "", 3);
//        lcd.noAutoscroll();
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
//        lcd.autoscroll();
//        lcd1.displayData("RTC is the same as compile time! (not expected but all is fine)", "", 3);
//        lcd.noAutoscroll();
    }
}

void loop () 
{
    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
//        lcd.autoscroll();
//        lcd1.displayData("RTC lost confidence in the DateTime!", "", 3);
//        lcd.noAutoscroll();
    }

//    delay(10000); // ten seconds
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Day(),
            dt.Month(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    lcd1.displayData("",datestring,2);        
    Serial.print(datestring);
}
};
