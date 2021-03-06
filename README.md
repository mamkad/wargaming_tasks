# Тестовое задание Wargaming Санкт-Петербург
## Задание 1
*На языке Python или С/С++, написать алгоритм (функцию) определения четности целого числа, который будет аналогичен нижеприведенному по функциональности, но отличен по своей сути. Объяснить плюсы и минусы обеих реализаций.*

У чётного числа последний бит равен `0`. Если сделать побитовое `И` чётного числа и `1`, то мы получим `0`. На этом принципе основан данный метод.
Побитовое `И` более быстрая операция, чем деление, поэтому на некоторых компиляторах, которые не делают оптимизацию при взятии остатка от `2`, данный метод будет работать быстрее.

С++: Исходный код: [ссылка](https://github.com/mamkad/wargaming_tasks/blob/main/wargaming/wargaming/IsEven.h)

## Задание 2
*На языках Python(2.7) и/или С++, написать минимум по 2 класса реализовывающих циклический буфер FIFO. Объяснить плюсы и минусы каждой реализации.*

**Реализация на основе статического массива**

Реализация на основе статического массива позволяет избежать проблем с памятью и увеличивает скороть работы, так как не используется динамическая память. Сложность вставки и удаления составляет `O(1)`, так как чтение и запись происходит по индексам из ячеек массива. Главный минус реализация состоит в том, что нельзя изменять размер буфера во время выполнения программы.

С++: Исходный код: [ссылка](https://github.com/mamkad/wargaming_tasks/blob/main/wargaming/wargaming/sRbuffer.h)

**Реализация на основе динамического массива**

Реализация на основе динамического массива, позволяет изменять размер буфера с помощью метода `Resize()` во время выполнения программы, что повышает гибкость класса. Метод `Resize()` работает за `O(n)`, поскольку при создании нового буфера нужно сохранить старые значения и записать их в новый буфер. Использование динамической памяти снижает скорость работы и безопасность класса. При выделении памяти для буфера нужно проверять, что память выделилась успешно. Сложность вставки и удаления также составляет `O(1)`, так как чтение и запись происходит по индексам из ячеек массива.

С++: Исходный код: [ссылка](https://github.com/mamkad/wargaming_tasks/blob/main/wargaming/wargaming/dRBuffer.h)

**Реализация на основе связного списка**

Реализация на основе связного списка позволяет быстро менять доступное количество элементов для чтения и записи, мы просто меняем переменную длины буфера. Когда мы добавляем (или удаляем) элемент, этот элемент загружается в память( или удаляется из неё), что может быть удобно. Например, если количество элементов в буфере прописано достаточно большое, а мы прочитали большую их часть(удалили из памяти), это значит, что буфер не будет занимать лишнее место для уже прочитанных значений, память выделется лишь при добавлении нового элемента. Но постоянные запросы на выделение памяти занимают время. При выделении памяти для элемента нужно проверять, что память выделилась успешно. Также памяти для хранения одного элемента нужно больше, чем на массиве, так как нужно хранить самое значение, а также указатели на узлы.

С++: Исходный код: [ссылка](https://github.com/mamkad/wargaming_tasks/blob/main/wargaming/wargaming/ldRBuff.h)

## Задание 3
*На языке Python или С/С++, написать функцию, которая быстрее всего (по процессорным тикам) отсортирует данный ей массив чисел.
Массив может быть любого размера со случайным порядком чисел (в том числе и отсортированным).
Объяснить почему вы считаете, что функция соответствует заданным критериям.*

**Реализация быстрой сортировки**
С++: Исходный код: [ссылка](https://github.com/mamkad/wargaming_tasks/blob/main/wargaming/wargaming/Sort.h)

Быстрая сортировка используется намного чаще, чем другие. Это связано с тем, что алгоритм быстрой сортировки легко реализовать, также алгоритм хорошо работает на различных видах данных и во многих случаях требует меньше ресурсов, чем другие методы сортировки. Алгоритм принадлежит к категории обменных сортировок, Время, затрачиваемое на сортировку `n` элементов, пропорционально `N*log(N)`. Неустойчивость это недостаток данной сортировки. На некоторых видах данных для его выполнения в худшем случае потребуется `N^2` операций.
Также быстрая сортировка чувствительна к реализации.
