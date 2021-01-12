#pragma once

#include <iostream>
#include <sstream>
#include "FileChainee.hpp"

using namespace std;
template <typename T>

class Guichet{
private :
	int numGuichet; //numero du guichet (entre 0 et N-1);
	FileChainee<T> *servi;  //file du client en train d'être servi
	FileChainee<T> *attente; //file des clients qui attendent d'etre servis
	double probaClient;  //probabilité des clients d'arriver (entre 0 et 1)

public : 
	Guichet() {}

	//constructeur
	Guichet(int numero,FileChainee<T> *fileServi, FileChainee<T> *fileAttente, double proba): 
		numGuichet(numero),servi(fileServi), attente(fileAttente), probaClient(proba)
		{}

	~Guichet(){
		//cout<<"Destructeur de Guichet"<<endl;
	}

	//accesseurs
	/*
	* renvoie la probabilité d'arrivée des clients du guichet courant
	*/		
	const double getProba() const{
		return this->probaClient;
	}

	/*
	* renvoie l'adresse de la file d'attente du guichet courant
	*/	
	FileChainee<T> *getFileAttente() const {
		return this->attente;
	}

	/*
	* renvoie l'adresse de la file servi du guichet courant
	*/
	FileChainee<T> *getFileServi() const {
		return this->servi;
	}

	//modificateur
	/*
	*	modifie la probabilité d'arrivee des clients du guichet courant
	*/
	void setProba(const double x){
		this->probaClient = x;
	}

	//fonction toString pour afficher la file
	const string toString() const{
		ostringstream s;
		s << "Guichet " << this->numGuichet << " : [" << *(this->servi) << "- "<< *(this->attente);
		s << "]";
		return s.str();
	}

	//surcharge d'operateur cout
	friend ostream& operator<< (ostream &f, const Guichet &g){
		return f << g.toString();
	}



};