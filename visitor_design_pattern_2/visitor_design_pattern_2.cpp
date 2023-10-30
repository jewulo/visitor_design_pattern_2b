// visitor_design_pattern_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// https://www.modernescpp.com/index.php/the-visitor-pattern

#include <iostream>
#include <string>
#include <vector>

class CarElementVisitor;

class CarElement {
public:
    virtual void accept(CarElementVisitor& visitor) const = 0;
    virtual ~CarElement() = default;
};

class Body;
class Car;
class Engine;
class Wheel;

class CarElementVisitor {
public:
    virtual void visit(Body body) const = 0;
    virtual void visit(Car car) const = 0;
    virtual void visit(Engine engine) const = 0;
    virtual void visit(Wheel wheel) const = 0;
    virtual ~CarElementVisitor() = default;
};

class Wheel : public CarElement {
public:
    Wheel(const std::string& n)
        : name(n)
    {}

    void accept(CarElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    std::string getName() const
    {
        return name;
    }
private:
    std::string name;
};

class Body : public CarElement {
public:
    void accept(CarElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

class Engine : public CarElement {
public:
    void accept(CarElementVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

class Car : public CarElement {
public:
    Car(std::initializer_list<CarElement*> carElements)
        : elements{carElements}
    {}

    void accept(CarElementVisitor& visitor) const override {
        for (auto elem : elements) {
            elem->accept(visitor);
        }
        visitor.visit(*this);
    }
private:
    std::vector<CarElement*> elements;
};

class CarElementDoVisitor : public CarElementVisitor {
    void visit(Body body) const override {
        std::cout << "Moving my body" << '\n';
    }

    void visit(Car car) const override {
        std::cout << "Starting my car" << '\n';
    }

    void visit(Wheel wheel) const override {
        std::cout << "Kicking my " << wheel.getName() << " wheel" << '\n';
    }

    void visit(Engine engine) const override {
        std::cout << "Starting my engine" << '\n';
    }
};

class CarElementPrintVisitor : public CarElementVisitor {
    void visit(Body body) const override {
        std::cout << "Visiting my body" << '\n';
    }

    void visit(Car car) const override {
        std::cout << "Visiting my car" << '\n';
    }

    void visit(Wheel wheel) const override {
        std::cout << "Visiting my " << wheel.getName() << " wheel" << '\n';
    }

    void visit(Engine engine) const override {
        std::cout << "Visiting my engine" << '\n';
    }
};
int main()
{
    std::cout << '\n';

    Wheel wheelFrontLeft("front left");
    Wheel wheelFrontRight("front right");
    Wheel wheelBackLeft("back left");
    Wheel wheelBackRight("back right");

    Body body;
    Engine engine;

    Car car { &wheelFrontLeft, &wheelFrontRight, &wheelBackLeft, &wheelBackRight, &body, &engine };

    CarElementPrintVisitor carElementPrintVisitor;
    engine.accept(carElementPrintVisitor);
    car.accept(carElementPrintVisitor);

    std::cout << '\n';

    CarElementDoVisitor carElementDoVisitor;
    engine.accept(carElementDoVisitor);
    car.accept(carElementDoVisitor);

    std::cout << '\n';

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
