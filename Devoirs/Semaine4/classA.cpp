#include <iostream>
#include <string>
#include <cmath>
using namespace std;


class A
{
protected:
    static int x;
};

class B : public A
{
public:
    int y;

    int gety() const { return y; }
    void sety(int d) { y = d; }

    int getx() const { return x; }
    void setx(int d) { x = d; }
};

int main()
{
    B obj;

    // compiles cleanly because B::sety/gety are public
    obj.sety(10);
    std::cout << obj.gety() << '\n';

    // compiles cleanly because B::setx/getx are public, even though
    // they touch A::x which is protected
    obj.setx(42);
    std::cout << obj.getx() << '\n';

    // compiles cleanly because B::y is public
    obj.y = 20;
    std::cout << obj.y << '\n';

    // compilation errors because A::x is protected
    obj.x = 84;
    std::cout << obj.x << '\n';
}