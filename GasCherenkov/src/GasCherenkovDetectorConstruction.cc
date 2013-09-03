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
// $Id: GasCherenkovDetectorConstruction.cc,v 1.17 2008/07/17 00:32:34 gum Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
// Editing by Ben Schlitzer in Summer 2013 to match proposed 
// Cherenkov Radiation Muon Detector
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "GasCherenkovDetectorConstruction.hh"
#include "GasCherenkovDetectorMessenger.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4VisAttributes.hh"
#include "G4UnionSolid.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GasCherenkovDetectorConstruction::GasCherenkovDetectorConstruction()
{
  fExpHallX = fExpHallY = 40*cm;
  fExpHallZ = 40*cm;
  fTankX    = 40*cm;
  fTankY    = 40*cm;
  fTankZ    = fExpHallZ;
  
  TankRMin  = 5*cm;      // Inner radius
  TankRMax  = 5.3 *cm;      // Outer radius
  TankDz    = 20.*cm;      // Half length in z
  TankSPhi  = 0.*deg;      // Starting angle in radians
  TankDPhi  = 360.*deg;    // Angle of segment in radians

  fMirrorX  = 2*2.54*cm;         //**2 inches wide
  fMirrorY = 2.82*2.54*cm;
  fMirrorZ  = 0.5*cm;

  fDetectorPlaneX = 15*cm; //maybe change in future to fit our detector
  fDetectorPlaneY = 1*cm;
  fDetectorPlaneZ = 15*cm;
  fDetectorPlanePositionZ = 2*TankDz-1;// lowered from 4*m to fit new detector
  
  fDetectorRmin = 0.0*cm;
  fDetectorRMax = 2.54*cm;
  fDetectorDz   = 1*cm;
  fDetectorSPhi = 0.*deg;
  fDetectorDPhi = 360*deg;

  detectorMessenger = new GasCherenkovDetectorMessenger(this);
  
  detectorMessenger = new GasCherenkovDetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GasCherenkovDetectorConstruction::~GasCherenkovDetectorConstruction()
{
  delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* GasCherenkovDetectorConstruction::Construct()
{

//	------------- Materials -------------

  G4double a, z, density;
  G4int nelements;

// Air
// 
  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* Air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  Air->AddElement(N, 70.*perCent);
  Air->AddElement(O, 30.*perCent);

// Water
// 
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

  G4Material* Water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);


//Carbon
// 
  G4Element* C = new G4Element("Carbon", "C", z=6 , a=12.0*g/mole);


//Iron
//
  G4Element* Fe = new G4Element("Iron", "Fe", z=26 , a=55.845*g/mole);


//Chromium
//
  G4Element* Cr = new G4Element("Chromium", "Cr", z=24 , a=41.996*g/mole);


//Nickel
//
  G4Element* Ni = new G4Element("Nickel", "Ni", z=28 , a=58.693*g/mole);


//Freon
//
  G4Material* Freon = new G4Material("Freon", density = 176.4*mg/cm3, nelements=2);
  Freon->AddElement(H, 4);
  Freon->AddElement(C, 8);


// Argon
// 
  G4Material* ArgonGas = new G4Material("ArgonGas", z=18, a=39.948*g/mole, 
                                        density= 8.82*mg/cm3);

//Aluminum
//
  G4Material* Aluminum = new G4Material("Aluminum",z=13, a=29.9815*g/mole, 
                                        density=2.699*g/cm3);

//Stainless Steel
  G4Material* StainlessSteel = new G4Material("StainlessSteel",density=8.03*g/cm3,
                                               nelements=3);
  StainlessSteel->AddElement(Ni,12.*perCent);
  StainlessSteel->AddElement(Cr,20.*perCent);
  StainlessSteel->AddElement(Fe,68.*perCent);
//
// ------------ Generate & Add Material Properties Table ------------
//
  const G4int nEntries = 3;

  G4double PhotonEnergy[nEntries] =
    { 2.0*eV, 3.0*eV, 4.0*eV};


  // argon
    G4double RefractiveIndex1[nEntries] =
           {1.00139, 1.00139, 1.00139};





  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  myMPT1->AddProperty("RINDEX",       PhotonEnergy, RefractiveIndex1,nEntries);
  //myMPT1->AddProperty("ABSLENGTH",    PhotonEnergy, Absorption1,     nEntries);
  //myMPT1->AddProperty("FASTCOMPONENT",PhotonEnergy, ScintilFast,     nEntries);
  //myMPT1->AddProperty("SLOWCOMPONENT",PhotonEnergy, ScintilSlow,     nEntries);
  
  //myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  //myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
  //myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  //myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  //myMPT1->AddConstProperty("YIELDRATIO",0.8);
  
  Freon->SetMaterialPropertiesTable(myMPT1);

  // Set the Birks Constant for the Water scintillator

  //  Water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

//
//**STP Argon

  G4double RefractiveIndex2[nEntries] =
    { 1.000281, 1.000281, 1.000281}; //*changed third entry from 1.00


  G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);
    ArgonGas->SetMaterialPropertiesTable(myMPT2);

//**STP Air

  G4double RefractiveIndex3[nEntries] =
    { 1.000277, 1.000277, 1.000277};


  G4MaterialPropertiesTable* myMPT3 = new G4MaterialPropertiesTable();
  myMPT3->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex3, nEntries);
    Air->SetMaterialPropertiesTable(myMPT3);


