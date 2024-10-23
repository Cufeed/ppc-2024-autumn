// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <cmath>
#include <random>
#include <corecrt_math_defines.h>
#include "seq/gusev_n_trapezoidal_rule/include/ops_seq.hpp"

TEST(gusev_n_trapezoidal_rule_seq, test_integration_1) {
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();

  double a = 0.0;
  double b = M_PI;
  int n = 1000;
  double out = 0.0;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&a));
  taskData->inputs_count.emplace_back(sizeof(a));  // Добавляем размер
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&b));
  taskData->inputs_count.emplace_back(sizeof(b));  // Добавляем размер 
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&n));
  taskData->inputs_count.emplace_back(sizeof(n));  // Добавляем размер 
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
  taskData->outputs_count.emplace_back(sizeof(out));  // Добавляем размер 

  gusev_n_trapezoidal_rule::TrapezoidalTask testTask(taskData);
  testTask.pre_processing();
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  ASSERT_EQ(testTask.validation(), true);
  testTask.run();
  std::cout << "After running:" << std::endl;
  testTask.post_processing();
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << out << std::endl;

  ASSERT_NEAR(out, 2.0, 0.01);  // Проверка на значение интеграла sin(x) от 0 до π
}

TEST(gusev_n_trapezoidal_rule_seq, test_integration_2) {
  std::shared_ptr<ppc::core::TaskData> taskData = std::make_shared<ppc::core::TaskData>();

  double a = 0.0;
  double b = M_PI / 2;
  int n = 1000;
  double out = 0.0;

  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&a));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&b));
  taskData->inputs.emplace_back(reinterpret_cast<uint8_t *>(&n));
  taskData->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));

  gusev_n_trapezoidal_rule::TrapezoidalTask testTask(taskData);
  testTask.pre_processing();
  ASSERT_EQ(testTask.validation(), true);
  testTask.run();
  testTask.post_processing();

  ASSERT_NEAR(out, 1.0, 0.01);  // Проверка на значение интеграла sin(x) от 0 до π/2
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  std::cout << "Press Enter to continue...";
  std::cin.get();  // Ожидание ввода от пользователя 
  return result;
}
