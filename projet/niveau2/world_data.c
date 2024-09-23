/**
 * \file world_data.c
 * \brief Fichier contenant les données du monde
 * \author DURHAM Patrick/BELUCHE Quentin
 * \version 2.0
 * \date 16/05/2022
 */

#include "texture_data.h"


void print_sprite(sprite_t *sprite){
    //Affichage des données du sprite
    printf("---- Sprite ----\n");
    printf("x : %d", sprite->x);
    printf("y : %d\n", sprite->y);
    printf("largeur (w) : %d", sprite->w);
    printf("hauteur (h) : %d\n", sprite->h);
    printf("vitesse verticale (v) : %d\n", sprite->v);
    if(sprite->is_visible == 0){
        printf("Est visible");
    }else{
        printf("Est invisible");
    }
    printf("----------------");
}

/**
 * \brief Set the sprite visible
 * \param sprite 
 */
void set_visible(sprite_t *sprite){ //Rend un sprite visible
    sprite->is_visible = 0;
}

/**
 * \brief Set the sprite invisible
 * \param sprite 
 */
void set_invisible(sprite_t *sprite){//Rend un sprite invisible
    sprite->is_visible = 1;
}

/**
 * \brief initialisation des données du sprite
*/
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v,int etat){
    sprite->x = x; //abscisse
    sprite->y = y; //ordonnée
    sprite->w = w; //largeur
    sprite->h = h; //hauteur
    sprite->v = v; //vitesse verticale
    sprite->is_visible = etat; //est visible

}

void init_data(world_t * world){
    //pour le vaisseau
    sprite_t* vaiss = malloc(sizeof(sprite_t));
    world->vaisseau = vaiss;
    init_sprite(world->vaisseau, SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE,0,0);
    print_sprite(world->vaisseau);
    //pour l'enemie
    sprite_t* enem = malloc(sizeof(sprite_t));
    world->enemy = enem;
    world->enemy->v = 2;
    init_sprite(world->enemy, SCREEN_WIDTH/2-SHIP_SIZE/2,0-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE,world->enemy->v,0);
    print_sprite(world->enemy);
    //pour le missile
    sprite_t* miss = malloc(sizeof(sprite_t));
    world->missile = miss;
    init_sprite(world->missile, world->vaisseau->x+SHIP_SIZE/2,world->vaisseau->y-SHIP_SIZE/4,MISSILE_SIZE,MISSILE_SIZE,0,1);
    print_sprite(world->missile);
    //pour les enemies
    init_enemies(world);
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    
}

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->enemy);
    free(world->missile);
}

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}

void colission_gauche(world_t *world){
    // Pour le coté gauche
    if(world->vaisseau->x < 0){
        world->vaisseau->x += SHIP_SPEED;
        world->missile->x += SHIP_SPEED;
    }
}

void colission_droite(world_t *world){
    // Pour le coté droit
    if(world->vaisseau->x > 268){
        world->vaisseau->x -= SHIP_SPEED;
        world->missile->x -= SHIP_SPEED;
    }
}

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void colission_enemy(world_t *world){
    // Pour qu'il reset sa position
    if(world->enemy->y > 448){
        world->enemy->y = 0;
    }
}

int sprites_collide(sprite_t *sp2, sprite_t *sp1){
    if((abs(sp1->x + sp1->w/2 - sp2->x - sp2->w/2) <= (sp1->w + sp2->w)/2) && abs(sp1->y + sp1->h/2 - sp2->y - sp2->h/2) <= (sp1->h + sp2->h)/2){
        return 1;
    }
    else{
        return 0;
    }
}

void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1){
    if((sprites_collide(sp1,sp2) == 1)&&(sp2->is_visible == 0)&&(sp1->is_visible == 0)){
        sp1->v = 0;
        sp2->y = 448;
        sp1->is_visible = 1;
        sp2->is_visible = 1;
    }
}

void update_data(world_t *world){
    world->enemy->y += ENEMY_SPEED;
    if(world->missile->is_visible == 0){
        world->missile->y -= MISSILE_SPEED;
    }
    if(world->vaisseau->is_visible == 1){
        set_invisible(world->missile);
    }
    colission_gauche(world);
    colission_droite(world);
    colission_enemy(world);
    handle_sprites_collision(world->vaisseau,world->enemy);
    handle_sprites_collision(world->missile,world->enemy);
}