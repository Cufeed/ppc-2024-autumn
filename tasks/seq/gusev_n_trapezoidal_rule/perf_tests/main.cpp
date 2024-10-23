// Copyright 2024 Nesterov Alexander
#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <random>
#include <vector>

#include "core/perf/include/perf.hpp"
#include "seq/gusev_n_trapezoidal_rule/include/ops_seq.hpp"

TEST(gusev_n_trapezoidal_rule_seq, test_pipeline_run) {
  std::vector<double> inputs(3);
  std::vector<double> output(1, 0.0);

  // Задаем границы интегрирования и количество трапеций 
  double a = 0.0; // Левая граница
  double b = 1.0;  // Правая граница
  int n = 1000;    // Количество трапеций

  inputs[0] = a;
  inputs[1] = b;
  inputs[2] = n;

  // Создаем TaskData
  auto taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(inputs.data()));
  taskDataSeq->inputs_count.emplace_back(inputs.size());

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  taskDataSeq->outputs_count.emplace_back(output.size());

  // Создаем задачу
  auto testTaskSequential = std::make_shared<gusev_n_integrate_trapezoidal::TestTaskSequential>(taskDataSeq);

  // Создаем Perf атрибуты
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Создаем и инициализируем результаты производительности 
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Создаем анализатор производительности
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->pipeline_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);

  // Проверяем результат интегрирования
  double expected_result = (b * b * b - a * a * a) / 3;  // Интеграл от x^2 от a до b
  ASSERT_NEAR(expected_result, output[0], 1e-5);         // Проверяем с точностью 1e-5
}

TEST(sequential_gusev_n_trapezoidal_rule_seq, test_task_run) {
  std::vector<double> inputs(3);
  std::vector<double> output(1, 0.0);

  // Задаем границы интегрирования и количество трапеций 
  double a = 0.0; // Левая граница
  double b = 1.0;  // Правая граница
  int n = 1000;    // Количество трапеций

  inputs[0] = a;
  inputs[1] = b;
  inputs[2] = n;

  // Создаем TaskData
  auto taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(inputs.data()));
  taskDataSeq->inputs_count.emplace_back(inputs.size());

  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  taskDataSeq->outputs_count.emplace_back(output.size());

  // Создаем задачу
  auto testTaskSequential = std::make_shared<gusev_n_integrate_trapezoidal::TestTaskSequential>(taskDataSeq);

  // Создаем Perf атрибуты 
  auto perfAttr = std::make_shared<ppc::core::PerfAttr>();
  perfAttr->num_running = 10;
  const auto t0 = std::chrono::high_resolution_clock::now();
  perfAttr->current_timer = [&] {
    auto current_time_point = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time_point - t0).count();
    return static_cast<double>(duration) * 1e-9;
  };

  // Создаем и инициализируем результаты производительности 
  auto perfResults = std::make_shared<ppc::core::PerfResults>();

  // Создаем анализатор производительности
  auto perfAnalyzer = std::make_shared<ppc::core::Perf>(testTaskSequential);
  perfAnalyzer->task_run(perfAttr, perfResults);
  ppc::core::Perf::print_perf_statistic(perfResults);

  // Проверяем результат интегрирования
  double expected_result = (b * b * b - a * a * a) / 3;  // Интеграл от x^2 от a до b
  ASSERT_NEAR(expected_result, output[0], 1e-5);         // Проверяем с точностью 1e-5
}