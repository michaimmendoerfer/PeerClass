#include <Arduino.h>
#include "PeerClass.h"
#include <Preferences.h>
#include <esp_now.h>
#include <WiFi.h>
#include "pref_manager.h"
#include "PeerClass.h"
#include "main.h"

int PeerCount;

Preferences preferences;
MultiMonitorClass Screen[MULTI_SCREENS];

char ScreenExportImportBuffer[30*MULTI_SCREENS];

char* MultiMonitorClass::Export() 
// fills ScreenExportImportBuffer with "Name;PeriphId0;PeriphId1;PeriphId2;PeriphId3"
{
    char ReturnBufferScreen[50];

    strcpy(ScreenExportImportBuffer, _Name);
                        
    for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
    {   
        sprintf(ReturnBufferScreen, ";%d",_PeriphId[Si]);
        strcat(ScreenExportImportBuffer, ReturnBufferScreen);
    }

    return ScreenExportImportBuffer;
}
void MultiMonitorClass::Import(char *Buf) 
// import from Buf with "Name;PeriphId0;PeriphId1;PeriphId2;PeriphId3"
{
    strcpy(_Name, strtok(Buf, ";"));
    
    for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
    {  
        _PeriphId[Si] = atoi(strtok(NULL, ";"));
        _Periph[Si]   = FindPeriphById(_PeriphId[Si]);
        _PeerId[Si]   = _Periph[Si]->GetPeerId();
        _Peer[Si]     = FindPeerById(_PeerId[Si]);
    }

}
void SavePeers() 
// writes [Peer-0] - [Name;Type;BroadcastAddress[0-5];SleepMode;DebugMode;DemoMode;Periph0Name;Periph0Type;Periph0Pos;Periph0PeerId...]
{
    PeerClass *P;
    char Buf[10];
    char ExportBuffer[50];
    
    preferences.begin("JeepifyPeers", true);
    
    preferences.putInt("PeerCount", PeerList.size());

    for(int i = 0; i < PeerList.size(); i++){
      P = PeerList.get(i);
      sprintf(Buf, "Peer-%d", i);
      preferences.putString(Buf, P->Export());
      Serial.printf("schreibe: [%s]: %s", Buf, P->Export());
      Serial.println();
    }
  
    Serial.println("jetzt kommt Multi");

    for (int s=0; s<MULTI_SCREENS; s++) {
      snprintf(Buf, sizeof(Buf), "Screen-%d", s);
      preferences.putString(Buf, Screen[s].Export());
      Serial.printf("schreibe: [%s]: %s", Buf, Screen[s].Export());
      Serial.println();
    }
    preferences.end();
}
void GetPeers() 
{
    PeerClass *P;
    char Buf[10];
    String Buffer;

    preferences.begin("JeepifyPeers", true);

    PeerList.clear();


    int PeerCount = preferences.getInt("PeerCount");
    
    for (int Pi=0 ; Pi<PeerCount; Pi++)
    {
        sprintf(Buf, "Peer-%d", Pi);
        Buffer = preferences.getString(Buf, "");
        strcpy(ScreenExportImportBuffer, Buffer.c_str());
        Serial.printf("gelesen: [%s]: %s\n", Buf, ScreenExportImportBuffer);

        P = new PeerClass();
        P->Import(ScreenExportImportBuffer);
        
        PeerList.add(P);
        for (int Si=0; Si<MAX_PERIPHERALS; Si++) PeriphList.add(P->GetPeriphPtr(Si));
    }
  
    Serial.println("jetzt kommt Multi");

    for (int s=0; s<MULTI_SCREENS; s++) {
      snprintf(Buf, sizeof(Buf), "Screen-%d", s);
      Buffer = preferences.getString(Buf, "");
      strcpy(ScreenExportImportBuffer, Buffer.c_str());
        
      Screen[s].Import(ScreenExportImportBuffer);
    }
    preferences.end();
}
void ClearPeers() {
  preferences.begin("JeepifyPeers", false);
    preferences.clear();
    Serial.println("JeepifyPeers cleared...");
  preferences.end();
}
void ClearInit() {
  preferences.begin("JeepifyInit", false);
    preferences.clear();
    Serial.println("JeepifyInit cleared...");
  preferences.end();
}
void DeletePeer(PeerClass *P) 
{
    PeriphClass *Periph;
    
    for (int s=0; s<MULTI_SCREENS; s++) {
      for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
      {
          if (Screen[s].GetPeerId(Si) == P->GetId())
          {
              Screen[s].SetPeerId(Si, -1);
              Screen[s].SetPeer(Si, NULL);
              Screen[s].SetPeriphId(Si, -1);
              Screen[s].SetPeer(Si, NULL);
              Screen[s].SetChanged(true);
          }
      }
    }

    for (int Si=PeriphList.size()-1; Si>=0; Si--)
    {
        Periph = PeriphList.get(Si);
        if (Periph->GetPeerId() == P->GetId()) PeriphList.remove(Si);
    }

    for(int i = 0; i < PeerList.size(); i++){
        if (PeerList.get(i) == P) 
        {
            PeerList.remove(i);
            Serial.printf("Peer: %s deleted and removed from list.", P->GetName());
            delete P;
            P = NULL;
        }
    }
}
void RegisterPeers() 
{
  PeerClass *P;

  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 1;
  peerInfo.encrypt = false;
  memset(&peerInfo, 0, sizeof(peerInfo));

  // Register BROADCAST
  for (int b=0; b<6; b++) peerInfo.peer_addr[b] = 0xff;
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
      PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
    }
    else {
      Serial.print (" ("); PrintMAC(peerInfo.peer_addr);  Serial.println(") added...");
    }

  // Register Peers
  for (int i=0; i<PeerList.size(); i++) 
  {
      P = PeerList.get(i);
      memcpy(peerInfo.peer_addr, P->GetBroadcastAddress(), 6);

      if (esp_now_add_peer(&peerInfo) != ESP_OK) 
      {
          PrintMAC(peerInfo.peer_addr); Serial.println(": Failed to add peer");
      }
      else {
          Serial.print("Peer: "); Serial.print(P->GetName()); 
          Serial.print (" ("); PrintMAC(peerInfo.peer_addr); Serial.println(") added...");
      }
  }
}

void ReportAll()
{
    PeerClass *P;
    
    for(int i=0; i < PeerList.size(); i++)
    {
      P = PeerList.get(i);
      Serial.printf("[%d] %s, Type:%d", P->GetId(), P->GetName(), P->GetType());
      Serial.println();
      for (int Si=0; Si<MAX_PERIPHERALS; Si++)
      {
          if (P->GetPeriphType(Si) > 0)
          {
              Serial.printf("    %d: %s(%d) at position %d", P->GetPeriphId(Si), P->GetPeriphName(Si), P->GetPeriphType(Si), P->GetPeriphPos(Si));
              Serial.println();
          }
      }

      for (int s=0; s<MULTI_SCREENS; s++) {
          //Serial.printf("Screen[%d]: %s", s, Screen[s].GetName());
          for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
          {
              if (Screen[s].GetPeriphId(Si))
              {
                Serial.printf("    %d: %s(%d) at position %d", Screen[s].GetPeriph(Si)->GetId(), Screen[s].GetPeriph(Si)->GetName(), Screen[s].GetPeriph(Si)->GetType(), Si);
                Serial.println();
              }
          }
      }
    }
}