//
//  ActionInitialization.cpp
//  
//
//  Created by Donal on 2020/06/05.
//

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "SteppingVerbose.hh"

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {}

void ActionInitialization::Build() const
{
    //Register custom action managers
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
    SetUserAction(new RunAction());
}

G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
    return new SteppingVerbose();
}
