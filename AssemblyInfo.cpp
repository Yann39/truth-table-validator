#include "stdafx.h"

#using <mscorlib.dll>

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;

//
// Les informations générales relatives à un assembly dépendent de 
// l'ensemble d'attributs suivant. Pour modifier les informations
// associées à un assembly, changez les valeurs de ces attributs.
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
//      Numéro de build
//      Révision
//
// Vous pouvez spécifier toutes les valeurs ou indiquer des numéros de révision et de build par défaut 
// en utilisant '*', comme ci-dessous :

[assembly:AssemblyVersionAttribute("1.0.*")];

//
// Pour signer votre assembly, vous devez spécifier la clé à utiliser. Consultez 
// la documentation Microsoft .NET Framework pour plus d'informations sur la signature d'un assembly.
//
// Utilisez les attributs ci-dessous pour contrôler la clé utilisée lors de la signature. 
//
// Remarques : 
//   (*) Si aucune clé n'est spécifiée, l'assembly n'est pas signé.
//   (*) KeyName fait référence à une clé installée dans le fournisseur de
//       services cryptographiques (CSP) de votre ordinateur.
//       KeyFile fait référence à un fichier qui contient une clé.
//   (*) Si les valeurs KeyFile et KeyName sont spécifiées, le 
//       traitement suivant se produit :
//       (1) Si KeyName se trouve dans le CSP, cette clé est utilisée.
//       (2) Si KeyName n'existe pas mais que KeyFile existe, la clé 
//           de KeyFile est installée dans le CSP et utilisée.
//   (*) Pour créer KeyFile, vous pouvez utiliser l'utilitaire sn.exe (Strong Name).
//        Lors de la spécification de KeyFile, son emplacement doit
//        être relatif au répertoire du projet.
//   (*) DelaySign (Signature différée) est une option avancée. Pour plus d'informations, consultez la
//       documentation Microsoft .NET Framework.
//
[assembly:AssemblyDelaySignAttribute(false)];
[assembly:AssemblyKeyFileAttribute("")];
[assembly:AssemblyKeyNameAttribute("")];

