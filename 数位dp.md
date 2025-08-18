# 数位dp求前缀的一般做法

假设某个数字系统，表示$x \in \mathbb{N}$
$$
x = \sum_{i = 0}^{n - 1}c_i p_i
$$
假设$\{p_i\}$为基，$c_i$为基中第$i$个元素出现次数，满足$c_{n - 1} \neq 0$，设$m = \max_{i = 0}^{n = 1}\{c_i\}$ 求$[l, r]$的答案。



其实就是求$[1, l - 1]$ 和$[1, r]$的答案然后用后者减去前者，有这样一个求$[1, r)$答案的方法：

```cpp
T work(int rem, int cnt, ...) // rem表示剩余多少位置可以放，cnt表示当前一共放的sum{c_i}

T solve(auto&& c) {
    T ans = 0;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 1; j <= c; j++) {
            ans += work(i - 1, j, ...);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = int(i == 0); j < c[i]; j++) {
            ans += work(n - i - 1, j, ...);
        }
    }
    return ans;
}
```

实际用起来, $[l, r]$的答案就是$solve(c_{r + 1}) - solve(c_l)$

其中$c_r, c_l$分别表示$r, l$在这个数字系统中的$\{c_{n - 1}, c_{n - 2}, \dots, c_0\}$ （从高位到低位排列）