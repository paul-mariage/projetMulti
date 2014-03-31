#include "Voiture.h"
#include <math.h>

Voiture::Voiture(float16 posX,
		  float16 posY,
	      float16 posZ, 
	      float16 angle,
	      float16 PV, 
	      float16 movement,
	      float16 protection,
	      float16 maniabilite,
	      std::string nomVoit,
	      std::string nomFichier) : Objet3DStatique(nomFichier)
{
  
  this->posX = posX;
  this->posY = posY;
  this->posZ = posZ;
  this->angle = angle;
  this->PV=PV; 
  this->movement=movement;
  this->protection=protection;
  this->maniabilite=maniabilite;
  this->nomVoit=nomVoit;
  
}

//Avancer en d'une certaine distance en fonction du mouvement
void Voiture::avancer(float16 distance)
{
  this->posX-= distance * movement * cos(this->angle * M_PI/180.0);
  this->posY-= distance * movement * sin(this->angle * M_PI/180.0);
}

void Voiture::tourner(float16 angleRot)
{
 
  this->angle += angleRot;
  
  if(this->angle >= 180.0) // Limite du demi tour vers la droite
  {
    this->angle-=360.0;
  }
    if(this->angle <= -180.0) // Limite du demi tour vers la droite
  {
    this->angle+=360.0;
  }
  
  void Voiture::getPosition(sint32* posx, sint32* posy)
{
    // Recupere la position de la voiture sur le circuit
    *posx = (sint32)this->posX;
    *posy = (sint32)this->posY;
}
}
