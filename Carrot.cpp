#include "Carrot.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "./data/DataCenter.h"
#include "./shapes/Rectangle.h"
#include "./data/ImageCenter.h"
#include <allegro5/allegro_primitives.h>

typedef unsigned long long size_t;

namespace CarrotSetting {
	static constexpr char Carrot_imgs_root_path[40] = {
		"./assets/image",
	};
	static constexpr char pic_postfix[1][10] = {
		"exist"
	};
}

void Carrot::init(){
    for(size_t type=0; type < static_cast<size_t>(CarrotState::CARROTSTATE_MAX); ++type){
        char buffer[50];
        sprintf(
		buffer, "%s/carrot_%s.png",
		CarrotSetting::Carrot_imgs_root_path,
		CarrotSetting::pic_postfix[static_cast<size_t>(type)]); //把字串印到buffer[50]裡面
        pngPath[static_cast<CarrotState>(type)] = std::string(buffer);
    }
	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
	ImageCenter *IMG = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IMG->get(pngPath[CarrotState::EXIST]);
	
	//hitbox
	shape.reset();
	shape.reset(new Rectangle{DC->window_width/2, DC->window_height/2, DC->window_width/2 + al_get_bitmap_width(img), DC->window_height/2 + al_get_bitmap_height(img)});
	//Rectangle:左上到右下的座標

    pos.first = shape->center_x();
    pos.second = shape->center_y();

}

void Carrot::draw(){
    ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IC->get(pngPath[state]);
	al_draw_bitmap(
		img,
		shape->center_x() - al_get_bitmap_width(img) / 2,
		shape->center_y() - al_get_bitmap_height(img) / 2, 0); //左上角座標
}

void Carrot::update(){
    DataCenter *DC = DataCenter::get_instance();
    ImageCenter *IMG = ImageCenter::get_instance();
    if(pos.first>DC->window_width) pos.first-=DC->window_width;
    if(pos.second>DC->window_height) pos.second-=DC->window_height;
    shape->update_center_x(pos.first);
	shape->update_center_y(pos.second);
    ALLEGRO_BITMAP *img = IMG->get(pngPath[CarrotState::EXIST]);
	const double &cx = shape->center_x();
	const double &cy = shape->center_y();
	// We set the hit box slightly smaller than the actual bounding box of the image because there are mostly empty spaces near the edge of a image.
	const int &w = al_get_bitmap_width(img)*0;
	const int &h = al_get_bitmap_height(img)*0;
	shape.reset(new Rectangle{
		(cx - w / 2.), (cy - h / 2.),
		(cx - w / 2. + w), (cy - h / 2. + h)
	});
}

