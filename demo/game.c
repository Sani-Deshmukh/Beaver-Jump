#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_ttf.h>

#include "asset.h"
#include "asset_cache.h"
#include "collision.h"
#include "forces.h"
#include "sdl_wrapper.h"
#include "body.h"
#include "SDL2/SDL_mixer.h"

const vector_t MIN = {0, 0};
const vector_t MAX = {1000, 500};
const vector_t USER_1_CENTER = {450, 0};
const vector_t USER_2_CENTER = {550, 0};
const vector_t REPULSE = {.x = 100, .y = 100};
const vector_t INV_IMPULSE = {.x = 3, .y = 3};
const SDL_Rect text_box = {.x = 20, .y = 20, .w = 100, .h = 100};
const SDL_Rect SHIELD_BOX_1 = {.x = 500, .y = 20, .w = 100, .h = 50};
const SDL_Rect SHIELD_BOX_2 = {.x = 500, .y = 80, .w = 100, .h = 50};
const size_t ROW_SEPARATION = 85;
const size_t MIN_TILES_PER_ROW = 3;
const size_t MAX_TILES_PER_ROW = 5;
const size_t INITIAL_NUM_ROWS = 4;
const size_t HEIGHT_TO_SCORE_RATIO = 2;
const size_t BEAVER_MASS = 1;
const double GRAVITY = 9.8;
const char *ROCKET_BGD_FILEPATH = "assets/rocket.png";
const double REG_TILE_VEL = -700.0;
const double SPRING_TILE_VEL = -1500.0;
const double ROCKET_TILE_VEL = -3000.0;

const size_t INITIAL_LOWEST_ROW = 50;

const size_t TILE_WIDTH = 100;
const size_t TILE_HEIGHT = 30;
const size_t SPRING_TILE_HEIGHT = 60;

const size_t DEFAULT_TILE_X = 0;
const size_t BREAK_TILES_PROBABILITY = 5;
const size_t BREAK_TILES_SELECT = 1;
const size_t SPRING_TILES_PROBABILITY = 5;
const size_t SPRING_TILES_SELECT = 1;
const size_t MOVE_TILES_PROBABILITY = 5;
const size_t MOVE_TILES_SELECT = 1;
const size_t MOVE_TILES_PER_ROW = 1;
const size_t SPECIAL_TILES_PROBABILITY = 5;
const size_t SPECIAL_TILES_SELECT = 1;

const size_t MAX_TILE_X_VELOCITY = 300;
const size_t MIN_TILE_X_VELOCITY = 200;
const size_t TILE_Y_VELOCITY = 0;

const double ACCEL = 500;
const double resting_speed = 300;
const size_t BEAVER_SIZE = 50;
const double INITIAL_Y_VEL = 400;
const double BOUNCE_Y_VEL = 10;
const double ELASTICITY = 1;
const double PLAYER_SAFE_RADIUS = BEAVER_SIZE * 2;
const double invader_velocity = 100;
const vector_t INVADER_BULLET_VEL = {0, -200};
const double INVADER_SIZE = 50;
const size_t CIRC_NPOINTS = 4;
const double BULLET_MASS = 10;
const double BULLET_RADIUS = 10;
const double SCORE_TILL_INVADER = 1000;
const size_t SPAWN_TIME = 1000;
const rgb_color_t PLAYER_COLOR = (rgb_color_t){1, 1, 1};
const rgb_color_t TILE_COLOR = (rgb_color_t){0, 0, 1};
const rgb_color_t TEXT_COLOR = (rgb_color_t){1, 0, 0};
const rgb_color_t INVADER_COLOR = (rgb_color_t){1, 0, 0};

const size_t SHIELDING_TIME = 200;
const size_t CIRCLE_POINTS = 200;

// Initial number of assets
size_t INITAL_NUM_ASSETS = 10;
// filepath for the beavers
const char *BEAVER_FILEPATH = "assets/beaver.png";
const char *TILE_FILEPATH = "assets/tile.png";
const char *BACKGROUND_PATH = "assets/background.png";
const char *TILE_BREAK_FILEPATH = "assets/tile-break.png";
const char *TILE_MOVE_FILEPATH = "assets/tile-move.png";
const char *TILE_SPRING_FILEPATH = "assets/tile-spring.png";
const char *TILE_ROCKET_FILEPATH = "assets/tile-rocket.png";

const char *FONT_PATH = "assets/DoodleJump.ttf";
const char *INVADER_FILEPATH = "assets/invader.png";
const char *BULLET__INFO = "bullet";
const char *BULLET_FILEPATH = "assets/bullet.png";
const double WALL_DIM = 1;

const char *TILE = "tile";
const char *TILE_SPRING = "tile-spring";
const char *TILE_MOVE = "tile-move";
const char *TILE_BREAK = "tile-break";
const char *TILE_ROCKET = "tile-rocket";
const char *TILE_SHIELD = "tile-shield";
const char *INVADER_INFO = "invader";
const char *BULLET_INFO = "bullet";
const char *PLAYER_1_INFO = "player 1";
const char *PLAYER_2_INFO = "player 2";
char *DOUBLE_PLAYER_STATE = "2";
char *SINGLE_PLAYER_STATE = "1";
char *OVER_STATE = "OVER";
char *HOME_STATE = "HOME";

int16_t tile_index = 1;

const char *HOME_PATH = "assets/home-screen.jpeg";
const char *GAME_OVER_PATH = "assets/game-over.jpeg";

