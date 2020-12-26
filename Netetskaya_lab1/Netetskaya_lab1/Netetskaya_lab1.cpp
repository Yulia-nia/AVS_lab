// Netetskaya_lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#pragma once
#include <iostream>

//  F[i] = (A[i] - B[i]) + (C[i] - D[i])

void variant_17(__int8* A, __int8* B, __int8* C, __int16* D)
{
	__int16 F[8] = { 0 };

	__asm {

		mov			ESI, A
		movq		mm2, [ESI]
		pxor  mm1, mm1
		movq		mm0, mm2	
		pcmpgtb		mm1, mm0	
		punpcklbw	mm0, mm1	
		movq		mm7, mm0	
		pxor  mm1, mm1
		movq		mm0, mm2	
		pcmpgtb		mm1, mm0	
		punpckhbw	mm0, mm1
		movq		mm6, mm0	

		
		mov			ESI, B
		movq		mm3, [ESI]
		pxor  mm1, mm1
		movq		mm0, mm3 
		pcmpgtb		mm1, mm0
		punpcklbw	mm0, mm1
		movq		mm5, mm0	
		pxor  mm1, mm1
		movq		mm0, mm3
		pcmpgtb		mm1, mm0
		punpckhbw	mm0, mm1
		movq		mm4, mm0	

		psubsw		mm7, mm5
		psubsw		mm6, mm4
		

		mov			ESI, C
		movq		mm3, [ESI]
		pxor  mm1, mm1
		movq		mm0, mm3	
		pcmpgtb		mm1, mm0	
		punpcklbw	mm0, mm1	
		movq		mm5, mm0	
		pxor  mm1, mm1
		movq		mm0, mm3	
		pcmpgtb		mm1, mm0	
		punpckhbw	mm0, mm1	
		movq		mm4, mm0	


		mov			ESI, D
		movq		mm0, [ESI]

		mov			ESI, D
		movq		mm1, [ESI + 2 * 4]	

		psubsw		mm5, mm0	
		psubsw		mm4, mm1

		paddw		mm5, mm7	
		paddw		mm4, mm6
		
		movq [F], mm5			
		movq [F + 2 * 4], mm4
	}	

	for (int i = 0; i < 8; i++)
	{
		std::cout << (A[i] - B[i]) + (C[i] - D[i]) << " ";
	}

	std::cout << "\n";

	for (int i = 0; i < 8; i++)
	{
		std::cout << F[i] << " ";
	}

	std::cout << "\n";
}

int main()
{
	__int8 A[8]{ -10, 56, 72, -4, -65, 120, 44, 2};
	__int8 B[8]{ 210, -44, 5, -78, 111, -32, 7, -11 };
	__int8 C[8]{ 5, 77, 32, 12, -67, 4, -82, 43 };
	__int16 D[8]{ 50, -300, 46, 500, -1000, 250, 2000, 10};
	
	variant_17(A, B, C, D);



	__int8 A_2[8]{ -10, 5, 19, -4, -165, 120, 82, 1 };
	__int8 B_2[8]{ 30, 94, 52, -78, 11, -32, 910, -110 };
	__int8 C_2[8]{ -5, 70, 80, 12, -7, 14, -122, 3 };
	__int16 D_2[8]{ 50, -3000, 16, 5000, -1000, 2500, 2000, 10 };

	variant_17(A_2, B_2, C_2, D_2);

	system("pause");
	return 0;
}
