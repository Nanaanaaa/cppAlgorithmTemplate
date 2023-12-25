template<class T, class U> T floor(T x, U y) {
    return x / y - (x % y && (x ^ y) < 0);
}

template<class T, class U> T ceil(T x, U y) {
    return floor(x + y - 1, y);
}