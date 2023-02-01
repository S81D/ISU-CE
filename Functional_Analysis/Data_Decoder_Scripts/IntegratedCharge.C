// Test File -- Trying to fix the ordering of waveforms and fixing axis scaling


//Created on July 2020, Navaneeth Poonthottathil - This class reads
//the waveform and analyse it...

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

#include "TROOT.h"
#include "TMath.h"
#include "TApplication.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TGraph.h"
#include "TProfile2D.h"

using namespace std;

//global TApplication object declared here for simplicity
TApplication *theApp;


void StuckBitFrac_IC(std::string filename){
//void StuckBitFrac(){

	TFile *gOut;

                //ROI tr_rawdata variables
                unsigned short subrun, chan;

                //Constants
                const int numChan = 64;// Quad FE ASIC Board

                const int const_numSubrun = 36;
                const int maxSubrun = 36;
                double signalSizes[64];
                std::vector<unsigned short> *wf = 0;
                std::vector<unsigned short> wfAll[64][64];
                unsigned short subrunIn, chanIn;
                double baseMean = 0;
                double baseRms = 0;
                double mean = 0;
                double val=0;
                int count = 0;
                int cnt = 0;
                double rms = 0;
                std::vector<double> sig;
                unsigned int sigNum;
                double sigPeriod;
                double pulseStart;


                TGraph *gCh_1 = new TGraph();
                TGraph *gCh_2 = new TGraph();
                TGraph *gCh_3 = new TGraph();

                TGraph *gCh_4 = new TGraph();
                TGraph *gCh_5 = new TGraph();
                TGraph *gCh_6 = new TGraph();
                TGraph *gCh_7 = new TGraph();
                TGraph *gCh_8 = new TGraph();
                TGraph *gCh_9 = new TGraph();
                TGraph *gCh_10 = new TGraph();
                TGraph *gCh_11 = new TGraph();
                TGraph *gCh_12 = new TGraph();
                TGraph *gCh_13 = new TGraph();
                TGraph *gCh_14 = new TGraph();
                TGraph *gCh_15 = new TGraph();
                TGraph *gCh_16 = new TGraph();

		TGraph *gCh_17 = new TGraph();

                TGraph *gCh_18 = new TGraph();
                TGraph *gCh_19 = new TGraph();
                TGraph *gCh_20 = new TGraph();
                TGraph *gCh_21 = new TGraph();
                TGraph *gCh_22 = new TGraph();
                TGraph *gCh_23 = new TGraph();
                TGraph *gCh_24 = new TGraph();
                TGraph *gCh_25 = new TGraph();
                TGraph *gCh_26 = new TGraph();
                TGraph *gCh_27 = new TGraph();
                TGraph *gCh_28 = new TGraph();
                TGraph *gCh_29 = new TGraph();
                TGraph *gCh_30 = new TGraph();
                TGraph *gCh_31 = new TGraph();
                TGraph *gCh_32 = new TGraph();
                TGraph *gCh_33 = new TGraph();
                TGraph *gCh_34 = new TGraph();
                TGraph *gCh_35 = new TGraph();
                TGraph *gCh_36 = new TGraph();
                TGraph *gCh_37 = new TGraph();
                TGraph *gCh_38 = new TGraph();
                TGraph *gCh_39 = new TGraph();
                TGraph *gCh_40 = new TGraph();
                TGraph *gCh_41 = new TGraph();
                TGraph *gCh_42 = new TGraph();
                TGraph *gCh_43 = new TGraph();
                TGraph *gCh_44 = new TGraph();
                TGraph *gCh_45 = new TGraph();
                TGraph *gCh_46 = new TGraph();
                TGraph *gCh_47 = new TGraph();
                TGraph *gCh_48 = new TGraph();
                TGraph *gCh_49 = new TGraph();
                TGraph *gCh_50 = new TGraph();
                TGraph *gCh_51 = new TGraph();
                TGraph *gCh_52 = new TGraph();
                TGraph *gCh_53 = new TGraph();
                TGraph *gCh_54 = new TGraph();
                TGraph *gCh_55 = new TGraph();
                TGraph *gCh_56 = new TGraph();
                TGraph *gCh_57 = new TGraph();
                TGraph *gCh_58 = new TGraph();
                TGraph *gCh_59 = new TGraph();
                TGraph *gCh_60 = new TGraph();
                TGraph *gCh_61 = new TGraph();
                TGraph *gCh_62 = new TGraph();
                TGraph *gCh_63 = new TGraph();
                TGraph *gCh_64 = new TGraph();



//	TFile*  inputFile = TFile::Open("/dsk/1/tmp/coldelec/feasic/quadFeAsic/20210927T103232/gain_enc_sequence-g2s2b0-0000/gain_enc_sequence-g2s2b0-0000-20210927T103324-parseBinaryFile.root");	
		TFile* inputFile = TFile::Open(filename.c_str());

                TTree *T = (TTree*)inputFile->Get("femb_wfdata");
	




        Long64_t nEntries(T->GetEntries());

//      T->GetEntry(0);
//      double X[1000000],Y[25000];


        T->SetBranchAddress("wf", &wf);
        T->SetBranchAddress("chan", &chan);
        T->SetBranchAddress("subrun", &subrun);

        for(Long64_t entry(0);entry<8064;++entry){

        T->GetEntry(entry);

//      std::cout<< "channnel = "<< " " << chan <<std::endl;

        for( int s = 0 ; s < wf->size() ; s++ ) {

             if(wf->size() == 0)
                return;

        //      double value = wf->at(s);
              //if(  wf->at(s) < 10 ) continue;

              // to get the stuckbit. 

      //        if ( (wf->at(s) & 0x3F ) == 0x0 || (wf->at(s) & 0x3F ) == 0x3F) continue;

                if( chan==0){
                        gCh_1->SetPoint(gCh_1->GetN(),gCh_1->GetN(),wf->at(s));

                }


                if( chan==1){
                        gCh_2->SetPoint(gCh_2->GetN(),gCh_2->GetN(),wf->at(s));
                //        adc_1->Fill(wf->at(s));       
                }


                if( chan==2){
                        gCh_3->SetPoint(gCh_3->GetN(),gCh_3->GetN(),wf->at(s));
                }

                if( chan==3){
                        gCh_4->SetPoint(gCh_4->GetN(),gCh_4->GetN(),wf->at(s));
                }


		if( chan==4){
                        gCh_5->SetPoint(gCh_5->GetN(),gCh_5->GetN(),wf->at(s));
                }

                if( chan==5){
                        gCh_6->SetPoint(gCh_6->GetN(),gCh_6->GetN(),wf->at(s));
                }

                if( chan==6){
                        gCh_7->SetPoint(gCh_7->GetN(),gCh_7->GetN(),wf->at(s));
                }

                if( chan==7){
                        gCh_8->SetPoint(gCh_8->GetN(),gCh_8->GetN(),wf->at(s));
                }

                if( chan==8){
                        gCh_9->SetPoint(gCh_9->GetN(),gCh_9->GetN(),wf->at(s));
                }

                if( chan==9){
                        gCh_10->SetPoint(gCh_10->GetN(),gCh_10->GetN(),wf->at(s));
                }

                if( chan==10){
                        gCh_11->SetPoint(gCh_11->GetN(),gCh_11->GetN(),wf->at(s));
                }

                if( chan==11){
                        gCh_12->SetPoint(gCh_12->GetN(),gCh_12->GetN(),wf->at(s));
                }

                if( chan==12){
                        gCh_13->SetPoint(gCh_13->GetN(),gCh_13->GetN(),wf->at(s));
                }

                if( chan==13){
                        gCh_14->SetPoint(gCh_14->GetN(),gCh_14->GetN(),wf->at(s));
                }

                if( chan==14){
                        gCh_15->SetPoint(gCh_15->GetN(),gCh_15->GetN(),wf->at(s));
                }

                if( chan==15){
                        gCh_16->SetPoint(gCh_16->GetN(),gCh_16->GetN(),wf->at(s));
                }
		
		if( chan==16){
                        gCh_17->SetPoint(gCh_17->GetN(),gCh_17->GetN(),wf->at(s));
                }

                if( chan==17){
                        gCh_18->SetPoint(gCh_18->GetN(),gCh_18->GetN(),wf->at(s));
                }

                if( chan==18){
                        gCh_19->SetPoint(gCh_19->GetN(),gCh_19->GetN(),wf->at(s));
                //      adc_1->Fill(wf->at(s));
                }

                if( chan==19){
                        gCh_20->SetPoint(gCh_20->GetN(),gCh_20->GetN(),wf->at(s));
                }

                if( chan==20){
                        gCh_21->SetPoint(gCh_21->GetN(),gCh_21->GetN(),wf->at(s));
                }

                if( chan==21){
                        gCh_22->SetPoint(gCh_22->GetN(),gCh_22->GetN(),wf->at(s));
                }


                if( chan==22){
                        gCh_23->SetPoint(gCh_23->GetN(),gCh_23->GetN(),wf->at(s));
                }

                if( chan==23){
                        gCh_24->SetPoint(gCh_24->GetN(),gCh_24->GetN(),wf->at(s));
                }

                if( chan==24){
                        gCh_25->SetPoint(gCh_25->GetN(),gCh_25->GetN(),wf->at(s));
                }

                if( chan==25){
                        gCh_26->SetPoint(gCh_26->GetN(),gCh_26->GetN(),wf->at(s));
                }

                if( chan==26){
                        gCh_27->SetPoint(gCh_27->GetN(),gCh_27->GetN(),wf->at(s));
                }
		
		if( chan==27){
                        gCh_28->SetPoint(gCh_28->GetN(),gCh_28->GetN(),wf->at(s));
                }

                if( chan==28){
                        gCh_29->SetPoint(gCh_29->GetN(),gCh_29->GetN(),wf->at(s));
                }

                if( chan==29){
                        gCh_30->SetPoint(gCh_30->GetN(),gCh_30->GetN(),wf->at(s));
                }

                if( chan==30){
                        gCh_31->SetPoint(gCh_31->GetN(),gCh_31->GetN(),wf->at(s));
                }

                if( chan==31){
                        gCh_32->SetPoint(gCh_32->GetN(),gCh_32->GetN(),wf->at(s));
                }

                if( chan==32){
                        gCh_33->SetPoint(gCh_33->GetN(),gCh_33->GetN(),wf->at(s));

                }

                if( chan==33){
                        gCh_34->SetPoint(gCh_34->GetN(),gCh_34->GetN(),wf->at(s));
                }

                if( chan==34){
                        gCh_35->SetPoint(gCh_35->GetN(),gCh_35->GetN(),wf->at(s));
                }

                if( chan==35){
                        gCh_36->SetPoint(gCh_36->GetN(),gCh_36->GetN(),wf->at(s));
                }

                if( chan==36){
                        gCh_37->SetPoint(gCh_37->GetN(),gCh_37->GetN(),wf->at(s));
                }

                if( chan==37){
                        gCh_38->SetPoint(gCh_38->GetN(),gCh_38->GetN(),wf->at(s));
                }

                if( chan==38){
                        gCh_39->SetPoint(gCh_39->GetN(),gCh_39->GetN(),wf->at(s));
                }
		
		if( chan==39){
                        gCh_40->SetPoint(gCh_40->GetN(),gCh_40->GetN(),wf->at(s));
                }

                if( chan==40){
                        gCh_41->SetPoint(gCh_41->GetN(),gCh_41->GetN(),wf->at(s));
                }

                if( chan==41){
                        gCh_42->SetPoint(gCh_42->GetN(),gCh_42->GetN(),wf->at(s));
                //      adc_1->Fill(wf->at(s));
                }


                if( chan==42){
                        gCh_43->SetPoint(gCh_43->GetN(),gCh_43->GetN(),wf->at(s));
                }

                if( chan==43){
                        gCh_44->SetPoint(gCh_44->GetN(),gCh_44->GetN(),wf->at(s));
                }

                if( chan==44){
                        gCh_45->SetPoint(gCh_45->GetN(),gCh_45->GetN(),wf->at(s));
                }

                if( chan==45){
                        gCh_46->SetPoint(gCh_46->GetN(),gCh_46->GetN(),wf->at(s));
                }

                if( chan==46){
                        gCh_47->SetPoint(gCh_47->GetN(),gCh_47->GetN(),wf->at(s));
                }

                if( chan==47){
                        gCh_48->SetPoint(gCh_48->GetN(),gCh_48->GetN(),wf->at(s));
                }

                if( chan==48){
                        gCh_49->SetPoint(gCh_49->GetN(),gCh_49->GetN(),wf->at(s));
                }

                if( chan==49){
                        gCh_50->SetPoint(gCh_50->GetN(),gCh_50->GetN(),wf->at(s));
                }

                if( chan==50){
                        gCh_51->SetPoint(gCh_51->GetN(),gCh_51->GetN(),wf->at(s));
                }

		if( chan==51){
                        gCh_52->SetPoint(gCh_52->GetN(),gCh_52->GetN(),wf->at(s));
                }

                if( chan==52){
                        gCh_53->SetPoint(gCh_53->GetN(),gCh_53->GetN(),wf->at(s));
                }

                if( chan==53){
                        gCh_54->SetPoint(gCh_54->GetN(),gCh_54->GetN(),wf->at(s));
                }

                if( chan==54){
                        gCh_55->SetPoint(gCh_55->GetN(),gCh_55->GetN(),wf->at(s));
                }

                if( chan==55){
                        gCh_56->SetPoint(gCh_56->GetN(),gCh_56->GetN(),wf->at(s));
                }

                if( chan==56){
                        gCh_57->SetPoint(gCh_57->GetN(),gCh_57->GetN(),wf->at(s));
                }

                if( chan==57){
                        gCh_58->SetPoint(gCh_58->GetN(),gCh_58->GetN(),wf->at(s));
                }

                if( chan==58){
                        gCh_59->SetPoint(gCh_59->GetN(),gCh_59->GetN(),wf->at(s));
                }

                if( chan==59){
                        gCh_60->SetPoint(gCh_60->GetN(),gCh_60->GetN(),wf->at(s));
                }

                if( chan==60){
                        gCh_61->SetPoint(gCh_61->GetN(),gCh_61->GetN(),wf->at(s));
                }

                if( chan==61){
                        gCh_62->SetPoint(gCh_62->GetN(),gCh_62->GetN(),wf->at(s));
                }


                if( chan==62){
                        gCh_63->SetPoint(gCh_63->GetN(),gCh_63->GetN(),wf->at(s));
                }

                if( chan==63){
                        gCh_64->SetPoint(gCh_64->GetN(),gCh_64->GetN(),wf->at(s));
                }

				
		 }



        }

               TFile *MyFile = new TFile("test_graph.root","RECREATE");
               gCh_1->Write("Graph_0");
               gCh_2->Write("Graph_1");
               gCh_3->Write("Graph_2");
               gCh_4->Write("Graph_3");
               gCh_5->Write("Graph_4");
               gCh_6->Write("Graph_5");
               gCh_7->Write("Graph_6");
               gCh_8->Write("Graph_7");
               gCh_9->Write("Graph_8");
               gCh_10->Write("Graph_9");
               gCh_11->Write("Graph_10");
               gCh_12->Write("Graph_11");
               gCh_13->Write("Graph_12");
               gCh_14->Write("Graph_13");
               gCh_15->Write("Graph_14");
               gCh_16->Write("Graph_15");

	       gCh_17->Write("Graph_16");
               gCh_18->Write("Graph_17");
               gCh_19->Write("Graph_18");
               gCh_20->Write("Graph_19");
               gCh_21->Write("Graph_20");
               gCh_22->Write("Graph_21");
               gCh_23->Write("Graph_22");
               gCh_24->Write("Graph_23");
               gCh_25->Write("Graph_24");
               gCh_26->Write("Graph_25");
               gCh_27->Write("Graph_26");
               gCh_28->Write("Graph_27");
               gCh_29->Write("Graph_28");
               gCh_30->Write("Graph_29");
               gCh_31->Write("Graph_30");
               gCh_32->Write("Graph_31");
               gCh_33->Write("Graph_32");
               gCh_34->Write("Graph_33");
               gCh_35->Write("Graph_34");
               gCh_36->Write("Graph_35");
               gCh_37->Write("Graph_36");
               gCh_38->Write("Graph_37");
               gCh_39->Write("Graph_38");
               gCh_40->Write("Graph_39");
               gCh_41->Write("Graph_40");
               gCh_42->Write("Graph_41");
               gCh_43->Write("Graph_42");
               gCh_44->Write("Graph_43");
               gCh_45->Write("Graph_44");
               gCh_46->Write("Graph_45");
               gCh_47->Write("Graph_46");
               gCh_48->Write("Graph_47");
               gCh_49->Write("Graph_48");
               gCh_50->Write("Graph_49");
               gCh_51->Write("Graph_50");
               gCh_52->Write("Graph_51");
               gCh_53->Write("Graph_52");
               gCh_54->Write("Graph_53");
               gCh_55->Write("Graph_54");
               gCh_56->Write("Graph_55");
               gCh_57->Write("Graph_56");
               gCh_58->Write("Graph_57");
               gCh_59->Write("Graph_58");
               gCh_60->Write("Graph_59");
               gCh_61->Write("Graph_60");
               gCh_62->Write("Graph_61");
               gCh_63->Write("Graph_62");
               gCh_64->Write("Graph_63");

               MyFile->Close();


               std::cout<< "done" <<std::endl;
        }




