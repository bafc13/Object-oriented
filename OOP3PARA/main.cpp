#include <iostream>
#include <vector>
#include <memory> // умные указатели тут
#include <utility> // интересные функции


//подумать о возвращении по ссылке, о чём-то подумать...
//если С = А + Б, то не портить А, надо возвращать не по ссылке, а по значению это всё дело, ибо мало ли
// нам понадобится ещё А и Б.
//в другом double get_x const написать и т.д. в других геттерах, дописать всё, что было в документе сверху, по типу
//инитов ебаных




class Monster
{ //хуярим правило 6: если один из конструкторов понадобился, то делаем ВСЕ 6!

public:
    Monster(int health = 10): health_(health){ std:: cout << "construct happend " << health_ <<  std::endl;}
    Monster(const Monster& m): health_(m.health_){std:: cout << "Copy construtcor happend" << health_ << std:: endl;}


    Monster& operator =(const Monster& m) // копирующее присваивание
    {
        health_ = m.health_;
        std:: cout << "Copy assingment" << health_ << std::endl;
        return *this;
    }

    Monster(Monster&& other): health_(std::exchange(other.health_, 0)){std:: cout << "Move construtcor happend" << health_ << std:: endl;}
        //&& - это перемещающая ссылка!
    Monster& operator =(Monster&& other) // перемещающее присваивание
    {
        health_ = std::exchange(other.health_,0);
        std:: cout << "Move assingment" << health_ << std::endl; //
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
    int GetHealth() const{return this->health_;}
    void SetHealth(int health_) { this->health_ =health_;}
private:
    int health_;
};

Monster ByValue(Monster m)
{
    m.SetHealth(m.GetHealth() * 10);
    return m;
}

Monster& ByRef(Monster& m)
{
    m.SetHealth(m.GetHealth() * 10);
    return m;
}

Monster& ByMoveRef(Monster&& m)
{
    m.SetHealth(m.GetHealth() * 10);
    return m;
}


int main()
{
    //Ex 1
    /*
    Monster m;
    ++m;
    std::cout << "smthng" << std:: endl;
    m++;
    std:: cout << "smthng" << std:: endl;*/
    //EX 2
//    Monster mas[5];
//    std::vector<Monster> vec(5);
    //EX 3
    /*
    std::vector<Monster> vec;
    vec.push_back(Monster());
    vec.push_back(Monster());*/

    //ex 4

//    Monster m;
//    m = ByValue(m);
//    m = ByRef(m);
//    m = ByMoveRef(std::move(m));

    //EX 5
//    Monster m, m1;
//    m1 = std::move(m); //МУВ ОБЫЧНО ИСПОЛЬЗУЮТ ЧТОБ ИЗ ОБЫЧНОЙ ССЫЛКИ СДЕЛАТЬ ПЕРЕМЕЩАЕМУЮ

//    std::cout << "bafc13 did it " << std::endl;

    //EX 6
//    std::unique_ptr<Monster> pm = std::make_unique <Monster>();



    //напишите функцию которая работает с уникальным указателем!!!!



    std::cout << "bafc13 swag" << std::endl;

    return 0;
}
