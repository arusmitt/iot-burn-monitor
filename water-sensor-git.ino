#define BLYNK_TEMPLATE_ID "fill in from Blynk"
#define BLYNK_TEMPLATE_NAME "sink monitor"
#define BLYNK_AUTH_TOKEN "fill in from Blynk"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "fill in your wifi name";  // type your wifi name
char pass[] = "fill in your wifi pass";  // type your wifi password

BlynkTimer timer;

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);


void getTemp()
{
  sensors.requestTemperatures(); 
  float temperatureF = sensors.getTempFByIndex(0);

  if (isnan(temperatureF)) {
    Serial.print("Failed to read from sensor!");
    return;
  }

  if(temperatureF >= 120){
    Blynk.logEvent("highest-temp");
  }
  else if(temperatureF >= 110){
    Blynk.logEvent("higher-temp");
  }
  else if(temperatureF >= 103){
    Blynk.logEvent("high-temp");
  }
  
    Blynk.virtualWrite(V0, temperatureF);
    Serial.print("Temperature : ");
    Serial.println(temperatureF);
}
void setup()
{   
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  sensors.begin();
  timer.setInterval(1000L, getTemp);
  }

void loop()
{
  Blynk.run();
  timer.run();
 }
