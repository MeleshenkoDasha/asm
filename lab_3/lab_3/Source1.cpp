//Задание на 3 лабораторную работу
//a^2/b - 1, a>b
//-a + 25, если a=b
//(8ab - 2b)/a, если a<b


#include <iostream>

using namespace std;


int get_value() {
    int value;
    while (true) {
        if (!(std::cin >> value) || (std::cin.peek() != '\n')) {
            std::cin.clear();                // если не удовлетворяет первому и второму условиям, то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(10000, '\n');    // и удаляем значения предыдущего ввода из входного буфера
            std::cout << "Error! Enter the value again.\n";
        }
        else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}


void print(int a, int b, int x) {

    cout << "Result asm: " << x << endl;

    cout << "Result C++: ";

    if (a == b)
        cout << a * (-1) + 25;
    else {
        if (a > b) {
            if (b != 0)
                cout << a * a / b - 1;
        }
        else {
            if (a != 0)
                cout << (8 * a * b - 2 * b) / a;
        }
    }
    cout << endl;
}


int main()
{
    int a, b, x, error;
    cout << "Enter a: ";
    a = get_value();
    cout << "Enter b: ";
    b = get_value();

    __asm {
        mov eax, a; eax = a
        mov ebx, b; ebx = b

        cmp eax, ebx;
        jg l_bigger; eax > ebx
            jl l_smaller; eax < ebx

            imul eax, -1; eax = a * (-1)
            add eax, 6; eax = -a + 25
            mov x, eax;
        jmp finish; // переход на конец программы

            //a^2/b - 1, a>b
            l_bigger :
        imul eax; eax = a * a
            jo error_of; //ошибка переполенения

            cmp ebx, 0; //сравнение b и 0
            je div_by_zero; //ошибка деления на ноль

            cdq
            idiv ebx; eax = a * a / b

            sub eax, 1; eax = a * a / b - 1
            mov x, eax;
        jmp finish; //переход на конец программы

            //(8ab - 2b)/a, если a<b
            l_smaller :
        mov ecx, eax;
        imul eax, ebx; eax = a * b
            jo error_of; //ошибка переполенения

            imul ebx, -2; ebx = -2 * b
            jo error_of; //ошибка переполенения

            add eax, ebx; eax = 8 * a * b - 2 * b
            jo error_of; //ошибка переполенения

            cmp ecx, 0; //сравнение a и 0
            je div_by_zero; //ошибка деления на ноль

            cdq
            idiv ecx; eax = (8ab - 2b) / a
            mov x, eax;
        jmp finish; //переход на конец программы

            div_by_zero :
        mov error, 1
            jmp finish; //переход на конец программы

            error_of :
        mov error, 2
            jmp finish; //переход на конец программы

            finish :
    }


    if (error == 1) {
        cout << "Division by zero\n";
        return 0;
    }
    if (error == 2) {
        cout << "Overflow\n";
        return 0;
    }

    print(a, b, x);

    return 0;
}
