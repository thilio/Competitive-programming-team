// Gerador de números aleatórios

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); -> pode ser global

uniform_int_distribution<int>(l, r)(rng) -> numero inteiro entre [l, r]
shuffle(v.begin(), v.end(), rng) -> embaralha vetor
