//
// LBNESteppingAction.hh
//

#ifndef LBNESteppingAction_H
#define LBNESteppingAction_H 1
#include <fstream>
#include <iostream>
#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "LBNESteppingActionMessenger.hh"

class G4EventManager;
class LBNEEventAction;
class LBNERunManager;

class LBNESteppingAction : public G4UserSteppingAction
{
  
 public:
  LBNESteppingAction();
  virtual ~LBNESteppingAction();
  
  virtual void UserSteppingAction(const G4Step*);

   void KillNonNuThresholdParticles(const G4Step * theStep);
   void CheckDecay(const G4Step * theStep);

   void CheckInHornEndPlane(const G4Step * theStep, G4int nhorn);

   void CheckInTgtEndPlane(const G4Step * theStep);
   
   void OpenAscii(const char *fname);

private:
   
   LBNERunManager *pRunManager;
   G4EventManager *EvtManager;
   LBNEEventAction *LBNEEvtAct;
//
// This partly "private code" from P. Lebrun, but could be used as template for other studies. 
//  Should not hurt if not activated..
// 
   LBNESteppingActionMessenger *pMessenger;
   std::ofstream fOutStudy;
   
   double fKillTrackingThreshold;
   

   // Study Geantino and absorption length patterns in the target/horn . 
   
   double totalAbsDecayChan; // total absorption probability. 
   double totalAbsHorn1Neck; //At various Z locations.. 
   double totalAbsHorn2Entr; 
   double waterAbsDecayChan; 
   double waterAbsHorn1Neck; 
   double waterAbsHorn2Entr; 
   double alumAbsHorn2Entr; // to check inner conductor horm geometry.
   
   bool goneThroughHorn1Neck;
   bool goneThroughHorn2Entr;
   
   
   void StudyAbsorption(const G4Step*); 
   
public:
   
   void  SetKillTrackingThreshold(double t) {fKillTrackingThreshold = t;} 

};

#endif