void ReadGraph_test_IC(){

       // We wish to pull one subrun from each of the subsequent channels
        // in the functional test

  TFile *f = TFile::Open("test_graph.root");
  f->ls();
  TCanvas *c;
  f->GetObject("c1", c);

  TGraph* g0 = (TGraph*)f->Get("Graph_0");
  TGraph* g1 = (TGraph*)f->Get("Graph_1");
  TGraph* g2 = (TGraph*)f->Get("Graph_2");
  TGraph* g3 = (TGraph*)f->Get("Graph_3");
  TGraph* g4 = (TGraph*)f->Get("Graph_4");
  TGraph* g5 = (TGraph*)f->Get("Graph_5");
  TGraph* g6 = (TGraph*)f->Get("Graph_6");
  TGraph* g7 = (TGraph*)f->Get("Graph_7");
  TGraph* g8 = (TGraph*)f->Get("Graph_8");
  TGraph* g9 = (TGraph*)f->Get("Graph_9");
  TGraph* g10 = (TGraph*)f->Get("Graph_10");
  TGraph* g11 = (TGraph*)f->Get("Graph_11");
  TGraph* g12 = (TGraph*)f->Get("Graph_12");
  TGraph* g13 = (TGraph*)f->Get("Graph_13");
  TGraph* g14 = (TGraph*)f->Get("Graph_14");
  TGraph* g15 = (TGraph*)f->Get("Graph_15");
  TGraph* g16 = (TGraph*)f->Get("Graph_16");
  TGraph* g17 = (TGraph*)f->Get("Graph_17");
  TGraph* g18 = (TGraph*)f->Get("Graph_18");
  TGraph* g19 = (TGraph*)f->Get("Graph_19");
  TGraph* g20 = (TGraph*)f->Get("Graph_20");
  TGraph* g21 = (TGraph*)f->Get("Graph_21");
  TGraph* g22 = (TGraph*)f->Get("Graph_22");
  TGraph* g23 = (TGraph*)f->Get("Graph_23");
  TGraph* g24 = (TGraph*)f->Get("Graph_24");
  TGraph* g25 = (TGraph*)f->Get("Graph_25");
  TGraph* g26 = (TGraph*)f->Get("Graph_26");
  TGraph* g27 = (TGraph*)f->Get("Graph_27");
  TGraph* g28 = (TGraph*)f->Get("Graph_28");
  TGraph* g29 = (TGraph*)f->Get("Graph_29");
  TGraph* g30 = (TGraph*)f->Get("Graph_30");
  TGraph* g31 = (TGraph*)f->Get("Graph_31");
  TGraph* g32 = (TGraph*)f->Get("Graph_32");
  TGraph* g33 = (TGraph*)f->Get("Graph_33");
  TGraph* g34 = (TGraph*)f->Get("Graph_34");
  TGraph* g35 = (TGraph*)f->Get("Graph_35");
  TGraph* g36 = (TGraph*)f->Get("Graph_36");
  TGraph* g37 = (TGraph*)f->Get("Graph_37");
  TGraph* g38 = (TGraph*)f->Get("Graph_38");
  TGraph* g39 = (TGraph*)f->Get("Graph_39");
  TGraph* g40 = (TGraph*)f->Get("Graph_40");
  TGraph* g41 = (TGraph*)f->Get("Graph_41");
  TGraph* g42 = (TGraph*)f->Get("Graph_42");
  TGraph* g43 = (TGraph*)f->Get("Graph_43");
  TGraph* g44 = (TGraph*)f->Get("Graph_44");
  TGraph* g45 = (TGraph*)f->Get("Graph_45");
  TGraph* g46 = (TGraph*)f->Get("Graph_46");
  TGraph* g47 = (TGraph*)f->Get("Graph_47");
  TGraph* g48 = (TGraph*)f->Get("Graph_48");
  TGraph* g49 = (TGraph*)f->Get("Graph_49");
  TGraph* g50 = (TGraph*)f->Get("Graph_50");
  TGraph* g51 = (TGraph*)f->Get("Graph_51");
  TGraph* g52 = (TGraph*)f->Get("Graph_52");
  TGraph* g53 = (TGraph*)f->Get("Graph_53");
  TGraph* g54 = (TGraph*)f->Get("Graph_54");
  TGraph* g55 = (TGraph*)f->Get("Graph_55");
  TGraph* g56 = (TGraph*)f->Get("Graph_56");
  TGraph* g57 = (TGraph*)f->Get("Graph_57");
  TGraph* g58 = (TGraph*)f->Get("Graph_58");
  TGraph* g59 = (TGraph*)f->Get("Graph_59");
  TGraph* g60 = (TGraph*)f->Get("Graph_60");
  TGraph* g61 = (TGraph*)f->Get("Graph_61");
  TGraph* g62 = (TGraph*)f->Get("Graph_62");
  TGraph* g63 = (TGraph*)f->Get("Graph_63"); 


  ofstream myfile_1;
  myfile_1.open ("example1.dat");

  // Full 35 subruns (889000 counts)
  // Last few subruns saturate - so only pull up to Subrun 32 (533400)
  // Subrun 20 --> [508000:533400]
  for (int i = 0; i <g0-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g0->GetX()[i] << " " << g0->GetY()[i] <<" 0\n"; //write to file
  }
  }

  for (int i = 0; i <g1-> GetN(); i++){
   if(i>507999 && i<533400){                         // Include column for channel #
           myfile_1 << g1->GetX()[i] << " " << g1->GetY()[i] <<" 1\n"; //write to file
  }
  }
  for (int i = 0; i <g2-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g2->GetX()[i] << " " << g2->GetY()[i] <<" 2\n"; //write to file
  }
  }
  for (int i = 0; i <g3-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g3->GetX()[i] << " " << g3->GetY()[i] <<" 3\n"; //write to file
  }
  }
  for (int i = 0; i <g4-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g4->GetX()[i] << " " << g4->GetY()[i] <<" 4\n"; //write to file
  }
  }
  for (int i = 0; i <g5-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g5->GetX()[i] << " " << g5->GetY()[i] <<" 5\n"; //write to file
  }
  }
  for (int i = 0; i <g6-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g6->GetX()[i] << " " << g6->GetY()[i] <<" 6\n"; //write to file
  }
  }
  for (int i = 0; i <g7-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g7->GetX()[i] << " " << g7->GetY()[i] <<" 7\n"; //write to file
  }
  }
  for (int i = 0; i <g8-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g8->GetX()[i] << " " << g8->GetY()[i] <<" 8\n"; //write to file
  }
  }
  for (int i = 0; i <g9-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g9->GetX()[i] << " " << g9->GetY()[i] <<" 9\n"; //write to file
  }
  }

  for (int i = 0; i <g10-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g10->GetX()[i] << " " << g10->GetY()[i] <<" 10\n"; //write to file
  }
  }
  for (int i = 0; i <g11-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g11->GetX()[i] << " " << g11->GetY()[i] <<" 11\n"; //write to file
  }
  }
  for (int i = 0; i <g12-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g12->GetX()[i] << " " << g12->GetY()[i] <<" 12\n"; //write to file
  }
  }
  for (int i = 0; i <g13-> GetN(); i++){
    if(i>507999 && i<533400){
           myfile_1 << g13->GetX()[i] << " " << g13->GetY()[i] <<" 13\n"; //write to file
  }
  }
  for (int i = 0; i <g14-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g14->GetX()[i] << " " << g14->GetY()[i] <<" 14\n"; //write to file
  }
  }
  for (int i = 0; i <g15-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g15->GetX()[i] << " " << g15->GetY()[i] <<" 15\n"; //write to file
  }
  }
  for (int i = 0; i <g16-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g16->GetX()[i] << " " << g16->GetY()[i] <<" 16\n"; //write to file
  }
  }
  for (int i = 0; i <g17-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g17->GetX()[i] << " " << g17->GetY()[i] <<" 17\n"; //write to file
  }
  }
   for (int i = 0; i <g18-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g18->GetX()[i] << " " << g18->GetY()[i] <<" 18\n"; //write to file
  }
  }
  for (int i = 0; i <g19-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g19->GetX()[i] << " " << g19->GetY()[i] <<" 19\n"; //write to file
  }
  }

  for (int i = 0; i <g20-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g20->GetX()[i] << " " << g20->GetY()[i] <<" 20\n"; //write to file
  }
  }
  for (int i = 0; i <g21-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g21->GetX()[i] << " " << g21->GetY()[i] <<" 21\n"; //write to file
  }
  }
  for (int i = 0; i <g22-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g22->GetX()[i] << " " << g22->GetY()[i] <<" 22\n"; //write to file
  }
  }
  for (int i = 0; i <g23-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g23->GetX()[i] << " " << g23->GetY()[i] <<" 23\n"; //write to file
  }
  }
  for (int i = 0; i <g24-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g24->GetX()[i] << " " << g24->GetY()[i] <<" 24\n"; //write to file
  }
  }
  for (int i = 0; i <g25-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g25->GetX()[i] << " " << g25->GetY()[i] <<" 25\n"; //write to file
  }
  }
  for (int i = 0; i <g26-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g26->GetX()[i] << " " << g26->GetY()[i] <<" 26\n"; //write to file
  }
  }
  for (int i = 0; i <g27-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g27->GetX()[i] << " " << g27->GetY()[i] <<" 27\n"; //write to file
  }
  }
  for (int i = 0; i <g28-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g28->GetX()[i] << " " << g28->GetY()[i] <<" 28\n"; //write to file
  }
  }
  for (int i = 0; i <g29-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g29->GetX()[i] << " " << g29->GetY()[i] <<" 29\n"; //write to file
  }
  }

  for (int i = 0; i <g30-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g30->GetX()[i] << " " << g30->GetY()[i] <<" 30\n"; //write to file
  }
  }
  for (int i = 0; i <g31-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g31->GetX()[i] << " " << g31->GetY()[i] <<" 31\n"; //write to file
  }
  }
  for (int i = 0; i <g32-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g32->GetX()[i] << " " << g32->GetY()[i] <<" 32\n"; //write to file
  }
  }
  for (int i = 0; i <g33-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g33->GetX()[i] << " " << g33->GetY()[i] <<" 33\n"; //write to file
  }
  }
  for (int i = 0; i <g34-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g34->GetX()[i] << " " << g34->GetY()[i] <<" 34\n"; //write to file
  }
  }
  for (int i = 0; i <g35-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g35->GetX()[i] << " " << g35->GetY()[i] <<" 35\n"; //write to file
  }
  }
  for (int i = 0; i <g36-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g36->GetX()[i] << " " << g36->GetY()[i] <<" 36\n"; //write to file
  }
  }
  for (int i = 0; i <g37-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g37->GetX()[i] << " " << g37->GetY()[i] <<" 37\n"; //write to file
   }
  }
  for (int i = 0; i <g38-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g38->GetX()[i] << " " << g38->GetY()[i] <<" 38\n"; //write to file
  }
  }
  for (int i = 0; i <g39-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g39->GetX()[i] << " " << g39->GetY()[i] <<" 39\n"; //write to file
  }
  }

  for (int i = 0; i <g40-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g40->GetX()[i] << " " << g40->GetY()[i] <<" 40\n"; //write to file
  }
  }
  for (int i = 0; i <g41-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g41->GetX()[i] << " " << g41->GetY()[i] <<" 41\n"; //write to file
  }
  }
  for (int i = 0; i <g42-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g42->GetX()[i] << " " << g42->GetY()[i] <<" 42\n"; //write to file
  }
  }
  for (int i = 0; i <g43-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g43->GetX()[i] << " " << g43->GetY()[i] <<" 43\n"; //write to file
  }
  }
  for (int i = 0; i <g44-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g44->GetX()[i] << " " << g44->GetY()[i] <<" 44\n"; //write to file
  }
  }
  for (int i = 0; i <g45-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g45->GetX()[i] << " " << g45->GetY()[i] <<" 45\n"; //write to file
  }
  }
  for (int i = 0; i <g46-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g46->GetX()[i] << " " << g46->GetY()[i] <<" 46\n"; //write to file
  }
  }
  for (int i = 0; i <g47-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g47->GetX()[i] << " " << g47->GetY()[i] <<" 47\n"; //write to file
   }
  }
  for (int i = 0; i <g48-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g48->GetX()[i] << " " << g48->GetY()[i] <<" 48\n"; //write to file
  }
  }
  for (int i = 0; i <g49-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g49->GetX()[i] << " " << g49->GetY()[i] <<" 49\n"; //write to file
  }
  }

  for (int i = 0; i <g50-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g50->GetX()[i] << " " << g50->GetY()[i] <<" 50\n"; //write to file
  }
  }
  for (int i = 0; i <g51-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g51->GetX()[i] << " " << g51->GetY()[i] <<" 51\n"; //write to file
  }
  }
  for (int i = 0; i <g52-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g52->GetX()[i] << " " << g52->GetY()[i] <<" 52\n"; //write to file
  }
  }
  for (int i = 0; i <g53-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g53->GetX()[i] << " " << g53->GetY()[i] <<" 53\n"; //write to file
  }
  }
  for (int i = 0; i <g54-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g54->GetX()[i] << " " << g54->GetY()[i] <<" 54\n"; //write to file
  }
  }
  for (int i = 0; i <g55-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g55->GetX()[i] << " " << g55->GetY()[i] <<" 55\n"; //write to file
  }
  }
  for (int i = 0; i <g56-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g56->GetX()[i] << " " << g56->GetY()[i] <<" 56\n"; //write to file
  }
  }
  for (int i = 0; i <g57-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g57->GetX()[i] << " " << g57->GetY()[i] <<" 57\n"; //write to file
   }
  }
  for (int i = 0; i <g58-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g58->GetX()[i] << " " << g58->GetY()[i] <<" 58\n"; //write to file
  }
  }
  for (int i = 0; i <g59-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g59->GetX()[i] << " " << g59->GetY()[i] <<" 59\n"; //write to file
  }
  }

  for (int i = 0; i <g60-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g60->GetX()[i] << " " << g60->GetY()[i] <<" 60\n"; //write to file
  }
  }
  for (int i = 0; i <g61-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g61->GetX()[i] << " " << g61->GetY()[i] <<" 61\n"; //write to file
  }
  }
  for (int i = 0; i <g62-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g62->GetX()[i] << " " << g62->GetY()[i] <<" 62\n"; //write to file
  }
  }
  for (int i = 0; i <g63-> GetN(); i++){
   if(i>507999 && i<533400){
           myfile_1 << g63->GetX()[i] << " " << g63->GetY()[i] <<" 63\n"; //write to file
  }
  }




  myfile_1.close();
 

	cout << "\ndone\n";

}


void run(std::string name){

const char *s = name.c_str();	

	StuckBitFrac_IC(s);
	ReadGraph_test_IC();

}

