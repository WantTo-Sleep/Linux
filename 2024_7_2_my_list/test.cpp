#include <iostream>
#include <vector>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <string>
#include "my_list.h"

template<typename T>
std::ostream& operator<<(std::ostream& s, const sjx::list<T>& v)
{
    s.put('{');
    char comma[]{ '\0', ' ', '\0' };
    for (const auto& e : v)
        s << comma << e, comma[0] = ',';
    return s << "}\n";
}

void print_info(std::string rem, const sjx::list<int>& v)
{
    std::cout << rem << "{ ";
    for (const auto& value : v)
        std::cout << value << ' ';
    std::cout << "}\n";
    std::cout << "Size=" << v.size() << '\n';
}

void print(int id, const sjx::list<int>& container)
{
    std::cout << id << ". ";
    for (const int x : container)
        std::cout << x << ' ';
    std::cout << '\n';
}

void print_container(const sjx::list<int>& c)
{
    for (int i : c)
        std::cout << i << ' ';
    std::cout << '\n';
}

template<typename T>
void print(T const& xs)
{
    std::cout << "[ ";
    for (auto const& x : xs)
        std::cout << x << ' ';
    std::cout << "]\n";
}

class Solustion
{
public:
    void test1()
    {
        // C++11 initializer list syntax:
        sjx::list<std::string> words1;
        words1.push_back("the");
        words1.push_back("frogurt");
        words1.push_back("is");
        words1.push_back("also");
        words1.push_back("cursed");
        std::cout << "1: " << words1;

        // words2 == words1
        sjx::list<std::string> words2(words1.begin(), words1.end());
        std::cout << "2: " << words2;

        // words3 == words1
        sjx::list<std::string> words3(words1);
        std::cout << "3: " << words3;

        sjx::list<std::string> words4;
        words4.push_back("I");
        words4.push_back("Love");
        words4.push_back("Linux");
        std::cout << "4: " << words4;

        words4 = words3;
        std::cout << "4: " << words4;

    }
    void test2()
    {
        sjx::list<char> letters;
        letters.push_back('a');
        letters.push_back('b');
        letters.push_back('c');
        letters.push_back('d');
        letters.push_back('e');
        letters.push_back('f');

        if (!letters.empty())
            std::cout << "The last character is '" << letters.front() << "'.\n";
    }
    void test3()
    {
        sjx::list<int> nums;
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(4);
        nums.push_back(8);
        nums.push_back(16);

        sjx::list<std::string> fruits;
        fruits.push_back("orange");
        fruits.push_back("apple");
        fruits.push_back("raspberry");

        sjx::list<char> empty;

        // Print list.
        std::for_each(nums.begin(), nums.end(), [](const int n) { std::cout << n << ' '; });
        std::cout << '\n';

        // Sums all integers in the list nums (if any), printing only the result.
        std::cout << "Sum of nums: " << std::accumulate(nums.begin(), nums.end(), 0) << '\n';

        // Prints the first fruit in the list fruits, checking if there is any.
        if (!fruits.empty())std::cout << "First fruit: " << *fruits.begin() << '\n';

        if (empty.begin() == empty.end())std::cout << "list 'empty' is indeed empty.\n";
    }
    void test4()
    {
        sjx::list<int> numbers;
        std::cout << std::boolalpha;
        std::cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';

        numbers.push_back(42);
        numbers.push_back(13317);
        std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';

        sjx::list<int> nums;
        nums.push_back(1);
        nums.push_back(3);
        nums.push_back(5);
        nums.push_back(7);

        std::cout << "nums contains " << nums.size() << " elements.\n";

        sjx::list<int> container;
        container.push_back(1);
        container.push_back(2);
        container.push_back(3);

        print_info("Before clear: ", container);
        container.clear();
        print_info("After clear: ", container);
    }
    void test5()
    {
        sjx::list<int> c1;
        c1.push_back(100);
        c1.push_back(100);
        c1.push_back(100);
        print(1, c1);

        auto it = c1.begin();
        it = c1.insert(it, 200);
        print(2, c1);

        it = c1.insert(it, (size_t)2, 300);
        print(3, c1);
        
        // reset `it` to the begin:
        it = c1.begin();
        ++it;
        sjx::list<int> c2;
        c2.push_back(400);
        c2.push_back(400);
        c1.insert(++it, c2.begin(), c2.end());
        print(4, c1);

        int arr[] = { 501, 502, 503 };
        c1.insert(c1.end(), arr, arr + std::size(arr));
        print(5, c1);
    }
    void test6()
    {
        std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        sjx::list<int> c(v.begin(),v.end());
        print_container(c);

        c.erase(c.begin());
        print_container(c);

        sjx::list<int>::iterator range_begin = c.begin();
        sjx::list<int>::iterator range_end = c.begin();
        ++range_begin;
        ++range_begin;
        ++range_end;
        ++range_end;
        ++range_end;
        ++range_end;
        ++range_end;

        c.erase(range_begin, range_end);
        print_container(c);

        // Erase all even numbers
        for (sjx::list<int>::iterator it = c.begin(); it != c.end();)
        {
            if (*it % 2 == 0)
                it = c.erase(it);
            else
                ++it;
        }
        print_container(c);
        c.erase(c.begin());
        print_container(c);
        c.erase(c.begin());
        print_container(c);
        c.erase(c.begin());
        print_container(c);
        c.erase(c.begin());
        print_container(c);
    }
    void test7()
    {
        sjx::list<std::string> letters;

        letters.push_back("abc");
        std::string s{ "def" };
        letters.push_back(std::move(s));

        std::cout << "std::list letters holds: ";
        for (auto&& e : letters)
            std::cout << std::quoted(e) << ' ';

        std::cout << "\nMoved-from string s holds: " << std::quoted(s) << '\n';
    }
    void test8()
    {
        sjx::list<int> numbers;

        print(numbers);

        numbers.push_back(5);
        numbers.push_back(3);
        numbers.push_back(4);

        print(numbers);

        numbers.pop_back();

        print(numbers);

        sjx::list<std::string> letters;

        letters.push_front("abc");
        std::string s{ "def" };
        letters.push_front(std::move(s));

        std::cout << "std::list letters holds: ";
        for (auto&& e : letters)
            std::cout << std::quoted(e) << ' ';

        std::cout << "\nMoved-from string s holds: " << std::quoted(s) << '\n';

        std::vector<char> v1{ 'A', 'B', 'C', 'D' };
        sjx::list<char> chars(v1.begin(), v1.end());

        for (; !chars.empty(); chars.pop_front())
            std::cout << "chars.front(): '" << chars.front() << "'\n";
    }
};


int main()
{
    Solustion().test8();
    return 0;
}