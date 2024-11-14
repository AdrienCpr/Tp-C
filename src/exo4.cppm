module;

import std;

export module exo4;

export namespace exo4 {
    class Shape {
    public:
        virtual double Perimeter() const = 0;

        virtual std::string ToString() const = 0;

        // Ajouté en cas d'override de destructeurs dans les classes enfants
        virtual ~Shape() = default;
    };

    class Circle : public Shape {
    public:
        explicit Circle(const double radius): radius{radius} {
        }

        double Perimeter() const override {
            return 2.0 * std::numbers::pi * radius;
        }

        std::string ToString() const override {
            return std::format("Circle({0:.2f})", radius);
        }

    private:
        double radius;
    };

    class Application {
    public:
        void displayPerimeter(const Shape& shape) const {
            std::cout
                << "Perimeter of " << shape.ToString()
                << std::format(" is {0:.2f}", shape.Perimeter())
                << std::endl;
        }

        Application() {
            displayPerimeter(Circle{1.2});
        }
    };
}