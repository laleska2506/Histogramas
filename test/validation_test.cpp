#include <gtest/gtest.h>

#include <random>

#include "sequential.h"
#include "openmp_critical.h"
#include "openmp_ompatomic.h"
#include "estandar.h"
#include "openmp_lock_unlock.h"
#include "openmp_atomic.h"
#include "estandar_reduction.h"
#include "openmp_reduction.h"
#include "openmp_lock_guard.h"

static int* randomInput = nullptr;
static const int MAXIMO_VALOR = 5;
static const int NUMERO_ELEMENTOS = 100000000;

void inicializa() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> uni_dis(1, MAXIMO_VALOR);

  if(randomInput == nullptr) {
    randomInput = new int[NUMERO_ELEMENTOS];
    for(int i = 0; i < NUMERO_ELEMENTOS; ++i) {
      randomInput[i] = uni_dis(gen);
    }
  }
}

void finaliza() {
  if(randomInput != nullptr) {
    delete[] randomInput;
    randomInput = nullptr;
  }
}

TEST(SequentialTest, pruebaOK) {
  Sequential histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPCriticalTest, pruebaOK) {
  OpenMPCritical histogramCalculatorC;
  auto histogramaC = histogramCalculatorC.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histogramaC) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPOMPATOMICTest, pruebaOK) {
  OpenMPOMPATOMIC histogramCalculatorAT;
  auto histogramaAT = histogramCalculatorAT.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histogramaAT) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(EstandarTest, pruebaOK) {
  Estandar histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR,
                                                  NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);  
}

TEST(OpenMPLockUnlockTest, PruebaOK) {
  OpenMPLockUnlock histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) {
    acum += puntuacion;
  }
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);  
}

TEST(OpenMPAtomicTest, pruebaOK) {
  OpenMPAtomic histogramCalculatorAT2;
  auto histogramaAT2 = histogramCalculatorAT2.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histogramaAT2) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(EstandarReductionTest, pruebaOK) {
  EstandarReduction histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPReductionTest, pruebaOK) {
  OpenMPReduction histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

TEST(OpenMPLockGuardTest, pruebaOK) {
  OpenMPLockGuard histogramCalculator;
  auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);

  int acum = 0;
  for(auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

int main(int argc, char** argv) {
  inicializa();
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  finaliza();
  return ret;
}
