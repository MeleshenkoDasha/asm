#include <iostream>
int get_value() {
	int value;
	std::cout << "Enter the value:\n";
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
int main() {
	int a, c, d, res;
	bool ezf = 0, eof = 0;
	a = get_value();
	c = get_value();
	d = get_value();
	__asm {
		mov eax, a;
		mov ebx, 4
			cdq
			idiv ebx //�������� a ������� �� 4
			add eax, 1 //����������� 1
			push eax; push a / 4 + 1 //��������� ���������� � ����
			mov eax, 2 //����������� �������� 2 � ������� eax
			imul c //��������� �� c
			jo error_of;
		add eax, d //� ���������� ����������� �������� d
			jo error_of;
		sub eax, 52 //���������� 52
			jo error_of;
		pop ebx; ebx = a / 4 + 1 //���� �������� ������ �������, �� �������� �� ����� ����������� � ������� ebx
			cdq
			idiv ebx; eax = (2 * c + d - 52) / (a / 4 + 1) //�������� eax � ebx ������� � ��������� ���������� � eax
			jz error_zf
			mov res, eax //eax ���������� � ���������� res
			jmp end

			error_zf :
		mov dl, 1
			mov ezf, dl
			jmp end; ����� � �������� �� 0
			error_of:
		mov dl, 1
			mov eof, dl
			pop eax
			jmp end; ����� � �������������, ���� ���� �� ����
			end :
	}
	if (ezf) std::cout << "Division by zero.\n";
	else if (eof == 1) std::cout << "Overflow error.\n";
	else {
		std::cout << "ASM: " << res << std::endl;
		std::cout << "C++: " << (2 * c + d - 52) / (a / 4 + 1) << std::endl;
	}
}