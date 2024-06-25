#include "interfaz_grafica.h"
#include "sprite_object.h"
#include "spritesheet.h"
#include "spritesManager.h"
#include "characters.h"
#include "event_handler.h"

#define MENU_MUSIC_PATH "../music_src/Music/TitleScreen.mp3"
#define SELECTION_MUSIC_PATH "../music_src/Music/Selection.mp3"
#define CASTLE_MUSIC_PATH "../music_src/Music/Castle.mp3"
#define COLONIUS_MUSIC_PATH "../music_src/Music/Colonius.mp3"
#define LABRATORY_MUSIC_PATH "../music_src/Music/Labratory.mp3"
#define MEDIVO_MUSIC_PATH "../music_src/Music/Medivo.mp3"

#define EFFECTS_VOLUME 100

#define SHOOTING_EFFECT_PATH "../music_src/Effects/Shooting.mp3"
#define SHOOTING_ROCKET_EFFECT_PATH "../music_src/Effects/ShootingRocket.mp3"
#define JUMPING_EFFECT_PATH "../music_src/Effects/Jump.mp3"
#define JAZZ_HURT_EFFECT_PATH "../music_src/Effects/JazzHurt.mp3"
#define SPAZ_HURT_EFFECT_PATH "../music_src/Effects/SpazHurt.mp3"
#define LORI_HURT_EFFECT_PATH "../music_src/Effects/LoriHurt.mp3"
#define INTOXICATED_EFFECT_PATH "../music_src/Effects/Intoxicated.mp3"
#define SPECIAL_ATTACK_EFFECT_PATH "../music_src/Effects/SpecialAttack.mp3"
#define DEATH_EFFECT_PATH "../music_src/Effects/Death.mp3"
#define REVIVING_EFFECT_PATH "../music_src/Effects/Reviving.mp3"
#define TOUCHING_GROUND_EFFECT_PATH "../music_src/Effects/TouchingGround.mp3"
#define TIMES_UP_PATH "../music_src/Effects/TimesUp.mp3"
#define TIMES_UP_2_PATH "../music_src/Effects/TimesUp2.mp3"
#define ENEMY_HURT_EFFECT_PATH "../music_src/Effects/EnemyHurt.mp3"
#define ENEMY_DEATH_EFFECT_PATH "../music_src/Effects/EnemyDeath.mp3"

SDL_Renderer* InterfazGrafica::renderer = nullptr;

SDL_Rect InterfazGrafica::camara = {0,0,ANCHO_WINDOW, ALTO_WINDOW};

//constructor
InterfazGrafica::InterfazGrafica(
    Queue<InfoJuego> &queueReceptora, ClientPlayer &client, MusicPlayer &musicPlayer
    ) : estado(Menu),
        queueReceptora(queueReceptora),
        renderizarPantalla(&InterfazGrafica::renderizarMenu),
        musicPlayer(musicPlayer),
        effectsPlayer(EFFECTS_VOLUME)
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        window = SDL_CreateWindow("Ventana del juego", SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, ANCHO_WINDOW,
                                ALTO_WINDOW, SDL_WINDOW_SHOWN);
        if (window == NULL)
            throw std::runtime_error("ERROR. Falló la creacion de SDL_Window");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL)
            throw std::runtime_error("ERROR. Falló la creacion del SDL_Renderer");
        
        SDL_SetRenderDrawColor(renderer,255, 255, 255, 255); // pongo fondo en blanco
        is_running = true;
    }
    else {
        is_running = false;
        throw std::runtime_error("ERROR. SDL no pudo inicializarse");
    }
    spritesManager = new SpritesManager();
    spritesManager->inicializarBotonesPartidas(client.getIdPartidas());
    spritesManager->inicializarBotonesCharacter();
    eventHandler =  new EventHandler(
        *this, client, effectsPlayer, spritesManager->getBotonesPartidas(),
        spritesManager->getBotonesCharacter(), this->is_running
    );

    eventHandler->start();
}

bool InterfazGrafica::estaAbierta() {
    return is_running;
}

