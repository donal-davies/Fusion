//
//  DetectorHit.hh
//  
//
//  Created by Donal on 2020/06/09.
//

#ifndef DetectorHit_h
#define DetectorHit_h


#endif /* DetectorHit_h */

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"


class G4AttDef;
class G4AttValue;

class DetectorHit : public G4VHit
{
public:
    DetectorHit(G4int i, G4int l, G4double e, G4double th, G4double p, G4double t, G4double le);
    virtual ~DetectorHit() {}
    
    inline void *operator new (size_t);
    inline void operator delete(void* aHit);
    
    void Print();
    
    G4int GetID() const { return detectorID; };
    
    void setEnergy(G4double gE) { fEnergy = gE; };
    G4double GetEnergy() const { return fEnergy; };
    
    void setTheta(G4double gT) { angleTheta = gT; };
    G4double getTheta() const { return angleTheta; };

    void setPhi(G4double gP) { anglePhi = gP; };
    G4double getPhi() const { return anglePhi; };
    
    void setTime(G4double pTime) { time = pTime; };
    G4double GetTime() const { return time; };

    void setLabel(G4int l) { particleLabel = l; };
    G4int getLabel() const { return particleLabel; };

    void setLength(G4double l) { length = l; };
    G4double getLength() const { return length; };
    
private:
    G4int detectorID;
    G4int particleLabel;
    G4double fEnergy;
    G4double angleTheta;
    G4double anglePhi;
    G4double time;
    G4double length;
};

typedef G4THitsCollection<DetectorHit> DetectorHitCollection;

extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

inline void* DetectorHit::operator new(size_t) {
    if(!DetectorHitAllocator)
        DetectorHitAllocator = new G4Allocator<DetectorHit>;
    return (void*)DetectorHitAllocator->MallocSingle();
}

inline void DetectorHit::operator delete(void* aHit){
    DetectorHitAllocator->FreeSingle((DetectorHit*) aHit);
}

