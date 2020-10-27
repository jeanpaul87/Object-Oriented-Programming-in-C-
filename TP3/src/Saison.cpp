/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   saison.cpp
   Date : 1 mars 2020 */

// To do
#include "Saison.h"

// To do
// Constructeur par defaut
Saison::Saison()
    : numSaison_(0)
    , nbEpisodesmax_(0) // maybe not 0. maybe vector
                        // To do
{
}

// To do
// Constructeur par paramètres
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax)
    : numSaison_(numSaison)
    , nbEpisodesmax_(nbEpisodemax)
// To do
{
}

// To do
//!   Constructeur par copie
Saison::Saison(const Saison& saison)
{
    // To do
    nbEpisodesmax_ = saison.nbEpisodesmax_;
    numSaison_ = saison.numSaison_;
    for (int i = 0; i < saison.getNbEpisodes(); i++)
    {
        Episode episode = *saison.episodes_[i];
        episodes_.push_back(std::make_unique<Episode>(episode));
    }
}

// To do
//!  Destructeur de saison
Saison::~Saison()
{
    // To do
    episodes_.clear();
}

// To do
//!  Opérateur += qui prend une saison à gauche et un episode à droite
//! \param episode                       L'épisode
//! \return                              L'objet courant
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
    // To do
    int indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
    if (indexEpisode != -1)
        *this -= episode->getNumEpisode();
    episodes_.push_back(std::make_unique<Episode>(*episode));
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode()); 
    return *this;
}

// To do
//!  Opérateur -= qui prend une saison à gauche et un numéro d'épisode à droite
//! \param numEpisode                    Le numéro de l'épisode
//! \return                              L'objet courant
Saison& Saison::operator-=(unsigned int numEpisode)
{
    // To do
    if (trouverIndexEpisode(numEpisode) != -1)
    {
        episodes_.erase(episodes_.begin() + trouverIndexEpisode(numEpisode));
    }
    return *this;
}

// To do
//!  Opérateur == qui prend une saison à gauche et un numéro de saison à droite
//! \param numEpisode                    Le numéro de l'épisode
//! \return                              L'objet courant
bool Saison::operator==(unsigned int numSaison)
{
    // To do
    if (numSaison == this->numSaison_)
    {
        return true;
    }
    return false;
}

// To do
//!  Opérateur << qui prend un os à gauche et une saison è droite
//! \param os                            le stream os
//! \param saison                        la saison
//! \return                              Le stream
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
    // To do
    std::string statut;
    if (saison.nbEpisodesmax_ > saison.episodes_.size())
    {
        statut = "(En cours)";
    }
    else
    {
        statut = "(Terminee)";
    }
    os << "\tSaison " << std::setw(2) << std::setfill('0') << 
		saison.numSaison_ << ": "
       << saison.episodes_.size() << "/"
       << saison.nbEpisodesmax_ << statut << std::endl;
    for (int i = 0; i < saison.episodes_.size(); i++)
    {
        os << *(saison.episodes_[i]) << std::endl;
    }
    return os;
}
// To do
//!  Opérateur >> qui prend un is à gauche et une saison è droite
//! \param os                            le stream is
//! \param saison                        la saison
//! \return                              Le stream
std::istream& operator>>(std::istream& is, Saison& saison)
{
    // To do
    is >> saison.numSaison_ >> saison.nbEpisodesmax_;
    return is;
}

// To do
//!  Méthode getter qui retourne le numéro de la saison
//! \return                              Le numéro de saison
unsigned int Saison::getNumSaison() const
{
    // To do
    return numSaison_;
}

// To do
//!  Méthode getter qui retourne le nombre d'épisode de la saison
//! \return                              Le nombre d'épisodes
size_t Saison::getNbEpisodes() const
{
    // To do
    return episodes_.size();
}

// To do
//!  Méthode qui retourne l'index d'un episode à partir de son numéro
//! \param numEpisode                    Le numéro de l'épisode
//! \return                              L'index
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
    // To do
    for (int i = 0; i < episodes_.size(); i++)
    {
        if (episodes_[i]->getNumEpisode() == numEpisode)
        {
            return i;
        }
    }
    return EPISODE_INEXSISTANTE;
}