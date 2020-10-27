/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   PivoterMatrice.h
   Date : 26 Mars 2020 
*/
#ifndef PIVOTER_MATRICE_H
#define PIVOTER_MATRICE_H

#include "def.h"

template <class M> class PivoterMatrice {
public:
  // Constructeurs
  PivoterMatrice();
  PivoterMatrice(M *matrice);
  // Destructeur
  ~PivoterMatrice() = default;
  void pivoterMatrice(Direction direction);

private:
  Coordonnees changerCoordonneesCentreMatrice(Coordonnees coords) const;
  Coordonnees recupererCoordonnees(Coordonnees coords) const;
  M *matrice_;
};

/**
 * @brief constructeur par défaut de la classe
 */
template <class M> inline PivoterMatrice<M>::PivoterMatrice() : matrice_(nullptr) {
  // TO DO
}

/**
 * @brief constructeur par paramètre de la classe
 */
template <class M>
inline PivoterMatrice<M>::PivoterMatrice(M *matrice) : matrice_(matrice) {
    //TODO
}


/**
 * @brief trouver les coordonnées du point par rapport au centre de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::changerCoordonneesCentreMatrice(Coordonnees coords) const {
  // TO DO
    int width = matrice_->getWidth();
    int milieu = (int)(width / 2.0);
    Coordonnees nouvellesCoordonnees{ coords.x - milieu, coords.y - milieu };
    return nouvellesCoordonnees;
}
/**
 * @brief revenir au système précédent, trouver les coordonnées du point par
 * rapport au premier élément de la matrice
 * @param coords les coordonnées du point originales
 */
template <class M>
inline Coordonnees
PivoterMatrice<M>::recupererCoordonnees(Coordonnees coords) const {
  // TO DO
    int width = matrice_->getWidth();
    int milieu = (int)(width / 2.0);
    Coordonnees anciennesCoordonnees{ coords.x + milieu, coords.y + milieu };
    return anciennesCoordonnees;
}

//Todo
//! Méthode qui pivote une matrice
//! \param direction La direction qu'on veut pivoter  ( droite ou gauche )
template<class M>
inline void PivoterMatrice<M>::pivoterMatrice(Direction direction)
{
    std::unique_ptr<M> copieMatrice = matrice_->clone();
    for(int y=0; y<matrice_->getHeight(); y++){
        for(int x=0; x<matrice_->getWidth(); x++){
            Coordonnees coordonnees{ x, y };
            Coordonnees nouvellesCoordonnees = changerCoordonneesCentreMatrice(coordonnees);

            //si on choise la direction 0 donc on va faire une rotation centree en 0.0 et vers la droite
            if (direction == Direction::Right) {
                //      [x, y] --> [y, -x]
                int copieX = nouvellesCoordonnees.x;
                nouvellesCoordonnees.x = nouvellesCoordonnees.y;
                nouvellesCoordonnees.y = -copieX;
            }
            //si on choise la direction 1 donc on va faire une rotation centree en 0.0 et vers la gauche
            else if (direction == Direction::Left) {
                //      [x, y] --> [-y, x]
                int copieX = nouvellesCoordonnees.x;
                nouvellesCoordonnees.x = -nouvellesCoordonnees.y;
                nouvellesCoordonnees.y = copieX;
            }


            nouvellesCoordonnees = recupererCoordonnees(nouvellesCoordonnees);
            matrice_->ajouterElement((*copieMatrice)(nouvellesCoordonnees.y, nouvellesCoordonnees.x), y, x);
            
		      }
	    }
    

          
}

#endif
