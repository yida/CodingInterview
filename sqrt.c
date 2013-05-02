#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>

double SQRT2(const double num) {
    const double ACCURACY = 1e-6;
    double lower, upper, guess;
    if (num < 1) {
        lower = num;
        upper = 1;
    } else {
        lower = 1;
        upper = num;
    }
    while ((upper - lower) > ACCURACY) {
        guess = (lower + upper)/2;
        if (guess * guess > num)
            upper = guess;
        else
            lower = guess;
    }
    return (lower + upper) / 2;
}

/* newton approach */
double SQRT(const double num) {
    const double eps = 1e-6;
    double front_n = 1;
    double back_n = num;
    if (num < 1) {
        front_n = num;
        back_n = 1;
    }
    double mid_n = (front_n + back_n) / 2;
    while ((back_n - front_n) > eps) {
        mid_n = (back_n + front_n) / 2;
        if (mid_n * mid_n > num)
            back_n = mid_n;
        else
            front_n = mid_n;
    }
    return (front_n + back_n) / 2;
}

int main(void) {
//    double pi = 3.1415926;
    double pi = 1415926.432423423442;
    clock_t start, stop;
    start = clock();
    double ret = sqrt(pi);
    stop = clock();
    printf("%.20f %.15f\n", ret, (double)(stop - start) / CLOCKS_PER_SEC);
    
    start = clock();
    ret = SQRT(pi);
    stop = clock();
    printf("%.20f %.15f\n", ret, (double)(stop - start) / CLOCKS_PER_SEC);

    start = clock();
    ret = SQRT2(pi);
    stop = clock();
    printf("%.20f %.15f\n", ret, (double)(stop - start) / CLOCKS_PER_SEC);
 
    return 0;
}
