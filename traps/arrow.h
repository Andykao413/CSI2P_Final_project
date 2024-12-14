#ifndef ARROW_H_INCLUDED //標頭檔保護
#define ARROW_H_INCLUDED
#include "../Object.h"
#include <map>
#include <string>
#include <queue>

enum class ArrowState {
    LEFT,
    RIGHT,
	RABBITSTATE_MAX
};

class Arrow : public Object
{

public:
	//void init();
	void update();
	void draw();
    static Arrow* createArrow();
    Arrow();


private:
    const double ini_speed = 2;
    const double flyspeed = 10;
    std::string pngPath;

};



#endif 