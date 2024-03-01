#include <Arduino.h>
#include "PeerClass.h"

int  PeriphClass::_PeriphClassId = 0;
int  PeerClass::_PeerClassId = 0;

PeriphClass::PeriphClass()
{
    _Id = _PeriphClassId;
    _PeriphClassId++;
}

//PeriphClass::PeriphClass(char* Name, int Id, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, float Value, float OldValue, bool Changed, int PeerId)
bool PeriphClass::SetName(char* Name)
{
    strcpy(_Name, Name);
    return true;
}

char *PeriphClass::GetName(){
    return (_Name);
}

int PeriphClass::GetId()
{
    return _Id;
}

PeerClass::PeerClass()
{
    _Id = _PeerClassId;
    _PeerClassId++;
}

bool PeerClass::SetName(char *Name)
{
    strcpy(_Name, Name);
    return true;
}

char *PeerClass::GetName()
{
    return (_Name);
}

char *PeerClass::GetPeriphName(int P)
{
    return Periph[P].GetName();
}

bool  PeerClass::SetPeriphName(int P, char *Name)
{
    Periph[P].SetName(Name);
    return true;
}

int PeerClass::GetId()
{
    return _Id;
}