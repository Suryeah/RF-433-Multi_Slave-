#include <RH_ASK.h>
#include <SPI.h>                       // Not actualy used but needed to compile
#include <avdweb_AnalogReadFast.h>

RH_ASK radio(4000, 11, 12);
String Value;

void setup() {
  Serial.begin(115200);               // Use this for debugging
  if (!radio.init()) {
    Serial.println("Radio module failed to initialize");
  }
}

void loop() {
  uint8_t receive_buffer[10];
  uint8_t buflen = sizeof(receive_buffer);
  radio.waitAvailable();
  if (radio.recv(receive_buffer, &buflen))
  {
    radio.printBuffer("Requested for:", receive_buffer, buflen);

    if (receive_buffer[0] == 49)      // Decimal value of "1"
    {
      int data = map(analogRead(A0), 0, 1024, 0, 100);
      String value = String(data);
      const char *msg = value.c_str();
      radio.send((char*)msg, sizeof(msg));
      radio.waitPacketSent();
      Serial.println((char)msg[0]);
    }
  }
}
