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
    strcpy(ScreenExportImportBuffer, _Name);
                        
    for (int Si=0; Si<PERIPH_PER_SCREEN; Si++)
    {   
        strcat(ReturnBufferScreen, ";%d",_PeriphId[Si]);
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
    char ExportBuffer[]
    
    preferences.begin("JeepifyPeers", true);
    
    preferences.putInt("PeerCount", PeerList.size());

    for(int i = 0; i < PeerList.size(); i++){
      P = PeerList.get(i);
      sprintf(Buf, "Peer-%d", i);
      preferences.putString(Buf, P->Export());
      Serial.printf("schreibe: [%s]: %s\n", Buf, P->Export());
    }
  
    Serial.println("jetzt kommt Multi");

    for (int s=0; s<MULTI_SCREENS; s++) {
      snprintf(Buf, sizeof(Buf), "Screen-%d", s);
      preferences.putString(Buf, Screen[s].Export());
      Serial.printf("schreibe: [%s]: %s\n", Buf, Screen[s].Export());
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
        strcpy(ScreenExportImportBuffer = Buffer.c_str());
        Serial.printf("gelesen: [%s]: %s\n", Buf, ScreenExportImportBuffer);

        P = new PeerClass();
        P->Import(ScreenExportImportBuffer);
        
        PeerList.add(P);
        for (int Si=0; Si<MAX_PERIPHERALS; Si++) PeriphList.add(P->GetPeriphPtr(Si));
    }
  
    Serial.println("jetzt kommt Multi");

    for (int s=0; s<MULTI_SCREENS; s++) {
      snprintf(Buf, sizeof(Buf), "Screen-%d", s);
      ScreenExportImportBuffer = preferences.getString(Buf, "");

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
        if (Periph.GetPeerId() == P->GetId()) PeriphList.remove(Si);
    }

    for(int i = 0; i < PeerList.size(); i++){
        if (PeerList.get(i) == P) 
        {
            PeerList.remove(i);
            sprintf(Buf, "Peer: %s deleted and removed from list.", P->GetName());
            delete P;
            P = NULL;
        }
    }
}