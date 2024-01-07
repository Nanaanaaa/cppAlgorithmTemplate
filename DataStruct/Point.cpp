template<typename T>
struct Point {
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point& operator+=(Point p)& {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(Point p)& {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point& operator*=(T v)& {
        x *= v;
        y *= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    constexpr friend Point operator+(Point a, Point b) {
        return a += b;
    }
    constexpr friend Point operator-(Point a, Point b) {
        return a -= b;
    }
    constexpr friend Point operator*(Point a, T b) {
        return a *= b;
    }
    constexpr friend Point operator*(T a, Point b) {
        return b *= a;
    }
    constexpr friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }
    constexpr friend bool operator!=(Point a, Point b) {
        return !(a == b);
    }
    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream& operator<<(std::ostream& os, Point p) {
        return os << p.x << " " << p.y;
    }
};