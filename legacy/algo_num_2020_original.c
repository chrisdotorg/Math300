/* cartouche */
/* program purpose: resolve some numerical analysis problems*/
/* program title: algo_num*/
/* author: @rich.com alias AMEDEKA Tsèvi Christian */
/* date and time: very soon*/
/* petit sommaire pour se retrouver
24 - fonctions lies aux equations non linéaires
430 - fonctions liés aux systemes lineaires
NB: A METTRE À JOUR APRES CHAQUE OPERATION EFFECTUE SUR LE CODE */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 15000
#define  pr 0.000000001

/// prototypes des fonctions utilises dans le main ///
double fun(double x);
double ptfixfun(double x);
int menu_principal();
void saisir_matrice();
void methode_de_newton();
void methode_de_la_secante();
void methode_de_la_corde_2();
void methode_de_la_corde1();
void methode_de_lagrange();
void methode_de_bissection_ou_dichotomie();
void methode_des_points_fixes();
void systemes_lineaire();
/// fonction mathematique faisant l'objet du travail ///
double fun(double x)
{
    return  x - 2*tan(x) + 1;
}
double ptfixfun(double x)
{
    // return pow(1-x,1/2);
    return 2*tan(x) -1;
}
/// fonctions de traitement ds données ///
/* methode_de_newton */
/// fonctions liés aux equations non lineaires ///

void methode_de_newton()
{
    double xo;/// valeur de depart ///
    double fo;/// image de xo///
    double *x ;/// tableau des valeurs de x pour les iterations ///
    int i ;/// indice courant ///
    double fi;/// image de xi ///
    double dfi ;///image de xi pat la derivée///
    printf("\n methode de Newton:\n");
    do
    {
        printf("\n entrez la valeur de depart:\n");
        scanf("%lf",&xo);
    }
    while(xo == 0);
    fo = fun(xo);
    if (fo == 0)
    {
        printf("\n ça c'est joli. la racine recherchée est %lf",xo);
        printf("\n easy!!!!");
    }
    else
    {
        x = malloc(n*sizeof(double));
        x[0] = xo ;
        i = 0 ;
        do
        {
            i++;
            fi = fun(x[i]);
            dfi = (fo-fi)/(xo-x[i]);
            x[i+1] = x[i] - (fi/dfi);
            printf("\n à la %d ieme itération, x =%lf",i,x[i+1]);
        }
        while(n<i||fabs(x[i+1]-x[i])>pr);
        printf("\n la solution x recherchée est %lf",x[i+1]);
        fflush(stdin);
        free(x);
    }
}
/*methode de bissection ou dichotomie */
void methode_de_bissection_ou_dichotomie()
{
    double a,b,c;
    double fa,fb,fc,fd;
    int i = 0;
    printf("Bienvenue dans l'analyse numerique\n");
    printf("\n methode de la bissection ou de dichotomie:\n");
    printf("\n entrez les bornes de l'intervalle d'étude:\n");
    scanf("%lf %lf",&a,&b);
    fa = fun(a);
    fb = fun(b);
    fd = fun((a+b)/2);
    if (fa*fb >0)
    {
        printf("\n ça c'est joli:");
        if (fa ==0 )
        {
            printf("\n la racine recherchée est %f",a);
        }
        else if (fb ==0)
        {
            printf("\n la racine recherchée est %f",b);
        }
        else if (fd ==0)
        {
            printf("\n la racine recherchée est %f",(a+b)/2);
        }
        else if(fa*fd <0 )
        {
            printf("\n il y a un nombre paire de solutions dans l'intervalle");
        }
        else if (fb*fd <0)
        {
            printf("\n il y a un nombre paire de solutions dans l'intervalle");
        }
        else
        {
            printf("\n il n' y a pas de changement de signe dans l'intervalle:\n");
        }
    }
    else
    {
        do
        {
            i++;
            c=(a+b)/2;
            if (c ==0)
            {
                printf("\n 0 est le milieu de l'intervalle\n");
                printf("\n error!!! le programme ne peut pas continuer");
            }
            else
            {
                fc = fun(c);
                if (fa*fc < 0)
                {
                    b=c;
                    printf("\n la valeur de a et b en %d itérations est %f %f",i,a,b);
                }
                else
                {
                    a = c;
                    printf("\n la valeur de a et b en %d itérations est %f %f",i,a,b);
                    // exit(EXIT_FAILURE);
                }
            }
        }
        while (fabs(b-a)>pr||i<n);
        printf("\n la racine recherchée est %.12lf",c);
        printf("\n f(c) =%f",fc);
    }
}

/* methode de lagrange*/

void methode_de_lagrange()
{
    float a,b,c,d;
    float fa,fb,fc,fd;
    int i = 0;
    printf("Bienvenue dans l'analyse numerique\n");
    printf("\n entrez les bornes de l'intervalle d'étude:\n");
    scanf("%f %f",&a,&b);
    fa = fun(a);
    fb = fun(b);
    d = a-((b-a)/(fb-fa))*fa;
    fd = fun(d);
    if (fa*fb >=0)
    {
        printf("\n ça c'est joli:");
        if (fa ==0 )
        {
            printf("\n la racine recherchée est %f",a);
        }
        else if (fb ==0)
        {
            printf("\n la racine recherchée est %f",b);
        }
        else if (fd ==0)
        {
            printf("\n la racine recherchée est %f",(a+b)/2);
        }
        else if(fa*fd <0 )
        {
            printf("\n il y a un nombre paire de solutions dans l'intervalle");
        }
        else if (fb*fd <0)
        {
            printf("\n il y a un nombre paire de solutions dans l'intervalle");
        }
        else
        {
            printf("\n il n' y a pas de changement de signe dans l'intervalle:\n");
        }
    }
    else
    {
        do
        {
            i++;
            c = a-((b-a)/(fb-fa))*fa;
            if (c ==0)
            {
                printf("\n error!!! le programme ne peut pas continuer");
            }
            else
            {
                fc = fun(c);
                if (fa*fc < 0)
                {
                    b=c;
                    printf("\n la valeur de a et b en %d itérations est %f %f",i,a,b);
                }
                else
                {
                    a = c;
                    printf("\n la valeur de a et b en %d itérations est %f %f",i,a,b);
                }
            }
        }
        while ( fabs(b-a)>pr || i<n );
        printf("\n la racine recherchée est %.12f",c);
        printf("\n f(c) =%.12f",fc);
    }
}
/* methode de la corde 1 */

