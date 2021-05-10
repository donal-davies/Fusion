
#ifndef DetectorConstruction_h
#define DetectorConstruction_h
#endif /* DetectorConstruction_h */

#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"


#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;
class G4Material;
class G4VSolid;
class G4Box;

class DetectorConstruction : public G4VUserDetectorConstruction {
    
public:
    DetectorConstruction();
    //virtual ~DetectorConstruction();
    
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    
    virtual void SetSampleThickness(G4double val);
    
    void ConstructMaterials();
    
private:
    void DefineCommands();
    
    G4GenericMessenger* messenger;
    G4double sample_thickness;
    
    G4LogicalVolume* world_logic;
    G4VPhysicalVolume* worldPhysical;

    G4LogicalVolume* detector_logic;
    G4VPhysicalVolume* detector_physical;
    
    G4Box* sample_solid;
    G4LogicalVolume* sample_logic;
    G4VPhysicalVolume* sample_physical;
    
};
