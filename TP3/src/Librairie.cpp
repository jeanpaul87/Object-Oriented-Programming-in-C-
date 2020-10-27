/*
   william younanian 2022401
   jean-paul khoueiry 2011397
   librairie.cpp
   Date : 1 mars 2020 */

#include "Librairie.h"

// To do
//!  Constructeur par copie de Librairie
//! \param librairie                  La librairie à copier
Librairie::Librairie(const Librairie& librairie)
{
    // To do
    *this = librairie;
}

// To do
//!  Surcharge de l'opérateur d'affectation
//! \param librairie                  La librairie à copier
//! \return                           La librairie courante 
Librairie& Librairie::operator=(const Librairie& librairie)
{
    // To do
    if (this != &librairie)
    {
        medias_.clear();
        for (int i = 0; i < librairie.medias_.size(); i++)
        {
            medias_.push_back(std::make_unique<Media>(*(librairie.medias_[i])));
        }
    }
    return *this;
}

//! Destructeur de la classe Librairie
Librairie::~Librairie()
{
    medias_.clear();
}

// To do
//!  Méthode pour trouver un film dans la liste des médias
//! \param nomFilm                    Le nom du film à trouver
//! \return                           Un pointeur raw vers le film 
Film* Librairie::chercherFilm(const std::string& nomFilm)
{
    // To do
    Media* media = chercherMedia(nomFilm, Media::TypeMedia::Film);
    return dynamic_cast<Film*>(media);
}

// To do
//!  Méthode pour trouver une série dans la liste des médias
//! \param nomSerie                   Le nom de la série à trouver
//! \return                           Un pointeur raw vers la série 
Serie* Librairie::chercherSerie(const std::string& nomSerie)
{
    // To do
    Media* media = chercherMedia(nomSerie, Media::TypeMedia::Serie);
    return dynamic_cast<Serie*>(media);
}

// To do
//!  Méthode pour ajouter une saison à une série
//! \param nomSerie                   Le nom de la série
//! \param saison                     La saison à ajouter
void Librairie::ajouterSaison(const std::string& nomSerie, std::unique_ptr<Saison> saison)
{
    // To do
    auto serie = chercherSerie(nomSerie);
    if(serie != nullptr)
    {
        *serie += std::move(saison);
    }
}

// To do
//!  Méthode pour retirer une saison à une série
//! \param nomSerie                   Le nom de la série
//! \param numSaison                  Le numéro de la saison
//! \param saison                     La saison à ajouter
void Librairie::retirerSaison(const std::string& nomSerie, unsigned int numSaison)
{
    // To do
    *chercherSerie(nomSerie) -= numSaison;
}

// To do
//!  Méthode pour ajouter un épisode à une serie
//! \param nomSerie                   Le nom de la série
//! \param numSaison                  Le numéro de la saison
//! \param episode                    L'épisode à ajouter
void Librairie::ajouterEpisode(const std::string& nomSerie, unsigned int numSaison,
                               std::unique_ptr<Episode> episode)
{
    // To do
    auto serie = chercherSerie(nomSerie);
    if (serie != nullptr)
    {
        serie->ajouterEpisode(numSaison, std::move(episode));
    }
}

//!  Méthode pour retirer un épisode à une serie
//! \param nomSerie                   Le nom de la série
//! \param numSaison                  Le numéro de la saison
//! \param numEpisode                 Le numéro de l'épisode à retirer
void Librairie::retirerEpisode(const std::string& nomSerie, unsigned int numSaison,
                               unsigned int numEpisode)
{
    // To do
    *(chercherSerie(nomSerie)->getSaison(numSaison)) -= numEpisode;
}

