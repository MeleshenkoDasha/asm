#include <iostream>
using namespace std;

int get_value(bool positive = false) { // проверка для размера массива и элемента массива
    int value;
    while (true) {
        if (!(cin >> value) || (cin.peek() != '\n') || (positive && value < 0)) {
            cin.clear();                // если не удовлетворяет первому и второму условиям, то возвращаем cin в 'обычный' режим работы
            cin.ignore(10000, '\n');    // и удаляем значения предыдущего ввода из входного буфера
            cout << "Error! Enter the value again.\n";
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}



int main()
{
    bool error = false;
    cout << "The multiplication of the array elements A={a[i]} satisfying the condition: b <= a[i] <= d.\n";
    cout << "Enter the size: ";
    int massize = get_value(true);

    int* mas = new int[massize];
    for (int i = 0; i < massize; ++i) {
        cout << "Enter mas[" << i + 1 << "]: ";
        *(mas + i) = get_value();
    }

    cout << "Enter the left border b: ";
    int b = get_value();
    cout << "Enter the right border d: ";
    int d = get_value();

    int result;

    __asm {
        xor esi, esi; //подготовим регистр индекса в массиве
        mov edx, 1; edx = 1
        mov ebx, mas; ebx //указывает на начало масссива
        mov ecx, massize; //счётчик цикла по всем элементам массива

        jecxz END; //завершить, если длина массива 0

        begin_loop:
        mov eax, [ebx + esi * 4]; //определяем текущий элемент
            cmp eax, d; //сравнение a[i] и d
            jg end_loop; //если больше, то завершаем цикл
            cmp eax, b; //сравнение a[i] и b
            jl end_loop; //если меньше, то завершаем цикл
            imul edx, eax; edx *= mas[i]

            jo of; //ошибка переполнения

            end_loop :
        inc esi; //переход к следующему элементу массива
            loop begin_loop; //повторяем цикл для всех элементов массива
            jmp END

            of : mov error, 1

            END : mov result, edx
    }

    if (error)
        cout << "Overflow" << endl;
    else {
        int count = 1;

        if (massize == 1 && !(mas[0] > b && mas[0] < d)) {
            --count;
            --result;
        }

        cout << "Result Assembly: " << result << endl;

        for (int i = 0; i < massize; ++i) {
            if (mas[i] > b && mas[i] < d) {
                count *= mas[i];
            }
        }

        cout << "Result C++: " << count << endl;
    }

    delete[] mas;
}
