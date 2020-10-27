/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   Matrice.h
   Date : 26 Mars 2020
*/

#ifndef MATRICE_H
#define MATRICE_H

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

template <typename T> class Matrice {

public:
  Matrice();
  // Destructeur
  ~Matrice() = default;
  T operator()(const size_t &posY, const size_t &posX) const;
  // Lecture du fichier
  bool chargerDepuisFichier(const std::string &nomFichier);
  bool lireElement(const std::string &elementFichier, const size_t &posY,
                   const size_t &posX);
  // Remplir un matrice
  bool ajouterElement(T element, const size_t &posY, const size_t &posX);
  // Faire une copie
  std::unique_ptr<Matrice<T>> clone() const;
  // Setters
  void setHeight(size_t height);
  void setWidth(size_t width);
  // Getters
  size_t getHeight() const;
  size_t getWidth() const;

private:
  std::vector<std::vector<T>> elements_;
  size_t height_;
  size_t width_;
};

namespace {
static constexpr int CAPACITE_MATRICE = 100;
}

/**
 * @brief constructeur par défaut de la classe
 */
template <typename T> inline Matrice<T>::Matrice() : elements_(CAPACITE_MATRICE), height_(0), width_(0) 
{ 
  // TO DO
    for(int i=0; i<CAPACITE_MATRICE; i++){
        elements_[i] = std::vector<T>(CAPACITE_MATRICE);
	}
}
/**
 * @brief retourne le nombre de lignes de la matrice
 * @return l'attribut height_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getHeight() const 
{
  return height_;
}
/**
 * @brief retourne le nombre de colonnes de la matrice
 * @return l'attribut width_ de l'objet
 */
template <typename T> inline size_t Matrice<T>::getWidth() const 
{
  return width_;
}

//Todo
//! opérateur() qui retourn un element a une position [x,y]
//! \param posY La valeur de la position Y
//! \param posX La valeur de la position X
//! \return     L'élément T de la matrice à la position donnée
template <typename T> T Matrice<T>::operator()(const size_t &posY, const size_t &posX) const
{
    if(posY < height_ && posX < width_ && posY >= 0 && posX >= 0){
        return elements_[posY][posX];
	}
    return T();
}

//Todo
//! Méthode qui ajoute un element a un psition preci
//! \param element L'element qu'on veut ajouter
//! \param posY La valeur de la position Y ou on veut l'ajouter
//! \param posX La valeur de la position X ou on veut l'ajouter
//! \return   Si un ajout a ete efectuer ou non
template <typename T> bool Matrice<T>::ajouterElement(T element, const size_t &posY, const size_t &posX)
{
    bool ajoutEffectue = false;
    if(posY < CAPACITE_MATRICE && posX < CAPACITE_MATRICE && posY >= 0 && posX >= 0){
        (elements_[posY]).insert(elements_[posY].begin() + posX, element);
        ajoutEffectue = true;
	}
    return ajoutEffectue;
}

//Todo
//! Méthode qui lit l'élément à partir de la chaine de caracteres puis lajoute dans la matrice
//! \param element L'element qu'on veut lire
//! \param posY La valeur de la position Y ou on veut lire
//! \param posX La valeur de la position X ou on veut lire
//! \return   Si un bool si la lecture a ete efectuer ou non
template <typename T> bool Matrice<T>::lireElement(const std::string &elementFichier, const size_t &posY, const size_t &posX)
{
    T element;
	std::istringstream streamElement(elementFichier);
    streamElement >> element;
    return ajouterElement(element, posY, posX);
}

//Todo
//! Méthode qui charge la matrice à partir du fichier passe en parametre
//! \param nomFichier Le fichier qu'on veut lire
//! \return   Si un bool
template <typename T> bool Matrice<T>::chargerDepuisFichier(const std::string &nomFichier)
{
    std::string ligne, mot;
    std::ifstream fichier(nomFichier);
    if(fichier){
        int posY = -1, posX = 0;
        while(getline(fichier, ligne)){ 
            if (ligne == "L") {
                posY++;
                posX = 0;
				continue;
            }
			if (!lireElement(ligne, posY, posX)) {
				return false;
			}
			posX++;
		}
		setHeight(posY+1);
		setWidth(posX);
        return true;
	}
    return false;
}

//Todo
//! méthode pour clôner la matrice
//! \return   Retourne un pointeur vers une copie de la matrice.
template <typename T> std::unique_ptr<Matrice<T>> Matrice<T>::clone() const
{
    return std::make_unique<Matrice<T>>(*this);
}

//Todo
//! setter pour le height
//! \param height Le height qu'on veut set
template<typename T> inline void Matrice<T>::setHeight(size_t height)
{
    height_ = (height < CAPACITE_MATRICE) ? height : CAPACITE_MATRICE;
    height_ = (height_ > 0) ? height_ : 0;
}

//Todo
//! setter pour le width
//! \param width Le width qu'on veut set
template<typename T> inline void Matrice<T>::setWidth(size_t width)
{
    width_ = (width < CAPACITE_MATRICE) ? width : CAPACITE_MATRICE; 
    width_ = (width_ > 0) ? width_ : 0;
}




#endif
