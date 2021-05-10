//
//  RunAction.hh
//  
//
//  Created by Donal on 2020/06/10.
//

#ifndef RunAction_h
#define RunAction_h


#endif /* RunAction_h */

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
    virtual G4Run* GenerateRun();
    
    void SetFilename(G4String s) { filename = s; };
    void SetEntry(G4int i) { entry = i; };
    
    virtual void DefineCommands();
    
private:
    G4String filename;
    G4double entry;
};
