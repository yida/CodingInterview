#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

/* big endian int 4324242342000  10e6:6 -> 1:0 */
/* negative 127->1, positive 127->0 */

void bigint_sum(char *Int1, char *Int2, char *sum);
void bigint_substract(char *Int1, char *Int2, char *sub);
void bigint_mul(char *Int1, char *Int2, char *mul);
void bigint_div(char *num, char *denom, char *div);
void bigint_mod(char *dividend, char *divisor, char *mod);

void double_2_bigint(char *Int, double num);
void string_2_bigint(char *Int, char * str);

int bigint_ge(char *Int1, char *Int2);
int bigint_le(char *Int1, char *Int2);
int bigint_eq(char *Int1, char *Int2);

void print_bigint(char *bigint);

const int int_max = 128;


/* large than  */
int bigint_ge(char *Int1, char *Int2) {
    int i = 0;
    /* Int1 is negative */
    if (Int1[int_max - 1] > Int2[int_max - 1])
        return 0;
    /* Int2 is negative */
    else if (Int2[int_max - 1] > Int1[int_max - 1])
        return 1;

    for (i = int_max - 2; i >= 0; i--)
        if (Int1[i] < Int2[i]) {
            printf("%d %d\n", Int1[i], Int2[i]);
            return 0;
        }
    return 1;
}

/* small than */
int bigint_le(char *Int1, char *Int2) {
    int i = 0;
    /* Int1 is negative */
    if (Int1[int_max - 1] > Int2[int_max - 1])
        return 1;
    /* Int2 is negative */
    else if (Int2[int_max - 1] > Int1[int_max - 1])
        return 0;

    for (i = int_max - 2; i >= 0; i--)
        if (Int1[i] > Int2[i]) {
            printf("%d %d\n", Int1[i], Int2[i]);
            return 0;
        }
    return 1;
}

int bigint_eq(char *Int1, char *Int2) {
    int i = 0;
    for (i = int_max - 1; i >= 0; i--)
        if (Int1[i] != Int2[i])
            return 0;
    return 1;
}


void bigint_div(char *num, char *denom, char *div) {
 
}

void bigint_mod(char *dividend, char *divisor, char *mod) {
}

void bigint_mul(char *Int1, char *Int2, char *mulp) {
    char *largep = NULL;
    char *smallp = NULL;
    int int1_len = int_max - 1;
    int int2_len = int_max - 1;
    int min_len = 0, max_len = 0;
    while (Int1[--int1_len]==0);
    while (Int2[--int2_len]==0);
    if (int1_len > int2_len) {
        largep = Int1;
        smallp = Int2;
        min_len = int2_len;
        max_len = int1_len;
    } else {
        largep = Int2;
        smallp = Int1;
        min_len = int1_len;
        max_len = int2_len;
    }
    int i = 0, j = 0;
    char mul = 0, carrier = 0;
    char *mul_buf = (char *)malloc(int_max * sizeof(char));
    memset(mul_buf, 0, int_max);
    char *sum_buf = (char *)malloc(int_max * sizeof(char));
    for (i = 0; i <= min_len; i++) {
        memset(sum_buf, 0, int_max);
        carrier = 0;
        mul = 0;
        for (j = 0; j <= max_len; j++) {
            mul = smallp[i] * largep[j] + carrier;
            carrier = mul / 10;
            mul = mul % 10;
            sum_buf[j + i] = mul;
        }
        sum_buf[max_len + i + 1] = carrier;
        bigint_sum(sum_buf, mul_buf, mul_buf);
    }
    memcpy(mulp, mul_buf, int_max);
    if (Int1[int_max - 1] ^ Int2[int_max - 1])
        mulp[int_max - 1] = -1;

    free(mul_buf);
    free(sum_buf);
}

void bigint_substract(char *Int1, char *Int2, char *sub) {
    char *minuend = Int1;
    char *subtrahend = (char *)malloc(int_max * sizeof(char));
    memcpy(subtrahend, Int2, int_max);
    subtrahend[int_max - 1] = 1 - subtrahend[int_max - 1];

    bigint_sum(minuend, subtrahend, sub);

    free(subtrahend);
}

