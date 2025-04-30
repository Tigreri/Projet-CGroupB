#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
int nb_client=0;

struct Parking{
char identifiant [100];
char Nom[100];
char Adresse[100];
char Ville[100];
char Etat[100];
int Place_disponible;
int capacite_max;
char date_de_mise_a_jour[100];
char affichage_panneaux[100];
};

struct Parking liste[100];

struct Client{
    char Immatriculation [100];
    int Montant_paye;
    time_t heure_entrer;
    time_t heure_sorti;
    };
    
struct Client listeInfo[1000];


int afficheParking(char identifiant_try[100], int compteur){
    int check=0;
    for (int i =0;i< compteur;i++){
        if (strcmp(liste[i].identifiant,identifiant_try)==0){
            printf("%s\n",liste[i].identifiant);
            printf("%s\n",liste[i].Nom);
            printf("%s\n",liste[i].Adresse);
            printf("%s\n",liste[i].Ville);
            printf("%s\n",liste[i].Etat);
            printf("%d\n",liste[i].Place_disponible);
            printf("%d\n",liste[i].capacite_max);
            printf("%s\n",liste[i].date_de_mise_a_jour);
            printf("%s\n",liste[i].affichage_panneaux);
            printf("--------------------------\n");
            check = 50;
        }
    }
    if (check == 0){
        printf("identifiant non trouvé");
        return 0;
    } 
    return 1;
}

void afficheParkings( int compteur){
    for (int i =0;i< compteur;i++){
        /*printf("%s\n",liste[i].identifiant);
        printf("%s\n",liste[i].Nom);
        printf("%s\n",liste[i].Adresse);
        printf("%s\n",liste[i].Ville);
        printf("%s\n",liste[i].Etat);
        printf("%d\n",liste[i].Place_disponible);
        printf("%d\n",liste[i].capacite_max);
        printf("%s\n",liste[i].date_de_mise_a_jour);
        printf("%s\n",liste[i].affichage_panneaux);
        printf("--------------------------\n");*/
    }
}

void afficheclient(){
    for (int i =0;i< nb_client;i++){
        printf("%s\n",listeInfo[i].Immatriculation);
        printf("%d\n",listeInfo[i].Montant_paye);
        printf("%time_t\n",listeInfo[i].heure_entrer);
        printf("%time_t\n",listeInfo[i].heure_sorti);
        printf("--------------------------\n");
    }
}

int lesparkings(){
    // Ouverture du fichier source
    FILE *fichier = fopen("parking-metropole (2).csv","r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture. ");
        return -1;
    }
    char ligne[1000];
    int i=0;
    fgets(ligne, sizeof(ligne), fichier);
    while (fgets(ligne, sizeof(ligne), fichier)) { // Lire une ligne
        //printf("%s", ligne);
        const char * separators = ";"; //separations des tokens
 // define strToken
        strcpy(liste[i].identifiant, strtok ( ligne, separators ));
        strcpy(liste[i].Nom , strtok ( NULL, separators ));
        strcpy(liste[i].Adresse , strtok ( NULL, separators ));
        strcpy(liste[i].Ville , strtok ( NULL, separators ));
        strcpy(liste[i].Etat , strtok ( NULL, separators ));
        liste[i].Place_disponible = atoi(strtok ( NULL, separators ));
        liste[i].capacite_max = atoi(strtok ( NULL, separators ));
        strcpy(liste[i].date_de_mise_a_jour , strtok ( NULL, separators ));
        strcpy(liste[i].affichage_panneaux , strtok ( NULL, separators ));
        i++;
    }
    
    printf("il y a %i parking possible",i);
    fclose(fichier);
    return i;

}

int entrerParking(char identifiant_donne[100],int compteur,char immatriculation[100]){
    for (int i =0;i< compteur;i++){
        if (strcmp(liste[i].identifiant,identifiant_donne)==0){
            time_t heure_entrer = time(NULL);
            strcpy(listeInfo[nb_client].Immatriculation , immatriculation);
            listeInfo[nb_client].heure_entrer = heure_entrer;
            nb_client++;
            return heure_entrer;
        }
    }
}


