int search(double array, double x, int p, int r) {
  int k = floor((p + r) / 2);
  if ((r-p) == 1) return p;
  if (array[k] > x)
    return search(array, x, p, k);
  else
    return search(array, x, k, r);
}

double sqrt(double n) {
  if (n < 0) return -1;
  if (n >= 1) {
    int levelcounter = 0;
    int ncurrent = floor(n);
    double* array = new double[ncurrent];
    for (int i = 0; i < ncurrent; i++) // initial the array 
      array[i] = i;
    int ret = search(array, n, 0, ncurrent);
  } else {

  }
}
