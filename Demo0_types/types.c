#include <windows.h>
#include <stdio.h>

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    printf("тип        розмір   насправді це\n");
    printf("--------------------------------------------------\n");
    printf("BYTE       %2zu       unsigned char\n", sizeof(BYTE));
    printf("WORD       %2zu       unsigned short\n", sizeof(WORD));
    printf("DWORD      %2zu       unsigned long   <- НЕ int\n", sizeof(DWORD));
    printf("BOOL       %2zu       int             <- НЕ bool\n", sizeof(BOOL));
    printf("HANDLE     %2zu       void*\n", sizeof(HANDLE));
    printf("SIZE_T     %2zu       залежить від розрядності\n", sizeof(SIZE_T));
    printf("WCHAR      %2zu       UTF-16, а не UTF-32\n", sizeof(WCHAR));
    printf("\nTRUE = %d, FALSE = %d\n", TRUE, FALSE);

    /* Пастка, заради якої існує це демо: BOOL - це int.
       Функція має право повернути будь-яке значення != 0 як "успіх". */
    BOOL result = 2;
    printf("\nBOOL result = 2;\n");
    printf("  if (result)          -> %s\n", result ? "виконається" : "не виконається");
    printf("  if (result == TRUE)  -> %s   <- ось де ховається помилка\n",
        (result == TRUE) ? "виконається" : "НЕ виконається");
    return 0;
}