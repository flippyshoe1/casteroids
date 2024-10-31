#include "vector2.h"

#include <raylib.h>

#include <math.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

/*--------------------------------------------------------/
| TODO:                                                   |
| - make the bullet shooting semi-automatic               |
| - add enemies, figure out how to do collision detection |
| - figure out how to do text labels                      |
/--------------------------------------------------------*/

// debug
#define SHIP_RAD 16
#define RSPEED 5
#define DEBUG_AMP 20
#define DEBUG_FPS 60

// game vars
#define SPEED_LIM 5
#define THRUST_AMP 15

// bullet specific
#define BULLET_TIME 5
#define BULLET_SPEED 250

// shortcuts
#define CLAMP(x, min, max) {x=(x<min)?max:(x>max)?min:x;}

// window constants
static const Vector2 screens = (Vector2){800, 450};

typedef struct Entity {
  Vector2 position;
  Vector2 velocity;
  Vector2 acceleration;
  float rotation;
} Entity;

typedef struct Ship {
  Entity body;
} Ship;

struct {
  Entity *bullet;
  float timer;
} bullets[256];

Entity *
CreateBullet(Entity *spawner){
  int index = -1;
  for(int i=0;i<256;++i)
    if(!bullets[i].bullet)
      index=i;

  if(index==-1) return NULL;

  bullets[index].bullet = (Entity *)malloc(sizeof(Entity));
  if(!bullets[index].bullet) return NULL;

  // temporary set, make adjustable timers later
  bullets[index].timer = BULLET_TIME;

  Entity *b = bullets[index].bullet;
  b->rotation = spawner->rotation;
  b->position = spawner->position;
  b->velocity = Vector2_FromPolar(BULLET_SPEED, b->rotation);

  return b;
}

void
MoveNKillBullets(float delta){
  Entity *b = NULL;
  int handle=0;
  for(int i=0;i<256;++i)
    if(bullets[i].bullet){
      b = bullets[i].bullet;
      Vector2 vel=Vector2_SMul(b->velocity, delta);
      b->position = Vector2_Add(b->position, vel);
      Vector2_Wrap(&b->position, screens);
      
      bullets[i].timer -= delta;
      // keep an eye on this...
      if(bullets[i].timer<=0) { free(b); b=NULL; bullets[i].bullet = NULL; }
      handle+=1;
    }

  printf("Handled %d bullets!\n", handle);
}

void
dDraw_Bullets(){
  Entity *b = NULL;
  for(int i=0;i<256;++i)
    if(bullets[i].bullet){
      b=bullets[i].bullet;
      DrawCircle(b->position.x, b->position.y, SHIP_RAD/4, MAGENTA);
    }
}

void // debug function
dShip_Draw(Entity *s){
  // circle dictates the ship itself
  DrawCircle(s->position.x, s->position.y, SHIP_RAD, DARKGRAY);
  // red line shows the velocity of the ship
  Vector2 vel = Vector2_SMul(s->velocity, DEBUG_AMP);
  DrawLine(s->position.x, s->position.y,
	   s->position.x+vel.x, s->position.y+vel.y,
	   RED);
  // green shows acceleration
  Vector2 acc = Vector2_SMul(s->acceleration, DEBUG_AMP);
  DrawLine(s->position.x, s->position.y,
	   s->position.x+acc.x, s->position.y+acc.y,
	   GREEN);
  // blue shows rotation
  Vector2 rot = Vector2_FromPolar(2*DEBUG_AMP, s->rotation);
  DrawLine(s->position.x, s->position.y,
	   s->position.x+rot.x, s->position.y+rot.y,
	   BLUE);
}

int main(){
  /* initialisation */  

  Ship player;
  memset(&player, 0, sizeof(Ship));
  player.body.position = (Vector2){screens.x/2, screens.y/2};

  // initialise bullet array
  for(int i=0;i<256;++i){
    bullets[i].bullet = NULL;
    bullets[i].timer = 0;
  }
  
  // start the window, set fps with raylib (convenient!)
  InitWindow(screens.x, screens.y, "Hello world... right?");
  SetTargetFPS(DEBUG_FPS);

  /* window loop */  
  while(!WindowShouldClose()){
    /* input */
    if(IsKeyDown(KEY_RIGHT)) { player.body.rotation += RSPEED; }
    if(IsKeyDown(KEY_LEFT))  { player.body.rotation -= RSPEED; }
    CLAMP(player.body.rotation, 0.0, 359.0);

    if(IsKeyDown(KEY_UP))    player.body.acceleration.y = THRUST_AMP;
    else                     player.body.acceleration.y = 0;

    if(IsKeyDown(69))        (void)CreateBullet(&player.body);
    
    /* logic */
    // get deltatime
    float delta = GetFrameTime();

    // calculate player velocity, add it to the player
    Vector2 acc = Vector2_SMul(player.body.acceleration, delta);
    acc = Vector2_FromPolar(acc.y, player.body.rotation);
    player.body.velocity = Vector2_Add(player.body.velocity, acc);
    // add velocty to the player
    player.body.velocity = Vector2_LimitLength(player.body.velocity, SPEED_LIM);
    player.body.position = Vector2_Add(player.body.velocity, player.body.position);

    Vector2_Wrap(&player.body.position, screens);

    // bullets
    MoveNKillBullets(delta);
    
    /* drawing */
    BeginDrawing();

    ClearBackground(RAYWHITE);
    dShip_Draw(&player.body);
    dDraw_Bullets();

    EndDrawing();
  }

  /* de-initialisation */
  CloseWindow();
  return 0;
}

