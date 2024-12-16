#ifndef CARROT_H_INCLUDED //標頭檔保護
#define CARROT_H_INCLUDED
#include "Object.h"
#include <map>
#include <string>
#include <queue>

enum class CarrotState {
    EXIST,
	CARROTSTATE_MAX
};

class Carrot : public Object
{

public:
	void init();
	void update();
	void draw();
    std::pair<double,double> pos;
    const std::pair<double,double> new_pos[17] = {
        {500,650},{870,650},{1050,650},{1450,650},
        {550,390},{650,390},{750,390},{1200,390},{1400,390},
        {500,920},{870,920},{1050,920},{1450,920},
        {1450,120},{1050,120},{870,120},{500,120}
    };
    const int posnum = 17;
private:
	CarrotState state = CarrotState::EXIST;
    std::map<CarrotState, std::string> pngPath;
};



#endif 