#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FAUX = 0, VRAI = 1 } Booleen;
Booleen EchoActif = FAUX;

// Messages emis par les instructions -----------------------------------------
#define MSG_INTERRUPTION "## fin de programme"

// Lexemes --------------------------------------------------------------------
#define LGMOT 35
#define NBCHIFFREMAX 5
typedef char Mot[LGMOT + 1];

void get_id(Mot id) {
    scanf("%s", id);
    if (EchoActif) printf(">>echo %s\n", id);
}
int get_int() {
    char buffer[NBCHIFFREMAX + 1];
    scanf("%s", buffer);
    if (EchoActif) printf(">>echo %s\n", buffer);
    return atoi(buffer);
}

// DONNEES ---------------------------------------------------------------

// Specialites
#define MAX_SPECIALITES 10

typedef struct {
    Mot nom;
    int cout_horaire;
} Specialite;

typedef struct {
    Specialite tab_specialites[MAX_SPECIALITES];
    unsigned int nb_specialites;
} Specialites;

// Travailleurs
#define MAX_TRAVAILLEURS 50

typedef struct {
    Mot nom;
    Booleen tags_competences[MAX_SPECIALITES];
    unsigned int nb_heures_restantes;
} Travailleur;

typedef struct {
    Travailleur tab_travailleurs[MAX_TRAVAILLEURS];
    unsigned int nb_travailleurs;
} Travailleurs;

// Client
#define MAX_CLIENTS 10

typedef struct {
    Mot tab_clients[MAX_CLIENTS];
    unsigned int nb_clients;
} Clients;

// Commande
#define MAX_COMMANDES 500

typedef struct {
    unsigned int nb_heures_requises;
    unsigned int nb_heures_effectuees;
    unsigned int travailleur_st;
}Tache;
typedef struct {
    Mot nom;
    unsigned int idx_client;
    Tache taches_spe[MAX_SPECIALITES];
}Commande;
typedef struct {
    Commande tab_commandes[MAX_COMMANDES];
    unsigned int nb_commandes;
}Commandes;


// Instructions ---------------------------------------------------------------
// Developpe
// Fonction qui prend en paramètre la structure tabSpecialites de type Specialites
void traite_developpe(Specialites* tabSpecialites) {

    Mot nom_specialite;
    get_id(nom_specialite);
    int cout_horaire = get_int();
    if (tabSpecialites->nb_specialites < MAX_SPECIALITES)
    {
        strcpy(tabSpecialites->tab_specialites[tabSpecialites->nb_specialites].nom, nom_specialite);
        tabSpecialites->tab_specialites[tabSpecialites->nb_specialites].cout_horaire = cout_horaire;
        tabSpecialites->nb_specialites += 1;
    }
    else
    {
        printf("Le nombre de specialite a atteint son maximum");
    }
}

// Interruption
void traite_interruption() {
    printf(MSG_INTERRUPTION);
}

// Embauche
/*
 * Cette fonction sert à s'occuper des différentes embauches pour les
 * travailleurs,
 * afin d'embaucher ces derniers de manière conveable selon s'ils ont déjà été
 * embauché ou non
 * */
void traite_embauche(Specialites tabSpecialites, Travailleurs* tabTravail) {
    Mot nom_travailleur, nom_competence;
    get_id(nom_travailleur);
    get_id(nom_competence);
    for (int count = 0; count < MAX_TRAVAILLEURS; ++count)
    {
        if (strcmp(nom_travailleur, tabTravail->tab_travailleurs[count].nom) == 0)
        {
            int i;
            for (i = 0; i < tabSpecialites.nb_specialites; ++i)
            {
                if (strcmp(nom_competence, tabSpecialites.tab_specialites[i].nom) == 0)
                {
                    tabTravail->tab_travailleurs[count].tags_competences[i] = VRAI;
                    return;
                }
            }

        }
    }
    strcpy(tabTravail->tab_travailleurs[tabTravail->nb_travailleurs].nom,
           nom_travailleur);
    tabTravail->tab_travailleurs[tabTravail->nb_travailleurs].nb_heures_restantes = 0;
    for (int count = 0; count < MAX_SPECIALITES; ++count)
    {
        tabTravail->tab_travailleurs[tabTravail->nb_travailleurs].
        tags_competences[count] = FAUX;
    }
    for (int i = 0; i < tabSpecialites.nb_specialites; ++i)
    {
        if (strcmp(nom_competence, tabSpecialites.tab_specialites[i].nom) == 0)
        {
            tabTravail->tab_travailleurs[tabTravail->nb_travailleurs].
            tags_competences[i] = VRAI;
            break;
        }
    }
    tabTravail->nb_travailleurs += 1;

}

