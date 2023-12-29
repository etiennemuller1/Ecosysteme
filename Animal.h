#pragma once
#include"Organisme.h"
#include <vector>
using namespace std;

class Animal : public Organisme
{
public:
	virtual bool chercherNourriture(Vector3* posNourriture, vector<Organisme*> organismes) = 0;
	virtual bool chercherPartenaire(Vector3* posPartenaire, vector<Organisme*> organismes) = 0;
	void chercher(vector<Organisme*> organismes);
	void mourir() override;
	void vieillir(float dt)override;
	void allerVers(Vector3 position);
	void seDeplacer(float dt);
	bool attaquer(Animal* proie,float dt);
	float getPuissance();
	float getVitesse();
	float getPuissanceMax();
	float getPorteVision();
	Vector3 getDirection();
	void setDirection(Vector3 direction);
	void setPartenaire(Animal* partenaire);
	Animal* getPartenaire();
	void setProie(Organisme* proie);
	Organisme* getProie();
	void unsetProie();
	void unsetPartenaire();
	float getPertePuissanceAge();
	float getPorteAttaque();
	float getPuissanceInitial();
	float getVitesseInitial();
	float getPerteVitesseAge();

protected:
	float perteVitesseAge;
	Vector3 direction;
	float vitesseInitial;
	float vitesse;
	float puissanceInitial;
	float puissance;
	float puissanceMax;
	float pertePuissanceAge;
	float porteVision;
	float porteAttaque;
	Animal* partenaire = nullptr;
	Organisme* proie = nullptr;
};

