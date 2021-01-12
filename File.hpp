#pragma once

#include <iostream>
#include <sstream>


using namespace std;

template <typename T>

class File{

public:

	virtual ~File(){
		//cout << "Destructeur de File" << endl;
	}


	virtual const string quisuisje() const{
		return "Une File";
	}

	/*
	* renvoie true si la file courant est vide
	*/
	virtual bool estVide() const=0;

	/*
	* enfile un element T à la file courante
	*/
	virtual void enfiler(const T &x) =0;

	/*
	*supprime le premier element de la file courante
	*/
	virtual void defiler() =0;

	/*
	* renvoie le premier element de la file courante
	*/
	virtual const T &premier() const =0;

	/*
	* methode d'affichage
	*/
	virtual const string toString() const =0;
};