__asm {
		mov eax, a;
		mov ebx, 3
			cdq
			idiv ebx //значение a делится на 4
			add eax, 1 //добавляется 1
			push eax; push a / 4 + 1 //результат помещается в стек
			mov eax, 2 //перемещение значения 2 в регистр eax
			imul c //умножение на c
			jo error_of;
		add eax, d //к результату добавляется значение d
			jo error_of;
		sub eax, 52 //вычитается 52
			jo error_of;
		pop ebx; ebx = a / 4 + 1 //если операция прошла успешно, то значение из стека извлекается в 
			регистр ebx
			cdq
			idiv ebx; eax = (2 * c + d - 52) / (a / 4 + 1) //значения eax и ebx делятся и результат помещается в 
			eax
			jz error_zf
			mov res, eax //eax копируется в переменную res
			jmp end

			error_zf :
		mov dl, 1
			mov ezf, dl
			jmp end; выход с делением на 0
			error_of:
		mov dl, 1
			mov eof, dl
			pop eax
			jmp end; выход с переполнением, если стек не пуст
			end :
	}