const char *BUTTON_1_PATH = "assets/button_1.png";
const char *BUTTON_2_PATH = "assets/button_2.png";
const size_t NUM_BUTTONS = 2;

const char *BOING_AUDIOPATH = "assets/boing_yay.wav";
const char *GAME_OVER_AUDIOPATH = "assets/game_over.wav";

const char *TILE_SHIELD_FILEPATH = "assets/shield_image.png";
const double SHIELD_HEIGHT = 30;
const char *ACTIVATED_MSG_1 = "Activated Shield Player 1";
const char *ACTIVATED_MSG_2 = "Activated Shield Player 2";
const size_t SHIELD_MSG_LEN = 50;
const size_t SCORE_STR_LEN = 50;
const size_t BEAVER_FALLING_FRAMES = 50;

const SDL_Rect BUTTON_1_BOX = {.x = 600, .y = 200, .w = 300, .h = 70};
const SDL_Rect BUTTON_2_BOX = {.x = 600, .y = 300, .w = 300, .h = 70};

typedef struct button_info {
  const char *image_path;
  const char *font_path;
  SDL_Rect image_box;
  SDL_Rect text_box;
  rgb_color_t text_color;
  const char *text;
  button_handler_t handler;
} button_info_t;

typedef struct body_info {
  bool is_tile;
  char *name;
  size_t index;
} body_info_t;

void play_state_1(state_t *state);
void play_state_2(state_t *state);

button_info_t button_templates[] = {
    {.image_path = "assets/button_1.png",
     .font_path = "assets/DoodleJump.ttf",
     .image_box = BUTTON_1_BOX,
     .text_box = BUTTON_1_BOX,
     .text_color = TEXT_COLOR,
     .text = " ",
     .handler = (void *)play_state_1},
    {.image_path = "assets/button_2.png",
     .font_path = "assets/DoodleJump.ttf",
     .image_box = BUTTON_2_BOX,
     .text_box = BUTTON_2_BOX,
     .text_color = TEXT_COLOR,
     .text = " ",
     .handler = (void *)play_state_2}};

struct state {
  list_t *body_assets;
  scene_t *scene;
  body_t *player_1;
  body_t *player_2;
  list_t *button_assets;
  int32_t score;
  bool invaders_activated;
  body_t *invader_1;
  body_t *invader_2;
  size_t frames;
  double max_cam_height;
  size_t highest_row;
  size_t current_tile_index;
  char *game_state;
  bool game_over;
  size_t frames_at_end;
  asset_t *bgd;
  bool bgd_changed;
  Mix_Chunk *boing_audio;
  Mix_Chunk *game_over_audio;
  bool player_bounced;
  bool beaver_fallen;
  size_t time_shield_1;
  size_t time_shield_2;
  bool render_shield_p_1;
  bool render_shield_p_2;
};

body_info_t *body_info_init(bool is_tile, char *name, size_t index) {
  body_info_t *body_info = malloc(sizeof(body_info_t));
  assert(body_info);
  body_info->is_tile = is_tile;
  body_info->name = strdup(name);
  body_info->index = index;
  return body_info;
}

/*
 * Creating a oval to overlay the Beaver asset on
 */
list_t *make_oval(double outer_radius, double inner_radius) {
  vector_t center = VEC_ZERO;
  center.y += inner_radius;
  list_t *c = list_init(CIRCLE_POINTS, free);
  for (size_t i = 0; i < CIRCLE_POINTS; i++)
  {
    double angle = 2 * M_PI * i / CIRCLE_POINTS;
    vector_t *v = malloc(sizeof(*v));
    assert(v);
    *v = (vector_t){center.x + inner_radius * cos(angle),
                    center.y + outer_radius * sin(angle)};
    list_add(c, v);
  }
  return c;
}

/*
 * Puts the the invader at a random x top of the screen
 */
static void reset_invader_loc(body_t *player, body_t *invader) {
  double invader_x = (rand() % (size_t)floor(MAX.x));
  vector_t invader_loc = (vector_t){.x = invader_x, .y = MAX.y};
  body_set_centroid(invader, invader_loc);
}

/*
 * Initializes an invader body at a random location for the given player
 */
body_t *initialize_invader(state_t *state, body_t *player) {
  body_info_t *body_info = body_info_init(false, "invader", 0);
  body_t *invader = body_init_with_info(make_oval(INVADER_SIZE, INVADER_SIZE), INFINITY, TILE_COLOR, body_info, NULL);
  asset_t *asset_invader = asset_make_image_with_body(INVADER_FILEPATH, sdl_get_bounding_box(invader), invader);
  list_add(state->body_assets, asset_invader);
  reset_invader_loc(player, invader);
  return invader;
}

/*
 * AI Enemy: Updates the Invader to move towards the player it is assigned to.
 * Platers have a safe radius, which if enchroached, the invader received an impulse in
 * the opposite direction
 */
void update_invader(body_t *player, body_t *invader)
{
  vector_t player_loc = body_get_centroid(player);
  vector_t invader_loc = body_get_centroid(invader);
  double dx = player_loc.x - invader_loc.x;
  double dy = player_loc.y - invader_loc.y;
  if (dy > VEC_ZERO.y) {
    body_add_impulse(invader, REPULSE);
  }
  if (fabs(dx) > PLAYER_SAFE_RADIUS || fabs(dy) > PLAYER_SAFE_RADIUS) {
    // Compute the direction vector from invader to player
    vector_t direction = (vector_t){.x = dx, .y = dy};
    // Normalize the direction vector
    double norm_x = direction.x / vec_get_length(direction);
    double norm_y = direction.y / vec_get_length(direction);
    // Scale by invader velocity
    double vx = invader_velocity * norm_x;
    double vy = invader_velocity * norm_y;
    // Set the invader's velocity
    body_set_velocity(invader, (vector_t){.x = vx, .y = vy});
  }
  else {
    body_add_impulse(invader, INV_IMPULSE);
  }
}

