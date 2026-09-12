/* Демо 5. Хто виділяє буфер: двофазний виклик і поле cb (cbSize).
   Збірка: cl /utf-8 /W4 demo05_buffer.c                                    */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

   /* Вивід UTF-16 рядка в UTF-8 консоль (працює і при перенаправленні). */
static void put_w(const wchar_t* s)
{
    char buf[1024];
    int n = WideCharToMultiByte(CP_UTF8, 0, s, -1, buf, sizeof(buf), NULL, NULL);
    if (n > 0) fputs(buf, stdout);
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    /* Фаза 1: питаємо розмір. Дані не передаються. */
    DWORD need = GetCurrentDirectoryW(0, NULL);
    printf("фаза 1: GetCurrentDirectoryW(0, NULL) -> %lu WCHAR (з нульовим)\n", need);

    /* Фаза 2: власне дані у власний буфер. */
    wchar_t* buf = (wchar_t*)malloc(need * sizeof(wchar_t));
    DWORD got = GetCurrentDirectoryW(need, buf);
    printf("фаза 2: записано %lu символів: ", got);
    put_w(buf);
    printf("\n");
    free(buf);

    /* Замалий буфер: функція не пише за межі, а повертає потрібний розмір. */
    wchar_t tiny[4];   /* small - це макрос у Windows SDK, назвати так не можна */
    DWORD r = GetCurrentDirectoryW(4, tiny);
    printf("\nбуфер на 4 WCHAR -> повернуто %lu\n", r);
    printf("  %lu > 4, отже це не довжина результату, а вимога до буфера\n", r);

    /* Поле cb: структура сама повідомляє системі свою версію. */
    STARTUPINFOW si = { sizeof(si) };
    printf("\nSTARTUPINFOW: si.cb = %lu (це sizeof структури)\n", si.cb);
    return 0;
}
