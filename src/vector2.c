#include "vector2.h"

#include <math.h>

Vector2
Vector2_Add(Vector2 a, Vector2 b){
  return (Vector2){a.x+b.x, a.y+b.y};
}

Vector2
Vector2_SMul(Vector2 a, float scalar){
  return (Vector2){a.x*scalar, a.y*scalar}; 
}

bool
Vector2_Cmp(Vector2 a, Vector2 b){
  return a.x==b.x&&a.y==b.y;
}

Vector2
Vector2_FromPolar(float length, float rotation){
  return (Vector2){length*cosf(DEG2RAD*rotation), length*sinf(DEG2RAD*rotation)};
}

void
Vector2_Wrap(Vector2 *within, Vector2 border){
  within->x = (within->x<0) ? border.x : within->x;
  within->x = (within->x>border.x) ? 0 : within->x;

  within->y = (within->y<0) ? border.y : within->y;
  within->y = (within->y>border.y) ? 0 : within->y;
}

float
Vector2_Len(Vector2 a){
  return sqrt(pow(a.x,2 )+pow(a.y, 2));
}

float
Vector2_Rot(Vector2 a){
  return atan(a.y/a.x)*(180.0f/PI);
}

Vector2
Vector2_Rotated(Vector2 a, float rotation){
  return Vector2_FromPolar(Vector2_Len(a), rotation);
}

Vector2
Vector2_Clamp(Vector2 a, Vector2 limit){
  if(Vector2_Len(a)>Vector2_Len(limit))
    return Vector2_Rotated(limit, Vector2_Rot(a));
  else
    return a;
}

Vector2
Vector2_Normalize(Vector2 a){
  float len = Vector2_Len(a);
  return (Vector2){a.x/len, a.y/len};
}

Vector2
Vector2_LimitLength(Vector2 a, float len){
  if(Vector2_Len(a)>len){
    Vector2 t = Vector2_Normalize(a);
    t = Vector2_SMul(t, len);
    return t;
  }
  else
    return a;
}
