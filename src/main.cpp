#include "LinearProgram.h"
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void printSimplexTable(const std::vector<std::vector<double>>& tableau, 
                      const std::vector<std::string>& varNames) {
    std::cout << "\n===============================================\n";
    std::cout << "СИМПЛЕКС-ТАБЛИЦА (текущая задача)\n";
    std::cout << "===============================================\n\n";
    
    // Заголовки столбцов
    std::cout << std::setw(10) << "Базис" 
              << std::setw(10) << "x" 
              << std::setw(10) << "y" 
              << std::setw(10) << "z" 
              << std::setw(10) << "s1" 
              << std::setw(10) << "s2" 
              << std::setw(10) << "s3"
              << std::setw(10) << "a1"
              << std::setw(15) << "Решение" << std::endl;
    
    std::cout << std::string(95, '-') << std::endl;
    
    // Данные таблицы
    for (size_t i = 0; i < tableau.size(); i++) {
        std::string basis;
        if (i == 0) {
            basis = "Z";
        } else if (i == 1) {
            basis = "a1";
        } else if (i == 2) {
            basis = "s2";
        } else if (i == 3) {
            basis = "s3";
        }
        
        std::cout << std::setw(10) << basis;
        for (size_t j = 0; j < tableau[i].size(); j++) {
            if (j < tableau[i].size() - 1) {
                std::cout << std::setw(10) << std::fixed << std::setprecision(4) << tableau[i][j];
            } else {
                std::cout << std::setw(15) << std::fixed << std::setprecision(4) << tableau[i][j];
            }
        }
        std::cout << std::endl;
    }
}

