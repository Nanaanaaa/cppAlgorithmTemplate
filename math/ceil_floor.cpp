template<class T, class U>
constexpr T floor(T x, U y) {
    return x / y - (x % y != 0 && (x < 0) != (y < 0));
}

template<class T, class U>
constexpr T ceil(T x, U y) {
    return x / y + (x % y != 0 && (x > 0) == (y > 0));
}