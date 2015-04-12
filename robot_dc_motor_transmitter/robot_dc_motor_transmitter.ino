#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include "Robot.h"
/* 
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
   - 
   Analog Joystick or two 10K potentiometers:
   GND to Arduino GND
   VCC to Arduino +5V
   X Pot to Arduino A0
   Y Pot to Arduino A1
*/   

#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X A0
#define JOYSTICK_Y A1

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
move_cmd_t packet;
int joystick[2];  // 2 element array holding Joystick readings

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop()
{
	joystick[0] = analogRead(JOYSTICK_X);
	joystick[1] = analogRead(JOYSTICK_Y);
	
	Robot::Packet(&packet, convert_data(joystick[0]), convert_data(joystick[1]));
	
	radio.write( &packet, sizeof(packet));
	delay(100);
}

int convert_data(int data) {
	data -= 512;	// center joystick
	if(data > 0)
		return map(data, 0, 512, 0, 255);
	else
		return map(data, -512, 0, -255, 0);
}
