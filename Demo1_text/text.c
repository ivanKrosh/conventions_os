/* Демо 2. ANSI проти Unicode: одна функція - дві реалізації.
   Збірка: cl /utf-8 /W4 demo02_text.c user32.lib
   Запуск з аргументом gui додає MessageBoxW.                              */
#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    SetConsoleOutputCP(CP_UTF8);

    const char* a = "Привіт, світ";
    const wchar_t* w = L"Привіт, світ";

    printf("strlen(a)  = %zu (байтів у char-рядку)\n", strlen(a));
    printf("wcslen(w)  = %zu (елементів WCHAR)\n", wcslen(w));
    printf("sizeof(L\"Привіт, світ\") = %zu (байтів у WCHAR-рядку)\n",
        sizeof(L"Привіт, світ"));

    /* A-шлях: байти віддаються консолі як є - результат залежить від
       кодової сторінки, а не від коду програми. */
    printf("\n[printf, char*] %s\n", a);

    /* W-шлях: система отримує UTF-16 і сама вирішує, як це намалювати. */
    DWORD written = 0;
    WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), w, (DWORD)wcslen(w), &written, NULL);
    printf("   <- WriteConsoleW, %lu символів\n", written);


    if (argc > 1 && strcmp(argv[1], "gui") == 0)
        MessageBoxW(NULL, w, L"MessageBoxW", MB_OK | MB_ICONINFORMATION);
    return 0;
}
