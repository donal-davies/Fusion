//
//  RunAction.cpp
//  
//
//  Created by Donal on 2020/06/10.
//

#include <stdio.h>

#include "RunAction.hh"
#include "Run.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"

#include "g4csv.hh"

RunAction::RunAction()
: G4UserRunAction(), filename("output"), entry(1.0*cm)
{
    DefineCommands();
    
    G4AnalysisManager* am = G4AnalysisManager::Instance();
    G4cout << "Using: " << am->GetType() << G4endl;
    
    am->SetVerboseLevel(0);
    am->SetFileName("Data/"+filename);
    
    am->CreateNtuple(filename,"Hits");
    am->CreateNtupleIColumn("Label");
    am->CreateNtupleDColumn("Time");
    am->CreateNtupleDColumn("Energy");
    am->CreateNtupleDColumn("AngleTheta");
    am->CreateNtupleDColumn("AnglePhi");
    am->CreateNtupleDColumn("PenetrationDepth");
    am->FinishNtuple();
}

RunAction::~RunAction(){}

void RunAction::DefineCommands(){
    G4GenericMessenger* messenger = new G4GenericMessenger(this, "/runData/", "Data control");
    
    G4GenericMessenger::Command& thicknessCommand = messenger->DeclareMethodWithUnit("entry","cm",&RunAction::SetEntry,"Set the thickness of the sample for the current run.");
    
    thicknessCommand.SetParameterName("thickness", true);
    thicknessCommand.SetDefaultValue(1.0*cm);
    
    G4GenericMessenger::Command& filenameCommand = messenger->DeclareMethod("filename",&RunAction::SetFilename,"Set the filename.");
    
    filenameCommand.SetParameterName("filename",true);
    filenameCommand.SetDefaultValue("output");
}

G4Run* RunAction::GenerateRun(){
    return new Run;
}

void RunAction::EndOfRunAction(const G4Run* run){
    const Run* myRun = dynamic_cast<const Run*>(run);
    if (myRun){
        G4int nEvents = myRun->GetNumberOfEvent();
        if ( nEvents < 1){
            G4ExceptionDescription msg;
            msg << "Run consists of 0 events";
            G4Exception("RunAction::EndOfRunAction()","Code001", JustWarning, msg);
        }
        G4double minTime = myRun->GetMinTime();
        G4double maxTime = myRun->GetMaxTime();
        std::map<G4double, G4int> energy = *(myRun->GetEnergy());
    }
    
    G4AnalysisManager* am = G4AnalysisManager::Instance();
    
    am->Write();
    am->CloseFile();
}

void RunAction::BeginOfRunAction(const G4Run* run){
    G4AnalysisManager* am = G4AnalysisManager::Instance();
    
    am->SetFileName("Data/"+filename);
    am->OpenFile();
}
