//
//  Run.cpp
//  
//
//  Created by Donal on 2020/06/10.
//

#include <stdio.h>

#include "Run.hh"

#include "G4Event.hh"
#include "G4SDManager.hh"
#include "DetectorHit.hh"

Run::Run() : G4Run(),
neutronFlux(0), minTime(INT_MAX), maxTime(INT_MIN), energy(),
detectorID(-1)
{
}

void Run::RecordEvent(const G4Event* event){
    G4Run::RecordEvent(event);
    
    if (detectorID < 0){
        G4SDManager* sdMan = G4SDManager::GetSDMpointer();
        detectorID = sdMan->GetCollectionID("detectorColl");
    }
    
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce){
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n";
        G4Exception("Run::RecordEvent()","Code001", JustWarning, msg);
        return;
    }
    const DetectorHitCollection* detectorHC = static_cast<const DetectorHitCollection*>(hce->GetHC(detectorID));
    
    if (!detectorHC){
        G4ExceptionDescription msg;
            msg << "Some of hits collections of this event not found.\n";
           G4Exception("Run::RecordEvent()","Code001", JustWarning, msg);
            return;
    }
    

    for (size_t i=0; i < detectorHC->GetSize(); i++){
        DetectorHit* hit = (*detectorHC)[i];
        G4double time = hit->GetTime();
        
        minTime = std::min(minTime, time);
        maxTime = std::max(maxTime, time);
        
        G4double hitEnergy = hit->GetEnergy();
        if (energy.count(hitEnergy)) {
            energy[hitEnergy] += 1;
        }else{
            energy[hitEnergy] = 1;
        }
    }
}

void Run::Merge(const G4Run* aRun){
    const Run* localRun = static_cast<const Run*>(aRun);
    
    G4Run::Merge(aRun);
}
