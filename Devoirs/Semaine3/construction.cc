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


  void operator^= (const Construction& b) const {
    typedef vector<Brique> Brique1D;
    typedef vector<Brique1D> Brique2D;
    typedef vector<Brique2D> Brique3D;

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
//  cout << this[0][0][0];
//  contenu[1].push_back(b.contenu[0]);
  this->contenu[1].push_back(b.contenu[0]);
//  icontenu.insert(i->begin(),ib->begin(),ib->end());
//  contenu.push_back(vector<vector<Brique> >());
//  contenu[0].push_back(vector<Brique>());
//  contenu[0][0].push_back(value);
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
  }

};
  
  ostream& Construction :: afficher (ostream& os) const {
    //Ref.: https://www.daniweb.com/software-development/cpp/threads/137814/iterate-a-3d-vector
    typedef vector<Brique> Brique1D;
    typedef vector<Brique1D> Brique2D;
    typedef vector<Brique2D> Brique3D;

//    Brique3D vector1; 
//    Brique3D::iterator OneDStart = this.begin();
//    Brique3D::iterator OneDEnd = this.end();
    //os << "Couche " << numéro << " :" << endl;
    for (Brique3D::const_iterator i = this->contenu.begin(); i != this->contenu.end(); ++i) {
      for (Brique2D::const_iterator j = i->begin(); j != i->end(); ++j) {
        for (Brique1D::const_iterator k = j->begin(); k != j->end(); ++k) {
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

//void Construction :: operator^= (const Construction& b) {
  //Construction temp;
//  b.contenu.insert(b.contenu.end(), contenu.begin(), contenu.end());
//  vector<vector<vector<Brique> > > :: iterator it;
//  it = b.contenu.begin();


//}
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
