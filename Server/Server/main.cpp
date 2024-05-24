#include <Windows.h>
#include <iostream>

int main(void)
{
    HANDLE hPipe;
    char buffer[1024];
    DWORD dwRead;
    DWORD dwProcessId;

    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Pipe"),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        1024 * 16,
        1024 * 16,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL);
    while (hPipe != INVALID_HANDLE_VALUE)
    {
        if (ConnectNamedPipe(hPipe, NULL) != FALSE) // ������� ����������� �������
        {
            // �������� Process ID �������
            if (GetNamedPipeClientProcessId(hPipe, &dwProcessId))
            {
                std::cout << "Client Process ID: " << dwProcessId << std::endl;
            }

            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
            {
                /* add terminating zero */
                buffer[dwRead] = '\0';

                /* do something with data in buffer */
                printf("%s", buffer);
            }
        }

        DisconnectNamedPipe(hPipe);
    }

    return 0;
}