//
//	------------- Volumes --------------

// The experimental Hall
//
  G4Box* fExpHall_box = new G4Box("World",fExpHallX,fExpHallY,fExpHallZ);

  G4LogicalVolume* fExpHall_log
    = new G4LogicalVolume(fExpHall_box,ArgonGas,"World",0,0,0);

  G4VPhysicalVolume* fExpHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),fExpHall_log,"World",0,false,0);

// Vertical Tube
// **Changed tank from Box to Tube**	
  G4Tubs* gasTank_tube = new G4Tubs("Tank",TankRMin,TankRMax,
                                    (TankDz - TankRMax/2),TankSPhi,TankDPhi);
// **changed gasTank_box to gasTank_tube

  G4LogicalVolume* gasTank_log
    = new G4LogicalVolume(gasTank_tube,ArgonGas,"Tank",0,0,0);
  
  G4RotationMatrix* rotation1 = new G4RotationMatrix(); //cylinder rotation
  rotation1 -> rotateX(90*deg);

  G4VPhysicalVolume* gasTank_phys
    = new G4PVPlacement(rotation1,G4ThreeVector(0,(TankDz+TankRMax/2),0),gasTank_log,"Tank",
                        fExpHall_log,false,0);
  
// Horizontal Tube
  G4Tubs* gasTank_tube2 = new G4Tubs("HTube",TankRMin,TankRMax,
				     (TankDz - TankRMax/2),TankSPhi,TankDPhi);
    G4LogicalVolume* gasTank_log2
    = new G4LogicalVolume(gasTank_tube2,ArgonGas,"HTube",0,0,0);
  
    G4VPhysicalVolume* gasTank_phys2
      = new G4PVPlacement(0,G4ThreeVector(0,0,-(TankDz+TankRMax/2)),gasTank_log2,"HTube",
                        fExpHall_log,false,0);
  
 
// The Planar Mirror
//
  G4Box* fMirror_box = new G4Box("pMirror",fMirrorX,fMirrorY,fMirrorZ);

  G4RotationMatrix* rotation = new G4RotationMatrix(); //mirror rotation
  rotation -> rotateX(-45*deg);

  G4LogicalVolume* fpMirror_log = 
    new G4LogicalVolume(fMirror_box,Aluminum,"pMirrorLog",0,0,0);

  // fpMirror_log->SetVisAttributes(DetVisAtt);

  G4VPhysicalVolume* fpMirror_phys =
      new G4PVPlacement(rotation,G4ThreeVector(0,0,0*cm),fpMirror_log,"pMirrorPhys",
			fExpHall_log,false,0);

