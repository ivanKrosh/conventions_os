/* Демо 4. Домовленість про помилки: значення -> GetLastError -> FormatMessage.
   Збірка: cl /utf-8 /W4 demo04_error.c                                     */
#include <windows.h>
#include <stdio.h>

   /* Вивід UTF-16 рядка в UTF-8 консоль: працює і при перенаправленні у файл,
      на відміну від WriteConsoleW, якому потрібен саме дескриптор консолі. */
static void put_w(const wchar_t* s)
{
    char buf[512];
    int n = WideCharToMultiByte(CP_UTF8, 0, s, -1, buf, sizeof(buf), NULL, NULL);
    if (n > 0) fputs(buf, stdout);
}

static void explain(const char* label, DWORD code)
{
    wchar_t* text = NULL;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, code, 0, (LPWSTR)&text, 0, NULL);
    printf("%s: код %lu - ", label, code);
    if (text) {
        put_w(text);
        LocalFree(text);          /* буфер виділила система, звільняє викликач */
    }
    else {
        printf("(опису немає)\n");
    }
}

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);

    HANDLE h = CreateFileW(L"файлу-точно-немає.txt", GENERIC_READ, 0, NULL,
        OPEN_EXISTING, 0, NULL);
    printf("CreateFileW повернув: %s\n",
        (h == INVALID_HANDLE_VALUE) ? "INVALID_HANDLE_VALUE" : "дескриптор");
    explain("одразу після виклику", GetLastError());

    /* Те саме, але код помилки читаємо не одразу. */
    h = CreateFileW(L"файлу-точно-немає.txt", GENERIC_READ, 0, NULL,
        OPEN_EXISTING, 0, NULL);
    printf("\nміж викликом і GetLastError ставимо printf...\n");
    explain("після printf", GetLastError());

    h = CreateFileW(L"файлу-точно-немає.txt", GENERIC_READ, 0, NULL,
        OPEN_EXISTING, 0, NULL);
    CloseHandle(NULL);            /* "прибирання" перед читанням коду */
    explain("після CloseHandle(NULL)", GetLastError());
    return 0;
}
