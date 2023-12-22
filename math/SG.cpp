i64 getSG(i64 p, i64 l, i64 r) {
    i64 len = p * l - l + 2;
    i64 cur = l - 1;
    while (r >= cur + len) {
        cur += len;
        len *= p;
    }
    i64 ans = 0, last = len + 1;
    for (auto x = len / (p * l - l + 2); x; x /= p) {
        if ((r - cur) % x == 0) {
            ans += (r - cur) / x - (r - cur) / last;
            break;
        }
        ans = len / x - 1;
        last = x;
    }
    return ans;
}
