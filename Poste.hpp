#pragma once 

#include <string>
#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime> 
#include <vector>
#include <sstream>

#include "Guichet.hpp"

template <int N, typename T>

class Poste {

private :
	vector<Guichet<int>> elem;  //vector des N guichet(s)
	int nbClients; //nombre de clients dans la poste depuis la début de la simulation
	int nbClientsServis; //nombre de clients servis depuis le début de la simulation
	int nbClientsImpatients; //nombre de clients impatients partis sans etre servis depuis le début de la simulation

public :
	//constructeur
	Poste(const double proba){
		nbClients=0;
		nbClientsServis=0;
		nbClientsImpatients=0;

		//creation des guichets
		for(int i=0 ; i<N ; i++){
			Guichet<int> g = Guichet<int>(i,new FileChainee<int>,new FileChainee<int>,proba);
			(this->elem).push_back(g);
		}
	}

	
	


	//methodes


	//accesseurs
	/*
	* renvoie le nombre de Guichet de la poste
	*/
	int longueur() const{
		return N;
	}

	/*
	* renvoie le nombre de clients de la poste
	*/
	int getNbClients() const{
		return this->nbClients;
	}

	/*
	* renvoie le nombre de clients servis de la poste
	*/
	int getNbClientsServis() const{
		return this->nbClientsServis;
	}

	/*
	* renvoie le nombre de clients impatients de la poste
	*/
	int getNbClientsImpatients() const{
		return this->nbClientsImpatients;
	}

	//modificateurs

	/*
	* incremente (+1) le nombre de clients
	*/
	void incrementerNbClients(){
		(this->nbClients)++;
	}

	/*
	* incremente (+1) le nombre de clients servis
	*/
	void incrementerNbClientsServis(){
		(this->nbClientsServis)++;
	}

	/*
	* incremente (+1) le nombre de clients impatients
	*/
	void incrementerNbClientsImpatients(){
		(this->nbClientsImpatients)++;
	}

	/*
	* renvoie le numéro (int) du guichet le moins rempli de la poste
	*/
	int GuichetLeMoinsRempli() const{
		if( (this->longueur())==1 ){
			//un seul guichet
			return 0;
		}
		else{
			//plusieurs guichets
			int min = ((this->elem)[0].getFileAttente()->getNbClientsFile());
			int num = 0;
			
			for (int i=1 ; i<N ; i++){
				//si guichet vide
				if ( ((this->elem)[i].getFileServi()->getNbClientsFile())==0 ) {
						return i;
				}
				
				//sinon chercher file d'attente la moins remplie
				else if ( ((this->elem)[i].getFileAttente()->getNbClientsFile()) < min ) {

					min = ((this->elem)[i].getFileAttente()->getNbClientsFile());
					num=i;
				}
			}
			return num;
		}

	}

	/*
	* surcharge de l'operateur []
	*/
	Guichet<int>& operator[](const int i)  {
		return (this->elem)[i];
	}

	//fonction toString pour afficher la file
	const std::string toString()const{
		std::ostringstream s;
		
		s << "\n\tNb de clients arrivés : " << nbClients;
		s << "\n\tNb de clients servis : " << nbClientsServis;
		s << "\n\tNb de clients impatients : " << nbClientsImpatients;
		s << "\n\n";

		for (int i = 0; i < N; i++){
			s<<"\t" << (this->elem)[i]<<"\n";	 
		}
		return s.str();
	}

	//surcharge d'operateur cout
	friend std::ostream &operator<<(std::ostream &f, const Poste<N,int> &p){
		return f << p.toString();
	}

};