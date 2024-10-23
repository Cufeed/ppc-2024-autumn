// Copyright 2024 Nesterov Alexander
#pragma once

#include <vector>

#include "core/task/include/task.hpp"

namespace gusev_n_trapezoidal_rule {

class TrapezoidalTask : public ppc::core::Task {
 public:
  explicit TrapezoidalTask(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  double a_;
  double b_;
  int n_;
  double result_;
};

}  // namespace gusev_n_trapezoidal_rule