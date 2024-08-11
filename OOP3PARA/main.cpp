#include <iostream>
#include <vector>
#include <memory> // ����� ��������� ���
#include <utility> // ���������� �������


//�������� � ����������� �� ������, � ���-�� ��������...
//���� � = � + �, �� �� ������� �, ���� ���������� �� �� ������, � �� �������� ��� �� ����, ��� ���� ��
// ��� ����������� ��� � � �.
//� ������ double get_x const �������� � �.�. � ������ ��������, �������� ��, ��� ���� � ��������� ������, �� ����
//������ ������




class Monster
{ //������ ������� 6: ���� ���� �� ������������� �����������, �� ������ ��� 6!

public:
    Monster(int health = 10): health_(health){ std:: cout << "construct happend " << health_ <<  std::endl;}
    Monster(const Monster& m): health_(m.health_){std:: cout << "Copy construtcor happend" << health_ << std:: endl;}


    Monster& operator =(const Monster& m) // ���������� ������������
    {
        health_ = m.health_;
        std:: cout << "Copy assingment" << health_ << std::endl;
        return *this;
    }

    Monster(Monster&& other): health_(std::exchange(other.health_, 0)){std:: cout << "Move construtcor happend" << health_ << std:: endl;}
        //&& - ��� ������������ ������!
    Monster& operator =(Monster&& other) // ������������ ������������
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
//    m1 = std::move(m); //��� ������ ���������� ���� �� ������� ������ ������� ������������

//    std::cout << "bafc13 did it " << std::endl;

    //EX 6
//    std::unique_ptr<Monster> pm = std::make_unique <Monster>();



    //�������� ������� ������� �������� � ���������� ����������!!!!



    std::cout << "bafc13 swag" << std::endl;

    return 0;
}
