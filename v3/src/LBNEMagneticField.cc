//----------------------------------------------------------------------
//LBNEMagneticField 
// $Id
//----------------------------------------------------------------------

#include "LBNEMagneticField.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ios.hh"
#include "G4TransportationManager.hh"
#include "LBNEVolumePlacements.hh"
#include "LBNESurveyor.hh"

//magnetic field between conductors ====================================================

LBNEMagneticFieldHorn::LBNEMagneticFieldHorn(bool isOne) : 
amHorn1(isOne),
fHornCurrent(0.),
coordinateSet(false),  
fShift(2, 0.),
fShiftSlope(2,0.),
fZShiftDrawingCoordinate(-1.0e13),
fZShiftUpstrWorldToLocal(-1.0e13),
fEffectiveLength(0.),
fHornNeckOuterRadius(-1.0e13),
fHornNeckInnerRadius(-1.0e13),
fOuterRadius(1.0e9),
fOuterRadiusEff(1.0e9),
fSkinDepth(4.1*mm)
{
 // 
 // We rely on the Volume Placement utility and the surveyor data to compute the coordinate transfers. 
 // Two distinct ones:
 //
 //  (i) Going from G4 World to the local coordinate system.  This is done in two steps: first a Z shift, fixed.
 //         Key variable: fZShiftUpstrWorldToLocal
 // second, a linearized rotation due misalignement, in both X and Y. 
 //
 //  (ii) A Z translation to go from G4 World the 8875.112 MD 363xxx drawing coordinate system, such that 
 //      we can used the exact parabolic equations (Outer radius one)
 //    fZShiftDrawingCoordinate 
 //
 // This strategy has the drawback of the danger of making mistakes in the code below, but has 
 // has the advantage of less coordinate transforms. (inverse one done in the G4 Propagation. )
 // It is assumed here that the misalignment are small, i.e., cos^2(tilt) ~ 0.  

  const LBNEVolumePlacements *aPlacementHandler = LBNEVolumePlacements::Instance();
// Radial equation interface.  Take the outer equations..
  
  fEqnIndicesInner.clear();
  fEqnIndicesOuter.clear();
  fZDCBegin.clear();
  fZDCEnd.clear();
  if(amHorn1) { // Use the Placement data to get the relevant Z coordinate to compute the distance to the inner or outer conductor.  
     const double zCDNeckStart = aPlacementHandler->GetHorn1NeckZPosition() - aPlacementHandler->GetHorn1NeckLength()/2.;
     const double zCDNeckEnd = aPlacementHandler->GetHorn1NeckZPosition() - aPlacementHandler->GetHorn1NeckLength()/2.;
     fZDCBegin.push_back(0.); fZDCEnd.push_back(zCDNeckStart); fEqnIndicesInner.push_back(0); fEqnIndicesOuter.push_back(5);
     fZDCBegin.push_back(zCDNeckStart); fZDCEnd.push_back(zCDNeckEnd);
     fEqnIndicesInner.push_back(99); fEqnIndicesOuter.push_back(99); // No equations, use the radius
     fHornNeckOuterRadius = aPlacementHandler->GetHorn1NeckOuterRadius(); 
     fHornNeckInnerRadius = aPlacementHandler->GetHorn1NeckInnerRadius(); 
     const double zEndNR = aPlacementHandler->GetHorn1ZDEndNeckRegion();
     fZDCBegin.push_back(zCDNeckEnd); fZDCEnd.push_back(zEndNR); 
     fEqnIndicesInner.push_back(3); fEqnIndicesOuter.push_back(7);
     const double zEnd = aPlacementHandler->GetHorn1ZEndIC();
     fZDCBegin.push_back(zEndNR); fZDCEnd.push_back(zEnd);
     fEqnIndicesInner.push_back(4); fEqnIndicesOuter.push_back(7);
     fEffectiveLength = aPlacementHandler->GetHorn1EffectiveLength();
     fOuterRadius = aPlacementHandler->GetHorn1OuterTubeOuterRad();
  } else {
     const LBNEVolumePlacementData *plDat = aPlacementHandler->Find("Bfield", 
                            "Horn2TopLevel", "LBNEMagneticFieldHorn::LBNEMagneticFieldHorn");
     fEffectiveLength = plDat->fParams[2];
     const double z1 = 	aPlacementHandler->GetHorn2ZEqnChange(0);	    
     fZDCBegin.push_back(0.); fZDCEnd.push_back(z1); 
     fEqnIndicesInner.push_back(6); fEqnIndicesOuter.push_back(10); //IO trasnsition, Part 1
      
     const double z2 = 	aPlacementHandler->GetHorn2ZEqnChange(1);	    
     fZDCBegin.push_back(z1); fZDCEnd.push_back(z2); 
     fEqnIndicesInner.push_back(6);  fEqnIndicesOuter.push_back(0); // Getting to the neck region

     const double z3 = 	aPlacementHandler->GetHorn2ZEqnChange(2);	    
     fZDCBegin.push_back(z2); fZDCEnd.push_back(z3); 
     fEqnIndicesInner.push_back(6);  fEqnIndicesOuter.push_back(1); // Just before the neck

     const double z4 = 	aPlacementHandler->GetHorn2ZEqnChange(3);	    
     fZDCBegin.push_back(z3); fZDCEnd.push_back(z4);     
     fEqnIndicesInner.push_back(99); fEqnIndicesOuter.push_back(99); //The neck, fixe radius
     fHornNeckOuterRadius = aPlacementHandler->GetHorn2NeckOuterRadius();
     fHornNeckInnerRadius = aPlacementHandler->GetHorn2NeckInnerRadius();

     const double z5 = 	aPlacementHandler->GetHorn2ZEqnChange(4);	    
     fZDCBegin.push_back(z4); fZDCEnd.push_back(z5); 
     fEqnIndicesInner.push_back(7);  fEqnIndicesOuter.push_back(3); // Just after the neck

     const double z6 = 	aPlacementHandler->GetHorn2ZEqnChange(5);	    
     fZDCBegin.push_back(z5); fZDCEnd.push_back(z6); 
     fEqnIndicesInner.push_back(7);  fEqnIndicesOuter.push_back(3); // moving along positive Z 

      const double z7 =  aPlacementHandler->GetHorn2ZEqnChange(6);	    
     fZDCBegin.push_back(z6); fZDCEnd.push_back(z7); 
     fEqnIndicesInner.push_back(8);  fEqnIndicesOuter.push_back(5);

      const double z8 =  aPlacementHandler->GetHorn2ZEqnChange(7);	    
     fZDCBegin.push_back(z7); fZDCEnd.push_back(z8); 
     fEqnIndicesInner.push_back(9);  fEqnIndicesOuter.push_back(5);
     
     fOuterRadius = aPlacementHandler->GetHorn2OuterTubeOuterRad();

  }
  fOuterRadiusEff = fOuterRadius - 2.0*fSkinDepth; // skin depth at 0.43 kHz 
  // Z coordinate change not yet initialize, done at the first track.
  std::cerr << " Table of Z position and equations for ";
  if (amHorn1) std::cerr << " Horn1 " ;
  else  std::cerr << " Horn2 " ;
  std::cerr << std::endl <<  " Z-Start      Z-End      Innner Eqn    Outer Eqn rIC thick" << std::endl;
  for(size_t k=0; k!= fZDCBegin.size(); k++) {
    std::cerr << " " << fZDCBegin[k] << " " << fZDCEnd[k] 
              << " " << fEqnIndicesInner[k] << " " << fEqnIndicesOuter[k];
    const double zMid = 0.5 *( fZDCBegin[k] + fZDCEnd[k]);     
    const double rOut = (amHorn1)  ? aPlacementHandler->GetConductorRadiusHorn1(zMid, fEqnIndicesOuter[k]) :
    	      aPlacementHandler->GetConductorRadiusHorn2(zMid, fEqnIndicesOuter[k]);
    const double rIn = (amHorn1)  ? aPlacementHandler->GetConductorRadiusHorn1(zMid, fEqnIndicesInner[k]) :
    	      aPlacementHandler->GetConductorRadiusHorn2(zMid, fEqnIndicesInner[k]);
    std::cerr << " " << rIn << " " << rOut - rIn  << std::endl;
  }
//
// Use now the survey data (simulated for now.. ) to establish the coordinate transform..  
//
  LBNESurveyor *theSurvey= LBNESurveyor::Instance();
  std::string hornIndexStr = (amHorn1) ? std::string("1") : std::string("2"); 
  std::string upstrStr("Upstream");std::string downstrStr("Downstream");
  std::string leftStr("Left"); std::string rightStr("Right"); 
  std::string ballStr("BallHorn");
  std::vector<LBNESurveyedPt>::const_iterator itUpLeft=
    theSurvey->GetPoint(G4String(upstrStr + leftStr + ballStr + hornIndexStr));
  std::vector<LBNESurveyedPt>::const_iterator itUpRight=
    theSurvey->GetPoint(G4String(upstrStr + rightStr + ballStr + hornIndexStr));
  std::vector<LBNESurveyedPt>::const_iterator itDwLeft=
    theSurvey->GetPoint(G4String(downstrStr + leftStr + ballStr + hornIndexStr));
  std::vector<LBNESurveyedPt>::const_iterator itDwRight=
    theSurvey->GetPoint(G4String(downstrStr + rightStr + ballStr + hornIndexStr));
  const G4ThreeVector pUpLeft = itUpLeft->GetPosition();
  const G4ThreeVector pUpRight = itUpLeft->GetPosition();
  const G4ThreeVector pDwLeft = itUpLeft->GetPosition();
  const G4ThreeVector pDwRight = itUpLeft->GetPosition();
  for (size_t k=0; k!=2; k++) {
    fShift[k] = -0.25*(pUpLeft[k] + pDwLeft[k] + pUpRight[k] + pDwRight[k]); // minus sign comes from the global to local.
    fShiftSlope[k] = 0.5*(pUpLeft[k] + pUpRight[k] -  pDwLeft[k] - pDwRight[k])/fEffectiveLength; 
  }
  
}

