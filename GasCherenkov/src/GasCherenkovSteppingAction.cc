
#include "GasCherenkovSteppingAction.hh"
#include "GasCherenkovEventAction.hh"
#include "GasCherenkovDetectorConstruction.hh"
///     Geant4 package includes
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4OpticalPhoton.hh"


GasCherenkovSteppingAction::GasCherenkovSteppingAction()
{
}

GasCherenkovSteppingAction::~GasCherenkovSteppingAction()
{
}

//---------------------------------------------------------------------------// 

void GasCherenkovSteppingAction::UserSteppingAction(const G4Step *theStep)
{
  fDetectorVolume = 
  ((GasCherenkovDetectorConstruction*)G4RunManager::GetRunManager()->GetUserDetectorConstruction())->GetDetectorPhysicalVolume();
  GasCherenkovEventAction *theEvent =
  (GasCherenkovEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();

  fPreVolume = theStep->GetPreStepPoint()->GetPhysicalVolume();
  fPostVolume = theStep->GetPostStepPoint()->GetPhysicalVolume();
  

  if(fPostVolume == fDetectorVolume){
    if(fPreVolume !=fDetectorVolume){
      if(theStep->GetTrack()->GetDefinition() ==
      G4OpticalPhoton::OpticalPhoton()){
        // then we have just entered the detector plane, so let's record the
        // useful info (the track has the GetVertexPosition, GetGlobalTime,
        // Get Position at the plane
        G4ThreeVector planePosition = theStep->GetPostStepPoint()->GetPosition();
        double globalTime = theStep->GetPostStepPoint()->GetGlobalTime();
        // Get initial position of track
        G4ThreeVector initialPosition = theStep->GetTrack()->GetVertexPosition();
        double wavelength = 
          (197*2*3.14159)/
          (theStep->GetPostStepPoint()->GetTotalEnergy()/eV);
          // because hbar*c = 197MeV*fm = 197 eV*nm
        theEvent->AddHit(planePosition, globalTime, initialPosition, wavelength);
      }
    }
  }

}


