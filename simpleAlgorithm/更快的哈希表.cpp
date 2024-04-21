#include <ext/pb_ds/assoc_container.hpp>
const int rnd = std::chrono::high_resolution_clock::now().time_since_epoch().count();
struct hash_ {
    int operator()(int x) const { return x ^ rnd; }
};
template<typename T, typename U>
using umap = __gnu_pbds::gp_hash_table<T, U, hash_>;
