//
//  DetectorHit.cpp
//  
//
//  Created by Donal on 2020/06/09.
//

#include <stdio.h>

#include "DetectorHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;

DetectorHit::DetectorHit(G4int i, G4int l, G4double e, G4double th, G4double p, G4double t, G4double le)
: G4VHit(),
detectorID(i),
particleLabel(l), fEnergy(e), angleTheta(th), anglePhi(p), time(t), length(le) {}

/*
    Outputs hit data to console. Deprecated.
*/
void DetectorHit::Print(){
    //G4cout << GetID() << "------------" << G4endl;
    //G4cout << GetEnergy() << " MeV" << G4endl;
    //G4cout << GetFlux() << " neutrons/m^2" << G4endl;
    //G4cout << GetTime() << " ns" << G4endl;
}
