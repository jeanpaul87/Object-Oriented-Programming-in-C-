#include "Pixel.h"

/**
 * @brief constructeur par défaut de la classe
 */
Pixel::Pixel() : rouge_(0), vert_(0), bleu_(0) {}
/**
 * @brief constructeur par paramètres de la classe
 * @param rouge, l'élément R du pixel, entre 0 -> 255
 * @param vert, l'élément G du pixel, entre 0 -> 255
 * @param bleu, l'élément B du pixel, entre 0 -> 255
 */
Pixel::Pixel(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : rouge_(rouge), vert_(vert), bleu_(bleu) {}

//! Operateur d'egalite qui assigne un pixel a une autre.
//! /param Pixel le pixel a copier.
void Pixel::operator=(const Pixel &pixel) {
  // TO DO
    if (this != &pixel)
    {
        this->bleu_ = pixel.bleu_;
        this->rouge_ = pixel.rouge_;
        this->vert_ = pixel.vert_;
    }
}
//! Méthode qui set la couleur rouge du pixel
//! \param rouge  la valeur de de la couleur rouge
void Pixel::setRouge(int rouge) {
    // TO DO
    rouge = ((rouge) < 0) ? 0 : rouge;
    rouge_ = ((rouge) > 255) ? 255 : rouge;
}

//! Méthode qui set la couleur vert du pixel
//! \param vert  la valeur de de la couleur vert
void Pixel::setVert(int vert) {
    // TO DO
    vert = (vert < 0) ? 0 : vert;
    vert_ = (vert > 255) ? 255 : vert;
}

//! Méthode qui set la couleur bleu du pixel
//! \param bleu  la valeur de de la couleur bleu
void Pixel::setBleu(int bleu) {
    // TO DO
    bleu = (bleu < 0) ? 0 : bleu;
    bleu_ = (bleu > 255) ? 255 : bleu;
}

/**
 * @brief retourn l'attribut rouge_ du pixel
 * @return rouge_ du type uint8_t
 */
uint8_t Pixel::getRouge() const { return rouge_; }
/**
 * @brief retourn l'attribut vert_ du pixel
 * @return vert_ du type uint8_t
 */
uint8_t Pixel::getVert() const { return vert_; }
/**
 * @brief retourn l'attribut bleu_ du pixel
 * @return bleu_ du type uint8_t
 */
uint8_t Pixel::getBleu() const { return bleu_; }

//! Méthode qui affiche un pixel en hexa decimal d'ordre (Rouge,Vert,Bleu)
//! \param stream Le stream dans lequel afficher
//! \param pixel Le pixel a afficher
//! \return   Le stream
std::ostream &operator<<(std::ostream &os, Pixel pixel) {
  // TO DO
    
    os << "#" <<std::uppercase<< std::setfill('0')<<std::hex <<std::setw(2) << unsigned(pixel.getRouge()) << " "
		 << std::setw(2) << unsigned(pixel.getVert()) << " "
		<< std::setw(2) << unsigned(pixel.getBleu());
    return os;
}

//! opérateur qui saisie un pixel
//! \param is Le istream duquel on va lire
//! \param pixel Pixel dont on veut faire la saisie
//! \return   Le stream
std::istream &operator>>(std::istream &is, Pixel &pixel) {
  // TO DO
    int bleu, rouge, vert;
    is >> rouge >> vert>> bleu;
    pixel.setRouge(rouge);
    pixel.setVert(vert);
    pixel.setBleu(bleu);
    return is;

}