void methode_de_la_corde1()
{
    double a,b;/// les bornes de l'intervalle d'etude ///
    int i ; /// indice courant ///
    double *x;
    double fa,fb; /// les images des bornes de l'intervalle d'etude ///
    printf("\nbienvenue dans ce programme. notre but est d'implementer la methode de la corde 1:\n");
    printf("\n entrez les borne de l'intervalle d'étude:\n");
    scanf("%lf %lf",&a,&b);
    x = malloc(n*sizeof(double));
    i = 0;
    //  x[0] = b;
    fa = fun(a);
    fb = fun(b);
    if (fa*fb > 0)
    {
        printf("\n il existe un nombre pair de solutions dans cet intervalle:\n");
        printf("\n la racine de l'equation n'est pas encadrée:\n");
    }
    else if (fa ==0)
    {
        printf("\n bravo!!! la racine recherchée est %lf",a);
        printf("\n \n");
    }
    else if (fb ==0)
    {
        printf("\n bravoo!!! la racine recherchée est %lf",b);
        printf("\n");
    }
    else
    {
        x[0] = a;
        printf("\n ENCADREMENT DE LA SOLUTION DE VOTRE EQUATION:\n");
        do
        {
            i++;
            x[i+1] = a-((x[i]-a)/(fun(x[i])-fa))*fa;
            printf("\n apres %d iteration, x = %.12lf",i,x[i+1]);
        }
        while (i < n || fabs(x[i+1]-x[i])>pr);
    }
}
/* methode_de_la_corde_2**/

void methode_de_la_corde_2()
{
    double xo;/// valeur de depart ///
    double fo;/// image de xo///
    double *x ;/// tableau des valeurs de x pour les iterations ///
    int i ;/// indice courant ///
    double fi;/// image de xi ///
    double dfi ;///image de xi pat la derivée///
    printf("\n methode de la corde 2:\n");
    printf("\n entrez la valeur de depart:\n");
    scanf("%lf",&xo);
    fo = fun(xo);
    x = malloc(n*sizeof(double));
    x[0] = xo ;
    i = 0 ;
    do
    {
        i++;
        fi = fun(x[i]);
        dfi = (fi-fo)/(x[i]-xo);
        x[i+1] = x[i] - (fi/dfi);
        printf("\n à la %d ieme itération, x =%lf",i,x[i+1]);
    }
    while(n<i||fabs(x[i+1]-x[i])>pr);
    free(x);
}
/* methode_de_la_secante*/
void methode_de_la_secante()
{

    double a,b;/// bornes de l'intervalle d'etude ///
    double fa,fb;/// images des bornes de l'intervalle ///
    double  *x; /// tableau des valeurs de la fonction ///
    int i ; /// indice courant ///
    printf("Hello world!\n");
    printf("\n bienvenue dans ce programme de celcul mathematique:\n");
    printf("\n ce programme traite la methode de la secante:\n");
    printf("\n entrez les bornes a et b de l'intervalle d'etude:\n ");
    scanf("%lf %lf",&a,&b);
    x = malloc(n*sizeof(double));
    fa = fun(a);
    fb = fun(b);
    x[0] = a;
    if ( fa * fb < 0)
    {
        i = 0;
        do
        {
            i++;
            x[i+1] = x[i] - ((b-x[i])/(fb-fun(x[i])))*fun(x[i]);
            if (x[i+1] ==0)
            {
                printf("\n easy!!!! le resultat recherché est %lf,",x[i+1]);
            }
            else
            {
                printf("\n à la %i ième itération , x est égal à : %lf",i,x[i+1]);
            }

            ///  printf("%f",fi1);
        }
        while(fabs((x[i+2]-x[i+1]))<=pr || i<=n);
        printf("\n le nombre recherché est %.10lf:",x[i+1]);
        printf("\n f(x) = %.10lf",fun(x[i+1]));
    }
    else
    {
        printf("\n il y a un nombre paire de solutions dans l'intervalle\n");
        printf("\n à nous revoir dans un nouveau code \n");
    }
    free(x);
}
/* methode_des_points_fixes*/
void methode_des_points_fixes()
{
    double a ; /// point de depart ///
    double *x ; /// tableau des valeurs de x
    int i,k ; /// indice courant ///
    printf("\n methode des points fixes\n");
    printf("\n entrez le points de depart pour la convergence:\n");
    scanf("%lf",&a);
    x = malloc(sizeof(double));
    x[0] = a;
    k = 0 ;
    for (i = 0 ; i<n ; i++ )
    {
        k++;
        x[i+1] = ptfixfun(x[i]);
        if (fabs(x[i+1]-x[i])< pr )
        {
            printf("\n après %d itérations, x = %lf",k,x[i+1]);
        }
        else
        {
            printf("\n après %d iterations, x = %lf",i,x[i+1]);
        }

    }
    free(x);
}
/// fonction liée à l'affichage ///

