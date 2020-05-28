#include "network.h"

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

// Compare le contenu de deux fichiers aux chemins a et b avec la commande diff. Incrémente test_reussis si les fichiers sont pareils.
#define TEST_FILE(a, b) tests_executes += 1;                                                \
						{                                                                   \
							int const r = system("diff --text --strip-trailing-cr " a " " b " > /dev/null");    \
							if(!WEXITSTATUS(r))                                             \
							{                                                               \
								tests_reussis += 1;                                         \
								printf("[SUCCES] ");                                        \
							}                                                               \
							else                                                            \
							{                                                               \
								printf("[ECHEC ] ");                                        \
							}                                                               \
							printf(STRINGIZE(__FILE__) ", " STRINGIZE(__LINE__) ": diff --test --strip-trailing-cr " STRINGIZE(a) " " STRINGIZE(b) "\n");   \
						}

// Fonction à executer lors d'une segmentation fault.
// On imprime les résultats obtenus jusqu'à lors et on arrête immédiatement le programme.
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	std::cout << "[SEGFAULT]" << std::endl;
	std::cout << tests_reussis << "/" << tests_executes << std::endl;
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

	{
		//----------------------LIST---------------------
		auto l = List<int>();
		l.addlast(1);
		l.addlast(2);
		l.addlast(3);
		TEST(l.first->data == 1);
		TEST(l.first->next->data == 2);
		TEST(l.first->next->next->data == 3);
		TEST(l.length == 3);
		TEST(l[0] == 1);
		TEST(l[1] == 2);
		TEST(l[2] == 3);
		l.remove(2);
		TEST(l[0] == 1);
		TEST(l[1] == 3);
		TEST(l.length == 2);
		l.remove(1);
		TEST(l[0] == 3);
		l.remove(3);
		TEST(l.first == NULL);
		TEST(l.last == NULL);
	}

	{
		//----------------------COMPANY---------------------
		auto c = Company("SpaceX", "42069", "spacex@gmail.com");
		TEST(c.name == "SpaceX");
		TEST(c.zip_code == "42069");
		TEST(c.email == "spacex@gmail.com");
	}

	{
		//----------------------JOB---------------------
		auto c = Company("SpaceX", "42069", "spacex@gmail.com");
		auto l = List<std::string>();
		auto j = Job("SpaceX", &l, &c);
		TEST(j.name == "SpaceX");
		TEST(j.skills == &l);
		TEST(j.company == &c);
	}

	{
		//----------------------WORKER---------------------
		auto c = Company("SpaceX", "42069", "spacex@gmail.com");
		auto l = List<std::string>();
		auto w = Worker("Max", "Veran", "max.v@gmail.com");
		TEST(w.first_name == "Max");
		TEST(w.last_name == "Veran");
		TEST(w.email == "max.v@gmail.com");
		TEST(w.employed() == false);
		w.set_company(&c);
		TEST(w.employed() == true);
		TEST(w.company == &c);
		w.set_zip_code("234567");
		TEST(w.zip_code == "234567");
		w.add_skill("C");
		// TEST(w.skills->first->data == "C");
		auto w2 = Worker("T", "L", "T.L@gmail.com");
		w.add_colleague(&w2);
		// TEST(w.colleagues->first->data == &w2);
	}

	{
		//----------------------DATA BASE---------------------
		auto lc = List<Company*>();
		auto lj = List<Job*>();
		auto lw = List<Worker*>();
		load(&lc,&lj,&lw,"./data_base");
		save(&lc,&lj,&lw,"./data_base");
		TEST_FILE("test/data_base/Companies.csv","test/correction/Companies.csv");
		TEST_FILE("test/data_base/Jobs.csv","test/correction/Jobs.csv");
		TEST_FILE("test/data_base/Employees.csv","test/correction/Employees.csv");
		TEST_FILE("test/data_base/Seekers.csv","test/correction/Seekers.csv");
	}

	{
		//----------------------NETWORK---------------------
		auto n = Network();
		auto w = Worker("Max", "Veran", "max.v@gmail.com");
		auto w2 = Worker("Thomas", "Billet", "t.b@gmail.com");
		auto w3 = Worker("Titouan", "Lacombe", "t.l@gmail.com");
		w.add_colleague(&w2);
		w2.add_colleague(&w);
		// TEST(n.size() == 0);
		// n.workers->addlast(&w);
		// n.workers->addlast(&w2);
		// n.workers->addlast(&w3);
		// TEST(n.size() == 3);
		TEST(n.linked(&w,&w2));
		TEST(!n.linked(&w,&w3));
	}

	std::cout << tests_reussis << "/" << tests_executes << std::endl;

	return tests_executes - tests_reussis;
}
