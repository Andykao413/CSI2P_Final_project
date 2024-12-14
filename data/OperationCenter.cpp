#include "OperationCenter.h"
#include "DataCenter.h"
#include "../monsters/Monster.h"
#include "../traps/Iron.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
#include "../Player.h"
#include "../Rabbit.h"
#include "../Plat.h"
#include <iostream>
#include "../Rabbit.h"
#include "../Carrot.h"
#include <vector>
#include <stdlib.h>
#include <time.h>

void OperationCenter::update() {
	// Update monsters.
	_update_monster();

	_update_iron();
	// Update towers.
	_update_tower();
	// Update tower bullets.
	_update_towerBullet();
	// If any bullet overlaps with any monster, we delete the bullet, reduce the HP of the monster, and delete the monster if necessary.
	_update_monster_towerBullet();
	// If any monster reaches the end, hurt the player and delete the monster.

	_update_iron_rabbit();

	_update_rabbit_plat();

	_update_rabbit_carrot();
}

void OperationCenter::_update_monster() {
	std::vector<Monster*> &monsters = DataCenter::get_instance()->monsters;
	for(Monster *monster : monsters)
		monster->update();
}


void OperationCenter::_update_iron() {
	//return ;
	std::vector<Iron*> &irons = DataCenter::get_instance()->irons;
	for(Iron *iron : irons)
		iron->update();
}

void OperationCenter::_update_tower() {
	std::vector<Tower*> &towers = DataCenter::get_instance()->towers;
	for(Tower *tower : towers)
		tower->update();
}

void OperationCenter::_update_towerBullet() {
	std::vector<Bullet*> &towerBullets = DataCenter::get_instance()->towerBullets;
	for(Bullet *towerBullet : towerBullets)
		towerBullet->update();
	// Detect if a bullet flies too far (exceeds its fly distance limit), which means the bullet lifecycle has ended.
	for(size_t i = 0; i < towerBullets.size(); ++i) {
		if(towerBullets[i]->get_fly_dist() <= 0) {
			towerBullets.erase(towerBullets.begin()+i);
			--i;
		}
	}
}

void OperationCenter::_update_monster_towerBullet() {
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Monster*> &monsters = DC->monsters;
	std::vector<Bullet*> &towerBullets = DC->towerBullets;
	for(size_t i = 0; i < monsters.size(); ++i) {
		for(size_t j = 0; j < towerBullets.size(); ++j) {
			// Check if the bullet overlaps with the monster.
			if(monsters[i]->shape->overlap(*(towerBullets[j]->shape))) {
				// Reduce the HP of the monster. Delete the bullet.
				monsters[i]->HP -= towerBullets[j]->get_dmg();
				towerBullets.erase(towerBullets.begin()+j);
				--j;
			}
		}
	}
}

void OperationCenter::_update_rabbit_carrot(){
	DataCenter *DC = DataCenter::get_instance();
	Rabbit* rabbit = DC->rabbit;
	Carrot* carrot = DC->carrot;
	Player *&player = DC->player;
	if(rabbit->shape->overlap(*(carrot->shape))) {
		player->score++;
		player->HP++;
		srand(time(0));
		int newposid = rand()%3;
		if(carrot->new_pos[newposid]==carrot->pos){
			newposid++;
			newposid%=3;
		}
		carrot->pos = carrot->new_pos[newposid];
	}
}

void OperationCenter::_update_iron_rabbit() {
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Iron*> &irons = DC->irons;
	Player *&player = DC->player;
	Rabbit *&rabbit = DC->rabbit;
	for(size_t i = 0; i < irons.size(); ++i) {
		if(irons[i]->shape->overlap(*(rabbit->shape))) {
			player->HP = 0;
		}
	}
}

void OperationCenter::_update_rabbit_plat() {
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Tile> tiles = (DC->plat)->get_tiles();
	int temp = 0;
	for(Tile t: tiles) {
		
		double width = (DC->plat)->get_width(t.len);
		double left =  (t.x - width/2);
		double right =  (t.x + width/2);
		double rabbit_speed = (DC->rabbit)->get_speed_y();
		double rabbit_x = (DC->rabbit->shape)->center_x();
		double rabbit_y = (DC->rabbit->shape)->center_y()+90;
		if(rabbit_speed >= 0 && rabbit_y>=t.y-25 && rabbit_y<=t.y &&  rabbit_x>=left && rabbit_x<= right){
			(DC->rabbit->shape)->update_center_y(t.y-90);
			temp = 1;
		}
	}
	(DC->rabbit)->set_steping(temp);
	//std::cout << temp;
}



void OperationCenter::draw() {
	_draw_monster();
	_draw_tower();
	_draw_towerBullet();
	_draw_carrot();
	_draw_iron();
}

void OperationCenter::_draw_monster() {
	std::vector<Monster*> &monsters = DataCenter::get_instance()->monsters;
	for(Monster *monster : monsters)
		monster->draw();
}

void OperationCenter::_draw_iron() {
	//return ;
	std::vector<Iron*> &irons = DataCenter::get_instance()->irons;
	for(Iron *iron : irons)
		iron->draw();
}

void OperationCenter::_draw_tower() {
	std::vector<Tower*> &towers = DataCenter::get_instance()->towers;
	for(Tower *tower : towers)
		tower->draw();
}

void OperationCenter::_draw_towerBullet() {
	std::vector<Bullet*> &towerBullets = DataCenter::get_instance()->towerBullets;
	for(Bullet *towerBullet : towerBullets)
		towerBullet->draw();
}

void OperationCenter::_draw_carrot() {
	Carrot* carrot = DataCenter::get_instance()->carrot;
	carrot->draw();
}
