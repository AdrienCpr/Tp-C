#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
import exo9;
using namespace exo9;

TEST_CASE("BinaryTree - Basic Operations", "[BinaryTree]") {
    BinaryTree<std::string> tree;

    SECTION("Initial state") {
        CHECK(tree.GetSize() == 0);
        CHECK_FALSE(tree.Contains("anything"));
    }

    SECTION("Single insertion") {
        tree.Insert("test");
        CHECK(tree.GetSize() == 1);
        CHECK(tree.Contains("test"));
    }

    SECTION("Multiple insertions") {
        tree.Insert("C++");
        tree.Insert("ASM");
        tree.Insert("GO");

        CHECK(tree.GetSize() == 3);
        CHECK(tree.Contains("C++"));
        CHECK(tree.Contains("ASM"));
        CHECK(tree.Contains("GO"));
        CHECK_FALSE(tree.Contains("Rust"));
    }

    SECTION("Clear operation") {
        tree.Insert("C++");
        tree.Insert("ASM");
        CHECK(tree.GetSize() == 2);

        tree.Clear();
        CHECK(tree.GetSize() == 0);
        CHECK_FALSE(tree.Contains("C++"));
        CHECK_FALSE(tree.Contains("ASM"));
    }

    SECTION("Traversal order") {
        tree.Insert("C++");
        tree.Insert("ASM");
        tree.Insert("GO");

        std::vector<std::string> result;
        tree.Traversal([&result](std::string& value) {
            result.push_back(value);
            return false;
        });

        REQUIRE(result.size() == 3);
        CHECK(result[0] == "ASM");
        CHECK(result[1] == "C++");
        CHECK(result[2] == "GO");
    }

    SECTION("Early traversal termination") {
        tree.Insert("C++");
        tree.Insert("ASM");
        tree.Insert("GO");

        std::vector<std::string> result;
        tree.Traversal([&result](std::string& value) {
            result.push_back(value);
            return value == "C++";
        });

        REQUIRE(result.size() == 2);
        CHECK(result[0] == "ASM");
        CHECK(result[1] == "C++");
    }
}

TEST_CASE("Map - Basic Operations", "[Map]") {
    Map<std::string, int> map;

    SECTION("Initial state") {
        CHECK(map.GetSize() == 0);
        CHECK_FALSE(map.Contains("anything"));
    }

    SECTION("Single put and get") {
        map.Put("test", 42);
        CHECK(map.GetSize() == 1);
        CHECK(map.Contains("test"));
        CHECK(map.Get("test") == 42);
    }

    SECTION("Update existing key") {
        map.Put("test", 42);
        CHECK(map.Get("test") == 42);

        map.Put("test", 24);
        CHECK(map.Get("test") == 24);
        CHECK(map.GetSize() == 1);
    }

    SECTION("Multiple entries") {
        map.Put("one", 1);
        map.Put("two", 2);
        map.Put("three", 3);

        CHECK(map.GetSize() == 3);
        CHECK(map.Get("one") == 1);
        CHECK(map.Get("two") == 2);
        CHECK(map.Get("three") == 3);
    }

    SECTION("Clear operation") {
        map.Put("one", 1);
        map.Put("two", 2);
        CHECK(map.GetSize() == 2);

        map.Clear();
        CHECK(map.GetSize() == 0);
        CHECK_FALSE(map.Contains("one"));
        CHECK_FALSE(map.Contains("two"));
    }

    SECTION("Get non-existent key") {
        CHECK_THROWS_AS(map.Get("nonexistent"), std::out_of_range);
    }
}

TEST_CASE("Map - Complex Value Types", "[Map]") {
    Map<std::string, std::vector<int>> map;

    SECTION("Store and retrieve vectors") {
        std::vector<int> v1 = {1, 2, 3};
        std::vector<int> v2 = {4, 5, 6};

        map.Put("first", v1);
        map.Put("second", v2);

        auto& retrieved1 = map.Get("first");
        auto& retrieved2 = map.Get("second");

        CHECK(retrieved1 == v1);
        CHECK(retrieved2 == v2);
    }
}

TEST_CASE("BinaryTree - Edge Cases", "[BinaryTree]") {
    BinaryTree<int> tree;

    SECTION("Duplicate values") {
        tree.Insert(5);
        tree.Insert(5);  // Duplicate
        CHECK(tree.GetSize() == 2);
        CHECK(tree.Contains(5));
    }

    SECTION("Large number of insertions") {
        const int N = 1000;
        for(int i = 0; i < N; i++) {
            tree.Insert(i);
        }
        CHECK(tree.GetSize() == N);

        CHECK(tree.Contains(0));
        CHECK(tree.Contains(N/2));
        CHECK(tree.Contains(N-1));
    }
}