#include <Arduino.h>
#include "MyClass.h"

PeriphClass::PeriphClass()
{
    Serial.println("PeriphClass-Constructor");
    Serial.print("_Id = "); Serial.println(_ClassId);
    _id = _ClassId;
    _ClassId++;
}

//PeriphClass::PeriphClass(char* Name, int Id, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, float Value, float OldValue, bool Changed, int PeerId)
PeriphClass::PeriphClass(char* Name)
{
    strcpy(_Name, Name);
}

bool  PeriphClass::SetName(char *Name) {
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
    Serial.println("PeerClass-Constructor");
    Serial.print("_Id = "); Serial.println(_ClassId);
    _id = _ClassId;
    _ClassId++;
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

int PeerClass::GetId()
{
    return _Id;
}