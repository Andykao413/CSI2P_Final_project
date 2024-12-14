#include "TrapCenter.h"
#include <string>
#include "Utils.h"
#include "traps/Iron.h"
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
	return ;
}





/**
 * @brief Updates monster_spawn_counter and create monster if needed.
*/
void
TrapCenter::update() {
    DataCenter *DC = DataCenter::get_instance();
    
    std::time_t end_time = std::time(nullptr); // 紀錄結束時間
    int now_time = std::difftime(end_time, DC->start_time);
    //std::cout << DC->start_time << ", " << end_time << ", " <<now_time << "\n";

    
    if(now_time > 0 && now_time % trap_time==0 && trap_num < now_time/trap_time){
        //以下random不同的case，依據case生出不同陷阱 
        DC->irons.emplace_back(Iron::createIron());
        //以上random不同的case，依據case生出不同陷阱 
        trap_num++;
    }

}

