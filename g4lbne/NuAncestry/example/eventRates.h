//////////////////////////////////////////////////////////
// Created by L. Loiacono
// Modified by L. Fields
//////////////////////////////////////////////////////////

#ifndef eventRates_h
#define eventRates_h

// C++
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

//ROOT
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TRandom3.h>

class eventRates {
public :

   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   //TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   Double_t        fTotalPOT; //total pot used for all files
   std::string     ffilename; //filename for saving histograms
   std::string     detectorname; // name for det location
   double detx;     // detector location
   double dety;
   double detz;

   TRandom3 *rand3;

   // Declaration of leaf types
 //LBNEDataNtp_t   *data;
   Int_t           run;
   Int_t           evtno;
   Int_t           protonN;
   Float_t         beamHWidth;
   Float_t         beamVWidth;
   Float_t         beamX;
   Float_t         beamY;
   Float_t         protonX;
   Float_t         protonY;
   Float_t         protonZ;
   Float_t         protonPx;
   Float_t         protonPy;
   Float_t         protonPz;
   Float_t         nuTarZ;
   Float_t         hornCurrent;
   Float_t         Ndxdz;
   Float_t         Ndydz;
   Float_t         Npz;
   Float_t         Nenergy;
   Float_t         NdxdzNear[5];
   Float_t         NdydzNear[5];
   Float_t         NenergyN[5];
   Double_t        NWtNear[5];
   Float_t         NdxdzFar[3];
   Float_t         NdydzFar[3];
   Float_t         NenergyF[3];
   Double_t        NWtFar[3];
   Int_t           Norig;
   Int_t           Ndecay;
   Int_t           Ntype;
   Float_t         Vx;
   Float_t         Vy;
   Float_t         Vz;
   Float_t         pdPx;
   Float_t         pdPy;
   Float_t         pdPz;
   Float_t         ppdxdz;
   Float_t         ppdydz;
   Float_t         pppz;
   Float_t         ppenergy;
   Float_t         ppmedium;
   Int_t           ptype;
   Int_t           ptrkid;
   Float_t         ppvx;
   Float_t         ppvy;
   Float_t         ppvz;
   Float_t         muparpx;
   Float_t         muparpy;
   Float_t         muparpz;
   Float_t         mupare;
   Float_t         Necm;
   Double_t        Nimpwt;
   Float_t         xpoint;
   Float_t         ypoint;
   Float_t         zpoint;
   Float_t         tvx;
   Float_t         tvy;
   Float_t         tvz;
   Float_t         tpx;
   Float_t         tpy;
   Float_t         tpz;
   Int_t           tptype;
   Int_t           tgen;
 //map<int,TrackPoint_t> fTrkPtMap;

