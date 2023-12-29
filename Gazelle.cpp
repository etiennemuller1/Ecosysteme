#include "Gazelle.h"

Gazelle::Gazelle(Vector3 position, Vector3 direction)
{
	this->position = position;
	this->direction = direction;

	this->energie = 250;
	this->energieMax = 1000;
	this->age = 0;
	this->ageMax = 25;
	this->perteEnergieMaxAge = 25;
	this->perteVitesseAge = 1.0f / 10;
	this->ageReproduction = 5;
	this->energieReproduction = 260;
	this->distanceMaxReproduction = pow(1, 2);
	this->energieDonner = 350;
	this->vitesse = 70.0f / 10;
	this->puissance = 0;
	this->puissanceMax = 0;
	this->pertePuissanceAge = 0;
	this->porteVision = pow(30, 2);
	this->porteAttaque = pow(1, 2);
}

void Gazelle::afficher()
{
	if(age<ageReproduction)
	{
		DrawCapsule(position, Vector3Add(position, Vector3Multiply(direction, { 0.25,0,0.25 })), 0.15, 5, 5, BROWN);
	}
	else
	{
		DrawCapsule(position, Vector3Add(position, Vector3Multiply(direction, { 0.5,0,0.5 })), 0.3, 10, 10, BROWN);
	}
}
void Gazelle::mettreAJour(float dt, vector<Organisme*> organismes, vector<Organisme*>& nouveauxOrganismes)
{
	chercher(organismes);

	if (proie != nullptr)
	{
		Plante* plante = dynamic_cast<Plante*>(proie);
		if (plante != nullptr)
		{
			if(plante->estManger())
			{
				seNourir();
				if (!plante->estComestible()) unsetProie();
			}
		}
	}

	Gazelle* nouveauNe = seReproduire();
	if (nouveauNe != nullptr)
	{
		nouveauxOrganismes.push_back(nouveauNe);
	}
	seDeplacer(dt);
	vieillir(dt);
}

bool Gazelle::chercherNourriture(Vector3* posNourriture, vector<Organisme*> organismes)
{
	if (age < ageReproduction)return false;
	float meilleurRapport = 0;
	bool planteTrouvee = false;

	for (auto& organisme : organismes)
	{
		Plante* plante = dynamic_cast<Plante*>(organisme);

		// Vérifier si l'organisme est une plante et s'il est comestible
		if (plante != nullptr && plante->estComestible())
		{
			float distance = Vector3DistanceSqr(position, plante->getPosition());

			// Calculer le rapport énergie donnée/distance
			float rapport = plante->getEnergieDonner() / distance;

			// Si le rapport est meilleur, mettre à jour la plante choisie
			if (rapport > meilleurRapport)
			{
				*posNourriture = plante->getPosition();
				meilleurRapport = rapport;
				planteTrouvee = true;

				if (distance < porteAttaque)
				{
					setProie(plante);
				}
			}
		}
	}

	return planteTrouvee;
}

bool Gazelle::chercherPartenaire(Vector3* posPartenaire, vector<Organisme*> organismes)
{
	if (age < ageReproduction)return false;
	float distanceMin = std::numeric_limits<float>::max(); // Initialiser à une valeur très grande 
	bool partenaireTrouve = false;

	for (const auto& organisme : organismes)
	{
		Gazelle* autreGazelle = dynamic_cast<Gazelle*>(organisme);
		if (autreGazelle != nullptr && autreGazelle != this
			&& autreGazelle->getAge() > ageReproduction && autreGazelle->getEnergie() > energieReproduction)
		{
			float distance = Vector3DistanceSqr(position, autreGazelle->getPosition());

			if (distance < porteVision && distance < distanceMin) // Utilisez le carré de la distance maximale pour un partenaire
			{
				distanceMin = distance;
				*posPartenaire = autreGazelle->getPosition();
				partenaireTrouve = true;

				if (distanceMin < distanceMaxReproduction)
				{
					setPartenaire(autreGazelle);
				}
			}
		}
	}

	return partenaireTrouve;
}

void Gazelle::seNourir()
{
	gagnerEnergie(proie->getEnergieDonner());
	energieDonner += proie->getEnergieDonner() / 10;
}

Gazelle* Gazelle::seReproduire()
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

	Gazelle* gazelle = new Gazelle(pos, directionMoyenne);
	//calculerStatistiquesEnfant(gazelle);
	partenaire->setDirection(directionMoyenne);
	setDirection(directionMoyenne);

	partenaire->unsetPartenaire();
	unsetPartenaire();

	return gazelle;
}


void Gazelle::calculerStatistiquesEnfant(Gazelle* enfant)
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
