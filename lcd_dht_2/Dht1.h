#include <Wire.h> 
#include <DHT.h>


    //Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 22  (AM2302)

DHT dht(DHTPIN,DHTTYPE);


class Dht1{


  private:

  //Variables
  int chk;
  float hum;  //Stores humidity value
  float temp; //Stores temperature value
  float temp_adjustment;
  float hum_adjustment;

  public:

  Dht1(float _temp_adjustment, int _hum_adjustment){
     float tem_adjustment = _temp_adjustment;
     int hum_adjustment = _hum_adjustment;
   setup();
    };
    
  void setup(void){
       dht.begin();
    }

  void loop(void){
    lcd.home ();
        //Read data and store it to variables hum and temp
    hum = hum_adjustment + dht.readHumidity();
    temp= temp_adjustment + dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);

    lcd.home ();                   // go home
//    lcd.print("Humidity: ");
//    lcd.print(hum);
//    lcd.print(" %");
    char str[32];
    dtostrf(hum, 4, 2, str);
    strcat(str," %");
    lcd1.displayData("Humidity",str,0);

    
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");

    memset(str, 0, sizeof(str));
    dtostrf(temp, 4, 2, str);   
    strcat(str," Celsius");
    lcd1.displayData("Temp",str,1);
        

//    lcd.setCursor ( 0, 1 );        // go to the next line
//    lcd.print ("Temp: "); 
//    lcd.print (temp);
//    lcd.print (" Celsius");
    }

  };