   // List of branches
   TBranch        *b_data_run;   //!
   TBranch        *b_data_evtno;   //!
   TBranch        *b_data_protonN;   //!
   TBranch        *b_data_beamHWidth;   //!
   TBranch        *b_data_beamVWidth;   //!
   TBranch        *b_data_beamX;   //!
   TBranch        *b_data_beamY;   //!
   TBranch        *b_data_protonX;   //!
   TBranch        *b_data_protonY;   //!
   TBranch        *b_data_protonZ;   //!
   TBranch        *b_data_protonPx;   //!
   TBranch        *b_data_protonPy;   //!
   TBranch        *b_data_protonPz;   //!
   TBranch        *b_data_nuTarZ;   //!
   TBranch        *b_data_hornCurrent;   //!
   TBranch        *b_data_Ndxdz;   //!
   TBranch        *b_data_Ndydz;   //!
   TBranch        *b_data_Npz;   //!
   TBranch        *b_data_Nenergy;   //!
   TBranch        *b_data_NdxdzNear;   //!
   TBranch        *b_data_NdydzNear;   //!
   TBranch        *b_data_NenergyN;   //!
   TBranch        *b_data_NWtNear;   //!
   TBranch        *b_data_NdxdzFar;   //!
   TBranch        *b_data_NdydzFar;   //!
   TBranch        *b_data_NenergyF;   //!
   TBranch        *b_data_NWtFar;   //!
   TBranch        *b_data_Norig;   //!
   TBranch        *b_data_Ndecay;   //!
   TBranch        *b_data_Ntype;   //!
   TBranch        *b_data_Vx;   //!
   TBranch        *b_data_Vy;   //!
   TBranch        *b_data_Vz;   //!
   TBranch        *b_data_pdPx;   //!
   TBranch        *b_data_pdPy;   //!
   TBranch        *b_data_pdPz;   //!
   TBranch        *b_data_ppdxdz;   //!
   TBranch        *b_data_ppdydz;   //!
   TBranch        *b_data_pppz;   //!
   TBranch        *b_data_ppenergy;   //!
   TBranch        *b_data_ppmedium;   //!
   TBranch        *b_data_ptype;   //!
   TBranch        *b_data_ptrkid;   //!
   TBranch        *b_data_ppvx;   //!
   TBranch        *b_data_ppvy;   //!
   TBranch        *b_data_ppvz;   //!
   TBranch        *b_data_muparpx;   //!
   TBranch        *b_data_muparpy;   //!
   TBranch        *b_data_muparpz;   //!
   TBranch        *b_data_mupare;   //!
   TBranch        *b_data_Necm;   //!
   TBranch        *b_data_Nimpwt;   //!
   TBranch        *b_data_xpoint;   //!
   TBranch        *b_data_ypoint;   //!
   TBranch        *b_data_zpoint;   //!
   TBranch        *b_data_tvx;   //!
   TBranch        *b_data_tvy;   //!
   TBranch        *b_data_tvz;   //!
   TBranch        *b_data_tpx;   //!
   TBranch        *b_data_tpy;   //!
   TBranch        *b_data_tpz;   //!
   TBranch        *b_data_tptype;   //!
   TBranch        *b_data_tgen;   //!

   eventRates(std::string simulation = "G4PBeam", std::string geometry = "CD1-CDR_Geo", std::string location = "LBNEFD", std::string physics_list = "QGSP_BERT", int n_files = 250, double pot_per_file = 100000);

   virtual ~eventRates();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   std::string GetPOTAsString(const double dpot);
   void SetTitles(TH1* h, 
		  const std::string &xtitle = "", 
		  const std::string &ytitle = "");
   
   double GetWeight(const std::vector<double> xdet,
			    double& nu_wght, 
			    double& nu_energy);

   double GetXSec(  double nu_type, 
		    double nu_energy,
		    std::string current);

   void ReadXSecsFromFiles(  );
   
   double GetOscillatedNeutrinoType(double E);


 private:

    std::ifstream fdat_file[4];
    int fnbins;
    int fnlines;
    double f_e_arr[1500][4][2]; // energy bins; neutrino type; CC/NC
    double f_xsec_arr[1500][4][2]; // energy bins; neutrino type; CC/NC
   
};

#endif

