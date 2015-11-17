#include <vector>
#include <iostream>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme à partir d'ici.
 *******************************************/
class Affichable {

public:
  //Pure virtual function
  virtual void affiche (ostream& sortie) const = 0;

};

class OptionVoyage : public Affichable {

protected:
  string name_;
  double flat_fee_;

public:
  OptionVoyage(string nm, double ff):name_(nm),flat_fee_(ff) {};
  friend ostream& operator<<(ostream&, const OptionVoyage&);

  string nom() const {
    return name_;
  }

  virtual double prix() const {
    return flat_fee_;
  }

  void affiche (ostream& sortie) const {
    sortie << nom() << " -> " << this->prix() << "CHF" << endl;
  }
};

  ostream& operator<< (ostream& os,const OptionVoyage& other) {
    other.affiche(os);
    return os;
  }

class Sejour : public OptionVoyage {

private:
  int nights_;
  double ppn_;

public:
  Sejour (string nm, double ff, int ngt, double prc):OptionVoyage(nm,ff),nights_(ngt),ppn_(prc) {};
  double prix () const {
    return (( nights_ * ppn_ ) + OptionVoyage::prix());
  }

};

class Transport : public OptionVoyage {

private:
  bool duration_;
  static double TARIF_LONG;
  static double TARIF_BASE;

public:
  Transport (string nm, double ff, bool dur=false):OptionVoyage(nm,ff),duration_(dur) {};
  double prix() const {
    if (duration_)
      return TARIF_LONG;
    else
      return (TARIF_BASE + prix());
  }
};

double Transport :: TARIF_LONG(1500.0);
double Transport :: TARIF_BASE(200.0);

class OptionCombinee : public Sejour, public Transport,public OptionVoyage{
public:
    OptionCombinee (string nm, double ff, int ngt, double prc,bool dur=false):Sejour(nm,ff,ngt,prc),Transport(nm,ff,dur),OptionVoyage(nm,ff) {};
    double prix() {
        return (0.75 * ( Sejour::prix() + Transport::prix() ));
    }
};

class KitVoyage {
private:
    vector <const OptionVoyage*> ovec;
    string dep_;
    string des_;

public:
    KitVoyage(string depr,string dest):dep_(depr),des_(dest) {};
    friend ostream& operator<<(ostream&, const KitVoyage&);
    double prix(void) const {
        double tot;
        for (vector<const OptionVoyage*>::const_iterator it = ovec.begin() ; it != ovec.end(); ++it) {
            tot += (*it)->prix();
        }
        cout << tot << endl;
        return tot;
    
    }
    void ajouter_option(const OptionVoyage& op) {
        ovec.push_back(&op);
    }
    
    void annuler(){
        ovec.clear();
    }
  
    void affiche (ostream& sortie) const {
        if (ovec.empty())
            sortie << "Voyage de "<< dep_ << " a " << des_ << ": vous n'avez rien réservé !" << endl;
        else {
            sortie << "Voyage de "<< dep_ << " a " << des_ << ": vous n'avez rien réservé !" << endl;
            for (vector<const OptionVoyage*>::const_iterator it = ovec.begin() ; it != ovec.end(); ++it) {
               sortie << *it;
            }
            sortie << "Prix total : " << prix() << " CHF" << endl;
        }
   }
};

  ostream& operator<< (ostream& os,const KitVoyage& other) {
    other.affiche(os);
    return os;
  }



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
