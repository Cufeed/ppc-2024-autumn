#include "seq/gusev_n_trapezoidal_rule/include/ops_seq.hpp"

#include <cmath>
#include <limits>

bool gusev_n_trapezoidal_rule::TrapezoidalTask::pre_processing() {
  if (taskData->inputs.size() < 3) {
    return false;  // Не хватает входных данных
  }

    // Проверка на корректность данных
    if (taskData->inputs[0] == nullptr || taskData->inputs[1] == nullptr || taskData->inputs[2] == nullptr) {
      return false;  // Входные данные не инициализированы
    }

    a_ = *reinterpret_cast<double*>(taskData->inputs[0]);
    b_ = *reinterpret_cast<double*>(taskData->inputs[1]);
    n_ = *reinterpret_cast<int*>(taskData->inputs[2]);

    // Добавьте проверку на корректность n
    if (n_ <= 0) {
      return false;  // n должно быть положительным
    }

    result_ = 0.0;
    return true;
}

bool gusev_n_trapezoidal_rule::TrapezoidalTask::validation() {
  return n_ > 0 && n_ < std::numeric_limits<int>::max();
}

bool gusev_n_trapezoidal_rule::TrapezoidalTask::run() {
  double h = (b_ - a_) / n_;
  result_ = 0.5 * (std::sin(a_) + std::sin(b_));
  for (int i = 1; i < n_; ++i) {
    result_ += std::sin(a_ + i * h);
  }
  result_ *= h;
  return true;
}

bool gusev_n_trapezoidal_rule::TrapezoidalTask::post_processing() {
  *reinterpret_cast<double*>(taskData->outputs[0]) = result_;
  return true;
}