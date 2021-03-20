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

ll t, test, temp;
ll n, m, k, kount;
ll a, b, c, ans, u, v;
ll x, y, z = -1, maxi, mini;

ll ara[maxn];
string str;

// Fibonacci Freeze

// [how many fibonacci numbers][how many digits can be at max]
int fib[5005][1200]; 

void make_fib(){
    fib[0][0] = 0;
    fib[1][0] = 1;

    // In the matrix, LSB at left most position
    for(ll i = 2; i < 5005; i++){
        for(ll j = 0; j < 1200; j++){

            fib[i][j] += fib[i-1][j] + fib[i-2][j];

	        if(fib[i][j] > 9){
                fib[i][j+1] += fib[i][j] / 10;
                fib[i][j] %= 10;
            }

        }
    }
}


// GCD

ll gcd(ll a, ll b){
    if(a % b == 0) return b;
    return gcd(b, a%b);
}


// Trailing 0s of n!

ll zerosinfact(ll n){
    ll ret = 0;
    for(ll i = 5; i <= n; i *= 5){
        ret += (n/i);
    }
    //Also count 2s if required
    return ret;
}

// Bigmod, Inverse Mod, Factorial, nCk

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
}

// Sieve Techniques

// Sieve 1

ll prime[sqrt(maxn)+10];
bool mark[maxn] = {false};

void sieve1(){
    prime[0] = 2;
    ll index = 1;

    for(ll i = 3; i*i <= maxn; i += 2){
        if(mark[i] == false){
            for(ll j = i*i; j <= maxn; j += i+i){
                mark[j] = true;
            }
        }
    }

    for(ll i = 3; i <= maxn && index < (ll)sqrt(maxn)+10; i += 2){
        if(mark[i] == false) prime[index++] = i;
    }
}

// Sieve 2

vector<ll> pr;