int menu_principal()
{
    unsigned int ch ; /// choix effectué par l'utilisateur ///
    do
    {
        printf("\n\t\t\t  ====== M   E   N   U =====\n");
        printf("\n\t B I E N V E N U E   D A N S   C E  P R O G R A M M E:\n");
        printf("\n nous traitons sur  des problèmes d'analyse numerique.\n");
        printf("\n faites un effort pour respecter les consignes ; c'est pour le bien de tous:\n");
        printf("\n 1 - resolution d'équations non linéaire:\n");
        printf("\n 2 - resolution des systemes lineaires:\n");
        printf("\n 3 - interpolation linéaire:\n");
        printf("\n 4 - Equations différentielles et Intégration Numérique:\n");
        printf("\n 5 - about the program\n");
        printf("\n choisissez ce que vous voulez faire:\n");
        scanf("%d",&ch);
        fflush(stdin);
        fflush(stdout);
        printf("\n ");
    }
    while(ch < 1 || ch > 5);
    return ch;

}
void systeme_non_lineaire ()
{

    int ch1;
    int ans;
    printf("\n vous voulez faire la resolution des systemes d'equation linéaire:\n");
    printf("\n n'est - ce pas?\n");
    printf("\n veuillez choisir la methode de resolution que vous voulez utiliser:\n");
    printf("\n 1 - methode de la bissection ou methode de dichotomie:\n");
    printf("\n 2 - methode de newton:\n ");
    printf("\n 3 - methode des points fixes:\n");
    printf("\n 4 - methode de lagrange:\n");
    printf("\n 5 - methode de la corde 1:\n ");
    printf("\n 6 - methode de la corde 2:\n");
    printf("\n 7 - methode de la secante:\n");
    scanf("%d",&ch1);
    switch(ch1)
    {
    case 1:
        printf("\n bisection method:\n");
        methode_de_bissection_ou_dichotomie();
        break;
    case 2:
        printf("\n vous avez choisi la methode de newton:\n");
        methode_de_newton();
        break;
    case 3:
        printf("\n vous avez choisi la methode des points fixes:\n");
        methode_des_points_fixes();
        break;
    case 4:
        printf("\n vous avez choisi la methode de Lagrange:\n");
        methode_de_lagrange();
        break;
    case 5:
        printf("\n vous avez choisi la methode de la corde 1:\n");
        methode_de_la_corde1();
        break;
    case 6:
        printf("\n vous avez choisi la methode de la corde 2:\n");
        methode_de_la_corde_2();
        break;
    case 7:
        printf("\n \t methode de la secante:\n");
        methode_de_la_secante();
        break;
    default:
        printf("\n vous n'avez choisi aucune methode de resolution:\n");
        printf("\n 0 : menu principal:\n");
        printf("\n si non appuyez n'importe quelle touche pour quitter:\n");
        scanf("%d",&ans);
        if (ans == 0)
        {
            menu_principal();
        }
        else
        {
            printf("\n vous avez quittté :\n");
        }
        printf("\n ");
    }
}
/// FONCTIONS LIES AUX SYSTEMES D'EQUATIONS LINEAIRES ///
void saisir_matrice( float A[10][10],float B[10], int N)
{
    int i, j;
    for (i = 1 ; i<=N ; i++)
    {
        for ( j =1 ; j <= N ; j++)
        {
            printf("\n entrez l'élément %d %d de la matrice\n\t\t>>",i,j);
            scanf("%f",&A[i][j]);
        }
    }
    for (i=  1 ; i<= N; i++)
    {
        printf("\n entrez l'element %d de la matrice du second nmembre\t>>",i);
        scanf("%f",&B[i]);
    }
}
void display_array(float mat[10][10],float lin[10],int l)
{
    int i,j; /// compteurs ///
    for ( i = 1 ; i <= l ; i++ )
    {
        for (j = 1 ; j <= l ; j++)
        {
            printf("\t\t%.2f",mat[i][j]);
        }
        printf("\t\t%.2f",lin[i]);
        printf("\n");
    }
}
void display_simple_matrix(float a[10][10],int o)
{
    for ( int i = 1 ; i <= o ; i++)
    {
        for (int j = 1 ; j<= o; j++)
        {
            printf("\t%.2f",a[i][j]);
        }
        printf("\n");
    }
}
void methode_de_crout(float a[10][10],float b[10],int o)
{
    float L[10][10],U[10][10],x[10],y[10],s;
    int i,j,k,m;
/// initialisation des matrices L et U ///
    for (i=0; i<o; i++)
        for (j=0; j<o; j++)
        {
            if(i==j)
                U[i][j]=1;
            else
                U[i][j]=0;
            L[i][j]=0;
        }
/// decomposition de la matrice en U et L ///
    for (m=0; m<o; m++)
    {
        for (i=m; i<o; i++)
        {
            s=0;
            for (k=0; k<m; k++)
                s=s+L[i][k]*U[k][m];
            L[i][m]=a[i][m]-s;
        }

        if (L[k][k]==0)
        {
            printf("\n pivot nul : cette methode ne ve pas fonctionner\n");
            exit(EXIT_FAILURE);
        }

        for (j=m+1; j<o; j++)
        {
            s=0;
            for (k=0; k<m; k++)
                s=s+L[m][k]*U[k][j];
            U[m][j]=(a[m][j]-s)/L[m][m];
        }
    }
    /// RESOLUTION DU SYSTEME OBTENU ///
    for(i=0; i<o; i++)
    {
        s=0;
        for(j=0; j<i; j++)
            s=s+L[i][j]*y[j];
        y[i]=(b[i]-s)/L[i][i];
    }

    for(i=o-1; i>=0; i--)
    {
        s=0;
        for(j=i+1; j<o; j++)
            s=s+U[i][j]*x[j];
        x[i]=(y[i]-s)/U[i][i];
    }
    /// AFFICHAGE DES RESULTATS ///
    printf("\n la matrice L\n");
    display_simple_matrix(L,o);
    printf("\n la matrice U\n");
    display_simple_matrix(U,o);
    printf("\n voici la solution du systeme \n");
    for ( i = 1 ; i <=o ; i++)
    {
        printf("\n X[%d] = %.4f",i,x[i]);
    }
}
void methode_de_cholesky(float a[10][10],float b[10],int l)
{
    float L[10][10],Lt[10][10],x[10],y[10],s,p;
    int i,j,k;
    int g = l ;
/// symetrical checks of the matrix ///
    for (i=0; i<l; i++)
    {
        for (j=0; j<l; j++)
        {
            if (a[i][j]!=a[j][i])
            {
                printf("\n\nla matrice n'est pas symetrique: cholesky ne fonctionnera pas avec cette matrice \n\n");
                printf("\n try another method\n");
            }
            else
            {
                printf("\n la matrice est symetrique\n");
            }
        }
    }
/// decomposition et controle de la symetrie ///
    for (i=0; i<l; i++)
    {
        for (j=0; j<l; j++)
        {
            L[i][j]=0;
        }
    }

    for (i=0; i<l; i++)
    {
        s=0;
        for (k=0; k<i; k++)
        {
            s+=pow(L[i][k],2);
        }
        p=a[i][i]-s;

        if (p<=0)
        {
            printf("\n\n la matrice n'est pas definie positive: la methode de cholesky ne fonctionnera pas\n\n");
            printf("\n try another method\n");
        }

        L[i][i]=sqrt(p);

        for(j=i+1; j<l; j++)
        {
            s=0;
            for (k=0; k<i; k++)
                s+=L[i][k]*L[j][k];
            L[j][i]=(a[j][i]-s)/L[i][i];
        }
    }
    /// transposition de la matrice L ///

    for (i=0; i<l; i++)
    {
        for (j=0; j<l; j++)
        {
            Lt[i][j]=L[j][i];
        }
    }

    /// resolution du systeme ///
    for(i=0; i<l; i++)
    {
        s=0;
        for(j=0; j<i; j++)
        {
            s=s+L[i][j]*y[j];
        }
        y[i]=(b[i]-s)/L[i][i];
    }

    for(i=l-1; i>=0; i--)
    {
        s=0;
        for(j=i+1; j<l; j++)
        {
            s=s+Lt[i][j]*x[j];
        }
        x[i]=(y[i]-s)/Lt[i][i];
    }
    /// affichage des resultats ///
    printf("\n voici les resultats des manipulations des matrices\n");
    printf("\n matrice L\n");
    display_simple_matrix(L,g);
    printf("\n matrice Lt\n");
    display_simple_matrix(Lt,g);
    printf("\n voici les solutions recherchées\n");
    for ( i = 1 ; i <=l ; i++)
    {
        printf("\n X[%d] = %.4f",i,x[i]);
    }
}
void methode_du_pivot_de_gauss(float a[10][10],float b[10], int l)
{

    int i, j, k ;
    int imin ;
    float p, x[10] ;
    float sum, valmin, tump1, tump2 ;

    for(k = 0 ; k < l-1 ; k++)
    {
        /// Dans un premier temps, on cherche l'élément minimum (non ///
        /// nul) en valeur absolue dans la colonne k et d'indice i   ///
        /// supérieur ou égal à k.  ////
        printf("\n voici le systeme initial\n");
        display_array(a,b,l);

        valmin = a[k][k] ;
        imin = k ;
        for(i = k+1 ; i < l ; i++)
        {
            if (valmin != 0)
            {
                if (abs(a[i][k]) < abs(valmin) && a[i][k] != 0)
                {
                    valmin = a[i][k] ;
                    imin = i ;
                }
            }
            else
            {
                valmin = a[i][k] ;
                imin = i ;
            }
        }

        ///Si l'élément minimum est nul, on peut en déduire ///
        /// que la matrice est singulière. Le pogramme est   ///
        /// alors interrompu.                                ///

        if (valmin == 0.)
        {
            printf("\npivot nul\n") ;
            exit( EXIT_FAILURE ) ;
        }

        /// Si la matrice n'est pas singulière, on inverse    ///
        ///les éléments de la ligne imax avec les éléments   ///
        ///de la ligne k. On fait de même avec le vecteur b. ///

        for(j = 0 ; j < l ; j++)
        {
            tump1 = a[imin][j] ;
            a[imin][j] = a[k][j] ;
            a[k][j] = tump1 ;
        }

        tump2 = b[imin] ;
        b[imin] = b[k] ;
        b[k] = tump2 ;


        /// On procède à la réduction de la matrice par la ///
        /// méthode d'élimination de Gauss. ///

        for(i = k+1 ; i < l ; i++)
        {
            p = a[i][k]/a[k][k] ;

            for(j = 0 ; j < l ; j++)
            {
                a[i][j] = a[i][j] - p*a[k][j] ;
            }

            b[i] = b[i] - p*b[k] ;
        }
    }

    /// On vérifie que la matrice n'est toujours pas singulière. ///
    ///Si c'est le cas, on interrompt le programme. ///

    if (a[l-1][l-1] == 0)
    {
        printf("\npivot nul n") ;
        exit( EXIT_FAILURE ) ;
    }

    /// Une fois le système réduit, on obtient une matrice triangulaire ///
    /// supérieure et la résolution du système se fait très simplement. ///

    x[l-1] = b[l-1]/a[l-1][l-1] ;

    for(i = l-2 ; i > -1 ; i--)
    {
        sum = 0 ;

        for(j = l-1 ; j > i ; j--)
        {
            sum = sum + a[i][j]*x[j] ;
        }
        x[i] = (b[i] - sum)/a[i][i] ;
    }
/// affichage des resultats ///
    printf("\n voici les solutions\n");

    for(i = 0 ; i < l; i++)
    {
        printf("(X%d)   =",i+1);
        printf("\t%.6f",x[i]);
        printf("\n\n");
    }
}
float calc_norme(float x[10],int o)
{
    float ref;
    int i;
    ref=0;
    for(i=0; i<o; i++)
        if (x[i]>ref)
            ref=x[i];
    return(ref);
}
void methode_de_jacobi(float a[10][10],float b[10], int o)
{
    printf("\n la methode de jacobi !!\n");
    /// float a[10][10], b[10];
    float x[10],x1[10],x2[10],s, er;
    int i,j,k;
    int maxiter;
    int iter;
    printf("\n entrez le nombre maximal d'iterations que vous voulez faire:\n");
    scanf("%d",&maxiter);
    printf("\n entrez la precision que vous voulez avoir sur le resultat\n");
    scanf("%f",&er);
//initialisation du vecteur
    printf("\n entrez les coordonnées du vecteur initial\n");
    for (i=0; i<o; i++)
    {
        printf(" X0[%d]= ",i+1);
        scanf("%f",&x1[i]);
    }
    float r = calc_norme(x,o);
    do
    {
        for(i=0; i<o; i++)
        {
            s=0;
            for (j=0; j<o; j++)
                if (i!=j)
                    s=s+a[i][j]*x1[j];
            x2[i]=(b[i]-s)/a[i][i];
        }
        for (k=0; k<o; k++)
        {
            x[k]=fabs(x1[k]-x2[k]);
            x1[k]=x2[k];
        }

        iter++;
    }
    while (r >er || iter < maxiter ) ;
    /// affichage des resultats des manipulatons ///
    printf("\n voici le systeme initial\n");
    display_array(a,b,o);
    printf("\n voici les resultats obtenus apres %d iterations\n:",iter);
    for (i=1; i<= o; i++)
    {
        printf(" \t\t X%d =  %.4f \n",i,x2[i]);

    }
}
void methode_de_doolittle( float a[10][10],float b[10],int o)
{

    float L[10][10],U[10][10],x[10],y[10],s;
    int i,j,k,m;

    for (i=0; i<o; i++)
        for (j=0; j<o; j++)
        {
            if(i==j)
                L[i][j]=1;
            else
                L[i][j]=0;
            U[i][j]=0;
        }

    for (m=0; m<o; m++)
    {
        for (j=m; j<o; j++)
        {
            s=0;
            for (k=0; k<m; k++)
                s=s+L[m][k]*U[k][j];
            U[m][j]=a[m][j]-s;
        }
        if (U[k][k]==0)
        {
            printf("\n un pivot nul. la methode LU de doolittle ne fonctionera pas\n");
            exit(EXIT_FAILURE);
        }

        for (i=m+1; i<o; i++)
        {
            s=0;
            for (k=0; k<m; k++)
                s=s+L[i][k]*U[k][m];
            L[i][m]=(a[i][m]-s)/U[m][m];
        }
    }

/// resolution du systeme ///
    for(i=0; i<n; i++)
    {
        s=0;
        for(j=0; j<i; j++)
            s=s+L[i][j]*y[j];
        y[i]=(b[i]-s)/L[i][i];
    }

    for(i=n-1; i>=0; i--)
    {
        s=0;
        for(j=i+1; j<n; j++)
            s=s+U[i][j]*x[j];
        x[i]=(y[i]-s)/U[i][i];
    }

    /// affichage des resultats ///
    printf("\n la matrice L\n");
    display_simple_matrix(L,o);
    printf("\n la matrice U\n");
    display_simple_matrix(U,o);
    printf("\n voici la solution du systeme \n");
    for ( i = 1 ; i <=o ; i++)
    {
        printf("\n X[%d] = %.4f",i,x[i]);
    }
}
void methode_de_gauss_jordan(float a[10][10], float b[10], int o)
{
    float au[10][10], x[10];
    int i,l,j;
    float p ;
    printf("\n voici le systeme entré\n");
    display_array(a,b,o);
    /// augmentation de la matrice pour les calculs ///
    int k = o+1 ;
    for (i = 1 ; i <= o ; i++ )
    {
        for ( j = 1 ; j <= o ; j++)
        {
            au[i][j] = a[i][j];
            if (j == o)
                au[i][k] = b[i];
        }
    }
    printf("\n voici la matrice augmentée\n");
    display_simple_matrix(au,k);
    for ( i = 1 ; i <= o ; i++)
    {
        for (j = 1 ; j <= o ; j++)
        {
            if (i != j)
            {
                p = au[j][i]/au[i][i];
                for (l = 1 ; l <=k ; l++ )
                {
                    au[j][l] = au[j][l] -p*au[i][l];
                }
            }
        }
    }
    printf("\n apres transformation, voici la solution du systeme:\n");
    for(i=1; i<=o; i++)
    {
        x[i]=au[i][k]/au[i][i];
        printf("\n x%d =%.2f\n",i,x[i]);
    }
}

