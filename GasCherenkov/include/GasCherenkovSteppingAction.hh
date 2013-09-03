#ifndef GasCherenkovSteppingAction_h
#define GasCherenkovSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Track.hh"
#include "globals.hh"


class GasCherenkovSteppingAction:public G4UserSteppingAction{

  public:
    GasCherenkovSteppingAction();
    ~GasCherenkovSteppingAction();

    void UserSteppingAction(const G4Step * theStep);
  
 

    const G4Track *theTrack;
    G4VPhysicalVolume *fPreVolume;
    G4VPhysicalVolume *fPostVolume;
    G4VPhysicalVolume *fDetectorVolume;

    G4int fParticleID;


};

#endif

