template <class T>
struct Min {
    T min;
    Min(T min = std::numeric_limits<T>::max() / 2) :min(min) {}
};
template <class T>
Min<T> operator+(const Min<T>& a, const Min<T>& b) {
    return std::min(a.min, b.min);
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
    T min;
    Min(T min = std::numeric_limits<T>::max() / 2) :min(min) {}
    void apply(const Tag<T>& t) {
        min += t.add;
    }
};
template <class T>
Min<T> operator+(const Min<T>& a, const Min<T>& b) {
    return std::min(a.min, b.min);
}