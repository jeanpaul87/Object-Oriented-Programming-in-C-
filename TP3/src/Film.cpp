/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   film.cpp
   Date : 1 mars 2020 */

// To do
#include "Film.h"
#include "Media.h"

// To do
//Constructeur avec l'auteur de la classe Film
//! \param auteur              L'auteur du film
Film::Film(Auteur* auteur)
    : Media(auteur, TypeMedia::Film)
    , duree_("")
// To do
{
}

// To do
//!  Constructeur par paramètres de la classe Film
//! \param nom                           Le nom du film
//! \param anneeDeSortie                 L'année de sortie du film
//! \param genre                         Le genre du film
//! \param pays                          Le pays du film
//! \param estRestreintParAge            Un bool représentant si le film est restreint par age
//! \param auteur                        l'auteur du film
//! \param duree                         La duree du film
Film::Film(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
           bool estRestreintParAge, Auteur* auteur, const std::string& duree)
    : Media(nom, anneeDeSortie, genre, pays, estRestreintParAge, auteur, TypeMedia::Film)
    , duree_(duree)
// To do
{
}

// To do
//!  Méthode pour afficher un film dans un stream
//! \param os                         Le stream dans lequel afficher
//! \return                           Le stream   
std::ostream& Film::afficher(std::ostream& os) const
{
    // To do
    //NOTE: Notre chargé nous a fait la mention d'enlever les accents dans le main
    //On n'a donc pas mis d'accents à Duree
    Media::afficher(os) << "\tDuree: " << duree_;
    return os;
}

// To do
//!  Méthode pour lire un film d'un stream
//! \param is                         Le stream duquel prendre les informations du film
//! \return                           Le stream   
std::istream& Film::lire(std::istream& is)
{ // To do

    Media::lire(is) >> std::quoted(duree_);
    return is;
}

// To do
//!  Méthode pour cloner un film
//! \return                           Un unique_ptr au film  
std::unique_ptr<Media> Film::clone() const
{
    // To do
    return std::make_unique<Film>(*this);
}
