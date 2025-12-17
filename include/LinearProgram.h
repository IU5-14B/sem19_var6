#ifndef LINEARPROGRAM_H
#define LINEARPROGRAM_H

#include <vector>
#include <string>

class LinearProgram {
private:
    std::vector<double> objectiveCoefficients;  // Коэффициенты целевой функции
    std::vector<std::vector<double>> constraints;  // Матрица ограничений
    std::vector<double> constraintRHS;  // Правые части ограничений
    std::vector<std::string> constraintTypes;  // Типы ограничений: "<=", ">=", "="
    
    // Переменные для задачи максимизации
    double maxX, maxY, maxZ;
    double maxValue;
    
public:
    LinearProgram();
    
    void setProblem(
        const std::vector<double>& objCoeff,
        const std::vector<std::vector<double>>& constr,
        const std::vector<double>& rhs,
        const std::vector<std::string>& types
    );
    
    void solveMaximizationProblem();  // Решение конкретной задачи
    void solveUsingSimplex();  // Общий симплекс-метод
    
    void printProblem() const;
    void printSolution() const;
    
    // Геттеры для результатов
    double getMaxX() const { return maxX; }
    double getMaxY() const { return maxY; }
    double getMaxZ() const { return maxZ; }
    double getMaxValue() const { return maxValue; }
    
    // Вспомогательные методы
    static LinearProgram createDemoProblem();
    
private:
    bool isFeasibleSolution(double x, double y, double z) const;
    void evaluateCornerPoints();
    void convertToStandardForm();
};

#endif