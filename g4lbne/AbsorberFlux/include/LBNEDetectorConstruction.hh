// LBNEDetectorConstruction.hh
//------------------------------------------------------------

#ifndef LBNEDetectorConstruction_H
#define LBNEDetectorConstruction_H 1

#include <vector>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "LBNEDetectorMessenger.hh"

class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VisAttributes;

class LBNEDataInput;
class LBNEMagneticField;
class LBNEMagneticFieldIC;
class LBNEMagneticFieldOC;

typedef std::vector<G4double> vdouble_t; 
typedef std::vector<G4int> vint_t;
typedef std::vector<LBNEMagneticField*> BFieldVec;
typedef std::vector<LBNEMagneticFieldIC*> ICBFieldVec;
typedef std::vector<LBNEMagneticFieldOC*> OCBFieldVec;

class LBNEDetectorConstruction : public G4VUserDetectorConstruction
{
public:
   
   LBNEDetectorConstruction();
   ~LBNEDetectorConstruction();
   
   G4VPhysicalVolume* Construct();
   
   G4LogicalVolume*  GetLogicalVolume(G4String LVname);
   //void SetTargetZ0(G4double val);
   //void SetHornCurrent(G4double val);

   void CheckOverlaps();
     
   void UpdateGeometry();

   G4VPhysicalVolume* GetPhysicalVolume(G4String PVname);
   G4Material* GetMaterial(G4int matcode);

   G4LogicalVolume* GetMuonDetectorLogical(){ return fMuonDetectorLogical; }
private:
   
   
   LBNEDataInput* LBNEData;
   //LBNEMagneticField* lbneMagField;
   //LBNEMagneticFieldIC* lbneMagFieldIC;
   //LBNEMagneticFieldOC* lbneMagFieldOC;

   BFieldVec   fHornBFieldVec;
   ICBFieldVec fHornICBFieldVec;
   OCBFieldVec fHornOCBFieldVec;

   void PrintDetectorGeometry();
   void PrintDetectorGeometry(const G4String &desc, 
			      const G4String &name);
   void GetWorldTransformation(G4VPhysicalVolume *physvol,
			       G4RotationMatrix &WorldRotation,
			       G4ThreeVector    &WorldTranslation);
   void PrintSolidDescription(const G4VSolid *solidvol,
			      const G4LogicalVolume *logvol,
			      G4RotationMatrix &WorldRotation,
			      G4ThreeVector    &WorldTranslation);

//
//LBNE stuff
   void ConstructLBNEBaffle();
   void ConstructLBNEDecayPipe();
   void ConstructLBNEHadronAbsorber();
   void ConstructLBNEShielding();
   void LBNEDetermineTargetHallShieldingClosestApproach(G4int ii);
   G4double fTgtHallShield_closest_yplus;
   G4double fTgtHallShield_closest_yminus;
   G4double fTgtHallShield_closest_xplus;
   G4double fTgtHallShield_closest_xminus;

   void ConstructLBNETargetHall();
   void ConstructLBNETarget();

   void ConstructLBNEHorns();
   G4double fTrackingPlane_halfwidth;
   G4double fTrackingPlane_halfheight;
   G4double fTrackingPlane_X0;
   G4double fTrackingPlane_Y0;
   void ConstructLBNEHorn(G4int nhorn, G4int nparts, G4int jstart);
   G4double LBNEphornRgivenZ(G4double a, G4double b, G4double c, G4double z);
//
//


//
//Specifically Exact Numi Target
//This automatically constructs the NUMI baffle and budal monitor
   void ConstructNUMITarget(); //budal mon is constructed in this function
   void ConstructNUMIBaffle();
//
//