/*
 * Makes the invader bullet object
 */
body_t *make_bullet(vector_t center, double radius, double mass,
                    rgb_color_t color, void *info) {
  list_t *c = list_init(CIRC_NPOINTS, free);
  for (size_t i = 0; i < CIRC_NPOINTS; i++)
  {
    double angle = 2 * M_PI * i / CIRC_NPOINTS;
    vector_t *v = malloc(sizeof(*v));
    *v = (vector_t){center.x + radius * cos(angle),
                    center.y + radius * sin(angle)};
    list_add(c, v);
  }
  body_info_t *body_info = body_info_init(false, info, 0);
  return body_init_with_info(c, mass, color, body_info, NULL);
}

/*
 * Makes the list of points for tiles
 */
list_t *make_tile(vector_t center, double width, double height) {
  list_t *points = list_init(4, free);
  vector_t *p1 = malloc(sizeof(vector_t));
  *p1 = (vector_t){center.x - width / 2, center.y - height / 2};
  vector_t *p2 = malloc(sizeof(vector_t));
  *p2 = (vector_t){center.x + width / 2, center.y - height / 2};

  vector_t *p3 = malloc(sizeof(vector_t));
  *p3 = (vector_t){center.x + width / 2, center.y + height / 2};

  vector_t *p4 = malloc(sizeof(vector_t));
  *p4 = (vector_t){center.x - width / 2, center.y + height / 2};

  list_add(points, p1);
  list_add(points, p2);
  list_add(points, p3);
  list_add(points, p4);
  return points;
}

list_t *generate_random_row(size_t height) {
  size_t max_tiles = MAX.x / (2 * TILE_WIDTH);
  size_t num_tiles = floor(rand() % max_tiles);
  // bound the number of tiles per row
  if (num_tiles < MIN_TILES_PER_ROW) {
    num_tiles = MIN_TILES_PER_ROW;
  }
  if (num_tiles > MAX_TILES_PER_ROW) {
    num_tiles = MAX_TILES_PER_ROW;
  }
  // case for a moving tiles row
  size_t move_tile = floor(rand() % MOVE_TILES_PROBABILITY);
  if (move_tile == MOVE_TILES_SELECT) {
    num_tiles = MOVE_TILES_PER_ROW;
  }
  list_t *all_tiles = list_init(num_tiles, (void *) body_free);
  size_t x_dist = floor(MAX.x / num_tiles);

  for (size_t i = 0; i < num_tiles; i++) {
    vector_t tile_pos = {DEFAULT_TILE_X, height};
    size_t rand_pos = floor(rand() % x_dist);
    // avoid overlapping tiles
    if (rand_pos < TILE_WIDTH / 2) {
      rand_pos = TILE_WIDTH / 2;
    } 
    if (rand_pos > x_dist - (TILE_WIDTH / 2)) {
      rand_pos = x_dist - (TILE_WIDTH / 2);
    }
    // case for a moving tiles row
    if (move_tile == MOVE_TILES_SELECT) {
      body_info_t *tile_info = body_info_init(true, (char *)TILE_MOVE, tile_index);
      body_t *tile = body_init_with_info(make_tile(tile_pos, TILE_WIDTH, TILE_HEIGHT),
                                         INFINITY, PLAYER_COLOR, tile_info, NULL);
      tile_index++;
      list_add(all_tiles, tile);
    } else {
      // adding break tiles to rows randomly
      size_t break_tile = floor(rand() % BREAK_TILES_PROBABILITY);
      size_t spring_tile = floor(rand() % SPRING_TILES_PROBABILITY);
      size_t rocket_tile = floor(rand() % SPECIAL_TILES_PROBABILITY);
      size_t shield_tile = floor(rand() % SPECIAL_TILES_PROBABILITY);

      tile_pos.x = (i * x_dist) + rand_pos;
      if (break_tile == BREAK_TILES_SELECT) {
        body_info_t *tile_info = body_info_init(true, (char *)TILE_BREAK, tile_index);
        body_t *tile = body_init_with_info(make_tile(tile_pos, TILE_WIDTH, TILE_HEIGHT),
                                           INFINITY, PLAYER_COLOR, tile_info, NULL);
        tile_index++;
        list_add(all_tiles, tile);
      } else if (spring_tile == SPRING_TILES_SELECT) { 
        // adding spring tiles to rows randomly
        body_info_t *tile_info = body_info_init(true, (char *)TILE_SPRING, tile_index);
        body_t *tile = body_init_with_info (
                              make_tile(tile_pos, TILE_WIDTH, SPRING_TILE_HEIGHT),
                              INFINITY, PLAYER_COLOR, tile_info, NULL);
        tile_index++;
        list_add(all_tiles, tile);
      } else if (rocket_tile == SPECIAL_TILES_SELECT) {
        body_info_t *tile_info = body_info_init(true, (char *)TILE_ROCKET, tile_index);
        body_t *tile = body_init_with_info(
                              make_tile(tile_pos, TILE_WIDTH, SPRING_TILE_HEIGHT),
                              INFINITY, PLAYER_COLOR, tile_info, NULL);
        tile_index++;
        list_add(all_tiles, tile);
      }
      else if (shield_tile == SPECIAL_TILES_SELECT) {
        body_info_t *tile_info = body_info_init(true, (char *)TILE_SHIELD, tile_index);
        body_t *tile = body_init_with_info(
                              make_tile(tile_pos, TILE_WIDTH, SHIELD_HEIGHT),
                              INFINITY, PLAYER_COLOR, tile_info, NULL);
        tile_index++;
        list_add(all_tiles, tile);
      } else {
        body_info_t *tile_info = body_info_init(true, "tile", tile_index);
        body_t *tile = body_init_with_info(
                              make_tile(tile_pos, TILE_WIDTH, TILE_HEIGHT),
                              INFINITY, PLAYER_COLOR, tile_info, NULL);
        tile_index++;
        list_add(all_tiles, tile);
      }
    }
  }
  return all_tiles;
}

