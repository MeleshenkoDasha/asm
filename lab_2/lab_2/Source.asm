__asm {
		mov eax, a;
		mov ebx, 3
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
		pop ebx; ebx = a / 4 + 1 //���� �������� ������ �������, �� �������� �� ����� ����������� � 
			������� ebx
			cdq
			idiv ebx; eax = (2 * c + d - 52) / (a / 4 + 1) //�������� eax � ebx ������� � ��������� ���������� � 
			eax
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