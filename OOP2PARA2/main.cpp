#include <iostream>
#include <vector>
#include <memory> // умные указатели тут
#include <utility> // интересные функции

class Monster
{ //ху€рим правило 6: если один из конструкторов понадобилс€, то делаем ¬—≈ 6!

public:
    Monster(int health = 10): health_(health){ std:: cout << "construct happend " << health_ <<  std::endl;}
    Monster(const Monster& m): health_(m.health_){std:: cout << "Copy construtcor happend" << health_ << std:: endl;}

    Monster& operator = (Monster m)
    {
        health_ = m.health_;
        std:: cout << "Copy assingment" << health_ << std::endl;
        return *this;
    }
    Monster& operator ++ () // prefix
    {
        ++health_;
        return *this;
    }
    Monster& operator ++ (int   ) // after fix!
    {
        Monster old = *this;
        ++health_;
        return old;
    }
    ~Monster()
    {
        std::cout << "MONSTRRR KILLED!!!" << health_ << std::endl;
    }
private:
    int health_;
};


int main()
{
    //Monster m;
    //m++;
    //std::cout << "huy" << std::endl;
    //++m;
    //std::cout << "ne huy" << std::endl;

    //Monster mas[5];

    std::cout << "Hello World!" << std::endl << std::endl;
    std::vector<Monster> vec;

    std::cout << "Hello World!" << std::endl << std::endl;
    vec.push_back(Monster());
    std::cout << "Hello World!" << std::endl << std::endl;
    Monster m;
    m = vec[0];
    return 0;
}
