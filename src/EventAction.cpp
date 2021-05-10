//
//  EventAction.cpp
//  
//
//  Created by Donal on 2020/06/09.
//

#include "EventAction.hh"
#include "DetectorHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "g4csv.hh"

EventAction::EventAction()
: G4UserEventAction(),
detectorID(-1)
{
    G4RunManager::GetRunManager()->SetPrintProgress(1);
}

EventAction::~EventAction(){
}

/*
    Acquire sensitive detector ID if no ID is currently stored.
*/
void EventAction::BeginOfEventAction(const G4Event*){
    if(detectorID == -1){
        G4SDManager* sdManager = G4SDManager::GetSDMpointer();
        detectorID = sdManager->GetCollectionID("detector/detectorColl");
    }
}

/*
    Collate event data once event has concluded
*/
void EventAction::EndOfEventAction(const G4Event* event){
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    
    if(!hce){
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found. \n";
        G4Exception("EventAction::EndOfEventAction()","Code001",JustWarning,msg);
        return;
    }
    
    DetectorHitCollection* HC = static_cast<DetectorHitCollection*>(hce->GetHC(detectorID));
    
    if( (!HC) ){
        G4ExceptionDescription msg;
        msg << "Portion of hits collections of this event not found.\n";
        G4Exception("EventAction::EndOfEventAction()","Code001",JustWarning,msg);
    }
    
    //Write recorded data to the analysis manager for later saving.
    G4AnalysisManager* am = G4AnalysisManager::Instance();
    
    for (int i = 0; i < HC->entries(); ++i){
        am->FillNtupleIColumn(0, (*HC)[i]->getLabel());
        am->FillNtupleDColumn(1, (*HC)[i]->GetTime());
        am->FillNtupleDColumn(2, (*HC)[i]->GetEnergy());
        am->FillNtupleDColumn(3, (*HC)[i]->getTheta());
        am->FillNtupleDColumn(4, (*HC)[i]->getPhi());
        am->FillNtupleDColumn(5, (*HC)[i]->getLength());
        am->AddNtupleRow();
    }
    
    //Diagnostics
    G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
    if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
}
