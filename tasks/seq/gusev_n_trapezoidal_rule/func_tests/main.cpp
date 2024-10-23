// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <vector>

#include "seq/gusev_n_trapezoidal_rule/include/ops_seq.hpp"

void runIntegrationTest(double a, double b, int n, double expected_result) {
  std::vector<double> inputs = {a, b, static_cast<double>(n)};
  std::vector<double> output(1, 0.0);

  // Создаем TaskData
  auto taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(inputs.data()));
  taskDataSeq->inputs_count.emplace_back(3);  // 3 входных данных
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(output.data()));
  taskDataSeq->outputs_count.emplace_back(1);  // 1 выходное значение

  // Создаем задачу
  auto testTaskSequential = std::make_shared<gusev_n_integrate_trapezoidal::TestTaskSequential>(taskDataSeq);
  ASSERT_EQ(testTaskSequential->validation(), true);
  testTaskSequential->pre_processing();
  testTaskSequential->run();
  testTaskSequential->post_processing();

  ASSERT_NEAR(expected_result, output[0], 1e-5);  // Проверяем с точностью 1e-5
}

TEST(gusev_n_trapezoidal_rule_seq, test_integration_0_to_1) {
  double a = 0.0;  // Левая граница 
  double b = 1.0;  // Правая граница
  int n = 1000;    // Количество трапеций
  double expected_result = (b * b * b - a * a * a) / 3;  // Интеграл от x^2 от 0 до 1

  runIntegrationTest(a, b, n, expected_result);
}

TEST(gusev_n_trapezoidal_rule_seq, test_integration_1_to_2) {
  double a = 1.0;  // Левая граница 
  double b = 2.0;  // Правая граница 
  int n = 1000;    // Количество трапеций
  double expected_result = (b * b * b - a * a * a) / 3;  // Интеграл от x^2 от 1 до 2

  runIntegrationTest(a, b, n, expected_result);
}

TEST(gusev_n_trapezoidal_rule_seq, test_integration_0_to_10) {
  double a = 0.0;  // Левая граница 
  double b = 10.0; // Правая граница
  int n = 1000;    // Количество трапеций
  double expected_result = (b * b * b - a * a * a) / 3;  // Интеграл от x^2 от 0 до 10

  runIntegrationTest(a, b, n, expected_result);
}

TEST(gusev_n_trapezoidal_rule_seq, test_integration_negative) {
  double a = -1.0;  // Левая граница
  double b = 0.0;   // Правая граница 
  int n = 1000;    // Количество трапеций
  double expected_result = (b * b * b - a * a * a) / 3;  // Интеграл от x^2 от -1 до 0

  runIntegrationTest(a, b, n, expected_result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  std::cout << "Press Enter to continue...";
  std::cin.get();  // Ожидание ввода от пользователя 
  return result;
}
