#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <numeric>

class Less_than {
    double v;
public:
    Less_than(double vv) : v{vv} { }

    bool operator()(const double val) { return val < v; }
};

template<typename C> void print(const C& c, char sep = '\n')
{
    std::cout << "CONTAINER ELEMENTS:\n"
              << "===================\n";

    for (const auto ele : c)
        std::cout << ele << sep;

    std::cout << '\n';
}

int main()
try {
    const std::string iname {"input_floats.txt"};
    std::ifstream ifs {iname};
    if (!ifs) throw std::runtime_error("Could not read from file: " + iname);

    std::vector<double> vd;
    for (double d; ifs >> d; )
        vd.push_back(d);

    print(vd);

    std::vector<int> vi (vd.size());
    std::copy(vd.begin(), vd.end(), vi.begin());

    for (int i = 0; i < vd.size(); ++i)
        std::cout << vd[i] << '\t' << vi[i] << '\n';

    double double_sum = std::accumulate(vd.begin(), vd.end(), 0.0);

    std::cout << "Sum of vector<double>: " << double_sum << '\n';

    double diff_sum =
        std::inner_product(vd.begin(), vd.end(),
                vi.begin(),
                0.0,
                std::plus<double>(),
                std::minus<double>());

    std::cout << "The cumulative difference of int(double) truncs is: "
              << diff_sum << '\n';

    std::reverse(vd.begin(), vd.end());

    print(vd);

    double vd_mean = double_sum / vd.size();

    std::cout << "The mean of vd is: " << vd_mean << '\n';

    std::vector<double> vd2 (vd.size());    // too big?

    auto it = std::copy_if(vd.begin(), vd.end(), vd2.begin(),
            Less_than(vd_mean));
    vd2.resize(std::distance(vd2.begin(), it));

    print(vd2);

    std::sort(vd.begin(), vd.end());

    print(vd);
}
catch(std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    std::cerr << "Unknown exception\n";
    return 2;
}
