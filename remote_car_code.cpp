#include <WiFi.h>
#include <WebServer.h>

//wifi details
const char* ssid="";
const char* password="";

//pin configuration
//wheels
//healights
//horn
//high beam
//back light 
//autopilot

const int frontLight1=26;
const int frontLight2=27;
const int backLight1=14;
const int backLight2=12;
const int horn=33;
const int highBeam=25;
const int enable1=32;
const int enable2=13;
const int wheel1=4;
const int wheel2=16;
const int wheel3=17;
const int wheel4=5;
const int trigPin=19;
const int echoPin=18;
int hornStart=0;
//booleans
bool frontLightsState=false;
bool backLightsState=false;
bool beamState=false;
bool autoPilotState=false;
bool hornActive=false;
//webserve code
WebServer server(80);
void handleRoot(){
    //html code
    //
    server.send(200, "text/html",html);
}
void handleForward(){
    //left-> 1,2
    //right-> 3,4
    digitalWrite(wheel1, HIGH);
    digitalWrite(wheel2, LOW);
    digitalWrite(wheel3, HIGH);
    digitalWrite(wheel4, LOW);
    Serial.println("Moving Forward!!");
}
void handleBackward(){
    digitalWrite(wheel1, LOW);
    digitalWrite(wheel2, HIGH);
    digitalWrite(wheel3, LOW);
    digitalWrite(wheel4, HIGH);
    Serial.println("Moving Backwards!");
}
void handleFrontLights(){
    if(frontLightsState==false){
        frontLightsState=true;
        frontLightsOn();
    }
    else{
        frontLightsState=false;
        frontLightsOff();
    }
}
void frontLightsOn(){
    digitalWrite(frontLight1,HIGH);
    digitalWrite(frontLight2, HIGH);
    Serial.println("Front Lights ON!");
}
void frontLightsOff(){
    digitalWrite(frontLight1,LOW);
    digitalWrite(frontLight2, LOW);
    Serial.println("Front Lights OFF!");
}
void handleBackLights(){
    if(backLightsState==false){
        backLightsState=true;
        backLightsOn();
    }
    else{
        backLightsState=false;
        backLightsOff();
    }
}
void backLightsOn(){
    digitalWrite(backLight1,HIGH);
    digitalWrite(backLight2, HIGH);
    Serial.println("Back Lights ON!");
}
void backLightsOff(){
    digitalWrite(backLight1,LOW);
    digitalWrite(backLight2, LOW);
    Serial.println("Back Lights OFF!");
}
void handleBeam(){
    if(beamState==false){
        beamState=true;
        highBeamOn();
    }
    else{
        beamState=false;
        highBeamOff();
    }
}
void highBeamOn(){
    digitalWrite(highBeam, HIGH);
    Serial.println("High Beam ON!");
}
void highBeamOFF(){
    digitalWrite(highBeam, LOW);
    Serial.println("High Beam OFF");
}
void handleHorn(){
    //buzzes for like 2seconds
    if(!hornActive){
        hornActive = true;
        hornStart = millis();
        digitalWrite(horn, HIGH);
    }
}
void handleAutopilot(){

}
void setup(){
    Serial.begin(9600);
    Serial.println("Beginning setup..");
    Serial.println("Connecting..");
    //wifi connection
    WiFi.begin(ssid, password);
    while(WiFi.status()!=WL_CONNECTED){
        delay(100);
        Serial.println(".");
    }
    Serial.println("Connected!");
    Serial.println("IP Address: ");
    Serial.println(WiFi.localIP());
    //pinModes
    pinMode(frontLight1, OUTPUT);
    pinMode(frontLight2, OUTPUT);
    pinMode(backLight1, OUTPUT);
    pinMode(backLight2, OUTPUT);
    pinMode(horn, OUTPUT);
    pinMode(highBeam, OUTPUT);
    pinMode(enable1, OUTPUT);
    pinMode(enable2, OUTPUT);
    pinMode(wheel1,OUTPUT);
    pinMode(wheel2, OUTPUT);
    pinMode(wheel3, OUTPUT);
    pinMode(wheel4, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    //handling different routes
    server.on("/", handleRoot);
    server.on("/move/forward", handleForward);
    server.on("/move/backward", handleBackward);
    server.on("/lights/front", handleFrontLights);
    server.on("/lights/back", handleBackLights);
    server.on("/lights/highbeam", handleBeam);
    server.on("/horn", handleHorn); 
    server.on("/autopilot", handleAutopilot);
    server.begin();
    Serial.println("Local host started!");

}
void loop(){
    server.handleClient();
    if(hornActive && millis()-hornStart>=2000){
        digitalWrite(horn, LOW);
        hornActive=false;
    }
}