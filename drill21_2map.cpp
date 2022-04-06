#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <numeric>

void f(std::map<std::string, int>& m)
{
    std::string s;
    int i = 0;

    while (m.size() < 10) {
        std::cin >> s >> i;
        m.insert(std::make_pair(s, i));
    }
}

template<typename T, typename U>
void print(const std::map<T,U>& m)
{
    std::cout << "MAP CONTENTS:" << '\n'
              << "=============" << '\n';

    for (const auto& a : m)
        std::cout << a.first << '\t' << a.second << '\n';

    std::cout << "END" << "\n\n";
}

int main()
try {
    std::map<std::string, int> msi;

    msi["Robert"] = 4;
    msi["Margret"] = 34;
    msi["Irene"] = 6;
    msi["Gregory"] = 38;
    msi["Lyle"] = 64;
    msi["Anne"] = 62;
    msi["Barbara"] = 33;
    msi["Young"] = 24;
    msi["Turk"] = 13;
    msi["Chloe"] = 9;

    print(msi);

    msi.erase(msi.begin(), msi.end());

    print(msi);

    f(msi);

    print(msi);
    int total = std::accumulate(msi.begin(), msi.end(), 0,
            [](int sum, const std::pair<std::string,int>& p)
            { return sum += p.second; });

    std::cout << "Total of integers: " << total << '\n';

    std::map<int, std::string> mis;

    for (const auto& a : msi)
        mis[a.second] = a.first;

    print(mis);
}
catch(std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    std::cerr << "Unknown exception\n";
    return 2;
}
