#ifndef WHEEL_H_INCLUDED //標頭檔保護
#define WHEEL_H_INCLUDED
#include "../Object.h"
#include <map>
#include <string>
#include <queue>

enum class WheelState {
    LEFT,
    RIGHT,
    DOWN,
	WHEELSTATE_MAX
};

class Wheel : public Object
{

public:
	//void init();
	void update();
	void draw();
    static Wheel* createWheel();
    Wheel();


private:
    WheelState state;
    double speed;
    double speed_x;
	double speed_y;
    double height; 
    double width;
    std::map<WheelState, std::string> gifPath;

};



#endif 