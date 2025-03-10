#include <windows.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <gdiplus.h>
#include <string>
#include <cstdlib>
#include <ctime>

#pragma comment(lib, "winmm.lib") // Para reproduzir sons
#pragma comment(lib, "gdiplus.lib") // Para GDI+

using namespace Gdiplus;

// Função para exibir um pop-up sem som do sistema
void ShowPopup(const std::string& message) {
    // Desativa o som do sistema para o pop-up
    MessageBeep(0xFFFFFFFF); // Som silencioso
    MessageBox(NULL, message.c_str(), "Result", MB_OK | MB_ICONINFORMATION);
}

// Função para carregar uma imagem PNG como HBITMAP
HBITMAP LoadPNGAsHBITMAP(const wchar_t* filePath) {
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    HBITMAP hBitmap = NULL;
    Image* image = new Image(filePath);
    if (image->GetLastStatus() == Ok) {
        Bitmap* bitmap = new Bitmap(image->GetWidth(), image->GetHeight(), PixelFormat32bppARGB);
        Graphics graphics(bitmap);
        graphics.DrawImage(image, 0, 0, image->GetWidth(), image->GetHeight());

        bitmap->GetHBITMAP(Color(255, 255, 255), &hBitmap);
        delete bitmap;
    }
    delete image;
    GdiplusShutdown(gdiplusToken);

    return hBitmap;
}

// Função principal da janela
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HBITMAP hBitmap = NULL;

    switch (uMsg) {
    case WM_CREATE: {
        // Cria o botão "Hunt!"
        CreateWindow(
            "BUTTON", "Hunt!", WS_VISIBLE | WS_CHILD,
            150, 300, 100, 40, hwnd, (HMENU)1, NULL, NULL
        );

        // Carrega a imagem PNG
        hBitmap = LoadPNGAsHBITMAP(L"images/monster.png");
        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 1) { // Botão "Hunt!" clicado
            // Gera um número aleatório entre 0 e 99
            int randomValue = std::rand() % 100;

            if (randomValue < 3) { // 3% de chance
                ShowPopup("You got Rathalos Mantle!");
                PlaySound(TEXT("sounds/success.wav"), NULL, SND_FILENAME | SND_ASYNC); // Toca o som de sucesso
            }
            else {
                ShowPopup("You got nothing!");
                PlaySound(TEXT("sounds/failure.wav"), NULL, SND_FILENAME | SND_ASYNC); // Toca o som de falha
            }
        }
        break;
    }
    case WM_PAINT: {
        // Desenha a imagem
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        if (hBitmap) {
            HDC hdcMem = CreateCompatibleDC(hdc);
            SelectObject(hdcMem, hBitmap);

            BITMAP bmp;
            GetObject(hBitmap, sizeof(BITMAP), &bmp);
            BitBlt(hdc, 100, 50, bmp.bmWidth, bmp.bmHeight, hdcMem, 0, 0, SRCCOPY);

            DeleteDC(hdcMem);
        }

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY: {
        if (hBitmap) {
            DeleteObject(hBitmap);
        }
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Função principal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Inicializa o gerador de números aleatórios
    std::srand(std::time(nullptr));

    // Inicializa o GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Registra a classe da janela
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "HuntToolClass";
    RegisterClass(&wc);

    // Cria a janela
    HWND hwnd = CreateWindow(
        "HuntToolClass", "Hunt Tool", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    // Exibe a janela
    ShowWindow(hwnd, nCmdShow);

    // Loop de mensagens
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Finaliza o GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}