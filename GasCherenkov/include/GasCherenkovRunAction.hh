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
// $Id: GasCherenkovRunAction.hh,v 1.9 2006/06/29 17:54:10 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef GasCherenkovRunAction_h
#define GasCherenkovRunAction_h 1

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"


#include "globals.hh"
#include "G4UserRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;
class GasCherenkovRunMessenger;

class GasCherenkovRunAction : public G4UserRunAction
{
  public:
    GasCherenkovRunAction();
   ~GasCherenkovRunAction();

  public:
    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);
    void InitializeTree();
    void SetFileName(G4String aName) { 
      fFileName = aName; 
      G4cout << "Setting file name to " << fFileName << G4endl;
    }

    TTree *GetTree() { return fTree; }
    TFile *GetFile() { return fFile; }

  private:
    G4Timer* timer;
    TFile *  fFile;
    TTree *  fTree;
    G4String fFileName;
    GasCherenkovRunMessenger* runMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*GasCherenkovRunAction_h*/
