#ifndef OBJET3DSTATIQUE_H_INCLUDED
#define OBJET3DSTATIQUE_H_INCLUDED

#include <string>
#include <set>
#include "mytypes.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "MesTextures.h"

class Objet3DStatique
{
    private:
        typedef std::set<std::string> Textures;

        Textures textures; // Les textures de l'objet
        MesTextures mesTextures;
        GLuint listeAffichage;
        GLuint listeRST;

    protected:
        // Position de l'objet
        float16 posX; //en x
        float16 posY; //en y
        float16 posZ; //en z

        // Angle horizontal avec la verticale en z
        float16 angle;

        std::string nom;

    public:
        Objet3DStatique(std::string nomFichier);
        ~Objet3DStatique();
        void dessiner();
};

#endif // OBJET3DSTATIQUE_H_INCLUDED
