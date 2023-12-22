``` cpp
const long long g0 = 3 ,g1 = 332748118, mod = 998244353;
const int N = 1e6 + 10;
int n, m, k;
int qmi(int a, int k, int P = 998244353)
{
    int res = 1;
    while(k)
    {
        if(k&1)res = res * a % P;
        a = a * a % P;
        k >>= 1;
    }
    return res;
}
namespace Poly
{
    int Pos, L, Rev[N];
    void Init(int ll)
    {
        for(Pos = 0, L = 1; L < ll;L <<= 1, ++ Pos);
        for(int i = 0; i < L; i ++ ) Rev[i] = (Rev[i >> 1] >> 1) | ((i & 1) << (Pos - 1));
        return;
    }
    void NTT(long long * C, int opt)
    {
        for(int i = 0; i < L; i ++ )
            if(i < Rev[i]) swap(C[i], C[Rev[i]]);
        for(int mid = 1; (mid << 1) <= L; mid <<= 1)
        {
            long long Wn = qmi((opt == 0) ? g0 : g1, (mod - 1) / (mid << 1)), W = 1;
            for(int i = 0; i < L; i += (mid << 1))
            {
                W = 1;
                for(int j = 0; j < mid; j ++, W = W * Wn % mod)
                {
                    long long tmp = C[i + mid + j] * W % mod;
                    C[i + mid + j] = (C[i + j] + mod - tmp) % mod;
                    C[i + j] = (C[i + j] + tmp) % mod;
                }
            }
        }
        if(opt == 1)
        {
            long long IV = qmi(L, mod - 2);
            for(int i = 0; i < L; i ++ )C[i] = C[i] * IV % mod;
        }
        return;
    }
    void Dot(long long * A, long long * B, long long * C, int ll)
    {
        for(int i = 0; i < ll; i ++ ) 
            C[i] = A[i] * B[i] % mod;
        return;
    }
    void Inte(long long * A, long long * B, int ll)
    {
        for(int i = ll - 1; i >= 0; i -- )
            B[i] = A[i - 1] * qmi(i, mod - 2) % mod;
        B[0] = 0;
        return;
    }
    void Deri(long long * A, long long * B, int ll)
    {
        for(int i = 0; i < ll - 1; i ++ )
            B[i] = A[i + 1] * (i + 1) % mod;
        B[ll - 1] = 0;
        return;
    }
    vector<int> Mul(vector<int> &A,vector<int> &B)
    {
        static long long TmpA[N], TmpB[N];
        int ll = A.size() + B.size() - 1;
        Init(ll);
        for(int i = 0; i < L; i ++ ) TmpA[i] = TmpB[i] = 0;
        for(int i = 0; i < A.size(); i ++ ) TmpA[i] = A[i];
        for(int i = 0; i < B.size(); i ++ ) TmpB[i] = B[i];
        NTT(TmpA, 0); NTT(TmpB, 0);
        for(int i = 0; i < L; i ++ ) TmpA[i] = TmpA[i] * TmpB[i] % mod;
        NTT(TmpA, 1);
        vector<int> C;
        C.clear(); C.resize(ll);
        for(int i = 0; i < ll; i ++ ) C[i] = TmpA[i];
        return C;
    }
    vector<int> Inv(vector<int> &A)
    {
        vector<int> B;
        int ll = A.size();
        static long long Tmp[N], TmpA[N], TmpB[N];
        for(int i = 0; i < (ll << 2);i ++ ) Tmp[i] = 0;
        for(int i = 0; i < (ll << 2); i ++ ) TmpA[i] = TmpB[i] = 0;
        for(int i = 0; i < ll; i ++ ) TmpA[i] = A[i]; 
        TmpB[0] = qmi(TmpA[0], mod - 2);
        for(int now = 2; now < (ll << 1); now <<= 1 )
        {
            Init(now << 1);
            for(int i = 0; i < now; i ++ ) Tmp[i] = TmpA[i];
            for(int i = now; i < (now << 1); i ++ ) Tmp[i] = 0;
            NTT(Tmp, 0); 
            NTT(TmpB, 0);
            for(int i = 0; i < (now << 1); i ++ )
                TmpB[i] = TmpB[i] * (mod + 2 - Tmp[i] * TmpB[i] % mod) % mod;
            NTT(TmpB, 1);
            for(int i = now; i < (now << 1); i ++ ) TmpB[i] = 0;
        }
        B.resize(ll);
        for(int i = 0; i < ll; i ++ ) B[i] = TmpB[i];
        return B;
    }
    vector<int> Sqrt(vector<int> &A)
    {
        int ll = A.size();
        static long long Tmp1[N], Tmp2[N], TmpA[N], TmpB[N];
        for(int i = 0; i < (ll << 2); i ++ )
            Tmp1[i] = Tmp2[i] = TmpA[i] = TmpB[i] = 0;
        for(int i = 0; i < ll; i ++ ) TmpA[i] = A[i];
        long long Inv2 = qmi(2, mod - 2);
        vector<int> B, BB;
        B.clear(); B.push_back(1);
        for(int now = 2; now < (ll << 1); now <<= 1 )
        {
            B.resize(now);
            for(int i = 0; i < now; i ++ ) Tmp1[i] = TmpA[i];
            for(int i = now; i < (now << 1); i ++ ) Tmp1[i] = 0;
            BB = Inv(B);
            for(int i = 0; i < now; i ++ ) Tmp2[i] = BB[i];
            for(int i = now; i < (now << 1); i ++ ) Tmp2[i] = 0;
            Init(now << 1);
            NTT(Tmp1, 0);NTT(Tmp2, 0);
            for(int i = 0; i < (now << 1); i ++ ) Tmp1[i] = Tmp1[i] * Tmp2[i] % mod;
            NTT(Tmp1, 1);
            for(int i = 0; i < now; i ++ ) B[i] = (B[i] + Tmp1[i]) * Inv2 % mod;
        }
        B.resize(ll);
        return B;
    }
    vector<int> Ln(vector<int> &A)
    {
        int ll = A.size();
        vector<int> B;
        B.resize(ll);
        static long long Tmp1[N], Tmp2[N], TmpA[N], TmpB[N];
        for(int i = 0; i < (ll << 2); i ++ ) Tmp1[i] = Tmp2[i] = TmpA[i] = TmpB[i] = 0;
        for(int i = 0; i < ll; i ++ ) TmpA[i] = A[i];
        Deri(TmpA, Tmp1, ll);
        B = Inv(A);
        for(int i = 0; i < ll; i ++ ) Tmp2[i] = B[i];
        Init(ll << 1); NTT(Tmp1, 0); NTT(Tmp2, 0); Dot(Tmp1, Tmp2, Tmp1, L); NTT(Tmp1, 1);
        Inte(Tmp1, Tmp2, ll);
        for(int i = 0; i < ll; i ++ ) B[i] = Tmp2[i];
        return B; 
    }
    vector<int> Exp(vector<int> &A)
    {
        int ll = A.size();
        static long long Tmp1[N], Tmp2[N], TmpA[N], TmpB[N];
        for(int i = 0; i < (ll << 2); i ++ ) Tmp1[i] = Tmp2[i] = TmpA[i] = TmpB[i] = 0;
        for(int i = 0; i < ll; i ++ ) TmpA[i] = A[i]; 
        vector<int> B;
        B.clear();
        vector<int> BB;
        B.push_back(1);
        for(int now = 2; now < (ll << 1); now <<= 1 )
        {
            B.resize(now);
            BB = Ln(B);
            for(int i = 0; i < now; i ++ ) Tmp1[i] = BB[i];
            for(int i = now; i < (now << 1); i ++ ) Tmp1[i] = 0;
            for(int i = 0; i < now; i ++ ) Tmp2[i] = TmpA[i];
            for(int i = now; i < (now << 1); i ++ ) Tmp2[i] = 0;
            for(int i = 0; i < now; i ++ ) TmpB[i] = B[i];
            for(int i = now; i < (now << 1); i ++ ) TmpB[i] = 0;
            Init(now << 1);
            NTT(Tmp1, 0); NTT(Tmp2, 0); NTT(TmpB, 0);
            for(int i = 0; i < (now << 1); i ++ ) TmpB[i] = TmpB[i] * (mod + 1 - Tmp1[i] + Tmp2[i]) % mod;
            NTT(TmpB, 1);
            for(int i = 0; i < now; i ++ ) B[i] = TmpB[i];
        }
        B.resize(ll);
        return B;
    }
    vector<int> Pow(vector<int> x, long long y, int lim)
    {
        if(y == -1) return Inv(x);
        vector<int> sum;
        sum.resize(lim + 1);
        sum[0] = 1;
        for( ; y; y >>= 1, x = Mul(x, x), x.resize(lim + 1))
            if(y & 1) sum = Mul(sum, x), sum.resize(lim + 1);
        return sum;
    }
};
```