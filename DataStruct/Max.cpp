template <class T>
struct Max {
    T max;
    Max(T max = std::numeric_limits<T>::min() / 2) :max(max) {}
};
template <class T>
Max<T> operator+(const Max<T>& a, const Max<T>& b) {
    return std::max(a.max, b.max);
}

template <class T>
struct Tag {
    T add;
    Tag(T add = 0) :add(add) {}
    void apply(const Tag& t) {
        add += t.add;
    }
};
template <class T>
struct Min {
    T max;
    Max(T max = std::numeric_limits<T>::min() / 2) :max(max) {}
    void apply(const Tag<T>& t) {
        max += t.add;
    }
};
template <class T>
Max<T> operator+(const Max<T>& a, const Max<T>& b) {
    return std::max(a.max, b.max);
}