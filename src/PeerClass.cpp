#include <Arduino.h>
#include "PeerClass.h"

int  PeriphClass::_ClassId = 0;
int  PeerClass::_ClassId = 0;

PeriphClass::PeriphClass()
{
    _Id = _ClassId;
    _ClassId++;
}
void  PeriphClass::Setup(char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId)
{
    strcpy(_Name, Name);
    _Type = Type;
    _isADS = isADS;
    _IOPort = IOPort;
    _Nullwert = Nullwert;
    _VperAmp = VperAmp;
    _PeerId = PeerId;
}
bool  PeriphClass::SetName(char* Name) { strcpy(_Name, Name); return true; }
char *PeriphClass::GetName(){ return (_Name); }
int   PeriphClass::GetId() { return _Id; }
void  PeriphClass::SetId(int Id) { _Id = Id; }
int   PeriphClass::GetType() { return _Type; }
void  PeriphClass::SetType(int Type) { _Type = Type; }
bool  PeriphClass::isADS() { return _isADS; }
bool  PeriphClass::GetADS() { return _isADS; }
void  PeriphClass::SetADS(bool isADS) { _isADS = isADS; }
int   PeriphClass::GetIOPort() { return _IOPort; }
void  PeriphClass::SetIOPort(int IOPort) { _IOPort = IOPort; }
float PeriphClass::GetNullwert() { return _Nullwert; }
void  PeriphClass::SetNullwert(float Nullwert) { _Nullwert = Nullwert; }
float PeriphClass::GetVperAmp() { return _VperAmp; }
void  PeriphClass::SetVperAmp(float VperAmp) { _VperAmp = VperAmp; }
int   PeriphClass::GetVin() { return _Vin; }
void  PeriphClass::SetVin(int Vin) { _Vin = Vin; }
float PeriphClass::GetValue() { return _Value; }
void  PeriphClass::SetValue(float Value) { _Value = Value; }
float PeriphClass::GetOldValue() { return _OldValue; }
void  PeriphClass::SetOldValue(float OldValue) { _OldValue = OldValue; }
bool  PeriphClass::hasChanged() { return _Changed; }
bool  PeriphClass::GetChanged() { return _Changed; }
void  PeriphClass::SetChanged(bool Changed) { _Changed = Changed; }



PeerClass::PeerClass()
{
    _Id = _ClassId;
    _ClassId++;
}
void  PeerClass::Setup(char* Name, int Type, uint8_t *BroadcastAddress, bool SleepMode, bool DebugMode, bool DemoMode, bool PairMode)
{
    strcpy(_Name, Name);
    _Type = Type;
    for (int b=0; b<6; b++)_BroadcastAddress[b] = BroadcastAddress[b];
    _SleepMode = SleepMode;
    _DebugMode = DebugMode;
    _DemoMode  = DemoMode;
    _PairMode  = PairMode;
}      
bool  PeerClass::SetName(char *Name) { strcpy(_Name, Name); return true; }
char *PeerClass::GetName() { return (_Name); }
int   PeerClass::GetId() { return _Id; }
void  PeerClass::SetId(int Id) { _Id = Id; }
int   PeerClass::GetType() { return _Type; }
void  PeerClass::SetType(int Type) { _Type = Type; }
uint8_t *PeerClass::GetBroadcastAddress() { return _BroadcastAddress; }
void     PeerClass::SetBroadcastAddress(int8_t *BroadcastAddress) 
{ 
    for (int b=0; b<6; b++)_BroadcastAddress[b] = BroadcastAddress[b];
}
uint32_t PeerClass::GetTSLastSeen() { return _TSLastSeen; }
void     PeerClass::SetTSLastSeen(uint32_t TSLastSeen) { _TSLastSeen = TSLastSeen; }
bool  PeerClass::GetSleepMode() { return _SleepMode; }
void  PeerClass::SetSleepMode(bool SleepMode) { _SleepMode = SleepMode; }
bool  PeerClass::GetDebugMode() { return _DebugMode; }
void  PeerClass::SetDebugMode(bool DebugMode) { _DebugMode = DebugMode; }
bool  PeerClass::GetDemoMode() { return _DemoMode; }
void  PeerClass::SetDemoMode(bool DemoMode) { _DemoMode = DemoMode; }
bool  PeerClass::GetPairMode() { return _PairMode; }
void  PeerClass::SetPairMode(bool PairMode) { _PairMode = PairMode; }
char *PeerClass::GetPeriphName(int P) { return Periph[P].GetName(); }
bool  PeerClass::SetPeriphName(int P, char *Name) { Periph[P].SetName(Name); return true; }
void  PeerClass::SetupPeriph(int P, char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId)
{
    Periph[P].Setup(Name, Type, isADS, IOPort, Nullwert, VperAmp, Vin, PeerId);
}

int   PeerClass::GetPeriphId(char *Name)
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) return Periph[P].GetId();
    }
    return -1;
}
void  PeerClass::SetPeriphValue(int P, float Value)
{
    Periph[P].SetValue(Value);
}
void  PeerClass::SetPeriphValue(char *Name, float Value)
{
   for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) Periph[P].SetValue(Value); 
    }    
}
float PeerClass::GetPeriphValue(int P) { return Periph[P].GetValue(); }
float PeerClass::GetPeriphValue(char *Name)
{
   for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) return Periph[P].GetValue(); 
    }    

    return -1;
}

float PeerClass::GetPeriphNullwert(int P) { return Periph[P].GetNullwert(); }
float PeerClass::GetPeriphNullwert(char *Name) 
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) return Periph[P].GetNullwert(); 
    }    

    return -1;
}
void  PeerClass::SetPeriphNullwert(int P, float Nullwert) { Periph[P].SetNullwert(Nullwert); }
void  PeerClass::SetPeriphNullwert(char *Name, float Nullwert)
{
    for (int P=0; P<MAX_PERIPHERALS; P++)
    {   
        if (strcmp(Name, Periph[P].GetName()) == 0) Periph[P].SetNullwert(Nullwert);
    }    
}