// Calcul de la norme du vecteur obtenu ///

float norme(float x[10],int na)
{
    float ref;
    int i;
    ref=0;
    for(i=0; i<na; i++)
        if (x[i]>ref)
            ref=x[i];
    return(ref);
}
void methode_de_gauss_seidel(float a[10][10],float b[10],int na)
{
    float x[10],x1[10],x2[10],s,p,eps;
    int i,j,k,iter,l=0;

//initialisation du vecteur
    printf("\n combien d'iterations voulez vous faire au maximum?\n");
    scanf("%d",&iter);
    printf("\n donnez la precision souhaitée sur le calcul du resultat\n"),
           scanf("%f",&eps);
    printf("\n initialisation vecteur solution : \n\n");
    for (i=0; i<na; i++)
    {
        printf(" X(0)[%d]= ",i+1);
        scanf("%f",&x1[i]);
    }

    do
    {
        for(i=0; i<na; i++)
        {
            s=0;
            p=0;
            for (j=i+1; j<na; j++)
                s+=a[i][j]*x1[j];
            for (j=0; j<i; j++)
                p+=a[i][j]*x2[j];
            x2[i]=(b[i]-s-p)/a[i][i];
        }
        for (k=0; k<na; k++)
        {
            x[k]=fabs(x1[k]-x2[k]);
            x1[k]=x2[k];
        }

        l++;
    }
    while (norme(x,na)>eps || l < iter) ;
    printf("\n resultats obtenus par la methode de gauss - seidel :\n\n");
    for (i=0; i<na; i++)
        printf(" X_%d =  %f  ;\n",i+1,x2[i]);
    printf("\n * Apres %d iterations \n",iter);
}

