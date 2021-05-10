#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//#include "HadronElasticPhysicsHP.hh"

#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"

#include "G4IonPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysicsXS.hh"
#include "G4IonPhysicsPHP.hh"
#include "G4IonINCLXXPhysics.hh"

#include "G4StoppingPhysics.hh"

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4Neutron.hh"
#include "G4ProcessManager.hh"
#include "G4HadronicInteraction.hh"


//This has been deprecated in favour of a pre-built physics list. Kept for posterity



PhysicsList::PhysicsList()
    :G4VModularPhysicsList(),
    fHadronElastic(nullptr), fHadronInelastic(nullptr),
    fIonElastic(nullptr), fIonInelastic(nullptr),
    fGammaNuclear(nullptr), fElectromagnetic(nullptr),
    fDecay(nullptr), fRadioactiveDecay(nullptr)
{
    G4int verb = 0;
    SetVerboseLevel(verb);


    // Hadron Elastic scattering
    fHadronElastic = new G4HadronElasticPhysics(verb);
    RegisterPhysics(fHadronElastic);

    // Hadron Inelastic Physics
    fHadronInelastic = new G4HadronInelasticQBBC(verb);
    RegisterPhysics(fHadronInelastic);

    // Ion Elastic Physics
    fIonElastic = new G4IonElasticPhysics(verb);
    RegisterPhysics(fIonElastic);

    // Ion Inelastic Physics
    fIonInelastic = new G4IonPhysicsXS(verb);
    RegisterPhysics(fIonInelastic);

    // EM physics
    fElectromagnetic = new G4EmStandardPhysics();
    RegisterPhysics(fElectromagnetic);

    // Decay
    fDecay = new G4DecayPhysics();
    RegisterPhysics(fDecay);
}

PhysicsList::~PhysicsList()
{ }

void PhysicsList::ConstructProcess()
{
    // Transportation first
    AddTransportation();

    // Physics constructors
    fIonInelastic->ConstructProcess();
    fIonElastic->ConstructProcess();
    fHadronElastic->ConstructProcess();
    fHadronInelastic->ConstructProcess();    
    fElectromagnetic->ConstructProcess();
    fDecay->ConstructProcess();
}

//In theory, this controls how far particles can move in a medium. In practice it changed absolutely nothing. I don't know.
void PhysicsList::SetCuts()
{
    SetCutValue(0.5 * km, "proton");
    SetCutValue(0.5 * mm, "e-");
    SetCutValue(0.5 * mm, "e+");
    SetCutValue(0.5 * mm, "gamma");
}