//! Methode qui charge les series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \param gestionnaireAuteurs  Le gestionnaire des auteurs. Necessaire pour associer une serie à un
//! auteur.
//! \return                     Un bool representant si le chargement a ete un succès.
bool Librairie::chargerMediasDepuisFichier(const std::string& nomFichier,
                                           GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (int i = 0; i < medias_.size(); i++)
        {
            medias_[i]->getAuteur()->setNbMedias(0);
        }
        medias_.clear();
        std::string ligne;
        while (getline(fichier, ligne))
        {
            if (!(lireLigneMedia(ligne, gestionnaireAuteurs)))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

//! Methode qui charge les restrictions des series à partir d'un fichier.
//! \param nomFichier           Le nom du fichier à lire.
//! \return                     Un bool representant si le chargement a ete un succès.
bool Librairie::chargerRestrictionsDepuisFichiers(const std::string& nomFichier)
{
    std::ifstream fichier(nomFichier);
    if (fichier)
    {
        for (size_t i = 0; i < medias_.size(); i++)
            medias_[i]->supprimerPaysRestreints();

        std::string ligne;
        while (getline(fichier, ligne))
        {
            if (!lireLigneRestrictions(ligne))
                return false;
        }
        return true;
    }
    std::cerr << "Le fichier " << nomFichier
              << " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
    return false;
}

// To do
//!  Méthode pour trouver le nombre de médias dans la librairie
//! \return                   Le nombre de medias
size_t Librairie::getNbMedias() const
{
    // To do
    return medias_.size();
}

// To do
//!  Surcharge de l'opérateur << qui prend un os à gauche et une librairie à droite
//! \param os                         Le stream dans lequel afficher
//! \param librairie                  La librairie à afficher
//! \return                           Le stream
std::ostream& operator<<(std::ostream& os, const Librairie& librairie)
{
    // To do
    for (int i = 0; i < librairie.medias_.size(); i++)
    {
        if (librairie.medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
        {
            librairie.medias_[i]->afficher(os) << std::endl;
        }
    }
    for (int i = 0; i < librairie.medias_.size(); i++)
    {
        if (librairie.medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
        {
            Serie* serie = dynamic_cast<Serie*>(librairie.medias_[i].get());
            serie->afficher(os) << std::endl;
        }
    }
    return os;
}

// To do
//!  Méthode pour trouver l'index d'un média
//! \param nomSerie                   Le nom du média
//! \return                           L'index du media
size_t Librairie::trouverIndexMedia(const std::string& nomMedia) const
{
    // To do
    for (int i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getNom() == nomMedia)
        {
            return i;
        }
    }
    return MEDIA_INEXSISTANT;
}

// To do
//!  Surcharge de l'opérateur += qui prend une librairie à gauche et un media à droite
//! \param media                      Le media a ajouter
//! \return                           L'objet librairie courant
Librairie& Librairie::operator+=(std::unique_ptr<Media> media)
{
    // To do
    if (media != nullptr)
    {
        medias_.push_back(std::move(media));
    }
    return *this;
}

// To do
//!  Surcharge de l'opérateur -= qui prend une librairie à gauche et le nom d'un média à gauche
//! \param nomMedia                   Le nom du media a enlever
//! \return                           L'objet librairie courant
Librairie& Librairie::operator-=(const std::string& nomMedia)
{
    // To do
    int indexMedia = trouverIndexMedia(nomMedia);
    if (indexMedia != MEDIA_INEXSISTANT)
    {
        medias_.erase(medias_.begin() + indexMedia);
    }
    return *this;
}

// To do
//!  Méthode pour chercher un média dans la librairie
//! \param nomMedia                   Le nom du média
//! \param typeMedia                  Le type du média
//! \return                           Un pointeur vers le média
Media* Librairie::chercherMedia(const std::string& nomMedia, Media::TypeMedia typeMedia)
{
    // To do
    int indexMedia = trouverIndexMedia(nomMedia);
    if (indexMedia == MEDIA_INEXSISTANT)
    {
        return nullptr;
    }
    return medias_[indexMedia].get();
}

// To do
//!  Méthode pour lire une ligne de restrictions dans le fichier restrictions
//! \param ligne                      La ligne à lire
//! \return                           Un bool pour le succès de lecture
bool Librairie::lireLigneRestrictions(const std::string& ligne)
{
    // To do
    int valeurTypeMedia;
    std::istringstream stream(ligne);
    std::string nomMedia;
    if (stream >> valeurTypeMedia >> std::quoted(nomMedia))
    {
        auto typeMedia = static_cast<Media::TypeMedia>(valeurTypeMedia);
        Media* media = chercherMedia(nomMedia, typeMedia);
        if (media == nullptr)
        {
            return false;
        }

        int paysValeurEnum;
        while (stream >> paysValeurEnum)
        {
            media->ajouterPaysRestreint(to_enum<Pays>(paysValeurEnum));
        }
        return true;
    }
    return false;
}

// To do
//!  Méthode pour lire une ligne de médias
//! \param ligne                      La ligne à lire
//! \param gestionnaireAuteurs        Le gestionnaire des auteurs
//! \return                           Un bool pour le succès de lecture
bool Librairie::lireLigneMedia(const std::string& ligne, GestionnaireAuteurs& gestionnaireAuteurs)
{
    lireLigneMediaFunction fonctionLireligne[] = {&Librairie::lireLigneFilm,
                                                  &Librairie::lireLigneSerie,
                                                  &Librairie::lireLigneSaison,
                                                  &Librairie::lireLigneEpisode};
    std::istringstream stream(ligne);
    int typeMediaValeurEnum;

    if (stream >> typeMediaValeurEnum)
        return invoke(fonctionLireligne[typeMediaValeurEnum], *this, stream, gestionnaireAuteurs);

    return false;
}

// To do
//!  Méthode qui retourne le vecteur de medias de la librairie
//! \return                           le vecteur de medias
const std::vector<std::unique_ptr<Media>>& Librairie::getMedias() const
{
    // To do
    return medias_;
}

// To do
//!  Méthode pour lire une ligne d'épisode
//! \param is                         Le stream duquel lire l'épisode
//! \return                           Un bool pour le succès de lecture
bool Librairie::lireLigneEpisode(std::istream& is, GestionnaireAuteurs&)
{
    // To do
    Episode episode;
    std::string nomSerie;
    int numSaison;
    if (!(is >> episode >> std::quoted(nomSerie) >> numSaison))
    {
        return false;
    }
    ajouterEpisode(nomSerie, numSaison, std::make_unique<Episode>(episode));
    return true;
}

// To do
//!  Méthode pour lire une ligne de Saison
//! \param is                         Le stream duquel lire la saison
//! \return                           Un bool pour le succès de lecture
bool Librairie::lireLigneSaison(std::istream& is, GestionnaireAuteurs&)
{
    // To do
    Saison saison;
    auto ptrSaison = std::make_unique<Saison>(saison);
    std::string nomSerie;
    if (!(is >> *ptrSaison >> std::quoted(nomSerie)))
    {
        return false;
    }
    ajouterSaison(nomSerie, std::move(ptrSaison)); 
    return true;
}

// To do
//!  Méthode pour lire une ligne de serie
//! \param is                         Le stream duquel lire la serie
//! \return                           Un bool pour le succès de lecture
bool Librairie::lireLigneSerie(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::string nomAuteur;
    if (!(is >> std::quoted(nomAuteur)))
    {
        return false;
    }
    Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
    Serie serie(auteur);
    if (!(is >> serie))
    {
        return false;
    }
    auteur->setNbMedias(auteur->getNbMedias() + 1);
    *this += std::make_unique<Serie>(serie);
    return true;
}

// To do
//!  Méthode pour lire une ligne de film
//! \param is                         Le stream duquel lire le film
//! \return                           Un bool pour le succès de lecture
bool Librairie::lireLigneFilm(std::istream& is, GestionnaireAuteurs& gestionnaireAuteurs)
{
    // To do
    std::string nomAuteur, duree;
    if (!(is >> std::quoted(nomAuteur)))
    {
        return false;
    }
    Auteur* auteur = gestionnaireAuteurs.chercherAuteur(nomAuteur);
    Film film(auteur);
    if (!(film.lire(is)))
    {
        return false;
    }
    auteur->setNbMedias(auteur->getNbMedias() + 1);
    *this += std::make_unique<Film>(film);
    return true;
}

// To do
//!  Méthode d'accès qui retourne le nombre de films dans la librairie
//! \return                           Le nombre de films
size_t Librairie::getNbFilms() const
{
    // To do
    int nbFilms = 0;
    for (int i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Film)
        {
            nbFilms++;
        }
    }
    return nbFilms;
}

// To do
//!  Méthode d'accès qui retourne le nombre de series dans la librairie
//! \return                           Le nombre de series
size_t Librairie::getNbSeries() const
{
    // To do
    int nbSeries = 0;
    for (int i = 0; i < medias_.size(); i++)
    {
        if (medias_[i]->getTypeMedia() == Media::TypeMedia::Serie)
        {
            nbSeries++;
        }
    }
    return nbSeries;
}

// To do
//!  Méthode d'accès qui retourne le nombre de saisons d'une série
//! \param nomSerie                   Le nom de la série
//! \return                           Le nombre de saisons dans la serie
size_t Librairie::getNbSaisons(const std::string& nomSerie) const
{
    // To do
    int indexSerie = trouverIndexMedia(nomSerie);
    Serie* serie = dynamic_cast<Serie*>((medias_[indexSerie]).get());
    return serie->getNbSaisons();
}

// To do
//!  Méthode d'accès qui retourne le nombre de d'épisodes d'une saison d'une série
//! \param nomSerie                   Le nom de la série
//! \param numSaison                  Le numéro de la saison
//! \return                           Le nombre de d'épisodes de la saison dans la serie
size_t Librairie::getNbEpisodes(const std::string& nomSerie, const unsigned int numSaison) const
{
    // To do
    int indexSerie = trouverIndexMedia(nomSerie);
    return dynamic_cast<Serie*>((medias_[indexSerie]).get())->getSaison(numSaison)->getNbEpisodes();
}
