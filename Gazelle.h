#pragma once
#include "Herbivore.h"
#include "Plante.h"
class Gazelle : public Herbivore
{
public:
	Gazelle(Vector3 position, Vector3 direction);
	void afficher() override;
	void mettreAJour(float dt, vector<Organisme*> organismes, vector<Organisme*>& nouveauxOrganismes)override;
	bool chercherNourriture(Vector3* posNourriture, vector<Organisme*> organismes)override;
	bool chercherPartenaire(Vector3* posPartenaire, vector<Organisme*> organismes)override;
	void seNourir() override;
	Gazelle* seReproduire() override;
	void calculerStatistiquesEnfant(Gazelle* enfant);

};

