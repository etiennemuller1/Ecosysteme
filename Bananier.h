#pragma once
#include"Plante.h"
#include "raylib.h"
#include <vector>
#include <cstdlib> 
using namespace std;



class Bananier : public Plante
{
public:
	Bananier(Vector3 position);
	void afficher() override;
	void mettreAJour(float dt, vector<Organisme*> organismes, vector<Organisme*>& nouveauxOrganismes)override;
	void seNourir() override;
	Bananier* seReproduire() override;
	bool estManger();
	void produireFruit();
	void setAge(float age);
	void setTempsDepuisDernierFruit(float tps);
	float getTempsEntreFruit();
	void setEnergie(float energie);
	void setNbFruits(int nb);
	int getNombreFruitsMax();

private:
	int nombreFruits = 0;
	int nombreFruitsMax;
	float tempsDepuisDernierFruit;
	float tempsEntreFruits;
	float energieFruit;
};

