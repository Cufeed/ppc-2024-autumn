// Copyright 2024 Nesterov Alexander
#include <gtest/gtest.h>
#include <random>
#include <vector>
#include "core/perf/include/perf.hpp"
#include "seq/gusev_n_trapezoidal_rule/include/ops_seq.hpp"
#include <corecrt_math_defines.h>

TEST(gusev_n_trapezoidal_rule_seq, test_pipeline_run) {
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();
  double a = 0.0;
  double b = M_PI;
  int n = 1000000;  // Увеличение n для увеличения времени выполнения 
  double out = 0.0;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&a));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&b));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&n));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));

  auto testTaskSequential = std::make_shared<gusev_n_trapezoidal_rule::TrapezoidalTask>(taskData);

  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Искусственная задержка
  std::this_thread::sleep_for(std::chrono::milliseconds(50));  // 50 мс

  auto perfResults = std::make_shared<ppc::core::PerfResults>();
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);
  ASSERT_NEAR(out, 2.0, 0.01);  // Проверка на значение интеграла sin(x) от 0 до π
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  std::cout << "Press Enter to continue...";
  std::cin.get();  // Ожидание ввода от пользователя
  return result;
}