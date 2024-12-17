#include "Fortbullet.h"
#include "../data/DataCenter.h"
#include "../data/ImageCenter.h"
#include "../shapes/Circle.h"
#include "../shapes/Point.h"
#include <algorithm>
#include <allegro5/bitmap_draw.h>

Fortbullet::Fortbullet(const Point &p) {
    char buffer[50] = "./assets/image/trap/Fortbullet.png";
    pngPath = buffer;
	ImageCenter *IC = ImageCenter::get_instance();
	ALLEGRO_BITMAP *img = IC->get(pngPath);
	double r = std::min(al_get_bitmap_width(img), al_get_bitmap_height(img)) * 0.5;
	shape.reset(new Circle{p.x, p.y, r});
	if(p.x>DataCenter::get_instance()->window_width/2) vx = -10;
	else vx = 10;
}

/**
 * @brief Update the Fortbullet position by its velocity and fly_dist by its movement per frame.
 * @details We don't detect whether to delete the Fortbullet itself here because deleting a object itself doesn't make any sense.
 */
void
Fortbullet::update() {
	DataCenter *DC = DataCenter::get_instance();
	shape->update_center_x(shape->center_x()+vx);
}

void
Fortbullet::draw() {
    ImageCenter *IC = ImageCenter::get_instance();
    ALLEGRO_BITMAP *img = IC->get(pngPath);
	al_draw_bitmap(
		img,
		shape->center_x() - al_get_bitmap_width(img) / 2,
		shape->center_y() - al_get_bitmap_height(img) / 2, 0);
}