void systemes_lineaire()
{
    int o;
    int ch2,ch3,ch4;
    float A[10][10], B[10] ;
    printf("\n entrez l'ordre de la matrice\n");
    scanf("%d",&o);
    saisir_matrice(A,B,o);
    display_array(A,B,o);
    do
    {
        printf("\n quelle methode type de methode de resolution voulez-vous utiliser?\n");
        printf("\n 1 - methodes directes\n ");
        printf("\n 2 - methodes itératives ou indirectes\n");
        scanf("%d",&ch2);
    }
    while(ch2 < 1 || 2 < ch2);
    switch(ch2)
    {
    case 1 :
        printf("\n\t\t METHODES DIRECTES DE RESOLUTION DES SYSTEMES LINEAIRES\n");
        printf("\n veuillez choisir votre methode de resolution\n\t");
        do
        {
            printf("\n\t\t 1 - methode d'élimination ou du pivot de GAUSS\n");
            printf("\n\t\t 2 - methode de Gauss-Jordan\n");
            printf("\n\t\t 3 - methode de Choleski\n");
            printf("\n\t\t 4 - methode LU de crout \n");
            printf("\n\t\t 5 - methode LU de doolittle\n");
            scanf("%d",&ch3);
        }
        while( ch3 < 1 || 5 < ch3 );
        switch(ch3)
        {
        case 1 :
            printf("\n\t\t GAUSSIAN ELIMINATION METHOD BY RICH.COM\n");
            methode_du_pivot_de_gauss(A,B,o);
            break;
        case 2 :
            printf("\n\t\t METHODE DE GAUSS - JORDAN \n");
            methode_de_gauss_jordan(A,B,o);
            break;
        case 3 :
            printf("\n\t\t METHODE DE CHOLESKY \n");
            methode_de_cholesky(A,B,o);
            break;
        case 4 :
            printf("\n\t\t METHODE LU DE CROUT \n");
            methode_de_crout(A,B,o);
            break;
        case 5 :
            printf("\n\t\t METHODE LU DE DOOLITTLE\n");
            methode_de_doolittle(A,B,o);
            break;
        }
        break;
    case 2 :
        printf("\n\t\t METHODES INDIRECTES OU ITERATIVES DE RESOLUTION DES SYSTEMES LINEAIRES\n\n");
        printf("\n veuillez choisir la methode de resolution que vous voulez utiliser\n");
        do
        {
            printf("\n\t\t 1 - methode de gauss seidel\n");
            printf("\n\t\t 2 - methode de jacobi\n");
            scanf("%d",&ch4);
        }
        while( ch4 < 1 || 2 <ch4 );
        switch(ch4)
        {
        case 1 :
            printf("\n\t\t METHODE DE GAUSS SEIDEL\n");
            methode_de_gauss_seidel(A,B,o);
            break;
        case 2 :
            printf("\n\t\t METHODE DE JACOBI \n");
            methode_de_jacobi(A,B,o);
            break;
        }
        break;
    }
}

