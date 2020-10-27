

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <string>
#include <unordered_map>
#include "LigneLog.h"

/// \author  		william younanian   2022401
///                	jean paul khoueiry 2011397
/// \date      		18 avril 2020
/// \file         	GestionnaireAuteurs.cpp


class EstDansIntervalleDatesFilm
{
public:
	/// Constructeur 
	/// \param anneeInferieure      la valeur de l'annee min
	/// \param anneeSuperieure		la valeur de l'annee max
    EstDansIntervalleDatesFilm (int anneeInferieure, int anneeSuperieure) : 
        min_(anneeInferieure), 
        max_(anneeSuperieure){};

	/// Foncteur prédicat unaire servant à déterminer si un film est sorti entre deux années 
	/// \param film					 pointeur inteligant film qu'on veut voire si il est entre les deux intrvale de ces parametre pour voire si il est entre ces deux dates'
	/// \return						 Retourne true si le film est dans ces deux intervalles.
    bool operator()(const std::unique_ptr<Film>& film)//prendre en parametrestd::unique_ptr
    {
        return (film->annee >= min_ && film->annee <= max_);
	};		  
private:
    int min_, max_;
};

class ComparateurLog
{
public:
	//Constructeur par defaut
	ComparateurLog(){};

	/// Foncteur prédicat binaire comparant les dates des lignes de log pour indiquer si elles sont en ordre chronologique. 
	/// \param ligneLog1       Le stream auquel écrire les informations des utilisateurs.
	/// \param ligneLog2		 Le gestionnaire d'utilisateurs à afficher au stream.
	bool operator()(LigneLog ligneLog1, LigneLog ligneLog2)
	{
		return (ligneLog1.timestamp < ligneLog2.timestamp);
	};
};

template<class T1,class T2>
class ComparateurSecondElementPaire
{
public:
	/// Constructeur par defaut
	ComparateurSecondElementPaire(){};

	/// Foncteur comparant les seconds éléments de paires pour déterminer si elles sont en ordre. 
	/// \param pair1		une paire pour effectuer la comparaison
	/// \param pair2		une autre paire pour effectuer la comparaison
	/// \return					 True si le second élément de la première paire est strictement inférieur au second
	///							 élément de la deuxième paire, false sinon
	bool operator()(const std::pair<T1, T2>& pair1 , const std::pair<T1, T2>& pair2)
	{
		return (pair1.second<pair2.second);
	}
};
#endif
