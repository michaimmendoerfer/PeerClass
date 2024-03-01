#include <Arduino.h>
#include "PeerClass.h"

PeerClass Peer;
PeriphClass Periph;

void setup() {
  Serial.begin(115000);

  Serial.println("Setup");

  Peer.SetName("PeerName1");
  Periph.SetName("PeripchName1");

  Serial.print("Peer.Id="); Serial.println(Peer.GetId());
  Serial.print("Peer.Nanme="); Serial.println(Peer.GetName());
  Serial.print("Periph.Id="); Serial.println(Periph.GetId());
  Serial.print("Periph.Name="); Serial.println(Periph.GetName());
}

void loop() {
  while(1) {

  }
}

