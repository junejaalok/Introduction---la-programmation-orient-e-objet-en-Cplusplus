#include <iostream>
#include <string>
#include <array>
#include <vector>
using namespace std;

/*******************************************
 * Completez le programme à partir d'ici.
 *******************************************/
class Mise {
protected:
  int mise_; // number of chips set
  int mise () const {
    return mise_;
  }

public:
  Mise () {};
  Mise (int n): mise_(n) {};
  virtual int gain (int winning_number) const = 0;
};

// Bet on number
class Pleine : public virtual Mise {
protected:
  int betonnum_; // bet has been put on this number
  static int factor;
public:
  Pleine (int cnt,int betnn) : Mise(cnt),betonnum_(betnn) {};
  Pleine() {};
  int gain (int winning_number) const {
    int amount=0;
    if (winning_number == betonnum_)
      amount = Mise::mise() * factor;
    return amount;
  }
};

int Pleine :: factor(35);

// Bet on red
class Rouges : public virtual Mise {
protected:
  //int betonred_;
  static int red[18];
public:
  Rouges(int cnt) : Mise(cnt) {};
  Rouges() {};

  int gain (int winning_number) const {
    int arraySize = sizeof(red)/sizeof(red[0]);
    int amount=0;
    for(int i = 0; i < arraySize; i++){
      if(red[i] == winning_number){
        amount = Mise::mise();
      }
    }
    return amount;
  }
};

int Rouges :: red[18]  = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

class Joueur : public virtual Pleine, public virtual Rouges {

private:
  string nom_;
  Mise* strt=nullptr; 

public:
  Joueur (string nm) : nom_(nm) {};
  Joueur(const Joueur& that) = delete;
  
  string nom () const {
    return nom_;
  }
  void set_strategie(Mise *strategie) {
    strt = strategie;
  }

  int mise() const {
    int cnt=0;
    if (strt != nullptr)
      cnt = mise();
    return cnt;
  }

  int gain (int winning_number) const {
    int amount = 0;
    if (strt != nullptr)
      amount = 0;
      //amount = strt->gain(winning_number);
    return amount;
  }
};

class Roulette : public Mise {
protected:
  vector<const Joueur*> pvec;
  int numdrawn_;
  static int casino_bal;

public:
  Roulette() {};
  Roulette(const Roulette& that) = delete;
  friend ostream& operator<<(ostream&, const Roulette&);

  void participe (const Joueur& op) {
    pvec.push_back(&op);
  }

  int bal () const {
    return casino_bal;
  }

  int tirage() const {
    return numdrawn_;
  }

  int nombre_participants() const {
    return pvec.size();
  }

  void rien_ne_va_plus(int valeur) {
    numdrawn_=valeur;
  }

  int gain_maison() const {
    int gain=0;
    for (vector<const Joueur*>::const_iterator it = pvec.begin() ; it != pvec.end(); ++it) {
      if (!(*it)->gain(tirage()))
        gain += (*it)->mise();
      else
        gain -= (*it)->gain(tirage());
    }
    return gain;
  }

  virtual int perte_mise(int player_bet) = 0;
  virtual void affiche (ostream& out) const = 0;

  void annoncer() const {
    cout << "Croupier : le numéro du tirage est le " << tirage() << endl;
    for (vector<const Joueur*>::const_iterator it = pvec.begin() ; it != pvec.end(); ++it) {
      if (!(*it)->gain(tirage()))
        cout << "Le joueur" << (*it)->nom() << " a misé " << (*it)->mise() << " et perd " << (*it)->perte_mise() << endl;
      else
        cout << "Le joueur" << (*it)->nom() << " a misé " << (*it)->mise() << " et gagne " << (*it)->gain(tirage()) << endl;
    }
    cout << "Gain/perte du casino : " << bal() << endl;
  }
};

ostream& operator<< (ostream& os,const Roulette& other) {
  other.affiche(os);
  return os;
}

int Roulette::casino_bal=0;

class RouletteFrancaise : public Roulette {
public:
  RouletteFrancaise () {};
  int perte_mise(int player_bet) {
    int tot=0;
    for (vector<const Joueur*>::const_iterator it = pvec.begin() ; it != pvec.end(); ++it) {
      tot += (*it)->mise();
    }
    return tot;
  }

  void afficher(ostream& out) {
    out << "Roulette française :" << endl;
  }
};



class RouletteAnglaise : public Roulette {
public:
  RouletteAnglaise () {};
  int perte_mise(int player_bet) {
    int tot=0;
    for (vector<const Joueur*>::const_iterator it = pvec.begin() ; it != pvec.end(); ++it) {
      tot += ((*it)->mise())/2;
    }
    return tot;
  }

  void afficher(ostream& out) {
    out << "Roulette anglaise :" << endl;
  }
};


/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

void simuler_jeu(Roulette& jeu)
{
  cout << jeu << " :" << endl;
  for (int tirage : array<int, 3>({ 12, 1, 31 })) {
    jeu.rien_ne_va_plus(tirage);
    jeu.annoncer();
    cout << endl;
  }
  cout << endl;
}

int main()
{
  Joueur joueur1("Dupond");
  Joueur joueur2("Dupont");
  Joueur joueur3("Dupond"); // un AUTRE joueur, du même nom

  Pleine p1(100, 1); // miser 100 jetons sur le 1
  Rouges p2(30);     // miser  30 jetons sur les rouges
  Pleine p3(20, 13); // miser  20 jetons sur le 13

  joueur1.set_strategie(&p1);
  joueur2.set_strategie(&p2);
  joueur3.set_strategie(&p3);

  RouletteAnglaise  jeu1;
  RouletteFrancaise jeu2;

  for (auto jeu : array<Roulette*, 2>({ &jeu1, &jeu2 })) {
    jeu->participe(joueur1);
    jeu->participe(joueur2);
    jeu->participe(joueur3); // c'est un autre joueur
    jeu->participe(joueur2); // c'est déjà un joueur du jeu
    simuler_jeu(*jeu);
  }

  return 0;
}
