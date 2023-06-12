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

void ProtonTreeMxRebin(){


//void Proton(){
    Float_t runnum, evnum, helicity, e_p, e_theta, e_phi, vz_e, p_p, p_theta, p_phi, vz_p, Q2, W, Mx, Mx2, x, y, z, xF, pT, zeta, eta, phi, RICH_pid, RQ_prob, pi_prob, k_prob, pr_prob, chi2pid, beta;

//  FILE *fp = fopen("InBending-NoCuts.txt","r");
FILE *fp = fopen("/work/clas12/hvalenty/Total-Eloss.txt","r");
 //   FILE *fp = fopen("OutBending-NoCuts.txt","r");
    TFile *hfile = hfile = TFile::Open("PKplus2TOT.root","RECREATE");

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

for(int k=0; k<9777418; k++){
//for(int k=0; k<100000; k++){
//for(int k=0; k<167304297; k++){ //Total-Eloss.txt

//for(int k=0; k<59019; k++){

    fscanf(fp, "%f %f %f %f %f %f %f ", &runnum, &evnum, &helicity, &e_p, &e_theta, &e_phi, &vz_e);

    fscanf(fp, " %f %f %f %f %f %f %f %f ", &p_p, &p_theta, &p_phi, &vz_p, &Q2, &W, &Mx, &Mx2);

    fscanf(fp, " %f %f %f %f %f %f %f %f ", &x, &y, &z, &xF, &pT, &zeta, &eta, &phi);

  
    outTree->Fill();

    }

outTree->Write();
fclose(fp);
hfile->Write();


///////////////////////////////////////////////////////////////
TCut NegHeli = ("helicity == -1");
TCut PosHeli = ("helicity == 1");
TCut Mxg1 = ("y<0.75");


TCut Mx1a0 = ("1.0<Q2&&Q2<1.5");
TCut Mx1a1 = ("1.5<Q2&&Q2<2.0");
TCut Mx1a2 = ("2.0<Q2&&Q2<2.5");

TCut Mx2a0 = ("2.5<Q2&&Q2<3.0");
TCut Mx2a1 = ("3.0<Q2&&Q2<3.5");
TCut Mx2a2 = ("3.5<Q2&&Q2<4.0");

TCut Mx3a0 = ("4.0<Q2&&Q2<4.5");
TCut Mx3a1 = ("4.5<Q2&&Q2<5.0");
TCut Mx3a2 = ("5.0<Q2&&Q2<5.5");

TCut Mx4a0 = ("5.5<Q2&&Q2<6.0");
TCut Mx4a1 = ("6.0<Q2&&Q2<6.5");
TCut Mx4a2 = ("6.5<Q2&&Q2<7.0");

TCut Mx5a0 = ("7.0<Q2&&Q2<7.5");
TCut Mx5a1 = ("7.5<Q2&&Q2<8.0");
//////////////////////////////////////////////////////////////
TH1F*h67 = new TH1F("h67","h67",20, 0, 6.4);
outTree->Draw("phi>>h67");

///////////////////////////////////////////////////////////////Mx1a///
TCanvas*c01 = new TCanvas("c01", "PKplus", 1600,1100);
c01->Divide(2,1);
//c01->Print("FitMethodTreeReBin1.pdf[");
TH1F*h1 = new TH1F("h1","h1",20, 0, 6.4);
c01->cd(1);
h1->GetXaxis()->SetTitle("[1.0<Q2<1.5");
h1->GetXaxis()->SetTitleSize(0.03);
h1->GetXaxis()->SetLabelSize(0.02);
h1->GetXaxis()->SetTitleOffset(1);
h1->GetYaxis()->SetTitle("Counts");
h1->GetYaxis()->SetTitleSize(0.035);
h1->GetYaxis()->SetLabelSize(0.02);
h1->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h1", PosHeli && Mx1a0 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h2 = new TH1F("h2","h2",20, 0, 6.4);
c01->cd(2);
h2->GetXaxis()->SetTitle("[1.0<Q2<1.5]");
h2->GetXaxis()->SetTitleSize(0.03);
h2->GetXaxis()->SetLabelSize(0.02);
h2->GetXaxis()->SetTitleOffset(1);
h2->GetYaxis()->SetTitle("Counts");
h2->GetYaxis()->SetTitleSize(0.035);
h2->GetYaxis()->SetLabelSize(0.02);
h2->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h2", NegHeli && Mx1a0 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c03 = new TCanvas("c03", "PKplus", 1600,1100);
c03->Divide(2,1);
//c03->Print("FitMethodTreeReBin2.pdf[");
TH1F*h3 = new TH1F("h3","h3",20, 0, 6.4);
c03->cd(1);
h3->GetXaxis()->SetTitle("[1.5<Q2<2.0]");
h3->GetXaxis()->SetTitleSize(0.03);
h3->GetXaxis()->SetLabelSize(0.02);
h3->GetXaxis()->SetTitleOffset(1);
h3->GetYaxis()->SetTitle("Counts");
h3->GetYaxis()->SetTitleSize(0.035);
h3->GetYaxis()->SetLabelSize(0.02);
h3->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h3", PosHeli && Mx1a1 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h4 = new TH1F("h4","h4",20, 0, 6.4);
c03->cd(2);
h4->GetXaxis()->SetTitle("[1.5<Q2<2.0]");
h4->GetXaxis()->SetTitleSize(0.03);
h4->GetXaxis()->SetLabelSize(0.02);
h4->GetXaxis()->SetTitleOffset(1);
h4->GetYaxis()->SetTitle("Counts");
h4->GetYaxis()->SetTitleSize(0.035);
h4->GetYaxis()->SetLabelSize(0.02);
h4->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h4", NegHeli && Mx1a1 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c05 = new TCanvas("c05", "PKplus", 1600,1100);
c05->Divide(2,1);
//c05->Print("FitMethodTreeReBin3.pdf[");
TH1F*h5 = new TH1F("h5","h5",20, 0, 6.4);
c05->cd(1);
h5->GetXaxis()->SetTitle("[2.0<Q2<2.5]");
h5->GetXaxis()->SetTitleSize(0.03);
h5->GetXaxis()->SetLabelSize(0.02);
h5->GetXaxis()->SetTitleOffset(1);
h5->GetYaxis()->SetTitle("Counts");
h5->GetYaxis()->SetTitleSize(0.035);
h5->GetYaxis()->SetLabelSize(0.02);
h5->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h5", PosHeli && Mx1a2 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h6 = new TH1F("h6","h6",20, 0, 6.4);
c05->cd(2);
h6->GetXaxis()->SetTitle("[2.0<Q2<2.5]");
h6->GetXaxis()->SetTitleSize(0.03);
h6->GetXaxis()->SetLabelSize(0.02);
h6->GetXaxis()->SetTitleOffset(1);
h6->GetYaxis()->SetTitle("Counts");
h6->GetYaxis()->SetTitleSize(0.035);
h6->GetYaxis()->SetLabelSize(0.02);
h6->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h6", NegHeli && Mx1a2 && Mxg1);



///////////////////////////////////////////////////////////////Mx2a///
TCanvas*c07 = new TCanvas("c07", "PKplus", 1600,1100);
c07->Divide(2,1);
//c02->Print("FitMethodTreeBin2.pdf[");
TH1F*h7 = new TH1F("h7","h7",20, 0, 6.4);
c07->cd(1);
h7->GetXaxis()->SetTitle("[2.5<Q2<3.0]");
h7->GetXaxis()->SetTitleSize(0.03);
h7->GetXaxis()->SetLabelSize(0.02);
h7->GetXaxis()->SetTitleOffset(1);
h7->GetYaxis()->SetTitle("Counts");
h7->GetYaxis()->SetTitleSize(0.035);
h7->GetYaxis()->SetLabelSize(0.02);
h7->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h7", PosHeli && Mx2a0 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h8 = new TH1F("h8","h8",20, 0, 6.4);
c07->cd(2);
h8->GetXaxis()->SetTitle("[2.5<Q2<3.0]");
h8->GetXaxis()->SetTitleSize(0.03);
h8->GetXaxis()->SetLabelSize(0.02);
h8->GetXaxis()->SetTitleOffset(1);
h8->GetYaxis()->SetTitle("Counts");
h8->GetYaxis()->SetTitleSize(0.035);
h8->GetYaxis()->SetLabelSize(0.02);
h8->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h8", NegHeli && Mx2a0 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c09 = new TCanvas("c09", "PKplus", 1600,1100);
c09->Divide(2,1);
//c02->Print("FitMethodTreeBin2.pdf[");
TH1F*h9 = new TH1F("h9","h9",20, 0, 6.4);
c09->cd(1);
h9->GetXaxis()->SetTitle("[3.0<Q2<3.5]");
h9->GetXaxis()->SetTitleSize(0.03);
h9->GetXaxis()->SetLabelSize(0.02);
h9->GetXaxis()->SetTitleOffset(1);
h9->GetYaxis()->SetTitle("Counts");
h9->GetYaxis()->SetTitleSize(0.035);
h9->GetYaxis()->SetLabelSize(0.02);
h9->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h9", PosHeli && Mx2a1 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h10 = new TH1F("h10","h10",20, 0, 6.4);
c09->cd(2);
h10->GetXaxis()->SetTitle("[3.0<Q2<3.5]");
h10->GetXaxis()->SetTitleSize(0.03);
h10->GetXaxis()->SetLabelSize(0.02);
h10->GetXaxis()->SetTitleOffset(1);
h10->GetYaxis()->SetTitle("Counts");
h10->GetYaxis()->SetTitleSize(0.035);
h10->GetYaxis()->SetLabelSize(0.02);
h10->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h10", NegHeli && Mx2a1 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c11 = new TCanvas("c11", "PKplus", 1600,1100);
c11->Divide(2,1);
//c02->Print("FitMethodTreeBin2.pdf[");
TH1F*h11 = new TH1F("h11","h11",20, 0, 6.4);
c11->cd(1);
h11->GetXaxis()->SetTitle("[3.5<Q2<4.0]");
h11->GetXaxis()->SetTitleSize(0.03);
h11->GetXaxis()->SetLabelSize(0.02);
h11->GetXaxis()->SetTitleOffset(1);
h11->GetYaxis()->SetTitle("Counts");
h11->GetYaxis()->SetTitleSize(0.035);
h11->GetYaxis()->SetLabelSize(0.02);
h11->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h11", PosHeli && Mx2a2 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h12 = new TH1F("h12","h12",20, 0, 6.4);
c11->cd(2);
h12->GetXaxis()->SetTitle("[3.5<Q2<4.0]");
h12->GetXaxis()->SetTitleSize(0.03);
h12->GetXaxis()->SetLabelSize(0.02);
h12->GetXaxis()->SetTitleOffset(1);
h12->GetYaxis()->SetTitle("Counts");
h12->GetYaxis()->SetTitleSize(0.035);
h12->GetYaxis()->SetLabelSize(0.02);
h12->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h12", NegHeli && Mx2a2 && Mxg1);


///////////////////////////////////////////////////////////////Mx3a///
TCanvas*c13 = new TCanvas("c13", "PKplus", 1600,1100);
c13->Divide(2,1);
//c03->Print("FitMethodTreeBin3.pdf[");
TH1F*h13 = new TH1F("h13","h13",20, 0, 6.4);
c13->cd(1);
h13->GetXaxis()->SetTitle("[4.0<Q2<4.5]");
h13->GetXaxis()->SetTitleSize(0.03);
h13->GetXaxis()->SetLabelSize(0.02);
h13->GetXaxis()->SetTitleOffset(1);
h13->GetYaxis()->SetTitle("Counts");
h13->GetYaxis()->SetTitleSize(0.035);
h13->GetYaxis()->SetLabelSize(0.02);
h13->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h13", PosHeli && Mx3a0 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h14 = new TH1F("h14","h14",20, 0, 6.4);
c13->cd(2);
h14->GetXaxis()->SetTitle("[4.0<Q2<4.5]");
h14->GetXaxis()->SetTitleSize(0.03);
h14->GetXaxis()->SetLabelSize(0.02);
h14->GetXaxis()->SetTitleOffset(1);
h14->GetYaxis()->SetTitle("Counts");
h14->GetYaxis()->SetTitleSize(0.035);
h14->GetYaxis()->SetLabelSize(0.02);
h14->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h14", NegHeli && Mx3a0 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c15 = new TCanvas("c15", "PKplus", 1600,1100);
c15->Divide(2,1);
//c03->Print("FitMethodTreeBin3.pdf[");
TH1F*h15 = new TH1F("h15","h15",20, 0, 6.4);
c15->cd(1);
h15->GetXaxis()->SetTitle("[4.5<Q2<5.0]");
h15->GetXaxis()->SetTitleSize(0.03);
h15->GetXaxis()->SetLabelSize(0.02);
h15->GetXaxis()->SetTitleOffset(1);
h15->GetYaxis()->SetTitle("Counts");
h15->GetYaxis()->SetTitleSize(0.035);
h15->GetYaxis()->SetLabelSize(0.02);
h15->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h15", PosHeli && Mx3a1 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h16 = new TH1F("h16","h16",20, 0, 6.4);
c15->cd(2);
h16->GetXaxis()->SetTitle("[4.5<Q2<5.0]");
h16->GetXaxis()->SetTitleSize(0.03);
h16->GetXaxis()->SetLabelSize(0.02);
h16->GetXaxis()->SetTitleOffset(1);
h16->GetYaxis()->SetTitle("Counts");
h16->GetYaxis()->SetTitleSize(0.035);
h16->GetYaxis()->SetLabelSize(0.02);
h16->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h16", NegHeli && Mx3a1 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c17 = new TCanvas("c17", "PKplus", 1600,1100);
c17->Divide(2,1);
//c03->Print("FitMethodTreeBin3.pdf[");
TH1F*h17 = new TH1F("h17","h17",20, 0, 6.4);
c17->cd(1);
h17->GetXaxis()->SetTitle("[5.0<Q2<5.5]");
h17->GetXaxis()->SetTitleSize(0.03);
h17->GetXaxis()->SetLabelSize(0.02);
h17->GetXaxis()->SetTitleOffset(1);
h17->GetYaxis()->SetTitle("Counts");
h17->GetYaxis()->SetTitleSize(0.035);
h17->GetYaxis()->SetLabelSize(0.02);
h17->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h17", PosHeli && Mx3a2 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h18 = new TH1F("h18","h18",20, 0, 6.4);
c17->cd(2);
h18->GetXaxis()->SetTitle("[5.0<Q2<5.5]");
h18->GetXaxis()->SetTitleSize(0.03);
h18->GetXaxis()->SetLabelSize(0.02);
h18->GetXaxis()->SetTitleOffset(1);
h18->GetYaxis()->SetTitle("Counts");
h18->GetYaxis()->SetTitleSize(0.035);
h18->GetYaxis()->SetLabelSize(0.02);
h18->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h18", NegHeli && Mx3a2 && Mxg1);

///////////////////////////////////////////////////////////////Mx4a///
TCanvas*c19 = new TCanvas("c19", "PKplus", 1600,1100);
c19->Divide(2,1);
TH1F*h19 = new TH1F("h19","h19",20, 0, 6.4);
c19->cd(1);
h19->GetXaxis()->SetTitle("[5.5<Q2<6.0]");
h19->GetXaxis()->SetTitleSize(0.03);
h19->GetXaxis()->SetLabelSize(0.02);
h19->GetXaxis()->SetTitleOffset(1);
h19->GetYaxis()->SetTitle("Counts");
h19->GetYaxis()->SetTitleSize(0.035);
h19->GetYaxis()->SetLabelSize(0.02);
h19->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h19", PosHeli && Mx4a0 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h20 = new TH1F("h20","h20",20, 0, 6.4);
c19->cd(2);
h20->GetXaxis()->SetTitle("[5.5<Q2<6.0]");
h20->GetXaxis()->SetTitleSize(0.03);
h20->GetXaxis()->SetLabelSize(0.02);
h20->GetXaxis()->SetTitleOffset(1);
h20->GetYaxis()->SetTitle("Counts");
h20->GetYaxis()->SetTitleSize(0.035);
h20->GetYaxis()->SetLabelSize(0.02);
h20->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h20", NegHeli && Mx4a0 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c21 = new TCanvas("c21", "PKplus", 1600,1100);
c21->Divide(2,1);
TH1F*h21 = new TH1F("h21","h21",20, 0, 6.4);
c21->cd(1);
h21->GetXaxis()->SetTitle("[6.0<Q2<6.5]");
h21->GetXaxis()->SetTitleSize(0.03);
h21->GetXaxis()->SetLabelSize(0.02);
h21->GetXaxis()->SetTitleOffset(1);
h21->GetYaxis()->SetTitle("Counts");
h21->GetYaxis()->SetTitleSize(0.035);
h21->GetYaxis()->SetLabelSize(0.02);
h21->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h21", PosHeli && Mx4a1 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h22 = new TH1F("h22","h22",20, 0, 6.4);
c21->cd(2);
h22->GetXaxis()->SetTitle("[6.0<Q2<6.5]");
h22->GetXaxis()->SetTitleSize(0.03);
h22->GetXaxis()->SetLabelSize(0.02);
h22->GetXaxis()->SetTitleOffset(1);
h22->GetYaxis()->SetTitle("Counts");
h22->GetYaxis()->SetTitleSize(0.035);
h22->GetYaxis()->SetLabelSize(0.02);
h22->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h22", NegHeli && Mx4a1 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c23 = new TCanvas("c23", "PKplus", 1600,1100);
c23->Divide(2,1);
TH1F*h23 = new TH1F("h23","h23",20, 0, 6.4);
c23->cd(1);
h23->GetXaxis()->SetTitle("[6.5<Q2<7.0]");
h23->GetXaxis()->SetTitleSize(0.03);
h23->GetXaxis()->SetLabelSize(0.02);
h23->GetXaxis()->SetTitleOffset(1);
h23->GetYaxis()->SetTitle("Counts");
h23->GetYaxis()->SetTitleSize(0.035);
h23->GetYaxis()->SetLabelSize(0.02);
h23->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h23", PosHeli && Mx4a2 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h24 = new TH1F("h24","h24",20, 0, 6.4);
c23->cd(2);
h24->GetXaxis()->SetTitle("[6.5<Q2<7.0]");
h24->GetXaxis()->SetTitleSize(0.03);
h24->GetXaxis()->SetLabelSize(0.02);
h24->GetXaxis()->SetTitleOffset(1);
h24->GetYaxis()->SetTitle("Counts");
h24->GetYaxis()->SetTitleSize(0.035);
h24->GetYaxis()->SetLabelSize(0.02);
h24->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h24", NegHeli && Mx4a2 && Mxg1);


///////////////////////////////////////////////////////////////Mx5a///
TCanvas*c25 = new TCanvas("c25", "PKplus", 1600,1100);
c25->Divide(2,1);
//c05->Print("FitMethodTreeBin5.pdf[");
TH1F*h25 = new TH1F("h25","h25",20, 0, 6.4);
c25->cd(1);
h25->GetXaxis()->SetTitle("[7.0<Q2<7.5]");
h25->GetXaxis()->SetTitleSize(0.03);
h25->GetXaxis()->SetLabelSize(0.02);
h25->GetXaxis()->SetTitleOffset(1);
h25->GetYaxis()->SetTitle("Counts");
h25->GetYaxis()->SetTitleSize(0.035);
h25->GetYaxis()->SetLabelSize(0.02);
h25->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h25", PosHeli && Mx5a0 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h26 = new TH1F("h26","h26",20, 0, 6.4);
c25->cd(2);
h26->GetXaxis()->SetTitle("[7.0<Q2<7.5]");
h26->GetXaxis()->SetTitleSize(0.03);
h26->GetXaxis()->SetLabelSize(0.02);
h26->GetXaxis()->SetTitleOffset(1);
h26->GetYaxis()->SetTitle("Counts");
h26->GetYaxis()->SetTitleSize(0.035);
h26->GetYaxis()->SetLabelSize(0.02);
h26->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h26", NegHeli && Mx5a0 && Mxg1);


///////////////////////////////////////////////////////////////
TCanvas*c27 = new TCanvas("c27", "PKplus", 1600,1100);
c27->Divide(2,1);
//c05->Print("FitMethodTreeBin5.pdf[");
TH1F*h27 = new TH1F("h27","h27",20, 0, 6.4);
c27->cd(1);
h27->GetXaxis()->SetTitle("[7.5<Q2<8.0]");
h27->GetXaxis()->SetTitleSize(0.03);
h27->GetXaxis()->SetLabelSize(0.02);
h27->GetXaxis()->SetTitleOffset(1);
h27->GetYaxis()->SetTitle("Counts");
h27->GetYaxis()->SetTitleSize(0.035);
h27->GetYaxis()->SetLabelSize(0.02);
h27->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h27", PosHeli && Mx5a1 && Mxg1);
///////////////////////////////////////////////////////////////
TH1F*h28 = new TH1F("h28","h28",20, 0, 6.4);
c27->cd(2);
h28->GetXaxis()->SetTitle("7.5<Q2<8.0]");
h28->GetXaxis()->SetTitleSize(0.03);
h28->GetXaxis()->SetLabelSize(0.02);
h28->GetXaxis()->SetTitleOffset(1);
h28->GetYaxis()->SetTitle("Counts");
h28->GetYaxis()->SetTitleSize(0.035);
h28->GetYaxis()->SetLabelSize(0.02);
h28->GetYaxis()->SetTitleOffset(0.9);
outTree->Draw("phi>>h28", NegHeli && Mx5a1 && Mxg1);


///////////////////////////////////////////////////////////////

ofstream outputfile14("FitMethodBin14Mx.txt");
int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile14 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h27->GetBinContent(i) << "\t" << h28->GetBinContent(i) << endl; }
outputfile14.close();


