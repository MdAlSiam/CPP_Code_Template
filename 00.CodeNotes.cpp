/// In the name of Allah SWT

using namespace std;
#include <bits/stdc++.h>

#define ll long long int
#define dd double

#define scl(x)              scanf("%lld", &x)
#define scll(x, y)          scanf("%lld %lld", &x, &y)
#define scd(x)              scanf("%lf", &x)
#define scdd(x, y)          scanf("%lf %lf", &x, &y)

#define prl(x)              printf("%lld\n", x)
#define prll(x, y)          printf("%lld %lld\n", x, y)
#define prYes               printf("YES\n")
#define prNo                printf("NO\n")
#define aNewLine            printf("\n")

#define ON(n, i)            (n|(1LL<<i))
#define OFF(n, i)           (n&(~(1LL<<i)))
#define CHK(n, i)           (n&(1LL<<i))

#define For(i, x, y)        for(ll i = x; i < y; i++)
#define Mem(ara, x)         memset(ara, x, sizeof(ara))

#define pb                  push_back
#define pll                 pair<ll, ll >
#define ff                  first
#define ss                  second

#define maxn                200005LL ///2x10^5 + 5

#define pi                  acos(-1.00)
#define eps                 0.0000000001 ///10^-10
#define inf                 LONG_LONG_MAX
#define mod                 1000000007LL ///10^9+7

bool debug = false;

ll t, test, temp;
ll n, m, k, kount;
ll a, b, c, ans, u, v;
ll x, y, z = -1, maxi, mini;

ll ara[maxn];
string str;

// [001] Fibonacci Freeze

// [how many fibonacci numbers][how many digits can be at max]
int fib[5005][1200]; 

void make_fib() {
    fib[0][0] = 0;
    fib[1][0] = 1;

    // In the matrix, LSB at left most position
    for (ll i = 2; i < 5005; i++) {
        for (ll j = 0; j < 1200; j++) {

            fib[i][j] += fib[i-1][j] + fib[i-2][j];

	        if (fib[i][j] > 9) {
                fib[i][j+1] += fib[i][j] / 10;
                fib[i][j] %= 10;
            }
        }
    }
}


// [002] GCD

ll gcd(ll a, ll b) {
    if(a % b == 0) return b;
    return gcd(b, a%b);
}


// [003] Trailing 0s of n!

ll zerosinfact(ll n) {
    ll ret = 0;
    for (ll i = 5; i <= n; i *= 5) {
        ret += (n/i);
    }
    //Also count 2s if required
    return ret;
}

// [004] Bigmod, Inverse Mod, Factorial, nCk

ll multiply(ll num1, ll num2) {return ((num1%mod)*(num2%mod))%mod;}
	 
ll add(ll num1, ll num2) {return ((num1%mod)+(num2%mod))%mod;}
	 
ll bigMod(ll base, ll pow) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    if (pow & 1) {
       return multiply(bigMod(base, pow-1), base);
    }
    else {
        ll ret = bigMod(base, pow/2);
	    ret = multiply(ret, ret);
        return ret;
    }
}
 
ll inverseMod(ll num1) {return bigMod(num1, mod-2);}

ll nCk(ll n, ll k) {
    return multiply(facts[n], multiply(inverseMod(facts[k]), inverseMod(facts[n-k])));
}

ll facts[1100];
ll make_fact() {
    facts[0] = facts[1] = 1;
    for (ll i = 2; i < 1100; i++) {
        facts[i] = multiply(facts[i-1], i);
    }
}

// [005] Sieve Techniques

// Sieve 1

ll prime[sqrt(maxn)+10];
bool mark[maxn] = {false};

void sieve1() {
    prime[0] = 2;
    ll index = 1;

    for (ll i = 3; i*i <= maxn; i += 2) {
        if (mark[i] == false) {
            for (ll j = i*i; j <= maxn; j += i+i) {
                mark[j] = true;
            }
        }
    }

    for (ll i = 3; i <= maxn && index < (ll)sqrt(maxn)+10; i += 2) {
        if (mark[i] == false) prime[index++] = i;
    }
}

// Sieve 2

vector<ll> pr;

void ektuonnorokom() {
	for(ll i = 2; i < 86028157; i++) {
		if(mark[i] == false) pr.pb(i);
		for(ll j = 0; j < pr.size() && pr[j]*i <= 86028157; j++) {
			mark[i*pr[j]] = true; ///composite marks are true
		}
	}
}

// Sieve 3 (Time-Memory Efficient)

bool mark[maxn/2];
ll primes[maxn/10];

void sieve() {
	memset(mark, false, sizeof(mark));
	for (ll i = 3; i <= maxi; i += 2) {
		if (mark[i/2] == false) {
			for (ll j = i; i*j <= maxi; j += 2) {
				mark[(i*j)/2] = true;
			}
		}
	}
	ll pin = 0;
	primes[pin++] = 2;
	for(ll i = 3; i <= maxi; i += 2)
		if(mark[i/2] == false) primes[pin++] = i;
}

// [006] Prime Divisor Kount

ll mark[maxn]; // number upper limit
// [r_i][till this number] = how many r_i prime factors holder occured till this number
ll cumkount[11][maxn]; 
void sieve_cumkount() {
	for (ll i = 2; i <= maxn; i += 2) mark[i]++;
	for (ll i = 3; i <= maxn; i += 2) {
		if (mark[i] == 0) {
			for(ll j = i; j <= maxn; j += i) mark[j]++;
        }
    }

	for(ll i = 0; i < 11; i++) {
		for(ll j = 1; j <= maxn; j++) {
			if(mark[j] == i) cumkount[i][j] = cumkount[i][j-1] + 1;
			else cumkount[i][j] = cumkount[i][j-1];
		}
	}
}

