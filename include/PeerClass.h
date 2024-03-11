#ifndef PEERCLASS_H
#define PEERCLASS_H

#include <Arduino.h>

#define MAX_PERIPHERALS   4
class PeriphClass {
    static int  _ClassId;

    private:
        char        _Name[50];
        int         _Id;
        int         _Type;      //1=Switch, 2=Amp, 3=Volt
        int         _Pos;       //Periph 1..4.. from one peer
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
        void  Setup(int P, char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId);
        
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
        PeriphClass Periph[MAX_PERIPHERALS]; 
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
        
        PeriphClass *GetPeriph(int P);
        PeriphClass *GetPeriph(char *Name);
        
        
        void  SetupPeriph(int P, char* Name, int Type, bool isADS, int IOPort, float Nullwert, float VperAmp, int Vin, int PeerId);
        char *GetPeriphName(int P);
        bool  SetPeriphName(int P, char *Name);
        
        float GetPeriphValue(int P);
        float GetPeriphValue(char *Name);
        void  SetPeriphValue(int P, float Value);
        void  SetPeriphValue(char *Name, float Value);
        float GetPeriphOldValue(int P);
        
        bool  PeriphChanged(int P);
        
        bool  PeriphHasADS(int P);
        bool  GetPeriphADS(int P);
        
        int   GetPeriphType(int P);
        
        int   GetPeriphVin(int P);
        void  SetPeriphVin(int P, float Vin);
        
        float GetPeriphVperAmp(int P);
        void  SetPeriphVperAmp(int P, float VperAmp);
        
        int   GetPeriphIOPort(int P);
        float GetPeriphNullwert(int P);
        float GetPeriphNullwert(char *Name);
        void  SetPeriphNullwert(int P, float Nullwert);
        void  SetPeriphNullwert(char *Name, float Nullwert);

        int   GetPeriphId(char *Name);    
        int   GetPeriphId(int Pos);    
};

#endif