#include "DataCenter.h"
#include <cstring>
#include "../Level.h"
#include "../Player.h"
#include "../monsters/Monster.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
#include "../Rabbit.h"
#include "../Plat.h"
#include "../Carrot.h"





// fixed settings
namespace DataSetting {
	constexpr double FPS = 60;
	constexpr int window_width = 1920;
	constexpr int window_height = 1080;
	constexpr int game_field_length = 1080;

	//map constant
	const double G = 1.5;
	const int floor_y = 900;
	const int wall_lx = 100;
	const int wall_rx = 1820;


}

DataCenter::DataCenter() {
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;

	this->G = DataSetting::G;
	this->floor_y = DataSetting::floor_y;
	this->wall_lx = DataSetting::wall_lx;
	this->wall_rx = DataSetting::wall_rx;


	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	player = new Player();
	level = new Level();
	rabbit = new Rabbit();
	plat = new Plat();
	carrot = new Carrot();
}

DataCenter::~DataCenter() {
	delete player;
	delete level;
	for(Monster *&m : monsters) {
		delete m;
	}
	for(Tower *&t : towers) {
		delete t;
	}
	for(Bullet *&b : towerBullets) {
		delete b;
	}
	delete rabbit;
	delete carrot;
}
