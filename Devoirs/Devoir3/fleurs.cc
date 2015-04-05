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
	friend ostream& operator<<(ostream&, const Fleur&);
    Fleur (string nm,string cl, double pb, bool prf=false, bool pr=false):nom(nm),couleur(cl),prix_base(pb),parfum_(prf),promotion(pr) {};

	double prix (void) const {
		if (promotion) 
			return prix_base/2.0;
		else 
			return prix_base;
	}

	bool parfum () const {
		return parfum_;
	}

	void affiche (ostream& sortie) const {
		if (parfum())
			sortie << nom << ' ' << couleur << " parfumée, prix : " << prix() << " CHF";
		else
			sortie << nom << ' ' << couleur << ", prix : " << prix() << " CHF";
}

    bool operator== (const Fleur&)const;

};

    bool Fleur::operator==(const Fleur& other) const {
        return (nom==other.nom && couleur==other.couleur && parfum()==other.parfum());
    }

    //Ref.: http://en.cppreference.com/w/cpp/language/operators
    //Ref.: https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx 
    ostream& operator<< (ostream& os,const Fleur& other) {
        other.affiche(os);
        return os;
    }


class Bouquet {
    
private:
    vector<Fleur> fvec;

public:

    Bouquet() {};
	//friend ostream& operator<<(ostream&, Bouquet&);
    bool parfum() const {
        for (vector<Fleur>::const_iterator it = fvec.begin() ; it != fvec.end(); ++it)
            if ((*it).parfum())
                return true;
        return false;
    }

    double prix() const {
        double ans=0.0;
	//cout << fvec.size() << endl;
        for (vector<Fleur>::const_iterator it = fvec.begin() ; it != fvec.end(); ++it)
            ans+=((*it).prix());
        if (parfum())
            ans*=2;
        return ans;
    }
 
   void affiche(ostream& bonq) const {
        if (fvec.size()==0)
            bonq << "Encore aucune fleur dans le Bouquet !" << endl;
        else {
            if(parfum())
                bonq << "Bouquet parfumé composé de :" << endl;
            else
                bonq << "Bouquet composé de :" << endl;
            for (vector<Fleur>::const_iterator it = fvec.begin() ; it != fvec.end(); ++it)
                bonq << *it << endl;
            bonq << "Prix total : " << prix() << " CHF" << endl;
        }
    }

    void operator+= (const Fleur& fl) {
            fvec.push_back(fl);
    }

//Ref.: http://stackoverflow.com/questions/4442477/remove-ith-item-from-c-stdvector
    void operator-= (const Fleur& fl) {
        for ( int i=fvec.size();i > 0;--i){
            if (fl == fvec[i-1]) {
		fvec[i-1] = fvec.back();		
		fvec.pop_back();
		i=fvec.size();
		}
	}
    }


    const Bouquet operator+ (const Fleur& fl) {
	*this += fl;
        return *this;
    }

    Bouquet& operator- (const Fleur& fl) {
	*this -= fl;
	return *this;
    }

};


   ostream& operator<< (ostream& os,Bouquet& other) {
        other.affiche(os);
        return os;
   }


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Fleur r1("Rose", "jaune", 1.5); // exemple de rose jaune inodore
  cout << r1 << endl;

  Fleur r2("Rose", "jaune", 3.0, true); // exemple de rose jaune parfumée
  Fleur r3("Rose", "rouge", 2.0, true, true); // exemple de rose rouge parfumée en promo
Bouquet b1;
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

  return 0;
}
