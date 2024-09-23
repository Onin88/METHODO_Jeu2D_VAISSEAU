#ifndef __TEXTURE_DATA__H__
#define __TEXTURE_DATA__H__

#include <stdio.h>
#include <stdlib.h>
#include "sdl2-light.h"

struct sprite_s{
    int x; //position x
    int y; //position y
    int h; //hauteur
    int w; //largeur
    int v; //vitesse verticale
    int is_visible; //visibilité du sprite; 0 si visible, 1 sinon
};
/**
 * @brief Type qui correspond aux données des sprites
 */
typedef struct sprite_s sprite_t;


struct world_s{
    sprite_t *vaisseau; //structure représentant le vaisseau
    sprite_t *enemy; //structure pour l'enemy
    sprite_t *missile; //structure pour le missile
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */
};
/**
 * \brief Type qui correspond aux données du monde
 */
typedef struct world_s world_t;

struct textures_s{
    SDL_Texture *background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture *vaisseau; /*!<Texture liée à l'image du vaisseau. */
    SDL_Texture *enemy; /*!<Texture liée à l'ennemie. */
    SDL_Texture *missile; /*!<Texture liée au missile. */
};
/**
 * @brief Type qui correspond aux données graphique des textures
 */
typedef struct textures_s textures_t;
/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300
/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480
/**
 * \brief Taille d'un vaisseau
 */
#define SHIP_SIZE 32
/**
 * \brief Taille du missile
*/
#define MISSILE_SIZE 8
/**
 * \brief Vitesse du Missile
*/
#define MISSILE_SPEED 8
/**
 * \brief Vitesse de l'enemy
*/
#define ENEMY_SPEED 2
/**
 * \brief Vitesse de l'enemy
*/
#define ENEMY_SPEED_NULL 0
/**
 * \brief Vitesse du vaisseau
*/
#define SHIP_SPEED 3

void print_sprite(sprite_t *sprite);
void set_visible(sprite_t *sprite);
void set_invisible(sprite_t *sprite);
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v,int etat);
void init_data(world_t *world);
void clean_data(world_t *world);
int is_game_over(world_t *world);
void colission_gauche(world_t *world);
void colission_droite(world_t *world);
void update_data(world_t *world);
void colission_enemy(world_t *world);
int sprites_collide(sprite_t *sp2, sprite_t *sp1);
void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1);

void clean_textures(textures_t *textures);
void handle_events(SDL_Event *event,world_t *world);
void init_textures(SDL_Renderer *renderer, textures_t *textures);
void apply_background(SDL_Renderer *renderer, textures_t *textures);
void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite);
void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures);
void clean(SDL_Window *window, SDL_Renderer *renderer, textures_t *textures, world_t *world);
void init(SDL_Window **window, SDL_Renderer **renderer, textures_t *textures, world_t *world);


#endif