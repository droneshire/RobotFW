#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include "Robot.h"

/*
 - CONNECTIONS: nRF24L01 Modules See:
 HTTP://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 9
   4 - CSN to Arduino pin 10
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED
*/

// ALL FORWARD* AND BACKWARD* PINS MUST BE PWM PINS!!!
#define BACK1       2
#define FORWARD1    3  
#define ENABLE1     4

#define BACK2       5
#define FORWARD2    6
#define ENABLE2     7

#define CE_PIN      9
#define CSN_PIN     10

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

move_cmd_t cmds;

Robot robot;
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

void setup() {
  Serial.begin(9600);
  robot.Init(FORWARD1, BACK1, ENABLE1, FORWARD2, BACK2, ENABLE2);
  delay(1000);
  Serial.println("Nrf24L01 Receiver STARTING");
  radio.begin();
  radio.setRetries(15,15);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  radio.printDetails();  
  robot.Stop();
}

void loop() {
  delay(500);
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( &cmds, sizeof(move_cmd_t) );
      robot.Move(&cmds);
      Serial.print("| ACTION1 = ");
      Serial.print(cmds.action1);
      Serial.print(", SPEED MOTOR 1 = ");      
      Serial.print(cmds.speed1);
      Serial.print(", ACTION2 = ");      
      Serial.println(cmds.action2);
      Serial.print(", SPEED MOTOR 2 = ");      
      Serial.print(cmds.speed2);
      Serial.println(" |");
    }
  }
  else
  {    
      Serial.println("No radio AVAILABLE");
  }

}
