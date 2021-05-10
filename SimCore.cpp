
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"
#include "SteppingVerbose.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UIManager.hh"
#include "G4StepLimiterPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "QGSP_BERT_HP.hh"

int main(int argc, char** argv){
    G4UIExecutive* ui = 0;
    if(argc == 1){
        ui = new G4UIExecutive(argc, argv);
    }

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(12);
#else
    G4VSteppingVerbose::SetInstance(new SteppingVerbose);
    G4RunManager* runManager = new G4RunManager;
#endif
    //Initialize Geometry
    runManager->SetUserInitialization(new DetectorConstruction);

    //Physics List
    //PhysicsList* phys = new PhysicsList;
    QGSP_BERT_HP* phys = new QGSP_BERT_HP();
    phys->RegisterPhysics(new G4StepLimiterPhysics());
    runManager->SetUserInitialization(phys);
    //runManager->SetUserInitialization(new QGSP_BERT_HP());

    //Action Initializer
    runManager->SetUserInitialization(new ActionInitialization());

    //Vis Manager
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if(argc>1){
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command + filename);
    }else{
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;

    return 0;
}
