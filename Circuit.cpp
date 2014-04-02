#include "Circuit.h"
#include <SDL/SDL.h>

//Classe de création du circuit à partir d'une image bmp
Circuit::Circuit(const char* nomFichier)
{
    // Initialisation des attributs
    this->Circuit = NULL;
    this->largeurCircuit = 0u;
    this->hauteurCircuit = 0u;
    this->listeAffichage = 0u;

    // Tentative de chargement
    SDL_Surface* imageCircuit = SDL_LoadBMP(nomFichier);

    // Si l'image est chargee et elle en 24 bits/px
    if ( (NULL != imageCircuit) && (24 == imageCircuit->format->BitsPerPixel) )
    {
        // Définition des dimensions du circuit
        this->largeurCircuit = imageCircuit->w;
        this->hauteurCircuit = imageCircuit->h;

        // Calcule le nombre de cases sur le circuit
        uint32 nombreCases = (this->largeurCircuit) * (this->hauteurCircuit);

        // Initialisation du circuit sous forme de matrice 
        this->Circuit = new uint8[nbCases];

        // Pour chaque ligne du circuit
		//On va redéfinir le pixel avec une composante rouge bleu et vert
		//Parcourir les pixels de la ligne
		//Si le pixel est noir sur le bmp, on va placer un mur sur la matrice 
        for(uint32 ligne = 0; ligne < this->hauteurCircuit; ligne++)
        {
            bgr* pixelsCircuit = (bgr*) ((uint8*)imageCircuit->pixels + ligne * imageCircuit->pitch);
			
            for(uint32 pixel = 0; pixel < this->largeurCircuit; pixel++)
            {
                if( (pixelsCircuit[pixel].rouge + pixelsCircuit[pixel].vert + pixelsCircuit[pixel].bleu) > 500 )
                {
					//Piste
                    this->Circuit[(this->largeurCircuit * ligne) + pixel] = 0;
                }
                else if( (pixelsCircuit[pixel].rouge + pixelsCircuit[pixel].vert + pixelsCircuit[pixel].bleu) > 250 )
                {
					//Mur
                    this->Circuit[(this->largeurCircuit * ligne) + pixel] = 1;
                }
                {
					//Herbe
                    this->Circuit[(this->largeurCircuit * ligne) + pixel] = 2;
                }
            }
        }

        // Creation de la liste d'affichage de la Circuit
        this->creerListeAffichage();


        SDL_FreeSurface(imageCircuit);
    }

    // Erreur de chargement
    else
    {
        printf("Erreur de chargement de la Circuit\n");
    }
}

Circuit::~Circuit()
{
    delete[] this->Circuit;
    this->MesTextures.supprimer("piste.bmp");
	this->MesTextures.supprimer("mur.bmp");
    this->MesTextures.supprimer("herbe.bmp");
}

void Circuit::dessiner()
{
    glCallList(this->listeAffichage);
}

void Circuit::creerListeAffichage()
{
    // Chargement de la texture du mur
	this->MesTextures.ajouter("piste.bmp");
	this->MesTextures.ajouter("mur.bmp");
    this->MesTextures.ajouter("herbe.bmp");

    // Creation de la liste d'affichage
    this->listeAffichage = glGenLists(1);
    glNewList(this->listeAffichage, GL_COMPILE);

    // On active les textures 2D
    glEnable(GL_TEXTURE_2D);

    // Dessin du mur
    glBindTexture(GL_TEXTURE_2D, this->MesTexturesTextures.texture("mur.bmp").texture);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex3i(0, 0, 0);
    glTexCoord2i(0, 1); glVertex3i(8, 0, 0);
    glTexCoord2i(1, 1); glVertex3i(8, 8, 0);
    glTexCoord2i(1, 0); glVertex3i(0, 8, 0);
	glEnd();


    // L'herbe
    glBindTexture(GL_TEXTURE_2D, this->MesTextures.texture("herbe.bmp").texture);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex3i(0, 0, 0);
    glTexCoord2i(0, 1); glVertex3i(8, 0, 0);
    glTexCoord2i(1, 1); glVertex3i(8, 8, 0);
    glTexCoord2i(1, 0); glVertex3i(0, 8, 0);
    glEnd();
	
	 // La piste
    glBindTexture(GL_TEXTURE_2D, this->MesTextures.texture("piste.bmp").texture);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex3i(0, 0, 0);
    glTexCoord2i(0, 1); glVertex3i(8, 0, 0);
    glTexCoord2i(1, 1); glVertex3i(8, 8, 0);
    glTexCoord2i(1, 0); glVertex3i(0, 8, 0);
    glEnd();

    // Fin de la liste d'affichage
    glEndList();
}

void Circuit::entourage(sint32 x, sint32 y, bool8 entourage[8])
{
	//Utilisation d'un tableau de booleen qui va permettre de savoir si il y a des murs sur les cases alentours :
	// |	entourage[0]		entourage[1]			entourage[2] |
	// | 	entourage[3] 		voiture					entourage[4] |
	// |	entourage[5]		entourage[6]			entourage[7] |
    sint32 largeurCircuit = this->largeurCircuit;

    // Initialisation 
    entourage[0] = 0;
    entourage[1] = 0;
    entourage[2] = 0;
    entourage[3] = 0;
    entourage[4] = 0;
    entourage[5] = 0;
    entourage[6] = 0;
    entourage[7] = 0;

    // Construction de la vue de l'entourage dans le milieu de la Circuit
    if (y > 0 && y < (sint32)hauteurCircuit - 1 && x > 0 && x < largeurCircuit - 1)
    {
        entourage[0] = this->Circuit[ (x-1) + ((y-1) * largeurCircuit) ];
        entourage[1] = this->Circuit[ (x)   + ((y-1) * largeurCircuit) ];
        entourage[2] = this->Circuit[ (x+1) + ((y-1) * largeurCircuit) ];
        entourage[3] = this->Circuit[ (x-1) + (  (y) * largeurCircuit) ];
        entourage[4] = this->Circuit[ (x+1) + (  (y) * largeurCircuit) ];
        entourage[5] = this->Circuit[ (x-1) + ((y+1) * largeurCircuit) ];
        entourage[6] = this->Circuit[ (x)   + ((y+1) * largeurCircuit) ];
        entourage[7] = this->Circuit[ (x+1) + ((y+1) * largeurCircuit) ];
    }

    // ATTENTION : Pour une gestion correcte des collisions,
    // la Circuit doit etre entouree de murs.
}
