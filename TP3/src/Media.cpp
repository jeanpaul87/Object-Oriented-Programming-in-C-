/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   media.cpp
   Date : 1 mars 2020 */

#include "Media.h"

namespace
{
    //! Fonction qui convertit le enum Media::Genre en string
    //! \param genre    Le genre à convertir
    //! \return         Le string qui represente le enum
    const std::string& getGenreString(Media::Genre genre)
    {
        static const std::string NOMS_GENRES[] = {"Action",
                                                  "Aventure",
                                                  "Comedie",
                                                  "Horreur",
                                                  "Romance"};

        auto index = enum_value(genre);
        assert(valid_as_enum<Media::Genre>(index));
        return NOMS_GENRES[index];
    }

    //! Fonction qui convertit le enum Pays en string
    //! \param pays     Le pays à convertir
    //! \return         Le string qui represente le enum
    const std::string& getPaysString(Pays pays)
    {
        static const std::string NOMS_PAYS[] = {"Bresil",
                                                "Canada",
                                                "Chine",
                                                "EtatsUnis",
                                                "France",
                                                "Japon",
                                                "RoyaumeUni",
                                                "Russie",
                                                "Mexique"};
        auto index = enum_value(pays);
        assert(valid_as_enum<Pays>(index));
        return NOMS_PAYS[index];
    }
} // namespace

// To do
//!  Constructeur de la classe média
//! \param auteur                         L'auteur du media
//! \param typeMedia                      Le type du media 
Media::Media(Auteur* auteur, Media::TypeMedia typeMedia)
    : auteur_(auteur)
    , typeMedia_(typeMedia)
    , nom_("")
    , anneeDeSortie_(0)
    , genre_(Genre::first_)
    , pays_(Pays::first_)
    , estRestreintParAge_(0)
// To do
{
}

// To do
//!  Constructeur par paramètres de la classe media
Media::Media(const std::string& nom, unsigned int anneeDeSortie, Genre genre, Pays pays,
             bool estRestreintParAge, Auteur* auteur, Media::TypeMedia typeMedia)
    : nom_(nom)
    , anneeDeSortie_(anneeDeSortie)
    , genre_(genre)
    , pays_(pays)
    , estRestreintParAge_(estRestreintParAge)
    , auteur_(auteur)
    , typeMedia_(typeMedia)
// To do
{
}

// To do
// Constructeur par copie de media
Media::Media(const Media& serie)
{
    // To do
    nom_ = serie.nom_;
    anneeDeSortie_ = serie.anneeDeSortie_;
    genre_ = serie.genre_;
    pays_ = serie.pays_;
    estRestreintParAge_ = serie.estRestreintParAge_;
    auteur_ = serie.auteur_;
    typeMedia_ = serie.typeMedia_;
    for (int i = 0; i < serie.paysRestreints_.size(); i++)
    {
        paysRestreints_.push_back(serie.paysRestreints_[i]);
    }
}

// To do
//!  Destructeur virtuel de media
Media::~Media()
{ 
  // To do
    paysRestreints_.clear();

}

// To do
//!  Méthode qui ajoute un pays restreint à un media
//! \param pays                          Le pays à ajouter
void Media::ajouterPaysRestreint(Pays pays)
{
    // To do
    paysRestreints_.push_back(pays);
}

// To do
//!  Méthode qui supprime un pays restreint à un media
//! \param pays                          Le pays à supprimer
void Media::supprimerPaysRestreints()
{
    // To do
    paysRestreints_.clear();
}

// To do
//!  Méthode qui regarde si un un média est restreint dans un certain pays
//! \param pays                          Le pays à vérifier
//! \return                              un bool qui représente si le pays est restreint
bool Media::estRestreintDansPays(Pays pays) const
{
    // To do
    for (int i = 0; i < paysRestreints_.size(); i++)
    {
        if (paysRestreints_[i] == pays)
        {
            return true;
        }
    }
    return false;
}

// To do
//!  Méthode qui regarde si un un média est restreint par age
//! \return                              un bool qui représente si le pays est restreint
bool Media::estRestreintParAge() const
{
    // To do
    // done
    return estRestreintParAge_;
}

// To do
//!  Méthode qui affiche le media
//! \param os                          Le stream dans lequel afficher
//! \return                            Le stream os
std::ostream& Media::afficher(std::ostream& os) const
{
    // To do
    os << nom_ << std::endl;
    os << "\tDate de sortie: " << anneeDeSortie_ << std::endl;
    os << "\tGenre: " << getGenreString(genre_) << std::endl;
    os << "\tAuteur: " << auteur_->getNom() << std::endl;
    os << "\tPays: " << getPaysString(pays_) << std::endl;
    if (paysRestreints_.size() == 0)
    {
        os << "\tAucun pays restreint." << std::endl;
    }
    else
    {
        os << "\tPays restreints: " << std::endl;
        for (int i = 0; i < paysRestreints_.size(); i++)
        {
            os << "\t\t" << getPaysString(paysRestreints_[i]) << std::endl;
        }
    }
    return os;
}

// To do
//!  Surcharge de l'opérateur d'affichage
//! \param os                          Le stream os
//! \param media                       Le média
//! \return                            Le stream
std::ostream& operator<<(std::ostream& os, const Media& media)
{ // To do
    return media.afficher(os);
}

// To do
//!  Méthode getter qui trouve le genre d'un média
//! \return                            Le genre
Media::Genre Media::getGenre() const
{
    // To do
    return genre_;
}

// To do
//!  Méthode getter qui retourne le nom d'un média
//! \return                            Le nom
const std::string& Media::getNom() const
{
    // To do
    return nom_;
}

// To do
//!  Méthode getter qui retourne le type d'un média
//! \return                            Le type du média
Media::TypeMedia Media::getTypeMedia() const
{
    // To do
    return typeMedia_;
}

//!  Méthode getter qui retourne l'auteur d'un média
//! \return                            L'auteur en pointeur raw
Auteur* Media::getAuteur() const
{
    return auteur_;
}

// To do
//!  Méthode qui lit un is et le met dans média
//! \param is                            Le stream is
//! \return                              Le stream is
std::istream& Media::lire(std::istream& is)
{
    // To do
    // On a enleve type et auteur
    int valeurNumeriqueGenre, valeurNumeriquePays;
    is >> std::quoted(nom_) >> anneeDeSortie_ >> valeurNumeriqueGenre >> valeurNumeriquePays >>
        estRestreintParAge_;
    genre_ = static_cast<Genre>(valeurNumeriqueGenre);
    pays_ = static_cast<Pays>(valeurNumeriquePays);
    return is;
}

// To do
//!  Opérateur de lecture
//! \param is                            Le stream is
//! \param media                         Le media
//! \return                              Le stream is
std::istream& operator>>(std::istream& is, Media& media)
{
    return media.lire(is);
}

// To do
//!  Méthode qui retourne un objet alloué dynamiquement qui est une copie de l'objet courant 
//! \return                              La copie
std::unique_ptr<Media> Media::clone() const
{
    // To do
    return std::make_unique<Media>(*this);
}