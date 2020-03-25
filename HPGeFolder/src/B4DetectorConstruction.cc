//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4SubtractionSolid.hh"
#include "G4Transform3D.hh"
#include "G4ThreeVector.hh"
#include "B4DetectorConstruction.hh"
#include "G4RotationMatrix.hh"

#include "G4Tubs.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fAbsorberPV(nullptr),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  new G4Material("Ge", z=32., a= 72.64*g/mole, density= 5.323*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Cobalt
  new G4Material("Co", z=27, a=59.93*g/mole, density= 8.86*g/cm3);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  G4int nofLayers = 1;
  G4double innerRadius = 0.*cm;
  G4double outerRadius = 60.9/2*cm;
  G4double hz = 62/2.*cm;
  G4double startAngle = 0.*deg;
  G4double spanningAngle = 360.*deg;  

  //Detector hole  
  G4double holeInnerRadius = 0.*cm;
  G4double holeOuterRadius = 9.3/2*cm;
  G4double holeHz = 50.375/2.*cm;

  //Marinelli
  G4double marinelliOuterRadius = 62/2.*cm;
  G4double marinelliHz = 10/2.*cm;
  
  // Get materials
  G4Material* defaultMaterial = G4Material::GetMaterial("Ge");
  G4Material* sampleMaterial = G4Material::GetMaterial("Galactic");
  auto worldSizeXY = 10. * outerRadius;
  auto worldSizeZ = 10.* hz *2.;
   
  //     
  // World
  //
  auto worldS 
    = new G4Box("World",           // its name
                 worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size
                         
  auto worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 defaultMaterial,  // its material
                 "World");         // its name
                                   
  auto worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
  
  
  //                               
  // Absorber
  //
  auto AbsorberS 
    = new G4Tubs("Absorber",
                 innerRadius,
                 outerRadius,
                 hz,
                 startAngle,
                 spanningAngle);  
    
  G4Tubs* AbsorberHole
    = new G4Tubs("Hole",
                 holeInnerRadius,
                 holeOuterRadius,
                 holeHz,
                 startAngle,
                 spanningAngle);
                         
  G4SubtractionSolid * AbsorberTube
   = new G4SubtractionSolid("Absorber",
                            AbsorberS,
                            AbsorberHole,
                            0,
                            G4ThreeVector(0, 0, -1*hz));

  G4LogicalVolume* AbsorberLV
    = new G4LogicalVolume(AbsorberTube, defaultMaterial, "Absorber");

  auto fAbsorberPV                                    
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(), // its position
                 AbsorberLV,       // its logical volume                         
                 "Abso",           // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 fCheckOverlaps);  // checking overlaps 
    
    
  //
  // Marinelli
  //
  G4Tubs* trackerTube_mar
    = new G4Tubs("Marinelli",
                 innerRadius,
                 marinelliOuterRadius,
                 marinelliHz,
                 startAngle,
                 spanningAngle);

  G4LogicalVolume* MarinelliLV
    = new G4LogicalVolume(trackerTube_mar, sampleMaterial, "Marinelli");

  G4RotationMatrix rotm_mar = G4RotationMatrix();
  rotm_mar.rotateY(00*deg);
  rotm_mar.rotateX(00*deg);
  G4ThreeVector position_mar = G4ThreeVector(0, 0, 1*hz+marinelliHz+0.01);
  G4Transform3D transform_mar = G4Transform3D(rotm_mar, position_mar);

  new G4PVPlacement(
                 transform_mar,        // rotation, position
                 MarinelliLV,	   // its logical volume
                 "Marinelli",        // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,
                 fCheckOverlaps);


  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::GetInvisible());

  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  simpleBoxVisAtt->SetVisibility(true);
  AbsorberLV->SetVisAttributes(simpleBoxVisAtt);

  G4VisAttributes* simpleBoxVisAttMar= new G4VisAttributes(G4Colour(2.0,1.0,0.0));
  simpleBoxVisAttMar->SetVisibility(true);
  MarinelliLV ->SetVisAttributes(simpleBoxVisAttMar);
  //
  // Always return the physical World
  //
  return worldPV;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

