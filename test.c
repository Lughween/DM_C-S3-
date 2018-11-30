#include "labyrinthe.h"
#include "test_matrices.h"

#define LIGNES 5
#define COLLONNES 5
#define TEMP 0

int main(){
  /* Tests de la création et affichage de matrices */
//   labyrinthe lab1,lab2,lab3;

//   // test1
//   lab1 = creerMatrice(4,4, testA1, testIA1, testJA1);
//   printf("\nLabyrinthe créé:");
//   afficherMatrice(lab1,4,4);
//   printf("\nMatrice attendue:");
//   printf("\n%s",strMat1());

//   //test2
//   lab2 = creerMatrice(10,10, testA2, testIA2, testJA2);
//   printf("\nLabyrinthe créé:\n");
//   afficherMatrice(lab2,10,10);
//   printf("\nMatrice attendue:");
//   printf("\n%s",strMat2());

//   //test3
//   lab3 = creerMatrice(10,10, testA3, testIA3, testJA3);
//   printf("\nLabyrinthe créé\n");
//   afficherMatrice(lab3,10,10);
//   printf("\nMatrice attendue:");
//   printf("\n%s",strMat3());

//   /* Tests de la vérification et de l'affichage des chemins */

//   coordonnee_t * coords = (coordonnee_t*) malloc(100*sizeof(coordonnee_t));
//   coordonnee_t coord;

//   coord.ligne=0;
//   coord.colonne=0;
//   coords[0]=coord;

//   coord.ligne=1;
//   coord.colonne=1;
//   coords[1]=coord;

//   coord.ligne=2;
//   coord.colonne=0;
//   coords[2]=coord;
  
//   coord.ligne=3;
//   coord.colonne=0;
//   coords[3]=coord;

  
//   chemin_t ch1;
//   ch1.coordonnees=coords;
//   ch1.taille=4;

//   coord.ligne=0;
//   coord.colonne=0;

//   printf("\nTests chemins sur la matrice:\n");
//   afficherMatrice(lab1,4,4);
//   printf("\nChemin:");
//   afficherChemin(ch1);
//   printf("\nverification chemin valide: %d", verifierChemin(ch1,lab1,4,4,coord));
//   printf("\nvaleur attendue: 1\n");
  
//   coord.colonne = 1;
//   coords[0]=coord;

//   coord.colonne = 2;
//   coords[1]=coord;
//   ch1.taille=2;

//   coord.colonne = 0;
//   printf("\nChemin:");
//   afficherChemin(ch1);
//   printf("\nverification chemin, 1ere coordonnee: %d", verifierChemin(ch1,lab1,4,4,coord));
//   printf("\nvaleur attendue: 0\n");

//   coords[0]=coord;

//   coord.colonne =2;
//   coords[1]=coord;
//   ch1.taille=2;

//   coord.colonne=0;
//   printf("\nChemin:");
//   afficherChemin(ch1);
//   printf("\nverification chemin, coordonnees non adjacentes: %d", verifierChemin(ch1,lab1,4,4,coord));
//   printf("\nvaleur attendue: 0\n");

  
//   coords[0]=coord;
//   coord.ligne=1;
//   coords[1]=coord;
  
//   ch1.taille=2;

//   coord.ligne=0;
//   printf("\nChemin:");
//   afficherChemin(ch = mah1);
//   printf("\nverifch = macation chemin, mur: %d", verifierChemin(ch1,lab1,4,4,coord));
//   printf("\nvaleuch = ma attendue: 0\n");

//  /***************ch = ma******************************Test résolution labyrinthe*****************************************************/

//   printf("\n");
//   coordonnee_t dech = maart = {0,0};

//   puts("lab1\n");ch = ma
//   labyrinthe M2_1 = allouerMatrice(4,4);
//   chemin_t test = plusCourtCheminDynamique(lab1,M2_1,4,4,depart);
//   printf("chemin:");
//   afficherChemin(test);
//   printf("chemin valide : %d\n",verifierChemin(test,lab1,4,4,depart));
//   free(test.coordonnees);

//   puts("lab2\n");
//   labyrinthe M2_2 = allouerMatrice(10,10);
//   chemin_t test1 = plusCourtCheminDynamique(lab2,M2_2,10,10,depart);
//   printf("chemin:");
//   printf("chemin valide : %d\n",verifierChemin(test1,lab3,10,10,depart));
//   afficherChemin(test1);

//   puts("lab3\n");
//   labyrinthe M2_3 = allouerMatrice(10,10);
//   chemin_t test2 = plusCourtCheminDynamique(lab3,M2_3,10,10,depart);
//   printf("chemin:");
//   afficherChemin(test2);
//   printf("chemin valide : %d\n",verifierChemin(test2,lab3,10,10,depart));
//   free(test2.coordonnees);

//   freelab(lab1,4);
//   freelab(M2_1,4);
//   freelab(lab2,10);
//   freelab(M2_2,10);
//   freelab(lab3,10);
//   freelab(M2_3,10);
//   free(ch1.coordonnees);

//generation aléatoire
  coordonnee_t depart = {0,0}; 
  labyrinthe lab = genererLabyrinthe(LIGNES,COLLONNES,TEMP);
  labyrinthe M2_1 = allouerMatrice(LIGNES,COLLONNES);
  afficherMatrice(lab,LIGNES,COLLONNES);
  chemin_t test = plusCourtCheminDynamique(lab,M2_1,LIGNES,COLLONNES,depart);
  printf("chemin:");
  afficherChemin(test);
  printf("chemin valide : %d\n",verifierChemin(test,lab,LIGNES,COLLONNES,depart));
  printf("%d,%d",LIGNES,COLLONNES);
  //free(test.coordonnees);



  return 1;
}
