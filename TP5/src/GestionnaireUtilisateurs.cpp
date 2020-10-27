/// Gestionnaire d'utilisateurs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

/// \author         william younanian   2022401
///                 jean paul khoueiry 2011397
/// \date           18 avril 2020
/// \file           GestionnaireUtilisateurs.cpp

#include "GestionnaireUtilisateurs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

/// Affiche les informations des utilisateurs gérés par le gestionnaire d'utilisateurs à la sortie du stream donné.
/// \param outputStream         Le stream auquel écrire les informations des utilisateurs.
/// \param gestionnaireFilms    Le gestionnaire d'utilisateurs à afficher au stream.
/// \return                     Une référence au stream.
std::ostream& operator<<(std::ostream& outputStream, const GestionnaireUtilisateurs& gestionnaireUtilisateurs)
{
    // TODO: Uncomment une fois que la fonction getNombreUtilisateurs est écrite
    outputStream << "Le gestionnaire d'utilisateurs contient " << gestionnaireUtilisateurs.getNombreUtilisateurs()
                 << " utilisateurs:\n";

    // TODO: Réécrire l'implémentation avec des range-based for et structured bindings (voir énoncé du TP)
    for (const auto& [id, utilisateur] : gestionnaireUtilisateurs.utilisateurs_) {
        outputStream<< '\t' << utilisateur << '\n';
    }
    return outputStream;
}

/// Ajoute les utilisateurs à partir d'un fichier de données d'utilisateurs.
/// \param nomFichier   Le fichier à partir duquel lire les informations des utilisateurs.
/// \return             True si tout le chargement s'est effectué avec succès, false sinon.
bool GestionnaireUtilisateurs::chargerDepuisFichier(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        utilisateurs_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string id;
            std::string nom;
            int age;
            int pays;

            if (stream >> id >> std::quoted(nom) >> age >> pays)
            {
                // TODO: Uncomment une fois que la fonction ajouterUtilisateur est écrite
                ajouterUtilisateur(Utilisateur{id, nom, age, static_cast<Pays>(pays)});
            }
            else
            {
                std::cerr << "Erreur GestionnaireUtilisateurs: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur GestionnaireUtilisateurs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

//TODO
/// Ajoute un utilisateur au gestionnaire, en l’insérant dans la map avec son ID comme clé et l’utilisateur comme valeur
/// \param utilisateur  L'utilisateur a afficher
/// \return             True si l’utilisateur a été ajouté avec succès, false si l’utilisateur n’a pas pu être ajouté puisque son ID était déjà présent dans la map
bool GestionnaireUtilisateurs::ajouterUtilisateur(const Utilisateur& utilisateur)
//"prénom.nom.1@email.com", "Prénom Nom", 20, Pays::Canada
{
    return utilisateurs_.std::unordered_map<std::string, Utilisateur>::emplace(utilisateur.id, utilisateur).second;
}

//TODO
/// Supprime un utilisateur du gestionnaire à partir de son ID
/// \param utilisateur  L'utilisateur a afficher
/// \return             True si l’utilisateur a été trouvé et supprimé avec succès, false si
///                     l’utilisateur n’a pas pu être supprimé puisque son ID n’était pas déjà présent dans
///                     la map.
bool GestionnaireUtilisateurs::supprimerUtilisateur(const std::string& idUtilisateur)
{
	return  utilisateurs_.unordered_map<std::string, Utilisateur>::erase(idUtilisateur);
}

//TODO
/// Retourne le nombre d’utilisateurs présentement dans le gestionnaire.
/// \return            Le nombre d’utilisateurs présentement dans le gestionnaire.
std::size_t GestionnaireUtilisateurs::getNombreUtilisateurs() const
{
    return utilisateurs_.size();
}

//TODO
/// Trouve et retourne un utilisateur en le cherchant à partir de son ID
/// \param utilisateur  L'utilisateur a afficher
/// \return             un pointeur vers l’utilisateur ou nullptr si aucun utilisateur avec le ID
///                     ne peut être trouvé.
const Utilisateur* GestionnaireUtilisateurs::getUtilisateurParId(const std::string& id) const
{
	auto it = utilisateurs_.find(id);
    if(it!=utilisateurs_.end())
       return &(it->second);
    return nullptr;
}