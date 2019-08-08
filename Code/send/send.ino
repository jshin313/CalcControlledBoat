/*************************************************
 *     Sends data to the reciever on the boat    *
 *************************************************/

#include "CBL2.h"
#include "TIVar.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte rxAddr[6] = "00001"; // Sets the address of the transmitter



CBL2 cbl;

// Toggle these as necessary
const int lineRed = 6;
const int lineWhite = 7;

// Lists are 2 + (9 * dimension) bytes,
// so incidentally a 255-byte max data length
// limits this demo's lists to 28 elements.
#define MAXDATALEN 255

uint8_t header[16];
uint8_t data[MAXDATALEN];

// Forward function definitions.
int onGetAsCBL2(uint8_t type, enum Endpoint model, int datalen);
int onSendAsCBL2(uint8_t type, enum Endpoint model, int* headerlen,
                 int* datalen, data_callback* data_callback);

// Run once when the Arduino resets. This first 
// initializes a new CBL2 instance. This is responsible for dealing with the
// actual calculator<->Arduino message exchange.
void setup() {

  // Sets up the nrf24l01 to send data
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
  
  Serial.begin(9600);                           // Used for debugging
  cbl.setLines(lineRed, lineWhite);
  cbl.resetLines();
  // cbl.setVerbosity(true, &Serial);			// Comment this in for verbose message information
  
  // The following registers buffers for exchanging data, the maximum
  // allowed data length, and functions to call on Get() and Send().
  cbl.setupCallbacks(header, data, MAXDATALEN,
                      onGetAsCBL2, onSendAsCBL2);
}

// Repeatedly check to see if the calculator has initiated a Get()
// or a Send() operation yet. If it has, then onGetAsCBL2() or
// onSendAsCBL2() will be invoked, since they were registered in
// setup() above.
void loop() {
  //Serial.println("Test");
  int rval;
  rval = cbl.eventLoopTick();
  if (rval && rval != ERR_READ_TIMEOUT) {
    Serial.print("Failed to run eventLoopTick: code ");
    Serial.println(rval);
  }
}

// Callback when the CBL2 class has successfully received a variable
// from the attached calculator.
int onGetAsCBL2(uint8_t type, enum Endpoint model, int datalen) {
  Serial.print("Got variable of type ");
  Serial.print(type);
  Serial.print(" from endpoint of type ");
  Serial.println((int)model);
  


  // Turn the motor on or off
  uint16_t list_len = TIVar::sizeWordToInt(&(data[0]));		// Convert 2-byte size word to int
  if (list_len == 1) {
    // It is indeed a 1-element list
	  int value = TIVar::realToLong8x(&data[2], model);	// First list element starts after 2-byte size word
    Serial.print("Received value ");
    Serial.println(value);
    const int data[1] = {value};
    radio.write(&data, sizeof(data));
    Serial.println(data[0]);
    delay(1000);
    
  } 
  else {
    Serial.println("Must send a 1-element list!");
  }
  return 0;
}

// Callback when the CBL2 class notices the attached calculator
// wants to start a Get() exchange. The CBL2 class needs to get
// any data to send before continuing the exchange.
int onSendAsCBL2(uint8_t type, enum Endpoint model, int* headerlen,
                 int* datalen, data_callback* data_callback)
{
  Serial.print("Got request for variable of type ");
  Serial.print(type);
  Serial.print(" from endpoint of type ");
  Serial.println((int)model);
  return -1;		// -1 means we have no data to send.
}


