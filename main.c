#include <stdio.h>
#include <conio.h>
#include <math.h>

FILE*archivo;
typedef struct _Nodo
{
    char dato;
    struct _Nodo *siguiente;
}
Nodo;

Nodo* crearNodo(char d)
{
    Nodo *nuevo;

    nuevo=(Nodo*)malloc(sizeof(Nodo));
    nuevo->dato=d;
    nuevo->siguiente=NULL;

    return nuevo;
}

Nodo* apilar(Nodo *top, char d)
{
    Nodo *nuevo;
    nuevo=crearNodo(d);

    if(top!=NULL)
        nuevo->siguiente=top;

    return nuevo;
}

Nodo* desapilar(Nodo *top)
{
    Nodo *aux;
    aux=top;

    if(aux!=NULL)
        {
            top=top->siguiente;
            free(aux);
        }

    return top;
}

void verPila(Nodo *top)
{
    Nodo *aux;
    aux=top;

    if(aux==NULL)
        {
            printf("\n\tPILA VACIA");
        }
    else
        {
            printf("\n\tCARACTERES APILADOS");
            while(aux!=NULL)
            {
                printf("\n%c", aux->dato);
                aux=aux->siguiente;
            }
        }
}

typedef struct _Nodo1
{
    float dato;
    struct _Nodo1 *siguiente;
}
Nodo1;

Nodo1* crearNodo1(float d)
{
    Nodo1 *nuevo;

    nuevo=(Nodo1*)malloc(sizeof(Nodo1));
    nuevo->dato=d;
    nuevo->siguiente=NULL;

    return nuevo;
}

Nodo1* apilar1(Nodo1 *top, float d)
{
    Nodo1 *nuevo;
    nuevo=crearNodo1(d);

    if(top!=NULL)
        nuevo->siguiente=top;

    return nuevo;
}

Nodo1* desapilar1(Nodo1 *top)
{
    Nodo1 *aux;
    aux=top;

    if(aux!=NULL)
        {
            top=top->siguiente;
            free(aux);
        }

    return top;
}

void verPila1(Nodo1 *top)
{
    Nodo1 *aux;
    aux=top;

    if(aux==NULL)
        {
            printf("\n\tPILA VACIA");
        }
    else
        {
            printf("\n\tRESULTADO DE PASAR DE INFIJA A POSTFIJA: ");
            while(aux!=NULL)
            {
                printf("%f\n", aux->dato);
                aux=aux->siguiente;
            }
        }
}

void leerLineas()
{
    int o=0;
    char linea[50];

    for(int i=0;i<50;i++)
    {
        linea[i]=NULL;
    }

    //printf("\tINGRESE UNA LINEA DEL ARCHIVO:");
    //scanf("%d",&o);

    FILE *archivo;
    archivo=fopen("practica1.txt","r");

    if(archivo==NULL)
        printf("\n\tEL ARCHIVO NO EXISTE\n");
    else
    {
        //for(int i = 0; i < o ; i++)
        //{

            for(int i=0;i<50;i++)
            {
                linea[i]=NULL;
            }

            while(!feof(archivo))
            {
                fscanf(archivo,"%s\n",&linea);
                Balanceo(linea);
            }
        //}

        //printf("\n\tUSTED SELECCIONO LA LINEA %s\n", linea);
        //Balanceo(linea);
        fclose(archivo);
    }
}

void Balanceo(char linea[50])
{
    printf("\n\tBALANCEO DE LA EXPRESION\n");
    int i=0;
    char *caracter;
    Nodo *top;
    top=NULL;

    while(linea[i]!='\0')
    {
        caracter=&linea[i];

        if(*caracter=='('||*caracter=='{'||*caracter=='[')
        {
            top=apilar(top,*caracter);
            printf("\nCARACTER APILADO");
        }

        if(*caracter==')'&& top->dato=='('||*caracter=='}'&&top->dato=='{'||*caracter==']'&&top->dato=='[')
        {
            top=desapilar(top);
            printf("\nCARACTER DESAPILADO");
        }

        i++;
    }

    while(linea[i]=='\0'||top==NULL)
    {
        if(top==NULL||linea[i]!='\0')
        {
            printf("\n\n\tLA EXPRESION %s ESTA BALANCEADA",linea);
            linea[i]=')';
            PostFija(linea);
            break;
        }
        else
            archivo=fopen("resultados.txt","a");
            fprintf(archivo,"ESTA EXPRESION NO ESTA BALANCEADA: %s\n",linea);
            printf("\n\n\tLA EXPRESION %s NO ESTA BALANCEADA",linea);
        break;
    }
}

