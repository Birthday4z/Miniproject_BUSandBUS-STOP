//Bus75 Square 
#include <SPI.h>
#include <LoRa.h>

#define NSS_PIN    10
#define NRESET_PIN 2
#define DIO0_PIN   4

int Menu;
int direct = 0;//direction
int x=0; //count

String linedirect1 = "75IN";// 1 mean Go IN 2 mean GO OUT
String linedirect2 = "75OUT";// 1 mean Go IN 2 mean GO OUT

// constants won't change. They're used here to set pin numbers:
const int buttonPin1 = 2;     // the number of the pushbutton pin "75IN"
const int buttonPin2 = 8;     // the number of the pushbutton pin "75OUT"
const int buttonPin3 = 9;     // the number of the pushbutton pin "reset"

#define LEDGreen          A1 // the number of the LEDGreen pin link with Button1
#define LEDBlue           A0 // the number of the LEDBlue pin link with Button2

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status "75IN"
int buttonState2 = 0;         // variable for reading the pushbutton status "75OUT"
int buttonState3 = 0;         // variable for reading the pushbutton status "reset"
int packetSize;

void setup() {
  // initialize the LED pin as an output:
//  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
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
  pinMode(LEDGreen, OUTPUT);
  pinMode(LEDBlue, OUTPUT);
  }

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
/////////////////////////////////////////////////////////////////
  //----------Recieve LoRa-----------------------------
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    // received a packet
    Serial.println();
    Serial.println("Received packet ");
    String Receivesignal = LoRa.readString();
    // read packet
    // ลบได้ ซ้ำกับข้างบนString Receivesignal = LoRa.readString();
      if (Receivesignal == "75_IN" && direct == 1){
        Menu = 1;
      }
      else if (Receivesignal == "75_OUT" && direct == 2){
        Menu = 2;
      }
    while (LoRa.available()) {
      //Serial.print((String)LoRa.readString());
    }
      Serial.print(" with RSSI ");
      Serial.print(LoRa.packetRssi());
      Serial.println();
      delay(10);
      }
/////////////////////////////////////////////////////////////////
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    direct = 1;
    Serial.println(direct);//แก้ตรงนี้ด้วย ใส่ไฟ
    analogWrite(LEDBlue, 150);
    analogWrite(LEDGreen, 0);
    }
  if (buttonState2 == HIGH) {
    direct = 2;
    Serial.println(direct);//แก้ตรงนี้ด้วย ใส่ไฟ
    analogWrite(LEDBlue, 0);
    analogWrite(LEDGreen, 150);
  }
  if (buttonState3 == HIGH) {
    Menu = 3;
    direct = 3;
    Serial.println(direct);//แก้ตรงนี้ด้วย ใส่ไฟ
    analogWrite(LEDBlue, 0);
    analogWrite(LEDGreen, 0);
    
  }
  if (Menu == 1){
    x=0;
    analogWrite(LEDBlue, 150);
    delay(500);
    analogWrite(LEDBlue, 0);
    LoRa.beginPacket();
    LoRa.print(linedirect1);
    LoRa.endPacket();
    Serial.print("Send '");
    Serial.print(linedirect1);
    Serial.print("'");
    Serial.println();
    delay(2000);
  }
  else if (Menu == 2){
    x=0;
    analogWrite(LEDGreen, 150);
    delay(500);
    analogWrite(LEDGreen, 0);
    LoRa.beginPacket();
    LoRa.print(linedirect2);
    LoRa.endPacket();
    Serial.print("Send '");
    Serial.print(linedirect2);
    Serial.print("'");
    Serial.println();
    delay(2000);
  }
  else if (Menu == 3 && x == 1){
    LoRa.endPacket();
    x++;
  }
delay(100);
}
