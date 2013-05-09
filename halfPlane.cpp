/**
* poj 1279 ok
* poj 1474 ok
* poj 3335 ok
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace std;

#define debug(x) cout<<#x<<"="<<x<<endl

const double INF = 1e100;
const double eps = 1e-8;
const double PI = acos(-1.0);

const int N = 1511;

struct Point {
        double x, y;
        Point () {}
        Point (double _x, double _y) {
                set(_x, _y);
        }
        void set(double _x, double _y) {
                x = _x, y = _y;
        }
        void read() {
                scanf("%lf%lf",&x, &y);
        }
        void write() {
                printf("(%lf %lf)\n", x, y);
        }
        Point operator + (Point p) const {
                return Point(x + p.x, y + p.y);
        }
        Point operator - (Point p) const {
                return Point(x - p.x, y - p.y);
        }
        Point operator * (double t) const {
                return Point( x*t, y*t );
        }
        Point operator / (double t) const {
                return Point( x/t, y/t );
        }
        bool operator == (Point p) const {
                return fabs(x - p.x) < eps && fabs(y - p.y) < eps;
        }
}O(0, 0);

double cross(Point a, Point b) {
        return a.x * b.y - a.y * b.x;
}

double cross(Point a, Point b, Point c) {
        return cross(a-c, b-c);
}

double abs(Point a) {
        return sqrt( a.x*a.x + a.y*a.y );
}

int sign(double t) {
        return t<-eps?-1:t>eps;
}

Point isSS (Point a, Point b, Point c, Point d) {
        double e = cross(a, b, c), f = -cross(a, b, d);
        return ( c*f + d*e )/(f+e);
}

struct Border {
        Point a, b;
        double ang;
        Border () {}
        Border (Point _a, Point _b) {
                set(_a, _b);
        }
        void set(Point _a, Point _b) {
                a = _a, b = _b;
                ang = atan2(b.y - a.y, b.x - a.x);
        }
        bool out(Point p) const {
                return sign (cross(a, b, p)) < 0;
        }
        bool operator < (const Border &c) const {
                if ( sign(ang - c.ang) )
                        return ang < c.ang;
                return out(c.a);
        }
        bool operator == (const Border &c) const {
                return fabs(ang - c.ang) < eps;
        }
        void write() {
                a.write();
                b.write();
                debug(ang);
                cout << endl;
        }
};

Point isSS(Border a, Border b) {
        return isSS(a.a, a.b, b.a, b.b);
}

Point hp[N];
int halfPlane(Point p[], int n) {
        static Border b[N], q[N];
        p[n] = p[0];
        for(int i=0;i<n;++i)
                b[i].set(p[i], p[i+1]);
        sort(b, b+n); int m = unique(b, b+n) - b;
        int l = 0, r = 0;
        for(int i=0;i<m;++i) {
                // 本来这里写的 l+2<r
                while( l+1<r && b[i].out( isSS(q[r-1], q[r-2]) ) )
                        r --;
                while( l+1<r && b[i].out( isSS(q[l], q[l+1]) ) )
                        l ++;
                q[r++] = b[i];
        }
        while( l+2 < r && q[l].out( isSS(q[r-1], q[r-2]) ) )
                r--;
        // 为什么是必要的
        //while( l+2 < r && q[r-1].out( isSS(q[l], q[l+1]) ) )
        //        l++;
        q[r++] = q[l];
        int tot = 0;
        for(int i=l;i<r-1;++i)
                hp[tot++] = isSS( q[i], q[i+1] );
        return tot;
}

double getArea(Point p[], int n) {
        if(n < 3)
                return 0;
        p[n] = p[0];
        double area = 0;
        for(int i=0;i<n;++i)
                area += cross(p[i], p[i+1]);
        return area / 2;
}
Point p[N];

int a[1111];

int main () {
        int T;
        scanf("%d", &T);
        while( T -- ) {
                int n;
                scanf("%d", &n);
                for(int i=0;i<n;++i)
                        p[i].read();
                if( getArea(p, n) < 0 )
                        reverse(p, p+n);
                int m = halfPlane(p, n);
                double ans = getArea(hp, m);
                if( m>=3 )
                        puts("YES");
                else
                        puts("NO");
        }
        return 0;
}
