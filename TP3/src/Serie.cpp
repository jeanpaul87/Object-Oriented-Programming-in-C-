/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   serie.cpp
   Date : 1 mars 2020 */

// To do
#include "Serie.h"

// To do
//!  Constructeur de serie avec un auteur
//! \param auteur                        L'auteur de la serie
Serie::Serie(Auteur* auteur)
    : Media(auteur, Media::TypeMedia::Serie)
    , GestionnaireSaisons()
// To do
{
}

// To do
//!  Constructeur par paramètres de serie
Serie::Serie(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur)
    : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, Media::TypeMedia::Serie)
    , GestionnaireSaisons()
// To do
{
}

// To do
//!  Constructeur par copie
//! \param serie                       La serie à copier
Serie::Serie(const Serie& serie)
    : Media(serie)
// To do
{
    // To do
    for (int i = 0; i < serie.saisons_.size(); i++)
    {
        saisons_.push_back(std::make_unique<Saison>(*(serie.saisons_[i])));
    }
}

// To do
//!  Méthode qui affiche une série dans un stream
//! \param os                        Le stream
//! \return                          Le stream
std::ostream& Serie::afficher(std::ostream& os) const
{
    // To do
    Media::afficher(os);
    //Saison saison(5, 15);Saison num 5 avec 15 episodes max pour tester, ca marche
    for (int i = 0; i < saisons_.size(); i++)
    {
        os << *(saisons_[i]); // affiche les saisons
    }
    return os;
}

// To do
//!  Méthode qui retourne un objet alloué dynamiquement qui est une copie de l'objet courante
//! \return                              L'objet alloué dynamiquement
std::unique_ptr<Media> Serie::clone() const
{
    // To do
    return std::make_unique<Media>(*this);
}