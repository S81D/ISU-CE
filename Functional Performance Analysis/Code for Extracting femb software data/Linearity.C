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


void StuckBitFrac_Lin(std::string filename){
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
              // MyFile->Close();

              // TFile *MyFile = new TFile("test_graph.root","RECREATE");
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




void findmaxtest_Lin(){


TGraph *GR0a= new TGraph();
TGraph *GR1a= new TGraph();
TGraph *GR2a = new TGraph();
TGraph *GR3a= new TGraph();
TGraph *GR4a= new TGraph();
TGraph *GR5a= new TGraph();
TGraph *GR6a= new TGraph();
TGraph *GR7a= new TGraph();
TGraph *GR8a= new TGraph();
TGraph *GR9a= new TGraph();
TGraph *GR10a= new TGraph();
TGraph *GR11a= new TGraph();
TGraph *GR12a= new TGraph();
TGraph *GR13a= new TGraph();
TGraph *GR14a= new TGraph();
TGraph *GR15a= new TGraph();
TGraph *GR16a= new TGraph();
TGraph *GR17a= new TGraph();
TGraph *GR18a = new TGraph();
TGraph *GR19a= new TGraph();
TGraph *GR20a= new TGraph();
TGraph *GR21a= new TGraph();
TGraph *GR22a= new TGraph();
TGraph *GR23a= new TGraph();
TGraph *GR24a= new TGraph();
TGraph *GR25a= new TGraph();
TGraph *GR26a= new TGraph();
TGraph *GR27a= new TGraph();
TGraph *GR28a= new TGraph();
TGraph *GR29a= new TGraph();
TGraph *GR30a= new TGraph();
TGraph *GR31a= new TGraph();
TGraph *GR32a= new TGraph();
TGraph *GR33a= new TGraph();
TGraph *GR34a = new TGraph();
TGraph *GR35a= new TGraph();
TGraph *GR36a= new TGraph();
TGraph *GR37a= new TGraph();
TGraph *GR38a= new TGraph();
TGraph *GR39a= new TGraph();
TGraph *GR40a= new TGraph();
TGraph *GR41a= new TGraph();
TGraph *GR42a= new TGraph();
TGraph *GR43a= new TGraph();
TGraph *GR44a= new TGraph();
TGraph *GR45a= new TGraph();
TGraph *GR46a= new TGraph();
TGraph *GR47a= new TGraph();
TGraph *GR48a= new TGraph();
TGraph *GR49a= new TGraph();
TGraph *GR50a = new TGraph();
TGraph *GR51a= new TGraph();
TGraph *GR52a= new TGraph();
TGraph *GR53a= new TGraph();
TGraph *GR54a= new TGraph();
TGraph *GR55a= new TGraph();
TGraph *GR56a= new TGraph();
TGraph *GR57a= new TGraph();
TGraph *GR58a= new TGraph();
TGraph *GR59a= new TGraph();
TGraph *GR60a= new TGraph();
TGraph *GR61a= new TGraph();
TGraph *GR62a= new TGraph();
TGraph *GR63a= new TGraph();


TGraph *GR0b= new TGraph();
TGraph *GR1b= new TGraph();
TGraph *GR2b= new TGraph();
TGraph *GR3b= new TGraph();
TGraph *GR4b= new TGraph();
TGraph *GR5b= new TGraph();
TGraph *GR6b= new TGraph();
TGraph *GR7b= new TGraph();
TGraph *GR8b= new TGraph();
TGraph *GR9b= new TGraph();
TGraph *GR10b= new TGraph();
TGraph *GR11b= new TGraph();
TGraph *GR12b= new TGraph();
TGraph *GR13b = new TGraph();
TGraph *GR14b= new TGraph();
TGraph *GR15b= new TGraph();
TGraph *GR16b= new TGraph();
TGraph *GR17b= new TGraph();
TGraph *GR18b = new TGraph();
TGraph *GR19b= new TGraph();
TGraph *GR20b= new TGraph();
TGraph *GR21b= new TGraph();
TGraph *GR22b= new TGraph();
TGraph *GR23b= new TGraph();
TGraph *GR24b= new TGraph();
TGraph *GR25b= new TGraph();
TGraph *GR26b= new TGraph();
TGraph *GR27b= new TGraph();
TGraph *GR28b= new TGraph();
TGraph *GR29b= new TGraph();
TGraph *GR30b= new TGraph();
TGraph *GR31b= new TGraph();
TGraph *GR32b= new TGraph();
TGraph *GR33b= new TGraph();
TGraph *GR34b = new TGraph();
TGraph *GR35b= new TGraph();
TGraph *GR36b= new TGraph();
TGraph *GR37b= new TGraph();
TGraph *GR38b= new TGraph();
TGraph *GR39b= new TGraph();
TGraph *GR40b= new TGraph();
TGraph *GR41b= new TGraph();
TGraph *GR42b= new TGraph();
TGraph *GR43b= new TGraph();
TGraph *GR44b= new TGraph();
TGraph *GR45b= new TGraph();
TGraph *GR46b= new TGraph();
TGraph *GR47b= new TGraph();
TGraph *GR48b= new TGraph();
TGraph *GR49b= new TGraph();
TGraph *GR50b = new TGraph();
TGraph *GR51b= new TGraph();
TGraph *GR52b= new TGraph();
TGraph *GR53b= new TGraph();
TGraph *GR54b= new TGraph();
TGraph *GR55b= new TGraph();
TGraph *GR56b= new TGraph();
TGraph *GR57b= new TGraph();
TGraph *GR58b= new TGraph();
TGraph *GR59b= new TGraph();
TGraph *GR60b= new TGraph();
TGraph *GR61b= new TGraph();
TGraph *GR62b= new TGraph();
TGraph *GR63b= new TGraph();


		 // TFile* GraphFile = TFile::Open(graphname.c_str());
                  TFile* GraphFile = TFile::Open("test_graph.root");

TList *l = gDirectory->GetListOfKeys();


 for (Int_t i = 0; i < l->GetSize(); i++) ((TKey *)(l->At(i)))->ls();

   TGraph *g = 0;

   for (Int_t u = 0; u< l->GetSize(); u++) {
        TKey *k = ((TKey *)(l->At(u)));
       if (TString("TGraph").EqualTo(k->GetClassName())) {
        g = dynamic_cast<TGraph *>(k->ReadObj());





//      std::cout<< "Number of Points  " << g->GetN() <<std::endl;    
    Double_t x, y;
    g->GetPoint(0, x, y);
    Double_t max_x = x, max_y = y;
    for(int i = 1; i < g->GetN(); i++)
    {
         g->GetPoint(i, x, y);

         if(y > max_y) {
           max_x = x;
           max_y = y;

//      

        }

//


if(u==0){
     GR0a->SetPoint(GR0a->GetN(),GR0a->GetN()/25200,max_y);
}

if(u==1){
     GR1a->SetPoint(GR1a->GetN(),GR1a->GetN()/25200,max_y);
}

if(u==2){
     GR2a->SetPoint(GR2a->GetN(),GR2a->GetN()/25200,max_y);
}

if(u==3){
     GR3a->SetPoint(GR3a->GetN(),GR3a->GetN()/25200,max_y);
}

if(u==4){
     GR4a->SetPoint(GR4a->GetN(),GR4a->GetN()/25200,max_y);
}

if(u==5){
     GR5a->SetPoint(GR5a->GetN(),GR5a->GetN()/25200,max_y);
}

if(u==6){
     GR6a->SetPoint(GR6a->GetN(),GR6a->GetN()/25200,max_y);
}

if(u==7){
     GR7a->SetPoint(GR7a->GetN(),GR7a->GetN()/25200,max_y);
}

if(u==8){
     GR8a->SetPoint(GR8a->GetN(),GR8a->GetN()/25200,max_y);
}

if(u==9){
     GR9a->SetPoint(GR9a->GetN(),GR9a->GetN()/25200,max_y);
}

if(u==10){
     GR10a->SetPoint(GR10a->GetN(),GR10a->GetN()/25200,max_y);
}

if(u==11){
     GR11a->SetPoint(GR11a->GetN(),GR11a->GetN()/25200,max_y);
}

if(u==12){
     GR12a->SetPoint(GR12a->GetN(),GR12a->GetN()/25200,max_y);
}

if(u==13){
     GR13a->SetPoint(GR13a->GetN(),GR13a->GetN()/25200,max_y);
}
if(u==14){
     GR14a->SetPoint(GR14a->GetN(),GR14a->GetN()/25200,max_y);
}

if(u==15){
     GR15a->SetPoint(GR15a->GetN(),GR15a->GetN()/25200,max_y);
}

if(u==16){
     GR16a->SetPoint(GR16a->GetN(),GR16a->GetN()/25200,max_y);
}

if(u==17){
     GR17a->SetPoint(GR17a->GetN(),GR17a->GetN()/25200,max_y);
}

if(u==18){
     GR18a->SetPoint(GR18a->GetN(),GR18a->GetN()/25200,max_y);
}

if(u==19){
     GR19a->SetPoint(GR19a->GetN(),GR19a->GetN()/25200,max_y);
}

if(u==20){
     GR20a->SetPoint(GR20a->GetN(),GR20a->GetN()/25200,max_y);
}

if(u==21){
     GR21a->SetPoint(GR21a->GetN(),GR21a->GetN()/25200,max_y);
}

if(u==22){
     GR22a->SetPoint(GR22a->GetN(),GR22a->GetN()/25200,max_y);
}

if(u==23){
     GR23a->SetPoint(GR23a->GetN(),GR23a->GetN()/25200,max_y);
}

if(u==24){
     GR24a->SetPoint(GR24a->GetN(),GR24a->GetN()/25200,max_y);
}

if(u==25){
     GR25a->SetPoint(GR25a->GetN(),GR25a->GetN()/25200,max_y);
}

if(u==26){
     GR26a->SetPoint(GR26a->GetN(),GR26a->GetN()/25200,max_y);
}

if(u==27){
     GR27a->SetPoint(GR27a->GetN(),GR27a->GetN()/25200,max_y);
}

if(u==28){
     GR28a->SetPoint(GR28a->GetN(),GR28a->GetN()/25200,max_y);
}

if(u==29){
     GR29a->SetPoint(GR29a->GetN(),GR29a->GetN()/25200,max_y);
}

if(u==30){
     GR30a->SetPoint(GR30a->GetN(),GR30a->GetN()/25200,max_y);
}

if(u==31){
     GR31a->SetPoint(GR31a->GetN(),GR31a->GetN()/25200,max_y);
}

if(u==32){
     GR32a->SetPoint(GR32a->GetN(),GR32a->GetN()/25200,max_y);
}

if(u==33){
     GR33a->SetPoint(GR33a->GetN(),GR33a->GetN()/25200,max_y);
}

if(u==34){
     GR34a->SetPoint(GR34a->GetN(),GR34a->GetN()/25200,max_y);
}

if(u==35){
     GR35a->SetPoint(GR35a->GetN(),GR35a->GetN()/25200,max_y);
}

if(u==36){
     GR36a->SetPoint(GR36a->GetN(),GR36a->GetN()/25200,max_y);
}

if(u==37){
     GR37a->SetPoint(GR37a->GetN(),GR37a->GetN()/25200,max_y);
}

if(u==38){
     GR38a->SetPoint(GR38a->GetN(),GR38a->GetN()/25200,max_y);
}

if(u==39){
     GR39a->SetPoint(GR39a->GetN(),GR39a->GetN()/25200,max_y);
}

if(u==40){
     GR40a->SetPoint(GR40a->GetN(),GR40a->GetN()/25200,max_y);
}

if(u==41){
     GR41a->SetPoint(GR41a->GetN(),GR41a->GetN()/25200,max_y);
}

if(u==42){
     GR42a->SetPoint(GR42a->GetN(),GR42a->GetN()/25200,max_y);
}

if(u==43){
     GR43a->SetPoint(GR43a->GetN(),GR43a->GetN()/25200,max_y);
}

if(u==44){
     GR44a->SetPoint(GR44a->GetN(),GR44a->GetN()/25200,max_y);
}

if(u==45){
     GR45a->SetPoint(GR45a->GetN(),GR45a->GetN()/25200,max_y);
}

if(u==46){
     GR46a->SetPoint(GR46a->GetN(),GR46a->GetN()/25200,max_y);
}

if(u==47){
     GR47a->SetPoint(GR47a->GetN(),GR47a->GetN()/25200,max_y);
}

if(u==48){
     GR48a->SetPoint(GR48a->GetN(),GR48a->GetN()/25200,max_y);
}

if(u==49){
     GR49a->SetPoint(GR49a->GetN(),GR49a->GetN()/25200,max_y);
}

if(u==50){
     GR50a->SetPoint(GR50a->GetN(),GR50a->GetN()/25200,max_y);
}

if(u==51){
     GR51a->SetPoint(GR51a->GetN(),GR51a->GetN()/25200,max_y);
}

if(u==52){
     GR52a->SetPoint(GR52a->GetN(),GR52a->GetN()/25200,max_y);
}

if(u==53){
     GR53a->SetPoint(GR53a->GetN(),GR53a->GetN()/25200,max_y);
}

if(u==54){
     GR54a->SetPoint(GR54a->GetN(),GR54a->GetN()/25200,max_y);
}

if(u==55){
     GR55a->SetPoint(GR55a->GetN(),GR55a->GetN()/25200,max_y);
}

if(u==56){
     GR56a->SetPoint(GR56a->GetN(),GR56a->GetN()/25200,max_y);
}

if(u==57){
     GR57a->SetPoint(GR57a->GetN(),GR57a->GetN()/25200,max_y);
}

if(u==58){
     GR58a->SetPoint(GR58a->GetN(),GR58a->GetN()/25200,max_y);
}

if(u==59){
     GR59a->SetPoint(GR59a->GetN(),GR59a->GetN()/25200,max_y);
}

if(u==60){
     GR60a->SetPoint(GR60a->GetN(),GR60a->GetN()/25200,max_y);
}

if(u==61){
     GR61a->SetPoint(GR61a->GetN(),GR61a->GetN()/25200,max_y);
}

if(u==62){
     GR62a->SetPoint(GR62a->GetN(),GR62a->GetN()/25200,max_y);
}

if(u==63){
     GR63a->SetPoint(GR63a->GetN(),GR63a->GetN()/25200,max_y);
}


}
// std::cout<< "Points around Y max  " << max_y <<std::endl;

    }
  }


  ofstream myfile;
  myfile.open ("example1.dat");
     for(int j=0;j<30;j++){

          GR0b->SetPoint(GR0b->GetN(),GR0b->GetN(),GR0a->Eval(j));
          GR1b->SetPoint(GR1b->GetN(),GR1b->GetN(),GR1a->Eval(j));
          GR2b->SetPoint(GR2b->GetN(),GR2b->GetN(),GR2a->Eval(j));
          GR3b->SetPoint(GR3b->GetN(),GR3b->GetN(),GR3a->Eval(j));
          GR4b->SetPoint(GR4b->GetN(),GR4b->GetN(),GR4a->Eval(j));
          GR5b->SetPoint(GR5b->GetN(),GR5b->GetN(),GR5a->Eval(j));
          GR6b->SetPoint(GR6b->GetN(),GR6b->GetN(),GR6a->Eval(j));
          GR7b->SetPoint(GR7b->GetN(),GR7b->GetN(),GR7a->Eval(j));
          GR8b->SetPoint(GR8b->GetN(),GR8b->GetN(),GR8a->Eval(j));
          GR9b->SetPoint(GR9b->GetN(),GR9b->GetN(),GR9a->Eval(j));
          GR10b->SetPoint(GR10b->GetN(),GR10b->GetN(),GR10a->Eval(j));
          GR11b->SetPoint(GR11b->GetN(),GR11b->GetN(),GR11a->Eval(j));
          GR12b->SetPoint(GR12b->GetN(),GR12b->GetN(),GR12a->Eval(j));
          GR13b->SetPoint(GR13b->GetN(),GR13b->GetN(),GR13a->Eval(j));
          GR14b->SetPoint(GR14b->GetN(),GR14b->GetN(),GR14a->Eval(j));
          GR15b->SetPoint(GR15b->GetN(),GR15b->GetN(),GR15a->Eval(j));
	 GR16b->SetPoint(GR16b->GetN(),GR16b->GetN(),GR16a->Eval(j));
          GR17b->SetPoint(GR17b->GetN(),GR17b->GetN(),GR17a->Eval(j));
          GR18b->SetPoint(GR18b->GetN(),GR18b->GetN(),GR18a->Eval(j));
          GR19b->SetPoint(GR19b->GetN(),GR19b->GetN(),GR19a->Eval(j));
          GR20b->SetPoint(GR20b->GetN(),GR20b->GetN(),GR20a->Eval(j));
          GR21b->SetPoint(GR21b->GetN(),GR21b->GetN(),GR21a->Eval(j));
          GR22b->SetPoint(GR22b->GetN(),GR22b->GetN(),GR22a->Eval(j));
          GR23b->SetPoint(GR23b->GetN(),GR23b->GetN(),GR23a->Eval(j));
          GR24b->SetPoint(GR24b->GetN(),GR24b->GetN(),GR24a->Eval(j));
          GR25b->SetPoint(GR25b->GetN(),GR25b->GetN(),GR25a->Eval(j));
          GR26b->SetPoint(GR26b->GetN(),GR26b->GetN(),GR26a->Eval(j));
          GR27b->SetPoint(GR27b->GetN(),GR27b->GetN(),GR27a->Eval(j));
          GR28b->SetPoint(GR28b->GetN(),GR28b->GetN(),GR28a->Eval(j));
          GR29b->SetPoint(GR29b->GetN(),GR29b->GetN(),GR29a->Eval(j));
          GR30b->SetPoint(GR30b->GetN(),GR30b->GetN(),GR30a->Eval(j));
          GR31b->SetPoint(GR31b->GetN(),GR31b->GetN(),GR31a->Eval(j));
          GR32b->SetPoint(GR32b->GetN(),GR32b->GetN(),GR32a->Eval(j));
          GR33b->SetPoint(GR33b->GetN(),GR33b->GetN(),GR33a->Eval(j));
          GR34b->SetPoint(GR34b->GetN(),GR34b->GetN(),GR34a->Eval(j));
          GR35b->SetPoint(GR35b->GetN(),GR35b->GetN(),GR35a->Eval(j));
          GR36b->SetPoint(GR36b->GetN(),GR36b->GetN(),GR36a->Eval(j));
          GR37b->SetPoint(GR37b->GetN(),GR37b->GetN(),GR37a->Eval(j));
          GR38b->SetPoint(GR38b->GetN(),GR38b->GetN(),GR38a->Eval(j));
          GR39b->SetPoint(GR39b->GetN(),GR39b->GetN(),GR39a->Eval(j));
          GR40b->SetPoint(GR40b->GetN(),GR40b->GetN(),GR40a->Eval(j));
          GR41b->SetPoint(GR41b->GetN(),GR41b->GetN(),GR41a->Eval(j));
          GR42b->SetPoint(GR42b->GetN(),GR42b->GetN(),GR42a->Eval(j));
          GR43b->SetPoint(GR43b->GetN(),GR43b->GetN(),GR43a->Eval(j));
          GR44b->SetPoint(GR44b->GetN(),GR44b->GetN(),GR44a->Eval(j));
          GR45b->SetPoint(GR45b->GetN(),GR45b->GetN(),GR45a->Eval(j));
          GR46b->SetPoint(GR46b->GetN(),GR46b->GetN(),GR46a->Eval(j));
          GR47b->SetPoint(GR47b->GetN(),GR47b->GetN(),GR47a->Eval(j));
          GR48b->SetPoint(GR48b->GetN(),GR48b->GetN(),GR48a->Eval(j));
          GR49b->SetPoint(GR49b->GetN(),GR49b->GetN(),GR49a->Eval(j));
          GR50b->SetPoint(GR50b->GetN(),GR50b->GetN(),GR50a->Eval(j));
          GR51b->SetPoint(GR51b->GetN(),GR51b->GetN(),GR51a->Eval(j));
          GR52b->SetPoint(GR52b->GetN(),GR52b->GetN(),GR52a->Eval(j));
          GR53b->SetPoint(GR53b->GetN(),GR53b->GetN(),GR53a->Eval(j));
          GR54b->SetPoint(GR54b->GetN(),GR54b->GetN(),GR54a->Eval(j));
          GR55b->SetPoint(GR55b->GetN(),GR55b->GetN(),GR55a->Eval(j));
          GR56b->SetPoint(GR56b->GetN(),GR56b->GetN(),GR56a->Eval(j));
          GR57b->SetPoint(GR57b->GetN(),GR57b->GetN(),GR57a->Eval(j));
          GR58b->SetPoint(GR58b->GetN(),GR58b->GetN(),GR58a->Eval(j));
          GR59b->SetPoint(GR59b->GetN(),GR59b->GetN(),GR59a->Eval(j));
          GR60b->SetPoint(GR60b->GetN(),GR60b->GetN(),GR60a->Eval(j));
          GR61b->SetPoint(GR61b->GetN(),GR61b->GetN(),GR61a->Eval(j));
          GR62b->SetPoint(GR62b->GetN(),GR62b->GetN(),GR62a->Eval(j));
          GR63b->SetPoint(GR63b->GetN(),GR63b->GetN(),GR63a->Eval(j));
 

// Obtaining values for max pulse heights for low, medium, and high subruns

          
                myfile << j << " 0 " <<  GR0a->Eval(j) << "\n";
                myfile << j << " 1 " <<  GR1a->Eval(j) << "\n";
                myfile << j << " 2 " <<  GR2a->Eval(j) << "\n";
                myfile << j << " 3 " <<  GR3a->Eval(j) << "\n";
                myfile << j << " 4 " <<  GR4a->Eval(j) << "\n";
                myfile << j << " 5 " <<  GR5a->Eval(j) << "\n";
                myfile << j << " 6 " <<  GR6a->Eval(j) << "\n";
                myfile << j << " 7 " <<  GR7a->Eval(j) << "\n";
                myfile << j << " 8 " <<  GR8a->Eval(j) << "\n";
                myfile << j << " 9 " <<  GR9a->Eval(j) << "\n";
                myfile << j << " 10 " <<  GR10a->Eval(j) << "\n";
                myfile << j << " 11 " <<  GR11a->Eval(j) << "\n";
                myfile << j << " 12 " <<  GR12a->Eval(j) << "\n";
                myfile << j << " 13 " <<  GR13a->Eval(j) << "\n";
                myfile << j << " 14 " <<  GR14a->Eval(j) << "\n";
                myfile << j << " 15 " <<  GR15a->Eval(j) << "\n";

		myfile << j << " 16 " <<  GR16a->Eval(j) << "\n";
                myfile << j << " 17 " <<  GR17a->Eval(j) << "\n";
                myfile << j << " 18 " <<  GR18a->Eval(j) << "\n";
                myfile << j << " 19 " <<  GR19a->Eval(j) << "\n";
                myfile << j << " 20 " <<  GR20a->Eval(j) << "\n";
                myfile << j << " 21 " <<  GR21a->Eval(j) << "\n";
                myfile << j << " 22 " <<  GR22a->Eval(j) << "\n";
                myfile << j << " 23 " <<  GR23a->Eval(j) << "\n";
                myfile << j << " 24 " <<  GR24a->Eval(j) << "\n";
                myfile << j << " 25 " <<  GR25a->Eval(j) << "\n";
                myfile << j << " 26 " <<  GR26a->Eval(j) << "\n";
                myfile << j << " 27 " <<  GR27a->Eval(j) << "\n";
                myfile << j << " 28 " <<  GR28a->Eval(j) << "\n";
                myfile << j << " 29 " <<  GR29a->Eval(j) << "\n";
                myfile << j << " 30 " <<  GR30a->Eval(j) << "\n";
                myfile << j << " 31 " <<  GR31a->Eval(j) << "\n";
		myfile << j << " 32 " <<  GR32a->Eval(j) << "\n";
                myfile << j << " 33 " <<  GR33a->Eval(j) << "\n";
                myfile << j << " 34 " <<  GR34a->Eval(j) << "\n";
                myfile << j << " 35 " <<  GR35a->Eval(j) << "\n";
                myfile << j << " 36 " <<  GR36a->Eval(j) << "\n";
                myfile << j << " 37 " <<  GR37a->Eval(j) << "\n";
                myfile << j << " 38 " <<  GR38a->Eval(j) << "\n";
                myfile << j << " 39 " <<  GR39a->Eval(j) << "\n";
                myfile << j << " 40 " <<  GR40a->Eval(j) << "\n";
                myfile << j << " 41 " <<  GR41a->Eval(j) << "\n";
                myfile << j << " 42 " <<  GR42a->Eval(j) << "\n";
                myfile << j << " 43 " <<  GR43a->Eval(j) << "\n";
                myfile << j << " 44 " <<  GR44a->Eval(j) << "\n";
                myfile << j << " 45 " <<  GR45a->Eval(j) << "\n";
                myfile << j << " 46 " <<  GR46a->Eval(j) << "\n";
                myfile << j << " 47 " <<  GR47a->Eval(j) << "\n";
                myfile << j << " 48 " <<  GR48a->Eval(j) << "\n";
                myfile << j << " 49 " <<  GR49a->Eval(j) << "\n";
                myfile << j << " 50 " <<  GR50a->Eval(j) << "\n";
                myfile << j << " 51 " <<  GR51a->Eval(j) << "\n";
                myfile << j << " 52 " <<  GR52a->Eval(j) << "\n";
                myfile << j << " 53 " <<  GR53a->Eval(j) << "\n";
                myfile << j << " 54 " <<  GR54a->Eval(j) << "\n";
                myfile << j << " 55 " <<  GR55a->Eval(j) << "\n";
                myfile << j << " 56 " <<  GR56a->Eval(j) << "\n";
                myfile << j << " 57 " <<  GR57a->Eval(j) << "\n";
                myfile << j << " 58 " <<  GR58a->Eval(j) << "\n";
                myfile << j << " 59 " <<  GR59a->Eval(j) << "\n";
                myfile << j << " 60 " <<  GR60a->Eval(j) << "\n";
                myfile << j << " 61 " <<  GR61a->Eval(j) << "\n";
		myfile << j << " 62 " <<  GR62a->Eval(j) << "\n";
                myfile << j << " 63 " <<  GR63a->Eval(j) << "\n";


        //      myfile.close();
              //std::cout<<"15  " <<  GR15a->Eval(j) <<std::endl;

         }



        myfile.close();

	cout << "done";

}


void run(std::string name){
//void run(){

//const char *s = "/dsk/1/tmp/coldelec/feasic/quadFeAsic/20210927T103232/gain_enc_sequence-g2s2b0-0000/gain_enc_sequence-g2s2b0-0000-20210927T103324-parseBinaryFile.root";

const char *s = name.c_str();	
//std::string s1 = "/dsk/1/tmp/coldelec/feasic/quadFeAsic/20210927T103232/gain_enc_sequence-g2s2b0-0000/gain_enc_sequence-g2s2b0-0000-20210927T103324-parseBinaryFile.root";


     // findmaxtest();
     // StuckBitFrac("/dsk/1/tmp/coldelec/feasic/quadFeAsic/20210927T103232/gain_enc_sequence-g2s2b0-0000/gain_enc_sequence-g2s2b0-0000-20210927T103324-parseBinaryFile.root");
//	StuckBitFrac(s1);
	StuckBitFrac_Lin(s);
	findmaxtest_Lin();

}

