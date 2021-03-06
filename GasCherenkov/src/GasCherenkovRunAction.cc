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
// $Id: GasCherenkovRunAction.cc,v 1.10 2006/06/29 17:54:31 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Make this appear first!
#include "G4Timer.hh"

#include "GasCherenkovRunAction.hh"
#include "GasCherenkovRunMessenger.hh"
#include "GasCherenkovEventAction.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GasCherenkovRunAction::GasCherenkovRunAction()
{
  //create a messenger for this class
  fFileName = "GasCherenkov.root";
  runMessenger = new GasCherenkovRunMessenger(this);
  
  G4cout << "The Name of the file is actually " << fFileName << G4endl;

  timer = new G4Timer;
  fFile = new TFile();
  fTree = new TTree();

  
  // create a messenger for the index of refraction
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GasCherenkovRunAction::~GasCherenkovRunAction()
{
  delete timer;
  delete runMessenger;
  //don't delete the tree! closing the file does that. I know it's stupid.
  //delete fTree;
  delete fFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GasCherenkovRunAction::BeginOfRunAction(const G4Run* aRun)
{
  TFile *tempFile = new TFile(fFileName.c_str(), "RECREATE");
  fFile = tempFile;
  InitializeTree();
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GasCherenkovRunAction::EndOfRunAction(const G4Run* aRun)
{   
  timer->Stop();
  G4cout << "Number of events: " << aRun->GetNumberOfEvent() 
         << G4endl;
  G4cout << "Timer Info: " << *timer << G4endl;
  fFile->Write();
  fFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//---------------------------------------------------------------------------// 
void GasCherenkovRunAction::InitializeTree()
{
  
  GasCherenkovEventAction *theEvent =
  (GasCherenkovEventAction*)G4RunManager::GetRunManager()->GetUserEventAction();

  TTree *tempTree = new TTree("fTree", "");
  tempTree->Branch("fNHits", theEvent->GetNHits(), "fNHits/I");
  tempTree->Branch("fNPhotons",theEvent->GetPhotonHits(),"fNPhotons/I");
  tempTree->Branch("fPlaneX_cm", theEvent->GetPlaneX(), "fPlaneX[fNHits]/D");
  tempTree->Branch("fPlaneY_cm", theEvent->GetPlaneY(), "fPlaneY[fNHits]/D");
  tempTree->Branch("fPlaneZ_cm", theEvent->GetPlaneZ(), "fPlaneZ[fNHits]/D");
  tempTree->Branch("fPlaneT_ns", theEvent->GetPlaneT(), "fPlaneT[fNHits]/D");
  tempTree->Branch("fTrackX_cm", theEvent->GetTrackX(), "fTrackX[fNHits]/D");
  tempTree->Branch("fTrackY_cm", theEvent->GetTrackY(), "fTrackY[fNHits]/D");
  tempTree->Branch("fTrackZ_cm", theEvent->GetTrackZ(), "fTrackZ[fNHits]/D");
  tempTree->Branch("fPrimePosX_cm", theEvent->GetPrimaryPositionX(), "fPrimePosX_cm/D");
  tempTree->Branch("fPrimePosY_cm", theEvent->GetPrimaryPositionY(), "fPrimePosY_cm/D");
  tempTree->Branch("fPrimePosZ_cm", theEvent->GetPrimaryPositionZ(), "fPrimePosZ_cm/D");
  tempTree->Branch("fPrimeMomX", theEvent->GetPrimaryMomentumX(), "fPrimeMomX/D");
  tempTree->Branch("fPrimeMomY", theEvent->GetPrimaryMomentumY(), "fPrimeMomY/D");
  tempTree->Branch("fPrimeMomZ", theEvent->GetPrimaryMomentumZ(), "fPrimeMomZ/D");
  tempTree->Branch("fWavelength_nm", theEvent->GetWavelength(), "fWavelength_nm[fNHits]/D");
  
  fTree = tempTree;

}
