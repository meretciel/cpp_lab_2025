#include <cctype>
#include <concepts>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

/**
   Define a concept. The static method is for demo purpose. It will be removed
   in the interface defined later because we cannot have virtual static method.

   The concept is for generic programming.
 */
template <typename T>
concept Demo = requires(T self) {
    // This is similar to the associated type in Rust.
    typename T::InputType;
    typename T::OutputType;

    // The first time we specify the member function.
    { self.member_function(std::declval<int>()) } -> std::same_as<int>;

    // We can also specify static method in a concept.
    { T::static_function(std::declval<std::vector<double>>()) } -> std::same_as<double>;
};


/**
   This interface is used to replciate the dyn Trait feature.
*/
class DemoInterface {
public:
    // The second time we specify the member function.
    virtual int member_function(int) = 0;
    virtual ~DemoInterface() = default;
};


template <Demo T> class DemoWrapper : public DemoInterface {  
private:
    std::unique_ptr<T> _inner;

public:
    DemoWrapper(std::unique_ptr<T>&& demo_instance)
        : _inner(std::move(demo_instance)) {}

    // The third time we write something about the member function.
    int member_function(int x) override { return _inner->member_function(x); }
};


class ConceptIsNotTrait {
public:
    using InputType = double;
    using OutputType = std::string_view;

    static double static_function(std::vector<double> values) {
        std::cout << "ConceptIsNotTrait: static_function is executed with values: ";
        std::copy(values.begin(), values.end(),
                  std::ostream_iterator<double>(std::cout, ","));
        std::cout << "\n";
        return 3.14;
    }

    int member_function(int value) {
        std::cout << "ConceptIsNotTrait.member_function is called with value: " << value << "\n";
        return value;
    }
};

class CppDoesNotLikeInterface {
public:
    using InputType = std::string;
    using OutputType = std::string;

    static double static_function(std::vector<double> values) {
                std::cout << "CppDoesNotLikeInterface: static_function is executed with values: ";
        std::copy(values.begin(), values.end(),
                  std::ostream_iterator<double>(std::cout, ","));
        std::cout << "\n";
        return 0.0;
    }     

    int member_function(int value) {
        std::cout << "CppDoesNotLikeInterface.member_function is called with value: " << value
                  << "\n";
        return 73;
    }
};

template <Demo T> void run_demo(T& instance) {
    
    if constexpr (std::is_same_v<decltype(instance), ConceptIsNotTrait&>) {
        std::cout << "run_demo is called with ConceptIsNotTrait.\n";
        ConceptIsNotTrait::static_function(std::vector<double>{1, 2, 3, 4, 5});
    } else if constexpr (std::is_same_v<decltype(instance), CppDoesNotLikeInterface&>) {
        std::cout << "run_demo is called with CppDoesNotLikeInterface.\n";
        CppDoesNotLikeInterface::static_function(std::vector<double>{-1, -2, -3});
    }
    instance.member_function(10);    
}

int main(int argc, char *argv[]) {

    std::cout << "---------- Generic Programming ----------\n";

    ConceptIsNotTrait instance_ma{};
    CppDoesNotLikeInterface instance_ca{};

    run_demo<>(instance_ma);
    run_demo<>(instance_ca);

    std::cout << "---------- Polymorphism ----------\n";

    std::vector<std::unique_ptr<DemoInterface>> vec_of_demo{};

    std::unique_ptr<DemoInterface> a = std::make_unique<DemoWrapper<ConceptIsNotTrait>>(std::make_unique<ConceptIsNotTrait>());
    std::unique_ptr<DemoInterface> b = std::make_unique<DemoWrapper<CppDoesNotLikeInterface>>(std::make_unique<CppDoesNotLikeInterface>());

    vec_of_demo.push_back(std::move(a));
    vec_of_demo.push_back(std::move(b));

    for (auto &item : vec_of_demo) {
        item->member_function(73);
    }

    return 0;
}
