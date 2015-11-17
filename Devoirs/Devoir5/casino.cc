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

public:
  //Mise () {};
  Mise (int n): mise_(n) {};
  virtual ~Mise() {};

  virtual int mise () const final {
    return mise_;
  }

  virtual int gain (int winning_number) const = 0;
};

// Bet on number
class Pleine : public virtual Mise {
protected:
  int betonnum_; // bet has been put on this number
  static int factor;
public:
  Pleine (int cnt,int betnn) : Mise(cnt),betonnum_(betnn) {};
//  Pleine() {};
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
//  Rouges() {};

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

class Joueur {

private:
  string nom_;
  Mise* strt; 

public:
  Joueur (string nm) : nom_(nm) {strt=nullptr;}
  Joueur(const Joueur& that) = delete;
  
  string nom () const {
    return nom_;
  }
  void set_strategie(Mise *strategie) {
//    cout << "strategy is: " << strategie << endl;
    strt = strategie;
//    cout << "strt is: " << strt << endl;
  }

  int mise() const {
    int cnt=0;
    if (strt != nullptr)
//      cout << "mise is: " << Mise::mise() << endl;
      cnt = strt->mise();
//    cout << "cnt is " << cnt << endl;
    return cnt;
  }

  int gain (int winning_number) const {
    int amount = 0;
    if (strt != nullptr)
      amount = strt->gain(winning_number);
    return amount;
  }
};

class Roulette {
protected:
  vector<const Joueur*> pvec;
  int numdrawn_;

public:
  Roulette() {};
  virtual ~Roulette () {};
  Roulette(const Roulette& that) = delete;
  friend ostream& operator<<(ostream&, const Roulette&);

  virtual void participe (const Joueur& op) {
    bool found=false;

    for (int i=0;i<nombre_participants();i++)
      if (pvec[i] == &op)
        found=true;

    if (!found)
      pvec.push_back(&op);
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
      if (!(*it)->gain(tirage())) {
//        cout << "gain: " << this->perte_mise((*it)->mise()) << endl;
        gain += this->perte_mise((*it)->mise());
      }
      else { 
//        cout << "loss: " << (*it)->gain(tirage()) << endl;
        gain -= (*it)->gain(tirage());
      }
    }
    return gain;
  }

  virtual int perte_mise(int player_bet) const = 0;
  virtual void afficher (ostream& out) const = 0;

  void annoncer() const {
    cout << "Croupier : le numéro du tirage est le " << tirage() << endl;
    for (vector<const Joueur*>::const_iterator it = pvec.begin() ; it != pvec.end(); ++it) {
//      cout << "size is : " << pvec.size() << endl;
      if (!(*it)->gain(tirage()))
        cout << "Le joueur " << (*it)->nom() << " a misé " << (*it)->mise() << " et perd " << this->perte_mise((*it)->mise()) << endl;
      else
        cout << "Le joueur " << (*it)->nom() << " a misé " << (*it)->mise() << " et gagne " << (*it)->gain(tirage()) << endl;
    }
    cout << "Gain/perte du casino : " << gain_maison() << endl;
  }
};

ostream& operator<< (ostream& os,const Roulette& other) {
  other.afficher(os);
  return os;
}

class RouletteFrancaise : public Roulette {
public:
  RouletteFrancaise () {};
  int perte_mise(int player_bet) const {
    return player_bet;
  }
  

  void afficher(ostream& out) const {
    out << "Roulette française";
  }
};


class RouletteAnglaise : public Roulette {
public:
  RouletteAnglaise () {};
  int perte_mise(int player_bet) const {
    return player_bet/2;
  }

  void participe (const Joueur& op) {
    bool found=false;

    for (int i=0;i<nombre_participants();i++) {
      if (pvec[i] == &op)
        found=true;
    }

    if (!found and nombre_participants() < 10)
      pvec.push_back(&op);
  }


  void afficher(ostream& out) const {
    out << "Roulette anglaise";
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