/// FONCTIONS LIES A L'INTERPOLATION LINEAIRE ///
void interpolation_de_lagrange()
{

    int n4, saisie_n, saisie_x, saisie_y, i, j;
    float X[20], Y[20], coef[20];

    printf("\n ____________ METHODE D'INTERPLATION DE LAGRANGE ________________\n");

        do
        {
            printf("Combien de points voulez vous interpoler? \n");
            saisie_n = scanf("%d", &n4);
            fflush(stdin);
        }
        while(saisie_n == 0 || n4 <= 1 || n4 >= 20);


        printf("Saisie des coordonées des points d'interpolation \n");
        for(i=1; i<=n4; i++)
        {
            do
            {
                printf("\npoint P%d (x%d, y%d)\n", i, i, i);
                printf("x%d = \t", i);
                saisie_x = scanf("%f", &X[i]);
                fflush(stdin);
                printf("y%d = \t", i);
                saisie_y = scanf("%f", &Y[i]);
                fflush(stdin);
            }
            while(saisie_x ==0 || saisie_y == 0);
        }

        for(i=1; i<=n4; i++)
        {
            coef[i]=1;
            for(j=1; j<=n4; j++)
            {
                if(i!=j)
                {
                    coef[i] = coef[i] * (X[i] - X[j]);
                }
            }
            coef[i] = Y[i] / coef[i];
        }

        printf("\n\nVoici le polynome d'interpolation de lagrange des points pré saisis \n\n");

        printf("\nP Lagrange (x) = ");

        for(i=1; i<=n4; i++)
        {
            if(coef[i]>=0)
            {
                printf("+%.4f", coef[i]);
                for(j=1; j<=n4; j++)
                {
                    if(i!=j)
                    {
                        printf("( x - (%.4f))", X[j]);
                    }

                }
                printf(" ");
            }

            else
            {
                printf("-%.4f", -coef[i]);
                for(j=1; j<=n4; j++)
                {
                    if(i!=j)
                    {
                        printf(" (x - (%.4f))", X[j]);
                    }

                }
                printf(" ");
            }
        }

    }
    void interpolation_de_newton()
    {

        int n7, saisie_n, saisie_x, saisie_y, i, j;
        float X[20], Y[20], f[20][20], coef[20];


        printf("\n ____________ METHODE D'INTERPLATION DE NEWTON ________________\n");

        do
        {
            printf("\ncombien de points voulez vous interpoler?\n");
            saisie_n = scanf("%d", &n7);
            fflush(stdin);
        }
        while(saisie_n == 0 || n7 <= 1 || n7 >= 20);


        printf(" Saisie des coordonnées des points à interpoler\n");
        for(i=1; i<=n7; i++)
        {
            do
            {
                printf("\n point P%d (x%d, y%d)  \n", i, i, i);
                printf("x%d = \t", i);
                saisie_x = scanf("%f", &X[i]);
                fflush(stdin);
                printf("y%d = \t", i);
                saisie_y = scanf("%f", &Y[i]);
                fflush(stdin);

                while(saisie_x == 0 || saisie_y == 0)
                {
                    printf("invalid input. you have to reload it\n");
                    printf("x%d = \t", i);
                    saisie_x = scanf("%f", &X[i]);
                    fflush(stdin);
                    printf("y%d = \t", i);
                    saisie_y = scanf("%f", &Y[i]);
                    fflush(stdin);
                }
            }
            while(saisie_x ==0 || saisie_y == 0);
        }

        for(i = 1; i<=n7; i++)
        {
            f[i][1] = Y[i];
        }
        for(j = 2; j<=n7; j++)
        {
            for(i = j; i <= n7; i++)
            {
                f[i][j] = (f[i-1][j-1] - f[i][j-1])/(X[1] - X[j]);
            }

        }

        for(j = 1; j<=n7; j++)
        {
            for(i = j; i <= n7; i++)
            {
                coef[i] = f[i][j];
            }

        }

        printf("\n\nvoici le polynome d'interpolation de newton des points saisis\n\n");

        printf("\nP Newton (x) = ");

        for(i = 1; i <= n7; i++)
        {
            if(coef[i]>0)
            {
                printf("+%.1f", coef[i]);
                for(j = 1; j < i; j++)
                {
                    printf("(x - ( %1.f ))", X[j]);
                }
                printf("\n");
            }
            else
            {
                printf("-%.1f", -coef[i]);
                for(j = 1; j < i; j++)
                {
                    printf("(x - ( %1.f ))", X[j]);
                }
                printf("\n");
            }
        }
    }

    void interpolation_des_moindres_carres()
    {
        int deg; /// degré du polynome d'interpolation de Newton ///
        int i,j,k; /// les compteurs ///
        int u, ni;
        float p[10][10] ; ///matrice des moindres carrées ///
        float *b ;/// vecteur du second membre ///
        float *c ; ///resultat ou les coefficients du polynome de newton ///
        float *ord ; /// ordonnée des points à interpoler ///
        float *ab ; /// abscisse des points à interpoler ///
        int temp1, temp2 ; /// variables d'aide ou temporaire ///
        printf("\n entrez le nombre de points à interpoler\n");
        scanf("%d",&u);
        ni = u+1 ;
        /// allocation de place pour les matrices et vecteurs ///
        b = (float *)malloc (sizeof(float)*ni);
        c = (float *)malloc(sizeof(float)*ni);
        ord = (float *)malloc(sizeof(float)*u);
        ab = (float *)malloc(sizeof(float)*u);
        /// saisie des coordonnées des points à interpoler ///
        for (i = 1 ; i <= u ; i++ )
        {
            printf("\n\t point %d",i);
            printf("\n entrez les coordonnées x[%d] y[%d]",i,i);
            scanf("%f %f",&ab[i],&ord[i]);
        }
        do
        {
            printf("\n entrez le degré du polynome d'interpolation\n");
            printf("\n il doit etre inferieur au nombre de points à interpoler\n");
            scanf("%d",&deg);
        }
        while (deg < 0 || deg > u );
        temp1 = 2*deg;
        /// calcul des coefficients de la matrice ///
        for (i = 1 ; i <= ni ; i++)
        {
            temp1 = temp2;
            for(j = 1 ; j <= ni ; j++)
            {
                p[i][j] = 0 ;
                for (k = 1 ; k <= u ; k++)
                {
                    p[i][j] += (pow(ab[k],temp1));
                }
                temp1 --;
            }
            temp2 --;
        }
        /// calcul du vecteur du second membre ///
        temp1 = deg;
        for ( i = 1 ; i <= ni ; i++)
        {
            b[i] = 0 ;
            for (k = 1 ; j <= u ; k++)
            {
                b[i]+= (pow(ab[k],temp1)*ord[k]);
            }
            temp1 --;
        }
        methode_de_gauss_jordan(p,b,ni);
        printf("\n\n\tAffichage de la matrice des moindres carrées: \n\n\n");

        for(i = 1 ; i<= ni ; i++)
        {
            for (j=1 ; j<=ni ; j++)
            {
                printf("(X%d)   =",i+1);
                printf("\t%.3f",p[i][j]);
                printf("\n\n");
            }

        }
        for (j=1 ; j <= ni ; j++)
        {
            printf("(X%d)   =",i+1);
            printf("\t%.3f",b[j]);
            printf("\n\n");
        }
        //Affichage de la solution
        temp2 = deg;
        printf("\n\n\t\tp(x)= ");
        for (i = 0 ; i < ni ; i++)
        {
            printf("%fx^%i ", c[i], temp2);
            temp2--;
            if (i<deg)
                printf("+");
        }
        printf("\n\n");
        // return 0 ;
    }
    void interpolation_lineaire() /// fonction qui pilote les interpolations lineaires
    {
        int a ;
        printf("\n Bienvenue dans ce code:\n nous allons interpoler des points à certains points\n");
        do
        {
            printf("\n choisissez la methode que vous voulez utiliser\n");
            printf("\n 1 - methode d'interpolation de lagrange\n");
            printf("\n 2 - methode d'interpolation de newton\n");
            printf("\n 3 - methode des moindres carrées\n");
            scanf("%d",&a);
        }
        while (a< 1 || 3 < a);
        switch (a)
        {
        case 1 :
            printf("\n vous avez choisi la methode de lagrange\n");
            interpolation_de_lagrange();
            break;
        case 2 :
            printf("\n vous avez choisi la methode de Newton\n");
            interpolation_de_newton();
            break;
        case 3 :
            printf("\n vous avez choisi la methode des moindres carrées\n");
            interpolation_des_moindres_carres();
            break;
        }
        printf("\n merci d'avoir utilisé le code: vos apports et commentaires ou suggestions sont les bienvenues\n");

    }

    void methode_des_rectangles_a_gauche()
    {
        float a,b;
        float fa ;
        float I;
        printf("\n entrez la borne inferieur  d'integration\n");
        scanf("%f",&a);
        printf("\n entrez la borne superieur d'integration\n");
        scanf("%f",&b);
        printf("\n entrez l'image par f de la borne inferieur d'integration\n");
        scanf("%f",&fa);
        I = (b-a)*fa;
        printf("\n l'integrale cherchée est %f",I);

    }

    void methode_des_rectangles_a_droite()
    {

        float a,b;
        float fa ;
        float I;
        printf("\n entrez la borne inferieur  d'integration\n");
        scanf("%f",&a);
        printf("\n entrez la borne superieur d'integration\n");
        scanf("%f",&b);
        printf("\n entrez l'image par f de la borne superieur d'integration\n");
        scanf("%f",&fa);
        I = (b-a)*fa;
        printf("\n l'integrale cherchée est %f",I);
    }

    void methode_du_point_milieu()
    {

        float a,b;
        float fa ;
        float I;
        printf("\n entrez la borne inferieur  d'integration\n");
        scanf("%f",&a);
        printf("\n entrez la borne superieur d'integration\n");
        scanf("%f",&b);
        printf("\n entrez l'image par f du milieu de l'intervale d'integration\n");
        scanf("%f",&fa);
        I = (b-a)*fa;
        printf("\n l'integrale cherchée est %f",I);
    }

    void methode_des_trapezes()
    {

        float a,b;
        float fa, fb;
        float I;
        printf("\n entrez la borne inferieur  d'integration\n");
        scanf("%f",&a);
        printf("\n entrez la borne superieur d'integration\n");
        scanf("%f",&b);
        printf("\n entrez l'image par f de la borne inferieur d'integration\n");
        scanf("%f",&fa);
        printf("\n entrez l'image par f de la borne superieur d'integration\n");
        scanf("%f",&fb);
        I = (b-a)*((fa + fb)/2);
        printf("\n l'integrale cherchée est %f",I);
    }
    int  menu_equadiff()
    {
        int rep;
        printf("\n Equation differentielle\n");
        do
        {
            printf("\n quelle methode voulez - vous utiliser\n");
            printf("\n 1 - Methode d'euler\n");
            printf("\n 2 - Methode de Runge - Kutta d'ordre 2\n");
            scanf("%d",&rep);
        }
        while(rep < 1 || rep > 2);
        return rep ;
    }
    float equafon(float m)
    {
        return m*m - 2*m + 1 ;
    }
    void methode_de_euler()
    {
        float *y;
        float a, b;
        float *x;
        float h ;
        float *xi;
        float *yi;
        float mat[10][10];
        float mat1[10];
        int i,j;
        int na;
        int ni ; /// nombre de points approximatifs ///
        do
        {
            printf("\n entrez les bornes de l'intervalle à utiliser (a <b )\n");
            scanf("%f %f",&a,&b);
        }
        while( a > b );
        printf("\n entrez l'écart ou le pas entre deux points consecutifs d'approximation\n");
        scanf("%f",&h);
        ni = (int) (b-a)/h;
        na = ni+2;
        x = (float *)malloc(sizeof(float)*ni);
        y = (float *)malloc(sizeof(float)*ni);
        xi = (float *)malloc(sizeof(float)*na+3);
        yi = (float *)malloc(sizeof(float)*na+2);
        x[0] = a ;
        y[0] = equafon(a) ;
        for(i = 1 ; i < ni ; i++)
        {
            x[i] = a + i*ni;
            y[i+1] = y[i]+(x[i+1]-x[i])*equafon(x[i]);

            printf("\n les points à interpoler sont %.3f  %.3f",x[i],y[i]);
        }
        printf("\n les points à interpoler sont %.3f  %.3f",x[0],y[0]);
        printf("\n les points à interpoler sont %.3f  %.3f",b,equafon(b));
        printf("\n partie 1 : terminée\n");
        /// preparation ou recueillement des points pour l'interpolation ///
        xi[1] = x[0];
        xi[2] = b;
        yi[1] = y[0];
        yi[2] = equafon(b);
        for (i = 3 ; i < na-3 ; i++)
        {
            for( j = 1 ; j < ni ; i++)
            {
                xi[i] = x[j];
                yi[i] = y[j];
            }
        }
        printf("\n effectué\n");
        /// preparation de la matrice pour l'interpolation naive ///
        for (i = 0 ; i < na ; i++)
        {
            for(j = 0 ; j < na ; j++)
            {
                mat[i][j] = pow(xi[i],j);
            }
            mat1[i] = yi[i];
        }
        /// resolution du systeme obtenu ///
        printf("\n resolution\n");
        // methode_de_gauss_jordan(mat,mat1,na);
        interpolation_de_lagrange();
    }
    void methode_de_runge_kutta()
    {
        float *y;
        float a, b;
        float *x;
        float h ;
        float *xi;
        float *yi;
        float mat[10][10];
        float mat1[10];
        int i,j;
        int na;
        int ni ; /// nombre de points approximatifs ///
        do
        {
            printf("\n entrez les bornes de l'intervalle à utiliser (a <b )\n");
            scanf("%f %f",&a,&b);
        }
        while( a > b );
        printf("\n entrez l'écart ou le pas entre deux points consecutifs d'approximation\n");
        scanf("%f",&h);
        ni = (int) (b-a)/h;
        na = ni+2;
        x = (float *)malloc(sizeof(float)*ni);
        y = (float *)malloc(sizeof(float)*ni);
        xi = (float *)malloc(sizeof(float)*na+3);
        yi = (float *)malloc(sizeof(float)*na+2);
        x[0] = a ;
        y[0] = equafon(a) ;
        for(i = 1 ; i < ni ; i++)
        {
            x[i] =( (a + i*ni)+x[i-1])/2;
            y[i+1] = y[i]+(x[i+1]-x[i])*equafon(x[i]);

            printf("\n les points à interpoler sont %.3f  %.3f",x[i],y[i]);
        }
        printf("\n les points à interpoler sont %.3f  %.3f",x[0],y[0]);
        printf("\n les points à interpoler sont %.3f  %.3f",b,equafon(b));
        printf("\n partie 1 : terminée\n");
        /// preparation ou recueillement des points pour l'interpolation ///
        xi[1] = x[0];
        xi[2] = b;
        yi[1] = y[0];
        yi[2] = equafon(b);
        for (i = 3 ; i < na-3 ; i++)
        {
            for( j = 1 ; j < ni ; i++)
            {
                xi[i] = x[j];
                yi[i] = y[j];
            }
        }
        printf("\n effectué\n");
        /// preparation de la matrice pour l'interpolation naive ///
        for (i = 0 ; i < na ; i++)
        {
            for(j = 0 ; j < na ; j++)
            {
                mat[i][j] = pow(xi[i],j);
            }
            mat1[i] = yi[i];
        }
        /// resolution du systeme obtenu ///
        printf("\n resolution\n");
        // methode_de_gauss_jordan(mat,mat1,na);
        interpolation_de_lagrange();
    }
    void equation_differentielle_et_integration_numerique()
    {
        int choix;
        int ch1;
        int ch2;
        printf("\n bienvenue dans cette partie du code\n");
        do
        {
            printf("\n que voulez - vous faire\n");
            printf("\n 1 - Intégration numérique \n 2 - Equation differentielle \n");
            scanf("%d",&choix);
        }
        while (choix < 1 || 2 < choix);
        switch (choix)
        {
        case 1 :
            printf("\n vous avez choisi l'Intégration numerique\n");
            do
            {
                printf("\n quelle methode voulez vous utiliser\n");
                printf("\n 1 - methode des rectangles à gauche\n 2 - methode des rectangles à droite\n 3 - methode du point milieu \n 4 - methode de trapezes\n ");
                scanf("%d",&ch1);
            }
            while (ch1 < 1 || 4 < ch1);
            switch (ch1)
            {
            case 1 :
                printf("\n methode des rectangles à gauche\n");
                methode_des_rectangles_a_gauche();
                break;
            case 2 :
                printf("\n methode de rectangles à droite\n");
                methode_des_rectangles_a_droite();
                break;
            case 3 :
                printf("\n methode du point de milieu \n");
                methode_du_point_milieu();
                break;
            case 4 :
                printf("\n methode des trapèzes\n");
                methode_des_trapezes();
                break;
            }
            break;
        case 2 :
            ch2 = menu_equadiff();
            switch(ch2)
            {
            case 1 :
                printf("\n vous avez choisi la methode d'euler\n");
                methode_de_euler();
                break;
            case 2 :
                printf("\n vous avez choisi la methode de runge kutta d'ordre 2 \n");
                methode_de_runge_kutta();
                break;
            }

        }

    }



