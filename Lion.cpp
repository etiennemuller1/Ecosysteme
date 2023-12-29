#include "Lion.h"

Lion::Lion(Vector3 position, Vector3 direction)
{
	this->position = position;
	this->direction = direction;
	this->energieInitial = 500;
	this->energie = energieInitial;
	this->energieMax = 2000;
	this->age = 0;
	this->ageMax = 23;
	this->perteEnergieMaxAge = 20;
	this->perteVitesseAge = 1.8f/10;
	this->ageReproduction = 4;
	this->energieReproduction = 600;
	this->distanceMaxReproduction = pow(1,2);
	this->energieDonner = 500;
	vitesseInitial = 90.0f / 10;
	this->vitesse = vitesseInitial;
	puissanceInitial = 280;
	this->puissance = puissanceInitial;
	this->puissanceMax = 500;
	this->pertePuissanceAge = 4;
	this->porteVision = pow(40,2);
	this->porteAttaque = pow(1,2);
}

void Lion::afficher()
{
	if (age < ageReproduction) {
		DrawSphere(position, 0.2, ORANGE);

		Vector3 posTete = Vector3Add({ 0,0.15,0 }, Vector3Add(position, Vector3Multiply(direction, { 0.25,0,0.25 })));
		DrawSphere(posTete, 0.1, ORANGE);

		Vector3 posCri = Vector3Add({ 0,0.15,0 }, Vector3Add(position, Vector3Multiply(direction, { 0.15,0,0.15 })));
		DrawSphere(posCri, 0.15, BROWN);
	}
	else
	{
		DrawSphere(position, 0.4, ORANGE);

		Vector3 posTete = Vector3Add({ 0,0.3,0 }, Vector3Add(position, Vector3Multiply(direction, { 0.5,0,0.5 })));
		DrawSphere(posTete, 0.2, ORANGE);

		Vector3 posCri = Vector3Add({ 0,0.3,0 }, Vector3Add(position, Vector3Multiply(direction, { 0.3,0,0.3 })));
		DrawSphere(posCri, 0.3, BROWN);
	}
}


void Lion::mettreAJour(float dt, vector<Organisme*> organismes, vector<Organisme*>& nouveauxOrganismes)
{
	chercher(organismes);

	if(proie != nullptr)
	{
		Animal* animal = dynamic_cast<Animal*>(proie);
		if (animal != nullptr)
		{
			if(attaquer(animal,dt))
			{
				seNourir();
			}

			if (!animal->estVivant()) unsetProie();
		}
		
	}

	Lion* nouveauNe = seReproduire();
	if (nouveauNe != nullptr)
	{
		nouveauxOrganismes.push_back(nouveauNe);
	}

	seDeplacer(dt);
	vieillir(dt);
}

bool Lion::chercherNourriture(Vector3* posNourriture, vector<Organisme*> organismes)
{
	if (age < ageReproduction)return false;
	float meilleurRapport = 0;
	bool proieTrouve = false;
	for (auto& organisme : organismes) 
	{
		Animal* animal = dynamic_cast<Animal*>(organisme);
		if (animal != nullptr && animal != this) 
		{
			Lion* autreLion = dynamic_cast<Lion*>(animal);
			if (autreLion == nullptr) 
			{
				float distance = Vector3DistanceSqr(position, animal->getPosition());
				
				if(distance<porteVision && vitesse > animal->getVitesse())
				{
					float distance = Vector3DistanceSqr(position, animal->getPosition());

					float rapport = animal->getEnergieDonner() / (animal->getEnergie() * distance * animal->getVitesse());

					if(rapport> meilleurRapport)
					{
						*posNourriture = animal->getPosition();
						meilleurRapport = rapport;
						proieTrouve = true;

						if(distance < porteAttaque)
						{
							setProie(animal);
						}
					}
				}
			}
		}
	}

	return proieTrouve;
}

bool Lion::chercherPartenaire(Vector3* posPartenaire, vector<Organisme*> organismes)
{
	if (age < ageReproduction)return false;
	float distanceMin = std::numeric_limits<float>::max(); // Initialiser à une valeur très grande 
	bool partenaireTrouve = false;

	for (const auto& organisme : organismes)
	{
		Lion* autreLion = dynamic_cast<Lion*>(organisme);
		if (autreLion != nullptr && autreLion != this
			&& autreLion->getAge() > ageReproduction && autreLion->getEnergie() > energieReproduction)
		{
			float distance = Vector3DistanceSqr(position, autreLion->getPosition());

			if (distance < porteVision && distance < distanceMin) // Utilisez le carré de la distance maximale pour un partenaire
			{
				distanceMin = distance;
				*posPartenaire = autreLion->getPosition();
				partenaireTrouve = true;

				if (distanceMin < distanceMaxReproduction)
				{
					setPartenaire(autreLion);
				}
			}
		}
	}

	return partenaireTrouve;
}




