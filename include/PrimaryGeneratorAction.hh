//
//  PrimaryGeneratorAction.hh
//  
//
//  Created by Donal on 2020/06/05.
//

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h


#endif /* PrimaryGeneratorAction_h */

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4GenericMessenger.hh"

class G4ParticleGun;
class G4GenericMessenger;
class G4Event;
class G4ParticleDefinition;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    
    virtual void GeneratePrimaries(G4Event*);
    
    void SetEnergy(G4double val) { fEnergy = val; }
    G4double GetEnergy() const { return fEnergy; }
    
    void SetSigmaMomentum(G4double val) { fSigmaMomentum = val; }
    G4double GetSigmaMomentum() const { return fSigmaMomentum; }
    
    void SetSigmaAngle(G4double val) { fSigmaAngle = val; }
    G4double GetSigmaAngle() const { return fSigmaAngle; }
    
    void SetRandomize(G4bool val) { fRandomizePrimary = val; }
    G4bool GetRandomize() const { return fRandomizePrimary; }

    virtual void DefineCommands();
    
private:
    //void DefineCommands();
    
    G4ParticleGun* fParticleGun;
    G4GenericMessenger* fMessenger;
    G4ParticleDefinition* fDeuteron;
    G4double fEnergy;
    G4double fSigmaMomentum;
    G4double fSigmaAngle;
    G4bool fRandomizePrimary;
    G4bool fGunRadius;
    G4GenericMessenger* messenger;
};
