#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#include "Client.hpp"
#include "File.hpp"

using namespace std;

template <typename T>

class FileChainee : public File<T>{
	private :
		Client *sf;  //client en sommet de file, premier de la file
		int nbClientsFile; //nombre de client dans la file d'attente

		
		//detruire
		void detruire(Client *c){
			if(c!=nullptr){
				detruire(c->getSuivant());
				delete c;
			}
		}
		

		//dupliquer iteratif
		Client *dupliquer(const Client *c){
			if(c==nullptr) return nullptr;
			//else
			Client *a, *b;
			a = b = new Client(c->getNumero());
			while (c->getSuivant() != nullptr){
				c = c->getSuivant();
				b->setSuivant(new Client(c->getNumero()) );
				b = b->getSuivant();
			}
			return a;
		}
		

	public :
		//constructeur
		FileChainee() : sf(nullptr), nbClientsFile(0) {}
		

		//constructeur de copie
		FileChainee(const FileChainee<T> &f){
		//#ifdef DEBUG
			//cout << "constructeur de copie File" << endl;
		//#endif
			this->sf = dupliquer(f.sf);
		}


		//destructeur
		~FileChainee(){
			this->detruire(this->sf);
		}
		


		//methodes
		/*
		* renvoie true si la file courant est vide
		*/
		bool estVide() const override{
			return this->sf==nullptr;
		}


		/*
		* enfile un element T à la file courante
		*/
		void enfiler(const T &x) override{
			nbClientsFile++;
			//si la file est vide
			if (this->estVide()){
				Client *p = new Client(x, nullptr);
				this->sf = p;
			}

			//la file est non vide
			else{
				Client *c = this->sf;			
				//parcourir la file
				while (c->getSuivant() != nullptr){
					c = c->getSuivant();
				}
				//ajouter le nouveau clientla fin de la file		
				Client *h = new Client(x, nullptr);
				c->setSuivant(h); 
			}
		}


		/*
		* ajoute un nouveau client a la fin de la file
		* prends en compte la position du client dans la file et son temps d'arrivee
		*/
		void enfilerAvecTemps(const T &x, int tpsArriveeClient=-1) {
			nbClientsFile++;
			//si la file est vide
			if (this->estVide()){
				Client *p = new Client(x, nullptr, tpsArriveeClient);
				this->sf = p;
			}

			//la file est non vide
			else{
				Client *c = this->sf;			
				//parcourir la file
				while (c->getSuivant() != nullptr){
					c = c->getSuivant();
				}
				//ajouter le nouveau client a la fin de la file		
				Client *h = new Client(x, nullptr, tpsArriveeClient);
				c->setSuivant(h); 
			}
		}

		


		/*
		* Supprime le premier client de la file
		*/
		void defiler() override{
			assert(!this->estVide());
			//la file est non vide
			nbClientsFile--;
			
			Client *c = this->sf;
			this->sf = this->sf->getSuivant();
			delete c;
		}

		/*
		* Supprime le client (impatient) en position i dans la file
		*/
		void defilerImpatient(int i){
			assert(!this->estVide());
			//la file est non vide
			nbClientsFile--;
			if (i==0){
				this->defiler();
			}
			//i different de 0
			else{
				
				Client *c = (this->sf);
				for (int k=0 ; k<(i-1) ; k++){
					c = c->getSuivant(); //on cherche le client précédent le client à défiler
				}
				Client *p = c->getSuivant();
				c->setSuivant(p->getSuivant()); //on raccorde le client d'avant avec le client d'après
			}
		}

		//accesseurs 
		/*
		* renvoie le premier element (T) de la file courante
		*/
		const T &premier() const override{
			assert(!this->estVide());
			//la file est non vide
			return (this->sf)->getNumero();
		}


		/*
		* renvoie l'adresse du premier client de la file courante
		*/
		Client  *getSf() const{
			return this->sf;
		}

		/*
		* renvoie le temps du traitement du premier element (client) de la file courante
		*/
		const double getTraitementPremier() const{
			assert(!this->estVide());
			return (this->sf)->getTraitement();
		}

		/*
		* renvoie le nombre de clients dans la file courante
		*/
		const int getNbClientsFile() const{
			return this->nbClientsFile;
		}


		//fonction toString pour afficher la file
		const string toString() const override{
			ostringstream s;

			Client *c = this->sf;
			while (c!=nullptr){
				s << *c << " ";
				c = c->getSuivant();
			}
			return s.str();

		}

		//surcharge d'operateur cout
		friend ostream &operator<<(ostream &f, const FileChainee<T> &F){
			return f << F.toString();
		}
};