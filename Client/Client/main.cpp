#include <Windows.h>
#include <iostream>

int main(void)
{
    HANDLE hPipe;
    DWORD dwWritten;
    DWORD dwProcessId;

    hPipe = CreateFile(TEXT("\\\\.\\pipe\\Pipe"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        // Получаем Process ID клиента
        if (GetNamedPipeClientProcessId(hPipe, &dwProcessId))
        {
            std::cout << "Client Process ID: " << dwProcessId << std::endl;
        }

        WriteFile(hPipe,
            "Hello Pipe\n",
            12,   // = length of string + terminating '\0' !!!
            &dwWritten,
            NULL);

        CloseHandle(hPipe);
    }

    return (0);
}