///////////////////////////////////////////////////////////////

ofstream outputfile13("FitMethodBin13Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile13 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h25->GetBinContent(i) << "\t" << h26->GetBinContent(i) << endl; }
outputfile13.close();


///////////////////////////////////////////////////////////////

ofstream outputfile12("FitMethodBin12Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile12 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h23->GetBinContent(i) << "\t" << h24->GetBinContent(i) << endl; }
outputfile12.close();


///////////////////////////////////////////////////////////////

ofstream outputfile11("FitMethodBin11Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile11 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h21->GetBinContent(i) << "\t" << h22->GetBinContent(i) << endl; }
outputfile11.close();


///////////////////////////////////////////////////////////////
ofstream outputfile10("FitMethodBin10Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile10 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h19->GetBinContent(i) << "\t" << h20->GetBinContent(i) << endl; }
outputfile10.close();


///////////////////////////////////////////////////////////////
ofstream outputfile9("FitMethodBin9Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile9 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h17->GetBinContent(i) << "\t" << h18->GetBinContent(i) << endl; }
outputfile9.close();


///////////////////////////////////////////////////////////////
ofstream outputfile8("FitMethodBin8Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile8 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h15->GetBinContent(i) << "\t" << h16->GetBinContent(i) << endl; }
outputfile8.close();

///////////////////////////////////////////////////////////////
ofstream outputfile7("FitMethodBin7Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile7 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h13->GetBinContent(i) << "\t" << h14->GetBinContent(i) << endl; }
outputfile7.close();

///////////////////////////////////////////////////////////////
ofstream outputfile6("FitMethodBin6Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile6 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h11->GetBinContent(i) << "\t" << h12->GetBinContent(i) << endl; }
outputfile6.close();

///////////////////////////////////////////////////////////////
ofstream outputfile5("FitMethodBin5Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile5 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h9->GetBinContent(i) << "\t" << h10->GetBinContent(i) << endl; }
outputfile5.close();

///////////////////////////////////////////////////////////////
ofstream outputfile4("FitMethodBin4Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile4 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h7->GetBinContent(i) << "\t" << h8->GetBinContent(i) << endl; }
outputfile4.close();

///////////////////////////////////////////////////////////////
ofstream outputfile3("FitMethodBin3Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile3 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h5->GetBinContent(i) << "\t" << h6->GetBinContent(i) << endl; }
outputfile3.close();


///////////////////////////////////////////////////////////////
ofstream outputfile2("FitMethodBin2Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile2 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h3->GetBinContent(i) << "\t" << h4->GetBinContent(i) << endl; }
outputfile2.close();


///////////////////////////////////////////////////////////////
ofstream outputfile1("FitMethodBin1Mx.txt");
//int N = h1->GetNbinsX() + 1; 
for(int i=0; i<N; ++i){
outputfile1 << "\t" << h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2  << "\t" << h1->GetBinContent(i) << "\t" << h2->GetBinContent(i) << endl; }
outputfile1.close();



/*
c01->Print("FitMethodBin1.pdf");
c01->Print("FitMethodBin1.pdf]");
c02->Print("FitMethodBin2.pdf");
c02->Print("FitMethodBin2.pdf]");
c03->Print("FitMethodBin3.pdf");
c03->Print("FitMethodBin3.pdf]");
c04->Print("FitMethodBin4.pdf");
c04->Print("FitMethodBin4.pdf]");
c05->Print("FitMethodBin5.pdf");
c05->Print("FitMethodBin5.pdf]");
c06->Print("FitMethodBin6.pdf");
c06->Print("FitMethodBin6.pdf]");
c07->Print("FitMethodBin7.pdf");
c07->Print("FitMethodBin7.pdf]");
c08->Print("FitMethodBin8.pdf");
c08->Print("FitMethodBin8.pdf]");
c09->Print("FitMethodBin9.pdf");
c09->Print("FitMethodBin9.pdf]");
c010->Print("FitMethodBin10.pdf");
c010->Print("FitMethodBin10.pdf]");
c011->Print("FitMethodBin11.pdf");
c011->Print("FitMethodBin11.pdf]");


*/
}






