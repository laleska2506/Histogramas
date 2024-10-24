#include "openmp_critical.h"

std::vector<int> OpenMPCritical::calculate(const int* input, const int buckets, const int size) {
  std::vector<int> histogram(buckets, 0);

  #pragma omp parallel for
  for (int idx = 0; idx < size; idx++) {
    #pragma omp critical
    histogram[input[idx] - 1]++;
    }

  return histogram;
}
