/**
 * \file main.c
 * \brief Programme principal du niveau 0
 * \author Quentin BELUCHE
 * \version 4.0
 * \date 05/05/2022
 */
#include "sdl2-light.h"


/**
 * \brief Largeur de l'écran
*/


#define SCREEN_WIDTH 320

/**
 * \brief Hauteur de l'écran
*/

#define SCREEN_HEIGHT 240

/**
 * \brief Taille du sprite
*/

#define SPRITE_SIZE 32

/**
 * \brief Pas de déplacement du sprite
*/

#define MOVING_STEP 5

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* sprite;
    /* A COMPLETER */
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;


/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    /*
      A COMPLETER
     */
    int x; /*!< Champ indiquant la position x du personnage*/
    int y; /*!< Champ indiquant la position y du personnage*/
    
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;





/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    
    //on n'est pas à la fin du jeu
    world->gameover = 0;
    //la position x et y du joueur est au centre de l'écran
    world->x = SCREEN_WIDTH/2;
    world->y = SCREEN_HEIGHT/2;
    
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
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
    /* A COMPLETER */
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
            //si la touche appuyée est 'D'
            if(event->key.keysym.sym == SDLK_d){
                printf("La touche D est appuyée\n");
                world->x += MOVING_STEP;
            }
            //si la flèche du haut est appuyée
            if(event->key.keysym.sym == SDLK_UP){
                world->y -= MOVING_STEP;
            }
            //si la flèche du bas est appuyée
            if(event->key.keysym.sym == SDLK_DOWN){
                world->y += MOVING_STEP;
            }
            //si la flèche de gauche est appuyée
            if(event->key.keysym.sym == SDLK_LEFT){
                world->x -= MOVING_STEP;
            }
            //si la flèche de droite est appuyée
            if(event->key.keysym.sym == SDLK_RIGHT){
                world->x += MOVING_STEP;
            }
            //si la touche echap est appuyée
            if(event->key.keysym.sym == SDLK_ESCAPE){
                world->gameover = 1;
            }
            //si la flèche du haut est appuyée
            if(event->key.keysym.sym == SDLK_z){
                world->y -= MOVING_STEP;
                printf("La touche Z est appuyée\n");
            }
            //si la flèche du bas est appuyée
            if(event->key.keysym.sym == SDLK_s){
                world->y += MOVING_STEP;
                printf("La touche S est appuyée\n");
            }
            //si la flèche de gauche est appuyée
            if(event->key.keysym.sym == SDLK_q){
                world->x -= MOVING_STEP;
                printf("La touche Q est appuyée\n");
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
    clean_texture(textures->sprite);
    /* A COMPLETER */
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/background.bmp",renderer);
    textures->sprite = load_image("ressources/sprite.bmp", renderer);
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





/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param screen la surface de l'écran de jeu
 * \param world les données du monde
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_texture(textures->sprite, renderer, world->x, world->y); //Player placé au milieu de l'écran
    /* A COMPLETER */
    
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
