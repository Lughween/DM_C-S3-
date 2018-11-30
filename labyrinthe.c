/*Labyrinthe.c*/

#include "labyrinthe.h"
#include <time.h>

typedef struct cheminPile{
  int tete;
  int queue;
  chemin_t* pile;
}cheminPile_t;
/*Premiere partie*/

int rand_a_b(int a,int b){
  return rand()%(b-a)+a;
}
//plus T est grand plus il y à d'elt non nuls si T_max = 80 (en %)
// void genererLabyrinthe(char *A,char *IA,char *JA,int lignes,int colonnes,int T){
//   IA = calloc(lignes+1,sizeof(char));
//   IA[0] = 0;
//   if(T>80)
//     T=80;
//   float ft = (float)(T/100);
//   int non_nuls = 0;
//   int nb_non_nul_col;
//   int mini;
//   for(int i=1;i<lignes;i++){
//     mini = ft*colonnes;
//     nb_non_nul_col = rand_a_b(mini,colonnes);
//     non_nuls += nb_non_nul_col; 
//     IA[i] = IA[i+1] + nb_non_nul_col; //il peut y avoir entre ft et le nombres de collones d'elt par colonnes si ft = 0.8 il y à donc 80% de la collonne non nulle; 
//   }

//   A = calloc(non_nuls,sizeof(char));
//   JA = calloc(non_nuls,sizeof(char));

//   for(int i=0;i<non_nuls;i++){ //initialisation des autres matrices
//     A[i] = 1;
//     JA[i] = rand_a_b(0,colonnes);
//   }

//   if(IA[1] == colonnes)
//     IA[1]--;
//   if(JA[0] == 0)
//     JA[0] == rand_a_b(1,colonnes);
//   int sortie = rand_a_b(0,non_nuls);
//   A[sortie] = 2;

// }


/*********************pile fifo de chemin**********************************/
void init_pile_ch(cheminPile_t *p,int largeur,int longueur){
  p->queue = -1;
  p->tete = -1;
  p->pile = malloc(largeur*longueur*sizeof(coordonnee_t));
}

char pile_vide_ch(cheminPile_t p){ //retourne 1 si vide 0 sinon
  if(p.queue == -1 || p.tete == -1)
    return 1;
  return 0;
}

chemin_t depiler_ch(cheminPile_t *p){
  if(!pile_vide(*p)){
    if(p->queue < p->tete)
      return p->pile[p->queue++];
    int q = p->queue;
    p->queue = -1;
    p->tete = -1;
    return p->pile[q];
  }
  else{
    printf("pile vide !\n");
    chemin_t c;
    c.taille = 0;
    return c;
  }
}

void empiler_ch(pileCoord_t *p,chemin_t ch){
  p->tete++;
  p->pile[p->tete] = ch;
  if(pile_vide(*p))
    p->queue = 0;
}


labyrinthe genererLabyrinthe(int lignes,int collones,int T){
  labyrinthe lab = calloc(lignes,sizeof(char*));
  for(int i=0;i<lignes;i++){
    lab[i] = calloc(collones,sizeof(char));
  }
  if(T>100)
    T = 100;
  int alea;
  srand(time(NULL));
  for(int i=0;i<lignes;i++){
    for(int j=0;j<collones;j++){
      alea = rand_a_b(0,1000);
      //printf("%d\n",alea);
      if(alea<T*10)
        lab[i][j]=1;
      else
        lab[i][j]=0;
    }
  }
  lab[0][0] = 0;
  lab[lignes-1][rand_a_b(0,collones)] = 2;
  return lab;
}

labyrinthe creerMatrice (unsigned int lignes, unsigned int colonnes, char* A, char* IA, char* JA){

  labyrinthe lab = allouerMatrice(lignes,colonnes);

  //on remplis avec des 0
  for(int i=0;i<lignes;i++){
    for(int j=0;j<colonnes;j++){
        lab[i][j] = 0;
    }
  }
  //puis on place les éléments dans la matrice
  int k=0;
  int i=0; //indice ligne 
  int nb_elt_ligne = IA[i+1] -IA[i]; // calcul du nombre d'elt sur la ligne 0;
  //printf("%d\n",nb_elt_ligne);
  while(A[k] != NULL){ //tant qu'on atteint pas la fin de A
    if(nb_elt_ligne == 0){
      i++;
      nb_elt_ligne = IA[i+1] -IA[i]; //calcul du nombre d'elt sur la ligne i
      //printf("%d\n",nb_elt_ligne);
    }else{
    lab[i][JA[k]] = A[k]; //placement de l'elt
      nb_elt_ligne--; //décrementation du nombre d'elt à traiter pour cette ligne
      k++;
    }
  }
  
  return lab;
  }

void afficherMatrice( labyrinthe lab, unsigned int lignes, unsigned int colonnes ){
  printf("\n");
  int prec = 2;
  for(int i=0;i<lignes;i++){
    for(int j=0;j<colonnes;j++){
      if(lab[i][j]==1)
        printf("\033[32m%d ",lab[i][j]);
      else if(lab[i][j]==2)
        printf("\033[35m%d ",lab[i][j]);
      else
        printf("\033[0m%d ",lab[i][j]);

    }
    printf("\033[0m\n");
  }
}

