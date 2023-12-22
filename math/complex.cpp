template<class D>
struct complex {
    D a, b;
    complex(D a = 0, D b = 0) :a(a), b(b) {}
    complex operator + (const complex& t) { return complex(a + t.a, b + t.b); }
    complex operator - (const complex& t) { return complex(a - t.a, b - t.b); }
    complex operator * (const complex& t) { return complex(a * t.a - b * t.b, a * t.b + t.a * b); }
};