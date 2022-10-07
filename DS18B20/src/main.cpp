/*
 I, Sam Gershkovich, student number 000801766, certify that this material is my original work.
 No other person's work has been used without due acknowledgment and neither have I made my work available to anyone else.
*/

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = D3;

OneWire oneWire(oneWireBus);
DallasTemperature DS18B20(&oneWire);

bool run = true;

void setup()
{
  Serial.begin(115200);
  DS18B20.begin();

  DeviceAddress address;

  Serial.println("");
  Serial.println("Temperature Application");

  if (!DS18B20.getAddress(address, 0))  {
    Serial.println("No DS18B20 temperature sensors are installed!");
    run = false;
  }
  else {
    Serial.print("Found DS18B20 sensor with address: ");

    for (uint8_t i = 0; i < 8; i++)
    {
      Serial.print(address[i], HEX);
    }
    Serial.println("");
  }
}

void loop()
{
  if (run)
  {
    float fTemp;
    DS18B20.requestTemperatures();
    fTemp = DS18B20.getTempCByIndex(0);

    String temp = "";

    if (fTemp < 10)
      temp = "Cold!";
    else if (fTemp >= 10 && fTemp < 15)
      temp = "Cool";
    else if (fTemp >= 15 && fTemp < 25)
      temp = "Perfect";
    else if (fTemp >= 25 && fTemp < 30)
      temp = "Warm";
    else if (fTemp >= 30 && fTemp < 35)
      temp = "Hot";
    else
      temp = "Too Hot!";

    Serial.println("Current temperature is: " + String(fTemp) + "° or " + temp);

    delay(5000);
  }
}