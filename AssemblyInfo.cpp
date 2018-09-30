#include "stdafx.h"

#using <mscorlib.dll>

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;

//
// Les informations g�n�rales relatives � un assembly d�pendent de 
// l'ensemble d'attributs suivant. Pour modifier les informations
// associ�es � un assembly, changez les valeurs de ces attributs.
//
[assembly:AssemblyTitleAttribute("")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("")];
[assembly:AssemblyCopyrightAttribute("")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];		

//
// Les informations de version pour un assembly se composent des quatre valeurs suivantes :
//
//      Version principale
//      Version secondaire 
//      Num�ro de build
//      R�vision
//
// Vous pouvez sp�cifier toutes les valeurs ou indiquer des num�ros de r�vision et de build par d�faut 
// en utilisant '*', comme ci-dessous :

[assembly:AssemblyVersionAttribute("1.0.*")];

//
// Pour signer votre assembly, vous devez sp�cifier la cl� � utiliser. Consultez 
// la documentation Microsoft .NET Framework pour plus d'informations sur la signature d'un assembly.
//
// Utilisez les attributs ci-dessous pour contr�ler la cl� utilis�e lors de la signature. 
//
// Remarques�: 
//   (*) Si aucune cl� n'est sp�cifi�e, l'assembly n'est pas sign�.
//   (*) KeyName fait r�f�rence � une cl� install�e dans le fournisseur de
//       services cryptographiques (CSP) de votre ordinateur.
//       KeyFile fait r�f�rence � un fichier qui contient une cl�.
//   (*) Si les valeurs KeyFile et KeyName sont sp�cifi�es, le 
//       traitement suivant se produit�:
//       (1) Si KeyName se trouve dans le CSP, cette cl� est utilis�e.
//       (2) Si KeyName n'existe pas mais que KeyFile existe, la cl� 
//           de KeyFile est install�e dans le CSP et utilis�e.
//   (*) Pour cr�er KeyFile, vous pouvez utiliser l'utilitaire sn.exe (Strong Name).
//        Lors de la sp�cification de KeyFile, son emplacement doit
//        �tre relatif au r�pertoire du projet.
//   (*) DelaySign (Signature diff�r�e) est une option avanc�e. Pour plus d'informations, consultez la
//       documentation Microsoft .NET Framework.
//
[assembly:AssemblyDelaySignAttribute(false)];
[assembly:AssemblyKeyFileAttribute("")];
[assembly:AssemblyKeyNameAttribute("")];