void ektuonnorokom(){
	for(ll i = 2; i < 86028157; i++){
		if(mark[i] == false) pr.pb(i);
		for(ll j = 0; j < pr.size() && pr[j]*i <= 86028157; j++){
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

// Prime Divisor Kount

ll mark[maxn]; // number upper limit
// [r_i][till this number] = how many r_i prime factors holder occured till this number
ll cumkount[11][maxn]; 
void sieve_cumkount(){
	for (ll i = 2; i <= maxn; i += 2) mark[i]++;
	for (ll i = 3; i <= maxn; i += 2) {
		if (mark[i] == 0) {
			for(ll j = i; j <= maxn; j += i) mark[j]++;
        }
    }
	for(ll i = 0; i < 11; i++){
		for(ll j = 1; j <= maxn; j++){
			if(mark[j] == i) cumkount[i][j] = cumkount[i][j-1] + 1;
			else cumkount[i][j] = cumkount[i][j-1];
		}
	}
}

// Prime Factors

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


// nCr DP
ll dp[100][100];

ll find_nCr(ll n, ll r) {
    if(r == n) return 1LL;
    if(r == 1) return n;

    ll &ret = dp[n][r];
    if(ret != -1) return ret;

    ret = find_nCr(n-1, r) + find_nCr(n-1, r-1);

    return ret;
}

// Knapsac DP [UVa 10130]

ll weight[1010], cost[1010], dp[1010][40];
ll number_of_items, capacity;

ll knapsac(ll i, ll w) {
    if(i >= number_of_items) return 0LL;
    if(dp[i][w] != -1) return dp[i][w];

    ll profit1 = 0, profit2 = 0;

    if(w + weight[i] <= capacity){
        profit1 = cost[i] + knapsac(i+1, w+weight[i]);
    }

    profit2 = knapsac(i+1, w);

    dp[i][w] = max(profit1, profit2);

    return dp[i][w];
}

// Coin Change DP (without setting memory for every query)

// Coin values
ll coins[] = {50, 25, 10, 5, 1};
ll make; // target amount
ll dp[6][8000];

ll call(ll i, ll amount){
    if (i >= 5){
        if (amount == 0LL) return 1LL;
        else return 0LL;
    }

    ll& ret = dp[i][amount];
    if(ret != -1) return ret;

    ll ret1 = 0LL, ret2 = 0LL;

    if (amount - coins[i] >= 0) 
        ret1 = call(i, amount - coins[i]);
    ret2 = call(i+1, amount);

    return ret = ret1 + ret2;
}

int in_main_for_calling(){
    memset(dp, -1, sizeof(dp));

    while(scanf("%lld", &make) == 1LL)
        printf("%lld\n", call(0, make));
}

// Coin Change DP (with limited number of coins) [LOJ 1231]

int val[56], permit[56], memtab[56][1024], n, make;

ll explore(ll i, ll amount){
    if(amount == make) return 1LL;
    if(i == n) return 0LL;

    if(memtab[i][amount] != -1) return memtab[i][amount];

    ll ret = 0;

    for(ll xx = 0; xx <= permit[i] && amount+val[i]*xx <= make; xx++){
        ret += explore(i+1, amount+val[i]*xx);
        ret %= mod;
    }

    return memtab[i][amount] = ret;
}

// Bitwise Operations

ll setBit(ll N, ll pos) {return N = N | (1LL<<pos);}
ll resetBit(ll N, ll pos) {return N = N & ~(1<<pos);}
bool checkBit (ll N, ll pos) {return (bool)(N & (1<<pos));}

// LIS with solution print

ll value[] = {-200, -100, 5, 0, 9, 2, 7, 3, 4};
ll n = sizeof(value) / sizeof(ll);
ll dp[maxn];
ll dir[maxn];

ll longestfrom(ll u){

    if(dp[u] != -1LL) return dp[u];

    ll maxlen = 0;
    for(int v = u+1; v < n; v++){
        if(value[v] > value[u]){
            if(longestfrom(v) > maxlen){
                maxlen = longestfrom(v);
                dir[u] = v;
            }
        }
    }

    return dp[u] = 1+maxlen;
}

int at_main_LIS(){
    memset(dp, -1, sizeof(dp));
    memset(dir, -1, sizeof(dir));

    ll start, LIS_len = 0;

    for(ll i = 0; i < n; i++){
        if(longestfrom(i) > LIS_len){
            LIS_len = longestfrom(i);
            start = i;
        }
    }

    cout << "Length of LIS: " << LIS_len << endl;
    ll curr = start;

    while(1){
        cout << value[curr] << " ";
        curr = dir[curr];
        if(dir[curr] == -1){
            cout << value[curr] << " ";
            break;
        }
    }
}

// Longest Common Subsequence

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


// Subset Sum Table (UVa 624)

ll tracks[26]; // Set of numbers
ll mat[26][100005]; //[num_of_elements_in_set][target_subset_sum]
ll total_length, number_of_tracks;

ll makematrix(){
    for(ll i = 0; i <= number_of_tracks; i++){
        for(ll j = 0; j <= total_length; j++){
            if(i == 0 || j == 0) mat[i][j] = 0;
            else if(j < tracks[i]) mat[i][j] = mat[i-1][j];
            else mat[i][j] = max(mat[i-1][j], tracks[i] + mat[i-1][j-tracks[i]]);
        }
    }
    return mat[number_of_tracks][total_length];
}

void traverse_print(){
    ll taken[26], index = 0;
    ll xp = number_of_tracks, yp = total_length;
    while(1){
        if(xp == 0 || yp == 0) break;
        else if(mat[xp-1][yp] == mat[xp][yp]) xp--;
        else{
            taken[index++] = tracks[xp];
            yp -= tracks[xp];
            xp--;
        }
    }
    for(ll i = index-1; i >= 0; i--) printf("%d ", taken[i]);
}

// 8 Queen Problem 

// Will store the position of row for each column where any queen exist safely
int position[10];

// for counting how many combinations exist
int kount = 0;

bool isSafe(int ro, int col){
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

void call(int col){

    if (col == 9) {
        /// Eight queens are already placed safely for a combination!
        /// Dam da dam da dam!
        /// Print this!

        for(int i = 1; i <= 8; i++){
            if(i == 1) cout << "{ " << position[i] << ", ";
            else if (i == 8) cout << position[i] << " },\n";
            else cout  << position[i] << ", ";
        }

        kount++; /// A new combination found.

        return;

    }

    /// Traverse all rows and see if that row is safe for that column
    for (int i = 1; i <= 8; i++) {
        if(isSafe(i, col)) {
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

// Longest Path using BFS

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

        for(it = adj_list[u].begin(); it != adj_list[u].end(); it++){
            ll v = *it;
            // Make the level as much as possible to make the path longer
            if (level[v] < level[u]+1) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
}

//Constructing priority queue

// এখানে arg কে প্রায়োরিটি কিউতে টপে রাখা হবে। 
// arg এর লেংথ বেশি হলে প্রায়োরিটি পাবে।
// সমান লেংথ হলে লেফটে থাকলে প্রায়োরিটি পাবে।
// arg should be at the top of priority queue
// arg, to be prioritised-
// -> length of arg should be greater 
// -> In case of length tie, arg should be at left

struct info{
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

// 
























