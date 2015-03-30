// inserting into a vector
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
  vector<vector<vector<int> > > dest {{{11}}};
  vector<vector<vector<int> > > src {{{12}}};

//  vector<vector<vector<int> > > dest {{{11,12,13}}};
//  vector<vector<vector<int> > > dest {{{11,12,13,14,15}}};
//  vector<vector<vector<int> > > src {{{46,47,48,49,40}}};
//  vector<vector<vector<int> > > dest {{{11,12,13,14,15},{21,22,24,25},{36,37,38,39,310}}};
//  vector<vector<vector<int> > > src {{{46,47,48,49,40},{55,56,57,58,59},{64,74,84,94,44}}};

//  dest.insert(dest.end(),src.begin(),src.end());

 // cout << dest[0][0] << endl;


    typedef vector<int> int1D;
    typedef vector<int1D> int2D;
    typedef vector<int2D> int3D;

    int3D::iterator i = dest.begin();
    int2D::iterator j = i->begin();
    int3D::iterator n = src.begin();

	cout << dest.size() << endl;
	cout << dest[0].size() << endl;
	cout << dest[0][0].size() << endl;
	cout << "========================" << endl;


	for (int i = 0; i < 1; i++) {
		dest.push_back(src[i]);
//		for(int j=0;j < 1;j++) {
//			dest[i].push_back(src[0]);
//			for(int k = 0; k < 1; k++) {
				cout << dest.size() << endl;
				cout << dest[i].size() << endl;
//				cout << dest[i][j].size() << endl;
//				dest[i][j].push_back(1000);
				cout << "--------------" << endl;
//			}
//		}
	}

//    for (int3D::iterator i = src.begin(); i != src.end(); ++i) {
//      for (int2D::iterator j = i->begin(); j != i->end(); ++j) {
        //for (int1D::iterator k = j->begin(); k != j->end(); ++k) {
//          dest.push_back(*j);
        //}
//      }
//    }
	
	int cnt = 0;
    for (int3D::iterator i = dest.begin(); i != dest.end(); ++i) {
	cout << "3D   " << cnt << endl;
      for (int2D::iterator j = i->begin(); j != i->end(); ++j) {
	cout << "2D   " << cnt << endl;
        for (int1D::iterator k = j->begin(); k != j->end(); ++k) {
	cout << "1D   " << cnt << endl;
          cout << *k << ' ';
			cnt++;
        }
      }
    }

/*
    // print plane by plane then modify cube elements
    for (int i = 0; i < (int)dest.size(); ++i)
    {
    cout << i << ":\n"; // i-th plane
    for (int j = 0; j < (int)dest[i].size(); ++j)
    {
    for (int k = 0; k < (int)dest[j].size(); ++k)
    {
    cout << '\t' << dest[i][j][k];
    dest[i][j][k] = 1; // why? See below
    }
    cout << "\n";	
    }
    }
    cout << endl;
*/
/*

  std::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  std::vector<int> anothervector {{6,7,8,9,10}};
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
*/
  return 0;
}