// Demarche
/*
 * Cette fonction prend comme paramètre la structure clientele de type Clients,
 * elle sert à donner à la variable nom_nouveau_client le nom du client
 * donné dans le Input du programme, que l'on retrouve dans
 * clientele->tab_clients[clientele->nb_clients] */
void traite_demarche(Clients* clientele) {
    Mot nom_nouveau_client;
    get_id(nom_nouveau_client);
    strcpy(clientele->tab_clients[clientele->nb_clients], nom_nouveau_client);
    clientele->nb_clients += 1;
}

// Commande
void traite_commande(Clients clientele, Commandes* tabCommande) {
    Mot nom_commande, nom_client_cmd;
    get_id(nom_commande);
    get_id(nom_client_cmd);
    for (int i = 0; i < MAX_SPECIALITES; ++i)
    {
        tabCommande->tab_commandes[tabCommande->nb_commandes].
        taches_spe[i].nb_heures_requises = 0;
        tabCommande->tab_commandes[tabCommande->nb_commandes].
        taches_spe[i].nb_heures_effectuees = 0;
    }
    for (int count = 0; count < MAX_CLIENTS; ++count)
    {
        if (strcmp(nom_client_cmd, clientele.tab_clients[count]) == 0)
        {
            strcpy(tabCommande->tab_commandes[tabCommande->nb_commandes].nom,
                   nom_commande);
            tabCommande->tab_commandes[tabCommande->nb_commandes].idx_client
            = count;
            tabCommande->nb_commandes += 1;
            break;
        }
    }
}

// Tache
void traite_tache(Specialites tabSpecialites, Commandes* tabCommande,
                  Travailleurs* tabTravail) {
    Mot nom_tache, nom_specialite;
    get_id(nom_tache);
    get_id(nom_specialite);
    int nb_heure = get_int();
    int sp = 0;
    int cm = 0;
    int count = 0;
    int j = count;
    unsigned int travailleur_st = 0;
    unsigned int min_heure_travail = 0;

    while (sp < tabSpecialites.nb_specialites)
    {
        if (strcmp(tabSpecialites.tab_specialites[sp].nom, nom_specialite) == 0)
        {
            break;
        }
        ++sp;
    }
    while (cm < tabCommande->nb_commandes)
    {
        if (strcmp(tabCommande->tab_commandes[cm].nom, nom_tache) == 0)
        {
            tabCommande->tab_commandes[cm].taches_spe[sp].nb_heures_requises =
                    nb_heure;
            break;
        }
        ++cm;
    }
    while (count < tabTravail->nb_travailleurs - 1)
    {
        if (tabTravail->tab_travailleurs[count].tags_competences[sp] == VRAI)
        {
            min_heure_travail = tabTravail->tab_travailleurs[count].
                    nb_heures_restantes;
            break;
        }
        ++count;
    }
    while (j < tabTravail->nb_travailleurs)
    {
        if (tabTravail->tab_travailleurs[j].tags_competences[sp] == VRAI)
        {
            if (tabTravail->tab_travailleurs[j].nb_heures_restantes <
            min_heure_travail)
            {
                min_heure_travail = tabTravail->tab_travailleurs[j].
                        nb_heures_restantes;
                travailleur_st = j;
            }
        }
        ++j;
    }
    tabCommande->tab_commandes[cm].taches_spe[sp].travailleur_st =
            travailleur_st;
    tabTravail->tab_travailleurs[travailleur_st].nb_heures_restantes += nb_heure;

}

