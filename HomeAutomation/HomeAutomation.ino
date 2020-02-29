//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "HOME_IOT.h" //Include the HOME_IOT Header File
//1. Include Firebase ESP8266 library (this library)
//https://github.com/mobizt/Firebase-ESP8266
#include "FirebaseESP8266.h"

//2. Include ESP8266WiFi.h and must be included after FirebaseESP8266.h
#include <ESP8266WiFi.h>

//3. Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

//Copy and Paste your IOT_TOKEN below
String IOT_TOKEN = "UrxsqoMRrOQXXivJaoFkMJfbWYT2";
//Paste or write you project Name (case sensitive)
String PROJECT_NAME = "myroom";
String path = "/projects/"+IOT_TOKEN+"/Home Automation 4 Switch/"+PROJECT_NAME+"/";


////////////Decalare Sensors PINS/////////////////
int relay1 = D0;
int relay2 = D1;
int relay3 = D2;
int relay4 = D5;
int counter = 0;

void setup() {
  // put your setup code here, to run once:
// put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
 

  WiFiManager wifiManager;
  wifiManager.autoConnect("IOT-HACK");
  Serial.println("connected...yeey :)");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  ///Check For the Relay 1
  if (Firebase.getInt(firebaseData, path+"relay1")) {

    if (firebaseData.dataType() == "int") {
      digitalWrite(relay1,firebaseData.intData());
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  ///Check For the Relay 2
  if (Firebase.getInt(firebaseData, path+"relay2")) {

    if (firebaseData.dataType() == "int") {
      digitalWrite(relay2,firebaseData.intData());
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  ///Check For the Relay 3
  if (Firebase.getInt(firebaseData, path+"relay3")) {

    if (firebaseData.dataType() == "int") {
      digitalWrite(relay3,firebaseData.intData());
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  ///Check For the Relay 4
  if (Firebase.getInt(firebaseData, path+"relay4")) {

    if (firebaseData.dataType() == "int") {
      digitalWrite(relay4,firebaseData.intData());
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  ////////////Run The Counter/////////////////////////
  if (Firebase.getInt(firebaseData, path+"runcounter")) {

    if (firebaseData.dataType() == "int") {
      counter = firebaseData.intData();
      if(counter == 1) counter = 0;else counter = 1;
      if(Firebase.setInt(firebaseData,path+"runcounter",counter)){}
      else{Serial.println(firebaseData.errorReason());} 
       }
      
     } else {
    Serial.println(firebaseData.errorReason());
  }
  delay(100);

}
