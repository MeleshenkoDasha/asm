//������� �� 3 ������������ ������
//a^2/b - 1, a>b
//-a + 25, ���� a=b
//(8ab - 2b)/a, ���� a<b


#include <iostream>

using namespace std;


int get_value() {
    int value;
    while (true) {
        if (!(std::cin >> value) || (std::cin.peek() != '\n')) {
            std::cin.clear();                // ���� �� ������������� ������� � ������� ��������, �� ���������� cin � '�������' ����� ������
            std::cin.ignore(10000, '\n');    // � ������� �������� ����������� ����� �� �������� ������
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
        jmp finish; // ������� �� ����� ���������

            //a^2/b - 1, a>b
            l_bigger :
        imul eax; eax = a * a
            jo error_of; //������ �������������

            cmp ebx, 0; //��������� b � 0
            je div_by_zero; //������ ������� �� ����

            cdq
            idiv ebx; eax = a * a / b

            sub eax, 1; eax = a * a / b - 1
            mov x, eax;
        jmp finish; //������� �� ����� ���������

            //(8ab - 2b)/a, ���� a<b
            l_smaller :
        mov ecx, eax;
        imul eax, ebx; eax = a * b
            jo error_of; //������ �������������

            imul ebx, -2; ebx = -2 * b
            jo error_of; //������ �������������

            add eax, ebx; eax = 8 * a * b - 2 * b
            jo error_of; //������ �������������

            cmp ecx, 0; //��������� a � 0
            je div_by_zero; //������ ������� �� ����

            cdq
            idiv ecx; eax = (8ab - 2b) / a
            mov x, eax;
        jmp finish; //������� �� ����� ���������

            div_by_zero :
        mov error, 1
            jmp finish; //������� �� ����� ���������

            error_of :
        mov error, 2
            jmp finish; //������� �� ����� ���������

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