void InterfazGrafica::addPlayer(int id, const TipoPlayer &tipo) {//temporal
    spritesManager->addPlayer(id, tipo);
}

void InterfazGrafica::setMapa (const TileMap &mapa) {
    spritesManager->setMapa(mapa);
    max_x = mapa.getFilas() * 32;
    max_y = mapa.getColumnas() * 32;
}

//muevo la camara para que quede centrada en la posicion recibida
void InterfazGrafica::updateCamara(const Position &pos) {
    int new_camara_x = pos.x - ANCHO_WINDOW / 2;
    int new_camara_y = pos.y - ALTO_WINDOW / 2;

    // Asegurarse de que la cámara no se salga de los márgenes del escenario
    if (new_camara_x < 0) {
        new_camara_x = 0;
    } else if (new_camara_x > max_x - ANCHO_WINDOW) {
        new_camara_x = max_x - ANCHO_WINDOW;
    }

    if (new_camara_y < 0) {
        new_camara_y = 0;
    } else if (new_camara_y > max_y - ALTO_WINDOW) {
        new_camara_y = max_y - ALTO_WINDOW;
    }

    // Actualizar la posición de la cámara
    camara.x = new_camara_x;
    camara.y = new_camara_y;
}

Position InterfazGrafica::posRelativaACamara(const int &x, const int &y) {
    return Position(x - camara.x, y- camara.y);
}

void InterfazGrafica::update(int it) {
    if (estado != Juego)
        return;
    iteracion += it;
    
    try {
        infoJuego = queueReceptora.pop();
        Position pos(infoJuego.players[0].pos_x, infoJuego.players[0].pos_y); // el player 0 debo "ser yo"
        updateCamara(pos);
        //std::cout << "Cant players: " << infoJuego.cantidadPlayers() << std::endl;
        
        for (int i=0; i< infoJuego.cantidadPlayers(); i++) {
            InfoPlayer &infoPlayer = infoJuego.players[i];
            EstadosPlayer &estado = infoPlayer.estado;
            pos = posRelativaACamara(infoPlayer.pos_x, infoPlayer.pos_y);
            try {
                spritesManager->updatePlayer(infoPlayer.id, estado, pos, infoPlayer.direccion);
                efectosPlayer(estado, infoPlayer);
            } catch (...) { // si lanza una excepcion quiere decir que el player i no existe en spritesManager. Debo agregarlo
                spritesManager->addPlayer(infoPlayer.id, infoPlayer.tipoPlayer);
                spritesManager->updatePlayer(infoPlayer.id, estado, pos, infoPlayer.direccion);
            }
        }
        for (int i=0; i< infoJuego.cantEnemigos(); i++) {
            InfoEnemigo &infoEnemigo = infoJuego.enemigos[i];
            EstadosEnemy &estado = infoEnemigo.estado;
            pos = posRelativaACamara(infoEnemigo.pos_x, infoEnemigo.pos_y);
            try {
                spritesManager->updateEnemy(i, estado, pos, infoEnemigo.direccion);
                //efectosEnemy(estado, infoEnemigo);
            } catch (...) {
                spritesManager->addEnemy(infoEnemigo.tipo);
                spritesManager->updateEnemy(i, estado, pos, infoEnemigo.direccion);
            }
        }
    
        if (iteracion % 2 == 0) {
            spritesManager->updateItems();
            spritesManager->updateProyectiles();
        }
    } catch (const ClosedQueue& e) {
        std::cout << "Capturo Queue cerrada en InterfazGrafica::update()" << std::endl;
        nextEstado();
        //cerrarInterfaz();
    }
} 