/**
 * Wrap object around other side of screen display if it reaches any edge of the
 * display.
 */
void user_wrap_edges(body_t *body)
{
  vector_t centroid = body_get_centroid(body);
  if (centroid.x - BEAVER_SIZE > MAX.x) {
    body_set_centroid(body, (vector_t){MIN.x, centroid.y});
  }
  else if (centroid.x + BEAVER_SIZE < MIN.x) {
    body_set_centroid(body, (vector_t){MAX.x, centroid.y});
  }
}

/*
 * Key handler for moving the Beavers
 */
void on_key(char key, key_event_type_t type, double held_time, state_t *state) {
  double vy1 = body_get_velocity(state->player_1).y;
  vector_t velocity_right_1 = (vector_t){.x = resting_speed + ACCEL * held_time, 
                                          .y = vy1};
  vector_t velocity_left_1 = (vector_t){.x = - resting_speed - ACCEL * held_time, 
                                          .y = vy1};
  // Moving Beaver 1
  if (type == KEY_PRESSED) {
    if (key == LEFT_ARROW) {
      body_set_velocity(state->player_1, velocity_left_1);
    }
    else if (key == RIGHT_ARROW) {
      body_set_velocity(state->player_1, velocity_right_1);
    }
  } else {
    body_set_velocity(state->player_1, (vector_t){.x = VEC_ZERO.x, .y = vy1});
  }
  // Moving Beaver 2
  if (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0) {
    double vy2 = body_get_velocity(state->player_2).y;
    vector_t velocity_right_2 = (vector_t){.x = resting_speed + ACCEL * held_time,
                                            .y = vy2};
    vector_t velocity_left_2 = (vector_t){.x = -resting_speed - ACCEL * held_time, 
                                            .y = vy2};
    if (type == KEY_PRESSED) {
      if (key == 'a' && (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0)) {
        body_set_velocity(state->player_2, velocity_left_2);
      }
      else if (key == 'd' && (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0)) {
        body_set_velocity(state->player_2, velocity_right_2);
      }
    } else {
      body_set_velocity(state->player_2, (vector_t){.x = VEC_ZERO.x, .y = vy2});
    }
  }
}

void on_click(state_t *state, double x, double y) {
  for (size_t i = 0; i < list_size(state->button_assets); i++) {
    asset_t *asset = list_get(state->button_assets, i);
    if (asset_get_type(asset) == ASSET_BUTTON) {
      asset_on_button_click(asset, state, x, y);
    }
  }
}

asset_t *create_button_from_info(state_t *state, button_info_t info) {
  asset_t *image_asset = asset_make_image(info.image_path, info.image_box);
  asset_t *text_asset = NULL;
  if (info.font_path != NULL) {
    text_asset = asset_make_text(info.font_path, info.text_box, info.text,
                                 info.text_color);
  }
  asset_t *button_asset =
      asset_make_button(info.image_box, image_asset, text_asset, info.handler);
  asset_cache_register_button(button_asset);
  return button_asset;
}

void create_buttons(state_t *state) {
  for (size_t i = 0; i < NUM_BUTTONS; i++) {
    button_info_t info = button_templates[i];
    asset_t *button = create_button_from_info(state, info);
    list_add(state->button_assets, button);
  }
}

void beaver_collision_handler(body_t *player, body_t *tile, vector_t axis,
                              void *aux, double force_const) {
  state_t *state = (state_t *)aux;
  if (body_get_velocity(player).y < 0) {
    state->player_bounced = true;
    double val = REG_TILE_VEL;
    vector_t new_axis = (vector_t){.x = VEC_ZERO.x, .y = axis.y};
    body_info_t *body_info = (body_info_t *)body_get_info(tile);
    if (strcmp(body_info->name, TILE_SPRING) == 0) {
      val = SPRING_TILE_VEL;
    } else if (strcmp(body_info->name, TILE_ROCKET) == 0) {
      val = ROCKET_TILE_VEL;
    }
    physics_collision_handler(player, tile, new_axis, &val, force_const);

    body_info_t *info = (body_info_t *)(body_get_info(player));
    if (strcmp(info->name, PLAYER_1_INFO) == 0) {
      vector_t invader_loc = body_get_centroid(state->invader_1);
      if (invader_loc.y < body_get_centroid(state->player_1).y) {
        body_set_centroid(state->invader_1, (vector_t){.x = invader_loc.x, 
                            .y = state->max_cam_height + MAX.y});
      }
    } else {
      vector_t invader_loc = body_get_centroid(state->invader_2);
      if (invader_loc.y < body_get_centroid(state->player_2).y) {
        body_set_centroid(state->invader_2, (vector_t){.x = invader_loc.x, 
                            .y = state->max_cam_height + MAX.y});
      }
    }
    if (strcmp(body_info->name, TILE_BREAK) == 0) {
      vector_t under_floor = {MAX.x, MIN.y - TILE_HEIGHT};
      body_set_centroid(tile, under_floor);
    }
    if (!state->bgd_changed && strcmp(body_info->name, TILE_ROCKET) == 0) {
      state->bgd_changed = true;
      SDL_Rect background_box = {.x = MIN.x, .y = MIN.y, .w = MAX.x, .h = MAX.y};
      state->bgd = asset_make_image(ROCKET_BGD_FILEPATH, background_box);
    }
    if (strcmp(body_info->name, TILE_SHIELD) == 0) {
      body_info_t *player_info = (body_info_t *)body_get_info(player);
      if ((strcmp(player_info->name, PLAYER_1_INFO) == 0) && 
                      strcmp(state->game_state, SINGLE_PLAYER_STATE) == 0) {
        state->render_shield_p_1 = true; 
        state->time_shield_1 = state->frames;
      } else {
        state->render_shield_p_2 = true;
        state->time_shield_2 = state->frames;
      } 
    }
  }
}

