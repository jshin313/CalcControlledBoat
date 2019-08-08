/*************************************************
 *    Receives data from the transmitter         *
 *************************************************/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); 

const byte rxAddr[6] = "00001"; // Sets up the address for the receiver


//Define Pins
//Motor A
int enableA = 2;
int MotorA1 = 3;
int MotorA2 = 4;
 
//Motor B
int enableB = 5;
int MotorB1 = 6;
int MotorB2 = 7;

void setup() {
  //configure pin modes
  pinMode (enableA, OUTPUT);
  pinMode (MotorA1, OUTPUT);
  pinMode (MotorA2, OUTPUT);  
  
  pinMode (enableB, OUTPUT);
  pinMode (MotorB1, OUTPUT);
  pinMode (MotorB2, OUTPUT);

  // Sets up the radio for receiving
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
  
  
}

void loop() {
  
  if (radio.available())
  {
    enable_motors();
    int data[1] = {0};
    radio.read(&data, sizeof(data)); // Reads incoming data

    // Controls the boat's directions
    if (data[0] == 1)
    {
      
      move_forward();
    }
    if(data[0] == 2)
    {
      turn_left();
    }

    if(data[0] == 3)
    {
      turn_right();
    }
    if(data[0] == 4)
    {
      stop_motors();
    }
      
  }
  
}

void move_forward()
{
  digitalWrite (MotorA1,LOW);
  digitalWrite (MotorA2,HIGH); 
   
  digitalWrite (MotorB1,LOW);
  digitalWrite (MotorB2,HIGH);  
}

void turn_left()
{
  
  digitalWrite(MotorA1, LOW); 
  digitalWrite(MotorA2, HIGH); 

  digitalWrite(MotorB1, HIGH); 
  digitalWrite(MotorB2, LOW);
}

void turn_right()
{
  digitalWrite(MotorA1, HIGH);
  digitalWrite(MotorA2, LOW); 

  digitalWrite(MotorB1, LOW); 
  digitalWrite(MotorB2, HIGH); 
}

void stop_motors()
{
  digitalWrite(enableA, LOW); 
  digitalWrite(enableB, LOW); 
  delay(25);
}

void enable_motors()
{
  //enabling motors
  digitalWrite(enableA, HIGH); 
  digitalWrite(enableB, HIGH); 
}



