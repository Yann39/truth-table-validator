// Il s'agit du fichier projet principal pour le projet d'application VC++ 
// généré en utilisant un Assistant Application.

#include "stdafx.h"
#include "stdio.h"
#include "string.h"

using namespace System;

//=====================================================
//======== Calcul de la puissance d'un nombre =========
//=====================================================
double Puiss(int n, int p) {
  double result=1;
  if (p==0)
	  return 1;
  if (p<0) {
	  double v;
	  for (p; p<0; p++) {
		  result = result * n;
	  }
	  v=1/result;
	  return v;
  }
  for (p;p>0;p--) {
	  result = result * n;
  }
  return result;
}


//=====================================================
//=== Calcul les valeurs des noeuds et de la sortie ===
//=====================================================
int* EvalCircuit(int* circuit, int* entrees) {
	int lg=0, derElem=0, cpt=0, ajout=0, i=0, elem=0;
	_asm {
		//charge les tableaux
		mov esi,circuit
		mov edi,entrees
		//calcul de la taille du tableau circuit
		mov eax,[esi+4]
		mov ebx,3
		mul ebx
		add eax,2
		mov lg,eax
		//calcul de l'indice du dernier elem en octet
		mov ebx,4
		mul ebx
		sub eax,4
		mov derElem,eax		
		//boucle for
		bclfor:
			//regarde si la sortie est toujours indéfinie
			mov eax,derElem
			cmp [edi+eax],2
			jne fini
			//initialise le compteur
			sub eax,16
			mov cpt,eax
			//Boucle for imbriquée
			bclforimbr:
				//Tant qu'on est pas a la fin du tableau
				mov edx,ajout
				cmp edx,cpt
				jg recommence
				//Regarde si les 2 entrées sont à 0 ou à 1
				cmp [edi+8],1
				jg passe
				jle unouzero
				unouzero:
					cmp [edi+12],1
					jg passe
					jle nand
				//c'est le cas donc on fait le nand
				nand:
					//Récupère les 2 entrées
					mov eax,[edi+8]
					mov ebx,[edi+12]
					//fait un ET
					and eax,ebx
					//inverse la sortie
					cmp eax,1
					je eax0
					jl eax1
					eax0:
						mov eax,0
						jmp eaxcont
					eax1:
						mov eax,1
					eaxcont:
					mov [edi+16],eax
					//Récupère le n° de la sortie et sa valeur
					mov eax,[esi+16]
					mov ebx,[edi+16]
					//Retourne à l'indice 0
					sub esi,ajout
					sub edi,ajout
					//initialise le compteur
					mov edx,8
					//boucle qui remplace chaque valeur
					bclforemp:	
						cmp edx,derElem
						jg ajouter
						cmp [esi+edx],eax
						jne continu
						mov [edi+edx],ebx
						continu:
							add edx,4
					jmp bclforemp
				ajouter:
					add esi,ajout
					add edi,ajout
				passe:
					//incrémente les pointeurs et les variables
					add esi,12
					add edi,12
					add ajout,12
			jmp bclforimbr
		recommence:
			sub esi,ajout
			sub edi,ajout
			mov ajout,0
		jmp bclfor
		//Rempli le tableau de sortie
		fini:
			sub edi,ajout
			mov ecx,0
			bclret:
				cmp ecx,derElem
				jg stop
				mov eax,[edi+ecx]
				mov elem,eax
				} entrees[i]=elem; _asm {
				add ecx,4
				inc i
			jmp bclret
		stop:
	}
	return entrees; 
}

