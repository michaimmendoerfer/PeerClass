#include <Arduino.h>
#include "PeerClass.h"

PeerClass Peer;
PeriphClass Periph;

void setup() {
  Serial.begin(115000);

  Serial.println("Setup");

  Peer.SetName("PeerName1");
  Periph.SetName("PeripchName1");
  
}

void loop() {
  while(1) {

  }
}