// [007] Prime Factors

void primeFactors(ll n) {
    ll num = n;
    ll root = sqrt(num);
  
    ll factors[root+10];
    ll power[root+10];
 
    ll index = 0;
 
    ll factorKount = 0;

    if (num%2 == 0) {
        factors[index] = 2;
        factorKount = 0;
        while (num%2 == 0) {
            num /= 2;
            factorKount++;
        }
        power[index] = factorKount;
        index++;
    }

    for (ll i = 3; i <= root; i += 2) {
        if (num % i == 0) {
           factors[index] = i;
           factorKount = 0;
           while (num%i == 0) {
               num /= i;
               factorKount++;
           }
           power[index] = factorKount;
           index++;
       }
    }

    if (num != 1) {
       factors[index] = num;
       num /= num;
       power[index] = 1;
       index++;
    }

    ll factorWithMaxPower;
    ll theMaxPower = -1;

    for (ll i = 0; i < index; i++) {
        if (power[i] > theMaxPower) {
            theMaxPower = power[i];
            factorWithMaxPower = factors[i];
        }
   }

   printf("%lld\n", theMaxPower);
}

// all factors (prime or non-prime)

vector<ll> allfactors;
void find_prime_factors(ll n) {
    for (ll i = 1; i*i <= n; i++) {
        if (n%i == 0) {
            allfactors.pb(i);
            if (i != n/i) allfactors.pb(n/i);
        }
    }
}

// [008] nCr DP
ll dp[100][100];

ll find_nCr(ll n, ll r) {
    if (r == n) return 1LL;
    if (r == 1) return n;

    ll &ret = dp[n][r];
    if (ret != -1) return ret;

    ret = find_nCr(n-1, r) + find_nCr(n-1, r-1);

    return ret;
}

// [009] Knapsac DP [UVa 10130]

ll weight[1010], cost[1010], dp[1010][40];
ll number_of_items, capacity;

ll knapsac(ll i, ll w) {
    if (i >= number_of_items) return 0LL;
    if (dp[i][w] != -1) return dp[i][w];

    ll profit1 = 0, profit2 = 0;

    if (w + weight[i] <= capacity) {
        profit1 = cost[i] + knapsac(i+1, w+weight[i]);
    }

    profit2 = knapsac(i+1, w);

    dp[i][w] = max(profit1, profit2);

    return dp[i][w];
}

// [010] Coin Change DP (without setting memory for every query)

// Coin values
ll coins[] = {50, 25, 10, 5, 1};
ll make; // target amount
ll dp[6][8000];

ll call(ll i, ll amount) {
    if (i >= 5) {
        if (amount == 0LL) return 1LL;
        else return 0LL;
    }

    ll& ret = dp[i][amount];
    if (ret != -1) return ret;

    ll ret1 = 0LL, ret2 = 0LL;

    if (amount - coins[i] >= 0) 
        ret1 = call(i, amount - coins[i]);
    ret2 = call(i+1, amount);

    return ret = ret1 + ret2;
}

int in_main_for_calling_coin_change() {
    memset(dp, -1, sizeof(dp));

    while (scanf("%lld", &make) == 1LL)
        printf("%lld\n", call(0, make));
}

// [011] Coin Change DP (with limited number of coins) [LOJ 1231]

int val[56], permit[56], memtab[56][1024], n, make;

ll explore(ll i, ll amount) {
    if (amount == make) return 1LL;
    if (i == n) return 0LL;

    if (memtab[i][amount] != -1) return memtab[i][amount];

    ll ret = 0;

    for (ll xx = 0; xx <= permit[i] && amount+val[i]*xx <= make; xx++) {
        ret += explore(i+1, amount+val[i]*xx);
        ret %= mod;
    }

    return memtab[i][amount] = ret;
}

// [012] Bitwise Operations

ll setBit(ll N, ll pos) {return N = N | (1LL<<pos);}
ll resetBit(ll N, ll pos) {return N = N & ~(1<<pos);}
bool checkBit(ll N, ll pos) {return (bool)(N & (1<<pos));}

// [013] LIS with solution print

ll value[] = {-200, -100, 5, 0, 9, 2, 7, 3, 4};
ll n = sizeof(value) / sizeof(ll);
ll dp[maxn];
ll dir[maxn];

ll longestfrom(ll u) {

    if (dp[u] != -1LL) return dp[u];

    ll maxlen = 0;
    for (int v = u+1; v < n; v++) {
        if (value[v] > value[u]) {
            if (longestfrom(v) > maxlen) {
                maxlen = longestfrom(v);
                dir[u] = v;
            }
        }
    }

    return dp[u] = 1+maxlen;
}

int at_main_LIS() {
    memset(dp, -1, sizeof(dp));
    memset(dir, -1, sizeof(dir));

    ll start, LIS_len = 0;

    for (ll i = 0; i < n; i++) {
        if (longestfrom(i) > LIS_len) {
            LIS_len = longestfrom(i);
            start = i;
        }
    }

    cout << "Length of LIS: " << LIS_len << endl;
    ll curr = start;

    while (1) {
        cout << value[curr] << " ";
        curr = dir[curr];
        if (dir[curr] == -1 ) {
            cout << value[curr] << " ";
            break;
        }
    }
}

// [014] Longest Common Subsequence

