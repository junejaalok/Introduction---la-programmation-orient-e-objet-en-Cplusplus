#include <iostream>
#include <utility> // pour la fonction swap
#include <string>
#include <vector>
using namespace std;

class Cellule
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
friend class Petri;
private:
    string nom;
    double taille;
    int energie;
    string couleur;

public:
    Cellule ();
    Cellule (string,double,int,string);
    void affiche(void);
    Cellule division(void);
};

Cellule::Cellule () : nom("Pyrobacculum"),taille(10),energie(5),couleur("verte") {}
Cellule::Cellule (string name,double size,int energy, string color) : nom(name),taille(size),energie(energy),couleur(color) {}
void Cellule::affiche(void) {
    cout << nom << ", taille = " << taille << " microns, énergie = " << energie << ", couleur = " << couleur << endl;
}
Cellule Cellule::division(void) {
    Cellule temp;
    temp.nom=nom;
    temp.taille=taille;
    temp.energie=energie;
    energie -= 1;
    if (couleur=="verte") temp.couleur = "bleue"; 
    else if(couleur=="bleue") temp.couleur = "rouge"; 
    else if (couleur=="rouge") temp.couleur = "rose bonbon"; 
    else if (couleur=="violet") temp.couleur = "violet"; 
    else temp.couleur = couleur + " fluo"; 
    return temp;
}

class Petri {
    
private:

vector<Cellule> popu;

public:

void ajouter(const Cellule&);
void affiche(void);
void evolue(void);
    
};

void Petri::ajouter(const Cellule& cell) {
    popu.push_back(cell);
}

void Petri::affiche() {
   for (int i=0;i<popu.size();i++) {
       popu[i].Cellule::affiche();
   }
}

void Petri::evolue(void) {
    vector <Cellule> init = popu;
    int siz=popu.size();
    for (int i=0;i<siz;i++) {
        Cellule tmp=popu[i].Cellule::division();
        popu.push_back(tmp);
    }
    
    for (int i=0;i<siz;i++) {
        if (popu[i].Cellule::energie<=0){
            swap(popu[i], popu.back());
            popu.pop_back();
        }
    }
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Petri assiette;

  assiette.ajouter(Cellule());
  assiette.ajouter(Cellule("PiliIV", 4, 1, "jaune"));
  cout << "Population avant évolution :" << endl;
  assiette.affiche();

  assiette.evolue();
  cout << "Population après évolution :" << endl;
  assiette.affiche();

  return 0;
}
