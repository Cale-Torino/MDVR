
for (int i = 0; i < 22; i++) {
    irsend.sendNEC(0x212F8C73, 32); // ZOOM OUT
    delay(80);
  }
  delay(1000);

  for (int i = 0; i < 22; i++) {
    irsend.sendNEC(0x212F847B, 32); // ZOOM in
    delay(80);
  } 



  //send repeat bursts
  unsigned int buf[3];
buf[0] = 9000;  // Mark 9ms
buf[1] = 2250;  // Space 2.25ms
buf[2] = 560;   // Burst
irsend.sendRaw(buf, 3, 38);




#include <IRremote.h>

IRsend irsend;
const int buttonPin = 2; // the number of the pushbutton pin
//const int ledPin = 3;
int buttonState = 0; // variable for reading the pushbutton status
void setup()
{
// pinMode(ledPin, OUTPUT);
// initialize the pushbutton pin as an input:
pinMode(buttonPin, INPUT);
Serial.begin(9600);
}

void loop() {

buttonState = digitalRead(buttonPin);

// check if the pushbutton is pressed.
// if it is, the buttonState is HIGH:
if (buttonState == HIGH) {
// turn LED on:
irsend.sendNEC(0x80BFA15E, 32);
}

}