#pragma once
#include <iostream>
#include <cstdio>
#include "Organisme.h"
#include "Animal.h"
#include "Plante.h"
#include <vector>
#include "Lion.h"
#include "Gazelle.h"
#include "Bananier.h"
using namespace std;
class Environnement
{
	public:
		Environnement(Vector3 centreArene, float rayonArene);
		vector<Organisme*> organismes;
		void ajouterOrganisme(Organisme *organisme);
		void mettreAJour(float dt);
		void afficher();
		void afficher2D();
		void ajouterOrganismesAleatoires(int nombreLions, int nombreGazelles, int nombreBananiers);
		Vector3 obtenirPositionAleatoire();
		Vector3 obtenirDirectionAleatoire();

private:
	Vector3 centreArene;
	float rayonArene;
};

