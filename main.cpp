//
//  main.cpp
//  Triangles
//
//  Created by Кирилл Воронин on 14.03.2024.
//

#include <iostream>
#include <vector>
#include <cmath>

// Структура, представляющая точку на плоскости

struct Point {
    
    double x, y;
    
};

// Функция для проверки, лежит ли точка P справа от вектора AB

bool pointSide(const Point& A, const Point& B, const Point& P) {
    
    // Если результат отрицательный, то точка P лежит справа от вектора AB
    return ((B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x)) < 0;
}

// Функция для нахождения точки пересечения двух отрезков AB и CD

Point computeIntersection(const Point& A, const Point& B, const Point& C, const Point& D) {
    
    // Вычисление коэффициентов уравнений прямых AB и CD в общем виде: ax + by = c
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1 * A.x + b1 * A.y;

    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2 * C.x + b2 * C.y;

    // Вычисление определителя матрицы коэффициентов (для определения пересечения прямых)
    double det = a1 * b2 - a2 * b1;

    // Нахождение координат точки пересечения по формулам Крамера
    double x = (b2 * c1 - b1 * c2) / det;
    double y = (a1 * c2 - a2 * c1) / det;

    // Возвращение координат точки пересечения
    return {x, y};
}


// Функция для вычисления площади многоугольника по формуле Гаусса

double polygonArea(const std::vector<Point>& polygon) {
    
    double area = 0.0; // Инициализация переменной для накопления площади
    
    int n = polygon.size(); // Количество вершин многоугольника

    // Цикл вычисления площади
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n; // Индекс следующей вершины

        // Вычисление площади и добавление ее к общей площади
        area += polygon[i].x * polygon[j].y;
        area -= polygon[j].x * polygon[i].y;
    }

    // Возвращение абсолютного значения площади, деленной на 2.0
    return std::abs(area) / 2.0;
}

// Функция для нахождения пересечения двух многоугольников
std::vector<Point> intersection(const std::vector<Point>& subjectPolygon, const std::vector<Point>& clipPolygon) {
    
    std::vector<Point> outputList = subjectPolygon;

    // Идем по всем ребрам второго многоугольника
    for (int i = 0; i < clipPolygon.size(); ++i) {
        int k = (i + 1) % clipPolygon.size();
        std::vector<Point> inputList = outputList;
        
        outputList.clear();
        
        Point S = inputList.back(); // Последняя точка входного списка

        // Перебираем все точки первого многоугольника
        
        for (const Point& E : inputList) {
            
            
            // Если точка лежит справа от ребра, добавляем ее в выходной список
            if (pointSide(clipPolygon[i], clipPolygon[k], E)) {
                if (!pointSide(clipPolygon[i], clipPolygon[k], S)) {
                    outputList.push_back(computeIntersection(S, E, clipPolygon[i], clipPolygon[k]));
                }
                outputList.push_back(E);
            }
            // Если точка лежит слева от ребра, добавляем точку пересечения и саму точку
            
            else if (pointSide(clipPolygon[i], clipPolygon[k], S)) {
                outputList.push_back(computeIntersection(S, E, clipPolygon[i], clipPolygon[k]));
            }
            
            S = E;
        }
    }

    return outputList; // Возвращаем список точек пересечения
}

int main() {
    
    
    // Создаем векторы для хранения вершин двух треугольников
    std::vector<Point> triangle1(3), triangle2(3);

    // Считываем координаты вершин для двух треугольников
    for (int i = 0; i < 3; ++i) {
        
        std::cin >> triangle1[i].x >> triangle1[i].y;
    }
    for (int i = 0; i < 3; ++i) {
        
        std::cin >> triangle2[i].x >> triangle2[i].y;
    }

    // Находим пересечение треугольников и вычисляем площадь пересечения
    std::vector<Point> intersectionPolygon = intersection(triangle1, triangle2);
    double intersectionArea = polygonArea(intersectionPolygon);
    
    std::cout << "Площадь пересечения: " << intersectionArea << std::endl;   // Выводим площадь пересечения

    return 0;
}

