#include <iostream>
#include <string>
#include <vector>
using namespace std;


    // int base for simplicity
    typedef std::vector<int> int1D;
    typedef std::vector<int1D> int2D;
    typedef std::vector<int2D> int3D;
    int main()
    {
    int dim = 3;
    int3D v;
    // initiate the cube so v[i][j][k] == ijk...
    v.resize(dim);
    for (int i = 0; i < (int)v.size(); ++i)
    {
    v[i].resize(dim);
    for (int j = 0; j < (int)v[i].size(); ++j)
    {
    v[i][j].resize(dim);
    for (int k = 0; k < (int)v[i][j].size(); ++k)
    v[i][j][k] = (i+1)*100+(j+1)*10+(k+1);
    }
    }

    // print plane by plane then modify cube elements
    for (int i = 0; i < (int)v.size(); ++i)
    {
    cout << i << ":\n"; // i-th plane
    for (int j = 0; j < (int)v.size(); ++j)
    {
    for (int k = 0; k < (int)v.size(); ++k)
    {
    cout << '\t' << v[i][j][k];
    v[i][j][k] = 1; // why? See below
    }
    cout << "\n";	
    }
    }
    cout << endl;

    // calculate sum of elements i*j*k*1 then go to Fortran...
    int sum = 0;
    for (size_t i = 0; i < v.size(); ++i)
    for (size_t j = 0; j < v[i].size(); ++j)
    for (size_t k = 0; k < v[i][j].size(); ++k)
    sum += v[i][j][k];
    // must be 3*3*3 == 27...
    cout << "Sum(v): " << sum << endl;
    return 0;
    }
