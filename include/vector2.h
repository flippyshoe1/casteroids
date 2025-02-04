#ifndef VECTOR2_H
#define VECTOR2_H

// the vector2 definitions are there, so include that
#include <raylib.h>
#include <stdbool.h>

/* "cheap" functions */
Vector2 Vector2_Add(Vector2 a, Vector2 b);
Vector2 Vector2_SMul(Vector2 a, float scalar);

bool Vector2_Cmp(Vector2 a, Vector2 b);

/* "expensive" functions */
Vector2 Vector2_FromPolar(float length, float rotation);
Vector2 Vector2_Rotated(Vector2 a, float rotation);
Vector2 Vector2_Clamp(Vector2 a, Vector2 limit);
Vector2 Vector2_Normalize(Vector2 a);
Vector2 Vector2_LimitLength(Vector2 a, float len);

float Vector2_Len(Vector2 a);
float Vector2_Rot(Vector2 a);

void Vector2_Wrap(Vector2 *within, Vector2 border);

#endif
