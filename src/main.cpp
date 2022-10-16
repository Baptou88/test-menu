#include <Arduino.h>
#include <WiFi.h>
#include<ArduinoOTA.h>


#include <heltec.h>
#include <digitalInput.h>
#include <menu.h>

menu *m;
menuItemList* ml;

digitalInput pin1(36,INPUT_PULLUP);
digitalInput pin2(38,INPUT_PULLUP);
digitalInput pinSelect(39,INPUT_PULLUP);
digitalInput pinPRG(0,INPUT_PULLUP);

const char* ssid = "Livebox-44C1";
const char* password = "20AAF66FCE1928F64292F3E28E";

int state = 0;

bool activate = false;
unsigned long prevmillis = 0;
void setup() {
  // put your setup code here, to run once:
  Heltec.begin(true,true,true,true,868E6);

  Heltec.display->clear();
  WiFi.disconnect(true);
	delay(100);
	WiFi.mode(WIFI_STA);
	WiFi.setAutoConnect(true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(1000);
  }

  Heltec.display->drawString(5,10,"Wiki Ok !");
  Heltec.display->drawString(5,20,(String)WiFi.localIP().toString());
  Heltec.display->display();
    delay(1000);
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
      Heltec.display->clear();
      Heltec.display->drawString(0,0,(String)type);
      Heltec.display->display();
      delay(500);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
      Heltec.display->clear();
      Heltec.display->drawString(0,0,(String)"End");
      Heltec.display->display();
      delay(1000);
      ESP.restart();
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      Heltec.display->clear();
      Heltec.display->drawProgressBar(0,20,120,20,(progress / (total/100 )));
      Heltec.display->display();
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
  Serial.println("poi");
  ml = new menuItemList(5);
  ml->addItem(new menuItembool(47,&activate));
  ml->addItem(new menuItemnew(1));
  ml->addItem(new menuItemnew(1));
  ml->addItem(new menuItemnew(2));
  ml->addItem(new menuItemnew(3));
  ml->addItem(new menuItemnew(3));

  m = new menu();
  m->actual = ml;
  
  //m.get(0)->draw();
  //m.get(1)->draw();
}

void loop() {
  
  pin1.loop();
  pin2.loop();
  pinSelect.loop();
  pinPRG.loop();

  static unsigned long lastprgmillis = 0;
  if (pinPRG.pressedTime()>2000 && millis() > lastprgmillis +1000)
  {
    lastprgmillis = millis();
    if (state == 0)
    {
      state =1;
    }else{
      state=0;
    }
    
    
  }
  
  
  
  
  
  Heltec.display->clear();


   
  switch (state)
  {
  case 0:
    Heltec.display->drawString(0,0,"idle");
    Heltec.display->drawString(20,20,"36");
    Heltec.display->drawString(100,20,"37");
    Heltec.display->drawString(20,32,(String)pin1.getState());
    Heltec.display->drawString(100,32,(String)pin2.getState());
    break;
  case 1:

    if (millis()> prevmillis +50)
    {
      prevmillis = millis();
      if (pin1.getState()==HIGH && pin2.getState()==LOW )
      {
        m->next();
      }
      if (pin1.getState()==LOW && pin2.getState()==HIGH )
      {
        m->prev();
      }
    }
    if (pinSelect.frontDesceandant())
    {
      m->select();
    }
    
    
    

    m->loop();
    break;
  default:
    break;
  }
 
 
  
  
   Heltec.display->display();

  ArduinoOTA.handle();
  delay(20);
}