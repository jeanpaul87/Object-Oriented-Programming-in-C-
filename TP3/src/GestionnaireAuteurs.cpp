/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   GestionnaireAuteurs.cpp
   Date : 1 mars 2020 */

#include "GestionnaireAuteurs.h"

//! Constructeur de la classe GestionnaireAuteurs
GestionnaireAuteurs::GestionnaireAuteurs()
    : auteurs_(std::vector<Auteur>(16))
{
}

//! Mehode qui cherche un auteur par son nom complet
//! \param nomAuteur Le nom de l'auteur à trouver
//! \return          Un pointeur vers l'auteur. Le pointeur est nullptr si l'auteur n'existe pas.
Auteur* GestionnaireAuteurs::chercherAuteur(const std::string& nomAuteur)
{
    for (size_t i = 0; i < auteurs_.size(); i++)
        if (auteurs_[i] == nomAuteur)
            return &auteurs_[i];

    return nullptr;
}

//! Methode qui prend un nom de fichier en paramètre et qui charge les auteurs
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool representant si le chargement a ete un succès
bool GestionnaireAuteurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        auteurs_.clear();
        std::string ligne;
        while (getline(fichier, ligne))
        {
            std::istringstream stream(ligne);
            Auteur auteur;
            if (!(stream >> auteur))
            {
                return false;
            }
            (*this) += auteur;
        }
            return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

//! Methode qui retourne le nombre d'auteurs
//! \return Le nombre d'auteurs
size_t GestionnaireAuteurs::getNbAuteurs() const
{
    return auteurs_.size();
}

//! operateur qui ajoute un auteur à la liste des auteurs
//! \param auteur L'auteur à ajouter
//! \return       Un bool representant si l'operation a fonctionnne
bool GestionnaireAuteurs::operator+=(const Auteur& auteur)
{
    if (auteurs_.size() >= NB_AUTEURS_MAX)
        return false;

    auteurs_.push_back(auteur);
    return true;
}

//! operateur qui affiche le film
//! \param os Le stream dans lequel afficher
//! \param gestionnaireAuteurs le gestionnaire que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnaireAuteurs& gestionnaireAuteurs)
{
    for (size_t i = 0; i < gestionnaireAuteurs.auteurs_.size(); i++)
        // if(gestionnaireAuteurs.auteurs_[i] != NULL)
        os << gestionnaireAuteurs.auteurs_[i] << '\n';

    return os;
}
