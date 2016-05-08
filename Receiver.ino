// Watch video here: https://www.youtube.com/watch?v=8VoDT6ae768

//Connect the Receiver data pin to Arduino pin 11
#include <Wire.h>
#include <LiquidCrystal.h>
#include <VirtualWire.h>
int led = 13;
const int  buttonPin = 8; 
// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;// previous state of the button
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);


byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void setup() {
   pinMode(buttonPin, INPUT);
 Serial.begin(9600);
 lcd.begin(16, 2);
  Wire.begin();
 Serial.println("Device is ready");
 pinMode(led, OUTPUT);
// Initialize the IO and ISR
 vw_setup(2000); // Bits per sec
 vw_rx_start(); // Start the receiver
}

void loop() {
 
   buttonState = digitalRead(buttonPin);
  
  if (vw_get_message(message, &messageLength)) {  // Non-blocking
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++) {
     Serial.write(message[i]);
    }
   if((message[0]==111) && (message[1]==110) ) { // this is "on": "o" corresponds to 111, "n" corresponds to 110
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
     }
     lastButtonState = buttonState;
     if (buttonPushCounter % 1 == 0 && buttonPushCounter % 2 != 0&&buttonPushCounter % 3 != 0)
     
    digitalWrite(13, HIGH);
    delay(5000); 
     lcd.setCursor(0,0);
    lcd.print("turn off light  ");
     lcd.setCursor(0,1);
    lcd.print("after 5s  ");
    digitalWrite(13, LOW);
    delay(10000000);
    
   }
   if (buttonPushCounter % 1 != 0 && buttonPushCounter % 2 == 0&&buttonPushCounter % 3 != 0)
   {
    digitalWrite(13, HIGH);
    delay(10000); 
     lcd.setCursor(0,0);
    lcd.print("turn off light  ");
     lcd.setCursor(0,1);
    lcd.print("after 10s  ");
    digitalWrite(13, LOW);
    delay(10000000);
   }
    if (buttonPushCounter % 1 != 0 && buttonPushCounter % 2 != 0&&buttonPushCounter % 3 == 0)
    {
    digitalWrite(13, HIGH);
    delay(15000); 
     lcd.setCursor(0,0);
    lcd.print("turn off light  ");
     lcd.setCursor(0,1);
    lcd.print("after 15s  ");
    digitalWrite(13, LOW);
    delay(10000000);
  }
   }
   else {
    digitalWrite(13, HIGH);  
   }
   Serial.println();
  }
  delay(50);

}
