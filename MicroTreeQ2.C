#include "TBrowser.h"
#include "TH2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TH1F.h>
#include <TMath.h>
#include <fstream>
#include <iostream>
#include <sstream>

void MicroTreeQ2(){


//void Proton(){
    Float_t runnum, evnum, helicity, e_p, e_theta, e_phi, vz_e, p_p, p_theta, p_phi, vz_p, xF, W, Mx, Mx2, x, y, z, Q2, pT, zeta, eta, phi;

    float xmean, binNumber, entriesNumber;
    FILE *fp = fopen("/work/clas12/hvalenty/Total-Eloss.txt","r");  // Text file called to start analysis

    TFile *hfile = hfile = TFile::Open("PKplus2TOT.root","RECREATE");  // File with ROOT Tree

    TTree *outTree = new TTree("T","kinematics tree");   //Variables in the the ROOT Tree
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
    outTree->Branch("xF",&xF,"xF/F");
    outTree->Branch("W",&W,"W/F");
    outTree->Branch("Mx",&Mx,"Mx/F");
    outTree->Branch("Mx2",&Mx2,"Mx2/F");
    outTree->Branch("x",&x,"x/F");
    outTree->Branch("y",&y,"y/F");
    outTree->Branch("z",&z,"z/F");
    outTree->Branch("Q2",&Q2,"Q2/F");
    outTree->Branch("pT",&pT,"pT/F");
    outTree->Branch("zeta",&zeta,"zeta/F");
    outTree->Branch("eta",&eta,"eta/F");
    outTree->Branch("phi",&phi,"phi/F");


//for(int k=0; k<9777418; k++){
//for(int k=0; k<16372460; k++){
//16372460 total number of events in Total-Eloss file 
// for(int k=0; k<6; k++){

// 10019 has 57938894 events 

for(int k=0; k<59019; k++){  // Determine the number of lines to scan in the text file

    fscanf(fp, "%f %f %f %f %f %f %f ", &runnum, &evnum, &helicity, &e_p, &e_theta, &e_phi, &vz_e);

    fscanf(fp, " %f %f %f %f %f %f %f %f ", &p_p, &p_theta, &p_phi, &vz_p, &Q2, &W, &Mx, &Mx2);

    fscanf(fp, " %f %f %f %f %f %f %f %f  ", &x, &y, &z, &xF, &pT, &zeta, &eta, &phi );


    outTree->Fill();

    }

outTree->Write();
fclose(fp);
hfile->Write();


///////////////////////////////////////////////////////////////
TCut NegHeli = ("helicity == -1");  // Negative helicity cut
TCut PosHeli = ("helicity == 1");  // Positive helicity cut
TCut Mxg1 = ("y<0.75");            // Cut applied to all cuts, change depending on parameters

char cut[20];
strcpy(cut, "1.0<Q2&&Q2<1.5");   // First cut applied on variable of focus, change for different variable

float start = 1.5;      // Larger value of first cut made on target variable
float end = 8.5;        // Number one increment greater than the larger value of the final cut (getting around the for-loop being not inclusive)
float increment = 0.5;  // Size of cut

float binmiddle; // Create variables for printing
float bin1;
float bin2;
//////////////////////////////////////////////////////////////////
TH1F*h67 = new TH1F("h67","h67",20, 0, 6.4);
outTree->Draw("phi>>h67");
//////////////////////////////////////////////////////////////////
FILE *outputfile;
	
	outputfile = fopen("FitMethodBinQ2.txt" , "wb");  // Text file to print to

	for (float j = start; j < end; j += increment) {  // Loop to run through the target variable cuts
		
        	TCut Q2cut = (cut);

        	TH1F*h1 = new TH1F("h1","h1",20, 0, 6.4);           // Histogram for positive helicity and other cuts
        	outTree->Draw("phi>>h1", PosHeli && Q2cut && Mxg1);

        	TH1F*h2 = new TH1F("h2","h2",20, 0, 6.4);           // Histogram for negative helicity and other cuts
        	outTree->Draw("phi>>h2", NegHeli && Q2cut && Mxg1);


		int N = h1->GetNbinsX() + 1;  // Loop to run through phi output for each target variable cut
		for(int i=0; i<N; ++i){

		binmiddle = h67->GetBinLowEdge(i)+h67->GetBinWidth(i)/2;
        	fprintf(outputfile, "%f \t", binmiddle);
		bin1 = h1->GetBinContent(i);
		fprintf(outputfile, "%f \t", bin1);
		bin2 = h2->GetBinContent(i);
		fprintf(outputfile, "%f \n", bin2);  }	
	
		sprintf(cut, "%f<Q2&&Q2<%f", j, j + increment);
		printf("%s \n", cut);
		
	}
fclose(outputfile);
 // }


}

///AVEPT N+ N-   
