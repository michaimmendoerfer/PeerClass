#include <Arduino.h>
#include "PeerClass.h"

PeerClass Peer[10];
PeriphClass Periph;

void PrintMAC(const uint8_t * mac_addr){
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
}
void setup() {
  Serial.begin(115200);

  Serial.println("Setup");

  uint8_t BroadcastAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  Peer[0].Setup("Peer-0", 10, BroadcastAddress, false, true, false, false);
  Peer[1].Setup("Peer-1", 11, BroadcastAddress, false, true, false, false);
  Peer[2].Setup("Peer-2", 12, BroadcastAddress, false, true, false, false);
  
  Peer[0].SetupPeriph(0,"Peer 0 - Periph 0", 1, 1, 23, 3521, 166, 200, Peer[0].GetId());
  Peer[0].SetupPeriph(1,"Peer 0 - Periph 1", 2, 1, 23, 3521, 166, 200, Peer[0].GetId());
  Peer[0].SetupPeriph(2,"Peer 0 - Periph 2", 3, 1, 23, 3521, 166, 200, Peer[0].GetId());
  Peer[0].SetupPeriph(3,"Peer 0 - Periph 3", 4, 1, 23, 3521, 166, 200, Peer[0].GetId());


  Serial.print("Peer[0].Id="); Serial.println(Peer[0].GetId());
  Serial.print("Peer[0].Name="); Serial.println(Peer[0].GetName());
  Serial.print("Peer[0].Periph1.Name="); Serial.println(Peer[0].GetPeriphName(1));
  Serial.print("Peer[0].MAC="); PrintMAC(Peer[0].GetBroadcastAddress());
}

void loop() {
  while(1) {

  }
}

