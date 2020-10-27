/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   utilisateur.cpp
   Date : 1 mars 2020 */

#include "Utilisateur.h"

//! Constructeur de la classe Utilisateur
//! \param nom          Le nom de l'utilisateur
//! \param age          L'âge de l'utilisateur
//! \param estPremium   Bool representant si l'utilisateur est premium
//! \param pays         Pays de l'utilisateur
Utilisateur::Utilisateur(const std::string& nom, unsigned int age, bool estPremium, Pays pays)
    : nom_(nom)
    , age_(age)
    , nbMediasVus_(0)
    , estPremium_(estPremium)
    , pays_(pays)
{
}

//! Methode qui retourne si le film est disponible pour un utilisateur
//! \param film Le film à evaluer
//! \return Un bool representant si un film est disponible à l'utilisateur
bool Utilisateur::mediaEstDisponible(const Media& media) const
{
    static constexpr unsigned int AGE_MINIMUM_POUR_FILMS_RESTREINTS = 16;

    bool ageApproprie = true;
    if (age_ < AGE_MINIMUM_POUR_FILMS_RESTREINTS)
    {
        ageApproprie = media.estRestreintParAge() == false;
    }
    return (ageApproprie == true && media.estRestreintDansPays(pays_) == false);
}

//! Methode qui retourne si un utilisateur a atteint le nombre limite de films qu'il peut regarder
//! \return Un bool representant si un utilisateur a atteint le nombre limite de films qu'il peut
//! regarder
bool Utilisateur::nbLimiteMediasAtteint() const
{
    return estPremium_ == false && nbMediasVus_ >= NB_FILMS_GRATUITS;
}

//! Methode qui incremente le nombre de films vus par l'utilisateur
//! \return Un bool representant si l'utilisateur a pu regarder le film
bool Utilisateur::regarderMedia(const Media& media)
{
    if (nbLimiteMediasAtteint() == false && mediaEstDisponible(media))
    {
        nbMediasVus_++;
        return true;
    }
    return false;
}

//! Methode qui retourne le nombre de films vus par l'utilisateur
//! \return Le nombre de films vus par l'utilisateur
unsigned int Utilisateur::getNbMediasVus() const
{
    return nbMediasVus_;
}
