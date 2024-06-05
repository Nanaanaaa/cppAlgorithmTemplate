template<class T, class U> T floor(const T& x, const U& y) {
    return x / y - (x % y && (x ^ y) < 0);
}

template<class T, class U> T ceil(const T& x, const U& y) {
    return floor(x + y - 1, y);
}