void PostFija(char linea[50])
{
    printf("\n\n\tCONVERSION A POSTFIJA\n");
    int i=0,e=0;
    char postfija[50];
    char *caracter;
    Nodo *top;
    top=NULL;

    top=apilar(top,'(');

    for(int i=0;i<50;i++)
        postfija[i]=NULL;

    while(linea[i]!='\0')
    {
        caracter=&linea[i];

        if(*caracter=='('||*caracter=='{'||*caracter=='[')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter=='-'&&top->dato=='/'||*caracter=='-'&&top->dato=='*'||*caracter=='-'&&top->dato=='%'||*caracter=='-'&&top->dato=='^')
        {
            postfija[e]=top->dato;
            printf("\nDATO AGREGADO A POSTFIJA %c",postfija[e]);
            top=desapilar(top);
            //top=apilar(top,*caracter);
            e++;
            //linea[i]='X';
            i=0;
        }

        else if(*caracter=='-'&&top->dato!='/'||*caracter=='-'&&top->dato!='*'||*caracter=='-'&&top->dato!='%'||*caracter=='-'&&top->dato!='^')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter=='+'&&top->dato=='/'||*caracter=='+'&&top->dato=='*'||*caracter=='+'&&top->dato=='%'||*caracter=='+'&&top->dato=='^')
        {
            postfija[e]=top->dato;
            printf("\nDATO AGREGADO A POSTFIJA %c",postfija[e]);
            top=desapilar(top);
            //top=apilar(top,*caracter);
            e++;
            //linea[i]='X';
            i=0;
        }

        else if(*caracter=='+'&&top->dato!='/' ||*caracter=='+'&&top->dato!='*' ||*caracter=='+'&&top->dato!='%' ||*caracter=='+'&&top->dato!='^')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter=='*'&&top->dato=='^')
        {
            postfija[e]=top->dato;
            printf("\nDATO AGREGADO A POSTFIJA %c",postfija[e]);
            top=desapilar(top);
        //    top=apilar(top,*caracter);
            e++;
         //   linea[i]='X';
            i=0;
        }

        else if(*caracter=='*'&&top->dato!='^')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter=='/'&&top->dato=='^')
        {
            postfija[e]=top->dato;
            printf("\nDATO AGREGADO A POSTFIJA %c",postfija[e]);
            top=desapilar(top);
            //top=apilar(top,*caracter);
            e++;
            //linea[i]='X';
            i=0;
        }

        else if(*caracter=='/'&&top->dato!='^')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter=='%'&&top->dato=='^')
        {
            postfija[e]=top->dato;
            printf("\nDATO AGREGADO A POSTFIJA %c",postfija[e]);
            top=desapilar(top);
            //top=apilar(top,*caracter);
            e++;
            //linea[i]='X';
            i=0;
        }

        else if(*caracter=='%'&&top->dato!='^')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter=='^')
        {
            top=apilar(top,*caracter);
            linea[i]='X';
        }

        if(*caracter==')'&&top->dato!='(' || *caracter=='}'&&top->dato!='{' || *caracter==']'&&top->dato!='[')
        {
            postfija[e]=top->dato;
            printf("\nCARACTER AGREGADO A POSTFIJA %c",postfija[e]);
            top=desapilar(top);
            e++;
            i=0;
        }

        else if(*caracter==')'&&top->dato=='(' || *caracter=='}'&&top->dato=='{' || *caracter==']'&&top->dato=='[')
        {
            top=desapilar(top);
            linea[i]='X';
        }

        if(*caracter=='A' || *caracter=='B' || *caracter=='C' || *caracter=='D' || *caracter=='E'  || *caracter=='F'  || *caracter=='G'  || *caracter=='H')
        {
            postfija[e]=*caracter;
            printf("\nDATO AGREGADO A POSTFIJA %c",postfija[e]);
            e++;
            linea[i]='X';
        }
        i++;
    }

    printf("\n\n\tEXPRESION POSTFIJA: %s",postfija);
    leerResultados(postfija);
}

