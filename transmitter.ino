int button = 11;
int result;
#include <VirtualWire.h>

void setup()
 {
 // Initialize the IO and ISR
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(13, OUTPUT);
  vw_setup(2000); // Bits per sec
 }

void loop()
 {
  result = digitalRead(button);
  if (result==1) {
  send("on");
  Serial.println("on");
  digitalWrite(13, HIGH);
  }
  else {
   send("off");
   Serial.println("off");
   digitalWrite(13, LOW);
  }
  delay(50);
 }

 void send (char *message)
 {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
 }
