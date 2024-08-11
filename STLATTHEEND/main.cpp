#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#define FILE1 "input1.txt"
#define FILE2 "input2.txt"

class Car {
private:
    std::string brand;
    std::string model;
    int year;
public:
    Car(const std::string& brand = "unnamed", const std::string& model = "unnamed", int year = 0) : brand(brand), model(model), year(year) {}
    const std::string& getBrand() const {
        return brand;
    }
    const std::string& getModel() const {
        return model;
    }
    int getYear() const {
        return year;
    }
    bool operator<(const Car& other) const {
        return year < other.year;
    }
    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << car.brand << " " << car.model << " (" << car.year << ")";
        return os;
    }
};

void fill_list(int i, std::list<Car>& list){
    std::string file;
    if(i == 0){
        file = FILE1;
    }else {
        file = FILE2;
    }
    std::ifstream stream(file, std::ios_base::in);
    if(stream.is_open()){
        std::vector<std::string> buf;
        std::string strBuf;
        unsigned int pos = 0;
        unsigned int counter = 0;
        while(std::getline(stream, strBuf)){

            while(pos < strBuf.size()){
                if(buf.size() != 2 + counter * 3){
                    pos = strBuf.find(" ");
                    buf.push_back(strBuf.substr(0,pos));
                    strBuf.erase(0,pos+1); // 1 is the length of the delimiter, "%20"
                    pos = 0;
                } else {
                    pos = strBuf.find("\n");
                    buf.push_back(strBuf.substr(0,pos));
                    strBuf.erase(0,pos);
                    pos = 0; strBuf = {};
                    break;
                }
            }
            ++counter;
        }
        if(!buf.empty()){
            for(unsigned int i = 0; i < buf.size(); i += 3){
                list.push_back(std::move(Car(buf.at(i), buf.at(i + 1), std::stoi(buf.at(i + 2)))));
            }
        }
    } else {std::cout << "NOT WORKING UNIT";}
}

void part1() {
    std::vector<int> container = {1, 2, 3, 4, 5};
    std::cout << "First container :";
    for (int num : container) {
        std::cout << "\t" << num << " ";
    }
    std::cout << std::endl;
    container.erase(container.begin() + 2);
    container[1] = 10;
    std::cout << "First container after deleting 3rd elem and changing 2nd elem:";
    for (auto& it:container) {
        std::cout << "\t" << it << " ";
    }
    std::cout << std::endl;
    std::vector<int> container2 = {6, 7, 8, 9, 10};
    int n = 2;
    container.erase(container.begin() + n, container.end());
    container.insert(container.end(), container2.begin(), container2.end());
    std::cout << "First container after deleting 2 last elems and merging :";
    for (auto& num : container) {
        std::cout << "\t" << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Second container :";
    for (auto& num : container2) {
        std::cout << "\t" << num << " ";
    }
    std::cout << std::endl << std::endl;
}

void part2() {
    std::list<Car> carContainer;
    fill_list(0, carContainer);
    std::cout << "First container : " << std::endl;
    for (auto& car : carContainer) {
        std::cout << "\t" << car << std::endl;
    }
    carContainer.erase(++carContainer.begin());
    std::cout << "After removing second car:" << std::endl;
    for (auto& car : carContainer) {
        std::cout << "\t" << car << std::endl;
    }

    auto car = carContainer.begin();
    *car= std::move(Car("Citroen", "C4", 2004));
    std::cout << "After changing first element" << std::endl;
    for (auto& car : carContainer) {
        std::cout << "\t" << car << std::endl;
    }

    std::list<Car> carContainer2;
    fill_list(1, carContainer2);

    auto it = carContainer.begin();
    std::advance(it,2);
    carContainer.erase(it, carContainer.end());
    carContainer.insert(carContainer.end(), carContainer2.begin(), carContainer2.end());

    std::cout << "After merging containers and deleting 2 last elems in 1 cont: \n First container :" << std::endl;
    for (auto& car : carContainer) {
        std::cout << "\t" << car << std::endl;

    } std::cout << "Second container :" << std::endl;
    for (auto& car : carContainer2) {
        std::cout << "\t" << car << std::endl;
    }
}

void part3(){
    std::vector<Car> cars = {
        {"Toyota", "Corolla", 2010},
        {"Honda", "Civic", 2008},
        {"Ford", "Fusion", 2015},
        {"Chevrolet", "Malibu", 2012},
    };
    std::sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
        return a.getYear() > b.getYear();
    });

    std::cout << "First container :" << std::endl;
    for(auto &car : cars){
        std::cout << "\t" << car << std::endl;
    }

    auto it = std::find_if(cars.begin(), cars.end(), [](const Car& car) { //lambda func
        return car.getYear() > 2050;
    });
    if(it != cars.end()){
        std::cout << "Element satisfying the condition year > 10 is: " << *it << std::endl;
    } else { std::cout << "...";}
    std::vector<Car> selectedCars;
    std::copy_if(cars.begin(), cars.end(), std::back_inserter(selectedCars), [](const Car& car) {
        return car.getYear() > 2010;
    });

    std::cout << "Second container with cars, which satisfying the condition year > 10: " << std::endl;
    for(auto& car : selectedCars){
        std::cout << "\t" << car << std::endl;
    }

    std::sort(cars.begin(), cars.end());
    std::cout << "First container after sort by increase :" << std::endl;
    for(auto &car : cars){
        std::cout << "\t" << car << std::endl;
    }
    std::sort(selectedCars.begin(), selectedCars.end());
    std::cout << "Second container after sort by increase: " << std::endl;
    for(auto& car : selectedCars){
        std::cout << "\t" << car << std::endl;
    }

    std::vector<Car> mergedCars;
    std::merge(cars.begin(), cars.end(), selectedCars.begin(), selectedCars.end(), std::back_inserter(mergedCars), [](const Car& a, const Car& b) {
        return a.getYear() < b.getYear();
    });
    std::cout << "Third container which represent the merge of the first two contrainers :" << std::endl;
    for(auto& car : mergedCars){
        std::cout << "\t" << car << std::endl;
    }

    unsigned int count = std::count_if(mergedCars.begin(), mergedCars.end(), [](const Car& car) {
        return car.getYear() > 2010;
    });
    std::cout << "Number of elements satisfying the condition year > 10 in the THIRD container is:" << count << std::endl;

    bool exists = std::any_of(mergedCars.begin(), mergedCars.end(), [](const Car& car) {
        return car.getYear() == 2008;
    });
    if (exists) {
        std::cout << "Third container has car from 2008 " << std::endl;
    } else {
        std::cout << "Third container has no car from 2008 " << std::endl;
    }
}

int main() {
    std::cout << "FIRST PART" << std::endl << std::endl;
    part1();
    std::cout << "SECOND PART" << std::endl << std::endl;
    part2();
    std::cout << "THIRD PART" << std::endl << std::endl;
    part3();
    return 0;
}
