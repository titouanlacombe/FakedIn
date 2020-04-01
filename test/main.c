#include "groupe.h"

#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nombre total de tests exécutés. 
int tests_executes = 0;
// Pour chaque test qui réussi, cette variable sera incrémentée de 1.
// Le but est de la garder égale à test_executes.
int tests_reussis = 0;

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST(x) tests_executes += 1;    \
				if(x)                   \
				{                       \
					tests_reussis += 1; \
					printf("[SUCCES] ");\
				}                       \
				else                    \
				{                       \
					printf("[ECHEC ] ");\
				}                       \
				printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": " STRINGIZE(x) "\n");

// Fonction à executer lors d'une segmentation fault.
// On imprime les résultats obtenus jusqu'à lors et on arrête immédiatement le programme.
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	printf("[SEGFAULT]\n");
	printf("%d/%d\n", tests_reussis, tests_executes);
	exit(tests_reussis - tests_executes);
}

int main()
{
	// Mise en place de la fonction à exécuter lors d'une segmentation fault.
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	// Lecture de la DB vers une liste en mémoire.
	groupe *g;
	{
		FILE *db = fopen("test/groupe.csv", "r");
		g = g_open(db);
		fclose(db);
	}

	// Tests des fonctiosn g_open et g_size.
	{
		TEST(g != NULL);
		TEST(g_size(g) == 20);
	}

	// Tests de la fonction g_index.
	{
		TEST(strcmp(g_index(g, 1)->nom, "Whiston") == 0);
		TEST(strcmp(g_index(g, 1)->prenom, "Jen") == 0);
		TEST(strcmp(g_index(g, 2)->courriel, "cwelldrake1@wix.com") == 0);
		TEST(strcmp(g_index(g, 3)->telephone, "+55 (654) 251-8634") == 0);
		TEST(strcmp(g_index(g, 19)->adresse, "328 Sunfield Pass") == 0);
		TEST(g_index(g, 20)->amis[0]->index == 1);
	}

	// Tests de la fonction g_friends.
	{
		TEST(g_friends(g, 1, 1) == false);
		TEST(g_friends(g, 1, 2) == false);
		TEST(g_friends(g, 1, 20) == true);
		TEST(g_friends(g, 19, 20) == true);
	}

	// Tests de la fonction g_bestie.
	{
		TEST(g_bestie(g, 1) == 10);
		TEST(g_bestie(g, 10) == 1);
		TEST(g_bestie(g, 3) == -1);
	}

	// Tests de la fonction g_oneway.
	{
		TEST(g_oneway(g, 1, 1) == false);
		TEST(g_oneway(g, 1, 2) == false);
		TEST(g_oneway(g, 1, 10) == false);
		TEST(g_oneway(g, 1, 13) == true);
	}

	// Tests de la fonction g_linked.
	{
		TEST(g_linked(g, 1, 1) == false);
		TEST(g_linked(g, 1, 10) == true);
		TEST(g_linked(g, 1, 12) == false);
		TEST(g_linked(g, 2, 19) == true);
		TEST(g_linked(g, 4, 10) == false);
		TEST(g_linked(g, 4, 11) == true);
	}

	// Tests de la fonction g_distance.
	{
		TEST(g_distance(g, 1, 1) == 0);
		TEST(g_distance(g, 1, 2) == 2);     // 1-20-2
		TEST(g_distance(g, 1, 7) == 3);     // 1-13-5-7
		TEST(g_distance(g, 9, 10) == 4);    // 9-3-13-6-10 
		TEST(g_distance(g, 15, 16) == 5);   // 15-3-13-6-10-16
		TEST(g_distance(g, 1, 8) == -1);
		TEST(g_distance(g, 8, 11) == 2);    // 8-4-11
	}

	// Tests de la fonction g_remove.
	{
		g_remove(g, 12);
		TEST(g_size(g) == 19);
		TEST(g_index(g, 12) == NULL);
		TEST(g_friends(g, 8, 12) == false);
		TEST(g_linked(g, 8, 11) == false);
	}

	printf("%d/%d\n", tests_reussis, tests_executes);

	return tests_executes - tests_reussis;
}
