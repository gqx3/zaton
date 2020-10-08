#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <GL/GL.h>
#include <GL/glcorearb.h>
#include <GL/wglext.h>

#define window_width 1280
#define window_height 720

void Print_Gl_Info()
{

    FILE* file_log;
    fopen_s(&file_log, "boot_log.txt", "w+");

    fprintf(file_log, "Vendor: %s.\n", glGetString(GL_VENDOR));
    fprintf(file_log, "Renderer: %s.\n", glGetString(GL_RENDERER));
    fprintf(file_log, "Version: %s.\n", glGetString(GL_VERSION));
    fprintf(file_log, "GLSL Version: %s.\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    fclose(file_log);
}

PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FVPROC glUniform3fv;
PFNGLUNIFORM4FVPROC glUniform4fv;
PFNGLUNIFORM4FPROC glUniform4f;

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

void load_opengl_extensions()
{
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
}

const char lpszAppName[] = "OpenGL";

HDC hDC;
HGLRC hRC;
bool quit = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            hDC = GetDC(hWnd);
            PIXELFORMATDESCRIPTOR pfd;

            // Установим временный формат пикселей
            // создадим и устанвоим временный контекст
            // для того чтобы могли получить доступ к wgl функциям
            SetPixelFormat(hDC, 1, &pfd);
            hRC = wglCreateContext(hDC);
            wglMakeCurrent(hDC, hRC);

            // Загрузим расширения
            load_opengl_extensions();
            // После удалим временный контекст

	    wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hRC);
            ReleaseDC(hWnd, hDC);

            // Создадим теперь уже контекст с нужным нам форматом пикселей
            // мне нужне вот такой формат пикселей

                // далее нужно запросить формат пикселей описанный выше
                // именно с помощью функции wglChoosePixelFormatARB
                // а для этого ее еще нужно получить
                // поэтому сосздадим временный контекст и получим ее

            int nPixCount;
            int nPixFormat;
            
            int pixAttribs[] = {
                WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
                WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
                WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB,         32,
                WGL_DEPTH_BITS_ARB,         24,
                WGL_STENCIL_BITS_ARB,       8,
                0
            };

            wglChoosePixelFormatARB(hDC, &pixAttribs[0], NULL, 1, &nPixFormat, (UINT*)&nPixCount);

            if (nPixFormat != -1)
            {
                SetPixelFormat(hDC, nPixFormat, &pfd);
                GLuint attribs[] = {
                    WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                    WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                    WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                    0,0, // NULL termination
                };


                hRC = wglCreateContextAttribsARB(hDC, 0, attribs);

                wglMakeCurrent(hDC, hRC);
            }
            break;
        }
            
        case WM_KEYDOWN:
            if (VK_ESCAPE == wParam)
                DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            wglMakeCurrent(hDC, NULL);
            wglDeleteContext(hRC);
            ReleaseDC(hWnd, hDC);
            PostQuitMessage(0);
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow)
{
    MSG msg;
    WNDCLASS wc;
    HWND hWnd;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC) WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // Фоновая кисть для окна OpenGL не требуется
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = lpszAppName;
    if (RegisterClass(&wc) == 0)
    {
        return false;
    }

    hWnd = CreateWindow(lpszAppName,
                        lpszAppName,
                        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPCHILDREN,
                        100, 100,
                        window_width, window_height,
                        NULL,
                        NULL,
                        hInstance,
                        NULL);
    if (hWnd == NULL)
        return false;
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);


    Print_Gl_Info();

    while (!quit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            quit = true;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.14f, 0.14f, 0.14f, 0); // #2e2e2e
        SwapBuffers(hDC);
    }
    return msg.wParam;
}