void InterfazGrafica::renderizarJuego() 
{
    if (!is_running)
        return;
    if (infoJuego.cantidadPlayers() == 0) {
        throw std::runtime_error("No hay ningun Player cargardo aun. En InterfazGrafica::renderizarJuego()");
    }
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);//borra todo

    spritesManager->renderizarTerreno(Position(camara.x, camara.y));

    // renderizo players
    for (int i=0; i< infoJuego.cantidadPlayers(); i++) {
        spritesManager->renderizarPlayer(infoJuego.players[i].id);
    }
    //renderizo enemigos
    for (int i=0; i< infoJuego.cantEnemigos(); i++) {
        spritesManager->renderizarEnemigo(i);
    }
    //renderizo los items
    for (int i=0; i< infoJuego.cantRecolectables(); i++) {
        Position pos = posRelativaACamara(infoJuego.recolectables[i].pos_x, infoJuego.recolectables[i].pos_y);
        spritesManager->renderizarItemEn(infoJuego.recolectables[i].tipo, pos.x, pos.y);
    }
    //renderizo los proyectiles
    for (int i=0; i< infoJuego.cantProyectiles(); i++) {
        //std::cout << "Hay " << infoJuego.cantProyectiles() << " proyectiles" << std::endl;
        Position pos = posRelativaACamara(infoJuego.proyectiles[i].pos_x, infoJuego.proyectiles[i].pos_y);
        spritesManager->renderizarProyectilEn(infoJuego.proyectiles[i].direccion, infoJuego.proyectiles[i].tipo, pos.x, pos.y);
        //spritesManager->updatePlayer(i, infoJuego.players[i].estado, posicion);
    }

    //HUD
    spritesManager->renderizarVidas(infoJuego.players[0].vida);
    spritesManager->renderizarMunicionArma(infoJuego.players[0].arma, infoJuego.players[0].municion);
    spritesManager->renderizarTiempo(infoJuego.tiempo_restante); //Pasar infoJuego.tiempo
    spritesManager->renderizarTablaPosiciones(infoJuego.rankingPlayers);

    SDL_RenderPresent(renderer); // dibuja todo
}

void InterfazGrafica::nextEstado() {
    switch (estado)
    {
    case Menu:
        musicPlayer.play_music(SELECTION_MUSIC_PATH);
        estado = SeleccionPartida;
        renderizarPantalla = &InterfazGrafica::renderizarSeleccionPartida;
        break;
    case SeleccionPartida:
        estado = SeleccionPlayer;
        renderizarPantalla = &InterfazGrafica::renderizarSeleccionPlayer;
        break;
    case SeleccionPlayer:
        musicPlayer.play_random_music();
        estado = Juego;
        renderizarPantalla = &InterfazGrafica::renderizarJuego;
        break;
    case Juego:
        musicPlayer.stop();
        effectsPlayer.play_effect(TIMES_UP_PATH);
        effectsPlayer.play_effect(TIMES_UP_2_PATH);
        estado = ResultadosFinales; //no implementado
        renderizarPantalla = &InterfazGrafica::renderizarTablaResultados;
        break;
    case ResultadosFinales:
        musicPlayer.stop();
        estado = Menu;
        renderizarPantalla = &InterfazGrafica::renderizarMenu;
    default:
        break;
    }
}

void InterfazGrafica::stop(){
    is_running = false;
} 

void InterfazGrafica::renderizarActual(){
    (this->*renderizarPantalla)();
}


