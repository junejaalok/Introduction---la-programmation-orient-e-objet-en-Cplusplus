#include <vector>
#include <iostream>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme à partir d'ici.
 *******************************************/
class OptionVoyage {

protected:
  string name_;
  double flat_fee_;

public:
  OptionVoyage(string nm, double ff):name_(nm),flat_fee_(ff) {};

  string nom() const {
    return name_;
  }

  double prix() const {
    return flat_fee_;
  }

  void affiche (ostream& sortie) const {
    sortie << nom() << " -> " << prix() << "CHF" << endl;
}


};




    out << "Voyage de "
        <<  " à "

      out << ":  vous n'avez rien réservé !" << endl;
      out << ", avec pour options : " << endl;

      out << "Prix total : "
          << " CHF"


/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Transport transp1("Trajet en train", 50.0);
  Transport transp2("Trajet en avion", 50.0, true);

  Sejour sejour1("Hotel 3* : Les amandiers ", 40.0, 5, 100.0);
  Sejour sejour2("Hotel 4* : Ambassador Plazza  ", 100.0, 2, 250.0);

  OptionCombinee combi("Hotel 4* : Ambassador Plazza et trajet en avion",
                       100.0, 2, 250.0, true);

  KitVoyage kit1("Zurich", "Paris");
  kit1.ajouter_option(transp1);
  kit1.ajouter_option(sejour1);
  cout << kit1 << endl;

  KitVoyage kit2("Zurich", "New York");
  kit2.ajouter_option(transp2);
  kit2.ajouter_option(sejour2);
  cout << kit2 << endl;

  KitVoyage kit3("Zurich", "New York");
  kit3.ajouter_option(combi);
  cout << kit3 << endl;

  kit1.annuler();
  kit2.annuler();
  cout << kit1 << endl;
  cout << kit2 << endl;

  return 0;

}
