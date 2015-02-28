#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

class Tirelire {
private:
  double montant;

public:
  double getMontant() {
    return montant;
  }

  void afficher() {
    if (getMontant() == 0.0)
      cout << "Vous etes sans le sous." << endl;
    else
      cout << "Vous avez : " << getMontant() << " euros dans votre tirelire." << endl;

  }

  void secouer() {
    if (getMontant() != 0.0)
      cout << "Bing bing" << endl;
  }

  void remplir (double amt) {
    if (amt > 0.0)
      montant += amt;
  }

  void vider() {
    montant = 0;
  } 

  void puiser(double wtd) {
    if (wtd > 0.0) {
      if (wtd > getMontant())
        montant = 0.0;
      else
        montant -= wtd;
    }
  }

  bool montant_suffisant (double bud,double& sol) {
    if (bud <= 0) {
      sol = getMontant();
      return true;
    }
    else {
      if (getMontant() >= bud) {
        sol = getMontant() - bud;
        return true;
      }
      else {
        sol = bud - getMontant();
        return false;
      }
    }
  }

};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