/*J'ai pris largeur pour nb de lignes et longueur pour le nb de colonnes */

int deplacementsPossibles( labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t posCourante, coordonnee_t* coordPossibles){
  if(lab[posCourante.ligne][posCourante.colonne] == 1){
    return 0;}
  int nb_possible = 0;
  coordonnee_t coord_possible;
  int l; //ligne lue
  int k; //colonne lue
  for(int i=-1;i<2;i++){
    for(int j=-1;j<2;j++){
      l = posCourante.ligne +i;
      k = posCourante.colonne +j;
      if(l >= 0 && k<longueur && k >= 0 && l<largeur /*&& i != 0 && j != 0*/){
        if(lab[l][k] == 0 || lab[l][k] == 2){
          coord_possible.colonne = k;
          coord_possible.ligne = l;
          coordPossibles[nb_possible].colonne = coord_possible.colonne;
          coordPossibles[nb_possible].ligne = coord_possible.ligne;
          nb_possible++;}
     }
    }
  }
  return nb_possible;
}

char CoordInTab(int taille,coordonnee_t coord,coordonnee_t *t){
  for(int i=0;i<taille;i++){
    if(t[i].colonne == coord.colonne && t[i].ligne == coord.ligne)
      return 1;
  }
  return 0;
}

char verifierChemin( chemin_t ch, labyrinthe lab, unsigned int largeur, unsigned int longueur, coordonnee_t depart ){
  for(int i=0;i<ch.taille-1;i++){
    coordonnee_t coordPos[8];
    int n= deplacementsPossibles(lab,largeur,longueur,ch.coordonnees[i],coordPos);
    if(CoordInTab(n,ch.coordonnees[i+1],coordPos) == 0)
      return 0;
  }
  if(ch.taille == 0)
    return 0;
  int n = ch.taille-1;
  if(lab[ch.coordonnees[n].ligne][ch.coordonnees[n].colonne] != 2) //vérifie que la dernière case est la sortie
    return 0; 
  return 1;
}

void afficherChemin( chemin_t ch ){
  for(int i=0;i<ch.taille;i++){
    printf("(%d,%d)",ch.coordonnees[i].ligne,ch.coordonnees[i].colonne);
  }
  printf("\n");
}


/*Seconde partie*/

void initMatAnnexe(labyrinthe M2,unsigned int largeur,unsigned int longueur){
  int val = largeur*longueur;
  for(int i=0;i<largeur;i++){
    for(int j=0;j<longueur;j++){
      M2[i][j] = val;
    }
  }
}

int MarquerCoords(labyrinthe M2,unsigned int largeur, unsigned int longueur,coordonnee_t *coordPossibles,int nb_possible,coordonnee_t pos){
  int nb_possible_fin = 0;
  for(int i=0;i<nb_possible;i++){
    if(M2[coordPossibles[i].ligne][coordPossibles[i].colonne] > M2[pos.ligne][pos.colonne] + 1){
      M2[coordPossibles[i].ligne][coordPossibles[i].colonne] = M2[pos.ligne][pos.colonne] + 1;
      coordPossibles[nb_possible_fin] = coordPossibles[i]; 
      nb_possible_fin++;}
  }
  return nb_possible_fin;
}

int CalculCoordPossible(labyrinthe lab,labyrinthe M2,unsigned int largeur, unsigned int longueur,coordonnee_t *coordPossibles,coordonnee_t pos){
  int nb_possible = deplacementsPossibles(lab,largeur,longueur,pos,coordPossibles);
  nb_possible = MarquerCoords(M2,largeur,longueur,coordPossibles,nb_possible,pos);
  return nb_possible;
}

void addCoordsPile(pileCoord_t *p,coordonnee_t *coords,int n){
  for(int i=0;i<n;i++){ 
    empiler(p,coords[i]);
  }
}

coordonnee_t suivre_chemin(labyrinthe M2,unsigned int largeur, unsigned int longueur,coordonnee_t pos){
  int l,k;
  coordonnee_t coord;
  for(int i=-1;i<2;i++){
    for(int j=-1;j<2;j++){
      l = pos.ligne +i;
      k = pos.colonne +j;
      if(l >= 0 && k<longueur && k >= 0 && l<largeur /*&& i != 0 && j != 0*/){
        if(M2[l][k] == M2[pos.ligne][pos.colonne] - 1){
          //printf("(%d;%d)%d(%d,%d)\n",pos.ligne,pos.colonne,M2[l][k],l,k);
          coord.colonne = k;
          coord.ligne =l;
          return coord;
         }
     }
    }
  }
}


