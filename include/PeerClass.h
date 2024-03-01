#ifndef PEERCLASS_H
#define PEERCLASS_H

#include <Arduino.h>

class PeriphClass {
  
    private:
        static int  _ClassId;

        char        _Name[20];
        int         _Id;
        int         _Type;      //1=Switch, 2=Amp, 3=Volt
        bool        _isADS;
        int         _IOPort;
        float       _NullWert;
        float       _VperAmp;
        int         _Vin;
        float       _Value;
        float       _OldValue;
        bool        _Changed;
        int         _PeerId;
    
    public:
        PeriphClass();
        //PeriphClass(char* Name, int Id, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, float Value, float OldValue, bool Changed, int PeerId);

        bool  SetName(char *Name);
        char *GetName();
        int   GetId();
};

class PeerClass 
{
    private:
        static int _ClassId;

        char       _Name[20];
        int        _Id;
        int        _PNumber;
        u_int8_t   _BroadcastAddress[6];
        uint32_t   _TSLastSeen;
        int        _Type;  // 
        bool       _SleepMode;
        bool       _DebugMode;
        bool       _DemoMode;
        bool       _ReadyToPair;
        PeriphClass *Periph[MAX_PERIPHERALS]; 
    
    public:
        PeerClass();

        bool  SetName(char *Name);
        char *GetName();
        int   GetId();
};

#endif