void LBNEMagneticFieldHorn::GetFieldValue(const double Point[3],double *Bfield) const
{

  
   G4double current = fHornCurrent/ampere/1000.;
   // Intialization of the coordinate transform. 
   const LBNEVolumePlacements *aPlacementHandler = LBNEVolumePlacements::Instance();
   if (!coordinateSet) {
     G4Navigator* numinavigator=new G4Navigator(); //geometry navigator
     G4Navigator* theNavigator=G4TransportationManager::GetTransportationManager()->GetNavigatorForTracking();
     numinavigator->SetWorldVolume(theNavigator->GetWorldVolume());
     G4ThreeVector Position=G4ThreeVector(Point[0],Point[1],Point[2]); 
     G4VPhysicalVolume* myVolume = numinavigator->LocateGlobalPointAndSetup(Position);
     G4TouchableHistoryHandle aTouchable = numinavigator->CreateTouchableHistoryHandle();
     G4ThreeVector localPosition = aTouchable->GetHistory()->GetTopTransform().TransformPoint(Position);
     delete numinavigator;
     G4String vName = myVolume->GetLogicalVolume()->GetName();
     if (amHorn1 ) {
       if ((vName.find("Horn1TopLevelUpstr") == std::string::npos) && 
           (vName.find("Horn1IOTransCont") == std::string::npos)) {
	   std::ostringstream mStrStr;
	   mStrStr << " Z coordinate entrance confusion for horn1, fieldMGr enetrance at World Z " << Point[2] << std::endl;
	   G4String mStr(mStrStr.str());
	   G4Exception("LBNEMagneticFieldHorn::GetFieldValue", " ",  FatalErrorInArgument, mStr.c_str()); 
	}
	fZShiftUpstrWorldToLocal = Point[2] - localPosition[2]; // to correct for the misalignment, via the first coordinate transform
        const double zDelta = aPlacementHandler->GetHorn1DeltaZEntranceToZOrigin();
        fZShiftDrawingCoordinate = Point[2] -  localPosition[2] + zDelta; // Check the sign ! 
     } else {
        if (vName.find("Horn2TopLevel") == std::string::npos) {
	   std::ostringstream mStrStr;
	   mStrStr << " Z coordinate entrance confusion for horn1, fieldMGr enetrance at World Z " << Point[2] << std::endl;
	   G4String mStr(mStrStr.str());
	   G4Exception("LBNEMagneticFieldHorn::GetFieldValue", " ",  FatalErrorInArgument, mStr.c_str()); 
	}
 	fZShiftUpstrWorldToLocal = Point[2] - localPosition[2]; // to correct for the misalignment, via the first coordinate transform
        const double zDelta = aPlacementHandler->GetHorn2DeltaZEntranceToZOrigin();
        fZShiftDrawingCoordinate = Point[2] -  localPosition[2] + zDelta;
     }
     coordinateSet = true;
   } // Initialization of Z coordinate transform 
   
   std::vector<double> ptTrans(2,0.);
   const double zLocal = Point[2] - fZShiftUpstrWorldToLocal; // from the start of the relevant volume 
   for (size_t k=0; k != 2; k++) 
     ptTrans[k] = Point[k] + fShift[k] + zLocal*fShiftSlope[k]; 
   const double r = std::sqrt(ptTrans[0]*ptTrans[0] + ptTrans[1]*ptTrans[1]); 
   for (size_t k=0; k!=3; ++k) Bfield[k] = 0.;
   if (r > fOuterRadius) return;
   if ( r < 1.0e-3) return; // The field should go smoothly to zero at the center of the horm 

   double magBField = current / (5.*r/cm)/10*tesla; //B(kG)=i(kA)/[5*r(cm)], 1T=10kG
   
   if ( r > fOuterRadiusEff) {
     const double dr = r - fOuterRadiusEff;
     const double attLength  = std::exp(-dr/fSkinDepth);
     magBField *= attLength;
   } else { 
     size_t kSelZ = fEqnIndicesInner.size();
     const double zLocD = Point[2] - fZShiftDrawingCoordinate;
     for (size_t k=0; k != fEqnIndicesInner.size(); ++k) {
       if (zLocD < fZDCBegin[k]) continue;
       if (zLocD > fZDCEnd[k]) break; // They are Z ordered.. 
       kSelZ = k; 
       break;
     }
     if (kSelZ ==  fEqnIndicesInner.size()) return;
     double radIC = fHornNeckInnerRadius;
     double radOC = fHornNeckOuterRadius;
     if (fEqnIndicesInner[kSelZ] != 99) {
       radIC = (amHorn1) ? aPlacementHandler->GetConductorRadiusHorn1(zLocD,fEqnIndicesInner[kSelZ] ) : 
                        aPlacementHandler->GetConductorRadiusHorn2(zLocD, fEqnIndicesInner[kSelZ]);
       radOC = (amHorn1) ? aPlacementHandler->GetConductorRadiusHorn1(zLocD,fEqnIndicesOuter[kSelZ] ) : 
                        aPlacementHandler->GetConductorRadiusHorn2(zLocD, fEqnIndicesOuter[kSelZ]);
     }
     if ((radIC < 1.0e-3) || (radOC < 1.0e-3)) {
       std::ostringstream mStrStr;
       mStrStr << " Wrong equation index at Z " << Point[2] << std::endl;
       G4String mStr(mStrStr.str());
      G4Exception("LBNEMagneticFieldHorn::GetFieldValue", " ",  FatalErrorInArgument, mStr.c_str()); 
      return; 
     }
     if (r < radIC) return; // zero field region (Amps law). 
     // 
     if ((r > radIC) && (r < radOC)) {
      const double surfCyl = radOC*radOC - radIC*radIC;
      magBField *= (r*r - radIC*radIC)/surfCyl; // Assume uniform current density and apply Amps law. 
     }
     Bfield[0] = -magBField*ptTrans[1]/r;
     Bfield[1] = magBField*ptTrans[0]/r;
   }
}