void bullet_collision_handler(body_t *player, body_t *bullet, vector_t axis,
                              void *aux, double force_const) {
  state_t *state = (state_t *)aux;
  state->game_state = OVER_STATE;
}

void create_beaver_collision(scene_t *scene, body_t *player, body_t *tile, 
                            double elasticity, state_t *state) {
  create_collision(scene, player, tile, beaver_collision_handler, (void *)state, elasticity);
}

// invader shoot bullet
void invader_shoot_bullet(scene_t *scene, body_t *player, body_t *invader, 
                          state_t *state, bool shield) {
  srand(time(NULL));
  body_t *bullet = make_bullet(body_get_centroid(invader), BULLET_RADIUS,
                               BULLET_MASS, INVADER_COLOR, (void *) BULLET_INFO);
  scene_add_body(state->scene, bullet);
  asset_t *bullet_asset = asset_make_image_with_body(BULLET_FILEPATH, sdl_get_bounding_box(bullet), bullet);
  list_add(state->body_assets, bullet_asset);
  body_set_velocity(bullet, INVADER_BULLET_VEL);
  if (!shield) {
    create_collision(scene, player, bullet, bullet_collision_handler, state, ELASTICITY);
  }
}

void add_force_creators(state_t *state) {
  for (size_t i = 0; i < list_size(state->body_assets); i++) {
    asset_t *asset = list_get(state->body_assets, i);
    body_t *tile = get_image_asset_body(asset);
    body_info_t *body_info = (body_info_t *)body_get_info(tile);
    if (asset_is_tile(asset)) {
      if (body_info->index > state->current_tile_index) {
        create_beaver_collision(state->scene, state->player_1, tile, ELASTICITY, state);
        if (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0 || 
              strcmp(state->game_state, "HOME") == 0) {
          create_beaver_collision(state->scene, state->player_2, tile, ELASTICITY, state);
        }
        state->current_tile_index++;
      }
    }
  }
}

asset_t *create_tile_type(char *tile_type, body_t *tile) {
  if (strcmp(tile_type, TILE_BREAK) == 0) {
    return asset_make_image_with_body(TILE_BREAK_FILEPATH, sdl_get_bounding_box(tile), tile);
  } if (strcmp(tile_type, TILE_MOVE) == 0) {
    return asset_make_image_with_body(TILE_MOVE_FILEPATH, sdl_get_bounding_box(tile), tile);
  } if (strcmp(tile_type, TILE_SPRING) == 0) {
    return asset_make_image_with_body(TILE_SPRING_FILEPATH, sdl_get_bounding_box(tile), tile);
  } if (strcmp(tile_type, TILE_ROCKET) == 0) {
    return asset_make_image_with_body(TILE_ROCKET_FILEPATH, sdl_get_bounding_box(tile), tile);
  } if (strcmp(tile_type, "tile-shield") == 0) {
    return asset_make_image_with_body(TILE_SHIELD_FILEPATH, sdl_get_bounding_box(tile), tile);
  }
  return asset_make_image_with_body(TILE_FILEPATH, sdl_get_bounding_box(tile), tile);
}

void spawn_row(size_t height, state_t *state) {
  list_t *row_tiles = generate_random_row(height);
  for (size_t i = 0; i < list_size(row_tiles); i++) {
    body_t *tile = (body_t *)list_get(row_tiles, i);
    scene_add_body(state->scene, tile);
    body_info_t *body_info = (body_info_t *)body_get_info(tile);
    asset_t *tile_asset = create_tile_type(body_info->name, tile);
    if (strcmp(body_info->name, TILE_MOVE) == 0) {
      size_t rand_vel_x = rand() % MAX_TILE_X_VELOCITY;
      if (rand_vel_x < MIN_TILE_X_VELOCITY) {
        rand_vel_x = MIN_TILE_X_VELOCITY;
      }
      vector_t tile_vel = {rand_vel_x, TILE_Y_VELOCITY};
      body_set_velocity(tile, tile_vel);
    }
    list_add(state->body_assets, tile_asset);
  }
}

void play_state_1(state_t *state) {
  for (size_t i = 0; i < list_size(state->button_assets); i++) {
    asset_t *asset = list_get(state->button_assets, i);
    list_remove(state->button_assets, i);
    free(asset);
  }
  state->game_state = (char *) SINGLE_PLAYER_STATE;
  body_set_centroid(state->player_2, (vector_t){.x = MAX.x / 2, .y = state->max_cam_height - MAX.y/2});
}

