mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int>(l, r)(rng)// rand int in [l,r]
shuffle(v.begin(), v.end(), rng)// shuffle array