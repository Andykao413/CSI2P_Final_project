#include "Rabbit.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "./data/DataCenter.h"
#include "./shapes/Rectangle.h"
#include "./data/ImageCenter.h"
#include <allegro5/allegro_primitives.h>

typedef unsigned long long size_t;

namespace RabbitSetting {
	static constexpr char rabbit_imgs_root_path[40] = {
		"./assets/image",
	};
	static constexpr char pic_postfix[2][10] = {
		"left", "right"
	};
}

void Rabbit::init(){
    for(size_t type=0; type < static_cast<size_t>(RabbitState::RABBITSTATE_MAX); ++type){
        char buffer[50];
        sprintf(
		buffer, "%s/rabbit_%s.png",
		RabbitSetting::rabbit_imgs_root_path,
		RabbitSetting::pic_postfix[static_cast<size_t>(type)]); //把字串印到buffer[50]裡面
        pngPath[static_cast<RabbitState>(type)] = std::string(buffer);
    }
	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
	ImageCenter *IMG = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IMG->get(pngPath[RabbitState::RIGHT]);
	
	//hitbox
	shape.reset();
	shape.reset(new Rectangle{DC->window_width/2., DC->window_height/2., DC->window_width/2 + al_get_bitmap_width(img)*0.5, DC->window_height/2 + al_get_bitmap_height(img)*0.5});
	//Rectangle:左上到右下的座標

}

void Rabbit::draw(){
    ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IC->get(pngPath[state]);
	al_draw_bitmap(
		img,
		shape->center_x() - al_get_bitmap_width(img) / 2,
		shape->center_y() - al_get_bitmap_height(img) / 2, 0); //左上角座標
}

void Rabbit::update(){
    DataCenter *DC = DataCenter::get_instance();
	if(shape->center_y() < DC->floor_y){
		speed_y = speed_y + DC->G;
	}else{
		speed_y = 0;
	}

	if((DC->key_state[ALLEGRO_KEY_W] || DC->key_state[ALLEGRO_KEY_SPACE]) && shape->center_y() >= DC->floor_y){
		speed_y  = speed_y - jump_height;

	}else if(DC->key_state[ALLEGRO_KEY_A] && shape->center_x() >= DC->wall_lx){
		shape->update_center_x(shape->center_x()-speed_x);
		state = RabbitState::LEFT;

	}else if(DC->key_state[ALLEGRO_KEY_D] && shape->center_x() <= DC->wall_rx){ 
		shape->update_center_x(shape->center_x()+speed_x);
		state = RabbitState::RIGHT;
	}

	shape->update_center_y(shape->center_y()+speed_y);


}

