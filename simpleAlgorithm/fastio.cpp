class IO
{
    constexpr static int N = 1000010, M = 1000000;
    char ibuf[N], obuf[N], * pil = ibuf, * pir = ibuf, * po = obuf;
    constexpr bool blankc(const char& c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }
public:
    constexpr void read() { if (pil == pir) pir = (pil = ibuf) + fread(pil, 1, 1 << 18, stdin); }
    void write() { fwrite(obuf, 1, po - obuf, stdout), po = obuf; }
    constexpr char ichar() { return read(), pil == pir ? EOF : *pil++; }
    constexpr void ochar(char c) { *po++ = c; if (po > obuf + M) write(); }
    char getc() { char c; for (; blankc(c = ichar());); return c; }
    constexpr IO& operator >> (int& i)
    {
        char c = ichar(); int s = 1; i = 0;
        for (; !isdigit(c); c = ichar()) if (c == '-') s = -1;
        for (; isdigit(c); c = ichar()) i = (i << 1) + (i << 3) + (c ^ 48);
        return i *= s, *this;
    }
    constexpr IO& operator >> (i64& i)
    {
        char c = ichar(); i64 s = 1; i = 0;
        for (; !isdigit(c); c = ichar()) if (c == '-') s = -1;
        for (; isdigit(c); c = ichar()) i = (i << 1) + (i << 3) + (c ^ 48);
        return i *= s, *this;
    }
    constexpr IO& operator >> (char& c) { return c = ichar(), *this; }
    IO& operator >> (char* s)
    {
        char c = ichar(); for (; blankc(c);) c = ichar();
        for (; !blankc(c); c = ichar()) *s++ = c;
        return *s = 0, *this;
    }
    constexpr IO& operator << (int i)
    {
        char stk[30], * top = stk;
        if (i < 0) ochar('-'), i = -i; if (!i) *++top = '0';
        for (; i; i /= 10) *++top = i % 10 + '0'; for (; top != stk;) ochar(*top--);
        return *this;
    }
    constexpr IO& operator << (i64 i)
    {
        char stk[30], * top = stk;
        if (i < 0) ochar('-'), i = -i; if (!i) *++top = '0';
        for (; i; i /= 10) *++top = i % 10 + '0'; for (; top != stk;) ochar(*top--);
        return *this;
    }
    constexpr IO& operator << (const char& c) { return ochar(c), * this; }
    constexpr IO& operator << (const char*& s) { for (; *s;) ochar(*s++); return *this; }
}io;