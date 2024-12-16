#include "DataCenter.h"
#include <cstring>
#include "../Level.h"
#include "../Player.h"
#include "../monsters/Monster.h"
#include "../traps/Iron.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
#include "../Rabbit.h"
#include "../Plat.h"
#include "../Carrot.h"
#include "../TrapCenter.h"
#include "../traps/Iron.h"
#include "../traps/Arrow.h"
#include <ctime>




// fixed settings
namespace DataSetting {
	constexpr double FPS = 60;
	constexpr int window_width = 1920;
	constexpr int window_height = 1080;
	constexpr int game_field_length = 1080;

	//map constant
	const double G = 1.5;
	const int sky_y = 0;
	const int floor_y = 900;
	const int wall_lx = 100;
	const int wall_rx = 1820;
	std::time_t start_time; //since 1970

}

DataCenter::DataCenter() {
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;

	this->G = DataSetting::G;
	this->sky_y = DataSetting::sky_y;
	this->floor_y = DataSetting::floor_y;
	this->wall_lx = DataSetting::wall_lx;
	this->wall_rx = DataSetting::wall_rx;
	this->start_time = DataSetting::start_time;


	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	player = new Player();
	level = new Level();
	trapcenter = new TrapCenter();
	rabbit = new Rabbit();
	plat = new Plat();
	carrot = new Carrot();
	//iron = new Iron();
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
	for(Iron *&b : irons) {
		delete b;
	}
	for(Arrow *&b : arrows) {
		delete b;
	}
	delete rabbit;
	delete carrot;
	delete plat;
}