// Progression
void traite_progression(Specialites tabSpecialites, Commandes* tabCommande,
                        Travailleurs* tabTravail) {
    Mot progression_cm, progression_spe;
    get_id(progression_cm);
    get_id(progression_spe);
    int nb_heure_realise = get_int();
    int count = 0;
    int i = 0;

    while (count < tabSpecialites.nb_specialites)
    {
        if (strcmp(tabSpecialites.tab_specialites[count].nom,
                   progression_spe) == 0)
        {
            break;
        }
        ++count;
    }

    while (i < tabCommande->nb_commandes)
    {
        if (strcmp(tabCommande->tab_commandes[i].nom, progression_cm) == 0)
        {
            tabCommande->tab_commandes[i].taches_spe[count].
            nb_heures_effectuees += nb_heure_realise;
            tabTravail->tab_travailleurs[tabCommande->tab_commandes[i].
            taches_spe[count].travailleur_st].nb_heures_restantes -= nb_heure_realise;
        }
        ++i;
    }
}
// Progression Passe
void traite_progression_passe() {
}
// Specialites
void traite_specialites(Specialites tabSpecialites) {
    printf("specialites traitees : ");
    unsigned int count = 0;
    for (; count < tabSpecialites.nb_specialites; ++count)
    {
        if (count == tabSpecialites.nb_specialites - 1)
            printf("%s/%d\n", tabSpecialites.tab_specialites[count].nom,
                   tabSpecialites.tab_specialites[count].cout_horaire);
        else
            printf("%s/%d, ", tabSpecialites.tab_specialites[count].nom,
                   tabSpecialites.tab_specialites[count].cout_horaire);
    }
}

// Travailleurs
/*
 * Ctte fonction sert à assigner chaque travailleurs à leur spécialité
 * */
