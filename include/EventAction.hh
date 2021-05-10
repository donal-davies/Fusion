//
//  EventAction.hh
//  
//
//  Created by Donal on 2020/06/09.
//

#ifndef EventAction_h
#define EventAction_h


#endif /* EventAction_h */

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    virtual ~EventAction();
    
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    
private:
    G4int detectorID;
};
