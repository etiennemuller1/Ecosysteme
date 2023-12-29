#include "Bananier.h"

Bananier::Bananier(Vector3 position)
{
	this->position = position;
	age = 0;
	comestible = false;
	energie = 1;
	energieDonner = 0;
	ageReproduction = 10;
	energieReproduction = 45;
	distanceMaxReproduction = 20;
	distanceMinReproduction = 5;
	tempsDepuisDernierFruit = 0.0f;
	tempsEntreFruits = 7.0f;
	ageMax = 100;
	nombreFruitsMax = 12;
	energieFruit = 400;
}

void Bananier::afficher()
{
		if(age<ageReproduction)
		{
			Vector3 p = { position.x, position.y -1, position.z };

			DrawCylinder(p, 0.5, 0.5, 3, 5, DARKBROWN);
			Vector3 p1 = { p.x, p.y + 0.5 + 3, p.z };
			DrawSphere(p1, 1, GREEN);
		}
		else
		{
			Vector3 p = { position.x, position.y - 1, position.z };
			DrawCylinder(p, 1, 1, 8, 10, DARKBROWN);
			Vector3 p1 = { p.x, p.y + 1.5 + 8, p.z };
			DrawSphere(p1, 3, GREEN);
			for (int i = 0; i < nombreFruits; ++i)
			{
				float theta = static_cast<float>(i) * (360.0f / nombreFruits); // Angle en degrés
				float phi = 45.0f; // Angle en élévation (en degrés)
				float radius = 3.0f; // Rayon de la sphère de fruits

				// Convertir les coordonnées sphériques en coordonnées cartésiennes
				float x = p.x + radius * sin(DEG2RAD * phi) * cos(DEG2RAD * theta);
				float y = p.y + 9.5  - radius * cos(DEG2RAD * phi);
				float z = p.z + radius * sin(DEG2RAD * phi) * sin(DEG2RAD * theta);

				Vector3 fruitPosition = { x, y, z };
				DrawSphere(fruitPosition, 0.5f, YELLOW);
			}
		}
		

		
}

void Bananier::mettreAJour(float dt, vector<Organisme*> organismes, vector<Organisme*>& nouveauxOrganismes)
{

	Organisme* nouveauNe = seReproduire();
	if (nouveauNe != nullptr)
	{
		nouveauxOrganismes.push_back(nouveauNe);
	}

	vieillir(dt);

	if (age >= ageReproduction)
	{
		tempsDepuisDernierFruit += dt;
		// Si le temps écoulé dépasse le temps nécessaire pour produire un fruit, créez un fruit
		if (tempsDepuisDernierFruit >= tempsEntreFruits)
		{
			tempsDepuisDernierFruit = 0.0f; // Réinitialisez le compteur
			produireFruit();
		}
	}

	energieDonner = energieFruit * nombreFruits;
}

void Bananier::seNourir()
{
	
}

Bananier* Bananier::seReproduire()
{
	if (energie <= energieReproduction) return nullptr;
	
	energie -= energieReproduction;

	float angleReproduction = static_cast<float>(rand() % 360); // Angle aléatoire en degrés
	float angleRadians = DEG2RAD * angleReproduction;
	float distanceReproduction = distanceMinReproduction + static_cast<float>(rand()) / RAND_MAX * (distanceMaxReproduction - distanceMinReproduction);

	Vector3 newPosition;
	newPosition.x = position.x + distanceReproduction * cos(angleRadians);
	newPosition.y = position.y;
	newPosition.z = position.z + distanceReproduction * sin(angleRadians);

	Bananier* nouveauBananier = new Bananier(newPosition);

	return nouveauBananier;
}

bool Bananier::estManger()
{
	if (nombreFruits <= 0) return false;
	nombreFruits --;
	energie+=6;
	if (nombreFruits == 0) setComestible(false);
	return true;
}

void Bananier::produireFruit()
{
	if (nombreFruits == nombreFruitsMax) return;
	nombreFruits++;
	setComestible(true);
}

void Bananier::setAge(float age)
{
	this->age = age;
}

void Bananier::setTempsDepuisDernierFruit(float tps)
{
	tempsDepuisDernierFruit = tps;
}

float Bananier::getTempsEntreFruit()
{
	return tempsEntreFruits;
}

void Bananier::setEnergie(float energie)
{
	this->energie = energie;
}

void Bananier::setNbFruits(int nb)
{
	if (nb > nombreFruitsMax)nb = nombreFruitsMax;
	nombreFruits = nb;
}

int Bananier::getNombreFruitsMax()
{
	return nombreFruitsMax;
}
