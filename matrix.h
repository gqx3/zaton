#ifndef AFISKON_LINEARALG_H
#define AFISKON_LINEARALG_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define DEG2RAD (M_PI / 180.0f)


#define UNUSED(x) (void)(x)

#define U(x) (x)

#define V(x) (1.0f - (x))

typedef struct Matrix
{
    float m[16];
} Matrix;

typedef union Vector
{
    float v[4];
    struct {
        float x, y, z, w;
    };
} Vector;

Vector vectorNull();

Vector vectorAdd(Vector v1, Vector v2);
Vector vectorMul(Vector v, float n);
void vectorNormalizeInplace(Vector* v);
float vectorDot(Vector v1, Vector v2);
Vector vectorCross(Vector v1, Vector v2);

Matrix matrixIdentity();
Matrix matrixPerspective(float fovy, float aspect, float zNear, float zFar);
Matrix matrixOrthogonal(float left, float right, float bottom, float top);
Matrix matrixLookAt(Vector eye, Vector center, Vector up);

Vector matrixMulVec(const Matrix* m, const Vector* v);
Matrix matrixMulMat(const Matrix* m1, const Matrix* m2);
Matrix matrixRotate(const Matrix* m, float angle,
	float axis_x, float axis_y, float axis_z);
void matrixScaleInplace(Matrix* m, float x, float y, float z);
void matrixTranslateInplace(Matrix* m, float x, float y, float z);

#endif // AFISKON_LINEARALG_H