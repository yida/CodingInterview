#include <iostream>

double fibonacci(int n) {
    if (n < 2) 
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

double fibonacci2(int n, double array[]) {
    if (n < 2) {
        array[n] = 1;
        return array[n];
    }
    if (array[n-2] < 0) array[n-2] = fibonacci2(n-2, array);
    if (array[n-1] < 0) array[n-1] = fibonacci2(n-1, array);
    array[n] = array[n-2] + array[n-1];
    return array[n];
}

int main() {
    int n = 100;
    double array[100];
    for (int i = 0; i < 100; i++)
        array[i] = -1;
    std::cout << fibonacci2(4, array) << std::endl;
//    std::cout << fibonacci(40) << std::endl;
    return 0;
}

