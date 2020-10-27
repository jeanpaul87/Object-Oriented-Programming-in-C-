/// Fonction main.
/// \author Misha Krieger-Raynauld
/// \date 2020-01-12

/// \author         william younanian   2022401
///                 jean paul khoueiry 2011397
/// \date           18 avril 2020
/// \file           main.cpp

#include <iostream>
#include "AnalyseurLogs.h"
#include "GestionnaireFilms.h"
#include "GestionnaireUtilisateurs.h"
#include "Tests.h"
#include "WindowsUnicodeConsole.h"

int main()
{
    // Change le code page de la console Windows en UTF-8 si l'OS est Windows
    initializeConsole();

    Tests::testAll();

    // Écrivez le code pour le bonus ici
    GestionnaireUtilisateurs gestionnaireUtilisateurs;
    gestionnaireUtilisateurs.chargerDepuisFichier("utilisateurs.txt");

	std::cout << "Le gestionnaire d'utilisateurs contient " << gestionnaireUtilisateurs.getNombreUtilisateurs()
	 		  << " utilisateurs: \n";

	std::cout << gestionnaireUtilisateurs;

    GestionnaireFilms gestionnaireFilms;
    gestionnaireFilms.chargerDepuisFichier("films.txt");
    std::cout << gestionnaireFilms;

    AnalyseurLogs analyseurLogs;
    analyseurLogs.chargerDepuisFichier("logs.txt", gestionnaireUtilisateurs, gestionnaireFilms);

    std::cout << "\nFilm le plus populaire (" <<  analyseurLogs.getNombreVuesFilm(analyseurLogs.getFilmPlusPopulaire())
        <<"): "<<   *analyseurLogs.getFilmPlusPopulaire()  << "\n\n";

    std::cout << "5 films les plus populaires:\n";
    std::vector<std::pair<const Film*, int>> filmsPlusPopulaires = analyseurLogs.getNFilmsPlusPopulaires(5);
    for(auto& [film, num] : filmsPlusPopulaires)
        std::cout << "\t" << *film << " (" << analyseurLogs.getNombreVuesFilm(film) << " vues)\n";

    std::cout << "\nNombre de films vus par l'utilisateur karasik@msn.com: " 
        << analyseurLogs.getNombreVuesPourUtilisateur(gestionnaireUtilisateurs.getUtilisateurParId("karasik@msn.com")) << "\n";
}
