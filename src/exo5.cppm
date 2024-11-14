module;

import std;

export module exo5;

export namespace exo5 {
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

    class Polygon : public Shape {
    public:
        Polygon(const std::initializer_list<double> args) {
            sides = args;
        }

        double Perimeter() const override {
            // Somme des côtés
            return std::accumulate(sides.begin(), sides.end(), 0.0);
        }

        std::string ToString() const override {
            auto message = std::stringstream{};
            message << "Polygon with sides ";
            for(const auto& side: sides) {
                message << side << " ";
            }
            return message.str();
        }
    private:
        std::vector<double> sides;
    };

    class Rectangle : public Polygon {
    public:
        // On utilise la syntaxe d'initialisation {} pour créer l'objet std::initializer_list
        Rectangle(const double side1, const double side2) : Polygon{{side1, side2, side1, side2}} {
        }

        std::string ToString() const override {
            return "Rectangle";
        }
    };

    class Square : public Rectangle {
    public:
        explicit Square(const double side) : Rectangle{side, side} {
        };

        std::string ToString() const override {
            return "Square";
        }
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
            displayPerimeter(Polygon{{1.0, 2.0, 3.0}});
            displayPerimeter(Rectangle{1.0, 2.0});
            displayPerimeter(Square{1.0});
        }
    };
}