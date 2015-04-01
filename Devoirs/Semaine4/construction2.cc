#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

class Piece {
protected:
	string name;
	
public:
	Piece (string nm) : name(nm) {};
  ostream& afficher(ostream& os) const ;
};

  ostream& Piece :: afficher (ostream& os) const {
    os << '"' << name << '"';
    return os;
  }


class Simple : public Piece {
protected:
	string orient;
public:
	Simple (string nm,string orint=""):Piece(nm),orient(orint){};
  friend ostream& operator<<(ostream&, const Simple&);
};

  ostream& operator<< (ostream& os,const Simple& other) {
    os << "pièce simple ";
    other.afficher(os);
    if (!other.orient.empty())
      os << " orienté vers la " << other.orient << endl;
    else
      os << endl;
    return os;
  }


class Composee : public Piece{
private:
  vector <Simple> svec;

public:
	Composee (string nm):Piece(nm) {};

  friend ostream& operator<<(ostream&, const Composee&);
	void construire (const Simple& sm) {
		svec.push_back(sm);
	}
};

  ostream& operator<< (ostream& os,const Composee& other) {
    os << "pièce ";
    other.afficher(os);
    os << " composée de :" << endl;
    for (vector<Simple>::const_iterator it = other.svec.begin() ; it != other.svec.end(); ++it) {
      os << "    * ";
      os << *it;
    }
    return os;
  }

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

// Sans polymorphisme, c'est difficile de faire autrement :-(...
template <typename T>
void ajouterComposant(T composant, unsigned int nb)
{
  cout << ' ' << nb << " exemplaire";
  if (nb > 1) cout << 's';
  cout << " de " << composant;
}

int main()
{
  cout << "Nous fabriquons une boîte de jeu contenant :" << endl;
  ajouterComposant(Simple("brique standard"), 59);

  // Déclare une pièce composée dont le nom est «porte»
  Composee porte("porte");

  // Une porte est constituée...
  //  ...d'un cadran de porte orienté à gauche
  porte.construire(Simple("cadran porte", "gauche"));
  //  ...et d'un battant orienté à gauche
  porte.construire(Simple("battant", "gauche"));

  // La boite de jeu a pour 2e composant la porte
  ajouterComposant(porte, 1);

  // Déclare une pièce composée dont le nom est «fenêtre»
  Composee fenetre("fenetre");

  // Une fenêtre est constituée...
  //  ...d'un cadran de fenêtre (sans orientation)
  fenetre.construire(Simple("cadran fenetre"));
  //  ...d'un volet orienté à gauche
  fenetre.construire(Simple("volet", "gauche"));
  //  ...d'un volet orienté à droite
  fenetre.construire(Simple("volet", "droite"));

  // La boite de jeu a en plus deux fenêtres
  ajouterComposant(fenetre, 2);

  return 0;
}
