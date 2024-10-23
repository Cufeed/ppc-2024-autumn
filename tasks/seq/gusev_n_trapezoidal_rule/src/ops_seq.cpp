// Copyright 2024 Nesterov Alexander
#include "seq/gusev_n_trapezoidal_rule/include/ops_seq.hpp"

#include <cmath>

using namespace std::chrono_literals;

#include <cmath>
#include <limits>

using namespace std::chrono_literals;

double integrate_trapezoidal(double (*func)(double), double a, double b, int n) {
  double h = (b - a) / n;
  double sum = 0.5 * (func(a) + func(b));

  for (int i = 1; i < n; i++) {
    sum += func(a + i * h);
  }
  return sum * h;
}

bool gusev_n_integrate_trapezoidal::TestTaskSequential::pre_processing() {
  internal_order_test();
  // Инициализация значений для границ интегрирования и количества трапеций
  a_ = *reinterpret_cast<double*>(taskData->inputs[0]);
  b_ = *reinterpret_cast<double*>(taskData->inputs[1]);
  n_ = static_cast<int>(
      *reinterpret_cast<double*>(taskData->inputs[2]));  // Преобразуйте в int // Инициализация результата res_ = 0.0;
  return true;
}

bool gusev_n_integrate_trapezoidal::TestTaskSequential::validation() {
  internal_order_test();
  // Проверка корректности входных данных
  std::cout << "n_: " << n_ << ", inputs_count.size(): " << taskData->inputs_count.size()
            << ", outputs_count.size(): " << taskData->outputs_count.size() << std::endl;
  return n_ > 0 && taskData->inputs_count.size() == 3 && taskData->outputs_count.size() == 1;
}

bool gusev_n_integrate_trapezoidal::TestTaskSequential::run() {
  internal_order_test();
  // Выполнение интегрирования методом трапеции
  double h = (b_ - a_) / n_;                   // Ширина трапеции
  res_ = (function(a_) + function(b_)) / 2.0;
  // Начальные значения
  for (int i = 1; i < n_; ++i) {
    double x = a_ + i * h;
    res_ += function(x);  // Суммируем значения функции
  }

res_ *= h;  // Умножаем на ширину
return true;
}

bool gusev_n_integrate_trapezoidal::TestTaskSequential::post_processing() {
  internal_order_test();
  // Сохранение результата
  *reinterpret_cast<double*>(taskData->outputs[0]) = res_;
  return true;
}

//double gusev_n_integrate_trapezoidal::TestTaskSequential::function(double x) {
//  return x * x;
//}
