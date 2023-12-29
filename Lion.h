#pragma once
#include "Carnivore.h"
#include "raylib.h"
#include <cstdlib> 

class Lion : public Carnivore
{
public:
	Lion(Vector3 position, Vector3 direction);
	void afficher() override;
	void mettreAJour(float dt,vector<Organisme*> organismes, vector<Organisme*> &nouveauxOrganismes)override;
	bool chercherNourriture(Vector3* posNourriture, vector<Organisme*> organismes)override;
	bool chercherPartenaire(Vector3* posPartenaire, vector<Organisme*> organismes)override;
	void seNourir() override;
	Lion* seReproduire() override;
	void calculerStatistiquesEnfant(Lion* enfant);

};

