#include <iostream>
#include <iomanip>
#include <cmath>
#define PI 3.141592653589793238462643383279

using namespace std;
double Sin(double x, double eps = 1e-5)
{
    double S = 0.;
    double N = 1.;
    double D = 2.;
    double edm = -1.;
    double ed = 1.;

    double pi2 = PI * 2;
    x = fmod(x, pi2);
    double P = x;

    double R;
    int sw;
    _asm {
        finit
        fld x
        fstp S
        FOR : fld N
        fmul D
        fst R
        fmul R
        fadd R
        fst R
        fld x
        fld x
        fmul
        fld edm
        fmul

        fdiv R
        fmul P
        fst P
        fadd S
        fstp S
        fld N
        fadd ed
        fstp N
        finit
        fld P
        fabs
        fld eps

        fcomi st(0), st(1)
        jna FOR
    }
    return S;
}

int main()
{
    cout << "teaylor:" << Sin(1000000000) << endl;
    cout << "math sin:" << sin(1000000000) << endl;
    cout << "error:" << 1 - Sin(1000000000) / sin(1000000000) << endl;
    cout << endl;

    cout << "teaylor:" << Sin(DBL_MIN) << endl;
    cout << "math sin:" << sin(DBL_MIN) << endl;
    cout << "error:" << 1 - Sin(DBL_MIN) / sin(DBL_MIN) << endl;
    cout << endl;

    cout << "teaylor:" << Sin(1.0) << endl;
    cout << "math sin:" << sin(1.0) << endl;
    cout << "error:" << 1 - Sin(1.0) / sin(1.0) << endl;
    cout << endl;

    cout << "teaylor:" << Sin(PI / 6) << endl;
    cout << "math sin:" << sin(PI / 6) << endl;
    cout << "error:" << 1 - Sin(PI / 6) / sin(PI / 6) << endl;
    cout << endl;

    cout << "teaylor:" << Sin(PI / 4) << endl;
    cout << "math sin:" << sin(PI / 4) << endl;
    cout << "error:" << 1 - Sin(PI / 4) / sin(PI / 4) << endl;
    cout << endl;

    cout << "teaylor:" << Sin(0.0) << endl;
    cout << "math sin:" << sin(0.0) << endl;
    cout << "error:" << 0<< endl;
    cout << endl;
    
    return 0;
}
/*
Sin(1000000000)
teaylor:0.545843
ideal:0.545843
error:-2.39346e-08

Sin(DBL_MIN)
teaylor:2.22507e-308
ideal:2.22507e-308
error:0

Sin(1.0)
teaylor:0.841471
ideal:0.841471
error:-2.95819e-08

Sin(PI/6)
teaylor:0.5
ideal:0.5
error:1.6262e-08

Sin(PI/4)
teaylor:0.707107
ideal:0.707107
error:-2.47533e-09

Sin(0.0)
teaylor:0
ideal:0
error:0

*/