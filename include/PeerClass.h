#ifndef PEERCLASS_H
#define PEERCLASS_H

#include <Arduino.h>

class PeriphClass {
    static int  _ClassId;

    private:
        char        _Name[20];
        int         _Id;
        int         _Type;      //1=Switch, 2=Amp, 3=Volt
        bool        _isADS;
        int         _IOPort;
        float       _Nullwert;
        float       _VperAmp;
        int         _Vin;
        float       _Value;
        float       _OldValue;
        bool        _Changed;
        int         _PeerId;
    
    public:
        PeriphClass();
        void  Setup(char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId);
        
        bool  SetName(char* Name);
        char *GetName();
        int   GetId();
        void  SetId(int Id);
        int   GetType();
        void  SetType(int Type);
        bool  isADS();
        bool  GetADS();
        void  SetADS(bool isADS);
        int   GetIOPort();
        void  SetIOPort(int IOPort);
        float GetNullwert();
        void  SetNullwert(float Nullwert);
        float GetVperAmp();
        void  SetVperAmp(float VperAmp);
        int   GetVin();
        void  SetVin(int Vin);
        float GetValue();
        void  SetValue(float Value);
        float GetOldValue();
        void  SetOldValue(float OldValue);
        bool  hasChanged();
        bool  GetChanged();
        void  SetChanged(bool Changed);        
};

class PeerClass 
{
    static int _ClassId;

    private:
        char       _Name[20];
        int        _Id;
        int        _Type;  
        u_int8_t   _BroadcastAddress[6];
        bool       _SleepMode;
        bool       _DebugMode;
        bool       _DemoMode;
        bool       _PairMode;
        PeriphClass Periph[4]; 
        uint32_t   _TSLastSeen;
        
    
    public:
        PeerClass();
        void  Setup(char* Name, int Type, uint8_t *BroadcastAddress, bool SleepMode, bool DebugMode, bool DemoMode, bool PairMode);
        
        bool  SetName(char *Name);
        char *GetName();
        int   GetId();
        void  SetId(int Id);
        int   GetType();
        void  SetType(int Type);
        uint8_t *GetBroadcastAddress();
        void     SetBroadcastAddress(int8_t* BroadcastAddress);
        uint32_t GetTSLastSeen();
        void     SetTSLastSeen(uint32_t TSLastSeen);
        bool  GetSleepMode();
        void  SetSleepMode(bool SleepMode);
        bool  GetDebugMode();
        void  SetDebugMode(bool DebugMode);
        bool  GetDemoMode();
        void  SetDemoMode(bool DemoMode);
        bool  GetPairMode();
        void  SetPairMode(bool PairMode);
        void  SetupPeriph(int P, char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId);
        char *GetPeriphName(int P);
        bool  SetPeriphName(int P, char *Name);
};

#endif