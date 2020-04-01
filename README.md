![](https://github.com/thierryseegers/DevCommeLesPros-2020-Projet/workflows/Test%20master/badge.svg)

# DevCommeLesPros-2020-Projet

Modèle de départ pour le projet de programmation à effectuer en groupe de deux ou trois étudiants.
Vous n'êtes pas dans l'obligation de garder exactment les mêmes équipes que pour les exercices précédents.

# Table des matières

- [Objectif](#objectif)
- [Spécifications fonctionelles](#sp%C3%A9cifications-fonctionelles)
    - [Fonctionalités pour une entreprise](#fonctionalit%C3%A9s-pour-une-entreprise)
    - [Fonctionalités pour un chercheur d'emploi](#fonctionalit%C3%A9s-pour-un-chercheur-demploi)
    - [Fonctionalité pour un employé](#fonctionalit%C3%A9-pour-un-employ%C3%A9)
- [Spécifications de conception](#sp%C3%A9cifications-de-conception)
    - [Interface](#interface)
    - [Base de données](#base-de-donn%C3%A9es)
        - [Table d'entreprise](#table-dentreprise)
        - [Table de postes](#table-de-postes)
        - [Table de chercheur d'emploi](#table-de-chercheur-demploi)
        - [Table des employés](#table-des-employ%C3%A9s)
    - [Langage de programmation et paramètres de compilateur](#langage-de-programmation-et-param%C3%A8tres-de-compilateur)
    - [Journal](#journal)
- [Instructions de travail](#instructions-de-travail)
    - [Modules/Bibliothèques](#modulesbiblioth%C3%A8ques)
    - [Tests](#tests)
        - [Tests unitaires et tests d'intégration](#tests-unitaires-et-tests-dint%C3%A9gration)
        - [Intégration continue](#int%C3%A9gration-continue)
    - [Documentation](#documentation)
        - [Documentation pour les ingénieurs](#documentation-pour-les-ing%C3%A9nieurs)
        - [Documentation pour les utilisateurs](#documentation-pour-les-utilisateurs)
    - [Stades de développement](#stades-de-d%C3%A9veloppement)
        - [Pré-alpha](#pr%C3%A9-alpha)
        - [Alpha](#alpha)
        - [Beta](#beta)
        - [Livraison](#livraison)
        - [Support et fonctionalités additionelles](#support-et-fonctionalit%C3%A9s-additionelles)
- [Évaluation](#%C3%A9valuation)
    - [La base de code](#la-base-de-code)
    - [L'application](#lapplication)
    - [La méthode de développement](#la-m%C3%A9thode-de-d%C3%A9veloppement)
- [Les extras](#les-extras)

# Objectif

Le site [LinkedIn](https://linkedin.com) est un réseau social servant de rapprochement et de moyen de contact entre des entreprises, des demandeurs d'emploi et d'anciens collègues travail.
Vous avez à créer un programme qui simule cette plateforme.

Cette application n'est pas un site web.
C'est un programme lancé à l'invite de commandes qui utilisent des fichers locaux comme base de données.

# Spécifications fonctionelles

Sur cette platforme, on distingue trois profils d'utilisateur avec des besoins propres.
Les entreprises, les chercheurs d'emploi et les employés.

## Fonctionalités pour une entreprise

Une entreprise annonce des postes à pourvoir, spécifiant les compétences requises.
Elle peut aussi rechercher parmi les chercheurs d'emploi ceux qui correspondent à ses besoins.

- [ ] Créer un profil
    - [ ] Nom
    - [ ] Code postal
    - [ ] Adresse mail
- [ ] Supprimer un profil
    - [ ] Supprime automatiquement les postes à pourvoir existant
- [ ] Créer le profil d'un poste à pourvoir
    - [ ] Titre
    - [ ] Compétences requises
- [ ] Supprimer le profil d'un poste pourvu
- [ ] Rechercher parmi les chercheurs d'emploi pour des profils qui correspondent à un poste à pourvoir
    - [ ] Recherche par compétences
    - [ ] Recherche par compétences et code postal
    - [ ] Résultats
        - [ ] Nom
        - [ ] Prénom
        - [ ] Adresse mail

## Fonctionalités pour un chercheur d'emploi

Pour un chercheur d'emploi, un bon moyen d'entrer en contact avec une entreprise qui nous intéresse est grâce à une personne que l'on connaît déjà (un(e) ancien(ne) collègue de travail) qui travaille présentement pour cette entreprise.

Lorsqu'un checheur d'emploi est embauché, son profil transitionne vers «employé».

- [ ] Créer un profil
    - [ ] Nom
    - [ ] Prénom
    - [ ] Adresse mail
    - [ ] Code postal
    - [ ] Compétences
    - [ ] Ancien(ne)s collègues de travail parmi les personne employés
- [ ] Modifier un profil
    - [ ] Ajouter des compétences
    - [ ] Ajouter un(e) ancien(ne) collègue de travail
    - [ ] Modifier le code postal
- [ ] Transitionner le profil de «chercheur d'emploi» à un profil «employé»
- [ ] Supprimer un profil
- [ ] Rechercher parmi les les postes à pourvoir qui correspondent à son profil
    - [ ] Recherche par compétences
    - [ ] Recherche par compétences et code postal
    - [ ] Résultats
        - [ ] Titre du poste
        - [ ] Nom de l'entreprise
        - [ ] Adresse mail de l'entreprise
        - [ ] Code postal de l'entreprise
- [ ] Rechercher parmi les anciens collègues
    - [ ] Recherche par entreprise (retoune les ancien(ne)s collègues employés à l'entreprise)
    - [ ] Recherche par compétences (pour les compétences du chercheur d'emploi, retourne les ancien(ne)s collègues employés aux entreprises qui recherchent ces compétences)
    - [ ] Résultats
        - [ ] Nom du (de la) collègue
        - [ ] Prénom du (de la) collègue
        - [ ] Adresse mail du (de la) collègue

## Fonctionalités pour un employé

C'est bien d'être à l'emploi mais pour diverses raisons il peut arriver qu'on veuille quand même s'informer sur les postes à pourvoir pour trouver un travail plus rémunérateur, plus près de chez soi, etc.

Lorsqu'un un employé quitte ou perd son emploi et est en recherche d'emploi, son profil transitionne vers «checheur d'emploi».

- [ ] Créer un profil
    - [ ] Nom
    - [ ] Prénom
    - [ ] Adresse mail
    - [ ] Code postal
    - [ ] Compétences
    - [ ] Ancien(ne)s collègues de travail parmi les personne employés
    - [ ] Entreprise
- [ ] Modifier un profil
    - [ ] Ajouter des compétences
    - [ ] Ajouter un(e) ancien(ne) collègue de travail
    - [ ] Modifier le code postal
    - [ ] Modifier l'entreprise
- [ ] Transitionner le profil «employé» vers «chercheur d'emploi»
    - [ ] Les employé(e)s de l'entreprise quittée s'ajoutent automatiquement à liste des ancien(ne)s collègues de travail
- [ ] Supprimer le profil
- [ ] Rechercher parmi les les postes à pourvoir qui correspondent au profil de l'employé
    - [ ] Recherche par compétences
    - [ ] Recherche par compétences et code postal
    - [ ] Résultats
        - [ ] Titre du poste
        - [ ] Nom de l'entreprise
        - [ ] Adresse mail de l'entreprise
        - [ ] Code postal de l'entreprise
- [ ] Rechercher parmi les anciens collègues
    - [ ] Recherche par entreprise (retoune les ancien(ne)s collègues employés à l'entreprise)
    - [ ] Recherche par compétences (pour les compétences du chercheur d'emploi, retourne les ancien(ne)s collègues employés aux entreprises qui recherchent ces compétences)
    - [ ] Résultats
        - [ ] Nom du (de la) collègue
        - [ ] Prénom du (de la) collègue
        - [ ] Adresse mail du (de la) collègue

# Spécifications de conception

## Interface

Ce programme sera lancé à l'invite de commandes.
L'utilisateur naviguera les divers fonctionalités grâce à une arborescence de menu affichée à l'écran. Quelques exemples :

```
*** Bienvenu sur LuminIn, le site des pros ***

* Menu principal *

Vous êtes :
1. Une entreprise
2. Un employé
3. À la recherche d'un emploi

Votre choix ('q' pour quitter) : 1
```

```
*** Bienvenu sur LuminIn, le site des pros ***

* Menu entreprise *

Vous voulez :
1. Créer le profil de votre entreprise
2. Créer le profil d'un poste à pourvoir
3. Supprimer le profil d'un poste maintenant pourvu
4. Faire une recherche parmi les chercheurs d'emploi

Votre choix ('q' pour quitter, 'p' pour menu précédent) : 
```

## Base de données

La base de données sera constituée de plusieurs fichiers `.csv`.
Un fichier par table.
Les tables de la base de données suivent le même format que la table utilisée dans l'exercice 4 (`groupe.csv`) où les champs sont séparés par des virgules.
Si un champ contient plusieurs valeurs, celles-ci sont séparées par des points-virgules. 

L'application doit pouvoir utiliser une base de données existante.
Les informations dans la base de données persiste entre les utilisations de l'application.
C'est-à-dire qu'elle n'est pas remise à zéro à chaque fois que lancez l'application.

Chaque tuple dans une table est assigné une clé primaire avec un numéro unique dans cette table.
Aussi, certains attributs peuvent être des clés étrangères.

Quelques exemples :

### Table d'entreprise

```
id,nom,code postal,mail
1,Disney,77700,walt@disney.com
2,Google,75009,emplois@google.com
```

### Table de postes

L'attribut `entreprise` est une clé `id` de la table des entreprises.

```
id,titre,competences,entreprise
1,acteur,comedie;gag;1
2,developpeur,C;SQL;Python,2
```

### Table de chercheur d'emploi

L'attribut `collegues` est une liste de clé `id` de la table des employés.

```
id,nom,prenom,mail,code postal,competences,collegues
1,Duck,Donald,donal.duck@canardville.gov,77700,comedie;gag,2
2,Pignon,Francois,pignouf@gmail.com,75020,C;SQL;Python,
```

### Table des employés

L'attribut `collegues` est une liste de clé `id` de la table des employés.
L'attribut `entreprise` est une clé `id` de la table des entreprises.

```
id,nom,prenom,mail,code postal,competences,collegues,entreprise
1,Untel,Michel,m_untel@google.com,13010,C++;Python;,,2
2,Mouse,Mickey,mickey@mickeyville.gov,77700,comedie,3,1
3,Mouse,Minnie,minnie@mickeyville.gov,77700,comedie;chant,2,1
```

> Est-ce qu'on doit «commit»er les fichiers de la base donnée ?

Il vous sera probablement bénéfique, en effet, d'avoir une certaine base de données de départ partagée entre vous. Ne perdez pas trop temps à la remplir. C'est amusant à faire mais les noms d'employé rigolos ne valent pas plus de points.

Par la suite, quand vous testez votre application, si la base de données est modifiée par les tests, elle ne devrait pas être «commit»ée. Car il faut toujours tester à partir du même point.

## Langage de programmation et paramètres de compilateur

Le projet peut être écrit en C ou en C++.

Utilisez les paramètres `-Wall -pedantic -Werror` au moment de compiler.

> `-Werror` ? C'est nouveau.

Oui, ce paramètre transforme les avertissments du compilateur en erreur. 
C'est une façon de se forcer à écouter ce que nous dit le compilateur à propos de code potentiellement incorrect ou dangereux.

## Journal

Le programme devra produire un [journal](https://www.dropbox.com/scl/fi/12l29vxc1v4z74wum6ay3/D-velopper-comme-les-pros.paper?dl=0&rlkey=gbd3b2ajnlo93wz6xvsph5bcu#:uid=877002050135560344832464&h2=D%C3%A9boguer-par-journal) de toute les opérations exécutées.
Les informations dans le journal persistent entre les utilisations de l'application. C'est-à-dire que le fichier servant de journal n'est pas remis à zéro quand vous lancez l'application.

# Instructions de travail

Suivez les instructions de départ et les instructions de travail de l'exercice 4 avec deux exceptions :
1. Vous pouvez travailler en groupe de deux ou trois.
1. La personne qui approuve et fusionne un «Pull Request» ne doit pas être la personne qui a ouvert le «Pull Request».
C'est-à-dire que si Alice pousse sa branche vers GitHub et ouvre un «Pull Request» pour demander de la fusionner à la branche `master`, ce doit être Bob ou Charlie qui approuvera et fusionnera.
Il incombe à Bob ou Charlie de confirmer que les tests ont bien passés sur la machine virtuelle de GitHub.

## Modules/Bibliothèques

Vous serez tentés d'essayer d'écrire ce programme de façon monolithique avec un gros fichier `main.c` qui fait tout.
Résistez à cette tentation !
La collaboration entre vous serait très difficile.

Travaillez ensemble pour déterminez de quels bibliothèques vous aurez besoin ainsi que leurs responsabilités (manipulation des base de données, fonctionalités entreprise/employé/chercheur, interface/menus, documentation, journal, etc.).
Déterminez aussi quels sont les dépendances entre les bibliothèques et quelles sont les fonctions requises des bibliothèques.
Ensuite vous pourez travaillez plus individuellement aux tâches que vous vous serez assignées sachant qui a besoin de quoi.

> Mais si mon module doit appeller une fonction d'une autre module qui n'existe pas encore ?

Rappellez-vous des exercices précédents où vous aviez à implémenter des fonctions «vides».
Ces fonctions ou méthodes s'appellent des [bouchons](https://fr.wikipedia.org/wiki/Bouchon_(informatique)) (ou [stub](https://en.wikipedia.org/wiki/Method_stub) en anglais).
Ces bouchons servent justement à deux choses :

1. Faire en sorte qu'un module A qui dépend de la fonction d'un module B puisse être développé et compilé _comme si_ la fonction était implémentée. 
Bien sûr, au début la fonction retourne une fausse valeur mais on peut continuer le développement du module A quand même en faisant semblant.
2. On peut écrire des tests avant même que la fonction soit implémentée. 
Connaissant la signature d'une fonction et ses responsabilités, on peut écrire des tests qui en vérifient le bon fonctionnement.
Écrire des tests à l'avance est d'ailleurs une très bonne aide pour comprendre à quoi l'implémentation d'une fonction doit répondre : cas généraux, cas spéciaux, cas d'erreurs, etc.

Écrivez une première version de vos bibliothèques avec des fonctions bounchons et publiez-la sur votre dépôt.
Vos coéquipiers pourront dès lors écrirent leur code en appellant ces fonctions.
Même si elle ne font rien, au moins le code compilera.
Écrivez ensuite les tests de vos fonctions et publiez-les.
Finalement, implémentez vos fonctions et publiez-les.

## Tests

Sans tests, vous n'aurez pas confiance ni en votre code ni en votre programme.
En plus du programme qui sera votre application, écrivez en parallèle un autre programme.
Un programme de tests qui rassemblera tout les tests que vous écrirez pour confirmer que vos bibliothèques opèrent correctement.
C'est ce programme de test qui sera lancé par la cible `check` du `makefile`.

> Vous avez mis `false` pour la cible `check` dans le makefile. Du coup, ça nous a fait un échec sur GitHub dès le premier «Pull Request».

Je sais.
C'est pour vous aider à bien faire les choses.
`false` est littéralement un programme qui ne fait que retourner un code d'erreur.
Remplacez `false` par autre chose tout de suite.

> Mais si mon module dépend d'une fonction d'une autre module qui n'est pas encore implémentée ?

Écrivez quand même vos tests quitte à les laisser commentés temporairement !
N'attendez pas que vos coéquipiers aient tout terminé pour commencer à travailler sur votre module.
Vous perdriez un temps précieux.

### Tests unitaires et tests d'intégration

Durant la première phase de développement, les tests que vous écrirez seront plutôt des test unitaires.
C'est-à-dire des tests qui testent les divers modules en isolation.

Une fois que votre application commence à se tenir debout vous pourrez commencer à le tester dans son ensemble, à le lancer à l'invite de commandes et l'utiliser comme un utilisateur lambda le ferait.

### Intégration continue

Tout comme pour les exercices 3 et 4, ce projet est configuré [1] de telle sorte qu'en ouvrant un «Pull Request», GitHub lance une machine virtuelle Ubuntu qui clone votre dépôt et exécute la commande `make check` à l'invite de commande.
De ce fait, assurez-vous que la cible `check` de votre `makefile` dépende de votre programme de test et le lance.

Si la vérification du service d'intégration continu venait à échouer, il vous incombe d'apporter les modifications nécéssaires à votre branch (toujours en faisant `add`, `commit` et `push`) pour rectifier la situation.
Essentiellement, je vous demande de travailler comme pour les exercices 3 et 4 en suivant leurs [instructions de travail](https://github.com/thierryseegers/DevCommeLesPros-2020-Ex4#instructions-de-travail). 
Seulement, cette fois-ci, c'est vous qui écrirez les tests.

[1] Curieux de savoir comment ?
Ouvrez le fichier `.github/workflows/test-pull-request.yml`.
Pour en savoir plus, cliquez [ici](https://help.github.com/en/actions/configuring-and-managing-workflows/configuring-a-workflow).

## Documentation

### Documentation pour les ingénieurs

Votre code doit être bien documenté pour vous-même et vos coéquipiers.
La documentation des fonctions dans les fichiers d'en-tête sert de moyen de communication entre l'auteur de la fonction et ceux qui auront à l'appeller.
La documentation du code à l'intérieur des fonctions sert à qui que ce soit qui aura à entretenir la fonction et à la déboguer.

Un diagramme UML représentant graphiquement les dépendances entre les divers modules est aussi un excellent outil de communication entre les programmeurs.

### Documentation pour les utilisateurs

Modifiez ce `README` que vous lisez présentement et écrivez le manuel d'instructions de votre programme.
Décrivez-y les fonctionalités implémentés ainsi que, peut-être, les erreurs de manipulation à ne pas commettre.
Ce sera le «[tuto](https://fr.wikipedia.org/wiki/Tutoriel)» de votre programme.

Ici, vous pouvez laisser parler votre créativité.
Comment aimeriez-_vous_ qu'on vous apprenne à utiliser ce programme ?
Par exemple, si vous vous sentez des âmes de comédiens, faites un tuto vidéo.

## Phases de développement

L'évolution de votre travail suivra les [stades de développement d'un projet](https://www.dropbox.com/scl/fi/12l29vxc1v4z74wum6ay3/D-velopper-comme-les-pros.paper?dl=0&rlkey=gbd3b2ajnlo93wz6xvsph5bcu#:uid=315118321024319072106121&h2=Stades-de-d%C3%A9veloppement).
Vous devrez qualifier les transitions entre ces étapes dans votre dépôt en utilisant des [tag](https://git-scm.com/book/en/v2/Git-Basics-Tagging)s sur votre branche `master`. 
Un tag est un commit qui ne contient qu'une courte description.
Cette description devra suivre les règles décrites [ici](https://semver.org/lang/fr/).

Pour taguer votre dépôt, faites à l'invite de commandes : `> git tag -a [la-version] -m "Message pour ce tag."`. Par exemple : `> git tag -a 1.0.0-alpha -m "Tout les modules sont à peu près finis. L'application peut être utilisée et est prête à être testée."`

Les tags doivent être «poussés» comme des commits.
Après avoir créé un nouveau tag, faites à l'invite de commandes: `git push origin --tags`.

### Pré-alpha

C'est la première phase de développement.
Dès le départ votre projet est en phase pré-alpha.
Vous pouvez, immédiatement après avoir créé votre nouveau dépôt, le taguer avec `1.0.0-alpha+pre`.

Temps estimé de la phase pré-alpha : quatre à cinq semaines.

### Alpha

Lorsque vos modules sont suffisament implémentés pour que l'application puisse être lancée et utlisée, vous entrez dans la phase alpha.
Il se peut que toutes les fonctionalités ne soient pas toutes implémentées mais il y en a suffisament pour voir si les divers modules interagissent bien entre eux.
À ce stade, il peut rester encore quelques fonctions bouchons.
Taguez votre dépôt `1.0.0-alpha`.

Temps estimé de la phase alpha : une à deux semaines.

### Beta

Quand toutes les fonctionalités sont implémentées mais qu'il reste encore des bogues, vous entrez dans la phase beta.
Taguez votre dépôt `1.0.0-beta`.

À ce stade, testez exhaustivement votre application.
À chaque nouveau bogue découvert, écrivez un nouveau test.
Demandez à vos «compétiteurs» de tester votre application.
Ils seront impitoyables... et c'est ce qu'on veut !

C'est aussi le bon moment de produire la documentation pour l'utilisateur car votre interface est figée et vous savez quelles fonctionalités sont présentes.

Temps estimé de la phase beta : une à deux semaines.

### Livraison

Votre application est complétée et tout fonctionne pour le mieux.
Félicitations !
Cela vous vaut de taguer votre dépôt `1.0.0` et de publier une «release» officielle.
Suivez [ces instructions](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository).

Vous croyez avoir terminé ?
Pas tout à fait...

### Support et fonctionalités additionelles

Vous avez déjà officiellement tagué votre dépôt `1.0.0` mais vous venez de découvrir un ou deux nouveaux bogues ?
Qu'à cela ne tienne, continuez avec `1.0.n` si vous les réparez.

La version `1.0.0` parfaite vous vaudra 18/20.
Allez chercher des points supplémentaires avec les [extras](#les-extras).
À chaque nouvel extra implémenté, incrémentez le numéro de version mineur de votre dépôt. Par exemple `1.1.0`.

# Évaluation

La date d'évaluation est le *vendredi 29 mai à 23:59*. Le code écrit passé cette date ne sera pas considéré.

Votre travail sera évalué sur les points suivants.

## La base de code

- Organisation du code en bibliothèques.
- Organisation du code en fonctions.
- Exhaustivité des tests.
- Documentation du code, inclus le `makefile`.

## L'application

- Convivialité de l'interface.
- Fonctionalités implémentées.
- Bogue(s) présent(s).
- Documentation de l'application.

## La méthode de développement

- Travail régulier, bien réparti dans le temps. (Ne faites pas tout à la dernière minute.)
- Bonne utilisation du service d'intégration continu.
- Respect des instructions de travail.

Vous avez tout bon ?
Ça vaut 18 sur 20.
Comment gagner d'autres points ?
Continuez de lire...

# Les extras

Chacun de ces extras vaut 1 point sur 20.
Il vous permettront donc d'atteindre 19 ou 20 sur 20.

*Ne tentez ces extras que si vous avez atteint l'objectif principal !
Ils ne valent aucuns points si votre programme ne répond pas aux exigences de base décritent dans les [spécifications fonctionnelles](#sp%C3%A9cifications-fonctionelles).*

À chaque extra correctement implémenté, incrémentez la version mineure de votre programme (par ex. «1.1.0» pour le premier extra, «1.2.0» pour le deuxième extra) comme décrit dans la section [Phases de développement](#Phases-de-d%C3%A9veloppement).

Voici une liste d'extras à envisager.
Je les ai mis dans un ordre qui, selon moi, est du plus facile au plus difficile.

1. Un utilisateur, que ce soit une entreprise ou une personne, s'authentifie avec un mot de passe (ne conservez pas le mot de passe en clair dans la table, utilisez une [fonction de hachage](https://fr.wikipedia.org/wiki/Fonction_de_hachage_cryptographique)).
1. Gardez une historique d'emploi pour chaque personne et utilisez cette historique lors des recherche parmi les anciens collègues.
C'est-à-dire «qui travaille *ou a déjà travaillé* à telle ou telle entreprise.
1. Compressez toute la base de données par un codage de Huffman.
Les fichiers sur le disque sont compressés.
Ils sont décompressés en mémoire, modifiés au fil des opérations et au moment de quitter le programme ils sont recompressés et écrit sur le disque.
Les fichiers décompressés n'apparaîssent jamais sur le disque, ni pendant, ni après l'utilisation du programme. 
1. Écrivez un programme de test qui lance votre programme d'application, exécute certaines commandes comme le ferait un utlisateur humain et vérifie que tout s'est bien déroulé et que la base de données contient les bonnes informations.
1. Utilisez une [véritable base de données SQL](https://sqlite.org/cintro.html) plutôt que des fichers `.csv` (cet extra n'est pas compatible avec l'extra 3).

Vous avez une autre idée d'extra ?
Faites-la approuver par votre «[client](thierry.seegers@yahoo.com)» au préalable.