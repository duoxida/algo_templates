#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 10010;
const double eps = 1e-8;
const double PI = acos(-1.0);
const double INF = 1e100;

int sign(double t) {
        return t < -eps ? -1 : t > eps;
}

struct Point {
        double x, y;
        Point() {}
        Point(double _x, double _y) {
                x = _x; y = _y;
        }
        void read() {
                scanf("%lf%lf",&x, &y);
        }
        void write() {
                printf("(%.2f %.2f)\n",x, y);
        }
        void set(double _x, double _y) {
                x = _x; y = _y;
        }
        Point operator - (Point p) {
                return Point(x - p.x, y - p.y);
        }
        Point operator + (Point p) {
                return Point(x + p.x, y + p.y);
        }
        Point operator * (double t) {
                return Point(x * t, y * t);
        }
        Point operator / (double t) {
                return Point(x / t, y / t);
        }
        double abs() {
                return sqrt(x * x + y * y);
        }
        double cross(Point p) {
                return x * p.y - y * p.x;
        }
        double dot(Point p) {
                return x * p.x + y * p.y;
        }
        double ang() {
                return atan2(y, x);
        }
        Point rot() {
                return Point(y, -x);
        }
}p[N], q[N], g[N];

double cross(Point &a, Point &b, Point &c) {
        return (c-b).cross(a-b);
}

bool cmp(Point a, Point b) {
        if(a.y == b.y)
                return a.x < b.x;
        return a.y < b.y;
}

void graham(Point p[], int n, Point set[], int &m) {
        sort(p, p+n, cmp); m = 0;
        for(int i=0;i<n;++i) {
                while( m >= 2 && sign( cross( set[m-2], set[m-1], p[i] ) ) <= 0 )
                        m --;
                set[m++] = p[i];
        } set[m++] = p[n-2];
        for(int i=n-3;i>=0;--i) {
                while( m >= 2 && sign( cross( set[m-2], set[m-1], p[i] ) ) <= 0 )
                        m --;
                set[m++] = p[i];
        } m--;
}

double PToL(Point a, Point b, Point c) {
        Point e = (b-c).rot();
        if( sign(e.cross(c-a)*e.cross(b-a)) <= 0 ) {
                return fabs( e.dot(c-a)/e.abs() );
        }
        return min( (b-a).abs(), (c-a).abs() );
}

double LToL(Point a, Point b, Point c, Point d) {
        if( (a-b).abs() < (c-d).abs() )
                return min( PToL(a, c, d), PToL(b, c, d) );
        return min( PToL(c, a, b), PToL(d, a, b) );
}

int main () {
        int n, m;
        while(scanf("%d%d",&n,&m) != EOF) {
                if(n == 0 && m == 0)
                        break;
                for(int i=0;i<n;++i) p[i].read();
                for(int i=0;i<m;++i) q[i].read();
                graham(p, n, g, n);
                for(int i=0;i<=n;++i) p[i] = g[i];
                graham(q, m, g, m);
                for(int i=0;i<=m;++i) q[i] = g[i];

                int pt = 0, qt = 0;
                for(int i=0;i<n;++i)
                if( sign(p[i].x - p[pt].x)==-1 || sign(p[i].x - p[pt].x)==0 && sign(p[i].y - p[pt].y)==-1 )
                        pt = i;
                for(int i=0;i<m;++i)
                if( sign(q[i].x - q[qt].x)==1 || sign(q[i].x - q[qt].x)==0 && sign(q[i].y - q[qt].y)==1 )
                        qt = i;
                double ans = INF;
                for(int i=pt, j=qt;;) {
                        int ang = sign( (q[j+1]-q[j]).cross(p[i+1]-p[i]) );
                        if(ang > 0) {
                                ans = min(ans, PToL(q[j], p[i], p[i+1]));
                                i++; if(i == n) i = 0;
                        }
                        else if(ang < 0) {
                                ans = min(ans, PToL(p[i], q[j], q[j+1]));
                                j++; if(j == m) j = 0;
                        }
                        else if(ang == 0) {
                                ans = min(ans, LToL(p[i], p[i+1], q[j], q[j+1]));
                                i++; if(i == n) i = 0;
                                j++; if(j == m) j = 0;
                        }
                        //cout << i << " " << j << endl;
                        if(i == pt && j == qt)
                                break;
                }
                printf("%.6f\n", ans);
        }
        return 0;
}
