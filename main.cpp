/*CURSO: COMPILADORES
  LABORATORIO N 07: AFD DE UN LENGUAJE DE PROGRAMACION
			 (ANALIZADOR LEXICO)

  DESCRIPCION: AFD para un lenguaje de programacion con las siguientes
		   caracteristicas:
		   *Numeros enteros: digito+
		   *Identificador: letra(letra|digito)*
		   *Asignador:  :=  .... <-
		   *Suma:  +
           *Por: *
		   *Parentesis izquierdo: (
           *Parentesis derecho: )
		   *Punto y coma:  ;

		   *Los espacios en blanco son ignorados

  ENTRADA: Un archivo fuente con lexemas, segun los tokens del lenguaje.
	   Ejm:  A:=(15+45)*2;
		     B:=10*2;
		     C:=A+B;

  SALIDA:  Reconocimiento de los tokens o ERROR segun el caso.
	   Ejm:  Para el caso anterior
		 IDENT
		 ASIG
		 (
		 ENTERO
		 +
		 ENTERO
		 )
		 *
		 ENTERO
		 ;    etc.


  SUGERENCIA: Construir siempre el AFD antes del programa
*/

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

using namespace std;

#define IDENT 300
#define ENTERO 302
#define ASIG 304
#define ERROR -10
int Fila=1;

FILE *Fuente;
int yylex(void)
{
int c;
c=fgetc(Fuente);

while (isspace(c))
  {
  	if (c=='\n')
  	    Fila++;
   c=fgetc(Fuente);
}


//SI ES ENTERO
if (isdigit(c))
  {
  c=fgetc(Fuente);
  while(isdigit(c))
	 c=fgetc(Fuente);
  ungetc(c,Fuente);
  return(ENTERO);
  }

//SI ES IDENTIFICADOR
if (isalpha(c))
   {
   c=fgetc(Fuente);
   while(isalpha(c)||isdigit(c))
	  c=fgetc(Fuente);
   ungetc(c,Fuente);
   return(IDENT);
   }
//SI ES ASIGNADOR
if (c==':')
  {
  c=fgetc(Fuente);
  if (c=='=')
	  return(ASIG);
  ungetc(c,Fuente);
  return(ERROR);
  }

//SI ES MAS
if (c=='+')
    return('+');

if(strchr("*();-",c))    //strchr devuelve verdadero si c esta en la cadena
			  //       sino devuelve falso (cero)
  return(c);

if (c==EOF)
   return(0);
return(ERROR);
}
void EscribeToken(int token)
{
if (token==IDENT)
   cout<<"Token = IDENT"<<endl;
if (token==ENTERO)
   cout<<"Token = ENTERO"<<endl;
if (token==ASIG)
   cout<<"Token = ASIG"<<endl;
if (strchr("+*();",token))
   cout<<"Token ="<<char(token)<<endl;
if (token == ERROR)
   cout<<"ERROR EN FILA "<<Fila<<":"<<endl;
}
int main(void)
{
char NomArch[30];
int token;
cout<<"Ingrese Archivo Fuente a procesar: ";
cin>>NomArch;
Fuente = fopen(NomArch, "rt");
if (Fuente == NULL)
   cout<<"No se puede abrir el archivo";
else
  while (token=yylex())
      EscribeToken(token);
fclose(Fuente);
getch();
}
