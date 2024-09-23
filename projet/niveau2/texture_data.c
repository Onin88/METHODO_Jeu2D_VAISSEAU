/**
 * \file texture_data.c
 * \brief Fichier contenant les données graphique
 * \author DURHAM Patrick/BELUCHE Quentin
 * \version 1.0
 * \date 16/05/2022
 */

#include "texture_data.h"

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->vaisseau);
    clean_texture(textures->enemy); // si le jeu est fini on clean la texture
}

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
void clean(SDL_Window *window, SDL_Renderer *renderer, textures_t *textures, world_t *world){
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
void init(SDL_Window **window, SDL_Renderer **renderer, textures_t *textures, world_t *world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);
}