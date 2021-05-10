//
//  ActionInitialization.h
//  
//
//  Created by Donal on 2020/06/05.
//

#ifndef ActionInitialization_hh
#define ActionInitialization_hh 1


#endif

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization();
    virtual ~ActionInitialization();
    
    virtual void BuildForMaster() const;
    virtual void Build() const;

    virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};
