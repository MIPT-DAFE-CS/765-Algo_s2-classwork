#include <iostream>

struct Segment {
    int min,max;

    int len () {
        return max-min;
    }
};

bool isIntersects(const Segment & p1, const Segment & p2) {
    int min = std::max(p1.min, p2.min);
    int max = std::min(p1.max, p2.max);
    return max>=min;
}


bool operator<(const Segment & p1, const Segment & p2) {
    if (p1.max < p2.max) {
        return true;
    } else if (p1.max == p2.max) {
        if (p1.min <= p2.min) {
            return true;
        }
    }
    return false;
}

Segment operator&(const Segment & p1, const Segment & p2) {
    int min = std::max(p1.min, p2.min);
    int max = std::min(p1.max, p2.max);
    return Segment{min,max};
}

struct Heap {
    private:
        int _size;
        Segment * _buffer;
    public:
        Heap(Segment * buffer, int n) {
            _size=n;
            _buffer=buffer;
            for (int i=n-1; i>=0; i--) {
                down(i);
            }
        }

        int size() const {
            return _size;
        }

        void sort() {
            int z=_size;
            while (_size>1) {
                std::swap(_buffer[0],_buffer[_size-1]);
                _size--;
                down(0);
            }
            _size=z;
        }

        bool hasLeft(int index) const {
            return index * 2 + 1 < _size;
        }

        bool hasRight(int index) const {
            return index * 2 + 2 < _size;
        }

        int left (int index) const {
            return index * 2 + 1;
        }

        int right (int index) const {
            return index * 2 + 2;
        }

        int parent (int index) const {
            return (index - 1) / 2;
        }

        void down (int index) {
            if (hasLeft(index) && hasRight(index)){
                int max = (_buffer[left(index)] < _buffer[right(index)])? right(index) : left(index);
                if (_buffer[index] < _buffer[max]) {
                    std::swap(_buffer[index], _buffer[max]);
                    down(max);
                }
            }
            if (hasLeft(index)) {
                if (_buffer[index] < _buffer[left(index)]) {
                    std::swap(_buffer[index], _buffer[left(index)]);
                    down(left(index));
                }
            }
        }
        void debug() const {
            for(int i=0; i<size(); ++i) {
                std::cout << _buffer[i].min << " " << _buffer[i].max << " | ";
            }
            std::cout << std::endl;
        }
};


int main () {
    int n;
    std::cin>>n;

    Segment a[n];
    for (int i=0; i<n; i++) {
        std::cin >> a[i].min >> a[i].max;
    }

    Heap heap(a,n);
    heap.sort();
//    heap.debug();

    int count = 0;
    Segment showing{-1,-1};

    for (int i = 0; i < n; i++) {

        if (a[i].min > showing.max) {
            count += 2;
            showing.min = a[i].max - 1;
            showing.max = a[i].max;
        } else if (a[i].min == showing.max) {
            count += 1;
            showing.min = showing.max;
            showing.max = a[i].max;
        } else if (a[i].min > showing.min && a[i].max > showing.max) {
            count +=1;
            showing.min = showing.max;
            showing.max = a[i].max;
        } else if (a[i].min > showing.min) {
            count +=1;
            showing.min = a[i].max;
        }
    }

    std::cout << count;
}