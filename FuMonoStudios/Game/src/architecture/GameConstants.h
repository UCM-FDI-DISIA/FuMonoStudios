#pragma once
#include <string>

#pragma region Paths
/*========================================================================================
* PATHS
*=====================================================================================*/
const std::string DIFF_SETTINGS_PATH = "recursos/config/mail.dificulty.json";
const std::string REMITENT_SETTINGS_PATH = "recursos/config/mail.destinatarios.json";
const std::string DIR_SETTINGS_PATH = "recursos/config/mail.direcctions.json";
const std::string SAVE_PATH = "recursos/data/saveFile.json";
const std::string NPC_DATA_PATH = "recursos/data/npcData.json";
const std::string TAPE_ROUTE_PATH = "recursos/data/rutas.JSON";
const std::string SOUNDS_PATH = "recursos/config/sounds.json";
const std::string END_PATH = "recursos/data/ends.json";
const std::string DIALOGS_PATH = "recursos/data/dialogos.json";
const std::string BOSS_EVENTS_PATH ="recursos/data/eventosjefe.json";
const std::string PERSISTENT_DATA_PATH = "recursos/config/persistentData.json";
#pragma endregion

#pragma region General
/*========================================================================================
* GENERAL CONSTANTS
*=====================================================================================*/
constexpr int INITIAL_MONEY = 0;
constexpr int INITIAL_FINAL = 0;
constexpr int INITIAL_EVENT = 0;
constexpr int INITIAL_DAY = 1;
constexpr int MAX_DAYS = 14;
constexpr int INITIAL_TUBE_AMOUNT = 1;
constexpr int WRITE_PACAGES_VALUE = 20;
constexpr int WRONG_PACAGES_VALUE = 30;
constexpr int MINIGAME_TIME = 154;
constexpr int INITIAL_FAILS_MARGIN = 1;
constexpr int LOGICAL_RENDER_WIDTH = 1920;
constexpr int LOGICAL_RENDER_HEITH = 1080;
constexpr int MAX_DISTRICTS = 7;
constexpr int MIN_HAPPINES = 1;
constexpr int MAX_HAPPINES = 99;
constexpr int BAD_HAPPINES = 30;
constexpr int NORMAL_HAPPINES = 65;
constexpr int UNLOCK_UPGRADE_HAPPINES = 90;
constexpr int RENT_VALUE = 100;
constexpr float GRAVITY_LIMIT = 625.0f; // Limite de gravedad (donde tenemos el suelo)
constexpr float DEFAUTL_FORCE = 9.8f * 4; // Fuerza de gravedad por deferto
constexpr float MAX_VELOCITY = 30.0f; // Limite de aceleracion
#pragma endregion

#pragma region Mejoras
/*========================================================================================
* UPGRADES SETTINGS
*=====================================================================================*/
constexpr int SOLDIER_NUM_FAIL = 2;
constexpr int CONTABLE_PLUS_MONEY = 10;
#pragma endregion 


#pragma region Package
/*========================================================================================
* PACKAGE SETTINGS
*=====================================================================================*/
constexpr int PESADO_MAX = 75;	//Limite del peso maximo de paquetes pesados 
constexpr int MEDIO_MAX = 50;	//Limite del peso maximo de paquetes de peso medio 
constexpr int LIGERO_MAX = 25;	//Limite del peso maximo de paquetes ligeros
constexpr int PAQUETE_MIN = 10;	//Limite del peso manimo de paquetes ligeros
constexpr int PESO_CARTA = 2;	//Peso carta
// posicion y tamano Tipo sellos
constexpr int TIPO_SELLO_POS_X = 10;
constexpr int TIPO_SELLO_POS_Y = 60;
constexpr int TIPO_SELLO_SIZE = 80;
// posicion y tamano Fragil sellos
constexpr int FRAGIL_SELLO_POS_X = 100;
constexpr int FRAGIL_SELLO_POS_Y = 60;
constexpr int FRAGIL_SELLO_SIZE = 80;
// posicion y tamano Peso sellos
constexpr int PESO_SELLO_POS_X = 190;
constexpr int PESO_SELLO_POS_Y = 60;
constexpr int PESO_SELLO_SIZE = 80;
//Escala del paquete 
constexpr float PAQUETE_SIZE = 0.25f;
// Probabilidad de carta en porcentaje
constexpr float PROBABILIDAD_CARTA = 7;
// probabilidad de paquete NPC
constexpr int PROBABILIDAD_NPC_Q1 = 70;
constexpr int PROBABILIDAD_NPC_Q2 = 80;
constexpr int PROBABILIDAD_NPC_Q3 = 90;
constexpr int PROBABILIDAD_NPC_Q4 = 100;
#pragma endregion