//=====================================================
//===== Retourne les sorties ou noeuds du circuit =====
//=====================================================
int* TrouverSorties(int* tab, int i_lg) {
	int cpt=0;
	for(int i=4;i<i_lg;i=i+3)
		cpt++;
	int* sorties = (int*)malloc(cpt*sizeof(int));
	if(sorties==NULL) {
		printf("\nECHEC ALLOCATION MEMOIRE !\n");
		exit(1);
	}
	int j=0;
	for(int i=4;i<i_lg;i=i+3) {
		sorties[j]=tab[i];
		j++;
	}
	sorties[j]='\0';
	return sorties;
	free(sorties);
}
//=====================================================
//========== Retourne les entrées du circuit ==========
//=====================================================
int* TrouverEntrees(int* tab, int* sorties, int i_lg) {
	int* entrees = (int*)calloc(i_lg-3,sizeof(int));
	if(entrees==NULL) {
		printf("\nECHEC ALLOCATION MEMOIRE !\n");
		exit(1);
	}
	int k=0;
	bool vrai = false;
	for(int i=2;i<i_lg;i++) {
		vrai = true;
		//Regarde si le nb est dans le tableau des sorties
		for(int j=0;j<tab[1];j++) {
			if(tab[i] == sorties[j]) {
				vrai = false;
			}
		}
		//Regarde si le nb n'est pas deja dans le tableau des entrees
		for(int j=0;j<tab[0];j++) {
			if(tab[i] == entrees[j]) {
				vrai = false;
			}
		}
		//On stock l'entrée dans le tableau
		if(vrai==true) {
			entrees[k]=tab[i];
			k++;
		}
	}
	//on réallou juste l'espace nécessaire
	entrees = (int*)realloc(entrees,k*sizeof(int));
	entrees[k]='\0';
	return entrees;
	free(entrees);
}


