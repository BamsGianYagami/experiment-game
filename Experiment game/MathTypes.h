#pragma once

#include <cmath>

/**
 * @brief Struktur vektor 2D (x, y)
 */
struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float xx, float yy) : x(xx), y(yy) {}

    static Vector2 Zero() { return Vector2(0, 0); }
};

/**
 * @brief Struktur vektor 3D (x, y, z)
 */
struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}

    static Vector3 Zero() { return Vector3(0, 0, 0); }
};

/**
 * @brief Struktur warna RGBA dengan float (0.0 - 1.0)
 */
struct Color {
    float r, g, b, a;

    Color() : r(1), g(1), b(1), a(1) {}
    Color(float rr, float gg, float bb, float aa = 1.0f) : r(rr), g(gg), b(bb), a(aa) {}

    static Color White()  { return Color(1, 1, 1, 1); }
    static Color Black()  { return Color(0, 0, 0, 1); }
    static Color Red()    { return Color(1, 0, 0, 1); }
    static Color Green()  { return Color(0, 1, 0, 1); }
    static Color Blue()   { return Color(0, 0, 1, 1); }
};

/**
 * @brief Matriks 4x4 sederhana untuk transformasi
 */
struct Matrix4x4 {
    float m[4][4];

    static Matrix4x4 Identity() {
        Matrix4x4 mat;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                mat.m[i][j] = (i == j) ? 1.0f : 0.0f;
        return mat;
    }
};

