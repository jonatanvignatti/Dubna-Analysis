#include <iostream>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

void treeplotter(){
	TFile *f=new TFile("electrontree.root","read");
	TTree *t1=(TTree*)f->Get("t1");
	float dedx[12]={};
	float tr[12]={};
	float total[12]={};
	float momentum;
	//float dedx,tr,total,momentum;
	t1->SetBranchAddress("dedx",&dedx);
	t1->SetBranchAddress("tr",&tr);
	t1->SetBranchAddress("total",&total);
	t1->SetBranchAddress("momentum",&momentum);
	TH1F *energylosses=new TH1F("energylosses","ELECTRON ENERGY LOSSES",100,0,50);
	int nentries=(int)t1->GetEntries();
	//cout<<"\n"<<nentries<<"\n";
	for (int i=0;i<nentries;i++){
		t1->GetEntry(i);
			//for(int a=0;a<12;a++){
		energylosses->Fill(total[11]);
				//}
		//cout<<total<<"\n";
	}
	TCanvas *c1=new TCanvas("c1","Electron Energy Losses");
	energylosses->Draw();
	c1->SaveAs("electronenergylosses.pdf");
}