#import "template.typ": *
// Change here
#show: project.with(
  title: "USP - Hoje tem 'in queue' do Ribamar",
  date: datetime.today().display(),
  authors: (
    "Gabriel Morete",
    "Lucas Harada",
    "Thiago Oliveira",
  ),
)

= Template hashing

```bash
sed -n $2','$3' p' $1 | cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
```
The cli command `md5sum` is used to validate if the template was written correctly.

Write the one liner above without line breaks and save it as `hash.sh`, and run
```bash
chmod +x hash.sh
``` 
to make it executable.

To get the hash in `file.cpp` between lines `<l1>` and `<l2>`, run
```sh
./hash.sh <file.cpp> <l1> <l2>
```

Hash is made by scope, delimited by the curly brackets (`"{"`, `"}"`).

The empty hash is 
`d41d8`
while
the hash of `hash.sh` is 
`9cd12`.

= Template
```cpp
#include "bits/stdc++.h"
using namespace std;
#define dbg(x)  cout << #x << " = " << x << endl
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
#define all(x)  x.begin(), x.end()
const int INF = 0x3f3f3f3f;
const long long int llINF = 0x3f3f3f3f3f3f3f;
ios_base::sync_with_stdio(false); 
cin.tie(NULL); cout.tie(NULL);

```
= Makefile
```makefile
#CPP = -O2 -std=gnu++17 -static
#SAN = -fsanitize=address -fsanitize=undefined -fno-sanitize-recover
#STL = -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
% : %.cpp .FORCE
 g++ $(CPP) $(SAN) $(STL) $<
```

= Code

// Script will be used to insert code here
