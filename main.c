#include <windows.h>

#include <GL/GL.h>
#include <GL/glcorearb.h>
#include <GL/wglext.h>

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <assert.h>   /* for assert */

#include "matrix.h"

#define window_width 1280
#define window_height 720

typedef struct
{
    int width;
    int height;
}_window;

// SHADER PROGRAM
GLuint program = 0;
void Set_Matrices();

_window win;


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

static float myEyeAngle = 0.095f;    /* Angle in radians eye rotates around knight. */
static float myProjectionMatrix[16];


PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
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

        glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
        glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
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

/* Shader program */
char *load_file(const char *path);
GLuint make_shader(GLenum type, const char *source);
GLuint load_shader(GLenum type, const char *path);
GLuint make_program(GLuint shader1, GLuint shader2);
GLuint load_program(const char *path1, const char *path2);

char *load_file(const char *path) {
    FILE *file;
    fopen_s(&file, path, "rb");
    if (!file) {
        fprintf(stderr, "fopen %s failed: %d %s\n", path, errno, strerror(errno));
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);
    char *data = (char*)calloc(length + 1, sizeof(char));
    fread(data, 1, length, file);
    fclose(file);
    return data;
}

GLuint make_shader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = (GLchar*)calloc(length, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, NULL, info);
        fprintf(stderr, "glCompileShader failed:\n%s\n", info);
        free(info);
    }
    return shader;
}

GLuint load_shader(GLenum type, const char *path) {
    char *data = load_file(path);
    GLuint result = make_shader(type, data);
    free(data);
    return result;
}

GLuint make_program(GLuint shader1, GLuint shader2) {
    GLuint program = glCreateProgram();
    glAttachShader(program, shader1);
    glAttachShader(program, shader2);
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = (GLchar*)calloc(length, sizeof(GLchar));
        glGetProgramInfoLog(program, length, NULL, info);
        fprintf(stderr, "glLinkProgram failed: %s\n", info);
        free(info);
    }
    glDetachShader(program, shader1);
    glDetachShader(program, shader2);
    glDeleteShader(shader1);
    glDeleteShader(shader2);
    return program;
}

GLuint load_program(const char *path1, const char *path2) {
    GLuint shader1 = load_shader(GL_VERTEX_SHADER, path1);
    GLuint shader2 = load_shader(GL_FRAGMENT_SHADER, path2);
    GLuint program = make_program(shader1, shader2);
    return program;
}

const char lpszAppName[] = "zaton";

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
                    0,0,
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

int Init()
{
    MSG msg;
    WNDCLASSEX wcx;
    RECT rect;
    DWORD style, exStyle;
    int x, y;
    HWND hWnd;

    memset(&wcx, 0, sizeof(wcx));
    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcx.lpfnWndProc = (WNDPROC)WndProc;
    wcx.hInstance = 0;
    wcx.hIcon = NULL;
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.lpszClassName = lpszAppName;
    if (RegisterClassEx(&wcx) == 0)
    {
        printf("RegisterClassEx fail (%d)\n", GetLastError());
        return false;
    }

    // style of window
    style   = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    exStyle = WS_EX_APPWINDOW;

    // alignment window by center of screen
    x = (GetSystemMetrics(SM_CXSCREEN) - window_width)  / 2;
    y = (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2;

    rect.left   = x;
    rect.right  = x + window_width;
    rect.top    = y;
    rect.bottom = y + window_height;

    AdjustWindowRectEx (&rect, style, FALSE, exStyle);

    hWnd = CreateWindowEx(exStyle, lpszAppName, lpszAppName, style, rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, NULL);
        

    if (hWnd == NULL) {
        printf("CreateWindowEx fail (%d)\n", GetLastError());
        return false;
    }
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    // get size of a window
    GetClientRect(hWnd, &rect);
    win.width  = rect.right - rect.left;
    win.height = rect.bottom - rect.top;
    
    // set up viewport whole window
    glViewport(0, 0, win.width, win.height);
    glEnable(GL_DEPTH_TEST);

    SetCursorPos(x + win.width / 2, y + win.height / 2);


    Print_Gl_Info();

    // init some data
    program = load_program("data/shaders/basic_vertex.glsl", "data/shaders/basic_fragment.glsl");

    float vertices[] = {-1.0, -1.0, 0.0, 0.0, 1.0, 0.0, 1.0, -1.0, 0.0};
    unsigned int indices[] = {0, 1, 2};

    typedef struct Vec3
    {
        float x, y, z;
    } Vec3;

    static const Vec3 kCubeVertices[] =
    {
        {  1.0f,  1.0f, -1.0f }, /* 0 */
        { -1.0f,  1.0f, -1.0f }, /* 1 */
        { -1.0f, -1.0f, -1.0f }, /* 2 */
        {  1.0f, -1.0f, -1.0f }, /* 3 */
        {  1.0f,  1.0f,  1.0f }, /* 4 */
        { -1.0f,  1.0f,  1.0f }, /* 5 */
        { -1.0f, -1.0f,  1.0f }, /* 6 */
        {  1.0f, -1.0f,  1.0f }, /* 7 */
    };

    static const unsigned int kCubeIndices[] =
    {
        0, 2, 1,   0, 3, 2,  /* front */
        4, 3, 0,   4, 7, 3,  /* right */
        4, 1, 5,   4, 0, 1,  /* top */
        1, 6, 5,   1, 2, 6,  /* left */
        3, 6, 2,   3, 7, 6,  /* bottom */
        5, 7, 4,   5, 6, 7,  /* back */
    };

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(kCubeVertices) * sizeof(Vec3), kCubeVertices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(kCubeIndices) * sizeof(unsigned int), kCubeIndices, GL_STATIC_DRAW);

    float *ptr = 0;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // position
    glEnableVertexAttribArray( 0 );

    glBindVertexArray(0);


    double aspectRatio = (float)window_width / (float)window_height;
    double fieldOfView = 60.0; /* Degrees */
    /* World-space positions for light and eye. */
    const float eyeRadius = 70;
    //const float eyePosition[3] = { cos(myEyeAngle)*eyeRadius, 0, sin(myEyeAngle)*eyeRadius };
    const float eyePosition[3] = { 0.0, 0.0, 10.0 };

    float viewMatrix[16], modelViewProjMatrix[16];
    buildPerspectiveMatrix(fieldOfView, aspectRatio, 10, 20,  /* Znear */ myProjectionMatrix);

    buildLookAtMatrix(eyePosition[0], eyePosition[1], eyePosition[2],
        0, 0, 0,
        0, 1, 0,
        viewMatrix);

    /* modelViewProj = projectionMatrix * viewMatrix (model is identity) */
    multMatrix(modelViewProjMatrix, myProjectionMatrix, viewMatrix);

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
        glUseProgram(program);
        glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, &modelViewProjMatrix[0]);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, (sizeof(kCubeIndices)/sizeof(kCubeIndices[0])), GL_UNSIGNED_INT, NULL);
        glBindVertexArray(0);

        SwapBuffers(hDC);
    }
    return msg.wParam;
}

__int32 __cdecl main()
{
    printf("Hello friend\n");
    int result = Init();
    return result;
}