/*
Example Iteration

                  #   # # #  
    -     Empty A G G T A B
    Empty     0 0 0 0 0 0 0
   #G         0 0 1 1 1 1 1
    X         0 0 1 1 1 1 1
   #T         0 0 1 1 2 2 2
    X         0 0 1 1 2 2 2
   #A         0 1 1 1 2 3 3
    Y         0 1 1 1 2 3 3
   #B         0 1 1 1 2 3 4
*/

void make_lcs(string str1, string str2) {
    str1 = '#'+str1;
    str2 = '#'+str2;

    ll lcs_tab[str1.length()][str2.length()];

    for (ll i = 0; i < str1.length(); i++) {
        for (ll j = 0; i < str2.length(); j++) {
            if (i == 0 or j == 0) {
                lcs_tab[i][j] = 0;
            }
            else if (str1[i] == str2[j]) {
                lcs_tab[i][j] = lcs_tab[i-1][j-1]+1;
            }
            else {
                lcs_tab[i][j] = max(lcs_tab[i][j-1], lcs_tab[i-1], j);
            }
        }
    }
}


// [015] Subset Sum Table (UVa 624)

ll tracks[26]; // Set of numbers
ll mat[26][100005]; //[num_of_elements_in_set][target_subset_sum]
ll total_length, number_of_tracks;

ll make_matrix() {
    for (ll i = 0; i <= number_of_tracks; i++) {
        for (ll j = 0; j <= total_length; j++) {
            if(i == 0 || j == 0) mat[i][j] = 0;
            else if (j < tracks[i]) mat[i][j] = mat[i-1][j];
            else mat[i][j] = max(mat[i-1][j], tracks[i] + mat[i-1][j-tracks[i]]);
        }
    }
    return mat[number_of_tracks][total_length];
}

void traverse_print() { 
    ll taken[26], index = 0;
    ll xp = number_of_tracks, yp = total_length;
    while (true) {
        if(xp == 0 || yp == 0) break;
        else if(mat[xp-1][yp] == mat[xp][yp]) xp--;
        else{
            taken[index++] = tracks[xp];
            yp -= tracks[xp];
            xp--;
        }
    }
    for (ll i = index-1; i >= 0; i--) printf("%d ", taken[i]);
}

// [016] 8 Queen Problem 

// Will store the position of row for each column where any queen exist safely
int position[10];

// for counting how many combinations exist
int kount = 0;

bool isSafe(int ro, int col) {
    /// To check the queen at position (ro, col) is safe or not
    /// First check risks created by the previous queens

    /// If any queen exist already in the same row
    for (int kol = col; kol > 0; kol--)
        if (position[kol] == ro) return false;

    /// If any queen already in the primary diagonal
    for(int i = ro, j = col; i > 0 && j > 0; i--, j--)
        if(position[j] == i) return false;

    /// If any queen already in the secondary diagonal
    for(int i = ro, j = col; i > 0 && j > 0; i++, j--)
        if(position[j] == i) return false;

    return true;

}

void call(int col) {

    if (col == 9) {
        /// Eight queens are already placed safely for a combination!
        /// Dam da dam da dam!
        /// Print this!

        for (int i = 1; i <= 8; i++) {
            if (i == 1) cout << "{ " << position[i] << ", ";
            else if (i == 8) cout << position[i] << " },\n";
            else cout << position[i] << ", ";
        }

        kount++; /// A new combination found.

        return;
    }

    /// Traverse all rows and see if that row is safe for that column
    for (int i = 1; i <= 8; i++) {
        if (isSafe(i, col)) {
            /// If the position is safe
            /// then place a queen here and move to the next column
            position[col] = i;
            call(col+1);
            position[col] = -1; ///backtrack (remove used queen to check another combination)
        }
    }
}

int n_queen_main() {
    memset(position, -1, sizeof position);
    /// Initially there is no queen in any row for any column
    /// Will start calculate from the first column
    call(1);
    cout << "Total = " << kount << endl;
}

/*
    11 12 13 14
    21 22 23 24
    31 32 33 34
    41 42 43 44
    51 52 53 54

    In major diagonal, value of (row+column) is the same, and increases by one per diagonal
    Here, 2, 3, 4, 5, ...

    In minor diagonal, value of (row+column) increases by 2 per element.
*/

// [017] Longest Path using BFS

ll level[maxn] = {-1};
vector<ll> adj_list[maxn];
vector<ll>::iterator it;

void BFS_and_Levelling(ll src) {

    queue<ll> q;

    level[src] = 0;
    q.push(src);

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        for(it = adj_list[u].begin(); it != adj_list[u].end(); it++) {
            ll v = *it;
            // Make the level as much as possible to make the path longer
            if (level[v] < level[u]+1) {
                level[v] = level[u]+1;
                q.push(v);
            }
        }
    }
}

// [018] Levelling and counting number of nodes in subtree

vector<ll> adj_list[maxn];
vector<ll>::iterator it;
ll level[maxn];
ll subordinate[maxn];
ll profit[maxn];

void searc_h(ll dad, ll son) {
    level[son] = level[dad] + 1;
    subordinate[son] = 1;
  
 	for (ll i = 0; i < adj_list[son].size(); i++) {
 		ll son_of_son = adj_list[son][i];
 		if(son_of_son == dad) continue;
  
 		searc_h(son, son_of_son);
  
 		subordinate[son] += subordinate[son_of_son];
 	}
 
    profit[son] = subordinate[son] - 1 - level[son];

}

// [019] Graph Coloring

ll maxcolor(ll src) {
    ll redkount = 0, greenkount = 0;

    queue<ll> q;
    q.push(src);
    color[src] = RED;
    redkount++;

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        list<ll>::iterator it;

        for (it = adj_list[u].begin(); it != adj_list[u].end(); it++) {
            ll v = *it;
            if (color[v] == WHITE) {
                if (color[u] == GREEN) {
                    color[v] = RED;
                    redkount++;
                }
                else{
                    color[v] = GREEN;
                    greenkount++;
                }
                q.push(v);
            }
        }
    }

    return max(redkount, greenkount);
}