void play_state_2(state_t *state) {
  for (size_t i = 0; i < list_size(state->button_assets); i++) {
    asset_t *asset = list_get(state->button_assets, i);
    list_remove(state->button_assets, i);
    free(asset);
  }
  state->game_state = (char *) DOUBLE_PLAYER_STATE;
}

void create_gravity(state_t *state) {
  if (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0) {
    body_set_velocity(state->player_1, 
                        (vector_t){.x = body_get_velocity(state->player_1).x,
                                    .y = body_get_velocity(state->player_1).y - GRAVITY});
    body_set_velocity(state->player_2, 
                        (vector_t){.x = body_get_velocity(state->player_2).x,
                                    .y = body_get_velocity(state->player_2).y - GRAVITY});
  } else {
    body_set_velocity(state->player_1, 
                        (vector_t){.x = body_get_velocity(state->player_1).x,
                                    .y = body_get_velocity(state->player_1).y - GRAVITY});
  }
}

state_t *emscripten_init() {
  asset_cache_init();
  TTF_Init();
  sdl_init(MIN, MAX);
  state_t *state = malloc(sizeof(state_t));
  assert(state);
  state->scene = scene_init();
  state->game_state = HOME_STATE;
  state->score = 0;
  state->invaders_activated = false;
  srand(time(NULL));
  state->max_cam_height = 0;
  state->current_tile_index = 0;
  state->bgd_changed = false;
  state->frames = 0;
  state->player_bounced = false;
  state->beaver_fallen = false;
  state->render_shield_p_1 = false;
  state->render_shield_p_2 = false;

  if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
  }
  Mix_Chunk *sound = Mix_LoadWAV(BOING_AUDIOPATH);
  Mix_Chunk *game_over = Mix_LoadWAV(GAME_OVER_AUDIOPATH);
  state->boing_audio = sound;
  state->game_over_audio = game_over;

  //Iniitalizing the Beavers
  body_info_t *body_info_player_1 = body_info_init(false, (char *)PLAYER_1_INFO, 0);
  body_info_t *body_info_player_2 = body_info_init(false, (char *)PLAYER_2_INFO, 0);
  state->player_1 = body_init_with_info(make_oval(BEAVER_SIZE, BEAVER_SIZE), BEAVER_MASS, 
                            PLAYER_COLOR, body_info_player_1, NULL);
  state->player_2 = body_init_with_info(make_oval(BEAVER_SIZE, BEAVER_SIZE), BEAVER_MASS,
                             PLAYER_COLOR, body_info_player_2, NULL);
  scene_add_body(state->scene, state->player_1);
  scene_add_body(state->scene, state->player_2);
  body_set_centroid(state->player_1, USER_1_CENTER);
  body_set_centroid(state->player_2, USER_2_CENTER);
  body_set_velocity(state->player_1, (vector_t){.x = VEC_ZERO.x, INITIAL_Y_VEL});
  body_set_velocity(state->player_2, (vector_t){.x = VEC_ZERO.x, INITIAL_Y_VEL});

  //Creates assets list  
  state->body_assets = list_init(INITAL_NUM_ASSETS, (void *)asset_destroy);
  SDL_Rect background_box = {.x = MIN.x, .y = MIN.y, .w = MAX.x, .h = MAX.y};
  asset_t *asset_bgd = asset_make_image(BACKGROUND_PATH, background_box);
  state->bgd = asset_bgd;
  state->bgd = asset_bgd;
  asset_t *asset_beaver_1 = asset_make_image_with_body(
      BEAVER_FILEPATH, sdl_get_bounding_box(state->player_1), state->player_1);
  asset_t *asset_beaver_2 = asset_make_image_with_body(
      BEAVER_FILEPATH, sdl_get_bounding_box(state->player_2), state->player_2);
  list_add(state->body_assets, asset_beaver_1);
  list_add(state->body_assets, asset_beaver_2);

  for (size_t j = 0; j < INITIAL_NUM_ROWS; j++) {
    spawn_row(INITIAL_LOWEST_ROW + ROW_SEPARATION * j, state);
    state->highest_row = INITIAL_LOWEST_ROW + ROW_SEPARATION * j;
  }
  state->score = 0;

  state->button_assets = list_init(NUM_BUTTONS, (free_func_t)asset_destroy);
  asset_t *home_bg = asset_make_image(HOME_PATH, background_box);
  state->game_over = false;

  list_add(state->button_assets, home_bg);
  add_force_creators(state);
  create_buttons(state);
  sdl_on_key((void *)on_key);
  sdl_on_mouse((mouse_handler_t)on_click);
  sdl_on_mouse((mouse_handler_t)on_click);
  return state;
}

bool out_of_frame(asset_t *asset, double cam_height) {
  body_t *body = get_image_asset_body(asset);
  if (body != NULL) {
    vector_t centroid = body_get_centroid(body);
    return (centroid.y + TILE_HEIGHT / 2 < cam_height);
  }
  return false;
}

asset_t *activated_shield(const char *msg, const SDL_Rect box) {
  char activated_shield[SHIELD_MSG_LEN];
  sprintf(activated_shield, "%s", msg);
  asset_t *shield_label = asset_make_text(FONT_PATH, box, activated_shield, TEXT_COLOR);
  return shield_label;
}