void leerResultados(char expresion[50])
{
    char caracter;
    char *la,*lb,*lc,*ld,*le,*lf,*lg,*lh;
    int i=0;
    char A[4],B[4],C[4],D[4],E[4],F[4],G[4],H[4];
    FILE *f;
    f=fopen("practica1_ev.txt","r");

    if(f==NULL)
        printf("NO EXISTE EL FICHERO");
    else
    {
        for(int i =65;i<90;i++)
        {
         caracter=i;
         if(caracter=='A')
         {
             for(int i = 0; i < 1 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&A);
                    }
                }
         }
         if(caracter=='B')
         {
             for(int i = 1; i < 2 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&B);
                    }
                }
         }
         if(caracter=='C')
         {
             for(int i = 2; i < 3 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&C);
                    }
                }
         }
         if(caracter=='D')
         {
             for(int i = 3; i < 4 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&D);
                    }
                }
         }
         if(caracter=='E')
         {
             for(int i = 4; i < 5 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&E);
                    }
                }
         }
         if(caracter=='F')
         {
             for(int i = 5; i < 6 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&F);
                    }
                }
         }
         if(caracter=='G')
         {
             for(int i = 6; i < 7 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&G);
                    }
                }
         }
         if(caracter=='H')
         {
             for(int i = 7; i < 8 ; i++)
                {
                    if(!feof(f))
                    {
                        fscanf(f,"%s\n",&H);
                    }
                }
         }

        }
        printf("\n\n\tVALORES DE LAS VARIABLES");
        printf("\n%s",A);
        printf("\n%s",B);
        printf("\n%s",C);
        printf("\n%s",D);
        printf("\n%s",E);
        printf("\n%s",F);
        printf("\n%s",G);
        printf("\n%s",H);
    }

    la=&A[2];
    lb=&B[2];
    lc=&C[2];
    ld=&D[2];
    le=&E[2];
    lf=&F[2];
    lg=&G[2];
    lh=&H[2];

     for(int i=0;i<50;i++)
     {
         if(expresion[i]=='A')
         {
             expresion[i]=A[2];
         }

         if(expresion[i]=='B')
         {
             expresion[i]=B[2];
         }

         if(expresion[i]=='C')
         {
             expresion[i]=C[2];
         }

         if(expresion[i]=='D')
         {
             expresion[i]=D[2];
         }

         if(expresion[i]=='E')
         {
             expresion[i]=E[2];
         }

         if(expresion[i]=='F')
         {
             expresion[i]=F[2];
         }

         if(expresion[i]=='G')
         {
             expresion[i]=G[2];
         }

         if(expresion[i]=='H')
         {
             expresion[i]=H[2];
         }
     }

     printf("\n\n\tEXPRESION SUSTITUIDA: %s",expresion);
     evaluacion(expresion);
}

void evaluacion(char expresion[50])
{
    printf("\n\n\tEVALUACION DE LA EXPRESION\n");

    int i=0;
    char *caracter;
    float A;
    float B;
    float C;
    Nodo1 *top;
    top=NULL;

    while(expresion[i]!='\0')
    {
        caracter=&expresion[i];

       /* if(*caracter=='0')
        {
            top=apilar1(top,0);
        }*/

        if(*caracter=='1')
        {
            top=apilar1(top,1);
        }

        if(*caracter=='2')
        {
            top=apilar1(top,2);
        }

        if(*caracter=='3')
        {
            top=apilar1(top,3);
        }

        if(*caracter=='4')
        {
            top=apilar1(top,4);
        }

        if(*caracter=='5')
        {
            top=apilar1(top,5);
        }

        /*if(*caracter=='6')
        {
            top=apilar1(top,6);
        }*/

        if(*caracter=='7')
        {
            top=apilar1(top,7);
        }

        if(*caracter=='8')
        {
            top=apilar1(top,8);
        }

        if(*caracter=='9')
        {
            top=apilar1(top,9);
        }

        if(*caracter=='+')
        {
            A=top->dato;
            top=desapilar1(top);
            B=top->dato;
            top=desapilar1(top);
            C=B+A;
            top=apilar1(top,C);
        }

        if(*caracter=='-')
        {
            A=top->dato;
            top=desapilar1(top);
            B=top->dato;
            top=desapilar1(top);
            C=B-A;
            top=apilar1(top,C);
        }

        if(*caracter=='*')
        {
            A=top->dato;
            top=desapilar1(top);
            B=top->dato;
            top=desapilar1(top);
            C=B*A;
            top=apilar1(top,C);
        }

        if(*caracter=='/')
        {
            A=top->dato;
            top=desapilar1(top);
            B=top->dato;
            top=desapilar1(top);
            C=B/A;
            top=apilar1(top,C);
        }

        if(*caracter=='^')
        {
            A=top->dato;
            top=desapilar1(top);
            B=top->dato;
            top=desapilar1(top);
            C=pow(B,A);
            top=apilar1(top,C);
        }

        i++;
    }

    verPila1(top);
    archivo=fopen("resultados.txt","a");
    fprintf(archivo,"EXPRESION POSTFIJA: %s\n",expresion);
    fprintf(archivo,"RESULTADO: %f\n",top->dato);
}



int main()
{
    printf("\tAPLICACION PARA PASAR EXPRESIONES INFIJAS A EXPRESIONES POSTFIJAS:\n\n");
    leerLineas();
    return 0;
}
