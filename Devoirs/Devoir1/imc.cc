#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/
class Patient {
private:
  double masse, hauteur;

public:
  void init(double,double);
  void afficher(void);
  double poids () {return masse;}
  double taille () {return hauteur;}
  double imc ();
};

void Patient::init (double x, double y) {
  if (x < 0.0 || y < 0.0) {
    masse=0.0;
    hauteur=0.0;
  }
  else {
    masse=x;
    hauteur=y;
  }
}

void Patient::afficher(void) {
  cout << "Patient : " << poids() << " kg pour " << taille() << " m" << endl;
}
double Patient::imc(void) {
  return (taille() == 0) ? 0 : poids() / (taille()*taille()); 
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Patient quidam;
  double poids, taille;
  do {
    cout << "Entrez un poids (kg) et une taille (m) : ";
    cin >> poids >> taille;
    quidam.init(poids, taille);
    quidam.afficher();
    cout << "IMC : " << quidam.imc() << endl;
  } while (poids * taille != 0.0);
  return 0;
}
