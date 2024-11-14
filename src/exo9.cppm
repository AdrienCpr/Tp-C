module;
import std;

export module exo9;

export namespace exo9 {

    template<typename T>
    struct Node {
        T data;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    template<typename T>
    class BinaryTree {
    public:
        void Insert(const T value) {
            if (root == nullptr) {
                root = std::make_unique<Node<T>>(value);
            } else {
                RecursiveInsert(root, value);
            }
            size += 1;
        }

        bool Traversal(const std::function< bool(T&) >& lambda) const {
            return RecursiveTraversal(root, lambda);
        }

        void Clear() {
            root = nullptr;
            size = 0;
        }

        bool Contains(const T value) const {
            bool found{false};
            Traversal([&](T& v) {
                if (value == v) {
                    found = true;
                    return true;
                }
                return false;
            });
            return found;
        }

        std::uint64_t GetSize() const { return size; }

    private:
        std::unique_ptr<Node<T>> root{nullptr};
        std::uint64_t size{0};

        void RecursiveInsert(std::unique_ptr<Node<T>>& node, T value) {
            if (node == nullptr) {
                node = std::make_unique<Node<T>>(value);
            } else if (value < node->data) {
                RecursiveInsert(node->left, value);
            } else {
                RecursiveInsert(node->right, value);
            }
        }

        bool RecursiveTraversal(const std::unique_ptr<Node<T>>& node, const std::function< bool(T&) >& lambda) const {
            if (node != nullptr) {
                if (RecursiveTraversal(node->left, lambda)) return true;
                if (lambda(node->data)) return true;
                if (RecursiveTraversal(node->right, lambda)) return true;
            }
            return false;
        }
    };

    template<typename K, typename V>
    struct MapEntry {
        K key;
        V value;

        friend bool operator<(const MapEntry& lhs, const MapEntry& rhs) {
            return lhs.key < rhs.key;
        }

        friend bool operator<=(const MapEntry& lhs, const MapEntry& rhs) {
            return !(rhs < lhs);
        }

        friend bool operator>(const MapEntry& lhs, const MapEntry& rhs) {
            return rhs < lhs;
        }

        friend bool operator>=(const MapEntry& lhs, const MapEntry& rhs) {
            return !(lhs < rhs);
        }

        friend bool operator==(const MapEntry& lhs, const MapEntry& rhs) {
            return lhs.key == rhs.key;
        }

        friend bool operator!=(const MapEntry& lhs, const MapEntry& rhs) {
            return !(lhs == rhs);
        }
    };

    template<typename K, typename V>
    class Map {
    public:
        void Clear() { tree.Clear(); }

        std::uint64_t GetSize() const { return tree.GetSize(); }

        bool Contains(const K& key) const {
            return tree.Contains({key});
        }

        V& Get(const K& key) {
            if (!tree.Contains({key})) {
                throw std::out_of_range("Key not found");
            }
            MapEntry<K, V> *result;
            tree.Traversal([&](MapEntry<K, V>& entry) {
                if (entry.key == key) {
                    result = &entry;
                    return true;
                }
                return false;
            });
            return result->value;
        }

        void Put(const K& key, const V& value) {
            if (!tree.Contains({key})) {
                tree.Insert({key, value});
                return;
            }
            auto f = [&](MapEntry<K, V>& entry) {
                if (entry.key == key) {
                    entry.value = value;
                    return true;
                }
                return false;
            };
            tree.Traversal(f);
        }
    private:
        BinaryTree<MapEntry<K, V>> tree;
    };


    class Application {
        public:
            Application() {
                BinaryTree<std::string> tree;

                tree.Insert("C++");
                tree.Insert("ASM");
                tree.Insert("GO");
                tree.Insert("Rust");
                tree.Insert("JavaScript");

                std::cout << "In order traversal: ";
                tree.Traversal([](const std::string& i) {
                    std::cout << i << ' ';
                    return false;
                });
                std::cout << "\n";

                std::cout << "Tree Size : " << tree.GetSize() << "\n";
                std::cout << "Tree Contains(\"Rust\") : " << tree.Contains("Rust") << "\n";
                std::cout << "Tree Contains(\"C#\") : " << tree.Contains("C#") << "\n";

                Map<std::string, std::int64_t> map;
                map.Put("Jean", 18);
                map.Put("Georges", 20);
                std::cout << "Map Size : " << map.GetSize() << "\n";
                std::cout << "Map Contains(\"Jean\") : " << map.Contains("Jean") << "\n";
                std::cout << "Map Contains(\"Jeanne\") : " << map.Contains("Jean") << "\n";
                std::cout << "Jean : " << map.Get("Jean") << "\n";
                map.Put("Jean", 8);
                std::cout << "Jean : " << map.Get("Jean") << "\n";
            }
    };

}