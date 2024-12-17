#include "TrapCenter.h"
#include <string>
#include "Utils.h"
#include "traps/Iron.h"
#include "traps/Arrow.h"
#include "traps/Fort.h"
#include "traps/Wheel.h"
#include "data/DataCenter.h"
#include <allegro5/allegro_primitives.h>
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <array>
#include <ctime>
#include <iostream>
#include <random>
// using namespace std;

// fixed settings
// namespace LevelSetting {
// 	constexpr char level_path_format[] = "./assets/level/LEVEL%d.txt";
// 	//! @brief Grid size for each level.
// 	constexpr array<int, 4> grid_size = {
// 		40, 40, 40, 40
// 	};
// 	constexpr int monster_spawn_rate = 90;
// };

void TrapCenter::init() {
    trap_num = 0;
    trap_time = 5;
    same = 0;
    lasttrap = -1;
	return ;
}





/**
 * @brief Updates monster_spawn_counter and create monster if needed.
*/
void
TrapCenter::update() {
    static int prev_time = 0;
    DataCenter *DC = DataCenter::get_instance();
    
    std::time_t end_time = std::time(nullptr); // 紀錄結束時間
    int now_time = std::difftime(end_time, DC->start_time);
    //std::cout << DC->start_time << ", " << end_time << ", " <<now_time << "\n";
    if(prev_time != now_time){
        prev_time = now_time;
        std::cout << "now second:" << now_time << "\n";
    }
    
    
    if(now_time > 0 && now_time % trap_time==0 && trap_num < now_time/trap_time){
        srand(time(0));
        int rnum = rand()%int(TrapType::TrapType_MAX);
        if(rnum == lasttrap){
            if(same == 1){
                rnum++;
                rnum%=int(TrapType::TrapType_MAX);
                same = 0;
            }
            else same++;
        }
        //以下random不同的case，依據case生出不同陷阱
        rnum = 2;
        switch(rnum){
            case(0):
                DC->irons.emplace_back(Iron::createIron());
                break;
            case(1):
                DC->arrows.emplace_back(Arrow::createArrow());
                break;
            case(2):
                DC->wheels.emplace_back(Wheel::createWheel());
                break;
            case(3):
                DC->forts.emplace_back(Fort::createFort());
                break;
            default:
                DC->arrows.emplace_back(Arrow::createArrow());
                break;
        }
        DC->arrows.emplace_back(Arrow::createArrow());
        
        //以上random不同的case，依據case生出不同陷阱 
        trap_num++;
        lasttrap = rnum;
    }
}

