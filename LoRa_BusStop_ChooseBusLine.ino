//Bus Stop Jaturat
#include <SPI.h>
#include <LoRa.h>

#define NSS_PIN     10
#define NRESET_PIN  2
#define DIO0_PIN    4

String busline21 = "21_IN";
String busline75 = "75_IN";
String busline88 = "88_IN";

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 2;     // the number of the pushbutton pin
const int buttonPin2 = 3;     // the number of the pushbutton pin
const int buttonPin3 = 8;     // the number of the pushbutton pin
const int buzzer = 9;         // buzzer pin

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
int packetSize;

void Beep(){
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
}
void longBeep(){
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
}

void BeepBeep(){
  Beep();
  delay(100);
  longBeep();
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Node - Receiver");
  Serial.println("LoRa Node - Sender");
  LoRa.setPins(NSS_PIN, NRESET_PIN, DIO0_PIN);
  if (!LoRa.begin(915E6)) 
  {
   Serial.println("Starting LoRa failed!");
    while(1);
  }
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buzzer, OUTPUT);
  }

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  
  //Recieve LoRa
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    // received a packet
    Serial.println();
    Serial.print("Received packet '");
    // read packet
    
    while (LoRa.available()) {
      Serial.print((String)LoRa.readString());
      if(LoRa.packetRssi() >=-70){
        BeepBeep();
        Beep();
      }
      else if(LoRa.packetRssi() >= -120 && LoRa.packetRssi() <= -71){
        Beep();
      }
      String Receivsig = LoRa.readString();
      if (Receivsig == "21IN"){
        longBeep();
      }
      else if (Receivsig == "75IN"){
        longBeep();
      }
      else if (Receivsig == "88IN"){
        longBeep();
      }
        
    }
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());
  }
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    LoRa.beginPacket();
    LoRa.print(busline21);
    LoRa.endPacket();
    Serial.print("Send '");
    Serial.print(busline21);
    Serial.print("'");
    Serial.println();
    //longBeep();
    delay(500);
  }
  if (buttonState2 == HIGH) {
    LoRa.beginPacket();
    LoRa.print(busline75);
    LoRa.endPacket();
    Serial.print("Send '");
    Serial.print(busline75);
    Serial.print("'");
    Serial.println();
    //longBeep();
    delay(500);
  }
  if (buttonState3 == HIGH) {
    LoRa.beginPacket();
    LoRa.print(busline88);
    LoRa.endPacket();
    Serial.print("Send '");
    Serial.print(busline88);
    Serial.print("'");
    Serial.println();
    //longBeep();
    delay(500);
  }

delay(10);
}
