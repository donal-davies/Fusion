//
//  SystemSD.cpp
//  
//
//  Created by Donal on 2020/06/09.
//

#include <stdio.h>

#include "SystemSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4VProcess.hh"
#include "G4String.hh"

SystemSD::SystemSD(G4String name)
: G4VSensitiveDetector(name), hitsCollection(0), detectorID(-1)
{
    G4String Dname = "detectorColl";
    collectionName.insert(Dname);
}

SystemSD::~SystemSD(){}

void SystemSD::Initialize(G4HCofThisEvent* HCE){
    hitsCollection = new DetectorHitCollection(SensitiveDetectorName,collectionName[0]);
    
    if (detectorID < 0){
        detectorID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
    }
    HCE->AddHitsCollection(detectorID, hitsCollection);
}

G4bool SystemSD::ProcessHits(G4Step* step, G4TouchableHistory*){

    bool CHECK_DEUT = false;

    if (!CHECK_DEUT) {
        const G4VProcess* s = step->GetTrack()->GetCreatorProcess();
        if (s == 0)return true;
        if (s->GetProcessName().compare("dInelastic") == 1)return true;

        if (!step->IsFirstStepInVolume())return true;

    }
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4Track* particleTrack = step->GetTrack();
    
    G4ParticleTable* table = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* neutron;
    if (CHECK_DEUT)neutron = table->FindParticle("deuteron");
    else neutron = table->FindParticle("neutron");
    G4ParticleDefinition* alpha = table->FindParticle("alpha");

    G4int label = 0;
    if (particleTrack->GetDefinition() == neutron)label = 1;
    else if (particleTrack->GetDefinition() == alpha)label = 2;
    if (label == 0)return true;
    G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    
    G4int copyNo = touchable->GetVolume()->GetCopyNo();

    if (CHECK_DEUT) {
        std::vector<DetectorHit*>* hits = hitsCollection->GetVector();
        for (auto iter = hits->begin(); iter != hits->end(); ++iter) {
            if ((*iter)->GetID() == copyNo) {
                (*iter)->setLength((*iter)->getLength() + step->GetStepLength());
                return true;
            }
        }
    }
    G4double energy = preStepPoint->GetKineticEnergy();


    G4ThreeVector direction = preStepPoint->GetMomentumDirection();
    G4double angleTheta = direction.getTheta();
    G4double anglePhi = direction.getPhi();
    G4double time = preStepPoint->GetGlobalTime()*ns;

    DetectorHit* hit = new DetectorHit(copyNo, label, energy, angleTheta, anglePhi, time, step->GetStepLength());
    hitsCollection->insert(hit);
    
    return true;
}
