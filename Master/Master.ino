#include <RH_ASK.h>           // Include the RH_ASK library
#include <SPI.h>              // Not actually used but needed to compile the RH_ASK library
#include <stdlib.h>

RH_ASK radio(4000, 11, 12);

const char *msg[2] = {"1","2"};
char value[3];

void setup()
{
  Serial.begin(115200);       // Use this for debugging
  DDRD |= 0b00100000;         // pinMode(5,OUTPUT);
  if (!radio.init()) {
    Serial.println("Radio module failed to initialize");
  }
} 

void loop()
{  
  for(uint8_t i = 0; i < 2; i++)
  {
  int retval = 0 ; 
  uint8_t receive_buffer[3];
  uint8_t buflen = sizeof(receive_buffer);

    Serial.print(msg[i]);
    Serial.print("=");
    PORTD &= 0b11011111;        //digitalWrite(5,LOW);    // OFF Rx
    radio.send((char*)msg[i], strlen(msg[i]));
    radio.waitPacketSent();
    
    PORTD |= 0b00100000;        //digitalWrite(5,HIGH);     //ON Rx

    radio.waitAvailableTimeout(100);
    if (radio.recv(receive_buffer, &buflen)){  
//        radio.printBuffer("Data ", receive_buffer, buflen);
//        retval = sprintf(value,"%x",receive_buffer);
       Serial.println((char)receive_buffer[0]);
    }
    else
    Serial.println(" NA ");
    receive_buffer[3] = 0;
    delay(00);
  }
}