void bigint_sum(char *Int1, char *Int2, char *sump) {
    char *largep = NULL;
    char *smallp = NULL;
    int i = 0;
    char * sum_buf = (char *)malloc(int_max * sizeof(char));
    memset(sum_buf, 0, int_max);

    int int1_len = int_max - 1;
    int int2_len = int_max - 1;
    int max_len = 0;
    while (Int1[--int1_len]==0);
    while (Int2[--int2_len]==0);
    if (int1_len > int2_len) {
        largep = Int1;
        smallp = Int2;
        max_len = int1_len;
    } else {
        largep = Int2;
        smallp = Int1;
        max_len = int2_len;
    }

    char sum = 0, carrier = 0, sub = 0;
    for (i = 0; i <= max_len; i++) {
        if (Int1[int_max - 1] ^ Int2[int_max - 1]) {
            /* not same sign */
            sub = largep[i] - smallp[i] - carrier;
            carrier = 0;
            if (sub < 0) {
                sub += 10;
                carrier = 1;
            }
            sum_buf[i] = sub;
        } else {
            /* same sign */
            sum = largep[i] + smallp[i] + carrier;
            carrier = sum / 10;
            sum -= carrier * 10;
            sum_buf[i] = sum;
        }
    }
    sum_buf[max_len + 1] = carrier;
    sum_buf[int_max - 1] = largep[int_max - 1];
    memcpy(sump, sum_buf, int_max);
    free(sum_buf);
}

void double_2_bigint(char *bigint, double num) {
    if (num < 0) {
        bigint[int_max - 1] = 1;
        num = -num;
    }
    int i = 0;
    double fractpart, intpart;
    fractpart = modf(num, &intpart);
    while (intpart > 10) {
        fractpart = modf(intpart / 10, &intpart);
        bigint[i++] = (char)round(fractpart * 10); 
    }
    bigint[i++] = (char)intpart;
}

void string_2_bigint(char *Int, char * str) {
    char * strp = str; 
    int str_len = strlen(str);
    if (*strp == '-') {
        Int[int_max - 1] = 1;
        strp ++;
    }
    int i = 0;
    while (*strp != '\0') {
        assert((*strp >= '0') && (*strp <= '9'));
        Int[str_len - (i++) - 2] = *strp - '0';
        strp ++;
    }
}

void print_bigint(char *bigint) {
    int i = int_max - 1;
    printf("BigInt\n");
    if (bigint[int_max - 1]) printf("-");
    while (bigint[--i] == 0);
    for (; i >= 0; i--)
        printf("%d", bigint[i]);
    printf("\n");
}

int main(void) {
    char * bigint1 = (char *)malloc(int_max * sizeof(char));
    char * bigint2 = (char *)malloc(int_max * sizeof(char));
    char * bigint3 = (char *)malloc(int_max * sizeof(char));
    char * bigintsum = (char *)malloc(int_max * sizeof(char));
    char * bigintsub = (char *)malloc(int_max * sizeof(char));
    char * bigintmul = (char *)malloc(int_max * sizeof(char));

    memset(bigint1, 0, int_max);
    memset(bigint2, 0, int_max);
    memset(bigint3, 0, int_max);
    memset(bigintsum, 0, int_max);
    memset(bigintsub, 0, int_max);
    memset(bigintmul, 0, int_max);

    double_2_bigint(bigint1, 7462911385);
    double_2_bigint(bigint2, 9800724324238);
    string_2_bigint(bigint3, "-4399000324898602398927826786492023650000000000000000000043242340000");
    bigint_sum(bigint1, bigint2, bigintsum);
    bigint_substract(bigint1, bigint2, bigintsub);
    bigint_mul(bigint1, bigint3, bigintmul);

    print_bigint(bigint1);
    print_bigint(bigint2);
    printf("large? %d\n", bigint_ge(bigint1, bigint2));
    printf("small? %d\n", bigint_le(bigint1, bigint2));
    printf("equal? %d\n", bigint_eq(bigint1, bigint2));
    print_bigint(bigint3);
    print_bigint(bigintsum);
    print_bigint(bigintsub);
    print_bigint(bigintmul);

    free(bigint1);
    free(bigint2);
    free(bigint3);
    free(bigintsum);
    free(bigintsub);
    free(bigintmul);
    return 0;
}