// [020] Diameter of a Tree/BFS with DFS

vector<ll> adj_list[200005];
ll level[200005];

void dfs(ll dad, ll son) {
    if (dad == -1) {
        level[son] = 0;
    }
    else {
        level[son] = level[dad] + 1;
    }

    for (ll son_of_son : adj_list[son]) {
        if (son_of_son == dad) {
            continue;
        }
        dfs(son, son_of_son);
    }
}

in_the_diameter_of_tree_main() {
    // DFS from any node
    dfs(-1, a);
    
    // find any maxlevel node
    ll id = 1;
    for (ll i = 1; i <= n; i++) {
        if (level[i] > level[id]) {
            id = i;
        }
    }

    // again DFS from that maxlevel node
    dfs(-1, id);

	// again find new maxlevel
    id = 1;
    for (ll i = 1; i <= n; i++) {
        if (level[i] > level[id]) {
            id = i;
        }
    }

    // hence, level[id] (maxlevel) is the diameter of the tree
    // diameter of a tree = the longest path between two leaves
}


// [021] Constructing priority queue

// এখানে arg কে প্রায়োরিটি কিউতে টপে রাখা হবে। 
// arg এর লেংথ বেশি হলে প্রায়োরিটি পাবে।
// সমান লেংথ হলে লেফটে থাকলে প্রায়োরিটি পাবে।
// arg should be at the top of priority queue
// arg, to be prioritised-
// -> length of arg should be greater 
// -> In case of length tie, arg should be at left

struct info {
    ll len;
    ll left;
    ll right;

    info(ll _left, ll _right) {
        left = _left;
        right = _right;
        len = _right - _left + 1;
    }

    bool operator < (const info &arg) const {
        if (len == arg.len) return arg.left < left;
        return arg.len > len;
    }
};

// initialise priority queue
priority_queue<info> pq;

// [022] Invoke compare in sorting a vector

sort(strs.begin(), strs.end(), 
    [](const auto &a, const auto &b) {
        if (a.size() == b.size()) return a < b;
        return a.size() > b.size();
    }
);

// [023] Check if subsequnce of other (Bruteforce)

bool isSubsequence(string subseqholder, string subseqcandidate) {
    int pointer = 0;
    for (int i = 0; i < subseqcandidate.size(); i++) {        
        while (true) {
            if (pointer >= subseqholder.size()) return false;
            if (subseqholder[pointer] == subseqcandidate[i]) {
                pointer++;
                break;
            }
            pointer++;
        }
    }

    return true;
}

// [024] Printing Permutations

void permutation(ll lo, ll hi) {

    if (lo == hi) {
        for(ll i = 0; i <= hi; i++)
            printf(i == hi ? "%d\n" : "%d ", init[i]);
        return;
    }

    for(ll i = lo; i <= hi; i++) {
        // Swap every other element including currrent element with the current element
        swap(init[lo], init[i]);
        permutation(lo+1, hi);
        // Backtrack: Place the current element at the lowest position again
        swap(init[lo], init[i]);
    }
}

// Lexicographically Sorted Permutation using C++ Library

ll arr[] = {1, 2, 3}; 
sort(arr, arr+3); 

// In asceding order 
do { 
    cout << arr[0] << " " << arr[1] << " " << arr[2] << "\n"; 
} while (next_permutation(arr, arr + 3)); 

// In descending order
do { 
    cout << arr[0] << " " << arr[1] << " " << arr[2] << "\n"; 
} while (prev_permutation(arr, arr + 3)); 

// [025] Segment Tree: The Mighty Thing

#define mx 100001LL

ll arr[mx];
ll tree[3*mx];

void init(ll node, ll b, ll e) {
    // sum from b till e in tree[node]
    if (b == e) {
        tree[node] = arr[b];
        return;
    }

    ll Left = node * 2;
    ll Right = node * 2 + 1;
    ll mid = (b + e) / 2;

    init(Left, b, mid);
    init(Right, mid + 1, e);

    // Fetch sum from subordinates
    tree[node] = tree[Left] + tree[Right];
}

ll query(ll node, ll b, ll e, ll i, ll j) {
    // Current node contains sum from index b to index e
    // Looking for the sum from index i to index j

    // If current node does not contain any part from the segment we are looking for
    // বাইরে চলে গিয়েছে
    if (i > e || j < b) return 0; 

    // Current node is in the range we are looking for
    // রিলেভেন্ট সেগমেন্ট
    if (i <= b && e <= j) return tree[node]; 

    // Oterwise go to the subordinate nodes
    // আরো ভাঙতে হবে
    ll Left = node * 2; 
    ll Right = node * 2 + 1;
    ll mid = (b + e) / 2;

    ll p1 = query(Left, b, mid, i, j);
    ll p2 = query(Right, mid + 1, e, i, j);
    // Return the sum got from the subordinates
    // বাম এবং ডান পাশের যোগফল
    return p1 + p2; 
}

void update(ll node, ll b, ll e, ll i, ll newvalue) {
    // Current node contains sum from index b to index e
    // We want to assign newvalue to index i

    // Current range does not contain index i
    // বাইরে চলে গিয়েছে
    if (i > e || i < b)
        return;

    // We are at index i
    // রিলেভেন্ট সেগমেন্ট
    if (b >= i && e <= i) { 
        tree[node] = newvalue;
        return;
    }

    // আরো ভাঙতে হবে
    ll Left = node * 2; 
    ll Right = node * 2 + 1;
    ll mid = (b + e) / 2;

    update(Left, b, mid, i, newvalue);
    update(Right, mid + 1, e, i, newvalue);

    tree[node] = tree[Left] + tree[Right];
}