// The Plane Detector
// Right now, this is just a separate volume, nested inside the Tank, also
// filled with freon.  The stepping action checks for particles that enter this
// volume and records those hits.

// ********** DETECTOR***********
// **Changed from box to cylinder
  G4Tubs *detector_box = new G4Tubs("Detector", 
				   fDetectorRmin,
				   fDetectorRMax,
				   fDetectorDz,
				   fDetectorSPhi,
				   fDetectorDPhi);

  fDetectorLogical = new G4LogicalVolume(detector_box, 
                                     ArgonGas, 
                                     "DetectorLogical",
                                     0,0,0);

  G4RotationMatrix* rotation90x = new G4RotationMatrix(); //mirror rotation
  rotation90x -> rotateX(90*deg);

  fDetectorPhysical = new G4PVPlacement(rotation90x,
					G4ThreeVector(0,
						      (fDetectorPlanePositionZ),0),
                                         fDetectorLogical, "Detector",
                                         fExpHall_log, false, 0);


// Planar Mirror
//
  G4OpticalSurface* OppMirrorSurface = new G4OpticalSurface("pOpMirrorSurface");
  OppMirrorSurface->SetType(dielectric_metal);
  OppMirrorSurface->SetFinish(polished);
  OppMirrorSurface->SetModel(glisur);

  G4LogicalSkinSurface* pMirrorSurface = 
	  new G4LogicalSkinSurface("plogMirrorSurface", fpMirror_log, OppMirrorSurface);

  if(pMirrorSurface->GetLogicalVolume() == fpMirror_log) G4cout << "Equal" << G4endl;
  G4OpticalSurface* popticalSurface = dynamic_cast <G4OpticalSurface*>
        (pMirrorSurface->GetSurface(fpMirror_log)->GetSurfaceProperty());

  if (popticalSurface) popticalSurface->DumpInfo();

  //**Tubes Stainless Steel Surface

  G4OpticalSurface* TubeSurface = new G4OpticalSurface("TubeSurface");
  TubeSurface->SetType(dielectric_metal);
  TubeSurface->SetFinish(polished);
  TubeSurface->SetModel(glisur);

  //** for vertical tube
  G4LogicalSkinSurface* pTubeSurface = 
	  new G4LogicalSkinSurface("plogTubeSurface", gasTank_log, TubeSurface);

  G4OpticalSurface* TubeSurface2 = new G4OpticalSurface("TubeSurface2");
  TubeSurface2->SetType(dielectric_metal);
  TubeSurface2->SetFinish(polished);
  TubeSurface2->SetModel(glisur);


  //** for horizontal tube
  G4LogicalSkinSurface* pTubeSurface2 = 
  	  new G4LogicalSkinSurface("plogTubeSurface2", gasTank_log2, TubeSurface2);

  /*
// Cylindrical "Filter"
//
  G4OpticalSurface* OpcMirrorSurface = new G4OpticalSurface("OpcMirrorSurface");
  OpcMirrorSurface->SetType(dielectric_metal);
  OpcMirrorSurface->SetFinish(polished);
  OpcMirrorSurface->SetModel(glisur);

  G4LogicalSkinSurface* cMirrorSurface = 
	  new G4LogicalSkinSurface("clogMirrorSurface", fcMirror_log, OpcMirrorSurface);

  if(cMirrorSurface->GetLogicalVolume() == fcMirror_log) G4cout << "Equal" << G4endl;
  G4OpticalSurface* copticalSurface = dynamic_cast <G4OpticalSurface*>
        (cMirrorSurface->GetSurface(fcMirror_log)->GetSurfaceProperty());

  if (copticalSurface) copticalSurface->DumpInfo();
  */

