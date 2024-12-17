#ifndef FORTFortbullet_H_INCLUDED
#define FORTFortbullet_H_INCLUDED

#include "../Object.h"
#include <allegro5/bitmap.h>
#include <string>

/**
 * @brief The Fortbullet shot from Fort.
 * @see Fort
 */
class Fortbullet : public Object
{
public:
	Fortbullet(const Point &p);
	void update();
	void draw();
private:
	double vx;
	std::string pngPath;
};

#endif