int seg_tree_main() {
    ll n;
    cin >> n;
    For (i, 1, n+1) cin >> arr[i];
    init(1, 1, n);
    update(1, 1, n, 2, 0);
    cout << query(1, 1, n, 1, 3) << endl;
    update(1, 1, n, 2, 2);
    cout << query(1, 1, n, 2, 2) << endl;
    return 0;
}

// [026] Upper Bound and Lower Bound

Iterator lower_bound (Iterator first, Iterator last, const val)
Iterator upper_bound (Iterator first, Iterator last, const val)
 
// lower_bound returns an iterator pointing to the first element in the range [first,last) 
// which has a value not less than (greater than or equal) ‘val’.
 
// upper_bound returns an iterator pointing to the first element in the range [first,last) 
// which has a value greater than ‘val’.

// For lower_bound():
//     Intialise the startIndex as 0 and endIndex as N – 1.
//     Compare K with the middle element(say arr[mid]) of the array.
//     If the middle element is greater equals to K then update the endIndex as middle index (mid).
//     Else Update startIndex as mid + 1.
//     Repeat the above steps untill startIndex is less than endIndex.
//     After all the above steps the startIndex is the lower_bound of K in the given array.
// For upper_bound():
//     Intialise the startIndex as 0 and endIndex as N – 1.
//     Compare K with the middle element(say arr[mid]) of the array.
//     If the middle element is less than equals to K then update the startIndex as middle index + 1 (mid + 1).
//     Else Update endIndex as mid.
//     Repeat the above steps untill startIndex is less than endIndex.
//     After all the above steps the startIndex is the upper_bound of K in the given array.

// C program for iterative implementation 
// of the above approach 
  
// Function to implement lower_bound 
int lower_bound(int arr[], int N, int X) { 
    int mid; 
  
    // Initialise starting index and 
    // ending index 
    int low = 0; 
    int high = N; 
  
    // Till low is less than high 
    while (low < high) { 
        mid = low + (high - low) / 2; 
  
        // If X is less than or equal 
        // to arr[mid], then find in 
        // left subarray 
        if (X <= arr[mid]) { 
            high = mid; 
        } 
  
        // If X is greater arr[mid] 
        // then find in right subarray 
        else { 
            low = mid + 1; 
        } 
    } 
  
    // Return the lower_bound index 
    return low; 
} 
  
// Function to implement upper_bound 
int upper_bound(int arr[], int N, int X) { 
    int mid; 
  
    // Initialise starting index and 
    // ending index 
    int low = 0; 
    int high = N; 
  
    // Till low is less than high 
    while (low < high) { 
        // Find the middle index 
        mid = low + (high - low) / 2; 
  
        // If X is greater than or equal 
        // to arr[mid] then find 
        // in right subarray 
        if (X >= arr[mid]) { 
            low = mid + 1; 
        } 
  
        // If X is less than arr[mid] 
        // then find in left subarray 
        else { 
            high = mid; 
        } 
    } 
  
    // Return the upper_bound index 
    return low; 
} 
  
// Function to implement lower_bound 
// and upper_bound of X 
void printBound(int arr[], int N, int X) { 
    int idx; 
  
    // If lower_bound doesn't exists 
    if (lower_bound(arr, N, X) == N) { 
        printf("Lower bound doesn't exist"); 
    } 
    else { 
        // Find lower_bound 
        idx = lower_bound(arr, N, X); 
        printf("Lower bound of %d is"
               "% d at index % d\n ", 
               X, 
               arr[idx], idx); 
    } 
  
    // If upper_bound doesn't exists 
    if (upper_bound(arr, N, X) == N) { 
        printf("Upper bound doesn't exist"); 
    } 
    else { 
  
        // Find upper_bound 
        idx = upper_bound(arr, N, X); 
        printf("Upper bound of %d is"
               "% d at index % d\n ", 
               X, 
               arr[idx], idx); 
    } 
} 
  
// Driver Code 
int in_upper_lower_bound_main() 
{ 
    // Given array 
    int arr[] = { 4, 6, 10, 12, 18, 20 }; 
    int N = sizeof(arr) / sizeof(arr[0]); 
  
    // Element whose lower bound and 
    // upper bound to be found 
    int X = 6; 
  
    // Function Call 
    printBound(arr, N, X); 
    return 0; 
} 

// [027] LCA: Lowest Common Ancestor
// See Shafayet Blog for detail: http://www.shafaetsplanet.com/?p=1831
// https://ideone.com/LK6jk0

vector<ll> adj_list[200005];
ll level[200005];
ll dadNode[200005]; // First parents
ll sparseTable[200005][23]; // To store 2^j-th parent of node i in (i, j) // log(200005)=17.6(<22)

void dfs(ll dad, ll son) {
    if (dad == -1) {
        level[son] = 0;
        dadNode[son] = dad;
    }
    else {
        level[son] = level[dad] + 1;
        dadNode[son] = dad;
    }

    printf("In ndoe %lld\n", son);

    for (ll grandson : adj_list[son]) {
        if (grandson == dad) {
            continue;
        }
        dfs(son, grandson);
    }
}

