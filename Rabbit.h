#ifndef RABBIT_H_INCLUDED //標頭檔保護
#define RABBIT_H_INCLUDED
#include "Object.h"
#include <map>
#include <string>
#include <queue>

enum class RabbitState {
    LEFT,
    RIGHT,
	RABBITSTATE_MAX
};

class Rabbit : public Object
{

public:
	void init();
	void update();
	void draw();

	double get_speed_y(){
		return speed_y;
	}

	void set_steping(int n){
		steping = n;
	}

private:
	int steping;
	RabbitState state = RabbitState::RIGHT;
    double speed_x = 15;
	double speed_y;
	double jump_height = 30;
    std::map<RabbitState, std::string> pngPath;
	
};



#endif 