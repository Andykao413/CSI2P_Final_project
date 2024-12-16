#ifndef FORT_H_INCLUDED //標頭檔保護
#define FORT_H_INCLUDED
#include "../Object.h"
#include "Fortbullet.h"
#include "../shapes/Point.h"
#include <map>
#include <string>
#include <queue>

enum class FortState {
    LEFT,
    RIGHT,
	RABBITSTATE_MAX
};

class Fort : public Object
{

public:
	//void init();
	void update();
	void draw();
    virtual bool attack();
    static Fort* createFort();
    Fort();
    virtual Fortbullet *create_bullet(){
		const Point &p = Point(shape->center_x(), shape->center_y());
		return new Fortbullet(p);
	}

private:
    const int attack_freq = 100;
	int counter;
    std::string pngPath;
};



#endif 