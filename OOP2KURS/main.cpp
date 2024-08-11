#include <QCoreApplication>
#include <Vector>
#include <cassert>
#include <deque>
#include <iostream>

class array_of_ints1
{
    int data[10] = {};

public:
    int size() const { return 10; } //���� ������� �� ������ ��������� ������� - ��� ������ ���� �����������!!!
                                    //const ��������� ������� �����������, ��� ��� ������� ������� � ������ �������������� ���
    int& at(int i) { return data[i]; }
};


void double_each_element(array_of_ints1 &arr)
{
    for(int i = 0; i<arr.size(); i++){ //��� ����������� ���������� �������������� ����������� i, � ��� ��� ���������� ��� �� ����������.
        arr.at(i) += arr.at(i);
    }
}


class container_of_ints
{
public:  //virtual - ������� � ���������� ��������������� ���� �������, � ��, ��� ����� ����� 0 - ������� � ���, ��� ��� ��������� ����� ����������� ��������
    //� ����� �������� ����� �����������. ������� ��� ��������� ������, �� �� ���������� ��������� ������
    virtual int size() const = 0; //���� ������� �� ������ ��������� ������� - ��� ������ ���� �����������!!!
                                    //const ��������� ������� �����������, ��� ��� ������� ������� � ������ �������������� ���
    virtual int& at(int i) = 0;
    //���� �� �������� ����������, �� � ������ ��� ����� - ������� ������� � ���� � ������
};


class array_of_ints: public container_of_ints
{
    int data[10] = {};
public:
    int size() const override { return 10; } // � ������� ���� ���������: ��������, ���������, ���� ���������� � �������������. ������������ ��������
    int& at(int i) override { return data[i]; }//� ��������� �� ������. ���� override �� ����� - ��������� ������� ��������, �� ���������� �� �����
                                               //������. ������� override ������� � ���, ��� ������� �������������� � ���� ��� �������� � ������� ������
                                              //�� ���������� ����� ������
};


void double_each_element(array_of_ints &arr)
{
    for(int i = 0; i<arr.size(); i++){ //��� ����������� ���������� �������������� ����������� i, � ��� ��� ���������� ��� �� ����������.
        arr.at(i) += arr.at(i);
    }
}


class list_of_ints: public container_of_ints
{

  struct node
  {
    int data;
    node *next;
  };


  node* head_ = nullptr; //NULL, 0 �� ������������/ ����� nullptr, ������� ���������
  int size_ {0}; //��� 0 ������� ����� � ����
  //int size_ = 0; � ��� ������� � ������� �����������, ���������� �������� �� ����������� ������ ����

public:
  int size() const override {return size_;}
  int& at(int i) override
  {
      if(i > size_) throw std::out_of_range("at");
      node* p = head_;
      for(int j = 0; j < size_; ++j){
          p = p->next;
      }
      return p->data;
  }
  ~list_of_ints()
  {
      for(node* next, *p = head_; p != nullptr; p = next)
      {
            next = p->next;
            delete p;
      }
  }
};

void double_each_element(list_of_ints &con)
{
    for(int i = 0; i<con.size(); i++){ //��� ����������� ���������� �������������� ����������� i, � ��� ��� ���������� ��� �� ����������.
        con.at(i) += con.at(i);
    }
}


template <class ContainerModel> //���� ����٨���� �������
void double_each_element(ContainerModel& con){   //�����������
    for(int i = 0; i < con.size(); ++i){    //����٨���� ������� �� ������� �������� ���(�.�. ���������� �� ����� �� �����, ��� ����� �������������)
        con.at(i) += con.at(i);
    }
}


template <class Container>
int Count(Container& con)
{
    int sum = 0;
    for(auto&& elt: con){ //auto - �������� ������ ���� ����, ��� ��������� ������
        ++sum;  //����� ��� �� ������ & - ������������� � ���������� �������. & - ���������� ���������, && - ��� ������������������ ������,
    } return sum;//��� ������ �� ����������, ��� ����� �������
}





void test1()
{
    array_of_ints1 arr;
    double_each_element(arr);

    array_of_ints arr_i;
    double_each_element(arr_i);

    list_of_ints list_i;
    double_each_element(list_i);

    std::vector<int> vec = {1,2,3};
    double_each_element(vec);

    std::deque<int> deq = {1,2,3};
    double_each_element(deq);
}


template<class Container, class Predicat>
int Count_if(Container& con, Predicat pred){
    int sum = 0;
    for(auto&& elt: con){ //auto - �������� ������ ���� ����, ��� ��������� ������
        if(pred(elt))
            ++sum;  //����� ��� �� ������ & - ������������� � ���������� �������. & - ���������� ���������, && - ��� ������������������ ������,
    } return sum;//��� ������ �� ����������, ��� ����� �������
}


void test2()
{
    std::vector<int> vec = {1,2,3};
    double_each_element(vec);

    std::deque<int> deq = {1,2,3,4,5,42};
    double_each_element(deq);

    assert(Count(deq) == 6); //������ ������, ���� ��������� �������� � ��� ������, ��� ������� ���������

    assert(Count_if(deq,[](int elt){ return elt > 10;}) == 1); //[](){} -������ ������� � �++ ����� ���
}
//����������� ������� - �� ������ ������ �� ������� ����� � �������� � ���������� ������������ �������� ������ ����� ���� ���������!!!


template <typename T> T half(T x){ return x/2; }
template <typename T> T Max(T x, T y){ return (x > y) ? x : y; }


void test3()
{
    int i = half<int>(5);
    assert(i == 2);

    auto j = half(5.f);
    assert(j == 2);

    auto ii = Max(1L, 2); // ��� ���� �� ��������, ���������� � ���� ���� ��������: ��� ��� ����?
    double huy = 2.111111111;
    auto iii = Max(1.f, huy);
}

int main()
{
    test1();
    test2();
    test3();

    return 0;
}
