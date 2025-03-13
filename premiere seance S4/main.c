#include <stdio.h>
#include <stdlib.h>

typedef struct Noeud {
    int data;
    struct Noeud *suiv;
} Noeud;

Noeud* Cree(int valeur)
{

    Noeud* NewE=(Noeud*)malloc(sizeof(Noeud));

    if (NewE==NULL){
        printf("Erreur allocation memoire");
        exit(1);
    }
    NewE->data = valeur;
    NewE->suiv = NULL;
    return NewE;
}

void Affiche(Noeud* debut)
{
    Noeud* tmp=debut;
    while (tmp!=NULL) {
        printf("%d->", tmp->data);
        tmp=tmp->suiv;
    }
    printf("NULL\n");
}

Noeud* ajoutD(Noeud* debut, int valeur)
{
    Noeud* NewE=Cree(valeur);

    if(debut==NULL)
    {
        debut=NewE;
    }else{
        NewE->suiv=debut;
        debut=NewE;
    }
    return debut;
}

Noeud* ajoutF(Noeud* debut, int valeur)
{
    Noeud* NewE = Cree(valeur);
    if (debut == NULL) {
        debut = NewE;
    } else {
        Noeud* tmp=debut;
        while (tmp->suiv!=NULL)
        {
            tmp =tmp->suiv;
        }
        tmp->suiv=NewE;
    }
    return debut;
}

int Taille(Noeud* debut)
{
    int count=0;
    Noeud* tmp=debut;

    while (tmp!=NULL)
    {
        count++;
        tmp=tmp->suiv;
    }
    return count;
}

Noeud* insertion(Noeud* debut, int pos, int valeur) {
    int size = Taille(debut); // Corrected from 'taille' to 'Taille'
    Noeud* NewE = Cree(valeur);

    if (pos < 1 || pos > size + 1) {
        printf("position introuvable!");
        return debut; // Added return to avoid undefined behavior
    }

    if (pos == 1) {
        NewE->suiv = debut;
        debut = NewE;
        return debut;
    } else {
        Noeud* tmp = debut;
        for (int i = 1; tmp != NULL && i < pos - 1; i++) {
            tmp = tmp->suiv;
        }
        NewE->suiv = tmp->suiv;
        tmp->suiv = NewE;
    }
    return debut;
}

void rechercher(Noeud* debut, int valeur) {
    int c = 0;
    Noeud* temp = debut;
    while (temp != NULL) {
        if (temp->data == valeur) {
            c = 1;
            break;
        }
        temp = temp->suiv;
    }
    if (c == 1) {
        printf("Valeur trouvable\n");
    } else {
        printf("valeur introuvable\n");
    }
}

Noeud* SuppressionD(Noeud* debut) {
    if (debut != NULL) {
        Noeud* temp = debut;
        debut = debut->suiv;
        free(temp);
    }
    return debut;
}

Noeud* SupprimF(Noeud* debut) {
    if (debut != NULL) {
        if (debut->suiv == NULL) {
            free(debut);
            debut = NULL;
        } else {
            Noeud* temp = debut;
            Noeud* prec = NULL;
            while (temp->suiv != NULL) {
                prec = temp;
                temp = temp->suiv;
            }
            prec->suiv = NULL;
            free(temp);
        }
    }
    return debut;
}

Noeud* SuppressionP(Noeud* debut, int pos) {
    int taille = Taille(debut);
    if (debut != NULL) {
        if (pos < 1 || pos > taille) {
            printf("Position invalide\n");
            return debut;
        }

        Noeud* temp = debut;
        if (pos == 1) { // position lwla
            debut = debut->suiv;
            free(temp);
            return debut;
        }

        Noeud* prec = NULL;
        for (int i = 1; temp != NULL && i < pos; i++) { // sinon
            prec = temp;
            temp = temp->suiv;
        }
        prec->suiv = temp->suiv;
        free(temp);
    }
    return debut;
}

Noeud* modifierD(Noeud* debut, int valeur) {
    if (debut != NULL) {
        Noeud* temp = debut;
        while (temp != NULL) {
            if (temp->data == valeur) {
                printf("Nouvelle valeur pour %d:", valeur);
                int NV;
                scanf("%d", &NV);
                temp->data = NV;
                break;
            }
            temp=temp->suiv;
        }
    }
    return debut;
}

Noeud* modifierF(Noeud* debut, int valeur)
 {
    if (debut==NULL) {
        printf("La liste est vide.\n");
        return debut;
    }

    Noeud* temp=debut;
    while (temp->suiv!=NULL) {
        temp=temp->suiv;
    }

    temp->data=valeur;
    return debut;
}

Noeud* modifierP(Noeud* debut, int pos, int valeur)
 {
    if (debut==NULL) {
        printf("La liste est vide.\n");
        return debut;
    }

    Noeud* temp = debut;
    int i=1;
    while (temp!=NULL && i<pos) {
        temp = temp->suiv;
        i++;
    }

    if (temp==NULL) {
        printf("Position invalide.\n");
    } else {
        temp->data = valeur;
    }

    return debut;
}

int main()
{

    Noeud* debut = NULL;
    debut = ajoutF(debut, 10);
    debut = ajoutF(debut, 20);
    debut = ajoutF(debut, 30);

    printf("Liste initiale :\n");
    Affiche(debut);

    printf("\n Taille de la liste : %d\n",Taille(debut));
    printf("\n Modification de la premiere valeur (nouvelle valeur:7)\n");
    debut = modifierD(debut,10);
    Affiche(debut);

    printf("\n Modification de la valeur a la position 2(nouvelle valeur:150)\n");
    debut = modifierP(debut,2,150);
    Affiche(debut);

    printf("\n Modification de la derniere valeur (nouvelle valeur :24)\n");
    debut = modifierF(debut,24);
    Affiche(debut);

    printf("\n Ajout de la valeur 40 en fin de liste\n");
    debut=ajoutF(debut, 40);
    Affiche(debut);

    printf("\n Insertion de la valeur 9 a la position 3\n");
    debut=insertion(debut,3,9);
    Affiche(debut);

    printf("\n Suppression de l'element a la position 4\n");
    debut=SuppressionP(debut, 4);
    Affiche(debut);

    int valeurR = 50;
    rechercher(debut, valeurR);

    return 0;
}
