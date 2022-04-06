#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <list>

struct Item {
    std::string name;
    int iid;
    double value;
};

std::ostream& operator<<(std::ostream& os, const Item& it)
{
    return os << it.name << '\t'
              << it.iid << '\t'
              << it.value;
}

std::istream& operator>>(std::istream& is, Item& it)
{
    std::string ss;
    int ii;
    double dd;
    is >> ss >> ii >> dd;
    Item itt {ss, ii, dd};
    it = itt;
    return is;
}

struct Cmp_by_dec_val {
    bool operator()(const Item& a, const Item& b)
    {
        return a.value > b.value;
    }
};

class Smaller_than {
    double val;
public:
    Smaller_than(double vv) : val{vv} { }
    bool operator()(const Item& x) const { return x.value < val; }
};

class Cmp_by_name {
    std::string name;
public:
    Cmp_by_name(const std::string& nn) : name{nn} { }
    bool operator()(const Item& x) const { return x.name == name; }
};

class Cmp_by_iid {
    int iid;
public:
    Cmp_by_iid(int id) : iid{id} { }
    bool operator()(const Item& x) const { return x.iid == iid; }
};
template<typename C>
void print(const C& c, char sep = ' ')
{
    for (const auto& a : c)
        std::cout << a << sep;
    std::cout << '\n';
}

int main()
try {
    const std::string iname {"input_items.txt"};

    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Could not read from file: " + iname);

    std::vector<Item> vi;
    for (Item ii; ifs >> ii; )
        vi.push_back(ii);

    std::list<Item> li (vi.size());
    std::copy(vi.begin(), vi.end(), li.begin());

    std::sort(vi.begin(), vi.end(),
            [](const Item& a, const Item& b) { return a.name < b.name; });

    std::sort(vi.begin(), vi.end(),
            [](const Item& a, const Item& b) { return a.iid < b.iid; });

    std::sort(vi.begin(), vi.end(), Cmp_by_dec_val());

    Item tmp {"horse shoe", 99, 1.34}; 
    vi.insert(
            std::find_if(vi.begin(), vi.end(), Smaller_than(tmp.value)),
            tmp);

    tmp = Item{"Canon S400", 9988, 499.95};
    vi.insert(
            std::find_if(vi.begin(), vi.end(), Smaller_than(tmp.value)),
            tmp);

    vi.erase(std::find_if(vi.begin(), vi.end(), Cmp_by_name("water")));
    vi.erase(std::find_if(vi.begin(), vi.end(), Cmp_by_name("chair")));

    vi.erase(std::find_if(vi.begin(), vi.end(), Cmp_by_iid(17)));
    vi.erase(std::find_if(vi.begin(), vi.end(), Cmp_by_iid(83)));

    print(li, '\n');

    li.sort([](const Item& a, const Item& b) { return a.name < b.name; });
    li.sort([](const Item& a, const Item& b) { return a.iid < b.iid; });
    li.sort([](const Item& a, const Item& b) { return a.value > b.value; });

    tmp = {"horse", 99, 1.34};
    li.insert(std::find_if(li.begin(), li.end(), Smaller_than(tmp.value)),
            tmp);

    tmp = {"Canon", 9988, 499.95};
    li.insert(std::find_if(li.begin(), li.end(), Smaller_than(tmp.value)),
            tmp);

    li.erase(std::find_if(li.begin(), li.end(), Cmp_by_name("table")));
    li.erase(std::find_if(li.begin(), li.end(), Cmp_by_name("phone")));

    li.erase(std::find_if(li.begin(), li.end(), Cmp_by_iid(58)));
    li.erase(std::find_if(li.begin(), li.end(), Cmp_by_iid(2011)));

    print(li, '\n');
}
catch(std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    std::cerr << "Unknown exception\n";
    return 2;
}
