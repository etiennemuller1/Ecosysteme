#include "Environnement.h"

Environnement::Environnement(Vector3 centreArene, float rayonArene)
{
	this->centreArene = centreArene;
	this->rayonArene = rayonArene;
}

void Environnement::ajouterOrganisme(Organisme* organisme)
{
	organismes.push_back(organisme);
}

void Environnement::mettreAJour(float dt)
{
	vector<Organisme*> nouveauxOrganismes;

	for(auto& organisme: organismes)
	{
		organisme->mettreAJour(dt, organismes, nouveauxOrganismes);
	}

	for (auto& nouveauOrganisme : nouveauxOrganismes)
	{
		ajouterOrganisme(nouveauOrganisme);
	}

	
	organismes.erase(
		remove_if(organismes.begin(), organismes.end(),
			[](Organisme* organisme) { return !organisme->estVivant(); }),
		organismes.end()
	);
}

void Environnement::afficher()
{
	for (auto& organisme : organismes)
	{
		organisme->afficher();
	}
	DrawCylinder(centreArene, rayonArene, rayonArene+10, 0.1, 200, DARKGREEN);
}

void Environnement::afficher2D()
{
	int nombreGazelles = 0;
	int nombreLions = 0;
	int nombreBananiers = 0;

	for (const auto& organisme : organismes)
	{
		if (dynamic_cast<Gazelle*>(organisme) != nullptr)
		{
			nombreGazelles++;
		}
		else if (dynamic_cast<Lion*>(organisme) != nullptr)
		{
			nombreLions++;
		}
		else if (dynamic_cast<Bananier*>(organisme) != nullptr)
		{
			nombreBananiers++;
		}
	}



	DrawRectangle(10, 10, 360, 230, Fade(SKYBLUE, 0.5f));
	DrawRectangleLines(10, 10, 360, 230, BLUE);

	DrawText("Free camera default controls:", 20, 20, 20, BLACK);
	DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 20, DARKGRAY);
	DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 20, DARKGRAY);
	DrawText("- W to zoom to (0, 0, 0)", 40, 80, 20, DARKGRAY);
	DrawText(TextFormat("Nombre de Gazelles : %d", nombreGazelles), 40, 100, 20, DARKGRAY);

	DrawText(TextFormat("Nombre de Lions : %d", nombreLions), 40, 120, 20, DARKGRAY);

	DrawText(TextFormat("Nombre de Bananiers : %d", nombreBananiers), 40, 140, 20, DARKGRAY);
}

void Environnement::ajouterOrganismesAleatoires(int nombreLions, int nombreGazelles, int nombreBananiers)
{
	for (int i = 0; i < nombreLions; ++i)
	{
		Vector3 position = obtenirPositionAleatoire();
		Vector3 direction = obtenirDirectionAleatoire();
		Lion* lion = new Lion(position, direction);
		ajouterOrganisme(lion);
	}

	for (int i = 0; i < nombreGazelles; ++i)
	{
		Vector3 position = obtenirPositionAleatoire();
		Vector3 direction = obtenirDirectionAleatoire();
		Gazelle* gazelle = new Gazelle(position, direction);
		ajouterOrganisme(gazelle);
	}

	for (int i = 0; i < nombreBananiers; ++i)
	{
		Vector3 position = obtenirPositionAleatoire();
		Bananier* bananier = new Bananier(position);
		bananier->setNbFruits(rand() % (3+ 1));
		bananier->setAge(static_cast<float>(rand() % 101));
		bananier->setEnergie(static_cast<float>(rand()) / RAND_MAX * bananier->getEnergieReproduction());
		bananier->setTempsDepuisDernierFruit(static_cast<float>(rand()) / RAND_MAX * bananier->getTempsEntreFruit());
		ajouterOrganisme(bananier);
	}
}

Vector3 Environnement::obtenirPositionAleatoire()
{
	float angle = static_cast<float>(rand() % 360);
	float distance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * rayonArene;

	float angleRadians = DEG2RAD * angle;

	Vector3 position;
	position.x = centreArene.x + distance * cos(angleRadians);
	position.y = centreArene.y+1;
	position.z = centreArene.z + distance * sin(angleRadians);

	return position;
}

Vector3 Environnement::obtenirDirectionAleatoire()
{
	Vector3 direction;
	direction.x = static_cast<float>(rand() % 2 - 1); 
	direction.y = 0.0f; 
	direction.z = static_cast<float>(rand() % 2 - 1);
	direction = Vector3Normalize(direction);
	return direction;
}
