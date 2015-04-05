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
//  friend const Construction operator^(Construction, const Construction&);
//  friend const Construction operator-(Construction, const Construction&);
//  friend const Construction operator+(Construction, const Construction&);

  Construction& operator^= (const Construction& b) {
	int a_height=contenu.size();
	int b_height=b.contenu.size();
	for(int i=0;i<b_height;i++) {
	   contenu.push_back(b.contenu[i]);
	}
	return *this;
  }

  Construction& operator-= (const Construction& b) {
	int a_height=contenu.size();
	int b_height=b.contenu.size();
	if (a_height <= b_height) {
		for(int i=0;i<a_height;i++) {
			int a_depth=contenu[i].size();
			int b_depth=b.contenu[i].size();
			for(int j=0;j < b_depth;j++) {
				contenu[i].push_back(b.contenu[i][j]);
			}
		}
	}
	return *this;
  }

  Construction& operator+= (const Construction& b) {
	int a_height=contenu.size();
	int b_height=b.contenu.size();
	if (a_height <= b_height) {
		for(int i=0;i<a_height;i++) {
			int a_depth=contenu[i].size();
			int b_depth=b.contenu[i].size();
			if (a_depth <= b_depth ) {
				for(int j=0;j < a_depth;j++) {
					int a_width=contenu[i][j].size();
					int b_width=b.contenu[i][j].size();
					for(int k = 0; k < b_width; k++) {
						contenu[i][j].push_back(b.contenu[i][j][k]);
					}
				}
			}
		}
	}
	return *this;
  }
};
  
  ostream& Construction :: afficher (ostream& os) const {
    //Ref.: https://www.daniweb.com/software-development/cpp/threads/137814/iterate-a-3d-vector
	//Ref.: https://www.daniweb.com/software-development/cpp/threads/161323/populating-a-3d-vector-array
    typedef vector<Brique> Brique1D;
    typedef vector<Brique1D> Brique2D;
    typedef vector<Brique2D> Brique3D;
	for (int i = contenu.size() - 1; i>=0;--i) {
      	os << "Couche " << i << " :" << endl;
		for (int j = contenu[i].size() -1; j >= 0; --j) {
			for (int k = 0; k<contenu[i][j].size();++k) {
				os << contenu[i][j][k];
			}
			os << endl;
		}
		//os << endl;
	}
	return os;
}
/*
    for (Brique3D::const_reverse_iterator i = contenu.rbegin(); i != contenu.rend(); ++i) {
      os << "Couche " << num << " :" << endl;
      for (Brique2D::const_reverse_iterator j = i->rbegin(); j != i->rend(); ++j) {
        for (Brique1D::const_iterator k = j->begin(); k != j->end(); ++k) {
          os << *k;
        }
      }
	  num--;
      os << endl;
    }
    return os;
  }
*/
  ostream& operator<< (ostream& os,const Construction& other) {
    other.afficher(os);
    return os;
  }  

  const Construction operator^ (const Construction& a, const Construction& b) {
	Construction temp(a);	
	temp ^= b;
	return temp;
  }

  const Construction operator- (const Construction& a, const Construction& b) {
	Construction temp(a);
	temp -= b;
	return temp;
  }

  const Construction operator+ (const Construction& a, const Construction& b) {
	Construction temp(a);
	temp += b;
	return temp;
  }


const Construction operator*(unsigned int n, const Construction& a){
	Construction temp(a);
	for (int i=0;i<n-1;i++)
		temp = temp + a;
	return temp;
}

const Construction operator/(unsigned int n, const Construction& a){
	Construction temp(a);
	for (int i=0;i<n-1;i++) 
		temp = temp ^ a;
	return temp;
}

const Construction operator%(unsigned int n, const Construction& a){
	Construction temp(a);
	for (int i=0;i<n-1;i++) 
		temp = temp - a;
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
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
