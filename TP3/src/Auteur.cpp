/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   auteur.cpp
   Date : 1 mars 2020 */

// To do
#include "Auteur.h"

// To do
//Constructeur par defaut de la classe Auteur
Auteur::Auteur()
    : nom_("")
    , anneeDeNaissance_(0)
    , nbMedias_(0)
// To do
{
}

//! Constructeur de la classe Auteur
//! \param nom              Nom de l'auteur
//! \param anneeDeNaissance Annee de naissance de l'auteur
Auteur::Auteur(const std::string& nom, unsigned int anneeDeNaissance)
    : nom_(nom)
    , anneeDeNaissance_(anneeDeNaissance)
    , nbMedias_(0)
{
}

//! Methode qui retourne le nom de l'auteur
//! \return Le nom de l'auteur
const std::string& Auteur::getNom() const
{
    return nom_;
}

//! Methode qui retourne l'annee de naissance de l'auteur
//! \return L'annee de naissance de l'auteur
unsigned int Auteur::getAnneeDeNaissance() const
{
    return anneeDeNaissance_;
}

//! Methode qui retourne le nombre de films de l'auteur
//! \return Le nombre de films de l'auteur
unsigned int Auteur::getNbMedias() const
{
    return nbMedias_;
}

//! Methode qui set le nombre de films de l'auteur
//! \param nbFilms  Le nombre de films de l'auteur
void Auteur::setNbMedias(unsigned int nbFilms)
{
    nbMedias_ = nbFilms;
}

//! Operateur qui compare un string avec le nom de l'auteur avec auteur comme operande de gauche
//! \param nom le nom avec le quel on veut compare l'auteur
//! \return vrai si les noms sont identique, faux sinon
bool Auteur::operator==(const std::string& nom) const
{
    return (nom_ == nom);
}

//! operateur qui affiche un auteur
//! \param os Le stream dans lequel afficher
//! \param auteur l'auteur a afficher
std::ostream& operator<<(std::ostream& os, const Auteur& auteur)
{
    os << "Nom: " << auteur.nom_ << " | Date de naissance: " << auteur.anneeDeNaissance_
       << " | Nombre de Film/Serie: " << auteur.nbMedias_;
    return os;
}

// To do
//Operateur >> pour mettre le istream dans auteur
std::istream& operator>>(std::istream& is, Auteur& auteur)
{
    // To do
    is >> std::quoted(auteur.nom_) >> auteur.anneeDeNaissance_; 
    return is;
}