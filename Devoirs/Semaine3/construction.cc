#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
    Brique(Forme f, Couleur c):forme(f),couleur(c) {};
    ostream& afficher(ostream& sortie) const ;
    friend ostream& operator<<(ostream&, const Brique&);

};

    ostream& Brique :: afficher (ostream& os) const {
        if (!couleur.empty())
          os << '(' << forme << ", " << couleur << ')';
        else
          os << forme;
        return os;
    }

    ostream& operator<< (ostream& os,const Brique& other) {
      return other.afficher(os);
    }

class Construction
{
  friend class Grader;

private:
  vector<vector<vector<Brique> > > contenu;

public:
  //Ref. : http://stackoverflow.com/questions/9812411/trying-to-create-a-3-dimensional-vector-in-c
  Construction(Brique br):contenu(1,vector<vector<Brique> >(1,vector <Brique>(1,br))) {};
  ostream& afficher(ostream& sortie) const ;
  friend ostream& operator<<(ostream&, const Construction&);
  friend Construction operator^(const Construction&, const Construction&);
  friend Construction operator-(const Construction&, const Construction&);
  friend Construction operator+(const Construction&, const Construction&);

  Construction& operator^= (const Construction& b) {
//    typedef vector<Brique> Brique1D;
//    typedef vector<Brique1D> Brique2D;
//    typedef vector<Brique2D> Brique3D;
	for(int i=0;i<1;i++) {
	   contenu.push_back(b.contenu[i]);
	}
	return *this;
  }

  Construction& operator-= (const Construction& b) {
	if (contenu.size() < b.contenu.size()) {
		for(int i=0;i<contenu.size();i++) {
		   contenu.push_back(vector<vector<Brique> >());
			for(int j=0;j < 1;j++) {
				contenu[i].push_back(b.contenu[i][j]);
			}
		}
	}
	return *this;
  }

  Construction& operator+= (const Construction& b) {
	if (contenu.size() < b.contenu.size()) {
		for(int i=0;i<contenu.size();i++) {
			contenu.push_back(vector<vector<Brique> >());
			if (contenu[i].size() < b.contenu[i].size() ) {
				for(int j=0;j < contenu[i].size();j++) {
					contenu[i].push_back(vector<Brique>());
					for(int k = 0; k < 1; k++) {
						contenu[i][j].push_back(b.contenu[i][j][k]);
					}
				}
			}
		}
	}
	return *this;
  }


//	for (int i = 0; i < 1; i++) {
//	cout << "Hewlo" << endl;
//		this->contenu.push_back(vector<vector<Brique> >());
//		for(int j=0;j < 1;j++) {
//			contenu[i].push_back(vector<Brique>());
//			for(int k = 0; k < 1; k++) {
//				cout << contenu.size() << endl;
//				cout << contenu[i].size() << endl;
//				cout << contenu[i][j].size() << endl;
//				//contenu[i][j].push_back(1000);
//				cout << "--------------" << endl;
//			}
//		}
//	}
};
  
  ostream& Construction :: afficher (ostream& os) const {
    //Ref.: https://www.daniweb.com/software-development/cpp/threads/137814/iterate-a-3d-vector
    typedef vector<Brique> Brique1D;
    typedef vector<Brique1D> Brique2D;
    typedef vector<Brique2D> Brique3D;
	int num =0;

    os << "Couche " << num << " :" << contenu.size() << endl;
    for (Brique3D::const_reverse_iterator i = contenu.rbegin(); i != contenu.rend(); ++i) {
	cout << "3D" << endl;
      for (Brique2D::const_reverse_iterator j = i->rbegin(); j != i->rend(); ++j) {
	cout << "2D" << endl;
        for (Brique1D::const_iterator k = j->begin(); k != j->end(); ++k) {
          os << *k;
		  num++;
        }
      }
        os << endl;
    }
    return os;
  }

  ostream& operator<< (ostream& os,const Construction& other) {
    other.afficher(os);
    return os;
  }  

  Construction operator^ (const Construction& a, const Construction& b) {
	Construction temp(a);
	temp ^= a;
	temp ^= b;
	return temp;
  }

  Construction operator- (const Construction& a, const Construction& b) {
	Construction temp(a);
	temp -= a;
	temp -= b;
	return temp;
  }

  Construction operator+ (const Construction& a, const Construction& b) {
	Construction temp(a);
	temp += a;
	temp += b;
	return temp;
  }


const Construction operator*(unsigned int n, Construction const& a){
	Construction temp(a);
	for (int i=0;i<n;i++) {
		temp=temp + a;
		cout << "I am here in *   " << i << "           ";
		cout << temp << endl;
	}
	return a;
}

const Construction operator/(unsigned int n, Construction const& a){
	Construction temp(a);
	for (int i=0;i<n;i++) 
		temp ^= a;
	return temp;
}

const Construction operator%(unsigned int n, Construction const& a){
	Construction temp(a);
	for (int i=0;i<n;i++) 
		temp -= a;
	return temp;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
Construction maison( largeur * mur );  
//  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );
//cout << maison << endl;/*
  // on construit le toit
//  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
//  toit ^= profondeur % (vide + toitG + toitD);
//cout << toit << endl;/*
  // on pose le toit sur les murs
//  maison ^= toit;

  // on admire notre construction
//  cout << maison << endl;

//  Construction maison(mur);
//  Construction toit(toitD);
//  maison += toit;
//  maison -= toit;
//  maison += toit;
cout << maison << endl;
  return 0;
}