// Generate & Add Material Properties Table attached to the optical surfaces
//
  const G4int num = 12;
  G4double Ephoton[num] = {2.0*eV, 2.2*eV, 2.4*eV, 2.6*eV, 2.8*eV,
                           3.0*eV, 3.2*eV, 3.4*eV, 3.6*eV, 3.8*eV,
                           4.0*eV, 4.2*eV};

  //Optical Mirror Surface 
  //  Data from CRC handbook
  G4double Reflectivity[num] = {0.9148, 0.92, 0.9228, 0.9238, 0.9242, 
				0.9241, 0.9243, 0.9245, 0.9246, 0.9247,
				0.9248, 0.9248};

  G4double BadReflectivity[num] = {0.01,0.01,0.01,0.01,0.01,0.01,
				   0.01,0.01,0.01,0.01,0.01,0.01};

  //**Stainless Steel Reflectivity (loose estimate)

  G4double Reflectivity2[num] = {0.9148, 0.92, 0.9228, 0.9238, 0.9242, 
				0.9241, 0.9243, 0.9245, 0.9246, 0.9247,
				0.9248, 0.9248};


  // efficiency for detector = 0 if absorbed
  G4double Efficiency[num] = {0.0, 0.0, 0.0, 0.0, 0.0, 
				0.0, 0.0, 0.0, 0.0, 0.0,
				0.0, 0.0};


  //G4double RefractiveIndex[num] = {1.35, 1.4 };

  // G4double SpecularLobe[num]    = {0.3, 0.3};
  // G4double SpecularSpike[num]   = {0.2, 0.2};
  // G4double Backscatter[num]     = {0.2, 0.2};

  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();
  
  //myST1->AddProperty("RINDEX",                Ephoton, RefractiveIndex, num);
  //myST1->AddProperty("SPECULARLOBECONSTANT",  Ephoton, SpecularLobe,    num);
  //myST1->AddProperty("SPECULARSPIKECONSTANT", Ephoton, SpecularSpike,   num);
  //myST1->AddProperty("BACKSCATTERCONSTANT",   Ephoton, Backscatter,     num);
  G4MaterialPropertiesTable* myBadST1 = new G4MaterialPropertiesTable(); 
  
  //**Stainless Steel Material Properties 
  G4MaterialPropertiesTable* myST2 = new G4MaterialPropertiesTable();



  //OpWaterSurface->SetMaterialPropertiesTable(myST1);

  //OpticalAirSurface

  //G4double Efficiency[num]   = {0.8, 1.0};

  //G4MaterialPropertiesTable *myST1 = new G4MaterialPropertiesTable();

  myST1->AddProperty("REFLECTIVITY", Ephoton, BadReflectivity, num);
  myST1->AddProperty("EFFICIENCY",   Ephoton, Efficiency,   num);
  myBadST1->AddProperty("REFLECTIVITY", Ephoton, BadReflectivity, num);
  myBadST1->AddProperty("EFFICIENCY",   Ephoton, Efficiency,   num);

  myST2->AddProperty("REFLECTIVITY",Ephoton,Reflectivity2,num);

  //  OpMirrorSurface->SetMaterialPropertiesTable(myST1);
  OppMirrorSurface->SetMaterialPropertiesTable(myST1);
  //OpcMirrorSurface->SetMaterialPropertiesTable(myBadST1);

  TubeSurface->SetMaterialPropertiesTable(myST2);
  TubeSurface2->SetMaterialPropertiesTable(myST2);


//---------------------------------------------------------------------------//
// Visualization Attributes
//---------------------------------------------------------------------------// 
   G4VisAttributes *DetVisAtt = new G4VisAttributes(G4Color(0.14, 0.73, 0.14));
   // sort of greenish
   DetVisAtt->SetVisibility(true);
   DetVisAtt->SetForceWireframe(true);
   fDetectorLogical->SetVisAttributes(DetVisAtt);

//always return the physical World
  return fExpHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
