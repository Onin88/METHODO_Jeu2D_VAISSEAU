/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "sdl2-light.h"


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

#define MISSILE_SPEED 8

#define ENEMY_SPEED 2

#define SHIP_SPEED 3

struct textures_s{
    SDL_Texture *background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture *vaisseau; /*!<Texture liée à l'image du vaisseau. */
    SDL_Texture *enemy; /*!<Texture liée à l'ennemie. */
    SDL_Texture *missile; /*!<Texture liée au missile. */
    /* A COMPLETER */
};
typedef struct sprite_s sprite_t;

struct sprite_s{
    int x; //position x
    int y; //position y
    int h; //hauteur
    int w; //largeur
    int v; //vitesse verticale
    int is_visible; //visibilité du sprite; 0 si visible, 1 sinon
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;
/**
 * \brief affiche les données du sprite 
*/
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
 * \brief Représentation du monde du jeu
*/
struct world_s{
    /*
      A COMPLETER
     */
    sprite_t *vaisseau; //structure représentant le vaisseau
    sprite_t *enemy; //structure pour l'enemy
    sprite_t *missile; //structure pour le missile
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

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
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;
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


/**
 * \brief initialisation des données dans le world
*/
void init_data(world_t * world){
    //pour le vaisseau
    sprite_t* vaiss = malloc(sizeof(sprite_t));
    world->vaisseau = vaiss;
    init_sprite(world->vaisseau, SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE,0,0);
    print_sprite(world->vaisseau);
    //pour l'enemie
    sprite_t* enem = malloc(sizeof(sprite_t));
    world->enemy = enem;
    init_sprite(world->enemy, SCREEN_WIDTH/2-SHIP_SIZE/2,0-SHIP_SIZE, SHIP_SIZE, SHIP_SIZE,ENEMY_SPEED,0);
    print_sprite(world->enemy);
    //pour le missile
    sprite_t* miss = malloc(sizeof(sprite_t));
    world->missile = miss;
    init_sprite(world->missile, world->vaisseau->x+SHIP_SIZE/2,world->vaisseau->y-SHIP_SIZE/4,MISSILE_SIZE,MISSILE_SIZE,0,1);
    print_sprite(world->missile);
    
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



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->enemy->y += ENEMY_SPEED;
    if(world->missile->is_visible == 0){
        world->missile->y -= MISSILE_SPEED;
    }
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
            //si la flèche du haut est appuyée
            if(event->key.keysym.sym == SDLK_z){
                world->vaisseau->y -= 0;
                world->missile->y -= 0;
                 printf("La touche Z est appuyée\n");
            }
            //si la flèche du bas est appuyée
            if(event->key.keysym.sym == SDLK_s){
                world->vaisseau->y += 0;
                world->missile->y += 0;
                 printf("La touche S est appuyée\n");
            }
            //si la flèche de gauche est appuyée
            if(event->key.keysym.sym == SDLK_q){
                world->vaisseau->x -= SHIP_SPEED;
                world->missile->x -= SHIP_SPEED;
                 printf("La touche Q est appuyée\n");
            }
            //si la flèche de droite est appuyée
            if(event->key.keysym.sym == SDLK_d){
                world->vaisseau->x += SHIP_SPEED;
                world->missile->x += SHIP_SPEED;
                 printf("La touche D est appuyée\n");
            }
            //si la touche echap est appuyée
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
            //si la touche espace est appuyée
            if(event->key.keysym.sym == SDLK_SPACE){
                set_visible(world->missile);
            }
        }
    }
}


/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->enemy); // si le jeu est fini on clean la texture
    /* A COMPLETER */
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    //chargement de la texture de l'arrière plan
    textures->background = load_image("ressources/space-background.bmp", renderer);
    //chargement de la texture du vaisseau
    textures->vaisseau = load_image("ressources/spaceship.bmp", renderer);
    //chargement de la texture de l'ennemie
    textures->enemy = load_image("ressources/enemy.bmp", renderer);
    //chargement de la texture du missiles
    textures->missile = load_image("ressources/missile.bmp", renderer); 
    /* A COMPLETER */
}


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}

void apply_sprite(SDL_Renderer *renderer, SDL_Texture *texture, sprite_t *sprite){
    //si le sprite est visible alors on applique la texture
    if(sprite->is_visible == 0){
        apply_texture(texture, renderer, sprite->x, sprite->y);
    }
}



/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    //application des textures du vaisseau
    apply_sprite(renderer, textures->vaisseau, world->vaisseau);
    //application des textures de l'enemy
    apply_sprite(renderer, textures->enemy, world->enemy);
    //application des textures du missile
    apply_sprite(renderer, textures->missile, world->missile);
    
    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