int sortieParking(char identifiant_donne[100],int compteur,int date_entrer,char immatriculation[100]){
    time_t heure_sortiee = time(NULL) ;
    int montant = (heure_sortiee-date_entrer);
    for (int i =0;i< compteur;i++){
        if (strcmp(liste[i].identifiant,identifiant_donne)==0){
            for (int j=0;j<=nb_client;j++){
                if (strcmp(listeInfo[j].Immatriculation,immatriculation)==0){
                    listeInfo[j].heure_sorti=heure_sortiee;
                    listeInfo[j].Montant_paye=montant;
                    afficheclient();
                    break;
                }
            }
            printf("%d ",montant);
            return montant;
        }
    }
}



void mettreAJourOccupation(char identifiant_donne[100], int compteur, int entree){
    for (int i=0; i<compteur; i++){
        if (strcmp(liste[i].identifiant, identifiant_donne) == 0){
            if (entree == 1 && liste[i].Place_disponible > 0){
                printf("%d ",liste[i].Place_disponible);
                liste[i].Place_disponible--;
                printf("%d ",liste[i].Place_disponible);
                break;
            }
            if (entree == 0 && liste[i].Place_disponible < liste[i].capacite_max){
                printf("%d ",liste[i].Place_disponible);
                liste[i].Place_disponible++;
                printf("%d ",liste[i].Place_disponible);
                break;
            }
        }
    }
}

int modeAdministrateur(){
    char code[100];
    printf("Entrer le code admin : ");
    scanf("%s", code);
    if (strcmp(code, "admin123") == 0){
        printf("accée autorisé");
        return 1;
    } else {
        printf("Code incorrect accée interdit");
        return 0;
    }
}

int verifierPlacesDisponibles(char identifiant_donne[100], int compteur){
    for (int i=0; i<compteur; i++){
        if (strcmp(liste[i].identifiant, identifiant_donne) == 0){
            if (liste[i].Place_disponible == 0){
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1; // identifiant non trouvé
}

void sauvegarderEtatParking(int compteur){
    FILE *fichier = fopen("parking-metropole-sauvegarde.csv", "w");
    if (fichier == NULL){
        printf("Erreur d'ouverture pour sauvegarde\n");
        return;
    }
    fprintf(fichier, "identifiant;Nom;Adresse;Ville;Etat;Place_disponible;capacite_max;date_de_mise_a_jour;affichage_panneaux\n");
    for (int i=0; i<compteur; i++){
        fprintf(fichier, "%s;%s;%s;%s;%s;%d;%d;%s;%s\n",
            liste[i].identifiant,
            liste[i].Nom,
            liste[i].Adresse,
            liste[i].Ville,
            liste[i].Etat,
            liste[i].Place_disponible,
            liste[i].capacite_max,
            liste[i].date_de_mise_a_jour,
            liste[i].affichage_panneaux);
    }
    printf("copy fini ");
    fclose(fichier);
}
int verifie_plaque(char immatriculation [100],int compteur){
    int check = 1;
    
    for (int i =0;i< compteur;i++){
        for (int j=0;j<liste[i].capacite_max;j++){
            if (strcmp(listeInfo[i].Immatriculation,immatriculation)==0){
            check = 0;
            break;
            }
        }
        
    }
    if (check == 1){
        printf("enregistrement");
        return 1;
    } 
    return 0;
}
int main(){
     modeAdministrateur();
    int compteur = lesparkings();
    printf("---------------------\n");
    afficheParkings(compteur);
    int check = 0;
    int check2 =0; 
    char identifiant_donne[100];
    while(check ==0){    
    printf("Entrer un identifiant de parking : ");
    scanf("%s", identifiant_donne);
    check = afficheParking(identifiant_donne,compteur);
    }
    char immatriculation[100];
    int max =0;
    while (check2 == 0){
    printf("Entrer votre plaque : ");
    scanf("%s", immatriculation);
    check2 = verifie_plaque(immatriculation,compteur);
    max = max+ 1;
    if (max ==5){
        break;
    }
    }
    int date_entrer = entrerParking(identifiant_donne, compteur,immatriculation);
    Sleep(10000); 
    sortieParking( identifiant_donne,compteur,date_entrer,immatriculation);
    mettreAJourOccupation( identifiant_donne, compteur, 0);
    int dispo = verifierPlacesDisponibles( identifiant_donne, compteur);
    printf("%d ",dispo);
    sauvegarderEtatParking(compteur);
    

}
