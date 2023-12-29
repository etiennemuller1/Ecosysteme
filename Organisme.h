#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
using namespace std;
class Organisme
{
public:
	virtual void seNourir() = 0;
	virtual Organisme* seReproduire() = 0;
	virtual void mourir()=0;
	virtual void vieillir(float dt)=0;
	virtual void mettreAJour(float dt,vector<Organisme*> organismes, vector<Organisme*> &nouveauxOrganismes) = 0;
	virtual void afficher() = 0;

	void perdreEnergie(float energiePerdu);
	void gagnerEnergie(float energieGagner);

	Vector3 getPosition();
	float getEnergie();
	float getAge();
	float getAgeMax();
	float getEnergieMax();
	bool getEnReproduction();
	float getAgeReproduction();
	float getEnergieDonner();
	float getDistanceMaxReproduction();
	float getEnergieReproduction();
	bool estVivant();
	float getPerteEnergieMaxAge();
	float getEnergieInitial();

	

protected:
	Vector3 position;
	float energieInitial;
	float energie;
	float age;
	float ageMax;
	float energieMax;
	float perteEnergieMaxAge;
	bool enReproduction = false;
	float ageReproduction;
	float energieReproduction;
	float distanceMaxReproduction;
	float energieDonner;
	bool vivant = true;
};