Lion* Lion::seReproduire()
{
	if (partenaire == nullptr) return nullptr;
	if (partenaire->getPartenaire() != this) return nullptr;

	perdreEnergie(energieReproduction);
	partenaire->perdreEnergie(energieReproduction);

	Vector3 pos = Vector3Scale(Vector3Add(position, partenaire->getPosition()), 0.5);

	// Calcul de la direction moyenne
	Vector3 directionMoyenne = Vector3Scale(Vector3Add(direction, partenaire->getDirection()), 0.5);

	// Si la direction moyenne est un vecteur nul, utilisez la direction orthogonale
	if (Vector3Length(directionMoyenne) < 0.001f)
	{
		bool choisirPremiereDirection = (rand() % 2) == 0;

		if (choisirPremiereDirection)
		{
			directionMoyenne.x = -direction.z;
			directionMoyenne.z = direction.x;
		}
		else
		{
			directionMoyenne.x = direction.z;
			directionMoyenne.z = -direction.x;
		}
	}

	directionMoyenne.y = 0;  // Assurez-vous que la composante z est à zéro pour rester dans le plan 2D

	Lion* lion = new Lion(pos, directionMoyenne);
	//calculerStatistiquesEnfant(lion);
	partenaire->setDirection(directionMoyenne);
	setDirection(directionMoyenne);

	partenaire->unsetPartenaire();
	unsetPartenaire();

	return lion;
}

void Lion::seNourir()
{
	gagnerEnergie(proie->getEnergieDonner());
	puissance += 30;
}

void Lion::calculerStatistiquesEnfant(Lion* enfant)
{
	// Calculer les moyennes
	float moyennePuissanceMax = (puissanceMax + partenaire->getPuissanceMax()) / 2.0f;
	float moyennePertePuissanceAge = (pertePuissanceAge + partenaire->getPertePuissanceAge()) / 2.0f;
	float moyennePorteVision = (porteVision + partenaire->getPorteVision()) / 2.0f;
	float moyennePorteAttaque = (porteAttaque + partenaire->getPorteAttaque()) / 2.0f;
	float moyennePuissanceInitial = (puissanceInitial + partenaire->getPuissanceInitial()) / 2.0f;
	float moyenneEnergieDonner = (energieDonner + partenaire->getEnergieDonner()) / 2.0f;
	float moyenneVitesseInitial = (vitesseInitial + partenaire->getVitesseInitial()) / 2.0f;
	float moyenneAgeMax = (ageMax + partenaire->getAgeMax()) / 2.0f;
	float moyennePerteEnergieMaxAge = (perteEnergieMaxAge + partenaire->getPerteEnergieMaxAge()) / 2.0f;
	float moyennePerteVitesseAge = (perteVitesseAge + partenaire->getPerteVitesseAge()) / 2.0f;
	float moyenneAgeReproduction = (ageReproduction + partenaire->getAgeReproduction()) / 2.0f;
	float moyenneEnergieReproduction = (energieReproduction + partenaire->getEnergieReproduction()) / 2.0f;
	float moyenneEnergieMax = (energieMax + partenaire->getEnergieMax()) / 2.0f;
	float moyenneEnergieInitial = (energieInitial + partenaire->getEnergieInitial()) / 2.0f;

	// Appliquer une variation de ± 10%
	float variation = ((rand() % 21) - 10) / 100.0f; // Variation entre -0.10 et 0.10

	// Appliquer la variation à chaque statistique
	enfant->puissanceMax = moyennePuissanceMax * (1.0f + variation);
	enfant->pertePuissanceAge = moyennePertePuissanceAge * (1.0f + variation);
	enfant->porteVision = moyennePorteVision * (1.0f + variation);
	enfant->porteAttaque = moyennePorteAttaque * (1.0f + variation);
	enfant->puissanceInitial = moyennePuissanceInitial * (1.0f + variation);
	enfant->energieDonner = moyenneEnergieDonner * (1.0f + variation);
	enfant->vitesseInitial = moyenneVitesseInitial * (1.0f + variation);
	enfant->ageMax = moyenneAgeMax * (1.0f + variation);
	enfant->perteEnergieMaxAge = moyennePerteEnergieMaxAge * (1.0f + variation);
	enfant->perteVitesseAge = moyennePerteVitesseAge * (1.0f + variation);
	enfant->ageReproduction = moyenneAgeReproduction * (1.0f + variation);
	enfant->energieReproduction = moyenneEnergieReproduction * (1.0f + variation);
	enfant->energieMax = moyenneEnergieMax * (1.0f + variation);
	enfant->energieInitial = moyenneEnergieInitial * (1.0f + variation);
}
