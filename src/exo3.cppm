module;

import std;

export module exo3;

export namespace exo3 {
    struct Vector {
            double x;
            double y;
            double z;

        std::string ToString() const {
            return std::format("({0:.2f},{1:.2f},{2:.2f})", x, y, z);
        }

        Vector operator +(const Vector& vector) const {
            return Vector{x + vector.x, y + vector.y, z + vector.z};
        }

        Vector operator *(const double value) const {
            return Vector{x * value, y * value, z * value};
        }

        friend bool operator ==(const Vector& vector1, const Vector& vector2) {
            return vector1.x == vector2.x && vector1.y == vector2.y && vector1.z == vector2.z;
        }
    };
    class Application {
    public:
        Application() {
            constexpr auto v1 = Vector{12.34, 56.78, 90.12};
            std::cout << v1.ToString() << std::endl;
            std::cout << (v1 * 2.0).ToString() << std::endl;
            std::cout << (v1 + Vector{1.1, 2.2, 3.3}).ToString() << std::endl;
            const auto v2 = v1 + Vector{34.12, 78.56, 12.90};
            if (v1 == v2) {
                std::printf("Equals\n");
            }
            else {
                std::printf("Different\n");
            }
        }
    };
}