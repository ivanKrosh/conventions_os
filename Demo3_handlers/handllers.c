/* Демо 3. Дескриптор - це не число, а дозвіл, який треба повернути.
   Збірка: cl /utf-8 /W4 demo03_handles.c
   Запуск: demo03_handles.exe        - усе закривається
           demo03_handles.exe leak   - CloseHandle "забули"                */
#include <windows.h>
#include <stdio.h>
#include <string.h>

static DWORD handles(void)
{
    DWORD n = 0;
    GetProcessHandleCount(GetCurrentProcess(), &n);
    return n;
}

int main(int argc, char** argv)
{
    SetConsoleOutputCP(CP_UTF8);
    BOOL leak = (argc > 1 && strcmp(argv[1], "leak") == 0);

    printf("режим: %s\n", leak ? "БЕЗ CloseHandle" : "з CloseHandle");
    printf("дескрипторів на старті: %lu\n", handles());

    for (int i = 0; i < 2000; i++) {
        HANDLE h = CreateFileW(L"demo03_probe.tmp",
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
        if (h == INVALID_HANDLE_VALUE) {
            printf("виклик №%d не вдався, код %lu\n", i, GetLastError());
            break;
        }
        if (!leak) CloseHandle(h);
    }

    printf("дескрипторів після 2000 відкриттів: %lu\n", handles());
    printf("\nПодивіться колонку \"Дескриптори\" у Диспетчері задач. Enter - вихід.\n");
    (void)getchar();
    return 0;
}
