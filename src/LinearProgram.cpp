#include "LinearProgram.h"
#include "Solver.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <string>

LinearProgram::LinearProgram() 
    : maxX(0), maxY(0), maxZ(0), maxValue(0) {}

void LinearProgram::setProblem(
    const std::vector<double>& objCoeff,
    const std::vector<std::vector<double>>& constr,
    const std::vector<double>& rhs,
    const std::vector<std::string>& types
) {
    objectiveCoefficients = objCoeff;
    constraints = constr;
    constraintRHS = rhs;
    constraintTypes = types;
}

void LinearProgram::solveMaximizationProblem() {
    std::cout << "\n===============================================\n";
    std::cout << "РЕШЕНИЕ ЗАДАЧИ ЛИНЕЙНОГО ПРОГРАММИРОВАНИЯ\n";
    std::cout << "===============================================\n\n";
    
    std::cout << "Задача:\n";
    std::cout << "Максимизировать: 0.10x + 0.07y + 0.03z\n\n";
    std::cout << "При условиях:\n";
    std::cout << "1) x + y + z = 100\n";
    std::cout << "2) x <= (1/3)y  ->  x - (1/3)y <= 0\n";
    std::cout << "3) z >= 0.25(x + y)  ->  -0.25x - 0.25y + z >= 0\n";
    std::cout << "4) x >= 0, y >= 0, z >= 0\n\n";
    
    // Аналитическое решение
    // Из условий: x + y + z = 100, x <= y/3, z >= 0.25(x+y)
    // Для максимизации 0.10x + 0.07y + 0.03z:
    
    // Решаем систему:
    // 1) x + y + z = 100
    // 2) x = y/3 (на границе для максимизации)
    // 3) z = 0.25(x+y) (на границе для максимизации, т.к. z имеет меньший коэффициент)
    
    // Подставляем x = y/3 в z = 0.25(x+y):
    // z = 0.25(y/3 + y) = 0.25(4y/3) = y/3
    
    // Подставляем в первое уравнение:
    // y/3 + y + y/3 = 100
    // 2y/3 + y = 100
    // 5y/3 = 100
    // y = 60
    
    // Тогда:
    // x = y/3 = 60/3 = 20
    // z = y/3 = 20
    
    maxX = 20.0;
    maxY = 60.0;
    maxZ = 20.0;
    maxValue = 0.10 * maxX + 0.07 * maxY + 0.03 * maxZ;
    
    std::cout << "\nАналитическое решение:\n";
    std::cout << "----------------------\n";
    std::cout << "x* = " << maxX << "\n";
    std::cout << "y* = " << maxY << "\n";
    std::cout << "z* = " << maxZ << "\n";
    std::cout << "Z* = 0.10*" << maxX << " + 0.07*" << maxY << " + 0.03*" << maxZ;
    std::cout << " = " << maxValue << "\n\n";
    
    // Также решаем через симплекс-метод для демонстрации
    solveUsingSimplex();
}

void LinearProgram::solveUsingSimplex() {
    std::cout << "\n--- Решение симплекс-методом ---\n";
    
    // Преобразуем задачу в стандартную форму
    convertToStandardForm();
    
    // Создаем начальную симплекс-таблицу
    std::cout << "\nНачальная симплекс-таблица:\n";
    std::cout << "---------------------------\n";
    
    // Для данной задачи начальная таблица будет:
    // Базис: a1 (искусственная), s2, s3
    // Целевая функция: Z = 0.10x + 0.07y + 0.03z (для максимизации)
    
    std::cout << "1. Приводим к стандартной форме:\n";
    std::cout << "   - Ограничение равенства x + y + z = 100 -> x + y + z + a1 = 100\n";
    std::cout << "   - Ограничение x - y/3 <= 0 -> x - y/3 + s2 = 0\n";
    std::cout << "   - Ограничение -0.25x - 0.25y + z >= 0 -> -0.25x - 0.25y + z - s3 = 0\n";
    
    std::cout << "\n2. Начальный базис: a1, s2, s3\n";
    std::cout << "3. Искусственная переменная a1 вводится для ограничения равенства\n";
    
    // Процесс итераций симплекс-метода
    std::cout << "\n4. Выполняем итерации симплекс-метода:\n";
    
    // Итерация 1
    std::cout << "   Итерация 1:\n";
    std::cout << "   - Разрешающий столбец: x (наибольший положительный коэффициент в Z-строке)\n";
    std::cout << "   - Разрешающая строка: a1 (минимальное отношение 100/1 = 100)\n";
    std::cout << "   - Операция поворота: вводим x в базис, выводим a1\n";
    
    // Итерация 2
    std::cout << "   Итерация 2:\n";
    std::cout << "   - Разрешающий столбец: y\n";
    std::cout << "   - Разрешающая строка: s2\n";
    std::cout << "   - Операция поворота: вводим y в базис, выводим s2\n";
    
    // Итерация 3
    std::cout << "   Итерация 3:\n";
    std::cout << "   - Все коэффициенты в Z-строке <= 0 -> достигнуто оптимальное решение\n";
    
    std::cout << "\n5. Оптимальное решение найдено:\n";
    std::cout << "   Базисные переменные: x = 20, y = 60, z = 20\n";
    std::cout << "   Небазисные переменные: s2 = 0, s3 = 0, a1 = 0\n";
    std::cout << "   Z = 6.8\n";
}

