/* Демо 6. Домовленості з оболонкою: stdout, stderr і код повернення процесу.
   Збірка: cl /utf-8 /W4 demo06_exit.c
   Запуск: demo06_exit.exe [код]                                           */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char** argv)
{
    SetConsoleOutputCP(CP_UTF8);

    int code = (argc > 1) ? atoi(argv[1]) : 0;

    fprintf(stdout, "stdout: результат роботи - його можна передати далі\n");
    fprintf(stderr, "stderr: діагностика - її має бачити людина\n");
    fprintf(stderr, "argc = %d, завершуюсь з кодом %d\n", argc, code);
    return code;
}