/// A PROPOS DU PROGRAMME ///
    void about()
    {
        printf("\n ce code est la compilations des programmes que nous avons eu à developper en maths 300 pour des histoires d'analyse numerique\n");
        printf("\n le developpeur richard.com est le propriétaire. espérons que des versions plus avancés dudit code sortent dans des jours à venir\n");
        printf("\n une version en interface graphique sera dispo dès la fin du semestre harmattan\n");
        printf("\n the author: @richard.com:\n");
        printf("\n copyright 2019\n");
    }

    int main()
    {
        printf("\n *************************************************************************\n");
        printf("\n\t\t A N A L Y S E   N U M E R I Q U E \n");
        printf("\n *************************************************************************\n");
        int ans;
        int z;
        z = menu_principal();
        do
        {
            switch (z)
            {
            case 1:
                printf("\n *************************************************************************\n");
                printf("\n\t\t S Y S T E M E S  N O N  L I N E A I R E S \n");
                printf("\n *************************************************************************\n");
                systeme_non_lineaire();
                break;
            case 2:
                printf("\n *************************************************************************\n");
                printf("\n\t\t S Y S T E M E S  L I N E A I R E S\n");
                printf("\n *************************************************************************\n");
                printf("\n nous allons travailler uniquement avec les matrices carrées:\n");
                printf("\n faites un effort pour respecter les consignes!!!\n");
                systemes_lineaire();
                break;
            case 3:
                printf("\n *************************************************************************\n");
                printf("\n\t\t I N T E R P O L A T I O N   L I N E A I R E \n");
                printf("\n *************************************************************************\n");
                interpolation_lineaire();
                break;
            case 4:
                printf("\n *********************************************************************************************************\n");
                printf("\n\t E Q U A T I O N S   D I F F E R E N T I E L L E  E T  I N T E G R A T I O N  N U M E R I Q U E  \n");
                printf("\n *********************************************************************************************************\n");
                equation_differentielle_et_integration_numerique();
                break;
            case 5 :
                printf("\n  ===== À  P R O P O S  D U  P R O G R A M M E \n ");
                about();
                break;
            }
            ///    do
            /// {
            printf("\n voulez-vous continuer avec le code?\n");
            printf("\n 0 - non \n 1 - oui \n");
            scanf("%d",&ans);
            if (ans != 1 || ans != 0 )
            {
                printf("\n vous n'avez pas suivi les consignes:\n");
                printf("\n je suis desole de vous l'apprendre: le programme s'est arreté\n");
            }
            fflush(stdin);
            ///}
            /// while(ans != 1 || ans != 0);
        }
        while(ans == 1);
        printf("\n merci pour votre compagnie!!!\n");
        printf("\n \n");
        return 0;
    }
