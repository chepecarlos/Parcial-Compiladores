#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h> 

using namespace std;

class Lexico
{
	char *nombreFichero;
    FILE* entrada;
    int n1;
    int traza;
    
    public:
          Lexico(const char *unNombreFichero, int una_traza=0);
          ~Lexico();
          // primera parte
          string siguienteToken(void);
          int lineaActual(void){return n1; }
          int existeTraza(void){if(traza)return 1; else return 0;}
          void errores(int codigo);
          
          // Segunda arte
          void programa (void);
};

Lexico::~Lexico()
{
     fclose(entrada);
}

Lexico::Lexico(const char *unNombreFichero, int una_traza)
{
     entrada=fopen(unNombreFichero, "rt");
     if((entrada==NULL))
     {
          cout<<"No se puede abrir el archivo"<<endl;
          system("sleep 2");
          exit(-2);
     }
     cout<<"Exito al abir el archivo"<<endl;
     if(una_traza) traza=1;
     else traza = 0;
     n1=1;
}

string Lexico::siguienteToken(void)
{
	 char car;
     string palabra = "";
     string palabra_aux;
     do{
     while((car=(char)fgetc(entrada))!=EOF)
     {
          if(car==' '){ break;}
          if(car=='\t'){ break;}
          if(car=='\n' ){ ++n1; break;}
          if(car=='\''){ 
			  if(palabra == "")
			  palabra = "\'";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}
		  if(car == ';'){
			  if(palabra == "")
			  palabra =";";
			  else
			  fseek(entrada,-1,SEEK_CUR);
			  break;}	  
          palabra_aux = car;
          palabra = palabra + palabra_aux;
    }
	}while(palabra == "");
     
    if(
    palabra == "main" ||
    //palabras reservadas
    palabra == "int" ||
    palabra == "bool" ||
    palabra == "char" ||
    palabra == "printf" ||
    palabra == "scanf" ||
    palabra == "if" ||
    palabra == "else" ||
    palabra == "for" ||
    palabra == "while" ||
    palabra == "do" ||
    palabra == "while" ||
    palabra == "do" ||
    palabra == "return" ||
    palabra == "void" ||
    //separadores
    palabra == "{" ||
    palabra == "}" ||
    palabra == "(" ||
    palabra == ")" ||
    palabra == ";" ||
    //operadores
    palabra == "+" ||
    palabra == "-" ||
    palabra == "/" ||
    palabra == "*" ||
    //asignacion
    palabra == "=" ||
    //especiales
    palabra == "\'" 
     
    ) return palabra;
    else {
		int l = palabra.length(); 
		string es = "Nada";
		for(int i = 0; i < l;i++){
			if( (char)palabra[i] >= '0' and (char)palabra[i] <= '9'){
			if(es == "Nada")
			es = "Numero";
			}
			if((char)palabra[i] >= 'A' and (char)palabra[i] <= 'z' ){
			if(es == "Nada")
			es = "Variable";
			else if(es == "Numero")
			es = "QuienSabe";
			}
		}
		palabra = es;	
        system("sleep 1");
        return palabra;
       }
	return palabra;
}
void Lexico::errores(int codigo){
cout<<"LINEA "<<lineaActual();
cout<<" ERROR SINTACTICO "<<codigo;
switch (codigo)
{
	case 1 :cout<<" :Falta un main "<<endl;break;
	case 2 :cout<<" :Falta un { inicial "<<endl;break;
	}
}


//Segund parte


void Lexico::programa (void){
	string token = siguienteToken();
	if(token == "main"){
		token = siguienteToken();
		if(token == "{"){
			cout<<"programa funcina hasta el momento";
			}
		else
			errores(2);
		}
	else
		errores(1);
	}

int main()
{
  string token;
  Lexico pollo("lila.txt",1);
  if(pollo.existeTraza())
         cout<<"INICIO DE ANALISIS LEXICO"<<endl;
  // pollo.programa();     
  while((token=pollo.siguienteToken()) != "}"){
		cout<<"Token: "<<token<<endl;
		system("sleep 1");
		}
   
  return 0;
}
