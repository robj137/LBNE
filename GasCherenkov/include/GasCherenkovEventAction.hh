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
// $Id: GasCherenkovEventAction.hh,v 1.2 2006/06/29 17:53:57 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#ifndef GasCherenkovEventAction_h
#define GasCherenkovEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"


const G4int kPMax = 1000; // maximum number of photons in event

class G4Event;
class GasCherenkovRunAction;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GasCherenkovEventAction : public G4UserEventAction
{
  public:
    GasCherenkovEventAction(GasCherenkovRunAction *);
   ~GasCherenkovEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);

    void ResetArrays();

    void AddHit(G4ThreeVector planePos, G4double globalTime, G4ThreeVector initialPos, G4double wavelength)
    {
     
      if ( fNHits > kPMax ){
        G4cout <<  " *** Error!: Hit array too small!  Fix me!" << G4endl;
        G4cout << " ***       : Keeping array sized at kPMax: " << kPMax << G4endl;
        fNHits = kPMax-1; // to prevent exceeding array size
      }
      fPlaneX[fNHits] = planePos.x()/cm;
      fPlaneY[fNHits] = planePos.y()/cm;
      fPlaneZ[fNHits] = planePos.z()/cm;
      fPlaneT[fNHits] = globalTime/ns;
      fTrackX[fNHits] = initialPos.x()/cm;
      fTrackY[fNHits] = initialPos.y()/cm;
      fTrackZ[fNHits] = initialPos.z()/cm;
      fWavelength[fNHits] = wavelength;
      fNHits++;
    }
    
    void AddPhoton( )
    {
      fNPhotons++;
      G4cout << "fNPhotons = " << fNPhotons << G4endl;
    }

    int *GetNHits() { return &fNHits; }
    int *GetPhotonHits() { return &fNPhotons; }
    double *GetPlaneX() { return fPlaneX; }
    double *GetPlaneY() { return fPlaneY; }
    double *GetPlaneZ() { return fPlaneZ; }
    double *GetPlaneT() { return fPlaneT; }
    double *GetTrackX() { return fTrackX; }
    double *GetTrackY() { return fTrackY; }
    double *GetTrackZ() { return fTrackZ; }
    double *GetPrimaryPositionX() { return &fPrimePosX; }
    double *GetPrimaryPositionY() { return &fPrimePosY; }
    double *GetPrimaryPositionZ() { return &fPrimePosZ; }
    double *GetPrimaryMomentumX() { return &fPrimeMomX; }
    double *GetPrimaryMomentumY() { return &fPrimeMomY; }
    double *GetPrimaryMomentumZ() { return &fPrimeMomZ; }
    double *GetWavelength() { return fWavelength; }

  private:
    GasCherenkovRunAction * theRun;
    G4int fNHits;
    G4int fNPhotons;
    double fPlaneX[kPMax];
    double fPlaneY[kPMax];
    double fPlaneZ[kPMax];
    double fPlaneT[kPMax];
    double fTrackX[kPMax];
    double fTrackY[kPMax];
    double fTrackZ[kPMax];
    double fPrimePosX;
    double fPrimePosY;
    double fPrimePosZ;
    double fPrimeMomX;
    double fPrimeMomY;
    double fPrimeMomZ;
    double fWavelength[kPMax];

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