void traite_travailleurs(Specialites tabSpecialites, Travailleurs* toutTravailleur) {
    Mot travailleur_diff;
    get_id(travailleur_diff);

    if (strcmp(travailleur_diff, "tous") == 0)
    {
        for (int count = 0; count < tabSpecialites.nb_specialites; ++count)
        {
            int k = 0;
            printf("la specialite %s peut etre prise en charge par : ",
                   tabSpecialites.tab_specialites[count].nom);
            for (int i = 0; i < toutTravailleur->nb_travailleurs; ++i)
            {
                if (toutTravailleur->tab_travailleurs[i]
                .tags_competences[count] == VRAI)
                {
                    if (k == 0)
                    {
                        printf("%s", toutTravailleur->tab_travailleurs[i].nom);
                        k += 1;
                    }
                    else if (k > 0 && k < toutTravailleur->nb_travailleurs)
                    {
                        printf(", %s", toutTravailleur->tab_travailleurs[i].nom);
                        k += 1;
                    }
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("la specialite %s peut etre prise en charge par : ",
               travailleur_diff);
        int i;
        int virgule = 0;
        for (i = 0; i < tabSpecialites.nb_specialites; ++i)
        {
            if (strcmp(travailleur_diff, tabSpecialites.tab_specialites[i].nom)
            == 0)
            {
                break;
            }
        }
        for (int count = 0; count < toutTravailleur->nb_travailleurs; ++count)
        {
            if (toutTravailleur->tab_travailleurs[count].tags_competences[i] ==
            VRAI)
            {
               if (virgule == 0)
                {
                     printf("%s", toutTravailleur->tab_travailleurs[count].nom);
                    virgule += 1;
                }
                else if(virgule > 0)
                {
                    printf(", %s", toutTravailleur->tab_travailleurs[count].nom);
                    virgule += 1;
                }
            }

        }
        printf("\n");
    }
}

// Client
/*
 * Cette fonction répoertorie les commandes des clients
 * */
void traite_client(Clients clientele, Commandes* tabCommande) {
    Mot nom_client;
    get_id(nom_client);

    if (strcmp(nom_client, "tous") == 0)
    {
        for (unsigned int count = 0; count < clientele.nb_clients; ++count)
        {
            printf("le client %s a commande : ", clientele.tab_clients[count]);
            int virgule = 0;
            for (unsigned int i = 0; i < tabCommande->nb_commandes; ++i)
            {
                if (tabCommande->tab_commandes[i].idx_client == count)
                {
                    if (virgule == 0)
                    {
                        printf("%s", tabCommande->tab_commandes[i].nom);
                        virgule += 1;
                    }
                    else if (virgule > 0)
                    {
                        printf(", %s", tabCommande->tab_commandes[i].nom);
                        virgule += 1;
                    }
                }
            }
            printf("\n");
        }
    }
    else
    {
        printf("le client %s a commande : ", nom_client);
        int v = 0;
        int count;
        for(count = 0; count < clientele.nb_clients; count++) {
            if (strcmp(nom_client, clientele.tab_clients[count]) == 0) {
                for (unsigned int i = 0; i < tabCommande->nb_commandes; ++i) {
                    if (tabCommande->tab_commandes[i].idx_client == count) {
                        if (v == 0) {
                            printf("%s", tabCommande->tab_commandes[i].nom);
                            v += 1;
                        } else if (v > 0) {
                            printf(", %s", tabCommande->tab_commandes[i].nom);
                            v += 1;
                        }
                    }
                }
                printf("\n");
            }
        }
    }
}

// Supervision
/*Cette commande répertorie l'état des tâches selon la commande effectué,
 * le nombre d'heure effectué ou requise et la spécialité.
 * */
void traite_supervision(Commandes tabCommande, Specialites tabSpecialites) {

    for (unsigned int count = 0; count < tabCommande.nb_commandes; ++count)
    {
        int cpt = 0;
        if (tabCommande.nb_commandes != 0)
        {
            printf("etat des taches pour %s : ", tabCommande.
            tab_commandes[count].nom);
            for (int i = 0; i < MAX_SPECIALITES; ++i)
            {
                if (tabCommande.tab_commandes[count].taches_spe[i].
                nb_heures_requises != 0 && cpt > 0)
                {
                    printf(", %s:%d/%d", tabSpecialites.tab_specialites[i].nom,
                           tabCommande.tab_commandes[count].taches_spe[i].
                           nb_heures_effectuees,
                           tabCommande.tab_commandes[count].taches_spe[i]
                           .nb_heures_requises);
                    cpt += 1;
                }
                else if (tabCommande.tab_commandes[count].taches_spe[i].nb_heures_requises != 0 && cpt == 0)
                {
                    printf("%s:%d/%d", tabSpecialites.tab_specialites[i].nom,
                           tabCommande.tab_commandes[count].taches_spe[i].
                           nb_heures_effectuees,
                           tabCommande.tab_commandes[count].taches_spe[i].
                           nb_heures_requises);
                    cpt += 1;
                }
            }
            printf("\n");
        }
    }
}
// Charge
/*
 * Cette fonction permet de savoir la charge de travail effectué par le travailleur,
 * elle prend donc en paramètre la spécialité, la commande effectué et le travailleur.
 *
 * */
void traite_charge(Specialites tabSpecialites, Commandes* tabCommande,
                   Travailleurs* tabTravail) {

    Mot charge_travail;
    get_id(charge_travail);
    int j;
    for (j = 0; j < tabTravail->nb_travailleurs; ++j)
    {
        if (strcmp(tabTravail->tab_travailleurs[j].nom, charge_travail) == 0)
        {
            break;
        }
    }
    int v = 0;
    printf("charge de travail pour %s : ", tabTravail->tab_travailleurs[j].nom);
    for (int i = 0; i < tabCommande->nb_commandes; ++i)
    {
        for (int k = 0; k < tabSpecialites.nb_specialites; ++k)
        {
            if (tabCommande->tab_commandes[i].taches_spe[k].travailleur_st == j) {
                if ((tabCommande->tab_commandes[i].taches_spe[k].nb_heures_requises -
                     tabCommande->tab_commandes[i].taches_spe[k].
                     nb_heures_effectuees) != 0) {
                    if (v == 0) {
                        printf("%s/%s/%dheure(s)", tabCommande->tab_commandes[i].nom,
                               tabSpecialites.tab_specialites[k].nom,
                               (tabCommande->tab_commandes[i].taches_spe[k].
                               nb_heures_requises -
                                tabCommande->tab_commandes[i].taches_spe[k].
                                nb_heures_effectuees));
                    }
                    else if (v > 0) {
                        printf(", %s/%s/%dheure(s)",
                               tabCommande->tab_commandes[i].nom,
                               tabSpecialites.tab_specialites[k].nom,
                               (tabCommande->
                               tab_commandes[i].taches_spe[k].nb_heures_requises -
                                tabCommande->tab_commandes[i].taches_spe[k].
                                nb_heures_effectuees));
                    }
                    v += 1;
                }
            }
        }
    }
    printf("\n");
}

//Boucle principale ----------------------------------------------------------
int main(int argc, char* argv[])
{
    /*
     * Initialisation des différentes variables nécessaires dans l'ensemble du code,
     * à savoir des variables que l'on va utiliser dans différentes fonctions .
     * */
    Specialites tabSpecialites;
    tabSpecialites.nb_specialites = 0;
    Clients clientele;
    clientele.nb_clients = 0;
    Travailleurs nouveau_travailleur;
    nouveau_travailleur.nb_travailleurs = 0;
    Commandes tabCommande;
    tabCommande.nb_commandes = 0;
    tabCommande.tab_commandes->idx_client = 501;

    if (argc >= 2 && strcmp("echo", argv[1]) == 0) {
        EchoActif = VRAI;
    }
    Mot buffer;
    /*
     * Forêt de "if" pour naviguer d'une fonction à une autre selon l'input donné.
     * */
    while (VRAI) {
        get_id(buffer);
        if (strcmp(buffer, "developpe") == 0) {
            traite_developpe(&tabSpecialites);
            continue;
        }
        if (strcmp(buffer, "interruption") == 0) {
            traite_interruption();
            break;
        }
        if (strcmp(buffer, "embauche") == 0) {
            traite_embauche(tabSpecialites, &nouveau_travailleur);
            continue;
        }
        if (strcmp(buffer, "demarche") == 0) {
            traite_demarche(&clientele);
            continue;
        }
        if (strcmp(buffer, "commande") == 0) {
            traite_commande(clientele, &tabCommande);
            continue;
        }
        if (strcmp(buffer, "tache") == 0) {
            traite_tache(tabSpecialites, &tabCommande, &nouveau_travailleur);
            continue;
        }
        if (strcmp(buffer, "progression") == 0) {
            traite_progression(tabSpecialites, &tabCommande, &nouveau_travailleur);
            continue;
        }
        if (strcmp(buffer, "passe") == 0) {
            traite_progression_passe();
            continue;
        }
        if (strcmp(buffer, "specialites") == 0) {
            traite_specialites(tabSpecialites);
            continue;
        }
        if (strcmp(buffer, "travailleurs") == 0) {
            traite_travailleurs(tabSpecialites, &nouveau_travailleur);
            continue;
        }
        if (strcmp(buffer, "client") == 0) {
            traite_client(clientele, &tabCommande);
            continue;
        }
        if (strcmp(buffer, "supervision") == 0) {
            traite_supervision(tabCommande, tabSpecialites);
            continue;
        }
        if (strcmp(buffer, "charge") == 0) {
            traite_charge(tabSpecialites, &tabCommande, &nouveau_travailleur);
            continue;
        }
        printf("!!! instruction inconnue >%s< !!!\n", buffer);
        return 0;
    }
}