void InterfazGrafica::renderizarMenu(){
    SDL_SetRenderDrawColor(renderer,0, 0, 0, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarMenu();

    SDL_RenderPresent(renderer);
}


void InterfazGrafica::renderizarSeleccionPartida(){
    SDL_SetRenderDrawColor(renderer,106, 101, 255, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarBotonesPartidas(); 

    SDL_RenderPresent(renderer);    
}

void InterfazGrafica::renderizarSeleccionPlayer(){
    SDL_SetRenderDrawColor(renderer,106, 101, 255, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarBotonesCharacter();

    SDL_RenderPresent(renderer);
}

void InterfazGrafica::renderizarTablaResultados(){
    SDL_SetRenderDrawColor(renderer,106, 101, 255, 1);
    SDL_RenderClear(renderer);

    spritesManager->renderizarPosicionesFinales(infoJuego.rankingPlayers);

    SDL_RenderPresent(renderer);
}

void InterfazGrafica::efectosArma(TipoArma &arma) {
    switch (arma) {
        case Tipo_1:
            effectsPlayer.play_effect(SHOOTING_EFFECT_PATH);
            break;
        case Tipo_2:
            effectsPlayer.play_effect(SHOOTING_ROCKET_EFFECT_PATH);
            break;
        case Tipo_3:
            effectsPlayer.play_effect(SHOOTING_ROCKET_EFFECT_PATH);
            break;
        case Tipo_4:
            effectsPlayer.play_effect(SHOOTING_ROCKET_EFFECT_PATH);
            break;
    }
}

void InterfazGrafica::efectosPlayer(EstadosPlayer &estado, InfoPlayer &infoPlayer) {
    if (estado == estado_anterior_player) {
        return;
    } else if (estado_anterior_player == EstadosPlayer::Falling && estado != EstadosPlayer::Shooting) {
        effectsPlayer.play_effect(TOUCHING_GROUND_EFFECT_PATH);
    } else if ((estado_anterior_player == EstadosPlayer::Falling && estado == EstadosPlayer::Shooting) ||
               (estado_anterior_player == EstadosPlayer::Walking && estado == EstadosPlayer::Shooting) ||
               (estado_anterior_player == EstadosPlayer::Running && estado == EstadosPlayer::Shooting) ||
               (estado_anterior_player == EstadosPlayer::Jumping && estado == EstadosPlayer::Shooting)) {
        // TODO: arreglar
        efectosArma(infoPlayer.arma);
    }
    switch (estado) {
        case EstadosPlayer::Shooting:
            efectosArma(infoPlayer.arma);
            break;
        case EstadosPlayer::Jumping:
            effectsPlayer.play_effect(JUMPING_EFFECT_PATH);
            break;
        case EstadosPlayer::Damaged:
            if (infoPlayer.tipoPlayer == TipoPlayer::Jazz) {
                effectsPlayer.play_effect(JAZZ_HURT_EFFECT_PATH);
            } else if (infoPlayer.tipoPlayer == TipoPlayer::Spaz) {
                effectsPlayer.play_effect(SPAZ_HURT_EFFECT_PATH);
            } else {
                effectsPlayer.play_effect(LORI_HURT_EFFECT_PATH);
            }
            break;
        case EstadosPlayer::IntoxicatedIdle:
            effectsPlayer.play_effect(INTOXICATED_EFFECT_PATH);
            break;
        case EstadosPlayer::SpecialAttack:
            effectsPlayer.play_effect(SPECIAL_ATTACK_EFFECT_PATH);
            break;
        case EstadosPlayer::Dying:
            effectsPlayer.play_effect(DEATH_EFFECT_PATH);
            break;
        /*case EstadosPlayer::Reviving:
            effectsPlayer.play_effect(REVIVING_EFFECT_PATH);
            break;*/
        default:
            break;
    }
    estado_anterior_player = estado;
}

void InterfazGrafica::efectosEnemy(EstadosEnemy &estado, InfoEnemigo &infoEnemigo) {
    if (estado == estado_anterior_enemy) {
        return;
    }
    switch (estado) {
        case EstadosEnemy::Damaged:
            effectsPlayer.play_effect(ENEMY_HURT_EFFECT_PATH);
            break;
        case EstadosEnemy::Death:
            if (enemigo_muerto.count(&infoEnemigo) && enemigo_muerto[&infoEnemigo]) {
                break;
            }
            effectsPlayer.play_effect(ENEMY_DEATH_EFFECT_PATH);
            enemigo_muerto[&infoEnemigo] = true;
            break;
        default:
            if (estado_anterior_enemy == EstadosEnemy::Death) {
                break;
            }
            enemigo_muerto[&infoEnemigo] = false;
            break;
    }
    estado_anterior_enemy = estado;
}

void InterfazGrafica::cerrarInterfaz() 
{
    this->is_running = false;
    eventHandler->stop();
    eventHandler->join();
    delete eventHandler;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//destructor
InterfazGrafica::~InterfazGrafica()
{
    std::cout << "fin interfaz" << std::endl; 
    this->is_running = false;
    eventHandler->stop();
    eventHandler->join();
    delete eventHandler;
    delete spritesManager;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
