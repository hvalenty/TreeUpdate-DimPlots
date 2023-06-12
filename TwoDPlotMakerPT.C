#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TH1F.h>
#include <TMath.h>
#include <fstream>
#include <iostream>

void TwoDPlotMakerPT(){


//void Proton(){
    Float_t runnum, evnum, helicity, e_p, e_theta, e_phi, vz_e, p_p, p_theta, p_phi, vz_p, Q2, W, Mx, Mx2, x, y, z, xF, pT, zeta, eta, phi;
    Float_t da, db, dc, dd, dw, de;
    float mean, rms;
FILE *fp = fopen("/work/clas12/fatiha/Depol/ProtonTotalinbending_Eloss_Depol.QA.txt","r");

//fopen("/work/clas12/fatiha/ProtonSpring2019inbending_Eloss_Depol.QA.txt","r");
FILE *fp1;
fp1 = fopen ("mean_vs_xF.txt", "w");
 //   FILE *fp = fopen("OutBending-NoCuts.txt","r");
    TFile *hfile = hfile = TFile::Open("PKplus2.root","RECREATE");

    TTree *outTree = new TTree("T","kinematics tree");
    outTree->Branch("runnum",&runnum,"runnum/F");
    outTree->Branch("evnum",&evnum,"evnum/F");
    outTree->Branch("helicity", &helicity,"helicity/F");
    outTree->Branch("e_p",&e_p,"e_p/F");
    outTree->Branch("e_theta",&e_theta,"e_theta/F");
    outTree->Branch("e_phi",&e_phi,"e_phi/F");
    outTree->Branch("vz_e",&vz_e,"vz_e/F");
    outTree->Branch("p_p",&p_p,"p_p/F");
    outTree->Branch("p_theta",&p_theta,"p_theta/F");
    outTree->Branch("p_phi",&p_phi,"p_phi/F");
    outTree->Branch("vz_p",&vz_p,"vz_p/F");
    outTree->Branch("Q2",&Q2,"Q2/F");
    outTree->Branch("W",&W,"W/F");
    outTree->Branch("Mx",&Mx,"Mx/F");
    outTree->Branch("Mx2",&Mx2,"Mx2/F");
    outTree->Branch("x",&x,"x/F");
    outTree->Branch("y",&y,"y/F");
    outTree->Branch("z",&z,"z/F");
    outTree->Branch("xF",&xF,"xF/F");
    outTree->Branch("pT",&pT,"pT/F");
    outTree->Branch("zeta",&zeta,"zeta/F");
    outTree->Branch("eta",&eta,"eta/F");
    outTree->Branch("phi",&phi,"phi/F");
    outTree->Branch("da",&da,"da/F");
    outTree->Branch("db",&db,"db/F");
    outTree->Branch("dc",&dc,"dc/F");
    outTree->Branch("dd",&dd,"dd/F");
    outTree->Branch("dw",&dw,"dw/F");
    outTree->Branch("de",&de,"de/F");


// for(int k=0; k<9777418; k++){
for(int k=0; k<190866012; k++){
//16372460 total number of events in this file 
// for(int k=0; k<6; k++){

// 10019 has 57938894 events 

//for(int k=0; k<59019; k++){

    fscanf(fp, "%f %f %f %f %f %f %f ", &runnum, &evnum, &helicity, &e_p, &e_theta, &e_phi, &vz_e);

    fscanf(fp, " %f %f %f %f %f %f %f %f ", &p_p, &p_theta, &p_phi, &vz_p, &Q2, &W, &Mx, &Mx2);

    fscanf(fp, " %f %f %f %f %f %f %f %f  ", &x, &y, &z, &xF, &pT, &zeta, &eta, &phi );

    fscanf(fp, " %f %f %f %f %f ", &da, &db, &dc, &dd, &dw);
    
    de = dw/da;

    outTree->Fill();

    }

outTree->Write();
fclose(fp);
hfile->Write();

gStyle->SetPadTopMargin(0.1);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadRightMargin(0.12);
////////////////////////////////////////////////////////////////
TCanvas*c01162 = new TCanvas("c01162", "", 1000,700);
gStyle->SetPalette(1);
c01162->Divide(1,1);
TH2D*mx2xf = new TH2D("mx2xf","", 500, 0.5, 0.75, 500, 0, 8);
c01162->cd(1);
mx2xf->GetXaxis()->SetTitle("Depolarization Factor");
mx2xf->GetXaxis()->SetTitleSize(0.1);
mx2xf->GetXaxis()->SetLabelSize(0.05);
mx2xf->GetXaxis()->SetTitleOffset(0.6);
mx2xf->GetYaxis()->SetTitle("p_{T}");
mx2xf->GetYaxis()->SetTitleSize(0.1);
mx2xf->GetYaxis()->SetLabelSize(0.05);
mx2xf->GetYaxis()->SetTitleOffset(0.6);

mx2xf->SetLineWidth(5);
mx2xf->SetStats(0);

outTree->Draw("pT:de>>mx2xf"); //"Y-Var:X-Var>>OntoPlot"
mx2xf->Draw("COLZ");

gPad->Modified();
gPad->Update();

c01162->Print("2DimPTvsde1.png");
//c01162->Print("2DimQ2vsde3.pdf");
}
