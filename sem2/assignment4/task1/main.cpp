#include <iostream>
#include <vector>
#include <cmath>

class SparseTable
{
public:
    size_t size;
    size_t height;
    std::vector<int> source;
    std::vector<std::vector<size_t>> array;
    SparseTable (std::vector<int> v)
    {
        source = v;
        size = v.size();
        height = std::ceil(std::log2(size));
        array.resize(size, std::vector<size_t>(size, 0));
        for( size_t i = 0; i < size; i++) {
            array[0][i] = i;
        }
        for( size_t i = 1; i < height; i++)
        {
            for( size_t j = 0; j < size - (1 << i) + 1; j++)
            {
                if(source[array[i-1][j]] < source[array[i-1][j + (1 << (i-1))]]) {
                    array[i][j] = j;
                } else {
                    array[i][j] = j + (1 << (i-1));
                }
            }

        }
    }

    /** @pre a < b
     @pre a < size
     @pre b < size */
    size_t min (size_t a, size_t b) {
        if (b < a) return a;
        size_t length = b - a;
        size_t logLength = std::floor(std::log2(length));
        size_t leftMinIndex = array[logLength][a];
        size_t rightMinIndex = array[logLength][b - (1 << logLength)];
        if(source[leftMinIndex] < source[rightMinIndex]) {
            return leftMinIndex;
        } else {
            return rightMinIndex;
        }
    }

    int solver (size_t a, size_t b) {
        size_t minIndex = min (a, b);
        size_t leftMinIndex = min (a, minIndex-1);
        size_t rightMinIndex = min (minIndex+1, b);
        if(source[leftMinIndex] < source[rightMinIndex]) {
            return source[leftMinIndex];
        } else {
            return source[rightMinIndex];
        }
    }
};

int main () {
    size_t n, m;
    size_t a, b;
    std::cin >> n >> m;
    std::vector<int> v (n, 0);
    for (size_t i(0); i < n; ++i) {
        std::cin >> v[i];
    }
    SparseTable st (v);
    for (size_t i(0); i < m; ++i) {
        std::cin >> a >> b;
        std::cout << st.solver (a, b) << std::endl;
    }
}
