#include "Wheel.h"
#include <iostream>
#include <cstdio>
#include <string>
#include "../data/GIFCenter.h"
#include "../algif5/algif.h"
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
#include <random>




typedef unsigned long long size_t;

namespace WheelSetting {
    
	static constexpr char wheel_imgs_root_path[40] = {
		"./assets/image/trap",
	};
	static constexpr char pic_postfix[][10] = {
		"left", "right", "down"
	};
}

// void Iron::init(){
//     char buffer[50] = "./assets/image/trap/Iron.png";
//     pngPath = buffer;
    
// 	DataCenter *DC = DataCenter::get_instance();
//     //gifcenter VS imagecenter
// 	ImageCenter *IMG = ImageCenter::get_instance();
// 	ALLEGRO_BITMAP *img = IMG->get(pngPath);
	

//     // 使用當前時間初始化隨機數種子
//     srand(time(0)); 
//     // 生成 1 到 7 之間的隨機數
//     int randomNumber = rand() % 7 + 1; 
// 	//hitbox
// 	shape.reset();
// 	shape.reset(new Circle{DC->window_width/8*randomNumber, DC->window_height + al_get_bitmap_height(img)/2, al_get_bitmap_width(img)});
// 	//Rectangle:左上到右下的座標

//     srand(time(0)); 
//     // 生成 1 到 7 之間的隨機數
//     randomNumber = rand() % 3; 
//     if(randomNumber == 0){ speed_x = -speed; speed_y = speed;}
//     else if(randomNumber == 1){ speed_x = 0; speed_y = speed;}
//     else{speed_x = speed; speed_y = speed;}
//     std::cout << randomNumber <<","<< speed_x << "," << speed_y << "\n";

 
// }

Wheel* Wheel::createWheel(){
    return new Wheel();
}

Wheel::Wheel(){
    srand(time(0)); 
    int type = rand() % 2; 
    for(size_t type=0; type < static_cast<size_t>(WheelState::WHEELSTATE_MAX); ++type){
        char buffer[50];
        sprintf(
		buffer, "%s/wheel_%s.gif",
		WheelSetting::wheel_imgs_root_path,
		WheelSetting::pic_postfix[static_cast<size_t>(type)]); //把字串印到buffer[50]裡面
        gifPath[static_cast<WheelState>(type)] = std::string(buffer);
    }
    
	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
    GIFCenter *GIFC = GIFCenter::get_instance();

    
    srand(time(0));
    int speed_type = rand() % 2; 
	
    std::cout << "create Wheel \n";
	//hitbox
    if(speed_type==0){
        speed = 5;
        speed_x = 0;
        speed_y = speed;
    }else{
        speed = 10;
        speed_x = 0;
        speed_y = speed;
    }
    if(type==0){
        state = WheelState::LEFT;
        ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
        shape.reset();
	    //shape.reset(new Rectangle{DC->wall_lx, DC->sky_y, DC->wall_lx +gif->width,  DC->sky_y + gif->height});
        shape.reset(new Rectangle{DC->wall_lx, DC->sky_y, DC->wall_lx,  DC->sky_y + gif->height});
        height = gif->height;
        width = gif->width;
    }else{
        state = WheelState::RIGHT;
        ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
        shape.reset();
	    //shape.reset(new Rectangle{DC->wall_rx - gif->width, DC->sky_y, DC->wall_rx,  DC->sky_y + gif->height});
        shape.reset(new Rectangle{DC->wall_rx , DC->sky_y, DC->wall_rx,  DC->sky_y + gif->height});
        height = gif->height;
        width = gif->width;
    }

    

    
	

}

void Wheel::draw(){
    GIFCenter *GIFC = GIFCenter::get_instance();
	ALGIF_ANIMATION *gif = GIFC->get(gifPath[state]);
	algif_draw_gif(
		gif,
		shape->center_x() - gif->width / 2,
		shape->center_y() - gif->height / 2, 0); //左上角座標
}

void Wheel::update(){
    DataCenter *DC = DataCenter::get_instance();
    switch(state){
        case(WheelState::LEFT):{
            if(shape->center_y() < DC->sky_y){
                shape->update_center_x(DC->wall_lx);
                shape->update_center_y(DC->sky_y);
                speed_y = speed_y*-1;
            }
            if(shape->center_y() > DC->floor_y){
                shape->update_center_x(DC->wall_lx+10);
                shape->update_center_y(DC->floor_y + height/2 - 20);
                speed_y = 0;
                speed_x = speed;
                state = WheelState::DOWN;
            }
            break;
        }
        case(WheelState::RIGHT):{
            if(shape->center_y() < DC->sky_y){
                shape->update_center_x(DC->wall_rx);
                shape->update_center_y(DC->sky_y);
                speed_y = speed_y * -1;
            }
            if(shape->center_y() > DC->floor_y){
                shape->update_center_x(DC->wall_rx-10);
                shape->update_center_y(DC->floor_y + height/2 - 20);
                speed_y = 0;
                speed_x = speed * -1;
                state = WheelState::DOWN;
            }
            break;
        }
        case(WheelState::DOWN):{
            if(shape->center_x() > DC->wall_rx){
                shape->update_center_x(DC->wall_rx);
                shape->update_center_y(DC->floor_y);
                speed_y = speed * -1;
                speed_x = 0;
                state = WheelState::RIGHT;
            }
            if(shape->center_x() < DC->wall_lx){
                shape->update_center_x(DC->wall_lx);
                shape->update_center_y(DC->floor_y);
                speed_y = speed * -1;
                speed_x = 0;
                state = WheelState::LEFT;
            }
            break;
        }
    }

    
    shape->update_center_y(shape->center_y()+speed_y);
	shape->update_center_x(shape->center_x()+speed_x);
    // shape->update_center_y(500);
	// shape->update_center_x(500);

}

