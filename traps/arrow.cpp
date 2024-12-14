#include "Arrow.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "../data/DataCenter.h"
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

namespace RabbitSetting {
    
	static constexpr char rabbit_imgs_root_path[40] = {
		"./assets/image",
	};
	static constexpr char pic_postfix[][10] = {
		
	};
}

Arrow* Arrow::createArrow(){
    return new Arrow();
}

Arrow::Arrow(){
    
    char buffer[50] = "./assets/image/trap/Arrow.png";
    pngPath = buffer;
    
	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
	ImageCenter *IMG = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IMG->get(pngPath);
	
    srand(time(0)); 
    // 生成 1 到 7 之間的隨機數
    int randomNumber = rand() % 20 + 1; 
	//hitbox
	shape.reset();
	shape.reset(new Rectangle{80*randomNumber,-al_get_bitmap_height(img),80*randomNumber+al_get_bitmap_width(img)/5,-al_get_bitmap_height(img)});
	//Rectangle:左上到右下的座標
}

void Arrow::draw(){
    ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IC->get(pngPath);
	al_draw_bitmap(
		img,
		shape->center_x() - al_get_bitmap_width(img) / 2,
		shape->center_y() - al_get_bitmap_height(img) / 2, 0); //左上角座標
}

void Arrow::update(){
    DataCenter *DC = DataCenter::get_instance();
    if(shape->center_y() < DC->sky_y-10){
        shape->update_center_y(shape->center_y()+ini_speed);
    }
    else    shape->update_center_y(shape->center_y()+flyspeed);
    // shape->update_center_y(500);
	// shape->update_center_x(500);

}

