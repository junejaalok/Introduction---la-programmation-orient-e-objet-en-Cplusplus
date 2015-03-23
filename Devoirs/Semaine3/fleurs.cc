#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Classe représentant les "fleurs".
 * Une instance de cette classe hors Bouquet est un exemple / une catégorie
 * un type de de fleurs.
 * Les fleurs "réelles" sont les instances présentes dans les bouquets.
 */
class Fleur
{
  /*******************************************
   * Complétez le programme à partir d'ici.
   *******************************************/
private:
   string nom;
   string couleur;
   double prix_base;
   bool parfum_;
   bool promotion;

public:

    Fleur (string nm,string cl, double pb, bool prf=false, bool pr=false):nom(nm),couleur(cl),prix_base(pb),parfum_(prf),promotion(pr) {};
	double prix (void) {
		if (promotion) return prix_base/2.0;
		else return prix_base;
	}

	bool parfum () {
		return parfum_;
	}

	void parfum(ostream& sortie) const {
		if (parfum) 
			cout << nom << ' ' << couleur << "  parfumée, prix : " << prix() << " CHF";
		else
			cout << nom << ' ' << couleur << ", prix : " << prix() << " CHF";
}
	
};


   //   out << "Encore aucune fleur dans le bouquet !" << endl;
     //   out << " parfumé";
     // out << " composé de :" << endl;


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Fleur r1("Rose", "jaune", 1.5); // exemple de rose jaune inodore
  cout << r1 << endl;

  Fleur r2("Rose", "jaune", 3.0, true); // exemple de rose jaune parfumée
  Fleur r3("Rose", "rouge", 2.0, true, true); // exemple de rose rouge parfumée en promo
/*  Bouquet b1;
  b1 += r1; // ajoute une fleur de type r1
  b1 += r1; // ajoute aurte une fleur de type r1
  b1 += r2;
  b1 += r3;
  cout << b1 << endl;

  b1 = b1 - r1; // supprime toutes les fleurs de même type que r1
  cout << b1 << endl;

  Bouquet b2;
  b2 = b1 + r1; // remet une fleur de type r1
  cout << b2 << endl;

  // supprime toutes les fleurs parfumées
  b2 -= r2;
  b2 -= r3;
  cout << b2;
*/
  return 0;
}