void initSparseTable() {
    memset(sparseTable, -1, sizeof(sparseTable));

    // Fill the table column by column
    for (ll j = 0; (1<<j) <= 200005; j++) {
        for (ll i = 1; i <= 23; i++) {
            if (j == 0) 
                sparseTable[i][j] = dadNode[i];
            else if (sparseTable[i][j-1] != -1)
                sparseTable[i][j] = sparseTable[sparseTable[i][j-1]][j-1];
        }
    }
}

ll lcaQuery(ll p, ll q) {
    // Assuming p is in deeper level than q
    if (level[p] < level[q]) swap(p, q);

    ll logVal = 1;
    while (true) {
        ll nextCandidate = logVal+1;
        if ((1 << nextCandidate) > level[p]) break;
        logVal++;
    }
    
    // Making levels the same
    for (ll i = logVal; i >= 0; i--) {
        if (level[p]-(1<<i) >= level[q]) {
            p = sparseTable[p][i];
        }
    }

    if (p == q) {
        return p;
    }

    // Moving the levels up at the same rate
    for (ll i = logVal; i >= 0; i--) {
        if (sparseTable[p][i] != -1 && sparseTable[p][i] != sparseTable[q][i]) {
            p = sparseTable[p][i];
            q = sparseTable[q][i];
        }
    }

    return dadNode[p];
}

int main() {
    ll n, nQueries;
    cin >> n >> nQueries;
    for (ll i = 0; i <= n; i++) {
        adj_list[i].clear();
        level[i] = -1;
        dadNode[i] = -1;
    }
    for (ll i = 1; i <= n-1; i++) {
        ll u, v;
        cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(-1, 1);
    for (ll i = 1; i <= n; i++) 
        printf(i == n ? "%lld\n" : "%lld ", level[i]);
    for (ll i = 1; i <= n; i++) 
        printf(i == n ? "%lld\n" : "%lld ", dadNode[i]);

    initSparseTable();
    for (ll i = 0; i <= n; i++) 
        for (ll j = 0; j <= 10; j++) 
            printf(j == 10 ? "%lld\n" : "%lld ", sparseTable[i][j]);
        printf("\n");

    while (nQueries--) {
        ll u, v;
        cin >> u >> v;
        ll lca = lcaQuery(u, v);
        cout << "LCA of " << u << " and " << v << " : " << lca << endl;
    }
}

// [028] Disjoint Set Union (DSU)

ll parent[100009], ranks[100009];

void initialize_nodes_till(ll limit) {
    for (ll i = 0; i <= limit; i++) {
        parent[i] = i;
        ranks[i] = 1;
    }
}

ll find_parent_and_compress(ll node) {
    if (parent[node] == node) return node;
    return parent[node] = find_parent_and_compress(parent[node]);
}

ll make_friendship_and_kount_friends_in_circle(ll node1, ll node2) {
    ll u = find_parent_and_compress(node1);
    ll v = find_parent_and_compress(node2);

    if (u == v) return ranks[u];

    if (ranks[u] > ranks[v]) {
        parent[v] = u;
        ranks[u] += ranks[v];
        return ranks[u];;
    }
    else {
        parent[u] = v;
        ranks[v] += ranks[u];
        return ranks[v];
    }
}

// [029] Merge Sort (n log n)

void merge_sort(ll* ara, ll lo, ll hi) {
    if (lo == hi) {
        return;
    }

    ll mid = lo + ((hi - lo) / 2);
    merge_sort(ara, lo, mid);
    merge_sort(ara, mid+1, hi);

    ll i, j, k, kk, temp[hi-lo+1];

    for (i = lo, j = mid+1, k = 0, kk = lo; kk <= hi; k++, kk++) {
        if (i == mid+1) {
            temp[k] = ara[j];
            j++;
        }
        else if (j == hi+1) {
            temp[k] = ara[i];
            i++;
        }
        else if (ara[i] <= ara[j]) {
            temp[k] = ara[i];
            i++;
        }
        else {
            temp[k] = ara[j];
            j++;
        }
    }

    for (kk = lo, k = 0; kk <= hi; kk++, k++) {
        ara[kk] = temp[k];
    }
}

// [030] Queue Using Stack

class MyQueue {
    // Queue Using Stack
public:
    /** Initialize your data structure here. */
    stack<int> queueStack;
    stack<int> temp;

    MyQueue() {
        while (!queueStack.empty()) queueStack.pop();
        while (!temp.empty()) temp.pop();
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        while (!temp.empty()) temp.pop();
        while (!queueStack.empty()) {
            int element = queueStack.top();
            temp.push(element);
            queueStack.pop();
        }
        queueStack.push(x);
        while (!temp.empty()) {
            int element = temp.top();
            queueStack.push(element);
            temp.pop();
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int element = queueStack.top();
        queueStack.pop();
        return element;
    }
    
    /** Get the front element. */
    int peek() {
        int element = queueStack.top();
        return element;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return queueStack.empty();
    }
};

// [031] Build a Balanced Binary Tree From a Sorted Array

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    TreeNode* go(vector<int>& nums, int start, int stop) {
        if (start > stop) {
            return nullptr;
        }

        int mid = start + (stop - start) / 2;

        TreeNode* node = new TreeNode(nums[mid]);
        node->left = go(nums, start, mid-1);
        node->right = go(nums, mid+1, stop);

        return node;
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return go(nums, 0, nums.size()-1);
    }
};

// [032] Reversing a Linked List

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* newHead = head;

        while (curr) {
            ListNode* toGo = curr->next; // Next Node of the current linked list

            curr->next = prev; // move the edge in opposite direction
            prev = curr; // will be the 'next' of the next node of current linked list
            newHead = curr; // new linked list will start from here, if there is no node ahead in the current linked list

            curr = toGo;
        }   

        return newHead;
    }
};

