#include "Fort.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "../data/DataCenter.h"
#include "../data/SoundCenter.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "../data/ImageCenter.h"
#include <allegro5/allegro_primitives.h>
#include <cstdlib>  // 用於 rand() 和 srand()
#include <ctime>    // 用於 time() 初始化隨機種子
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

typedef unsigned long long size_t;

namespace FortSetting {
    
	static constexpr char fort_imgs_root_path[40] = {
		"./assets/image",
	};
	static constexpr char pic_postfix[2][10] = {
		"left", "right"
	};
}

Fort* Fort::createFort(){
    return new Fort();
}

Fort::Fort(){
    srand(time(0));
	int randnum = rand()%2;
	
	if(randnum){
		char buffer[50] = "./assets/image/trap/Fort_right.png";
		pngPath = buffer;
	}
	else{
		char buffer[50] = "./assets/image/trap/Fort_left.png";
		pngPath = buffer;
	}
    //char buffer[50] = "./assets/image/trap/Fort.png";
    
    
	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
	ImageCenter *IMG = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IMG->get(pngPath);

	
	
	//hitbox
	shape.reset();
	if(randnum)
		shape.reset(new Rectangle{DC->wall_rx, DC->window_height/2, DC->wall_rx + al_get_bitmap_width(img), DC->window_height/2 + al_get_bitmap_height(img)});
	else
		shape.reset(new Rectangle{DC->wall_lx-al_get_bitmap_width(img), DC->window_height/2, DC->wall_lx, DC->window_height/2 + al_get_bitmap_height(img)});
	//Rectangle:左上到右下的座標

    counter = attack_freq;
}

bool Fort::attack() {
	if(counter) return false;
	//DataCenter *DC = DataCenter::get_instance();
	//SoundCenter *SC = SoundCenter::get_instance();
	//DC->arrow.emplace_back(create_arrow());
	//SC->play(TowerSetting::attack_sound_path, ALLEGRO_PLAYMODE_ONCE);
    std::cout<<"attack"<<std::endl;
	counter = attack_freq;
	return true;
}

void Fort::draw(){
    ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IC->get(pngPath);
	al_draw_bitmap(
		img,
		shape->center_x() - al_get_bitmap_width(img) / 2,
		shape->center_y() - al_get_bitmap_height(img) / 2, 0); //左上角座標
}

void Fort::update(){
    DataCenter *DC = DataCenter::get_instance();
    if(counter) counter--;
	else{
		std::cout<<"shoot!"<<std::endl;
		DC->fortbullets.emplace_back(create_bullet());
		counter = attack_freq;
	}
}

