#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main()
{

	vector <vector <int> > v1 = {{1},{2}};
	vector <vector <int> > v2 = {{3},{4}};
	vector<vector<int> >::iterator it1,it2;
	int A,B;

	for (it1 = v1.begin(); it1 != v1.end(); it1++)
	{
	    for (it2 = v2.begin(); it2 != v2.end(); it2++)
	    {
		vector<int>::iterator it6,it7;
		it6=it1->end();
		it7=it2->begin();

		if (*it6 == A && *it7 == B)
		{
		    vector<int> v3(it1->begin(),it1->end());
		    v3.insert(v3.end(),it2->begin(),it2->end());    
		}
		else if (*it6 == B && *it7 == A)
		{
		    vector<int> v3(it1->begin(),it1->end());
		    v3.insert(v3.end(),it2->begin(),it2->end());               
		}
	    }
	}

	cout << *it1 << endl;
	return 0;
}

