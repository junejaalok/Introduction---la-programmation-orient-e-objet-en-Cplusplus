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


  Construction& operator^= (const Construction& b) {
//    typedef vector<Brique> Brique1D;
//    typedef vector<Brique1D> Brique2D;
//    typedef vector<Brique2D> Brique3D;
//	cout << b.contenu[0][0].size() << endl;
	for(int i=0;i<1;i++) {
	   contenu.push_back(b.contenu[i]);
	}
	return *this;

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
	}


    //Brique3D vector1; 
//    Brique3D::const_iterator OneDStart = contenu.begin();
//    Brique3D::const_iterator OneDEnd = contenu.end();
//    Brique2D::const_iterator 

//    contenu.insert (contenu.begin(),b.contenu.begin(),b.contenu.end());
//    this->contenu[0].push_back(b.contenu);
//    contenu[0][0][0].push_back(b.contenu);
//    cout << contenu.size() ;

//  Brique3D::const_iterator i = this->contenu.end();
//  Brique3D::const_iterator ib = b.contenu.begin();
//  Brique3D::const_iterator ibe = b.contenu.end();
//  cout << contenu[0][0][0];
//  contenu[1][0][].push_back(b.contenu[0][0][0]);

//  this->contenu.insert(i->begin(),ib->begin(),ib->end());
//  this->contenu.insert(this->contenu.begin(),b.contenu.begin(),b.contenu.end());
//  contenu.push_back(vector<vector<Brique> >());
//  contenu[0].push_back(vector<Brique>());
//  contenu[0][0].push_back(b.contenu[0][0][0]);
/*
    for (; ib != b.contenu.end(); ++i,++ib) {
      for (Brique2D::const_iterator j = i->begin(); j != i->end(); ++j,jb++) {
        for (Brique1D::const_iterator k = j->begin(); k != j->end(); ++k,kb++) {
          cout << "Hello" << endl;
        }
      }
    }
*/

//  contenu[0].insert(contenu.end(), contenu.begin(), contenu.end());*/
//  vector<vector<vector<Brique> > > :: iterator it;
//  it = b.contenu.begin();
  //}

};
  
  ostream& Construction :: afficher (ostream& os) const {
    //Ref.: https://www.daniweb.com/software-development/cpp/threads/137814/iterate-a-3d-vector
    typedef vector<Brique> Brique1D;
    typedef vector<Brique1D> Brique2D;
    typedef vector<Brique2D> Brique3D;

    //os << "Couche " << numéro << " :" << endl;
    for (Brique3D::const_reverse_iterator i = this->contenu.rbegin(); i != this->contenu.rend(); ++i) {
      for (Brique2D::const_reverse_iterator j = i->rbegin(); j != i->rend(); ++j) {
        for (Brique1D::const_reverse_iterator k = j->rbegin(); k != j->rend(); ++k) {
          os << *k;
        }
        os << endl;
      }
    }
    return os;
  }

  ostream& operator<< (ostream& os,const Construction& other) {
    other.afficher(os);
    return os;
  }  

/*
const Construction operator*(unsigned int n, Construction const& a)
{
}

const Construction operator/(unsigned int n, Construction const& a)
{
}

const Construction operator%(unsigned int n, Construction const& a)
{
}
*/
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
/*
  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;
*/
  Construction maison(mur);
  Construction toit(toitD);
  maison ^= toit;
  cout << maison << endl;
  return 0;
}