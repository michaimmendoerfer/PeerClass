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
void  PeriphClass::SetIOPort(int Port) { _IOPort = IOPort; }
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
bool  PeerClass::SetName(char *Name) { strcpy(_Name, Name); return true; }
char *PeerClass::GetName() { return (_Name); }
int   PeerClass::GetId() { return _Id; }
void  PeerClass::SetId(int Id) { _Id = Id; }
int   PeerClass::GetType() { return _Type; }
void  PeerClass::SetType(int Type) { _Type = Type; }
uint8_t[6] PeerClass::GetBroadcastAddress() { return _BroadcastAddress; }
void       PeerClass::SetBroadcastAddress(int8_t[6] BroadcastAdress) { _BroadcastAddress = BroadcastAdress }
uint32_t   PeerClass::GetTSLastSeen() { return _TSLastSeen; }
void       PeerClass::SetTSLastSeen(uint32_t TSLastSeen) { _TSLastSeen = TSLastSeen; }
bool  PeerClass::GetSleepMode() { return _SleepMode; }
void  PeerClass::SetSleepMode(bool SleepMode) { _SleepMode = SleepMode; }
bool  PeerClass::GetDebugMode() { return _SleepMode; }
void  PeerClass::SetDebugMode(bool DebugMode) { _DebugMode = DebugMode; }
bool  PeerClass::GetDemoMode() { return _SleepMode; }
void  PeerClass::SetSleepMode(bool SleepMode) { _SleepMode = SleepMode; }

        uint32_t   _TSLastSeen;
        int        _Type;  // 
        bool       _SleepMode;
        bool       _DebugMode;
        bool       _DemoMode;
        bool       _ReadyToPair;
        PeriphClass Periph[4]; 
char *PeerClass::GetPeriphName(int P) { return Periph[P].GetName(); }
bool  PeerClass::SetPeriphName(int P, char *Name) { Periph[P].SetName(Name); return true; }
int   PeerClass::GetId() { return _Id; }
