//
// Решение предполагает использование стека.
// Способ реализации стека может быть любым (список/динамический массив).
//

/****************************************************************************

Задача 5_3. Прямоугольники.

Дана последовательность *N* прямоугольников различной ширины и высоты
(w_i,h_i). Прямоугольники расположены, начиная с точки (0, 0), на оси
ОХ вплотную друг за другом (вправо). Требуется найти M - площадь
максимального прямоугольника (параллельного осям координат), который
можно вырезать из этой фигуры. Время работы - O(n).

```
^ y                              ^ y
|                                |
|        +--+                    |        +--+
|        |  |    +--+            |        |  |    +--+
|        |  |    |  |            |        |  |    |  |
+--------+  |    |  |            *************    |  |
|        |  |    |  |            *************    |  |
|        |  +----+  |            *************----+  |
|        |  |    |  |    x       *************    |  |      x
+--------+--+----+--+---->       *************----+--+------>
```

*Формат входных данных.* В первой строке задано число N (1 ≤ N ≤ 10000).
Далее идет N строк. В каждой строке содержится два числа width
и height: ширина и высота i-го прямоугольника. (0 < width ≤ 10000, 0 ≤ height ≤ 10000)

*Формат выходных данных.* Вывести число *M*. (0 ≤ M ≤ 10^9).

  in      | out
  --------|------
  4       | 1200
  30 30   | 
  10 40   | 
  20 10   | 
  10 40   | 

  in      | out
  --------|------
  1       | 3000
  1 3000  | 

  in      | out
  --------|------
  3       | 8
  1 1     | 
  1 3     | 
  3 2     | 

****************************************************************************/

#include <iostream>

int main()
{
    return 0;
}
