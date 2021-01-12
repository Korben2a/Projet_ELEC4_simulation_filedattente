#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


class Client{
	private :
		int numero;			//numero du client
		Client *suivant;	//adresse du client suivant
		int traitement;		// temps de traitement à un guichet
		double tolerance;	//temps de tolerance dans une file
		int tpsArriveeFile; //temps d'arrivee dans la file

	public :
		//constructeur
		Client(const int &num, Client *s=nullptr, int arrivee=-1)  {
			suivant = s;
			numero = num;
			tpsArriveeFile = arrivee;
			
			srand(time(nullptr));
    		traitement = 1 + rand()%5;  //temps de traitement uniforme entre 1 et 5 minutes
			tolerance = 5 + rand()%4; //temps de tolerance uniforme entre 5 et 8 minutes
		} 



		~Client(){
			//std::cout << "Destructeur de Client " << this->numero << std::endl;
		}


		//accesseurs
		/*
		* renvoie le numéro du client courant
		*/
		const int &getNumero() const{
			return this->numero;
		}

		/*
		*renvoie l'adresse du client suivant
		*/
		Client *getSuivant() const{
			return this->suivant;
		}

		/*
		*renvoie le temps de traitement du client courant
		*/
		const double getTraitement() const{
			return this->traitement;
		}

		/*
		*renvoie le temps de tolerance du client courant
		*/
		const int getTolerance() const{
			return this->tolerance;
		}

		/*
		* renvoie le temps d'arrivée du client courant dans sa file d'attente
		*/
		const int getTpsArriveeFile() const{
			return this->tpsArriveeFile;
		}


	
		//modificateur
		/*
		*modifie le suivant du client courant
		*/
		void setSuivant(Client *s){
			this->suivant = s;
		}


			//fonction toString pour afficher le client
		const string toString() const {
			ostringstream s;
			s << this->numero;
			return s.str();
		}

		//surcharge d'operateur cout
		friend ostream& operator<<(ostream& f, const Client &c){
			return f << c.toString();
		}


};