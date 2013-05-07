#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200100;

typedef long long LL;
const LL INF = 1LL<<60;

struct Node{
        Node *ch[2], *p;
        int sz;
        LL key, val, sum, muls;
        Node() {sz = 0;}
        bool d() {return p->ch[1] == this;}
        void setc(int d, Node *x){ch[d] = x; x->p = this;}
        void upd() {
                sz = ch[0]->sz + 1 + ch[1]->sz;
                sum = ch[0]->sum + val + ch[1]->sum;
                muls = ch[0]->muls + ch[0]->sz * val + ch[1]->muls + (ch[0]->sz + 1)*ch[1]->sum;
        }
}mem[MAX_N], Tnull, *null = &Tnull, *root, *cur = mem;
Node *newNode(LL key, LL val) {
        cur->sz = 1;
        cur->val = cur->sum = val;
        cur->key = key;
        cur->muls = 0;
        cur->ch[0] = cur->ch[1] = cur->p = null;
        return cur ++;
}
Node *rot(Node *x) {
        Node *y = x->p, *z = y->p;
        int d = x->d();
        z->setc(y->d(), x);
        y->setc(d, x->ch[!d]);
        x->setc(!d, y);
        y->upd();
        if(x->p == null)
                root = x;
}
void splay(Node *x, Node *f=null) {
        //while(x->p != f) rot(x); x->upd();
        while(x->p != f) {
                if(x->p->p != f)
                        x->d()==x->p->d()?rot(x->p):rot(x);
                rot(x);
        } x->upd();
}
void insert(Node *t) {
        Node *p = root;
        while(p->ch[ t->key > p->key ] != null) {
                p = p->ch[ t->key > p->key ];
        }
        p->setc(t->key > p->key, t);
        splay(t);
}
Node* next(Node *x, int d) {
        if(x->ch[d] == null) {
                while (x->d() == d)
                        x = x->p;
                return x->p;
        }
        Node *t = x->ch[d];
        while(t->ch[!d] != null)
                t = t->ch[!d];
        return t;
}
Node* find(LL K) {
        Node *x = root;
        while( 1 ) {
                if(x->key == K || x->ch[K > x->key] == null)
                        return x;
                x = x->ch[K > x->key];
        }
}
void erase(Node *x) {
        Node *l = next(x, 0); splay(l);
        Node *r = next(x, 1); splay(r, l);
        r->ch[0] = null; r->upd(); l->upd();
}

/* ----- Splay ----- */
int a[MAX_N], sa[MAX_N];
int n;
Node *build(int l, int r) {
        if(l > r)
                return null;
        int m = (l + r) >> 1;
        Node *x = newNode(sa[m], sa[m]);
        x->setc(0, build(l, m-1));
        x->setc(1, build(m+1, r));
        x->upd();
        return x;
}
void display(Node *x){
        if(x == null)return;
        display(x->ch[0]);
        cout << x->sz << " ";
        display(x->ch[1]);
}

int main() {
        cin >> n;
        for(int i=1;i<=n;++i) {
                cin >> a[i];
                sa[i] = a[i];
        }
        sort(sa+1, sa+1+n);
        root = build(1, n);
        insert(newNode(INF,0));
        insert(newNode(-INF,0));
        int m; cin >> m;
        while( m -- ) {
                LL c, l, r;
                cin >> c >> l >> r;
                if( c == 1 ) {
                        Node *t = find(a[l]);
                        erase(t);
                        insert(newNode(a[l]+r, a[l]+r));
                        a[l] += r;
                }
                else {
                        Node *x = find(l);
                        Node *y = find(r);
                        if(x->key >= l) x = next(x, 0);
                        if(y->key <= r) y = next(y, 1);
                        splay(x); splay(y, x);
                        Node *t = y->ch[0];
                        cout << 2 * t->muls - (t->sz-1) * t->sum << endl;
                }
        }
        return 0;
}
