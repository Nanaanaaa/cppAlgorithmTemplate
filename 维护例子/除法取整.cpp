template<class T>
T floor(T a, T b) {
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b;
    return a / b - 1;
}
template<class T>
T ceil(T a, T b) {
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b + 1;
    return a / b;
}