#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
  const string nom_ ;
  int niveau_ ;
  int points_de_vie_ ;
  int force_ ;
  int position_ ;

public:
  Creature (string nm, int ni, int pdv, int fr, int pos=0) : nom_(nm),niveau_(ni),points_de_vie_(pdv),force_(fr),position_(pos) {} ;
  bool vivant() {
    if (points_de_vie_ > 0 )return true;
    else return false;
  }

  int points_attaque () {
    if (vivant()) return ( niveau_ * force_ );
    else return 0;
  }

  void deplacer(int n) {
    position_ += n;
  }

  void adieux(){
    cout << nom_ << " n'est plus!";
  }

  void faiblir (int n) {
    if (vivant()) {
      points_de_vie_ -= n;
    }
    else {
      points_de_vie_ = 0;
      adieux();
    }  
  }
    
  void afficher () {
    cout << nom_ << ", niveau: " << niveau_ << ", points de vie: " << points_de_vie_ <<", force: " << force_ << ", points d'attaque: " << points_attaque() << ", position: " << position_ ;
  }


};

class Dragon : public Creature {

private:
  int portee_flamme_;

public:
  Dragon (string nm, int ni, int pdv, int fr, int flm,int pos=0) : Creature(nm,ni,pdv,fr,pos), portee_flamme_(flm) {} ;
  void voler(int pos) {
    position_ += pos;
  }

  void souffle_sur(Creature& bete) {
    if (vivant() and bete.vivant()) {
      
    }


  }



};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