   ///use for testing gometry stuff
   void ConstructTesting();
  



 
//
   /*
   void ConstructTargetHall();
   void ConstructTarget();
   void ConstructBaffle();
   void ConstructDecayPipe();
   void ConstructHadronAbsorber();  
   void ConstructHorns();  
   void ConstructHorn1(G4ThreeVector pos, G4RotationMatrix rot);
   void ConstructHorn2(G4ThreeVector pos, G4RotationMatrix rot);
   void ConstructSecMonitors();
   */
   void DefineMaterials();
   G4int GetMaterialCode(const G4String &matName);
   G4Material* GetMaterial(G4String matName);
   G4VisAttributes* GetMaterialVisAttrib(G4int matCode);
   G4VisAttributes* GetMaterialVisAttrib(G4String matName);
   void DestroyMaterials();
   

   // Messenger
   LBNEDetectorMessenger *detectorMessenger;

   /*


   G4double phornRgivenZ(G4double a, G4double b, G4double c, G4double z);
   G4double PHorn2ICRin(G4double z);
   G4double PHorn2ICRout(G4double z);
   G4double PHorn2OCRin(G4double z);
   G4double PHorn2OCRout(G4double z);
   G4double PHorn1ICRin(G4double z);
   G4double PHorn1ICRout(G4double z);
   G4double PHorn1OCRin(G4double z);
   G4double PHorn1OCRout(G4double z);
   */
   
   // Materials
   G4Material* Vacuum;
   G4Material* DecayPipeVacuum;
   G4Material* NumiDecayPipeHelium;
   G4Material* Air;
   G4Material* Water;
   G4Material* He;
   G4Material* Be;
   G4Material* C;
   G4Material* Al;
   G4Material* Ar;
   G4Material* Pb;
   G4Material* Fe;
   G4Material* CT852;
   G4Material* Concrete;
   G4Material* Shotcrete;
   G4Material* Rebar_Concrete;
   G4Material* Target;
   G4Material* NumiTargetHelium;
   G4Material* DolomiteRock;
   G4Material* DoloStone;
   G4Material* MaqShale;
   G4Material* Chert;
   G4Material* Pyrite;
   G4Material* MaqSiltstone;
   G4Material* var_Al;
   G4Material* var_Stl;
   G4Material* Slab_Stl;
   G4Material* Blu_Stl;
   G4Material* n1018_Stl;
   G4Material* A500_Stl;
   G4Material* M1018_Stl;
   G4Material* Alumina;
   G4Material* HeGas;
   G4Material* Drywall;
   G4Material* Paraffin;
   G4Material* DefaultMaterial;



  // Logical volumes
  //
  G4LogicalVolume* ROCK_log;
  G4LogicalVolume* TRGT_lv;
  // G4LogicalVolume* lvTUNE;
  G4LogicalVolume* BLK_log[100]; 
  G4LogicalVolume* CShld_log[16];
  G4LogicalVolume* TGAR_log;
  G4LogicalVolume* Horn_PM_lv[8];
  G4LogicalVolume* LVCPipe[20];
  G4LogicalVolume* LVCPipeW[20];
  G4LogicalVolume* HadrBox_log;
  G4LogicalVolume* ShldBox_log;
  G4LogicalVolume* fMuonDetectorLogical;
  
  // Physical volumes
  //
  G4VPhysicalVolume* ROCK;
  G4VPhysicalVolume* pvTUNE;
  G4VPhysicalVolume* TGAR;
  G4VPhysicalVolume* TRGT;
  G4VPhysicalVolume* PHORN[8];
  G4VPhysicalVolume* PVCPipe[20];
  G4VPhysicalVolume* CNT[20];
  G4VPhysicalVolume* HadrBox;
  G4VPhysicalVolume* ShldBox;
 
  G4LogicalVolume* fConcShld; 
  G4LogicalVolume* fAHTop;
  G4LogicalVolume* fAHBack; 
  G4LogicalVolume* fMuonAlk; 

  //Solids
  //
  G4VSolid* BLK_solid[100];
  G4VSolid* CShld_solid[16];
  G4VSolid* Horn_PM[8];
};

#endif