coordonnee_t CreerM2(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  initMatAnnexe(M2,largeur,longueur);
  M2[depart.ligne][depart.colonne] = 0;
  // if(lab[depart.ligne][depart.colonne] == 1){
  //   ch.taille = 0;
  //   puts("Départ dans un mur !!!\n");
  //   return ch;
  // }
  pileCoord_t pile;
  init_pile(&pile,largeur,longueur);

  coordonnee_t pos = {depart.ligne,depart.colonne};
  coordonnee_t coordPossibles[8];
  int nb_possible = CalculCoordPossible(lab,M2,largeur,longueur,coordPossibles,pos);
  addCoordsPile(&pile,coordPossibles,nb_possible);
  while(lab[pos.ligne][pos.colonne] != 2 && !pile_vide(pile)){
    pos = depiler(&pile);
    nb_possible = CalculCoordPossible(lab,M2,largeur,longueur,coordPossibles,pos);
    addCoordsPile(&pile,coordPossibles,nb_possible);
  }
  free(pile.pile);
  return pos;
}
chemin_t plusCourtCheminDynamique (labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  chemin_t ch;
  //printf("(%d;%d)\n",pos.ligne,pos.colonne); 
  coordonnee_t pos = CreerM2(lab,M2,largeur,longueur,depart);
  if(lab[pos.ligne][pos.colonne] != 2){
    ch.taille = 0;
    ch.coordonnees = calloc(1,sizeof(coordonnee_t));
    puts("labyrinthe impossible !!");}
  else{
    ch.taille = M2[pos.ligne][pos.colonne]+1;
    ch.coordonnees = malloc(ch.taille*sizeof(coordonnee_t));
    ch.coordonnees[ch.taille-1] = pos;
   for(int i=ch.taille-2;i>=0;i--){
    pos = suivre_chemin(M2,largeur,longueur,pos);
    ch.coordonnees[i] = pos;
    }
  }
  afficherMatrice(M2,largeur,longueur);
  return ch;
}

void suivre_plusieurs_chemins(labyrinthe M2,unsigned int largeur, unsigned int longueur,coordonnee_t pos,chemin_t* chemins,){
  int l,k;
  for(int i=-1;i<2;i++){
    for(int j=-1;j<2;j++){
      l = pos.ligne +i;
      k = pos.colonne +j;
      if(l >= 0 && k<longueur && k >= 0 && l<largeur /*&& i != 0 && j != 0*/){
        if(M2[l][k] == M2[pos.ligne][pos.colonne] - 1){
          
         }
     }
    }
  }
}


chemin_t* tousPlusCourtsChemins(labyrinthe lab, labyrinthe M2, unsigned int largeur, unsigned int longueur, coordonnee_t depart){
  chemin_t *ch;
  cheminPile_t pile;
  coordonnee_t pos = CreerM2(lab,M2,largeur,longueur,depart);
  if(lab[pos.ligne][pos.colonne] != 2){ //cas où le labyrinthe est imposible
    ch = malloc(sizeof(chemin_t));
    ch->taille = 0;
    ch->coordonnees = calloc(1,sizeof(coordonnee_t));
    puts("labyrinthe impossible !!");}
  else{
    ch = malloc(sizeof(chemin_t));
    ch->taille = M2[pos.ligne][pos.colonne]+1;
    ch->coordonnees = malloc(ch.taille*sizeof(coordonnee_t)); 
    ch.coordonnees[ch.taille-1] = pos;
   for(int i=ch.taille-2;i>=0;i--){
    pos = suivre_chemin(M2,largeur,longueur,pos);
    ch.coordonnees[i] = pos;
    }
  }
  return ch;
}


/*********************pile fifo de coordonnées**********************************/
void init_pile(pileCoord_t *p,int largeur,int longueur){
  p->queue = -1;
  p->tete = -1;
  p->pile = malloc(largeur*longueur*sizeof(coordonnee_t));
}

char pile_vide(pileCoord_t p){ //retourne 1 si vide 0 sinon
  if(p.queue == -1 || p.tete == -1)
    return 1;
  return 0;
}

coordonnee_t depiler(pileCoord_t *p){
  if(!pile_vide(*p)){
    if(p->queue < p->tete)
      return p->pile[p->queue++];
    int q = p->queue;
    p->queue = -1;
    p->tete = -1;
    return p->pile[q];
  }
  else{
    printf("pile vide !\n");
    coordonnee_t c= {-1,-1};
    return c;
  }
}

void empiler(pileCoord_t *p,coordonnee_t coord){
  p->tete++;
  p->pile[p->tete] = coord;
  if(pile_vide(*p))
    p->queue = 0;
}

/******************Free****************************/

void freelab(labyrinthe lab,unsigned int largeur){
  for(int i=0;i<largeur;i++){
    free(lab[i]);
  }
  free(lab);
}


/*******************alocation***************************/
labyrinthe allouerMatrice(unsigned int lignes,unsigned int colonnes){
  labyrinthe lab;
  lab = (unsigned char**) malloc(lignes*sizeof(unsigned char*));
  for(int i=0;i<lignes;i++){
    lab[i] = (unsigned char*) malloc(colonnes*sizeof(unsigned char));
  }
  return lab;
}