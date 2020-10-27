/// Analyseur de statistiques grâce aux logs.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

/// \author         william younanian   2022401
///                 jean paul khoueiry 2011397
/// \date           18 avril 2020
/// \file           AnalyseurLogs.cpp

#include "AnalyseurLogs.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Foncteurs.h"

/// Ajoute les lignes de log en ordre chronologique à partir d'un fichier de logs.
/// \param nomFichier               Le fichier à partir duquel lire les logs.
/// \param gestionnaireUtilisateurs Référence au gestionnaire des utilisateurs pour lier un utilisateur à un log.
/// \param gestionnaireFilms        Référence au gestionnaire des films pour pour lier un film à un log.
/// \return                         True si tout le chargement s'est effectué avec succès, false sinon.
bool AnalyseurLogs::chargerDepuisFichier(const std::string& nomFichier,
                                         GestionnaireUtilisateurs& gestionnaireUtilisateurs,
                                         GestionnaireFilms& gestionnaireFilms)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        logs_.clear();
        vuesFilms_.clear();

        bool succesParsing = true;

        std::string ligne;
        while (std::getline(fichier, ligne))
        {
            std::istringstream stream(ligne);

            std::string timestamp;
            std::string idUtilisateur;
            std::string nomFilm;

            if (stream >> timestamp >> idUtilisateur >> std::quoted(nomFilm))
            {
                // TODO: Uncomment une fois que la fonction creerLigneLog est écrite
                 creerLigneLog(timestamp, idUtilisateur, nomFilm, gestionnaireUtilisateurs, gestionnaireFilms);
            }
            else
            {
                std::cerr << "Erreur AnalyseurLogs: la ligne " << ligne
                          << " n'a pas pu être interprétée correctement\n";
                succesParsing = false;
            }
        }
        return succesParsing;
    }
    std::cerr << "Erreur AnalyseurLogs: le fichier " << nomFichier << " n'a pas pu être ouvert\n";
    return false;
}

//TODO
/// Crée une ligne de log
/// \ param timestamp                   Le temps ou le film a été regardé
/// \ param idUtilisateur               Le id de l'utilisateur qui a regardé le film
/// \ param nomFilm                     Le nom du film regardé
/// \ param gestionnaireUtilisateurs    Le gestionnaire d'utilisateurs pour trouver l'utilisateur
/// \ param gestionnaireFilms           Le gestionnaire de films pour trouver le film
/// \ return    Un bool représentant si la création et l'addition de lignelog a été faite avec succès
bool AnalyseurLogs::creerLigneLog(const std::string& timestamp, const std::string& idUtilisateur, const std::string& nomFilm,
                       GestionnaireUtilisateurs& gestionnaireUtilisateurs, GestionnaireFilms& gestionnaireFilms)
{
    LigneLog lignelog = {timestamp, gestionnaireUtilisateurs.getUtilisateurParId(idUtilisateur), gestionnaireFilms.getFilmParNom(nomFilm)};
    if(lignelog.film != nullptr && lignelog.utilisateur != nullptr)
    {
        ajouterLigneLog(lignelog);
        return true;
    }
    return false;
}

//TODO
/// Ajoute la ligne de log créé aux attributs logs_ et vuesFilms_
/// \param ligneLog                La ligne de log à ajouter
void AnalyseurLogs::ajouterLigneLog(const LigneLog& ligneLog)
{
    // binary_search
    auto estTrouve = std::upper_bound(logs_.begin(),logs_.end(),ligneLog, ComparateurLog());
    logs_.insert(estTrouve, ligneLog);
    vuesFilms_[ligneLog.film]++;
}

//TODO
/// Méthode qui trouve le nombre de vues d'un film
/// \param film                Le film pour lequel on doit trouver le nombre de vues
/// \return                    Le nombre de vues du film, ou 0 si le film n'existe pas
int AnalyseurLogs::getNombreVuesFilm(const Film* film) const
{
    auto it = vuesFilms_.find(film);
    if(it != vuesFilms_.end())
        return it->second;
    return 0;
}

//TODO
/// Méthode qui trouve le film le plus populaire
/// \return                Un pointeur constant au film le plus populaire
const Film* AnalyseurLogs::getFilmPlusPopulaire() const
{
    auto it = std::max_element(vuesFilms_.begin(), vuesFilms_.end(), ComparateurSecondElementPaire<const Film*, int>());
    if(it == vuesFilms_.end())
        return nullptr;
    return it->first;
}

//TODO
/// Méthode qui trouve les N films les plus populaires
/// \param nombre                  le nombre de films à trouver
/// \return                        Un vecteur de pairs des N films les plus populaires avec le nombre de vues
std::vector<std::pair<const Film*, int>> AnalyseurLogs::getNFilmsPlusPopulaires(std::size_t nombre) const
{
    std::vector<std::pair<const Film*, int>> filmsPlusPopulaires(std::min(nombre, vuesFilms_.size()));
    std::partial_sort_copy( vuesFilms_.begin(),
                            vuesFilms_.end(),
                            filmsPlusPopulaires.begin(),
                            filmsPlusPopulaires.end(),
                            [](auto &pair1, auto &pair2) { return pair1.second > pair2.second;});
    return filmsPlusPopulaires;
}

//TODO
/// Méthode qui trouve le nombre de vues d'un utilisateur
/// \param utilisateur             l'utilisateur pour lequel trouver le nombre de vues
/// \return                        le nombre de vues de cet utilisateur
int AnalyseurLogs::getNombreVuesPourUtilisateur(const Utilisateur* utilisateur) const
{
    return static_cast<int>(std::count_if(logs_.begin(), logs_.end(), [utilisateur](LigneLog lignelog){return utilisateur == lignelog.utilisateur;}));
}

//TODO
/// Méthode qui trouve les films vus par un utilisateur
/// \param utilisateur              l'utilisateur en question
/// \return                         un vecteur de const Film* pointant aux films vus par l'utilisateur
std::vector<const Film*> AnalyseurLogs::getFilmsVusParUtilisateur(const Utilisateur* utilisateur) const
{
    std::unordered_set<const Film*> setFilmsVus;
    for(const LigneLog& lignelog : logs_)
    {
        if(lignelog.utilisateur == utilisateur)
            setFilmsVus.insert(lignelog.film);
    }
    std::vector<const Film*> filmsVusParUtilisateur(setFilmsVus.size());
    std::copy(setFilmsVus.begin(), setFilmsVus.end(), filmsVusParUtilisateur.begin());
    return filmsVusParUtilisateur;
}