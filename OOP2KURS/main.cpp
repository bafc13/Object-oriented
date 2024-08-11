#include <QCoreApplication>
#include <Vector>
#include <cassert>
#include <deque>
#include <iostream>

class array_of_ints1
{
    int data[10] = {};

public:
    int size() const { return 10; } //если функция не меняет состояние объекта - она должна быть константной!!!
                                    //const позволяет увидеть компилятору, что это простая функция и больше оптимизировать код
    int& at(int i) { return data[i]; }
};


void double_each_element(array_of_ints1 &arr)
{
    for(int i = 0; i<arr.size(); i++){ //при постфиксной происходит дополнительное копирование i, а вот при префиксной его не происходит.
        arr.at(i) += arr.at(i);
    }
}


class container_of_ints
{
public:  //virtual - говорит о дальнейшем переопределении этой функции, а то, что метод равен 0 - говорит о том, что это явлвяется чисто виртуальной функцией
    //и класс является чисто виртуальным. создать его экземпляр нельзя, но он становится родителем других
    virtual int size() const = 0; //если функция не меняет состояние объекта - она должна быть константной!!!
                                    //const позволяет увидеть компилятору, что это простая функция и больше оптимизировать код
    virtual int& at(int i) = 0;
    //надо бы написать деструктор, но у класса нет полей - поэтому удалять у него и нечего
};


class array_of_ints: public container_of_ints
{
    int data[10] = {};
public:
    int size() const override { return 10; } // у функции есть сигнатура: название, параметры, типы параметров и константность. возвращаемое значение
    int& at(int i) override { return data[i]; }//в сигнатуру не входят. если override не юзают - сигнатура функции меняется, но компилятор не выдаёт
                                               //ошибку. поэтому override говорит о том, что функция переопределена и если она меняется в базовом классе
                                              //то компилятор выдаёт ошибку
};


void double_each_element(array_of_ints &arr)
{
    for(int i = 0; i<arr.size(); i++){ //при постфиксной происходит дополнительное копирование i, а вот при префиксной его не происходит.
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


  node* head_ = nullptr; //NULL, 0 НЕ ИСПОЛЬЗОВАТЬ/ юзать nullptr, нулевой указатель
  int size_ {0}; //тут 0 задаётся сразу в сайз
  //int size_ = 0; а это задание с помощью копирования, происходит экономия на копировании одного инта

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
    for(int i = 0; i<con.size(); i++){ //при постфиксной происходит дополнительное копирование i, а вот при префиксной его не происходит.
        con.at(i) += con.at(i);
    }
}


template <class ContainerModel> //день ОБОБЩЁННОЙ функции
void double_each_element(ContainerModel& con){   //ОСОБЕННОСТИ
    for(int i = 0; i < con.size(); ++i){    //ОБОБЩЁННАЯ ФУНКЦИЯ НЕ ГЕНЕРИТ МАШИННЫЙ КОД(т.к. компилятор до конца не знает, что будет компилировать)
        con.at(i) += con.at(i);
    }
}


template <class Container>
int Count(Container& con)
{
    int sum = 0;
    for(auto&& elt: con){ //auto - оператор вывода типа того, что находится справа
        ++sum;  //когда нет ни одного & - вытаскивается и копируется элемент. & - копируется указатель, && - это специализированная ссылка,
    } return sum;//так ничего не копируется, это самое быстрое
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
    for(auto&& elt: con){ //auto - оператор вывода типа того, что находится справа
        if(pred(elt))
            ++sum;  //когда нет ни одного & - вытаскивается и копируется элемент. & - копируется указатель, && - это специализированная ссылка,
    } return sum;//так ничего не копируется, это самое быстрое
}


void test2()
{
    std::vector<int> vec = {1,2,3};
    double_each_element(vec);

    std::deque<int> deq = {1,2,3,4,5,42};
    double_each_element(deq);

    assert(Count(deq) == 6); //кидает ошибку, если выражение неверное и даёт строку, где неверно произошло

    assert(Count_if(deq,[](int elt){ return elt > 10;}) == 1); //[](){} -лямбда функция в С++ БЛЯТЬ ЧТО
}
//полиморфная функция - мы создаём ссылку на базовый класс и работает с отдельными наследниками базового класса через этот указатель!!!


template <typename T> T half(T x){ return x/2; }
template <typename T> T Max(T x, T y){ return (x > y) ? x : y; }


void test3()
{
    int i = half<int>(5);
    assert(i == 2);

    auto j = half(5.f);
    assert(j == 2);

    auto ii = Max(1L, 2); // тут авто не работает, компилятор в ахуи кого выводить: инт или лонг?
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
