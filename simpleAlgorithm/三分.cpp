int l = 0, r = 1e6;
for (int times = 0; times < 100; times++)
{
    int lmid = l + (r - l) / 3;
    int rmid = r - (r - l) / 3;
    if (cal(lmid) < cal(rmid)) r = rmid;
    else l = lmid;
}

auto ans = 1e18L;
for (int i = l; i <= r; i++) ans = std::min(ans, cal(i));