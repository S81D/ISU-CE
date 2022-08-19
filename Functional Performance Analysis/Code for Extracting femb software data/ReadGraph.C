#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include <fstream>
using namespace std;

void ReadGraph()
{
  TFile *f = TFile::Open("test_graph105CT.root");
  f->ls();
  TCanvas *c; 
  f->GetObject("c1", c);
//  c->ls();
  //TGraph *g = ((TGraph *)(c->FindObject("Graph_32")));
 
  TGraph* g = (TGraph*)f->Get("Graph_27");
  //TGraph *g = (TFile *f(c->FindObject("Graph_32")));
  // g->Print();
  
  ofstream myfile;
  myfile.open ("example_CT_nan.txt");
  myfile << "TS ns nserr\n";
 
  ofstream myfile_1;
  myfile_1.open ("example_CT_3.txt");
  myfile_1 << "TS ns nserr\n"; 

  for (int i = 0; i <g-> GetN(); i++){
 // for (int i = 0; i < g->GetN(); i++)
    //std::cout << i << " " << g->GetX()[i] << " " << g->GetY()[i] << std::endl;

   if(i<25400){
	   myfile << g->GetX()[i] << " " << g->GetY()[i] <<"\n"; //write to file
   }

   if(i>25399 && i<50000){
           myfile_1 << g->GetX()[i] << " " << g->GetY()[i] <<"\n"; //write to file
  }



  }

  myfile.close();
  myfile_1.close();
}
