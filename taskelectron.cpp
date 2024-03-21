#include <iostream>
#include <TH1F.h>
#include <TTree.h>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

void taskelectron4 (){
	string DATOS;
	int i= 0;
	ifstream infile; //defined
	infile.open ("el_1.5.txt");	//la definicion normal de un vector std::vector<int> V = {};
	std::vector<float> v; //vecto v definido
    while(!infile.eof()) // while is not at the end.
        {
	        getline(infile,DATOS); // GUARDO LA LINEA EN mi STRING DATOS.
	        std::istringstream iss(DATOS); //creo un istring que mantiene guardado los datos
	    	std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(), std::back_inserter(v)); //copia los datos de mi string y los copia en mi vector como floats y los va insertando al final
	        //i+=1; //contador para saber cuantas lineas tiene
        }
    //std::copy(v.begin(), v.end(),std::ostream_iterator<float>(std::cout, ", "));
  	//std::cout << "\n";
  	//std::cout<<"\n"<<v.at(2136450)<<"\n";
  	//std::cout<<v.size()<<"\n"; //tamano de mi vector
	infile.close(); //cierro el archivo infile
	TFile *f=new TFile("electrontree.root","recreate"); //creo un archivo en root. recreate crea uno nuevo si este no existi. Si existe lo reemplaza
	TTree *t1=new TTree("t1","ELECTRONS"); //tree definido como t1, con el nombre electrones
	float dedx[12]={}; //arrays defined with 0s
	float tr[12]={};
	float total[12]={};
	float momentum;
	t1->Branch("dedx",&dedx,"dedx[12]/F");
	t1->Branch("tr",&tr,"tr[12]/F");
	t1->Branch("total",&total,"total[12]/F");
	t1->Branch("momentum",&momentum,"momentum/F");
	int variable=1; //defino una variable. idk how to do it
	//int contador=0;
	int anothervariable=0;
	for(int m=0;m<v.size();m++){
		if((m+1)%37==0){
			momentum=v.at(m)*std::pow(10.0,6); //*std::pow(10.0,6); // momentum quedara guardada hasta el proximo fill
			variable=1; //reset a 1 de mi variable que cuenta
			anothervariable=0; //reset my counter for my arrays
			//std::cout<<momentum;
			t1->Fill(); // fill
			//std::cout<<momentum<<"\n";
			continue;
		}
		if((variable)%3==0){
			dedx[anothervariable]=v.at(m-2)*std::pow(10.0,6);
			tr[anothervariable]=v.at(m-1)*std::pow(10.0,6);
			total[anothervariable]=v.at(m)*std::pow(10.0,6);
			//std::cout<<v.at(m)<<"\n";
			//std::cout<<anothervariable<<"\n";
			//std::cout<<dedx[anothervariable]<<"\n";
			//std::cout<<tr[anothervariable]<<"\n";
			//std::cout<<total[anothervariable]<<"	";
			anothervariable+=1;
			//contador+=1;
		}
		variable+=1;
	}
	//std::cout<<"\n la cantidad de particulas es: "<<contador<<"\n\n";	
	t1->Write();
	f->Close();
	//std::cout<<"\n"<<total[10]<<"\n";
	//t1->Print();
	//t1->Scan("dedx:tr");
    }