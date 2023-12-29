#pragma once
#include"Organisme.h"
class Plante : public Organisme
{
public:
	virtual bool estManger() = 0;
	void mourir() override;
	void vieillir(float dt)override;
	bool estComestible();
	void setComestible(bool comestible);


protected:
	bool comestible;
	float distanceMinReproduction;

};

