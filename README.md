CALCULATEUR DE CRIBLES
======================


le calculateur de cribles est un logiciel utilisable sur terminal permettant de composer des groupes comme le faisait Xénakis

la fonction de XEN 
------------------

3(1) = 1, 4, 7, 10... -> c(3,1)

la syntaxe de XEN :
-------------------

- x union y -> a(x,y)

- x inter y -> i(x,y)

- non x -> n(x)


d'ou : 3(1) + ( 3(2) inter 3(4) ) -> a( c(3,1), i(c(3,2), c(3,4)))

la formule donnée dans l'article sur la théorie des cribles de iannis-xenakis.org s'écrit : 

a(i( n(a(  a(a(c(13, 3), c(13,5)) ,c(13,7)), c(13, 9))), c(11,2)),a(i(n(a(c(11, 4), c(11, 8))), c(13, 9)), a(c(13, 0), a(c(13,1), c(13, 6)))))

les espaces sont tolérés

Bibliographie 
-------------

https://www.iannis-xenakis.org/theorie-des-cribles/ 

http://recherche.ircam.fr/equipes/repmus/moreno/AndreattaENSTBretagne2005.pdf



ChangeLog
---------

XEN 1.2 :

- refonte du parsing et de l'AST (arbres.c)

Il n'y a normalement plus de cas dans lequel le programme pourrait crasher. 

- ajout du tutoriel

XEN 1.3 :

- refonte de logic.c avec complexité O(n)

- correction bug sur un type d'erreur de parenthèses

XEN 1.4 alpha : 

- ajout de la fonction m() (musique) pour l'affichage en notes
  
- ajout de la fonction s() (shifting) pour le décalage des listes

La fonction m() et s() apportent des bugs innhérents à leurs fonctionnement:

- erreur d'affichage des octaves > 20

- le shifting negatif n'est pas comptabilisé

ces bugs seront corrigés dans une version 1.4

