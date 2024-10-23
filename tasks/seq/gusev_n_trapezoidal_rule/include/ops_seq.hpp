// Copyright 2023 Nesterov Alexander
#pragma once

#include <functional>
#include <limits>
#include <string>
#include <vector>

#include "core/task/include/task.hpp"

namespace gusev_n_integrate_trapezoidal {

double integrate_trapezoidal(double (*func)(double), double a, double b, int n);

class TestTaskSequential : public ppc::core::Task {
 public:
  explicit TestTaskSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;
  double function(double x) {
    return x * x;  // Интегрируем f(x) = x^2
  }

 private:
  double a_{};
  double b_{};
  int n_{};
  double res_{};
};

}  // namespace gusev_n_integrate_trapezoidal