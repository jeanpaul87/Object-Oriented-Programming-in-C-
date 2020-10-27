/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   episode.cpp
   Date : 1 mars 2020 */

// To do
#include "Episode.h"

// To do
//Constructeur par defaut
Episode::Episode():nom_(""), duree_(""), numEpisode_(0)
// To do
{
}

// To do
//Constructeur par paramètres
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree):
    nom_(nom), duree_(duree), numEpisode_(numEpisode)
// To do
{
}

// To do
//!  Surcharge de l'opérateur == avec Episode a gauche et numEpisode a droite
//! \param numEpisode              Numéro de l'épisode
//! \return     Un bool représentant l'égalité
bool Episode::operator==(unsigned int numEpisode)
{
    // To do
    if(numEpisode_ == numEpisode){
        return true;
    }
    return false;
}


// To do
//!  Surcharge de l'opérateur << avec un os à gauche et un episode à droite
//! \param numEpisode              Le numéro de l'épisode
//! \param os              Le stream dans lequel afficher
//! \return     Le os
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
    // To do
    os << "\t\tEpisode " << std::setw(2) << std::setfill('0') << episode.numEpisode_ << ": " << episode.nom_
       << " | Duree: " << episode.duree_;
    //revoir l'affichage
    return os;
}

// To do
//!  Surcharge de l'opérateur >> avec un is à gauche et un episode à droite
//! \param episode              L'épisode à remplir
//! \param is              Le stream duquel prendre l'épisode
//! \return     Le is
std::istream& operator>>(std::istream& is, Episode& episode)
{
    // To do
    is >> episode.numEpisode_ >> std::quoted(episode.nom_) >> std::quoted(episode.duree_);
    return is;
}

// To do
//!  Méthode d'accès au numéro d'épisode
//! \return     Le numéro de l'épisode
unsigned int Episode::getNumEpisode() const
{
    // To do
    return numEpisode_;
}
