#include "Plante.h"

void Plante::mourir()
{
	vivant = false;
}

void Plante::vieillir(float dt)
{
	age += dt;
	if (age > ageMax) mourir();
}

bool Plante::estComestible()
{
	return comestible;
}

void Plante::setComestible(bool comestible)
{
	this->comestible = comestible;
}
