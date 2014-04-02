#ifndef CIRCUIT_H_INCLUDED
#define CIRCUIT_H_INCLUDED

#include <set>
#include "mytypes.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include "MesTextures.h"

class Circuit
{
    private:
        MesTextures myTextures;

        uint8* carte;
        uint32 largeurCircuit;
        uint32 hauteurCircuit;
        GLuint listeAffichage;

        void creerListeAffichage();

    public:
        Circuit(const char* nomFichier);
        ~Circuit();
        void dessiner();

        void entourage(sint32 x, sint32 y, bool8 entourage[8]);
};

#endif // CIRCUIT_H_INCLUDED
