#ifndef MAIN_H
#define MAIN_H

#include <esp_now.h>
#include <WiFi.h>
#include <LinkedList.h>
#include <Preferences.h>


#include "PeerClass.h"

void   PrintMAC(const uint8_t * mac_addr);

extern LinkedList<PeerClass*>   PeerList;
extern LinkedList<PeriphClass*> PeriphList;

extern PeerClass Self;
extern Preferences preferences;

#endif