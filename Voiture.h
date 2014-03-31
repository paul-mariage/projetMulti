#ifndef VOITURE_H_INCLUDED
#define VOITURE_H_INCLUDED

#include "objet3DStatique.h"
#include <string>

class Voiture : public Objet3DStatique
{
    private:
	      float16 PV;
	      float16 acceleration;
	      float16 decceleration;
	      float16 protection;
	      float16 maniabilite;


    public:
        Voiture::Voiture(float16 posX, float16 posY, float16 posZ, float16 angle, float16 PV, float16 movement, float16 protection, float16 maniabilite, std::string nomVoit,std::string nomFichier);

        // Avancer
        void Voiture::avancer(float16 distance)
		//Tourner
        void Voiture::tourner(float16 angleRot)
		//Position de la voiture sur la carte
        void getPosition(sint32* x, sint32* y);
};

#endif // VOITURE_H_INCLUDED