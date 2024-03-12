#ifndef PREF_MANAGER_H
#define PREF_MANAGER_H

#include <Preferences.h>


class MultiMonitorClass {
    
    private:
        char         _Name[20];
        int          _Id;
        bool         _Changed;
        PeerClass   *_Peer    [PERIPH_PER_SCREEN];
        int          _PeerId  [PERIPH_PER_SCREEN];
        PeriphClass *_Periph  [PERIPH_PER_SCREEN];
        int          _PeriphId[PERIPH_PER_SCREEN];
        bool         _Used;
    
    public:
        MultiMonitorClass() { strcpy(_Name, ""); };
        char *Export();
        void  Import(char *Buf);

        bool  SetName(char* Name) { strcpy(_Name, Name); return true; }
        char *GetName(){ return (_Name); }
        int   GetId() { return _Id; }
        void  SetId(int Id) { _Id = Id; }
        bool  hasChanged() { return _Changed; }
        bool  GetChanged() { return _Changed; }
        void  SetChanged(bool Changed) { _Changed = Changed; }
        int   GetPeerId(int Pos) { return _PeerId[Pos]; }
        void  SetPeerId(int Pos, int PeerId) { _PeerId[Pos] = PeerId; }
        int   GetPeriphId(int Pos) { return _PeriphId[Pos]; }
        void  SetPeriphId(int Pos, int PeriphId) { _PeriphId[Pos] = PeriphId; }
        
        PeriphClass *GetPeriph(int Pos) { return _Periph[Pos]; }
        void         SetPeriph(int Pos, PeriphClass *Periph) { _Periph[Pos] = Periph; }
        PeerClass   *GetPeer  (int Pos) { return _Peer[Pos]; }
        void         SetPeer  (int Pos, PeerClass *Peer) { _Peer[Pos] = Peer; }

        void         AddPeriph(int Pos, PeriphClass *Periph) { _Periph[Pos]   = Periph; 
                                                               _PeriphId[Pos] = Periph->GetId();
                                                               _Peer[Pos]     = FindPeerById(Periph->GetPeerId());
                                                               _PeerId[Pos]   = Periph->GetPeerId();
                                                               _Changed = true; }
        void         DelPeriph(int Pos)                      { _Periph[Pos]   = NULL; 
                                                               _PeriphId[Pos] = -1;
                                                               _Peer[Pos]     = NULL;
                                                               _PeerId[Pos]   = -1; }
        
};

void   SavePeers();
void   GetPeers();
void   DeletePeer(PeerClass *P);
void   ReportAll();
void   RegisterPeers();
void   ClearPeers();
void   ClearInit();
void   ReportAll();
void   ReportScreen(int s);

extern Preferences preferences;
extern MultiMonitorClass Screen[MULTI_SCREENS];
#endif