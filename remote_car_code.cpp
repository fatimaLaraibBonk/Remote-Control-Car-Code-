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

//toggle:
//lights, beam, autopilot
//buttons:
//left, right, forward, backward, horn
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
const int trigPinLeft=19;
const int echoPinLeft=18;
const int trigPinRight=23;
const int echoPinRight=22;
const int trigPinFront=2;
const int echoPinFront=15;
const int trigPinBack=21;
const int echoPinBack=34;
int hornStart=0;
//booleans
//for toggle modes-> basically keep these states until stated otherwise 
bool frontLightsState=false;
bool backLightsState=false;
bool beamState=false;
bool autoPilotState=false;
bool hornActive=false;
bool manualState=true;
//other measurements
long durationFront, durationBack, durationLeft, durationRight;
float distanceFront, distanceBack, distanceLeft, distanceRight;
//webserve code
WebServer server(80);
void handleRoot(){
    //html code
    //
    server.send(200, "text/html",html);
}

//AUTO PILOT CODE 
void forward(){
    digitalWrite(wheel1, HIGH);
    digitalWrite(wheel2, LOW);
    digitalWrite(wheel3, HIGH);
    digitalWrite(wheel4, LOW);
    Serial.println("Moving Forward!!");
}
void backward(){
    digitalWrite(wheel1, LOW);
    digitalWrite(wheel2, HIGH);
    digitalWrite(wheel3, LOW);
    digitalWrite(wheel4, HIGH);
    Serial.println("Moving Backwards!");
}
void left(){
    digitalWrite(wheel1, LOW); 
    digitalWrite(wheel2, LOW); 
    digitalWrite(wheel3, HIGH); 
    digitalWrite(wheel4, HIGH); 
    Serial.println("Turning Left!!");
}
void right(){
    digitalWrite(wheel1, HIGH);
    digitalWrite(wheel2, HIGH); 
    digitalWrite(wheel3, LOW); 
    digitalWrite(wheel4, LOW); 
    Serial.println("Turning Right!!");
}
void stop(){
    digitalWrite(wheel1, LOW);
    digitalWrite(wheel2, LOW);
    digitalWrite(wheel3, LOW);
    digitalWrite(wheel4, LOW);
    Serial.println("RC Car stopped!");
}
//AUTO PILOT CODE ENDED
//MANUAL MOVEMENT CODE 
void handleForward(){
    if(manualState==false) return;
    //left-> 1,2
    //right-> 3,4
    digitalWrite(wheel1, HIGH);
    digitalWrite(wheel2, LOW);
    digitalWrite(wheel3, HIGH);
    digitalWrite(wheel4, LOW);
    Serial.println("Moving Forward!!");
}
void handleBackward(){
    if(manualState==false) return;
    digitalWrite(wheel1, LOW);
    digitalWrite(wheel2, HIGH);
    digitalWrite(wheel3, LOW);
    digitalWrite(wheel4, HIGH);
    Serial.println("Moving Backwards!");
}
void handleLeft(){
    if(manualState==false) return;
    digitalWrite(wheel1, LOW); 
    digitalWrite(wheel2, LOW); 
    digitalWrite(wheel3, HIGH); 
    digitalWrite(wheel4, HIGH); 
    Serial.println("Turning Left!!");
}
void handleRight(){
    if(manualState==false) return;
    digitalWrite(wheel1, HIGH);
    digitalWrite(wheel2, HIGH); 
    digitalWrite(wheel3, LOW); 
    digitalWrite(wheel4, LOW); 
    Serial.println("Turning Right!!");
}
void handleFrontLights(){
    if(manualState==false) return;
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
    if(manualState==false) return;
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
void handleStop(){
    if(manualState==false) return;
    digitalWrite(wheel1, LOW);
    digitalWrite(wheel2, LOW);
    digitalWrite(wheel3, LOW);
    digitalWrite(wheel4, LOW);
    Serial.println("RC Car stopped!");
}
void handleBeam(){
    if(manualState==false) return;
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
    if(manualState==false) return;
    //buzzes for like 2seconds
    if(!hornActive){
        hornActive = true;
        hornStart = millis();
        digitalWrite(horn, HIGH);
    }
}
//MANUAL CODE ENDED

void autoPilotMode() {
    //autopilot is on toggle mode
    //measuring alll distances 
    //FRONT
    digitalWrite(trigPinFront, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinFront, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinFront, LOW);
    durationFront=pulseIn(echoPinFront, HIGH);
    distanceFront=durationFront * 0.034 / 2;

    //BACK
    digitalWrite(trigPinBack, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinBack, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinBack, LOW);
    durationBack=pulseIn(echoPinBack, HIGH);
    distanceBack=durationBack * 0.034 / 2;

    //LEFT
    digitalWrite(trigPinLeft, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinLeft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinLeft, LOW);
    durationLeft=pulseIn(echoPinLeft, HIGH);
    distanceLeft=durationLeft * 0.034 / 2;

    //RIGHT
    digitalWrite(trigPinRight, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinRight, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinRight, LOW);
    durationRight=pulseIn(echoPinRight, HIGH);
    distanceRight=durationRight * 0.034 / 2;

   
    Serial.print("Front: ");
    Serial.print(distanceFront); 
    Serial.print(" cm, ");
    Serial.print("Back: "); 
    Serial.print(distanceBack); 
    Serial.print(" cm, ");
    Serial.print("Left: "); 
    Serial.print(distanceLeft); 
    Serial.print(" cm, ");
    Serial.print("Right: "); 
    Serial.println(distanceRight);
    Serial.print(" cm");

    //decisions:

    //if forward distance is high keep moving forward
    if(distanceFront>50){
        //move forward
        forward();
    }
    else if(distanceLeft>distanceRight){
        left();
    }
    else if(distanceRight>distanceLeft){
        right();
    }
    else if(distanceBack>50){
        backward();
    }
    else{
        stop();
    }
    //if not then check left or right
    //else move
    delay(100); 
}

void handleAutopilot(){
    if(autoPilotState==false){
        //turn on autopliot
        autoPilotState=true;
        manualState=false;
        autoPilotMode();
    }
    else{
        //back to manual
        autoPilotState=false;
        manualState=true;
    }
}

//SETUP CODE 
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
    pinMode(trigPinLeft, OUTPUT);
    pinMode(echoPinLeft, INPUT);
    pinMode(trigPinRight, OUTPUT);
    pinMode(echoPinRight, INPUT);
    pinMode(trigPinFront, OUTPUT);
    pinMode(echoPinFront, INPUT);
    pinMode(trigPinBack, OUTPUT);
    pinMode(echoPinBack, INPUT);

    //handling different routes
    server.on("/", handleRoot);
    server.on("/move/forward", handleForward);
    server.on("/move/backward", handleBackward);
    server.on("/move/stop", handleStop);
    server.on("/move/left", handleLeft);
    server.on("/move/right", handleRight);
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
    if(autoPilotState) {
        autoPilotMode(); 
    }
}