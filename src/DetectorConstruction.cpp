//
//  DetectorConstruction.cpp
//  
//
//  Created by Donal on 2020/06/05.
//

#include "DetectorConstruction.hh"
#include "SystemSD.hh"

#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), messenger(0),
sample_thickness(1.0*mm),
world_logic(0), worldPhysical(0),
sample_solid(0), sample_logic(0), sample_physical(0),
detector_physical(0){
    DefineCommands();
}

/*
    Define geometry and visualization
*/
G4VPhysicalVolume* DetectorConstruction::Construct()
{
    //Load registered materials
    ConstructMaterials();
    G4Material* air = G4Material::GetMaterial("G4_Galactic");
    G4Material* tritium = G4Material::GetMaterial("Doped Zirconium");
    G4bool checkOverlaps = true;
    
    //Create world container volume
    G4VSolid* world = new G4Box("WorldSolid", 0.5*m, 0.5*m, 0.5*m);
    world_logic = new G4LogicalVolume(world, air, "WorldLogic");
    worldPhysical = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), world_logic, "WorldPhysical", 0, false, 0, checkOverlaps);
    
    //Create target volume
    sample_solid = new G4Box("SampleSolid", 1.0*mm, 2.5*cm, 2.5 * cm);
    sample_logic = new G4LogicalVolume(sample_solid, tritium, "SampleLogic");
    sample_physical = new G4PVPlacement(0, G4ThreeVector(5*cm,0.*cm,0.*cm), sample_logic, "SamplePhysical", world_logic, false, 0 , checkOverlaps);
    
    //Visualization
    
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    visAttributes->SetVisibility(false);
    world_logic->SetVisAttributes(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0.0,0.4,0.9));
    visAttributes->SetVisibility(true);
    sample_logic->SetVisAttributes(visAttributes);
    
    return worldPhysical;
}

/*
    Denotes a Sensitive Detector volume for data collection
*/
void DetectorConstruction::ConstructSDandField(){
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String SDname;
    
    G4VSensitiveDetector* detector = new SystemSD(SDname="/detector");
    SDman->AddNewDetector(detector);
    sample_logic->SetSensitiveDetector(detector);
}

/*
    Register materials for use in volumes
*/
void DetectorConstruction::ConstructMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    
    //Load pre-constructed materials and elements
    nistManager->FindOrBuildElement("Zr"); 
    nistManager->FindOrBuildMaterial("G4_Galactic");

    //Define Tritium isotope for use in the target material
    G4Element* hydrogen = new G4Element("Tritium", "H3", 1);
    //G4Isotope* tritium = new G4Isotope("Tritium", 1, 3, 3.016049 * g / mole);
    G4Isotope* tritium = new G4Isotope("Tritium", 1, 3, 6.032099 * g / mole);
    hydrogen->AddIsotope(tritium, 1.0);

    //Create Tritium doped Zirconium target
    G4Element* zirconium = G4Element::GetElement("Zr");
    G4Material* zirconTrit = new G4Material("Doped Zirconium", 6.49 * g / cm3, 2);
    zirconTrit->AddElement(zirconium, 0.8);
    zirconTrit->AddElement(hydrogen, 0.2);

    
    G4cout << G4endl << "The defined materials are: " << G4endl << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

/*
    Dynamic rescaling of target volume thickness
*/
void DetectorConstruction::SetSampleThickness(G4double val){
    if(!sample_physical){
        G4cerr << "Sample has not yet been constructed." << G4endl;
        return;
    }
    
    sample_thickness = val;
    
    sample_physical->SetTranslation(G4ThreeVector(sample_thickness / 2.0,0.,0.));
    
    G4RunManager::GetRunManager()->GeometryHasBeenModified(); //Flag to visualizer and physics engine that geometry must be reloaded
}

void DetectorConstruction::DefineCommands(){
    //No commands defined here anymore
}
