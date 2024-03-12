#include <Arduino.h>
#include "PeerClass.h"
#include "pref_manager.h"
#include <LinkedList.h>
#include "Jeepify.h"

LinkedList<PeerClass*>   PeerList =   LinkedList<PeerClass*>();
LinkedList<PeriphClass*> PeriphList = LinkedList<PeriphClass*>();

void setup() {
  Serial.begin(115200);

  Serial.println("Setup");
  PeerClass *Peer;

  uint8_t BroadcastAddress[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  
  Peer = new PeerClass();
  Peer->Setup("Peer-1", 1, BroadcastAddress, false, true, false, false);
	PeerList.add(Peer);

  Peer = new PeerClass();
  Peer->Setup("Peer-2", 4, BroadcastAddress, false, true, false, false);
  PeerList.add(Peer);

  Peer = new PeerClass();
  Peer->Setup("Peer-3", 9, BroadcastAddress, false, true, false, false);
  PeerList.add(Peer);

  char Buf[50];
  Serial.printf("PeerList.size() = %d",PeerList.size());
  Serial.println();

    for(int i = 0; i < PeerList.size(); i++){

      Peer = PeerList.get(i);

      Serial.printf("List: %d - Peer-Id %d - Periph-Id - %d", i, Peer->GetId(), Peer->GetPeriphId(0));
      Serial.println();
      Peer->PeriphSetup(0, "Volt-1", SENS_TYPE_VOLT, false, 0, 0, 0, 0, Peer->GetId());
      PeriphList.add(Peer->GetPeriphPtr(0));
      Serial.printf("List: %d - Peer-Id %d - Periph-Id - %d", i, Peer->GetId(), Peer->GetPeriphId(1));
      Serial.println();
      Peer->PeriphSetup(1, "Volt-2", SENS_TYPE_VOLT, false, 0, 0, 0, 0, Peer->GetId());
      PeriphList.add(Peer->GetPeriphPtr(1));
      Serial.printf("List: %d - Peer-Id %d - Periph-Id - %d", i, Peer->GetId(), Peer->GetPeriphId(2));
      Serial.println();
      Peer->PeriphSetup(2, "Switch-1", SENS_TYPE_SWITCH, false, 0, 0, 0, 0, Peer->GetId());
      PeriphList.add(Peer->GetPeriphPtr(2));
    }

      ReportAll();

      Serial.println();

      ActivePeer = FindFirstPeer(MODULE_ALL);
      Serial.printf("1.Peer ist %s\n\r", ActivePeer->GetName());
      ActivePeriph = FindFirstPeriph(ActivePeer, SENS_TYPE_VOLT);
      Serial.printf("1.VOLT-Sensor of %s ist %s.\n\r", ActivePeer->GetName(), ActivePeriph->GetName());
      ActivePeriph = FindNextPeriph(ActivePeriph, SENS_TYPE_VOLT, true);
      Serial.printf("2.VOLT-Sensor of %s ist %s.\n\r", ActivePeer->GetName(), ActivePeriph->GetName());
      ActivePeriph = FindNextPeriph(ActivePeriph, SENS_TYPE_VOLT, true);
      Serial.printf("3.VOLT-Sensor of %s ist %s.\n\n\r", ActivePeer->GetName(), ActivePeriph->GetName());
        
      ActivePeer = FindFirstPeer(MODULE_ALL);

      do {
          Serial.printf("[%d] - %s\n\r", ActivePeer->GetId(), ActivePeer->GetName());
          ActivePeer = FindNextPeer(ActivePeer, MODULE_ALL, false);
      } while (ActivePeer);

      ActivePeer = FindFirstPeer(MODULE_ALL);
      Serial.printf("FirstPeer: %s", ActivePeer->GetName());
      ActivePeer = FindNextPeer(ActivePeer, MODULE_ALL, true);
      Serial.printf("NextPeer: %s", ActivePeer->GetName());
      ActivePeer = FindPrevPeer(ActivePeer, MODULE_ALL, true);
      Serial.printf("PrevPeer: %s", ActivePeer->GetName());
      
      Serial.printf("after FirstPeer - NextPeer - PrevPeer:\n\r[%d] - %s\n\r", ActivePeer->GetId(), ActivePeer->GetName());

      ActivePeriph = FindFirstPeriph(ActivePeer, SENS_TYPE_SWITCH);
      Screen[0].AddPeriph(0, ActivePeriph);
      ActivePeriph = FindNextPeriph(ActivePeriph, SENS_TYPE_SENS, true);
      Screen[0].AddPeriph(1, ActivePeriph);
      ActivePeriph = FindNextPeriph(ActivePeriph, SENS_TYPE_SENS, true);
      Screen[0].AddPeriph(2, ActivePeriph);
      ActivePeriph = FindNextPeriph(ActivePeriph, SENS_TYPE_SENS, true);
      Screen[0].AddPeriph(3, ActivePeriph);

      Serial.println("Screen-0:");
      for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
      {
          Serial.printf("    [%d] - %s[%d]\n\r", Screen[0].GetPeriph(Si)->GetId(), Screen[0].GetPeriph(Si)->GetName(), Screen[0].GetPeriph(Si)->GetType());
      }
}

void loop() {
  while(1) {

  }
}

void PrintMAC(const uint8_t * mac_addr){
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
}