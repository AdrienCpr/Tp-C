module;
import std;

export module exo8;

export namespace exo8 {

     struct Node {
        int data;
        std::unique_ptr<Node> left{nullptr};
        std::unique_ptr<Node> right{nullptr};
    };

    class BinaryTree {
    public:
        void Insert(const int value) {
            if (root == nullptr) {
                root = std::make_unique<Node>(value);
            }
            else {
                RecursiveInsert(root, value);
            }
        }

        void Traversal(const std::function<void(int)>& lambda) const {
            RecursiveTraversal(root, lambda);
        }

    private:
        std::unique_ptr<Node> root{nullptr};

        void RecursiveInsert(std::unique_ptr<Node>& node, const int value) {
            if (node == nullptr) {
                node = std::make_unique<Node>(value);
            }
            else if (value < node->data) {
                RecursiveInsert(node->left, value);
            }
            else {
                RecursiveInsert(node->right, value);
            }
        }

        void RecursiveTraversal(const std::unique_ptr<Node>& node, const std::function<void(int)>& lambda) const {
            if (node != nullptr) {
                RecursiveTraversal(node->left, lambda);
                lambda(node->data);
                RecursiveTraversal(node->right, lambda);
            }
        }
    };


    class Application {
    public:
        Application() {
            auto tree = BinaryTree{};

            tree.Insert(10);
            tree.Insert(5);
            tree.Insert(15);
            tree.Insert(3);
            tree.Insert(7);

            std::cout << "In order traversal: ";
            tree.Traversal([](int i) {
                std::cout << i << ' ';
            });
            std::cout << "\n";
        }
    };
}