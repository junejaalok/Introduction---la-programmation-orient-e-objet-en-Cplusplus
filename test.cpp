#include <iostream>
using namespace std;

	class Number {
	private:
		int n;
	public:
		Number() : n(0) {
			std::cout << n;
		}

		Number( int nn )
		 : n(nn)
		{
			std::cout << n;
		}

		Number(Number const& otherNum)
		 : n(otherNum.n+1)
		{
			std::cout <<  n;
		}

		void display() { std::cout << n; }
		void increase() { n += 1; }
	};
	
	int main(){
		Number a, b(1), c(b);
		b.increase();
		c.display();
		b.display();
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
