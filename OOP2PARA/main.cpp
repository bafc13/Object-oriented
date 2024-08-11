#include <QCoreApplication>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Animal
{
public:
    virtual string Voice() const = 0; // const - �� �� ������ ��������� �������
    virtual ~Animal() {cout << "Destroy animal!!!" << endl;} //���� ���� ������� ����� � ������������ ��������� - ������ ����������.

};

class Cat: public Animal
{
public:
    string Voice() const override
    {
        return "MEoooooW!!!";
    }
    ~Cat() {cout << "DESTROYING CAT!!!!!" << endl;}
};

class Dog: public Animal
{
public:
  string Voice() const override
  {
      return "Woof-woof!!!!";
  }
  ~Dog() {cout << "DESTROI DOG!" << endl;}
};

class Tiger: public Animal
{
public:
    string Voice() const override
    {
        return "RAAAAAAARRRR!";
    }
    ~Tiger() { cout << "BIG CAT KILLED!" << endl;}
};

using Zoo = vector<unique_ptr<Animal>>;


void Process(const Zoo& zoo)
{
    for(const auto& animal: zoo)
        cout << animal->Voice() << endl;
}

int main()
{
    Zoo zoo;
    //zoo.emplace_back(make_unique <Cat>());
    //zoo.push_back(new Dog); //old style, �������� � ������������
    //zoo.push_back(new Tiger);//push_back ��� ������ �� ��������

    zoo.emplace_back(new Cat);
    zoo.emplace_back(new Dog); //new style c++11, �������� ��� ��, ��� �����������
    zoo.emplace_back(new Tiger);

    Process(zoo);

//    for(const auto& animal: zoo)
//        delete animal;



}
