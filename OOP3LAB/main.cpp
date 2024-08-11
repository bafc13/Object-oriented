#include <iostream>
#include <array>
#include <deque>
#include <forward_list>
#include <map>
#include <set>

int main(){
    std::deque<int> deq;
    deq.push_back(1);
    std::forward_list <int> lis;
    lis.push_front(11);
    lis.push_front(1222);
    std::map<std::string,int> ma = {{"huy",1},{"cclen", 2}};
    std::cout  << "map" << sizeof(ma);

    std::set<int> se = {1,2,5};
    std::cout  << "set" << sizeof(se) /*<< std::endl << /*sizeof(se.begin()) <<*//* std::endl*/;
}











//#include <iostream>
//#include <stdexcept>

////Во всех вариантах требуется создать целевой шаблонный класс А с
////помощью серверного класса В. Это означает, что объект класса А содержит объект класса В. Не
////использовать классы стандартной библиотеки (ВАЖНО).
////Вызывающая программа (main) должна продемонстрировать использование класса. Показать
////инстанцирование шаблона для типов int, double и std::string. Если на лекциях проходили
////обработку исключений, то её также можно включить и продемонстрировать.


//// Queue /*List*/
//template <typename T>
//class List {
//private:
//    struct Node{
//        T data;
//        Node* prev;
//        Node* next;
//        Node(const T& item, Node* p = nullptr, Node* n = nullptr) : data(item), prev(p), next(n) {}
//    };
//    Node* head = nullptr;
//    Node* tail = nullptr;
//    int size = 0;
//public:
//    List() = default;
//    List(T item) {
//        push_back(item);
//    }
//    List(T* items, int size) {
//        for (unsigned int i = 0; i < size; i++) {
//            push_back(items[i]);
//        }
//    }
//    ~List() {
//        clear();
//    }
//    void clear(){
//        while (head != nullptr) {
//            if (head->next) {
//                head = head->next;
//                delete head->prev;
//            }
//            else {
//                delete head;
//                head = nullptr;
//            }
//        }
//        tail = nullptr;
//    }
//    class iterator {
//           Node* current;
//       public:
//           iterator(Node* node) : current(node) {}
//           T operator*() { return current->data; }
//           void operator++() { current = current->next; }
//           void operator--() { current = current->prev; }
//           bool operator!=(const iterator& other) { return current != other.current; }
//           Node* get_iterator() { return current; }
//           bool operator ==(const iterator& other) { return current == other.current; }
//    };
//    iterator begin() { return iterator(head); }
//    iterator end() { return iterator(tail->next); }
//    void push_back(const T& item) {
//        Node* newNode = new Node(item, tail, nullptr);
//        if (tail) {
//            tail->next = newNode;
//        }
//        else {
//            head = newNode;
//        }
//        tail = newNode;
//        size++;
//    }
//    void push_front(const T& item) {
//        Node* newNode = new Node(item, nullptr, head);
//        if (head) {
//            head->prev = newNode;
//        }
//        else {
//            tail = newNode;
//        }
//        head = newNode;
//        size++;
//    }
//    void insert(int pos, const T& item) {
//        if (pos < 0 || pos > size)
//            throw std::out_of_range("Index out of bounds");

//        if (pos == 0) {
//            push_front(item);
//            return;
//        }
//        else if (pos == size) {
//            push_back(item);
//            return;
//        }
//        Node* current = head;
//        for(int i = 0; i < pos - 1; i++) {
//            current = current->next;
//        }
//        Node* newNode = new Node(item, current, current->next);
//        current->next->prev = newNode;
//        current->next = newNode;
//        size++;
//    }
//    void display() {
//        Node* current = head;
//        while (current) {
//            std::cout << current->data << " ";
//            current = current->next;
//        }
//        std::cout << std::endl;
//    }
//    unsigned int getSize() {
//        return size;
//    }
//    void pop_front() {
//        if (head) {
//            Node* toDelete = head;
//            head = head->next;
//            if (head) {
//                head->prev = nullptr;
//            } else {
//                tail = nullptr;
//            }
//            delete toDelete;
//            size--;
//        }
//    }
//    void pop_back() {
//        if (tail) {
//            Node* toDelete = tail;
//            tail = tail->prev;
//            if (tail) {
//                tail->next = nullptr;
//            } else {
//                head = nullptr;
//            }
//            delete toDelete;
//            size--;
//        }
//    }
//    void erase(iterator pos) {
//        Node* toDelete = pos.get_iterator();

//        if (toDelete == nullptr) {
//            throw std::out_of_range("Invalid iterator");
//        }

//        if (toDelete->prev != nullptr) {
//            toDelete->prev->next = toDelete->next;
//        } else {
//            head = toDelete->next;
//        }

//        if (toDelete->next != nullptr) {
//            toDelete->next->prev = toDelete->prev;
//        } else {
//            tail = toDelete->prev;
//        }

//        delete toDelete;
//        size--;
//    }
//    Node* getTail(){
//        return tail;
//    }
//    bool isEmpty(){
//        if(head == nullptr){
//            return 1;
//        } else {
//            return 0;
//        }
//    }
//};

//template <typename T>
//class Queue {
//private:
//    List<T> list;
//public:
//    void enqueue(const T& item) {
//        list.push_back(item);
//    }
//    void dequeue() {
//        if (list.begin() != list.end()) {
//            list.erase(list.begin());
//        }
//    }
//    const T front() {
//        if (list.begin() != list.end()) {
//            return *list.begin();
//        }
//        throw std::out_of_range("Queue is empty");
//    }
//    const T back() {
//        if (list.begin() != list.end()) {
//            return list.getTail()->data;
//        }
//        throw std::out_of_range("Queue is empty");
//    }
//    bool empty() {
//         return list.isEmpty();
//    }
//    unsigned int getSize() {
//        return list.getSize();
//    }
//    void clear(){
//        list.clear();
//    }
//};


//int main()
//{
//    int size = 4;
//    int mas[size] = {1,2,3,4};
//    List <int> list(mas,size);
//    list.display();
//    std::cout << "\n\n";

//    Queue<int> queue;
//    queue.enqueue(100);
//    queue.enqueue(1);
//    queue.enqueue(2);
//    while(!queue.empty()){
//        std::cout << "Front: " << queue.front() << std::endl;
//        std::cout << "Queue size: " << queue.getSize() << std::endl;
//        queue.dequeue();
//    }
//    std::cout << "Queue is empty? " << queue.empty() << "\n\n\n";

//    Queue <double> q;
//    q.enqueue(2.333);
//    q.enqueue(1.22222);
//    q.enqueue(100.22222);
//    while(!q.empty()){
//        std::cout << "Front: " << q.front() << std::endl;
//        std::cout << "Queue size: " << q.getSize() << std::endl;
//        q.dequeue();
//    }
//    std::cout << "Queue is empty? " << q.empty() << "\n\n\n";

//    Queue <std::string> qu;
//    qu.enqueue("aa11");
//    qu.enqueue("vbbb11");
//    qu.enqueue("21231bbb");
//    while(!qu.empty()){
//        std::cout << "Front: " << qu.front() << std::endl; //
//        std::cout << "Queue size: " << qu.getSize() << std::endl;
//        qu.dequeue();
//    }
//    std::cout << "Queue is empty? " << qu.empty() << "\n\n\n";

//    std::string str1 = "aaa111";
//    std::cout<< sizeof(str1) << std::endl;
//    std::cout << str1.size() << std::endl;
//    std::cout << str1.capacity() << std::endl;


//    return 0;
//}
