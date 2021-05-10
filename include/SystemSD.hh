//
//  SystemSD.h
//  
//
//  Created by Donal on 2020/06/09.
//

#ifndef SystemSD_h
#define SystemSD_h

#include "G4VSensitiveDetector.hh"
#include "DetectorHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class SystemSD : public G4VSensitiveDetector
{
public:
    SystemSD(G4String name);
    virtual ~SystemSD();
    
    virtual void Initialize(G4HCofThisEvent* HCE);
    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist);
    
private:
    DetectorHitCollection* hitsCollection;
    G4int detectorID;
};

#endif /* SystemSD_h */
