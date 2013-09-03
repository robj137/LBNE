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
// $Id: GasCherenkovPrimaryGeneratorAction.cc,v 1.6 2006/06/29 17:54:27 gunter Exp $
// GEANT4 tag $Name: geant4-09-02 $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "GasCherenkovPrimaryGeneratorAction.hh"
#include "GasCherenkovPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "TF1.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GasCherenkovPrimaryGeneratorAction::GasCherenkovPrimaryGeneratorAction()
{
  G4Gun = new G4ParticleGun();
  //create a messenger for this class
  gunMessenger = new GasCherenkovPrimaryGeneratorMessenger(this);
  // Set the angular distribution function. As defined, it's normalized 
  fAngleDist = 
    new TF1("fAngleDist", "(x/pow([0],2))*exp(-0.5*(pow(x/[0],2)))",0, 20);
    //new TF1("fAngleDist", "0*[0]", 0, 20);
  fAngleDist->SetParameter(0,0.02);

  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GasCherenkovPrimaryGeneratorAction::~GasCherenkovPrimaryGeneratorAction()
{
  delete G4Gun;
  delete fAngleDist;
  delete gunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GasCherenkovPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // There is a functional form for the sigma as a function of momentum, so the 
  //double partMom = G4Gun->GetParticleMomentum();
 
  G4double partEne = G4Gun->GetParticleEnergy()/GeV;
  double partMom = sqrt(pow(partEne,2) - pow(0.1057,2));
  
  double sig = 5.78*pow(partMom, -0.684); // power law fit
  
  fAngleDist->SetParameter(0, sig);
  // fAngleDist->SetParameter(0, whatever)
  double phi = 2*3.14159*G4UniformRand();
  
  //   double theta = 0; //** this is now not randomized
  double theta = fAngleDist->GetRandom(-5,5)*deg;  // incident angle is limited to
                                                 // (+-)10 degrees by coincidence detetcion
  aDirection = 
    G4ThreeVector(cos(phi)*sin(theta), sin(phi)*sin(theta), cos(theta));
  //aDirection.setTheta(fAngleDist->GetRandom());
  G4Gun->SetParticleMomentumDirection(aDirection);
  
  // also need to set the position of the initial vertex
  G4double posR = sqrt(G4UniformRand())*5*cm;
  G4double posPhi = 2.0*3.14159*G4UniformRand();

  aPosition = G4ThreeVector(posR*cos(posPhi), posR*sin(posPhi), -40.*cm); //** changing this 
                                                                          // z value to match setup
  G4Gun->SetParticlePosition(aPosition);
  G4Gun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GasCherenkovPrimaryGeneratorAction::SetOptPhotonPolar()
{
 G4double angle = G4UniformRand() * 360.0*deg;
 SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GasCherenkovPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (G4Gun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the GPS is not an opticalphoton" << G4endl;
     return;
   }
     	       
 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = G4Gun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton); 
 G4double modul2       = product*product;

 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product; 
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 G4Gun->SetParticlePolarization(polar);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
