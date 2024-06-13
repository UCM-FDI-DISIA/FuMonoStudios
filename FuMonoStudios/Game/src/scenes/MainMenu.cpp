#ifndef DEV_TOOLS
#include <utils/checkML.h>
#endif // !DEV_TOOLS
#include "MainMenu.h"
#include <components/Render.h>
#include <architecture/Game.h>
#include <architecture/GeneralData.h>
#include <sistemas/ComonObjectsFactory.h>
#include <sistemas/SoundEmiter.h>

//ecs::MainMenu::MainMenu()
//{
//	init();
//}

ecs::MainMenu::MainMenu() : Scene() {

}

ecs::MainMenu::~MainMenu()
{
}

void ecs::MainMenu::init()
{
#ifdef _DEBUG
	std::cout << "Hola Menu" << std::endl;
#endif // _DEBUG

	sdlutils().clearRenderer();

	Entity* fondo = addEntity(ecs::layer::BACKGROUND);
	Texture* texturaFondo = &sdlutils().images().at("menuPrincipal");
	fondo->addComponent<Transform>(0.0f, 0.0f, LOGICAL_RENDER_WIDTH, LOGICAL_RENDER_HEITH);
	fondo->addComponent<RenderImage>(texturaFondo);

	factory_->setFont("hvdComicSerif");
	factory_->setLayer(layer::UI);

	Vector2D pos(LOGICAL_RENDER_WIDTH - 725, 500);
	bool saveFileExist = file_exist(SAVE_PATH);

	buildStartButton(pos,saveFileExist);

	if (saveFileExist) {
		buildLoadSaveButton(pos);
	}

	if (gD().hasGameEndedOnce()) {
		buildShowEndsButton(pos);
	}

	buildConfigButton(pos);

	buildExitButton(pos);

	SoundEmiter::instance()->playMusic("mainMenu");
	factory_->setFont("arial");
}

ecs::Entity* ecs::MainMenu::buildStartButton(Vector2D& pos,bool saveExist)
{
	auto start = factory_->createTextuButton(pos, "Nueva partida", 50, [this, saveExist]() {
		int buttonId = 1;
		if (saveExist) {

			const SDL_MessageBoxButtonData buttons[] = {
			{ /* .flags, .buttonid, .text */        0, 0, "no" },
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "si" },
			};
			SDL_MessageBoxData data;
			data.flags = SDL_MESSAGEBOX_INFORMATION;
			data.window = sdlutils().window();
			data.title = "Archivo de guardado Existente";
			data.message = "Archivo de guardado detectado\nAl empezar una nueva partida se sobreescribiran los datos del archivo de guardado anterior\nEstas seguro?";
			data.numbuttons = SDL_arraysize(buttons);
			data.buttons = buttons;
			data.colorScheme = NULL;
			SDL_ShowMessageBox(&data, &buttonId);
		}
		if (buttonId == 1) {
			sdlutils().musics().at("mainMenu").haltMusic();
			gD().newGame();
			gD().saveGame();
			gm().requestChangeScene(ecs::sc::MENU_SCENE, ecs::sc::INTRO_SCENE);
		}
		}, "click", textColor_);
	pos.setY(pos.getY() + 100);
	factory_->addHoverColorMod(start,hilightColor_);
	return start;
}

ecs::Entity* ecs::MainMenu::buildLoadSaveButton(Vector2D& pos)
{
	auto loadSave = factory_->createTextuButton(pos, "Cargar partida guardada", 50, [this]() {
		sdlutils().musics().at("mainMenu").haltMusic();
		gm().requestChangeScene(ecs::sc::MENU_SCENE, ecs::sc::EXPLORE_SCENE);
		try {
			gD().loadSaveFile();
		}
		catch (save_Missing& e) {
			std::string god = e.what();
			god += "se cargara una nueva partida desde el dia 1";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "ERROR", god.c_str(), sdlutils().window());
			gD().newGame();
		}
		}, "click", textColor_);
	pos.setY(pos.getY() + 100);
	factory_->addHoverColorMod(loadSave,hilightColor_);
	return loadSave;
}

ecs::Entity* ecs::MainMenu::buildShowEndsButton(Vector2D& pos)
{
	auto endScene = factory_->createTextuButton(pos, "Mostramos Final Juego", 50, [this]() {
		sdlutils().musics().at("mainMenu").haltMusic();
		gm().requestChangeScene(ecs::sc::MENU_SCENE, ecs::sc::FINALS_INFO_SCENE);
		}, "click", textColor_);
	pos.setY(pos.getY() + 100);
	factory_->addHoverColorMod(endScene, hilightColor_);
	return endScene;
}

ecs::Entity* ecs::MainMenu::buildConfigButton(Vector2D& pos)
{
	auto ajustes = factory_->createTextuButton(pos, "Configuracion", 50, [this]() {
		sdlutils().musics().at("mainMenu").haltMusic();
		gm().requestChangeScene(ecs::sc::MENU_SCENE, ecs::sc::CONFIG_SCENE);
		}, "click", textColor_);
	pos.setY(pos.getY() + 100);
	factory_->addHoverColorMod(ajustes, hilightColor_);
	return ajustes;
}

ecs::Entity* ecs::MainMenu::buildExitButton(Vector2D& pos)
{
	auto exit = factory_->createTextuButton(pos, "Salir", 50, [this]() {
		sdlutils().musics().at("mainMenu").haltMusic();
		gm().endGame();
		}, "click", textColor_);
	factory_->addHoverColorMod(exit, hilightColor_);
	return exit;
}
