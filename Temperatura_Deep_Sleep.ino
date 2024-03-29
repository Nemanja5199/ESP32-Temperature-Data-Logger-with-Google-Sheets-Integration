#include <WiFi.h>
#include "time.h"
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GS_SDHelper.h>



const int oneWireBus= 4;


OneWire oneWire(oneWireBus);


DallasTemperature sensors(&oneWire);


#define WIFI_SSID ""
#define WIFI_PASSWORD ""


#define uS_TO_S_FACTOR 1000000 
#define TIME_TO_SLEEP 60



// Google Project ID
#define PROJECT_ID ""

#define CLIENT_EMAIL ""


const char PRIVATE_KEY[] PROGMEM = "";

const char spreadsheetId[] = "";

// Token Callback function
void tokenStatusCallback(TokenInfo info);


/*// Timer variables
unsigned long lastTime = 0;  
unsigned long timerDelay = 5000;
*/

// NTP server to request epoch time
const char* ntpServer = "pool.ntp.org";

// Variable to save current epoch time
char* Time; 

// Function that gets current epoch time
char* getTime() {
    time_t now;
    struct tm timeinfo;

    // Adjust timezone to Belgrade
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();

    if (!getLocalTime(&timeinfo)) {
        // Serial.println("Failed to obtain time");
        return NULL;
    }

    time(&now);

    static char buffer[20]; // Sufficiently large buffer to hold the formatted time
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M", &timeinfo);

    return buffer;
}
float temp;


void setup() {
  

  Serial.begin(115200);


  Serial.println();
  Serial.println();
    //Configure time
    configTime(0, 0, ntpServer);

   sensors.begin();

  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print("."); delay(300);
  }

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


    // Set the callback for Google API access token generation status (for debug only)
    GSheet.setTokenCallback(tokenStatusCallback);

    // Set the seconds to refresh the auth token before expire (60 to 3540, default is 300 seconds)
    GSheet.setPrerefreshSeconds(10*60);

    // Begin the access token generation for Google API authentication
    GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);


DataPrintSerial();
SendData();



esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
esp_deep_sleep_start();

 
   


}

void loop(){

}
void DataPrintSerial(){
   float temperatureC = sensors.getTempCByIndex(0);
    String temp_C(temperatureC);
  Serial.print(temp_C);
  Serial.println("ºC");

  
}

void SendData(){

   float temperatureC = sensors.getTempCByIndex(0);
    String temp_C(temperatureC);

   bool ready = GSheet.ready();


       if (ready){
        

        FirebaseJson response;

        Serial.println("\nAppend spreadsheet values...");
        Serial.println("----------------------------");

        FirebaseJson valueRange;

        // New BME280 sensor readings
        temp = sensors.getTempCByIndex(0);
        String temp_S(temp);
        // Get timestamp
        Time = getTime();

        valueRange.add("majorDimension", "COLUMNS");
        valueRange.set("values/[0]/[0]", Time);
        valueRange.set("values/[1]/[0]", "              " + temp_C + "ºC" );

        // For Google Sheet API ref doc, go to https://developers.google.com/sheets/api/reference/rest/v4/spreadsheets.values/append
        // Append values to the spreadsheet
        bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
        if (success){
            response.toString(Serial, true);
            valueRange.clear();
        }
        else{
            Serial.println(GSheet.errorReason());
        }
        Serial.println();
        Serial.println(ESP.getFreeHeap());
    }





}

void tokenStatusCallback(TokenInfo info){
    if (info.status == token_status_error){
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
    }
    else{
        GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    }
}



 