bool emscripten_main(state_t *state) {
  bool scroll_up = true;
  state->player_bounced = false;
  sdl_clear();
  double dt = time_since_last_tick();

  //Rendering the homescreen 
  if (strcmp(state->game_state, HOME_STATE) == 0) {
    for (size_t i = 0; i < list_size(state->button_assets); i++) {
      asset_t *asset = list_get(state->button_assets, i);
      asset_render(asset);
    }
  } else if (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0) {
    if (state->max_cam_height / HEIGHT_TO_SCORE_RATIO > state->score) {
      state->score = state->max_cam_height / HEIGHT_TO_SCORE_RATIO;
    }
    if (state->render_shield_p_1 && state->frames > state->time_shield_1 + SHIELDING_TIME) {
      state->render_shield_p_1 = false;
    }
    if (state->render_shield_p_1 && state->frames > state->time_shield_2 + SHIELDING_TIME) {
      state->render_shield_p_2 = false;
    }
    // handle invaders
    if (!state->invaders_activated) {
      state->invader_1 = initialize_invader(state, state->player_1);
      scene_add_body(state->scene, state->invader_1);
      state->invader_2 = initialize_invader(state, state->player_2);
      scene_add_body(state->scene, state->invader_2);
      state->invaders_activated = true;
    }
    update_invader(state->player_1, state->invader_1);
    update_invader(state->player_2, state->invader_2);
    // shooting bullets from invaders
    if (state->frames % SPAWN_TIME == 0 && state->invaders_activated) {
      invader_shoot_bullet(state->scene, state->player_1, state->invader_1, state, state->render_shield_p_1);
    }
    if (state->frames % SPAWN_TIME == 0 && state->invaders_activated) {
      invader_shoot_bullet(state->scene, state->player_2, state->invader_2, state, state->render_shield_p_2);
    }
    //Changing background
    if (state->bgd_changed && (body_get_velocity(state->player_1).y < 0 && body_get_velocity(state->player_2).y < 0)) {
      SDL_Rect background_box = {.x = MIN.x, .y = MIN.y, .w = MAX.x, .h = MAX.y};
      state->bgd = asset_make_image(BACKGROUND_PATH, background_box);
      state->bgd_changed = false;
    }
    double player_1_height = body_get_centroid(state->player_1).y - (BEAVER_SIZE / 2);
    double player_2_height = body_get_centroid(state->player_2).y - (BEAVER_SIZE / 2);
    double higher_player_height = fmax(player_1_height, player_2_height);
    double lower_player_height = fmin(player_1_height, player_2_height);
    state->max_cam_height = fmax(state->max_cam_height, higher_player_height);
    create_gravity(state);

    //Deleting and rendering new tiles
    for (size_t i = 0; i < list_size(state->body_assets); i++) {
      asset_t *asset = list_get(state->body_assets, i);
      body_t *body = get_image_asset_body(asset);
      if (body != NULL) {
        if (out_of_frame(asset, state->max_cam_height - MAX.y / 2)) {
          if (asset_is_tile(asset)) {
            body_remove(body);
            list_remove(state->body_assets, i);
            asset_destroy(asset);
            if ((state->highest_row < state->max_cam_height) && scroll_up) {
              spawn_row(state->max_cam_height + ROW_SEPARATION, state);
              state->highest_row = state->max_cam_height + ROW_SEPARATION;
              add_force_creators(state);
              state->current_tile_index = tile_index;
            }
          } else if (check_asset_info_field(asset, "player 2") 
                        || check_asset_info_field(asset, "player 1")) {
            if (!state->beaver_fallen) {
              state->beaver_fallen = true;
              state->frames_at_end = state->frames;
              scroll_up = false;
            }
            state->max_cam_height = lower_player_height;
          }
        } if (state->beaver_fallen 
                    && state->frames > state->frames_at_end + BEAVER_FALLING_FRAMES) {
          body_remove(body);
          list_remove(state->body_assets, i);
          free(asset);
          state->game_state = OVER_STATE;
        }
      }
    }
    sdl_clear();
    asset_render_with_cam(state->bgd, state->max_cam_height - MAX.y / 2, scroll_up);
    for (size_t i = 0; i < list_size(state->body_assets); i++) {
      asset_t *asset = list_get(state->body_assets, i);
      asset_render_with_cam(asset, state->max_cam_height - MAX.y / 2, scroll_up);
      body_info_t *body_info = (body_info_t *)body_get_info(get_image_asset_body(asset));
      if (strcmp(body_info->name, TILE_MOVE) == 0) {
        user_wrap_edges(get_image_asset_body(asset));
      }
    }
    
    char score_str[SCORE_STR_LEN];
    sprintf(score_str, "%d", state->score);
    asset_t *score_label = asset_make_text(FONT_PATH, text_box, score_str, TEXT_COLOR);
    asset_render(score_label);
    asset_destroy(score_label);

    if (state->render_shield_p_1) {
      asset_t *new_shield = activated_shield(ACTIVATED_MSG_1, SHIELD_BOX_1);
      asset_render(new_shield);
      asset_destroy(new_shield);
    }
    if (state->render_shield_p_2) {
      asset_t *new_shield = activated_shield(ACTIVATED_MSG_2, SHIELD_BOX_2);
      asset_render(new_shield);
      asset_destroy(new_shield);
    }
    user_wrap_edges(state->player_1);
    user_wrap_edges(state->player_2);
  } else if (strcmp(state->game_state, SINGLE_PLAYER_STATE) == 0) {
    if (state->max_cam_height / HEIGHT_TO_SCORE_RATIO > state->score) {
      state->score = state->max_cam_height / HEIGHT_TO_SCORE_RATIO;
    }
    if (state->render_shield_p_1 && state->frames > state->time_shield_1 + SHIELDING_TIME) {
      state->render_shield_p_1 = false;
    }
    // handle invaders
    if (!state->invaders_activated) {
      state->invader_1 = initialize_invader(state, state->player_1);
      scene_add_body(state->scene, state->invader_1);
      state->invaders_activated = true;
    }
    update_invader(state->player_1, state->invader_1);
    if (state->frames % SPAWN_TIME == 0 && state->invaders_activated) {
      invader_shoot_bullet(state->scene, state->player_1, state->invader_1, state, state->render_shield_p_1);
    }
    create_gravity(state);

    // change this
    if (state->bgd_changed && (body_get_velocity(state->player_1).y < 0)) {
      SDL_Rect background_box = {.x = MIN.x, .y = MIN.y, .w = MAX.x, .h = MAX.y};
      state->bgd = asset_make_image(BACKGROUND_PATH, background_box);
      state->bgd_changed = false;
    }
    double player_1_height = body_get_centroid(state->player_1).y - (BEAVER_SIZE / 2);
    state->max_cam_height = fmax(state->max_cam_height, player_1_height);

    // just generating new rows and garbage collection
    for (size_t i = 0; i < list_size(state->body_assets); i++) {
      asset_t *asset = list_get(state->body_assets, i);
      body_t *body = get_image_asset_body(asset);
      if (body != NULL) {
        if (out_of_frame(asset, state->max_cam_height - MAX.y / 2)) {
          if (asset_is_tile(asset) ||  check_asset_info_field(asset, "player 2") || check_asset_info_field(asset, "bullet")) {
            body_remove(body);
            list_remove(state->body_assets, i);
            asset_destroy(asset);
            if (state->highest_row < state->max_cam_height) {
              spawn_row(state->max_cam_height + ROW_SEPARATION, state);
              state->highest_row = state->max_cam_height + ROW_SEPARATION;
              add_force_creators(state);
            }
          }
          else if (check_asset_info_field(asset, (void *) PLAYER_1_INFO)) {
            if (!state->beaver_fallen) {
              state->beaver_fallen = true;
              state->frames_at_end = state->frames;
              scroll_up = false;
            }
            state->max_cam_height = player_1_height;
          }
        } if (state->beaver_fallen && state->frames > 
                  state->frames_at_end + BEAVER_FALLING_FRAMES) {
          state->game_state = OVER_STATE;
        }
      }
    }
    asset_render_with_cam(state->bgd, state->max_cam_height - MAX.y / 2, scroll_up);
    for (size_t i = 0; i < list_size(state->body_assets); i++) {
      asset_t *asset = list_get(state->body_assets, i);
      asset_render_with_cam(asset, state->max_cam_height - MAX.y / 2, scroll_up);
      // moving the moving tiles
      body_info_t *body_info = (body_info_t *)body_get_info(get_image_asset_body(asset));
      if (strcmp(body_info->name, TILE_MOVE) == 0) {
        user_wrap_edges(get_image_asset_body(asset));
      }
    }

    char score_str[SCORE_STR_LEN];
    sprintf(score_str, "%d", state->score);
    asset_t *score_label = asset_make_text(FONT_PATH, text_box, score_str, TEXT_COLOR);
    asset_render(score_label);
    asset_destroy(score_label);

    if (state->render_shield_p_1) {
      asset_t *new_shield = activated_shield(ACTIVATED_MSG_1, SHIELD_BOX_1);
      asset_render(new_shield);
      asset_destroy(new_shield);
    }
    user_wrap_edges(state->player_1);
  } else if ((strcmp(state->game_state, OVER_STATE) == 0) || state->game_over) {
    SDL_Rect background_box = {.x = MIN.x, .y = MIN.y, .w = MAX.x, .h = MAX.y};
    asset_t *over_screen = asset_make_image(GAME_OVER_PATH, background_box);
    asset_render(over_screen);
    char score_str[SHIELD_MSG_LEN];
    sprintf(score_str, "FINAL SCORE: %d", state->score);
    asset_t *score_label = asset_make_text(FONT_PATH, text_box, score_str, TEXT_COLOR);
    asset_render(score_label);
    asset_destroy(score_label);

    sdl_play_sound(state->game_over_audio);
    for (size_t i = 0; i < list_size(state->body_assets); i++) {
      asset_t *asset = list_get(state->body_assets, i);
      body_t *body = get_image_asset_body(asset);
      if (body != NULL) {
        body_remove(body);
        list_remove(state->body_assets, i);
        free(asset);
      }
    }
    sdl_show();
    return state->game_over;
  }
  scene_tick(state->scene, dt);
  state->frames++;
  if (state->player_bounced) {
    sdl_play_sound(state->boing_audio);
    state->player_bounced = false;
  }
  sdl_show();
  return state->game_over;
}

void emscripten_free(state_t *state) {
  body_free(state->player_1);
  if (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0) {
    body_free(state->player_2);
  }
  body_free(state->invader_1);
  if (strcmp(state->game_state, DOUBLE_PLAYER_STATE) == 0) {
    body_free(state->invader_2);
  }
  Mix_FreeChunk(state->boing_audio);
  Mix_FreeChunk(state->game_over_audio);
  list_free(state->body_assets);
  list_free(state->button_assets);
  for (size_t i = 0; i < scene_bodies(state->scene); i++) {
    free((body_info_t *)body_get_info(scene_get_body(state->scene, i)));
  }
  scene_free(state->scene);
  free(state);
}
