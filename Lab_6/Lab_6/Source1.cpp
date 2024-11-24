//a^2/b + 21, a>b
//-a + 6, если a=b
//(ab - 12b)/a, если a<b

//a^2/b - 1, a>b
//-a + 25, если a=b
//(8ab - 2b)/a, если a<b

#include <iostream>

using namespace std;

double get_value() {
    double value;
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

bool dvz = 0;
short status;

double solve_asm(double a, double b) {
    const double inv_b1 = -1;
    const double b6 = 25;
    const double a21 = 1;
    const double inv_a12 = -2;
    const double c12 = 2;


    _asm {
        finit; //инициализация сопроцессора
        fld qword ptr[a]; ST(0) = a
        fld qword ptr[b]; ST(0) = b, ST(1) = a
        fcomi ST, ST(1); //сравнение b с a с дальнейшим установлением флагов в EFLAGS
        ja b_bigger; //переход если b больше
        jb a_bigger; //переход если a больше

        fxch ST(1); ST(0) = a, ST(1) = b
        fmul qword ptr[inv_b1]; ST(0) = a * (-1)
        fadd b6; ST(0) = -a + 25
        jmp finish

        b_bigger :
        fldz; //загрузка нуля в вершину стека сопроцессора
            fcomip ST, ST(2); //сравнение a с 0 с дальнейшим установлением флагов в EFLAGS
            jz div_by_zero;
        fmul; ST(0) = 8 * a * b
            fld qword ptr[b]; ST(0) = b, ST(1) = 8 * a * b
            fmul qword ptr[inv_a12]; ST(0) = -2 * b, ST(1) = 8 * a * b
            fadd; ST(0) = 8 * a * b - 2 * b
            fld qword ptr[a]; ST(0) = a, ST(1) = 8 * a * b - 2 * b
            fdiv; ST(0) = (8 * a * b - 2 * b) / a
            jmp finish

            a_bigger :
        fldz; //загрузка нуля в вершину стека сопроцессора
            fcomip ST, ST(1); //сравнение b с 0 с дальнейшим установлением флагов в EFLAGS
            jz div_by_zero;
        fld qword ptr[a]; ST(0) = a, ST(1) = b, ST(2) = a
            fmulp st(2), st; ST(0) = b, ST(1) = a * a
            fdiv; ST(0) = a * a / b
            fadd qword ptr[a21]; ST(0) = a * a / b - 1
            jmp finish

            div_by_zero : ; //обработка состояние деления на 0
            mov dvz, 1

            finish :; //анализируем результат
            fxam; //проверяет вершину регистрового стека ST и сообщает тип объекта, содержащегося в нём, путем установки флагов C3, C2, C0
            fstsw ax; //перекидываем swr(куда входят C3, C2, C0)  в ax
            and ax, 0100010100000000b; //обнуляем в ax все ненужные байты
            mov status, ax
    }

    return;
}

int main() {
    cout << "Enter a: ";
    double a = get_value();
    cout << "Enter b: ";
    double b = get_value();

    double x = solve_asm(a, b);

    if (dvz) {
        cout << "Divizion by zero!\n";
    }
    else {
        cout << "Result asm: " << x;
        if (status == 0)
            cout << " Unsupported format";
        if (status == 256)
            cout << " NaN";
        if (status == 1024)
            cout << " Finite number";
        if (status == 1280)
            cout << " Infinity";
        if (status == 16384)
            cout << " Zero";
        if (status == 16640)
            cout << " Empty register";
        if (status == 17408)
            cout << " An unnormalized number";

        cout << endl << "Result C++: ";

        if (a == b)
            cout << a * (-1) + 6;
        else {
            if (a > b) {
                if (b != 0)
                    cout << a * a / b - 1;
            }
            else {
                if (a != 0)
                    cout << (8 *a * b - 2 * b) / a;
            }
        }
        cout << endl;
    }

}
