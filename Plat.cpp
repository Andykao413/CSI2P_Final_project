#include "Plat.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "./data/DataCenter.h"
#include "./shapes/Rectangle.h"
#include "./data/ImageCenter.h"
#include <allegro5/allegro_primitives.h>

typedef unsigned long long size_t;

namespace PlatSetting {
	static constexpr char plat_imgs_root_path[40] = {
		"./assets/image/tile",
	};
	static constexpr char pic_postfix[2][10] = {
		"1", "2"
	};
}

void Plat::init(){
    for(size_t type=0; type < static_cast<size_t>(PlatState::PLATSTATE_MAX); ++type){
        char buffer[50];
        sprintf(
		buffer, "%s/tile%s.png",
		PlatSetting::plat_imgs_root_path,
		PlatSetting::pic_postfix[static_cast<size_t>(type)]); //把字串印到buffer[50]裡面
        pngPath[static_cast<PlatState>(type)] = std::string(buffer);
    }

	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
	ImageCenter *IMG = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IMG->get(pngPath[PlatState::ONE]);
    width_ONE = al_get_bitmap_width(img);
    img = IMG->get(pngPath[PlatState::TWO]);
    width_TWO = al_get_bitmap_width(img);
	//all tile initalize
    std::vector<Tile> all_tile{
        {PlatState::ONE, DC->window_width/4*1, DC->window_height/4*1-60},
        {PlatState::TWO, DC->window_width/4*2, DC->window_height/4*1-60}, 
        {PlatState::ONE, DC->window_width/4*3, DC->window_height/4*1-60}, 

        {PlatState::TWO, DC->window_width/3*1, DC->window_height/4*2-60}, 
        {PlatState::TWO, DC->window_width/3*2, DC->window_height/4*2-60}, 

        {PlatState::ONE, DC->window_width/4*1, DC->window_height/4*3-60},
        {PlatState::TWO, DC->window_width/4*2, DC->window_height/4*3-60}, 
        {PlatState::ONE, DC->window_width/4*3, DC->window_height/4*3-60}
    };
    for(Tile t: all_tile) tiles.emplace_back(t);

	//hitbox
	// shape.reset();
	// shape.reset(new Rectangle{DC->window_width/2, DC->window_height/2, DC->window_width/2 + al_get_bitmap_width(img), DC->window_height/2 + al_get_bitmap_height(img)});
	//Rectangle:左上到右下的座標

}

void Plat::draw(){
    for(Tile t: tiles){
        ImageCenter *IC = ImageCenter::get_instance();
        ALLEGRO_BITMAP *img = IC->get(pngPath[t.len]);
        al_draw_bitmap(
		img,
		t.x - al_get_bitmap_width(img) / 2,
		t.y - al_get_bitmap_height(img) / 2, 0); //左上角座標
    }
}

