#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 1010;
const int M = 1010;
const int NN = N * 100;

#define DD(i,c) for(Node *i=c->D;i!=c;i=i->D)
#define RR(i,c) for(Node *i=c->R;i!=c;i=i->R)
#define UU(i,c) for(Node *i=c->U;i!=c;i=i->U)
#define LL(i,c) for(Node *i=c->L;i!=c;i=i->L)

struct Node {
        int i, j;
        Node *U, *D, *L, *R;
} mem[NN], Tnull, *null = &Tnull, *cur ;
Node *H[ N ], *C[ M ];
int SZ[ M ];

void remove(Node *c) {
        c->L->R = c->R;
        c->R->L = c->L;

        DD(i, c) RR(j, i) {
                        j->U->D = j->D;
                        j->D->U = j->U;
                        SZ[ j->j ] --;
        }
}

void resume(Node *c) {
        c->L->R = c->R->L = c;

        UU(i, c) LL(j, i) {
                        j->U->D = j->D->U = j;
                        SZ[ j->j ] ++;
        }
}


int ans;

void Dance(int k) {
        if(mem->R == mem) {
                ans ++;
                return ;
        }
        int sz = N; Node *c;
        RR(i, mem) {
                if(sz > SZ[i->j]) {
                        c = i;
                        sz = SZ[i->j];
                }
        }

        remove(c);
        DD(i, c) {
                RR(j, i)
                        remove(C[j->j]);
                Dance(k+1);
                if(ans > 1)
                        return;
                LL(j, i)
                        resume(C[j->j]);
        }
        resume(c);
}

void Link(int i, int j) {
        cur->i = i;
        cur->j = j;

        if( H[i] == null ) {
                H[i] = cur;
                cur->L = cur->R = cur;
        }
        else {
                cur->R = H[i]->R;
                H[i]->R = cur;
                cur->R->L = cur;
                cur->L = H[i];
        }

        if( C[j] == null ) {
                C[j] = cur;
                cur->U = cur->D = cur;
                SZ[j] = 0;
        }
        else {
                cur->D = C[j]->D;
                C[j]->D = cur;
                cur->D->U = cur;
                cur->U = C[j];
                SZ[j] ++;
        }

        cur ++;
}

void place(int i, int j, int k) {
        int x, y[4];
        x = (i*9 + j)*9 + k;
        y[0] = i*9 + j + 1;
        y[1] = 81 + i*9 + k;
        y[2] = 162 + j*9 + k;
        y[3] = 243 + (i/3*3+j/3)*9 + k;
        for(int t=0;t<4;++t)
                Link(x, y[t]);
}

int a[88];

void buildG() {
        cur = mem;
        int n = 729;
        int m = 324;
        ans = 0;
        fill(C, C+1+m, null);
        fill(H, H+1+n, null);

        Link(0, 0);
        for(int i=1;i<=m;++i) {
                Link(0, i);
        }

        for(int i=0;i<81;++i) {
                if(a[i]) {
                        place(i/9, i%9, a[i]);
                }
                else for(int j=1;j<=9;++j) {
                        place(i/9, i%9, j);
                }
        }
}

int main () {
        int T;
        cin >> T;
        while(T --) {
                for(int i=0;i<81;++i)
                        cin >> a[i];
                buildG();
                Dance(0);

                if(ans == 1) {
                        cout << "Yes" << endl;
                }
                else {
                        cout << "No" << endl;
                }
        }
        return 0;
}

