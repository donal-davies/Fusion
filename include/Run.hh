//
//  Run.hh
//  
//
//  Created by Donal on 2020/06/10.
//

#ifndef Run_h
#define Run_h


#endif /* Run_h */

#include "G4Run.hh"

class G4Event;

class Run : public G4Run {
    
public:
    Run();
    virtual ~Run() {};
    
    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);
    
    G4double GetNeutronFlux() const { return neutronFlux; };
    G4double GetMinTime() const { return minTime; };
    G4double GetMaxTime() const { return maxTime; };
    const std::map<G4double, G4int>* GetEnergy() const { return &energy; };
    
private:
    G4double neutronFlux;
    G4int detectorID;
    G4double minTime;
    G4double maxTime;
    std::map<G4double, G4int> energy;
};
