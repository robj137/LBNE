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
// $Id: GasCherenkovEventAction.cc,v 1.3 2006/06/29 17:54:20 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
#include "GasCherenkovEventAction.hh"
#include "GasCherenkovRunAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
GasCherenkovEventAction::GasCherenkovEventAction(GasCherenkovRunAction *theRA): theRun(theRA)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
GasCherenkovEventAction::~GasCherenkovEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void GasCherenkovEventAction::BeginOfEventAction(const G4Event* anEvent)
{
  fNHits = 0;
  fNPhotons = 0;
  ResetArrays();
  fPrimePosX= anEvent->GetPrimaryVertex()->GetX0()/cm;
  fPrimePosY= anEvent->GetPrimaryVertex()->GetY0()/cm;
  fPrimePosZ= anEvent->GetPrimaryVertex()->GetZ0()/cm;
  fPrimeMomX = anEvent->GetPrimaryVertex()->GetPrimary()->GetPx();
  fPrimeMomY = anEvent->GetPrimaryVertex()->GetPrimary()->GetPy();
  fPrimeMomZ = anEvent->GetPrimaryVertex()->GetPrimary()->GetPz();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GasCherenkovEventAction::ResetArrays()
{
  for(G4int i = 0; i<kPMax; i++){
    fPlaneX[i] = 0;
    fPlaneY[i] = 0;
    fPlaneZ[i] = 0;
    fPlaneT[i] = 0;
    fTrackX[i] = 0;
    fTrackY[i] = 0;
    fTrackZ[i] = 0;
    fWavelength[i] = 0;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void GasCherenkovEventAction::EndOfEventAction(const G4Event*)
{
  if(fNHits >= 0)
    {
    theRun->GetTree()->Fill();
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