// [033] 2D Line Sweeping (Requires 1D Line Sweeping) [LC Rectangle Area II]

class Solution {
public:
    long long int mod = 1000000007;
    struct vertical_line {
        long long int x;
        long long int type;
        long long int y1;
        long long int y2;
    };

    vertical_line* ara;

    void init_lines(long long int size) {
        ara = new vertical_line[3*size];
    }

    static bool compare(vertical_line v1, vertical_line v2) {
        return v1.x < v2.x;
    }

    int rectangleArea(vector<vector<int>>& rectangles) {
        init_lines(rectangles.size());

        long long int index = 0;

        for (long long int i = 0; i < rectangles.size(); i++) {
            long long int x1 = (long long int) rectangles[i][0];
            long long int y1 = (long long int) rectangles[i][1];
            long long int x2 = (long long int) rectangles[i][2];
            long long int y2 = (long long int) rectangles[i][3];

            ara[index].x = x1;
            ara[index].type = 0;
            ara[index].y1 = y1;
            ara[index].y2 = y2;
            index++;

            ara[index].x = x2;
            ara[index].type = 1;
            ara[index].y1 = y1;
            ara[index].y2 = y2;
            index++;
        }

        sort(ara, ara+index, compare);

        multiset<pair<long long int, long long int>> ys;
        ys.clear();

        long long int prev_x;
        long long int ans = 0;

        for (long long int i = 0; i < index; i++) {
            if (ys.size()) {
                long long int totalHeightHere = 0;

                long long int startVal = -1;
                long long int stopVal = -1;

                for (pair<long long int, long long int> ypair : ys) {

                    if (stopVal < ypair.first) {
                        // a new segment
                        totalHeightHere += (stopVal-startVal);
                        startVal = ypair.first;
                        stopVal = ypair.second;
                    }
                    else {
                        stopVal = max(stopVal, ypair.second);
                    }
                }
                totalHeightHere += (stopVal-startVal);

                long long int addhere = (((ara[i].x-prev_x)%mod)*(totalHeightHere%mod))%mod;
                ans = ((ans%mod)+(addhere%mod))%mod;
            }

            if (ara[i].type == 0) {
                ys.insert({ara[i].y1, ara[i].y2});
            }
            else {
                ys.erase(ys.find({ara[i].y1, ara[i].y2}));
            }

            prev_x = ara[i].x;
        }

        return (int) ans%mod;
    }
};

// [034] Trie

class Trie {
    struct node {
        bool endsHere;
        node* child[26];

        node() {
            endsHere = false;
            for (int i = 0; i < 26; i++) {
                child[i] = nullptr;
            }
        }
    };

    node* root;
public:
    Trie() {
        root = new node();
    }
    
    void insert(string word) {
        node* curr = root;

        for (int i = 0; i < word.size(); i++) {
            if (curr->child[word[i]-'a'] == nullptr) {
                curr->child[word[i]-'a'] = new node();
            }

            curr = curr->child[word[i]-'a'];
        }

        curr->endsHere = true;
    }
    
    bool search(string word) {
        node* curr = root;

        for (int i = 0; i < word.size(); i++) {
            if (curr->child[word[i]-'a'] == nullptr) return false;
            curr = curr->child[word[i]-'a'];
        }

        return curr->endsHere;
    }
    
    bool startsWith(string prefix) {
        node* curr = root;
        
        for (int i = 0; i < prefix.size(); i++) {
            if (curr->child[prefix[i]-'a'] == nullptr) return false;
            curr = curr->child[prefix[i]-'a'];
        }

        return true;
    }
};

// [035] Find All Subsets (Power Set) | Bit Mask | O(n*2^n)

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> all_subsets;

    int arrayLength = nums.size();
    int nSubsets = 1 << arrayLength;

    for (int i = 0; i < nSubsets; i++) {
        vector<int> a_subset;
        for (int j = 0; j < arrayLength; j++) {
            if (i & (1<<j)) {
                a_subset.push_back(nums[j]);
            }
        }
        all_subsets.push_back(a_subset);
    }

    return all_subsets;
}

// [036.01] Find the Next Greater Element | Monotone Stack | O(n)

void nextGreaterElement(vector<int>& nums) {
    // the index to the next greater element of the element at index i is stored here, initially -1
    int nextGreaterIndex[nums.size()];
    for (int i = 0; i < nums.size(); i++) nextGreaterIndex[i] = -1;

    stack<int> st;

    for (int i = 0; i < nums.size(); i++) {
        if (st.empty()) {
            // if the stack is empty, then no current element is waiting for the next greater
            // just push the index so that any next greater can be inserted as the next greater of this element, later
            st.push(i);
            continue;
        }

        while ((not st.empty()) and (nums[i] > nums[st.top()])) {
            // if the current element is greater than the top element at the index at the top of the stack 
            // then the next greater of the top index element is the current element 
            nextGreaterIndex[st.top()] = i;
            st.pop();
        }

        // push the current index for finding its next greater further
        st.push(i);
    }

    for (int i = 0; i < nums.size(); i++) {
        cout << i << " " << nums[i] << " -> " << nums[nextGreaterIndex[i]] << endl;
    }
}

// [036.02] Find the Maximum Area of a Histogram | Monotone Stack | O(n)

// Ref: Tushar Roy's Video: https://youtu.be/ZmnqCZp9bBs
// Ref: Tushar Roy's Code: https://github.com/mission-peace/interview/blob/master/src/com/interview/stackqueue/MaximumHistogram.java

// Time Complexity: O(N) --> Each element is visited maximum twice (Once pushed in stack and once popped for stack)
// Spact Complexity: O(N) --> At most n elemnts can be in the stack at once

