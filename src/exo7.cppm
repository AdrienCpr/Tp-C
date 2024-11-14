module;
import std;

export module exo7;

export namespace exo7 {

    class Resource {
    public:
        Resource() { std::cout << "Resource() constructor called\n"; }
        ~Resource() { std::cout << "~Resource() destructor called\n"; }
        void DoSomething() { std::cout << "Doing something\n"; }
    };

    class Application {
    public:
        void UniquePtr() {
            const auto res = std::make_unique<Resource>();
            res->DoSomething();
        }

        void UseSharedPtr(const std::shared_ptr<Resource> res) {
            std::cout << "resource use count: " << res.use_count() << '\n';
            res->DoSomething();
            if (res.use_count() < 5) UseSharedPtr(res);
        }

        void SharedPtr() {
            const auto res = std::make_shared<Resource>();
            std::cout << "resource use count: " << res.use_count() << '\n';
            UseSharedPtr(res);
            std::cout << "resource use count: " << res.use_count() << '\n';
        }

        Application() {
            UniquePtr();
            SharedPtr();
        }
    };
}