#include <iostream>
using namespace std;

class A
{
private:
	int a;
public:
	A(int a1) : a(a1) { }
	int getA() const { return a; }
	void display() const { cout << "A" << getA() << " ";}
};

class B : public A
{
private:
	int b;
public:
	B(int a1, int b1) : A(a1), b(b1) { }
	int getB() const { return b; }
	void display() const { cout << "B"  << getA() << " ";}
};

void print(A const& obj) {
	obj.display();
}

int main() {
A a(1); B b(2,3); A c(b);
print(a);
print(b);
print(c);
return 0;
}

/*	class Rectangle {
	private:
		double h, l;
	public:
		Rectangle() = default;

		Rectangle(double h1, double l1)
		 : h(h1*2.0), l(l1*3.0)
		{ }

		Rectangle(Rectangle const& autre)
		 : h(autre.h/2.0), l(autre.l/3.0)
		{ }

		void display(){
			std::cout << h << ", " << l << std::endl;
		}
	};
	
	int main(){
		Rectangle r1(2.0, 4.0), r2(r1);

		r1.display();
		r2.display();
		return 0;	
	} */
/*
class Circle {
private:
  double radius;
public:
  void setRadius(double radius){
    this->radius = radius;
  }
};


class Point {
private:
  double x;
  double y;
public:
  void init() { x = 0.0; y = 0.0; }

  void setX(double newX) { x = newX; }
  void setY(double newY) { y = newY; }

  double getX() const { return x; }
  double getY() const { return y; }
};



int main() {
Point p1;
Point p2;

p1.init();
p2.init();
p1.setX(2.5);
p2.setY(4.0);
cout << p1.getX() << ", " << p1.getY() << endl;
cout << p2.getX() << ", " << p2.getY() << endl;
	return 0;
}

*/