int largestRectangleArea(vector<int>& heights) {
    int maxArea = 0;

    heights.push_back(0);

    stack<int> st;

    for (int i = 0; i < heights.size(); i++) {
        if (st.empty()) {
            st.push(i);
            continue;
        }

        while ((not st.empty()) and heights[i] < heights[st.top()]) {
            int width = heights[st.top()];
            st.pop();

            int length;
            // if stack is empty means everything till i has to be greater or equal to input[top]
            // if stack is not empty then everythin from st.top()+1 to i-1 have to be greater or equal to input[top]
            if (st.empty()) length = i;
            else length = i-st.top()-1;

            int area = width*length;

            maxArea = max(maxArea, area);
        }

        st.push(i);
    }

    return maxArea;
}

// [037] Catalan Number/Count The Number of unique BST with n values
// Problem: https://leetcode.com/problems/unique-binary-search-trees/
// Solution: https://youtu.be/YDf982Lb84o

class Solution {
public:
    int numTrees(int n) {
        int dp[n+1];
        memset(dp, 0, sizeof(dp));

        dp[0] = 1; // with 0 val, we can form a empty tree
        dp[1] = 1; // with 1 val, we can form only one tree

        for (int i = 2; i <= n; i++) {
            // if we have i vals, how many unique trees could we build
            for (int j = 0; j < i; j++) {
                // use j-th val as root
                dp[i] += dp[j]*dp[i-j-1];
            }
        }

        return dp[n];
    }
};

// [038] Sliding Window Technique
// LC 438: https://leetcode.com/problems/find-all-anagrams-in-a-string/

vector<int> findAnagrams(string s, string p) {
    vector<int> freq_p(26, 0);
    vector<int> window(26, 0);
    vector<int> ans;
    ans.clear();

    if (s.length() < p.length()) return ans;
    
    for (int i = 0; i < p.length(); i++) {
        freq_p[p[i]-'a']++;
        window[s[i]-'a']++;
    }
    if (freq_p == window) ans.push_back(0);
    
    for(int i = p.length(); i < s.length(); i++){
        window[s[i-p.length()]-'a']--;
        window[s[i]-'a']++;
        
        if (freq_p == window) ans.push_back(i-p.length()+1);
    }

    return ans;
}

// [039] Moore's algorithm: Maximum Occuring Element at O(1) Space | LeetCode 169

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int kount = 0, res = 0;

        for (int num : nums) {
            if (kount == 0) {
                res = num;
            }

            if (num == res) {
                kount++;
            }
            else {
                kount--;
            }
        }

        return res;
    }
};


// [040] LeetCode 287: Slow Fast Algorithm to find duplicate | O(n), no extra space and modification in the main array
// Learn: https://www.youtube.com/watch?v=32Ll35mhWg0

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;

        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];

            if (slow == fast) break;
        }

        fast = 0;

        while (true) {
            slow = nums[slow];
            fast = nums[fast];

            if (slow == fast) break;
        }

        return slow; 
    }
};

// [041] Binary Search on Answer Range
// LeetCode 410. Split Array Largest Sum

class Solution {
    int isPossible(vector<int>& nums, int mid) {
        // Kounts how many subarrays are possible in nums with sum less than or equal mid

        int kount = 0;
        int tempsum = 0;

        for (int i = 0; i < nums.size(); i++) {
            if (tempsum+nums[i] <= mid) {
                tempsum += nums[i];
            }
            else {
                kount++;
                tempsum = nums[i];
            }
        }
        kount++; // The last subsequnece

        return kount;
    }
public:
    int splitArray(vector<int>& nums, int m) {

        int lo = 0;
        int hi = 0;

        for (int i = 0; i < nums.size(); i++) {
            lo = max(lo, nums[i]);
            hi += nums[i];
        }

        int mid = 0;
        int ans = 0;

        while (lo <= hi) {
            mid = (lo+hi)/2;

            int kountOfSegment = isPossible(nums, mid);

            if (kountOfSegment <= m) {
                ans = mid;
                hi = mid-1;
            }
            else {
                lo = mid+1;
            }
        }

        return ans;
    }
};

// [042] First Missing Positive | MEX: Minimum Excluded | LeetCode XXX

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size(); 
        // MEX will be 1 to n+1
        // 1, if 1 is missing, n+1, if all number from 1 to n is present
        // Here, as the array size is n, all number from 1 to n will appear only once 
        // So the numbers in the array in range [1, n] will be considered, others will be discarded
        // Make all the out of range [1, n] values 1
        // But before making them 1, think that, 1 might be the MEX, which will loose after adding 1
        // So check if MEX is 1 at the very beginning

        bool isMEXOne = true;
        for (int num : nums) {
            if (num == 1) isMEXOne = false;
        }

        if (isMEXOne) {
            return 1;
        }

        // Now make all the numbers out of [1,n] equal to 1
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 1 and nums[i] <= n) {
                // No need to change
            }
            else {
                nums[i] = 1;
            }
        }

        for (int num : nums) {
            // Make the number at index equal to an existing number negative
            // index-1 will be modified as we have array index 0 to n-1
            if (nums[abs(num)-1] > 0) {
                // Checked if still positive
                // already negative means already exisiting element for this index, hence got negated
                nums[abs(num)-1] *= -1;
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] >= 1) {
                // At this index, the number did not negated, hence no existing number equal to index
                return i+1;
            }
        }

        return n+1;
    }
};

void solve() {
    printf("This is a test case.\n");
} 
 
int32_t main() {
    test = 1;
    scl(test);
    while (test--) solve();
}
