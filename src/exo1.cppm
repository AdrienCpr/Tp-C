module;

import std;

export module exo1;

export namespace exo1 {
    class Vector {
    public:
        Vector(const double x, const double Y, const double Z) : x{x}, y{Y}, z{Z} {}

            double GetX() const { return x; }
            double GetY() const { return y; }
            double GetZ() const { return z; }

            void SetX(const double x) { this->x = x; }
            void SetY(const double y) { this->y = y; }
            void SetZ(const double z) { this->z = z; }

            void Homothety(const double value) {
                    x *= value;
                    y *= value;
                    z *= value;
                }

            void Sum(const Vector vector) {
                    x += vector.x;
                    y += vector.y;
                    z += vector.z;
                }

            std::string ToString() const {
                    // Afficher avec deux chiffres après la virgule
                    return std::format("({0:.2f},{1:.2f},{2:.2f})", x, y, z);
            }
       private:
            double x;
            double y;
            double z;
       };
    // Exemple de classe utilisée dans la fonction main()
    class Application {
    public:
        Application() {
            auto v1 = Vector{12.34, 56.78, 90.12};
            std::cout << v1.ToString() << std::endl;
            v1.Homothety(2);
            std::cout << v1.ToString() << std::endl;
            v1.Sum(Vector{1.1, 2.2, 3.3});
            std::cout << v1.ToString() << std::endl;
        }
    };

}