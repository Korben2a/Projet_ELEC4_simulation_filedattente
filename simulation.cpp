// g++ -Wall -o simulation simulation.cpp -lncurses
//make

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <ncurses.h>



#include "FileChainee.hpp"
#include "Client.hpp"
#include "Guichet.hpp"
#include "Poste.hpp"


using namespace std;


int main(){
    //parametres de l'affichage
    initscr();            // Initialise la structure WINDOW et autres paramètres 
    //definition des couleurs
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);



    //paramètres de la simulation
    double proba = (50.0/60.0); //50 clients par heure donc 50/60 clients par minute
    const int N = 4; //nombre de guichet
    int dureeOuverture = 8*60;  //8H en minutes
    int libre[N]={0}; //tableau de minutes à laquelle le guichet i sera libre
    int min=0; //numero du guichet le moins rempli
    /*----------------------------------*/

    srand(time(nullptr));
    Poste<N,int> poste = Poste<N,int>(proba);

    
    for (int t=1; t <= dureeOuverture ; t++){
        srand(time(nullptr));

        //affichage
        attron(COLOR_PAIR(5));
        printw("------------------------------Poste------------------------------\n\n");
        attron(COLOR_PAIR(3));
        printw("Durée d'ouverture : 8h (480 minutes)\n");
        printw("temps de simulation : %d minutes\n",t);  
        attron(COLOR_PAIR(4));
        printw("%s \n",poste.toString().c_str());
    	
        
    	cout << setprecision(2); //afficher 2 chiffres après la virgule
        double p = ((double) rand() / (double) RAND_MAX) ;  //double aleatoire entre 0 et 1
        
        //arriver dans file d'attente
        if (p <= poste[0].getProba()){  //un client peut rentrer
            poste.incrementerNbClients();
            min = poste.GuichetLeMoinsRempli();
            mvprintw(9+min,38+(4*poste[min].getFileAttente()->getNbClientsFile()),"<-- %d \n",poste.getNbClients());
            poste[min].getFileAttente()->enfilerAvecTemps(poste.getNbClients(),t);  //enfiler client
        }

        //verifier les clients impatients
        for (int k=0 ; k<N ; k++){      //k est 1 des N guichet(s)
            Client *c = poste[k].getFileAttente()->getSf();
            int l=0;
            while(c!=nullptr){
                if(t >= c->getTpsArriveeFile()  + c->getTolerance()){
                    attron(COLOR_PAIR(1));
                    mvprintw(9+k,52+(4*poste[k].getFileAttente()->getNbClientsFile()),"--> %d (impatient) \n",c->getNumero());
                    attroff(COLOR_PAIR(1));
                    
                    poste[k].getFileAttente()->defilerImpatient(l);  //defiler client de la place i
                    poste.incrementerNbClientsImpatients();
                }
                l++;
                c=c->getSuivant();
           }
        }


        //etre servi au guichet
        for (int j=0 ; j<N ; j++){
            if (libre[j] <= t) {
                if( !(poste[j].getFileServi())->estVide() ){
                    poste.incrementerNbClientsServis();
                    //cout << poste[j] << "  -->" << poste[j].getFileServi()->getSf()->getNumero() <<" (servi)" << endl;
                    attron(COLOR_PAIR(2));
                    mvprintw(9+j,45+(4*poste[j].getFileAttente()->getNbClientsFile()),"--> %d (servi)\n",poste[j].getFileServi()->getSf()->getNumero());
                    attroff(COLOR_PAIR(2));
                    poste[j].getFileServi()->defiler();
                    //cout << poste[j] << "  -->" << poste.getNbClientsServis() <<" (servi)" << endl;                
                }

            	if( !(poste[j].getFileAttente())->estVide() ){

                    libre[j] = t + poste[j].getFileAttente()->getTraitementPremier();
                    poste[j].getFileServi()->enfiler(poste[j].getFileAttente()->premier());
                    poste[j].getFileAttente()->defiler();
                }
            }
        }

        //calculs de ratios de la poste
        double ratio = 0.0;
        ratio = (double) poste.getNbClientsImpatients()/poste.getNbClients();
        mvprintw(15,0,"Ratio de clients impatients par rapport aux clients totaux : %lf\n\n",ratio);
        if (ratio <= 0.05){
            mvprintw(16,0,"==> Nombre de guichets suffisant\n");
        }
        else{
            mvprintw(16,0,"==> Nombre de guichets insuffisant (il faut 4 guichets)\n");
        }

       attron(COLOR_PAIR(5)); 
       mvprintw(20+N,0,"-----------------------------------------------------------------");
       refresh();
       sleep(1);  //attendre 1 seconde
	   clear();
	}
    
    refresh();              // Rafraîchit la fenêtre courante afin de voir le message apparaître
    getch();                // On attend que l'utilisateur appui sur une touche pour quitter
    endwin();      
    
    
}

