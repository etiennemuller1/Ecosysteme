#include "Animal.h"
void Animal::allerVers(Vector3 position)
{
    direction = Vector3Normalize(Vector3Subtract(position, this->position));
}

void Animal::seDeplacer(float dt)
{
    position = Vector3Add(position, Vector3Scale(direction, dt * vitesse));
}

bool Animal::attaquer(Animal* proie,float dt)
{
    if (!proie->estVivant()) return false;
    proie->perdreEnergie(puissance*dt);
    return !proie->estVivant();
}

float Animal::getPuissance()
{
    return puissance;
}

float Animal::getVitesse()
{
    return vitesse;
}

float Animal::getPuissanceMax()
{
    return puissanceMax;
}

float Animal::getPorteVision()
{
    return porteVision;
}

Vector3 Animal::getDirection()
{
    return direction;
}

void Animal::setDirection(Vector3 direction)
{
    this->direction = direction;
}

void Animal::setPartenaire(Animal* partenaire)
{
    this->partenaire = partenaire;
}

Animal* Animal::getPartenaire()
{
    return partenaire;
}

void Animal::setProie(Organisme* proie)
{
    this->proie = proie;
}

Organisme* Animal::getProie()
{
    return proie;
}

void Animal::unsetProie()
{
    proie = nullptr;
}

void Animal::unsetPartenaire()
{
    partenaire = nullptr;
}

float Animal::getPertePuissanceAge()
{
    return pertePuissanceAge;
}

float Animal::getPorteAttaque()
{
    return porteAttaque;
}

float Animal::getPuissanceInitial()
{
    return puissanceInitial;
}

float Animal::getVitesseInitial()
{
    return vitesseInitial;
}

float Animal::getPerteVitesseAge()
{
    return perteVitesseAge;
}

void Animal::chercher(vector<Organisme*> organismes)
{
    Vector3 newPos;

    if(age>=ageReproduction && energie >= energieReproduction && chercherPartenaire(&newPos, organismes))
    {
       
        Vector3 newDirection = Vector3Subtract(newPos, position);
        newDirection = Vector3Normalize(newDirection);
        direction = newDirection;        
    }
    else if (chercherNourriture(&newPos, organismes))
    {
        Vector3 newDirection = Vector3Subtract(newPos, position);
        newDirection = Vector3Normalize(newDirection);
        direction = newDirection;
    }
}

void Animal::mourir()
{
    vivant = false;
}

void Animal::vieillir(float dt)
{
    age += dt;
    if (age > ageMax) mourir();

    energieMax -= perteEnergieMaxAge*dt;
    vitesse -= perteVitesseAge*dt;
    puissance -= pertePuissanceAge*dt;

    if (energie > energieMax) energie = energieMax;
    if (energie < 0) mourir();
    if (vitesse < 0) vitesse = 0;
    if (puissance < 0) puissance = 0;
}