//=====================================================
//========== Vérifie l'integrite du circuit ===========
//=====================================================
char** VerifierCircuit(char* chaine, int* tab, int i_lg) {
	char** msg = (char**)calloc(13,sizeof(char*));
	if(msg==NULL) {
		printf("\nECHEC ALLOCATION MEMOIRE !\n");
		exit(1);
	}
	int pos=0, compt=0;
	bool ckent=true, trouve=false;
	msg[pos] = "\nLes donnees ont ete generees avec succes !\n";
	//Vérifie que la chaine saisie ne commence pas par une virgule
	if (chaine[0]==',') {
			msg[pos] = "******\nErreur : Impossible de commencer par une virgule !\n******";
			pos++; ckent=false;
	}
	//Vérifie que la chaine saisie ne se termine pas par une virgule
	if (chaine[strlen(chaine)-1]==',') {
			msg[pos] = "******\nErreur : Impossible de terminer par une virgule !\n******";
			pos++;
	}
	for (int i=0;i<(int)strlen(chaine);i++)	{
		//Vérifie si la chaine saisie ne comporte pas 2 virgule à la suite
		if((chaine[i] == ',')&&(chaine[i+1] == ',')) {
			msg[pos] = "******\nErreur : deux virgules se suivent !\n******";
			pos++;
			break;
		}
		//Vérifie si tous les caractères saisis sont des chiffres ou des virgules
		if ((chaine[i] < '0' || chaine[i] > '9') && chaine[i] != ',') {
			msg[pos] = "******\nErreur : vous ne pouvez saisir que des chiffres ou des virgules !\n******";
			pos++;
			break;
		}
	}
	//Vérifie si au moins 5 valeurs ont été saisies
	if(i_lg<5) {
		msg[pos] = "******\nErreur : Saisissez au moins 5 valeurs !\n******";
		pos++;
	}
	//Vérifie si au moins une porte et une entrée ont été saisies
	if((tab[0]==0 || tab[1]==0)&& (ckent==true)) {
		msg[pos] = "******\nErreur : Le circuit doit avoir au moins une entree et une porte !\n******";
		pos++;
	}
	for (int i=2; i<i_lg-2; i=i+3) {
		//Vérifie si la sortie d'une porte n'est pas reliée à une de ses entrées
		if(((tab[i+2]==tab[i])||(tab[i+2]==tab[i+1]))&&(ckent==true)) {
			msg[pos] = "******\nErreur : Impossible de relier la sortie d'une porte a une de ses entrees !\n******";
			pos++;
			break;
		}
		//Vérifie si 2 portes n'ont pas la même sortie
		for (int j=4;j<i_lg;j=j+3)
			if((tab[i+2]==tab[j]) && (j!=i+2) && (ckent==true)) {
				msg[pos] = "******\nErreur : Impossible d'avoir une meme sortie pour 2 portes differentes !\n******";
				pos++; ckent=false;
				break;
			}
		//Vérifie si la sortie du circuit n'est pas réutilisée
		if(((tab[i]==tab[i_lg-1])||(tab[i+1]==tab[i_lg-1]))&&(ckent==true)) {
			msg[pos] = "******\nErreur : La sortie du circuit ne peut pas etre reutilisee !\n******";
			pos++; ckent=false;
			break;
		}
	}
	//Vérifie si toutes les sorties des portes sont utilisée mis à part la sortie du circuit
	if (i_lg>5) {
		for (int i=4; i<i_lg-1; i=i+3) {
			trouve = false;
			for (int j=2; j<i_lg; j=j+3) {
				if((tab[i]==tab[j])||(tab[i]==tab[j+1]))
					trouve=true;
			}
			if(trouve==false) {
				msg[pos] = "******\nErreur : Une ou plusieurs sorties sont inutilisees !\n******";
				pos++;
				break;
			}
		}
	}
	//Vérifie que les valeurs rentrées ne dépassent pas une certaine limite
	for(int i=0;i<i_lg;i++){	
		if(tab[i]>=1000) {
			msg[pos] = "******\nErreur : Veuillez saisir des nombres inferieurs a 1000 !\n******";
			pos++; ckent=false; break;
		}
	}
	//Vérifie le nombre de portes et le nombre d'entrées
	if((tab[0]!=0)&&(tab[1]!=0)&&(i_lg>4)) {
		if (ckent==true) {
			int* sorties = TrouverSorties(tab,i_lg);
			int* entrees = TrouverEntrees(tab,sorties,i_lg);
			//Vérifie que le nombre de portes indiquées correspond bien au nombre de portes reel
			for(int i=0;sorties[i]!='\0';i++)
				compt++;
			if(compt != tab[1]) {
				msg[pos] = "******\nErreur : Le nombre de portes saisies ne correspond pas au nb de portes reel !\n******";
				pos++; ckent=false;
			}
			//Vérifie que le nombre d'entrées indiquées correspond bien au nombre d'entrées reel
			compt=0;
			for(int i=0;entrees[i]!='\0';i++)
				compt++;
			if(compt != tab[0] && ckent==true) {
				msg[pos] = "******\nErreur : Le nombre d'entrees saisies ne correspond pas au nb d'entrees reel !\n******";
				pos++;
			}
		}
	}
	return msg;
	free(msg);
}

