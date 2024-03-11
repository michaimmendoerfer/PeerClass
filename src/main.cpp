#include <Arduino.h>
#include "PeerClass.h"
#include <LinkedList.h>

LinkedList<PeerClass*> PeerList = LinkedList<PeerClass*>();


void PrintMAC(const uint8_t * mac_addr){
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
}
void setup() {
  Serial.begin(115200);

  Serial.println("Setup");
  PeerClass *Peer;

  uint8_t BroadcastAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  
  Peer = new PeerClass();
  Peer->Setup("Peer-0", 10, BroadcastAddress, false, true, false, false);
	PeerList.add(Peer);

  Peer = new PeerClass();
  Peer->Setup("Peer-1", 11, BroadcastAddress, false, true, false, false);
  PeerList.add(Peer);

  Peer = new PeerClass();
  Peer->Setup("Peer-2", 12, BroadcastAddress, false, true, false, false);
  PeerList.add(Peer);

  
  int current = 0;

  char Buf[50];

	for(int i = 0; i < PeerList.size(); i++){

		// Get animal from list
		Peer = PeerList.get(i);

		// If its a mammal, then print it's name
		if(Peer->GetType() == 11){

			// Avoid printing spacer on the first element
			
			Serial.print(Peer->GetName());
      Serial.println(" is Type:11");
		}
    sprintf(Buf, "List: %d - Peer-Id %d - Periph-Id - %d", i, Peer->GetId(), Peer->GetPeriphId(0));
    Peer->SetupPeriph(0, Buf, 10, false, 0, 0, 0, 0, Peer->GetId());
    sprintf(Buf, "List: %d - Peer-Id %d - Periph-Id - %d", i, Peer->GetId(), Peer->GetPeriphId(1));
    Peer->SetupPeriph(1, Buf, 10, false, 0, 0, 0, 0, Peer->GetId());
    sprintf(Buf, "List: %d - Peer-Id %d - Periph-Id - %d", i, Peer->GetId(), Peer->GetPeriphId(2));
    Peer->SetupPeriph(2, Buf, 10, false, 0, 0, 0, 0, Peer->GetId());
    }

  for(int i = 0; i < PeerList.size(); i++){

		// Get animal from list
		Peer = PeerList.get(i);

    Serial.printf("%s:\n%s\n%s\n%s\n", Peer->GetName(), Peer->GetPeriphName(0),Peer->GetPeriphName(1),Peer->GetPeriphName(2));
		
	}
}

void loop() {
  while(1) {

  }
}

