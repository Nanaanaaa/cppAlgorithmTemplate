template<class P, class Q> P floor(P a, Q b) {
    P res = a / b;
    if ((a ^ b) < 0 && a % b != 0) {
        res--;
    }
    return res;
}

template<class P, class Q> P ceil(P a, Q b) {
    P res = a / b;
    if ((a ^ b) > 0 && a % b != 0) {
        res++;
    }
    return res;
}