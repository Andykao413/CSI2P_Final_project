#ifndef PLAT_H_INCLUDED //標頭檔保護
#define PLAT_H_INCLUDED
#include "Object.h"
#include <map>
#include <string>
#include <vector>
#include "./data/DataCenter.h"

enum class PlatState {
    ONE,
    TWO,
	PLATSTATE_MAX
};

typedef struct _Tile{
    PlatState len;
    double x;
    double y;

}Tile;



class Plat : public Object
{

public:
	void init();
	void draw();
    void update(){
        return ;
    };
    std::vector<Tile> get_tiles(){
        return tiles;
    }

    double get_width(PlatState l){
        if(l == PlatState::ONE){
            return width_ONE;
        }else if(l == PlatState::TWO){
            return width_TWO;
        }else{
            return 0;
        }
    }

private:
	std::vector<Tile> tiles;
    std::map<PlatState, std::string> pngPath;
    double width_ONE;
    double width_TWO;

};



#endif 