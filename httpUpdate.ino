#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include<HTTPUpdate.h>

#ifndef APSSID
#define APSSID "Alcodex"
#define APPSK  "Adx@2013"
#endif
WiFiMulti WiFiMulti;
#define FIRMWARE_VERSION "0.2"
void setup()
{
Serial.begin(115200);
// Serial.setDebugOutput(true);
Serial.println();
Serial.println();
Serial.println();

 for(uint8_t t =4; t >0; t--)
{
Serial.printf("[SETUP] WAIT %d...\n", t);
Serial.flush();
delay(1000);
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(APSSID, APPSK);
  Serial.print(F("Firmware version "));
 Serial.println(FIRMWARE_VERSION);
delay(2000);
}
void loop()
{

  // wait for WiFi connection
  if((WiFiMulti.run()== WL_CONNECTED))
  {
    WiFiClient client;

    httpUpdate.rebootOnUpdate(false);
  // remove automatic update

    Serial.println(F("Update start now!"));

    // t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://192.168.1.125:3000/firmware/httpUpdateNew.bin");
    // Or:

    t_httpUpdate_return ret = httpUpdate.update(client,"68.183.86.143",2001,"/ota/getdata/");

  switch (ret)
      {

    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILD   Error (%d): %s\n", httpUpdate.getLastError(),httpUpdate.getLastErrorString().c_str());
      Serial.println(F("Retry in 10secs!"));
       delay(10000);
     // Wait 10secs
        break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;

    case HTTP_UPDATE_OK:
        Serial.println("HTTP_UPDATE_OK");
        delay(1000);
        // Wait a second and restart
        ESP.restart();
        break;

  }

}

}
