template<class T = i64>
struct Point {
    T x;
    T y;
    Point(const T& x_ = 0, const T& y_ = 0) : x(x_), y(y_) {}

    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point& operator+=(const Point& p)& {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p)& {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point& operator*=(const T& v)& {
        x *= v;
        y *= v;
        return *this;
    }
    Point& operator/=(const T& v)& {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, const Point& b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point& b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T& b) {
        return a *= b;
    }
    friend Point operator/(Point a, const T& b) {
        return a /= b;
    }
    friend Point operator*(const T& a, Point b) {
        return b *= a;
    }
    friend bool operator==(const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }
    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T>& a_ = Point<T>(), const Point<T>& b_ = Point<T>()) : a(a_), b(b_) {}
};

template<class T>
T dot(const Point<T>& a, const Point<T>& b) {
    return a.x * b.x + a.y * b.y;
}

template<class T>
T cross(const Point<T>& a, const Point<T>& b) {
    return a.x * b.y - a.y * b.x;
}

template<class T>
Point<T> rotate(const Point<T>& a) {
    return Point(-a.y, a.x);
}

template<class T>
bool pointOnLineLeft(const Point<T>& p, const Line<T>& l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

using P64 = Point<i64>;