//
//  PrimaryGeneratorAction.cpp
//  
//
//  Created by Donal on 2020/06/09.
//

#include <stdio.h>

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0), fMessenger(0),
    fDeuteron(0),
    fEnergy(1 * MeV),
    fSigmaMomentum(0.0),
    fSigmaAngle(0. * deg),
    fRandomizePrimary(false),
    fGunRadius(0.4 * cm),
    messenger(0)
{
    G4int n_particle = 1; //Number of particles fired at once
    fParticleGun = new G4ParticleGun(n_particle); //Base class for primary particle generation
    
    //Register deuteron particle for the particle gun
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    fDeuteron = particleTable->FindParticle(particleName="deuteron");
    
    //Set initial position and particle definition
    fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
    fParticleGun->SetParticleDefinition(fDeuteron);

    DefineCommands();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){
    delete fParticleGun;
    delete fMessenger;
}

/*
    Produce primary particles on event start
*/
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event){
    G4ParticleDefinition* particle = fParticleGun->GetParticleDefinition(); //Load particle definition
    
    //Set initial energy
    G4double Ekin = GetEnergy();
    fParticleGun->SetParticleEnergy(Ekin);
    
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0,0));
    
    //Set initial emission angle
    G4double angle = (G4UniformRand() * 360 * deg);
    
    //Randomize initial starting position at fixed radius from the starting point
    fParticleGun->SetParticlePosition(G4ThreeVector(0.0, fGunRadius*std::cos(angle), fGunRadius * std::sin(angle)));
    fParticleGun->GeneratePrimaryVertex(event);
}

/*
    Allow runtime control of primary particle energies
*/
void PrimaryGeneratorAction::DefineCommands() {
    messenger = new G4GenericMessenger(this, "/generator/", "Generator control");

    G4GenericMessenger::Command& thicknessCommand = messenger->DeclareMethodWithUnit("particleEnergy", "MeV", &PrimaryGeneratorAction::SetEnergy, "Set the energy of outgoing deuterons.");

    thicknessCommand.SetParameterName("energy", true);
    thicknessCommand.SetRange("energy>=0.01");
    thicknessCommand.SetDefaultValue("0.1");
}
