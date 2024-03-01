#include <Arduino.h>
#include "PeerClass.h"

PeerClass Peer[10];
PeriphClass Periph;

void setup() {
  Serial.begin(115200);

  Serial.println("Setup");

  Peer[0].SetName("PeerName0");
  Peer[0].SetPeriphName(1, "P0-PeriphName1");

  Peer[1].SetName("PeerName1");
  Peer[1].SetPeriphName(1, "P1-PeriphName1");



  Serial.print("Peer[0].Id="); Serial.println(Peer[0].GetId());
  Serial.print("Peer[0].Name="); Serial.println(Peer[0].GetName());
  Serial.print("Peer[0].Periph1.Name="); Serial.println(Peer[0].GetPeriphName(1));
  Serial.print("Peer[1].Id="); Serial.println(Peer[1].GetId());
  Serial.print("Peer[1].Name="); Serial.println(Peer[1].GetName());
  Serial.print("Peer[1].Periph1.Name="); Serial.println(Peer[1].GetPeriphName(1));
}

void loop() {
  while(1) {

  }
}