//=====================================================
//============ Affiche la table de vérité =============
//=====================================================
void AfficherTable(int* tab,int* entrees,int nbElem) {
	bool cbon=false;
	//initialise le tableau avec des valeurs différentes de 1 ou 0
	int* valEntrees = (int*)malloc(nbElem*sizeof(int));
	if(valEntrees==NULL) {
		printf("\nECHEC ALLOCATION MEMOIRE !\n");
		exit(1);
	}

	//rempli un tableau d'entiers de 0 à 2^nbentrees
	int p = (int)Puiss(2,tab[0]);
	int* tab2 = (int*)malloc(p*sizeof(int));
	if(tab2==NULL) {
		printf("\nECHEC ALLOCATION MEMOIRE !\n");
		exit(1);
	}
	for(int i=0;i<p;i++)
		tab2[i]=i;

	//Affiche l'entête de la table de vérité
	printf("\n\nTable de verite du circuit :\n\n");
	for(int k=0;k<tab[0];k++) {
		printf("%d ",entrees[k]);
	}
	printf("| %d\n\n",tab[nbElem-1]);

	for(int j=0;j<p;j++) {
		char* bin = (char*)malloc(tab[0]*sizeof(char));
		if(bin==NULL) {
			printf("\nECHEC ALLOCATION MEMOIRE !\n");
			exit(1);
		}
		bin[tab[0]]='\0';
		//rempli valEntrees avec des 2
		for(int i=0;i<nbElem;i++) {
			valEntrees[i]=2;
		}
		//Transforme chaque valeur en binaire
		itoa(tab2[j],bin,2);
		for(int m=tab[0];m>0;m--) {
		if((int)strlen(bin)<tab[0])
			for(int l=tab[0];l>0;l--) {
				bin[l]=bin[l-1];
				bin[l-1]='0';
			}
		}
		for(int l=0;l<tab[0];l++) {
			for(int k=2;k<nbElem;k++) {
				if (tab[k]==entrees[l])
					valEntrees[k]=bin[l]-48;
			}
		}
		for(int n=2;n<nbElem;n=n+3)
			if((valEntrees[n]==0 || valEntrees[n]==1)&&(valEntrees[n+1]==0 || valEntrees[n+1]==1)) {
				cbon=true;
			}
		if(cbon==false){
			printf("******\nErreur : Aucunes valeur de porte n'a pu etre calculer, verifiez votre circuit !\n******\n\n");
			exit(1);
		}
		for(int k=0;k<tab[0];k++) {
			printf("%d ",bin[k]-48);
		}

		int* resultat = EvalCircuit(tab,valEntrees);
		printf("| %d\n",resultat[nbElem-1]);
		//free(bin);
	}
	free(valEntrees);
	free(tab2);
}

//=====================================================
//=================== Fonction Main ===================
//=====================================================
int main() {
	while(true) {
		char* chaine = (char*)malloc(100*sizeof(char));
		if(chaine==NULL) {
			printf("\nECHEC ALLOCATION MEMOIRE !\n");
			exit(1);
		}
		int cpt = 0, nbvirg = 0;

		printf("Saisissez votre circuit :");
		scanf("%s",chaine);

		int taille=strlen(chaine);

		//on compte combien de virgules il y a dans tab
		for(int i=0;i<taille;i++)
			if(chaine[i]==',')
				nbvirg++;

		//on rempli un tableau de int
		int* tab = (int*)calloc(nbvirg+1,sizeof(int));
		if(tab==NULL) {
			printf("\nECHEC ALLOCATION MEMOIRE !\n");
			exit(1);
		}
		for (int i=0;i<taille;i++) {		
			if(chaine[i] != ',') {
				tab[cpt]=(tab[cpt]*10)+(int)chaine[i]-48;
			}
			else cpt++;
		}
		int nbElem = cpt+1;
		
		//On récupère les éventuels messages d'erreur
		char** message = VerifierCircuit(chaine,tab,nbElem);
		
		//On affiche les messages récupérés
		int p=0;
		while (message[p]!=0){
			printf("%s\n",message[p]);
			p++;
		}
		//On calcul la solution seulement si il n'y a pas d'erreurs dans la saisie du circuit
		if(*message[0] != '*') {
			printf("*********************** START ***********************\n");
			printf("Le circuit comporte %d entree(s) et %d porte(s).\n",tab[0],tab[1]);

			//Créé et affiche un tableau de int contenant les sorties
			int* sorties = TrouverSorties(tab,nbElem);
			printf("Les %d noeuds/sorties sont : ",tab[1]);
			for (int l=0;l<tab[1];l++)
				printf("%d ",sorties[l]);

			//Créé et affiche un tableau de int contenant les entrées
			int* entrees = TrouverEntrees(tab,sorties,nbElem);
			printf("\nLes %d entrees sont : ",tab[0]);
			for (int l=0;l<tab[0];l++)
				printf("%d ",entrees[l]);

			//Affiche la table de vérité
			AfficherTable(tab,entrees,nbElem);
		}
		printf("\n");
		printf("************************ END ************************\n");
		free(chaine);
		free(tab);
	}
}
