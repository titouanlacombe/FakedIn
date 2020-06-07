#include "UI.h"

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
		//----------------------MYLOG---------------------
		log_begin("test/logs");
		log_write("salut!");
		log_write("ca va ?");
		log_end();
		// TEST_FILE("test/log.txt","test/log_correction.txt");
	}

	{
		//----------------------LIST---------------------
		auto l = List<int>();
		l.addlast(1);
		l.addlast(2);
		l.addlast(3);
		TEST(l.first_n->data == 1);
		TEST(l.first_n->next->data == 2);
		TEST(l.first_n->next->next->data == 3);
		TEST(l.length == 3);
		TEST(l[0] == 1);
		TEST(l[1] == 2);
		TEST(l[2] == 3);
		l.remove(2);
		auto it = l.first();
		TEST(*it == 1);
		it++;
		TEST(*it == 3);
		TEST(l.length == 2);
		l.remove(1);
		TEST(l[0] == 3);
		l.remove(3);
		TEST(l.first_n == NULL);
		TEST(l.last_n == NULL);
		l.addlast(1);
		l.addlast(6);
		l.addlast(7);
		l.addlast(2);
		l.addlast(3);
		l.addlast(8);
		l.addlast(9);
		l.addlast(5);
		l.addlast(10);
		l.addlast(4);
		l.sort();
		TEST(l[0] == 1);
		TEST(l[1] == 2);
		TEST(l[2] == 3);
		TEST(l[3] == 4);
		TEST(l[4] == 5);
		TEST(l[5] == 6);
		TEST(l[6] == 7);
		TEST(l[7] == 8);
		TEST(l[8] == 9);
		TEST(l[9] == 10);
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
		auto j = Job("SpaceX", &c);
		TEST(j.title == "SpaceX");
		TEST(j.skills.length == 0);
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
		TEST(w.skills.first_n->data == "C");
		auto w2 = Worker("T", "L", "T.L@gmail.com");
		w.add_co_worker(w2);
		TEST(w.co_workers.first_n->data == &w2);
	}

	{
		//----------------------DATA BASE---------------------
		Worker w;
		auto lc = List<Company*>();
		auto lj = List<Job*>();
		auto lw = List<Worker*>();
		load(lc, lj, lw, "test/in");
		w = Worker("first_name", "full_name", "email@e.com");
		w.set_zip_code("zip");
		lw.addlast(&w);
		save(lc, lj, lw, "test/out");
		TEST_FILE("test/out/Companies.csv", "test/correction/Companies.csv");
		TEST_FILE("test/out/Jobs.csv", "test/correction/Jobs.csv");
		TEST_FILE("test/out/Employees.csv", "test/correction/Employees.csv");
		TEST_FILE("test/out/Seekers.csv", "test/correction/Seekers.csv");
	}

	{
		//----------------------SEARCH---------------------
		auto w = Worker("Max", "Veran", "max.v@gmail.com");
		auto w2 = Worker("Thomas", "Billet", "t.b@gmail.com");
		auto w3 = Worker("Titouan", "Lacombe", "t.l@gmail.com");
		w.add_co_worker(w2);
		w2.add_co_worker(w);
		//test des searchs
	}

	std::cout << tests_reussis << "/" << tests_executes << std::endl;

	return tests_executes - tests_reussis;
}
