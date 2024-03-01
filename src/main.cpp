#include <Arduino.h>
#include "PeerClass.h"

PeerClass Peer;
PeriphClass Periph;

void setup() {
  Serial.begin(115200);

  Serial.println("Setup");

  Peer.SetName("PeerName1");
  Peer.SetPeriphName(1, "PeriphName1");

  Serial.print("Peer.Id="); Serial.println(Peer.GetId());
  Serial.print("Peer.Name="); Serial.println(Peer.GetName());
  Serial.print("Periph.Name="); Serial.println(Peer.GetPeriphName(1));
}

void loop() {
  while(1) {

  }
}

