#include <iostream>
#include <utility>

//Ќечеткое число описываетс€ тройкой действительных чисел (X Ц e1_ , X, X + e2), где x Ц среднее
//значение числа, X Ц e1 Ц минимально допустимое значение, X + e2 Ц максимально допустимое
//значение. –еализовать класс дл€ работы с нечеткими числами.

class fuzzy_number
{
private:
    double x_, e1_, e2_;
public:
    fuzzy_number(double e1 = 1.5, double x = 5, double e2 = 2.5):x_(x), e1_(e1), e2_(e2)
    { //default constructor
        std::cout << "Default constructor happend" << std:: endl;
    }
    fuzzy_number(const fuzzy_number& num): x_(num.x_), e1_(num.e1_), e2_(num.e2_)
    { //copy constructor
        std::cout << "Copy constructor happend" << std:: endl;
    }
    fuzzy_number(fuzzy_number &&num): x_(std::exchange(num.x_, 0)), e1_(std::exchange(num.e1_,0)), e2_(std::exchange(num.e2_,0))
    { //move constructor
        std::cout << "Move constructor happend" << std:: endl;
    }
    fuzzy_number& operator =(const fuzzy_number &num)
    { //copy assignment
        x_ = num.x_;
        e1_ = num.e1_;
        e2_ = num.e2_;
        std::cout << "Copy assignment happend with x = " << x_ << std:: endl;
        std::cout << "min value = " << x_ - e1_ << " and max value = " << x_ + e2_ << std::endl;
        return *this;
    }
    fuzzy_number& operator =(fuzzy_number &&num)
    { //move assignment
        x_ = std::exchange(num.x_,0);
        e2_ = std::exchange(num.e2_,0);
        e1_ = std::exchange(num.e1_,0);
        std:: cout << "Move assingment happend with x = " << x_ << std::endl;
        std::cout << "min value = " << x_ - e1_ << " and max value = " << x_ + e2_ << std::endl;
        return *this;
    }
    fuzzy_number const operator +(const fuzzy_number &num)
    { //? сложение: A + B = (A + B Ц a1 Ц b1, A + B, A + B + a2 + b2)
        double e1 = e1_, x = x_, e2 = e2_;
        e1 =  e1 + num.e1_ - num.x_;
        e2 = num.x_ + e2 + num.e2_;
        x += num.x_;
        std:: cout << "\t A+B with x = " << x << std::endl;
        std::cout << "min value = " << x - e1 << " and max value = " << x + e2 << std::endl;
        return { e1, x, e2 };
    }
    fuzzy_number const operator -(const fuzzy_number &num)
    { //? вычитание: A Ц B = (A Ц B Ц a1 Ц b1, A Ц B, A Ц B + a2 + b2)
        double e1 = e1_, x = x_, e2 = e2_;
        e1 = num.x_ + e1 + num.e1_;
        e2 = e2 - num.x_ + num.e2_;
        x -= num.x_;
        std:: cout << "\t A-B with x = " << x << std::endl;
        std::cout << "min value = " << x - e1 << " and max value = " << x + e2 << std::endl;
        return { e1, x, e2 };
    }
    fuzzy_number const operator *(const fuzzy_number &num)
    { //? умножение: A * B = (A*B Ц B*a1 Ц A*b1 + a1*b1, A*B, A*B + B*a1 + A*b1 + a1*b1)
        double e1 = e1_, x = x_, e2 = e2_;
        e1 = x - ((x * num.x_) - (num.x_ * e1) - (x * num.e1_) + (e1 * num.e1_));
        e2 = ((x * num.x_) + (num.x_ * e1) + (x * num.e1_) + (e1 * num.e1_)) - x;
        x *= num.x_;
        std:: cout << "\t A*B with x = " << x << std::endl;
        std::cout << "min value = " << x - e1 << " and max value = " << x + e2 << std::endl;
        return { e1, x, e2 };
    }
    fuzzy_number const operator /(const fuzzy_number &num)
    { //? деление: A / B = ((A Ц a1) /(B + b1), A/B, (A + a1) / (B Ц b1)
        double e1 = e1_, x = x_, e2 = e2_;
        e1 = x - ((x - e1)/(num.x_ + e1));
        e2 = ((x + e1)/(num.x_ - num.e1_)) - x;
        x /= num.x_;
        std:: cout << "\t A/B with x = " << x << std::endl;
        std::cout << "min value = " << x - e1 << " and max value = " << x + e2 << std::endl;
        return {e1,x,e2};
    }
    double get_x() const { return x_; }
    void set_x(const double x) { x_ = x;}
    double get_min_value() const {return x_ - e1_;}
    void set_min_value(const double value){e1_ = x_ - value;}
    double get_max_value() const {return x_ + e2_;}
    void set_max_value(const double value){e2_ = value - x_;}
    void print_number()
    {
        std::cout << "fuzzy number\tmin value\tvalue\tmax value\n\t\t" << x_ - e1_ << "\t\t" << x_ << "\t\t" << x_ + e2_ << std::endl;
    }
};

fuzzy_number const operator /(const int &num,fuzzy_number &fyz)
{ //? обратное число: 1 / B = (1 /(B + b1), 1/B, 1 / (B Ц b1)
    double x = fyz.get_x();
    double max_val = fyz.get_max_value();
    double min_val = fyz.get_min_value();
    min_val = num / (x + (x-min_val));
    max_val = num / (x - (x-min_val));
    x = num / x;
    std::cout << "\t 1/A with x = " << x << std::endl;
    std::cout << "min value = " << min_val << " and max value = " << max_val << std::endl;
    return { x - min_val, x, x + max_val };
}

int main()
{
    //Math operations test
    std::cout << "Math operations test" << std::endl;
    fuzzy_number A(3,5,7), B(5,7,9);
    A+B;
    A-B;
    A*B;
    A/B;
    1/A;
    //Constructors test
    std::cout << "\nConstructors test" << std::endl;
    fuzzy_number C1;
    fuzzy_number A1(1,2,3);
    fuzzy_number B1 = A1;
    fuzzy_number m1(2,3,4);
    fuzzy_number m =std::move(m1);
    C1.print_number();
    A1.print_number();
    B1.print_number();
    m.print_number();
    //Assignments test
    std::cout << "\nAssignments test" << std::endl;
    fuzzy_number A2,B2(2,4,99);
    A2 = B2;
    fuzzy_number C2;
    A2 = std::move(C2);
}