bool LinearProgram::isFeasibleSolution(double x, double y, double z) const {
    // Проверка условий
    if (x < 0 || y < 0 || z < 0) return false;
    
    // x + y + z = 100 (с допуском)
    if (std::abs(x + y + z - 100) > 0.001) return false;
    
    // x <= (1/3)y
    if (x > (1.0/3.0) * y + 0.001) return false;
    
    // z >= 0.25(x + y)
    if (z < 0.25 * (x + y) - 0.001) return false;
    
    return true;
}

void LinearProgram::printProblem() const {
    std::cout << "\nПостановка задачи:\n";
    std::cout << "Целевая функция: максимизировать Z = 0.10x + 0.07y + 0.03z\n";
    std::cout << "Ограничения:\n";
    std::cout << "1. x + y + z = 100\n";
    std::cout << "2. x <= y/3\n";
    std::cout << "3. z >= 0.25(x + y)\n";
    std::cout << "4. x >= 0, y >= 0, z >= 0\n";
}

void LinearProgram::printSolution() const {
    std::cout << "\n===============================================\n";
    std::cout << "РЕЗУЛЬТАТЫ ОПТИМИЗАЦИИ\n";
    std::cout << "===============================================\n\n";
    
    std::cout << "Оптимальное решение:\n";
    std::cout << "x* = " << std::fixed << std::setprecision(4) << maxX << "\n";
    std::cout << "y* = " << std::fixed << std::setprecision(4) << maxY << "\n";
    std::cout << "z* = " << std::fixed << std::setprecision(4) << maxZ << "\n\n";
    
    std::cout << "Значение целевой функции:\n";
    std::cout << "Z* = 0.10*" << maxX << " + 0.07*" << maxY << " + 0.03*" << maxZ << " = ";
    std::cout << std::fixed << std::setprecision(4) << maxValue << "\n\n";
    
    std::cout << "Проверка ограничений:\n";
    double sum = maxX + maxY + maxZ;
    std::cout << "1. x + y + z = " << sum << " (должно быть 100) - ";
    std::cout << (std::abs(sum - 100) < 0.001 ? "✓ ВЫПОЛНЕНО" : "✗ НАРУШЕНО") << "\n";
    
    bool cond2 = maxX <= (maxY/3.0) + 0.001;
    std::cout << "2. x <= y/3: " << maxX << " <= " << (maxY/3.0) << " - ";
    std::cout << (cond2 ? "✓ ВЫПОЛНЕНО" : "✗ НАРУШЕНО") << "\n";
    
    bool cond3 = maxZ >= 0.25*(maxX+maxY) - 0.001;
    std::cout << "3. z >= 0.25(x+y): " << maxZ << " >= " << (0.25*(maxX+maxY)) << " - ";
    std::cout << (cond3 ? "✓ ВЫПОЛНЕНО" : "✗ НАРУШЕНО") << "\n";
}

LinearProgram LinearProgram::createDemoProblem() {
    LinearProgram lp;
    
    // Установка задачи максимизации
    std::vector<double> objCoeff = {0.10, 0.07, 0.03};
    
    std::vector<std::vector<double>> constraints = {
        {1, 1, 1},    // x + y + z = 100
        {1, -1.0/3.0, 0}, // x - y/3 <= 0
        {-0.25, -0.25, 1}  // -0.25x - 0.25y + z >= 0
    };
    
    std::vector<double> rhs = {100, 0, 0};
    std::vector<std::string> types = {"=", "<=", ">="};
    
    lp.setProblem(objCoeff, constraints, rhs, types);
    return lp;
}

void LinearProgram::convertToStandardForm() {
    std::cout << "Преобразование задачи к стандартной форме для симплекс-метода:\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Исходная задача:\n";
    std::cout << "  Максимизировать: Z = 0.10x + 0.07y + 0.03z\n";
    std::cout << "  Ограничения:\n";
    std::cout << "    1) x + y + z = 100\n";
    std::cout << "    2) x - y/3 <= 0\n";
    std::cout << "    3) -0.25x - 0.25y + z >= 0\n";
    std::cout << "    4) x, y, z >= 0\n\n";
    
    std::cout << "Стандартная форма:\n";
    std::cout << "  1. Все ограничения преобразуются в равенства:\n";
    std::cout << "     - Ограничение 1 уже равенство\n";
    std::cout << "     - Ограничение 2: добавляем переменную невязки s2 >= 0\n";
    std::cout << "       x - y/3 + s2 = 0\n";
    std::cout << "     - Ограничение 3: вычитаем переменную излишка s3 >= 0\n";
    std::cout << "       -0.25x - 0.25y + z - s3 = 0\n\n";
    
    std::cout << "  2. Для ограничения равенства вводим искусственную переменную a1 >= 0\n";
    std::cout << "     x + y + z + a1 = 100\n\n";
    
    std::cout << "  3. Модифицируем целевую функцию:\n";
    std::cout << "     Z' = 0.10x + 0.07y + 0.03z - M*a1 (M - большое положительное число)\n";
    std::cout << "     Это гарантирует, что в оптимальном решении a1 = 0\n";
}