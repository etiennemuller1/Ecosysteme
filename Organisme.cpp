#include "Organisme.h"

Vector3 Organisme::getPosition()
{
    return position;
}

void Organisme::perdreEnergie(float energiePerdu)
{
    energie -= energiePerdu;
    if (energie <= 0) mourir();
}

void Organisme::gagnerEnergie(float energieGagner)
{
    energie += energieGagner;
}

float Organisme::getEnergie()
{
    return energie;
}

float Organisme::getAge()
{
    return age;
}

float Organisme::getAgeMax()
{
    return ageMax;
}

float Organisme::getEnergieMax()
{
    return energieMax;
}

bool Organisme::getEnReproduction()
{
    return enReproduction;
}

float Organisme::getAgeReproduction()
{
    return ageReproduction;
}

float Organisme::getEnergieReproduction()
{
    return energieReproduction;
}

bool Organisme::estVivant()
{
    return vivant;
}

float Organisme::getPerteEnergieMaxAge()
{
    return perteEnergieMaxAge;
}

float Organisme::getEnergieInitial()
{
    return energieInitial;
}

float Organisme::getEnergieDonner()
{
    return energieDonner;
}

float Organisme::getDistanceMaxReproduction()
{
    return distanceMaxReproduction;
}


