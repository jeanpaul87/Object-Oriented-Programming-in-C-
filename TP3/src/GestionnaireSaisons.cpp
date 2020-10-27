/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   GestionnaireSaisons.cpp
   Date : 1 mars 2020 */

// To do
#include "GestionnaireSaisons.h"

// To do
//!  Destructeur de la classe GestionnaireSaisons
GestionnaireSaisons::~GestionnaireSaisons()
{ // To do
    saisons_.clear();
}

// To do
//!  Opérateur += de la classe GestionnaireSaisons pour ajouter une saison
//! \param saison                     La saison à ajouter au vecteur de saisons
//! \return                           L'objet Gestionnaire saison  
GestionnaireSaisons& GestionnaireSaisons::operator+=(std::unique_ptr<Saison> saison)
{
    // To do
    int indexSaison = trouverIndexSaison(saison->getNumSaison());
    if (indexSaison != SAISON_INEXSISTANTE) 
    {
        *this -= saison->getNumSaison();
    }
    saisons_.push_back(std::move(saison));
    sort(saisons_.begin(), saisons_.end(), Saison::SortByNumSaison());
    return *this;
}

// To do
//!  Opérateur -= de la classe GestionnaireSaisons pour enlever une saison
//! \param numSaison                  Le numéro de la saison à enlever   
//! \return                           L'objet Gestionnaire saison  
GestionnaireSaisons& GestionnaireSaisons::operator-=(const unsigned int numSaison)
{
    // To do
    int indexSaison = trouverIndexSaison(numSaison);
    if (indexSaison != SAISON_INEXSISTANTE)
    {
        saisons_.erase(saisons_.begin() + trouverIndexSaison(numSaison));
    }
    return *this;
}

// To do
//!  Méthode qui ajoute un épisode à une saison
//! \param numSaison                  Le numéro de la saison à laquelle ajouter l'épisode
//! \param episode                    L'épisode à ajouter
void GestionnaireSaisons::ajouterEpisode(const unsigned int numSaison,
                                         std::unique_ptr<Episode> episode)
{
    // To do
    int indexSaison = trouverIndexSaison(numSaison);
    if (indexSaison != SAISON_INEXSISTANTE)
    {
        *(saisons_[indexSaison]) += std::move(episode);
    }
}

// To do
//!  Méthode qui retire un épisode à une saison
//! \param numSaison                  Le numéro de la saison à laquelle retirer l'épisode
//! \param episode                    Le numéro de l'épisode à enlever
void GestionnaireSaisons::retirerEpisode(const unsigned int numSaison,
                                         const unsigned int numEpisode)
{
    // To do
    int indexSaison = trouverIndexSaison(numSaison);
    *saisons_[indexSaison] -= numEpisode;
}

/// To do
//!  Méthode qui trouve l'index d'une saison dans le vecteur saisons_
//! \param numSaison                  Le numéro de la saison à trouver
//! \return                           L'index de la saison
size_t GestionnaireSaisons::trouverIndexSaison(const unsigned int numSaison) const
{
    // To do
    for (int i = 0; i < saisons_.size(); i++)
    {
        if (numSaison == saisons_[i]->getNumSaison())
        {
            return i;
        }
    }
    return SAISON_INEXSISTANTE;
}

// To do
//!  Méthode qui trouve une saison dans le vecteur de GestionnaireSaisons
//! \param numSaison                  Le numéro de la saison à trouver
//! \return                           Un pointeur (raw) vers la saison
Saison* GestionnaireSaisons::getSaison(const unsigned int numSaison) const
{
    // todo
    int indexSaison = trouverIndexSaison(numSaison);
    if (indexSaison != SAISON_INEXSISTANTE)
    {
        return saisons_[indexSaison].get();
    }
    return nullptr;
}

// To do
//!  Méthode getter pour trouver le nombre de saisons dans le vecteur
//! \return                           Le nombre de saisons
size_t GestionnaireSaisons::getNbSaisons() const
{
    // To do
    return saisons_.size();
}