#ifdef eventRates_cxx
eventRates::eventRates(std::string simulation, std::string geometry, std::string location, std::string physics_list, int n_files, double potperfile)
{
  //simulation = G4PBeam or Fluka

  // Read the cross-sections from files
  ReadXSecsFromFiles();

//????????????????????????????
//????????????????????????????
//
   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   //
   //Add files here
   //
  std::vector<std::string> fFileVec;

  detectorname = location;
  if(location=="LBNEND") {
    detx = 0.0;
    dety = 0.0;
    detz = 47915.0;
  }
  
  if(location=="LBNEFD") {
    detx = 0.0;
    dety = 0.0;
    detz = 129700000.0;
  }

  if(location=="LBNEFD_XSHIFT+21") {
    detx = 2100.0;
    dety = 0.0;
    detz = 129700000.0; 
  }
  if(location=="LBNEFD_XSHIFT-21") {
    detx = -2100.0;
    dety = 0.0;
    detz = 129700000.0; 
  }
  if(location=="LBNEFD_YSHIFT+21") {
    detx = 0.0;
    dety = 2100.0;
    detz = 129700000.0; 
  }
  if(location=="LBNEFD_YSHIFT-21") {
    detx = 0.0;
    dety = -2100.0;
    detz = 129700000.0; 
  }
  if(location == "LBNEFD_XSHIFT500") {
    detx = 50000.0;
    dety = 0.0;
    detz = 129700000.0; 
  }
  if(location == "LBNEFD_XSHIFT2000") {
    detx = 200000.0;
    dety = 0.0;
    detz = 129700000.0; 
  }
  
  std::string physics_list_file_path1 = "";
  std::string physics_list_file_path2 = "";

  physics_list_file_path1 = "/"+physics_list;
  physics_list_file_path2 = "_"+physics_list;
  
  std::string flux_dir = "/lbne/data/users/ljf26/fluxfiles/g4lbne/"+geometry+"/"+physics_list+"/nubeam-"+simulation+"-stdnubeam/flux/";
  
  int start_index = 1;
  int end_index = n_files;
  
  for(int i = start_index; i<= end_index; i++) {
    
    // convert index into zero-padded string
    std::ostringstream ss;
    ss << std::setw( 3 ) << std::setfill( '0' ) << i;
    std::string index_string = ss.str();
    
    std::string flux_file = flux_dir + geometry+"_"+physics_list+"_nubeam-"+simulation+"-stdnubeam_"+index_string+".root";
    
    // check that the file exists and is a valid root file
    TFile f(flux_file.c_str());
    if (!f.IsZombie())
      fFileVec.push_back(flux_file.c_str());
  }

  //set number of pot per file !!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //
  fTotalPOT  = potperfile*(double)fFileVec.size();

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //set the filename prefix for saving histogram plots 
  //
  ffilename = "g4lbne_"+geometry+"_"+physics_list;
  if(simulation=="Fluka")
     ffilename = "fluka_"+geometry+"_"+physics_list;
   
   //
   //????????????????????????????
   //????????????????????????????

   fChain = new TChain("nudata");
   for(std::vector<std::string>::const_iterator sit = fFileVec.begin(); sit != fFileVec.end(); ++sit)
   {
     fChain -> Add(sit -> c_str());
   }

   Init(fChain);

   // initialize random numbers used for oscillation calculations
   rand3 = new TRandom3(0); 

}

