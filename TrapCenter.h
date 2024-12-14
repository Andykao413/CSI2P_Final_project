#ifndef TRAPCENTER_H_INCLUDED
#define TRAPCENTER_H_INCLUDED

#include <vector>
#include <utility>
#include <tuple>
#include "./shapes/Rectangle.h"

/**
 * @brief The class manages data of each level.
 * @details The class could load level with designated input file and record. The level itself will decide when to create next monster.
 * @see DataCenter::level
 */

enum class TrapType {
    IRON,
	TrapType_MAX
};


class TrapCenter
{
public:
	TrapCenter() {}
	void init();
	void update();

	
private:
    int trap_num;
    int trap_time = 5;
	
};

#endif
