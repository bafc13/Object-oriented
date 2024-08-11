#include <iostream>
#include <utility>
#include <memory>
#include <vector>

/*Создать абстрактный базовый класс Body (тело) с виртуальными функциями вычисления
площади поверхности и объема. Создать производные классы: Parallelepiped (параллелепипед)
и Ball (шар) со своими функциями вычисления площади поверхности и объема.*/

class Body
{
public:
    Body(){ std::cout << "Body constructor" << std::endl; }
    virtual double calcSquare() const = 0;
    virtual double calcSize() const = 0;
    virtual void printFig() const = 0;
    virtual ~Body(){ std::cout << "Body deleted" << std::endl; }
     // создаем виртуальный деструктор, чтобы вызывался соответствующий
     //деструктор дочернего класса в случае, если удалим указатель на класс Body
};

class Parallelepiped: public Body //взял прямоугольный параллелепипед
{
private:
    double a_, b_, c_;
public:
    Parallelepiped(const double a = 1, const double b = 1, const double c = 1): a_(a), b_(b), c_(c)
    { //default constructor
        std::cout << "Parallelepiped constructor happend" << std::endl;
    }
    Parallelepiped(const Parallelepiped &fig):a_(fig.a_), b_(fig.b_), c_(fig.c_)
    { //copy constructor
        std::cout << "Par Copy constructor happend" << std::endl;
    }
    Parallelepiped(Parallelepiped &&fig): a_(std::exchange(fig.a_, 0)), b_(std::exchange(fig.b_, 0)), c_(std::exchange(fig.c_, 0))
    { //copy constructor
        std::cout << "Par Move constructor happend" << std::endl;
    }
    Parallelepiped& operator =(const Parallelepiped& fig)
    { //copy assignment
        a_ = fig.a_;
        b_ = fig.b_;
        c_ = fig.c_;
        std::cout << "Par Copy assignment happend" << std::endl;
        return *this;
    }
    Parallelepiped &operator =(Parallelepiped &&fig)
    { //move assignment
        a_ = std::exchange(fig.a_,0);
        b_ = std::exchange(fig.b_,0);
        c_ = std::exchange(fig.c_,0);
        std::cout << "Par Move assignment happend" << std::endl;
        return *this;
    }
    double calcSquare() const override
    { //высчитывание площади
        return (2*((a_*b_) + (b_*c_) + (a_*c_)));
    }
    double calcSize() const override
    { //высчитывание объёма
        return (a_*b_*c_);
    }
    void printFig() const override
    { //output variables
        std::cout << "Parallelepiped height = " << a_ << ", width = " << b_ << " and leght = " << c_ << std::endl;
        std::cout << "Parallelepiped square = " << calcSquare() << std::endl << "Parallelepiped size = " << calcSize() << std::endl;
    }
    ~Parallelepiped()
    { //destructor
        std::cout << "Parallelepiped deleted" << std:: endl;
    }
};

class Ball: public Body
{
private:
    double r_;
public:
    Ball(double r = 1):r_(r)
    { //default constructor
        std::cout << "Ball constructor happend" << std::endl;
    }
    Ball(const Ball & ball): r_(ball.r_)
    { //copy constructor
        std::cout << "Ball Copy constructor happend" << std::endl;
    }
    Ball(Ball &&ball): r_(std::exchange(ball.r_,0))
    { //move constructor
        std::cout << "Ball Move constructor happend" << std::endl;
    }
    Ball & operator =(const Ball &ball)
    { //copy assignment
        r_ = ball.r_;
        std::cout << "Ball Copy assignment happend" << std::endl;
        return *this;
    }
    Ball & operator =(Ball && ball)
    {
        r_ = std::exchange(ball.r_,0);
        std::cout << "Ball Move assignment happend" << std::endl;
        return *this;
    }

    double calcSquare() const override
    { //высчитывание площади
        return (4*3.14*r_*r_);
    }
    double calcSize() const override
    { //высчитывание объёма
        return (4/3*3.14*r_*r_*r_);
    }
    void printFig() const override
    { //output variables
        std::cout << "Ball radius = " << r_ << std::endl;
        std::cout << "Ball square = " << calcSquare() << std::endl << "Ball size = " << calcSize() << std::endl;
    }
    ~Ball()
    { //destructor
        std::cout << "Ball deleted" << std::endl;
    }
};

//Вызывающая программа должна продемонстрировать все варианты вызова виртуальных функций с
//помощью указателей на базовый класс. Написать функцию вывода, получающую параметры базового
//класса по ссылке и демонстрирующую виртуальный вызов.
//Использовать “умные” указатели и стандартные контейнеры.


int main()
{
    //CTOR TEST
   Ball first = Ball (1.2555);
   Ball second = first;
   Ball third = std::move(second);
   std::cout << "\n\n";
   //PTR TEST
   std::vector <std::unique_ptr<Body>> bod;
   bod.push_back(std::make_unique<Ball>(2.345));
   bod.push_back(std::make_unique<Parallelepiped>(13,23,14));

   for(int i = 0; i < 2; ++i)
   {
        bod[i].get()->printFig();
   }

}




