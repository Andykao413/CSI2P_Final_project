#include "Iron.h"
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
	static constexpr char pic_postfix[2][10] = {
		"left", "right"
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

Iron* Iron::createIron(){
    return new Iron();
}

Iron::Iron(){
    
    char buffer[50] = "./assets/image/trap/Iron.png";
    pngPath = buffer;
    
	DataCenter *DC = DataCenter::get_instance();
    //gifcenter VS imagecenter
	ImageCenter *IMG = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IMG->get(pngPath);
	
    //std::cout << "create Iron \n";
    // 使用當前時間初始化隨機數種子
    srand(time(0)); 
    // 生成 1 到 7 之間的隨機數
    int randomNumber = rand() % 7 + 1; 
	//hitbox
	shape.reset();
	shape.reset(new Circle{DC->window_width/8*randomNumber, DC->window_height + al_get_bitmap_height(img)/5, al_get_bitmap_width(img)/5});
	//Rectangle:左上到右下的座標
    

    srand(time(0)); 
    // 生成 1 到 7 之間的隨機數
    randomNumber = rand() % 3; 
    if(randomNumber == 0){ speed_x = -speed; speed_y = speed;}
    else if(randomNumber == 1){ speed_x = 0; speed_y = speed;}
    else{speed_x = speed; speed_y = speed;}
    /*std::cout << "create Iron finish\n";
    std::cout << randomNumber <<","<< speed_x << "," << speed_y << "\n";*/

}

void Iron::draw(){
    ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IC->get(pngPath);
	al_draw_bitmap(
		img,
		shape->center_x() - al_get_bitmap_width(img) / 2,
		shape->center_y() - al_get_bitmap_height(img) / 2, 0); //左上角座標
}

void Iron::update(){
    DataCenter *DC = DataCenter::get_instance();
    if(shape->center_y() < DC->sky_y || shape->center_y() > DC->floor_y ){
        if(shape->center_y() < DC->sky_y){
            shape->update_center_y(DC->sky_y);
        }else if(shape->center_y() > DC->floor_y){
            shape->update_center_y(DC->floor_y);
        }
        speed_y = speed_y * -1;
        
    }
    if(shape->center_x() > DC->wall_rx || shape->center_x() < DC->wall_lx){
        if(shape->center_x() < DC->wall_lx){
            shape->update_center_x(DC->wall_lx);
        }else if(shape->center_x() > DC->wall_rx){
            shape->update_center_x(DC->wall_rx);
        }
        speed_x = speed_x * -1;
    }
    
    shape->update_center_y(shape->center_y()+speed_y);
	shape->update_center_x(shape->center_x()+speed_x);
    // shape->update_center_y(500);
	// shape->update_center_x(500);

}