void generateHTMLReport(const LinearProgram& lp, 
                       const std::vector<std::vector<double>>& tableau) {
    std::ofstream html("reports/report.html");
    
    html << "<!DOCTYPE html>\n";
    html << "<html lang='ru'>\n";
    html << "<head>\n";
    html << "    <meta charset='UTF-8'>\n";
    html << "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
    html << "    <title>Отчет по задаче линейного программирования</title>\n";
    html << "    <style>\n";
    html << "        body { font-family: Arial, sans-serif; margin: 40px; line-height: 1.6; }\n";
    html << "        h1, h2, h3 { color: #333; }\n";
    html << "        .container { max-width: 1200px; margin: 0 auto; }\n";
    html << "        .problem { background: #f4f4f4; padding: 20px; border-radius: 5px; margin: 20px 0; }\n";
    html << "        .solution { background: #e8f4f8; padding: 20px; border-radius: 5px; margin: 20px 0; }\n";
    html << "        table { border-collapse: collapse; width: 100%; margin: 20px 0; }\n";
    html << "        th, td { border: 1px solid #ddd; padding: 12px; text-align: center; }\n";
    html << "        th { background-color: #4CAF50; color: white; }\n";
    html << "        tr:nth-child(even) { background-color: #f2f2f2; }\n";
    html << "        .result { background: #d4edda; padding: 15px; border-radius: 5px; margin: 15px 0; }\n";
    html << "        .simplex-table { overflow-x: auto; margin: 20px 0; }\n";
    html << "        .simplex-table table { min-width: 800px; }\n";
    html << "    </style>\n";
    html << "</head>\n";
    html << "<body>\n";
    html << "    <div class='container'>\n";
    html << "        <h1>Отчет по решению задачи линейного программирования</h1>\n";
    
    // Постановка задачи
    html << "        <div class='problem'>\n";
    html << "            <h2>Постановка задачи</h2>\n";
    html << "            <p><strong>Целевая функция:</strong> максимизировать Z = 0.10x + 0.07y + 0.03z</p>\n";
    html << "            <p><strong>Ограничения:</strong></p>\n";
    html << "            <ul>\n";
    html << "                <li>x + y + z = 100</li>\n";
    html << "                <li>x ≤ (1/3)y</li>\n";
    html << "                <li>z ≥ 0.25(x + y)</li>\n";
    html << "                <li>x ≥ 0, y ≥ 0, z ≥ 0</li>\n";
    html << "            </ul>\n";
    html << "        </div>\n";
    
    // Симплекс-таблица
    html << "        <div class='solution'>\n";
    html << "            <h2>Симплекс-таблица</h2>\n";
    html << "            <div class='simplex-table'>\n";
    html << "                <table>\n";
    html << "                    <tr>\n";
    html << "                        <th>Базис</th><th>x</th><th>y</th><th>z</th><th>s1</th><th>s2</th><th>s3</th><th>a1</th><th>Решение</th>\n";
    html << "                    </tr>\n";
    
    std::vector<std::string> basisNames = {"Z", "a1", "s2", "s3"};
    for (size_t i = 0; i < tableau.size(); i++) {
        html << "                    <tr>\n";
        html << "                        <td><strong>" << basisNames[i] << "</strong></td>\n";
        for (size_t j = 0; j < tableau[i].size(); j++) {
            if (j == tableau[i].size() - 1) {
                html << "                        <td><strong>" << std::fixed << std::setprecision(4) << tableau[i][j] << "</strong></td>\n";
            } else {
                html << "                        <td>" << std::fixed << std::setprecision(4) << tableau[i][j] << "</td>\n";
            }
        }
        html << "                    </tr>\n";
    }
    
    html << "                </table>\n";
    html << "            </div>\n";
    html << "            <p><em>Примечание: s1, s2, s3 - дополнительные переменные, a1 - искусственная переменная</em></p>\n";
    html << "        </div>\n";
    
    // Результаты
    html << "        <div class='solution'>\n";
    html << "            <h2>Результаты оптимизации</h2>\n";
    html << "            <div class='result'>\n";
    html << "                <h3>Оптимальное решение:</h3>\n";
    html << "                <table>\n";
    html << "                    <tr><th>Переменная</th><th>Значение</th></tr>\n";
    html << "                    <tr><td>x</td><td>" << std::fixed << std::setprecision(4) << lp.getMaxX() << "</td></tr>\n";
    html << "                    <tr><td>y</td><td>" << std::fixed << std::setprecision(4) << lp.getMaxY() << "</td></tr>\n";
    html << "                    <tr><td>z</td><td>" << std::fixed << std::setprecision(4) << lp.getMaxZ() << "</td></tr>\n";
    html << "                </table>\n";
    html << "                <p><strong>Максимальное значение целевой функции:</strong> " 
         << std::fixed << std::setprecision(4) << lp.getMaxValue() << "</p>\n";
    html << "            </div>\n";
    
    // Проверка ограничений
    html << "            <h3>Проверка ограничений:</h3>\n";
    html << "            <table>\n";
    html << "                <tr><th>Ограничение</th><th>Значение</th><th>Статус</th></tr>\n";
    
    double sum = lp.getMaxX() + lp.getMaxY() + lp.getMaxZ();
    bool cond1 = std::abs(sum - 100) < 0.001;
    html << "                <tr><td>x + y + z = 100</td><td>" << sum << "</td><td>" 
         << (cond1 ? "✓ Выполнено" : "✗ Нарушено") << "</td></tr>\n";
    
    bool cond2 = lp.getMaxX() <= (lp.getMaxY()/3.0) + 0.001;
    html << "                <tr><td>x ≤ y/3</td><td>" << lp.getMaxX() << " ≤ " 
         << std::fixed << std::setprecision(4) << (lp.getMaxY()/3.0) << "</td><td>" 
         << (cond2 ? "✓ Выполнено" : "✗ Нарушено") << "</td></tr>\n";
    
    bool cond3 = lp.getMaxZ() >= 0.25*(lp.getMaxX() + lp.getMaxY()) - 0.001;
    html << "                <tr><td>z ≥ 0.25(x+y)</td><td>" << lp.getMaxZ() << " ≥ " 
         << std::fixed << std::setprecision(4) << 0.25*(lp.getMaxX() + lp.getMaxY()) << "</td><td>" 
         << (cond3 ? "✓ Выполнено" : "✗ Нарушено") << "</td></tr>\n";
    
    html << "            </table>\n";
    html << "        </div>\n";
    
    // Анализ
    html << "        <div class='solution'>\n";
    html << "            <h2>Анализ решения</h2>\n";
    html << "            <p>Задача решена с использованием симплекс-метода. Процесс решения включает:</p>\n";
    html << "            <ul>\n";
    html << "                <li>Приведение задачи к стандартной форме</li>\n";
    html << "                <li>Построение начальной симплекс-таблицы</li>\n";
    html << "                <li>Выполнение итераций симплекс-метода</li>\n";
    html << "                <li>Проверка условий оптимальности</li>\n";
    html << "            </ul>\n";
    html << "            <p>Оптимальное решение достигается при x = " << lp.getMaxX() 
         << ", y = " << lp.getMaxY() << ", z = " << lp.getMaxZ() 
         << " с максимальным значением целевой функции Z = " << lp.getMaxValue() << ".</p>\n";
    html << "        </div>\n";
    
    html << "    </div>\n";
    html << "</body>\n";
    html << "</html>\n";
    
    html.close();
    std::cout << "\nHTML-отчет создан: reports/report.html\n";
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    
    // Создаем и решаем задачу линейного программирования
    LinearProgram lp = LinearProgram::createDemoProblem();
    lp.printProblem();
    lp.solveMaximizationProblem();
    lp.printSolution();
    
    // Создаем симплекс-таблицу для демонстрации
    std::vector<std::vector<double>> simplexTable = {
        // Z-строка: коэффициенты для x, y, z, s1, s2, s3, a1, решение
        {-0.10, -0.07, -0.03, 0, 0, 0, 0, 0},  // Z (максимизация, поэтому отрицательные)
        
        // Ограничения:
        // 1) x + y + z = 100 -> x + y + z + a1 = 100 (искусственная переменная)
        {1.0, 1.0, 1.0, 0, 0, 0, 1.0, 100.0},  // a1
        
        // 2) x - y/3 <= 0 -> x - y/3 + s2 = 0
        {1.0, -1.0/3.0, 0, 0, 1.0, 0, 0, 0.0},  // s2
        
        // 3) -0.25x - 0.25y + z >= 0 -> -0.25x - 0.25y + z - s3 = 0
        {-0.25, -0.25, 1.0, 0, 0, -1.0, 0, 0.0}  // s3
    };
    
    std::vector<std::string> varNames = {"x", "y", "z", "s1", "s2", "s3", "a1"};
    
    // Выводим симплекс-таблицу
    printSimplexTable(simplexTable, varNames);
    
    // Генерируем HTML-отчет
    generateHTMLReport(lp, simplexTable);
    
    return 0;
}