eventRates::~eventRates()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t eventRates::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t eventRates::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void eventRates::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers

   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_data_run);
   fChain->SetBranchAddress("evtno", &evtno, &b_data_evtno);
   fChain->SetBranchAddress("protonN", &protonN, &b_data_protonN);
   fChain->SetBranchAddress("beamHWidth", &beamHWidth, &b_data_beamHWidth);
   fChain->SetBranchAddress("beamVWidth", &beamVWidth, &b_data_beamVWidth);
   fChain->SetBranchAddress("beamX", &beamX, &b_data_beamX);
   fChain->SetBranchAddress("beamY", &beamY, &b_data_beamY);
   fChain->SetBranchAddress("protonX", &protonX, &b_data_protonX);
   fChain->SetBranchAddress("protonY", &protonY, &b_data_protonY);
   fChain->SetBranchAddress("protonZ", &protonZ, &b_data_protonZ);
   fChain->SetBranchAddress("protonPx", &protonPx, &b_data_protonPx);
   fChain->SetBranchAddress("protonPy", &protonPy, &b_data_protonPy);
   fChain->SetBranchAddress("protonPz", &protonPz, &b_data_protonPz);
   fChain->SetBranchAddress("nuTarZ", &nuTarZ, &b_data_nuTarZ);
   fChain->SetBranchAddress("hornCurrent", &hornCurrent, &b_data_hornCurrent);
   fChain->SetBranchAddress("Ndxdz", &Ndxdz, &b_data_Ndxdz);
   fChain->SetBranchAddress("Ndydz", &Ndydz, &b_data_Ndydz);
   fChain->SetBranchAddress("Npz", &Npz, &b_data_Npz);
   fChain->SetBranchAddress("Nenergy", &Nenergy, &b_data_Nenergy);
   fChain->SetBranchAddress("NdxdzNear[5]", NdxdzNear, &b_data_NdxdzNear);
   fChain->SetBranchAddress("NdydzNear[5]", NdydzNear, &b_data_NdydzNear);
   fChain->SetBranchAddress("NenergyN[5]", NenergyN, &b_data_NenergyN);
   fChain->SetBranchAddress("NWtNear[5]", NWtNear, &b_data_NWtNear);
   fChain->SetBranchAddress("NdxdzFar[3]", NdxdzFar, &b_data_NdxdzFar);
   fChain->SetBranchAddress("NdydzFar[3]", NdydzFar, &b_data_NdydzFar);
   fChain->SetBranchAddress("NenergyF[3]", NenergyF, &b_data_NenergyF);
   fChain->SetBranchAddress("NWtFar[3]", NWtFar, &b_data_NWtFar);
   fChain->SetBranchAddress("Norig", &Norig, &b_data_Norig);
   fChain->SetBranchAddress("Ndecay", &Ndecay, &b_data_Ndecay);
   fChain->SetBranchAddress("Ntype", &Ntype, &b_data_Ntype);
   fChain->SetBranchAddress("Vx", &Vx, &b_data_Vx);
   fChain->SetBranchAddress("Vy", &Vy, &b_data_Vy);
   fChain->SetBranchAddress("Vz", &Vz, &b_data_Vz);
   fChain->SetBranchAddress("pdPx", &pdPx, &b_data_pdPx);
   fChain->SetBranchAddress("pdPy", &pdPy, &b_data_pdPy);
   fChain->SetBranchAddress("pdPz", &pdPz, &b_data_pdPz);
   fChain->SetBranchAddress("ppdxdz", &ppdxdz, &b_data_ppdxdz);
   fChain->SetBranchAddress("ppdydz", &ppdydz, &b_data_ppdydz);
   fChain->SetBranchAddress("pppz", &pppz, &b_data_pppz);
   fChain->SetBranchAddress("ppenergy", &ppenergy, &b_data_ppenergy);
   fChain->SetBranchAddress("ppmedium", &ppmedium, &b_data_ppmedium);
   fChain->SetBranchAddress("ptype", &ptype, &b_data_ptype);
   fChain->SetBranchAddress("ptrkid", &ptrkid, &b_data_ptrkid);
   fChain->SetBranchAddress("ppvx", &ppvx, &b_data_ppvx);
   fChain->SetBranchAddress("ppvy", &ppvy, &b_data_ppvy);
   fChain->SetBranchAddress("ppvz", &ppvz, &b_data_ppvz);
   fChain->SetBranchAddress("muparpx", &muparpx, &b_data_muparpx);
   fChain->SetBranchAddress("muparpy", &muparpy, &b_data_muparpy);
   fChain->SetBranchAddress("muparpz", &muparpz, &b_data_muparpz);
   fChain->SetBranchAddress("mupare", &mupare, &b_data_mupare);
   fChain->SetBranchAddress("Necm", &Necm, &b_data_Necm);
   fChain->SetBranchAddress("Nimpwt", &Nimpwt, &b_data_Nimpwt);
   fChain->SetBranchAddress("xpoint", &xpoint, &b_data_xpoint);
   fChain->SetBranchAddress("ypoint", &ypoint, &b_data_ypoint);
   fChain->SetBranchAddress("zpoint", &zpoint, &b_data_zpoint);
   fChain->SetBranchAddress("tvx", &tvx, &b_data_tvx);
   fChain->SetBranchAddress("tvy", &tvy, &b_data_tvy);
   fChain->SetBranchAddress("tvz", &tvz, &b_data_tvz);
   fChain->SetBranchAddress("tpx", &tpx, &b_data_tpx);
   fChain->SetBranchAddress("tpy", &tpy, &b_data_tpy);
   fChain->SetBranchAddress("tpz", &tpz, &b_data_tpz);
   fChain->SetBranchAddress("tptype", &tptype, &b_data_tptype);
   fChain->SetBranchAddress("tgen", &tgen, &b_data_tgen);
   Notify();
}

Bool_t eventRates::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void eventRates::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t eventRates::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef eventRates_cxx
