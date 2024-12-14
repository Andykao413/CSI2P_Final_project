#ifndef IRON_H_INCLUDED //標頭檔保護
#define IRON_H_INCLUDED
#include "../Object.h"
#include <map>
#include <string>
#include <queue>

enum class IronState {
    LEFT,
    RIGHT,
	RABBITSTATE_MAX
};

class Iron : public Object
{

public:
	//void init();
	void update();
	void draw();
    static Iron* createIron();
    Iron();


private:
    double speed = 10;
    double speed_x;
	double speed_y;
    std::string pngPath;
	
};



#endif 