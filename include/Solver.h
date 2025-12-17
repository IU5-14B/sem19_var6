#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

class Solver {
public:
    enum class ConstraintType {
        LESS_EQUAL,
        GREATER_EQUAL,
        EQUAL
    };
    
    struct Constraint {
        std::vector<double> coefficients;
        double rhs;
        ConstraintType type;
        std::string name;
    };
    
    static std::vector<double> solveLinearProgram(
        const std::vector<double>& objective,
        const std::vector<Constraint>& constraints,
        bool maximize = true
    );
    
    static void printResults(const std::vector<double>& solution, 
                            const std::vector<double>& objective);
    
private:
    static std::vector<std::vector<double>> createTableau(
        const std::vector<double>& objective,
        const std::vector<Constraint>& constraints,
        bool maximize
    );
    
    static int findPivotColumn(const std::vector<std::vector<double>>& tableau);
    static int findPivotRow(const std::vector<std::vector<double>>& tableau, int pivotCol);
    static void performPivot(std::vector<std::vector<double>>& tableau, 
                           int pivotRow, int pivotCol);
    static bool isOptimal(const std::vector<std::vector<double>>& tableau);
};

#endif