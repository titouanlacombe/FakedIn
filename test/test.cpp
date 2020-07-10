#include "mylog.h"
#include "list.h"
#include "company.h"
#include "job.h"
#include "worker.h"
#include "data_base.h"
#include "search.h"

#include <signal.h>
#include <string.h>
#include <iostream>

using namespace std;

int nb_tests = 0; // Number of tests
int nb_tests_passed = 0; // Number of successful tests

#define STRINGIZE_(x) #x
#define STRINGIZE(x) STRINGIZE_(x)

// Increments nb_tests and if successful increments nb_tests_passed
#define TEST(x)           \
	nb_tests++;             \
	if(x)                   \
	{                       \
		nb_tests_passed++;    \
		cout << "[SUCCESS] "; \
	}                       \
	else                    \
	{                       \
		cout << "[FAILURE] "; \
	}                       \
	cout << "Line " STRINGIZE(__LINE__) ", Tested: " STRINGIZE(x) << endl;

// Test if two files are the sames
#define TEST_FILE(a, b)    \
	nb_tests++;              \
	{                        \
		int const r = system("diff --text --strip-trailing-cr " a " " b " > /dev/null");\
		if(!WEXITSTATUS(r))    \
		{                      \
			nb_tests_passed++;   \
			cout << "[SUCCESS] ";\
		}                      \
		else                   \
		{                      \
			cout << "[FAILURE] ";\
		}                      \
		cout << "Line " STRINGIZE(__LINE__) ", Tested files: " STRINGIZE(a) " and " STRINGIZE(b) << endl;\
	}

// Executed function when segfault
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	cout << "[SEGFAULT]" << endl;
	cout << "[RESULTS] " << nb_tests_passed << "/" << nb_tests << " Tests passed" << endl;
	exit(nb_tests_passed - nb_tests);
}

int main()
{
	// Setup of the function to execute when segfault
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	//----------------------TESTS---------------------
	{
		//----------------------MYLOG---------------------
		log_begin("test/output", false);
		log_write("hello!", false);
		log_write("how are you ?", false);
		log_end();
		TEST_FILE("test/output/log.txt", "test/correction/log.txt");
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
		auto l = List<string>();
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
		load("test/input/data_base");
		Worker *w = new Worker("first_name", "full_name", "email@e.com");
		w->set_zip_code("zip");
		save("test/output/data_base");
		TEST_FILE("test/output/data_base/Companies.csv", "test/correction/data_base/Companies.csv");
		TEST_FILE("test/output/data_base/Jobs.csv", "test/correction/data_base/Jobs.csv");
		TEST_FILE("test/output/data_base/Workers.csv", "test/correction/data_base/Workers.csv");
	}

	{
		//----------------------SEARCH---------------------
		auto w = Worker("Max", "Veran", "max.v@gmail.com");
		auto w2 = Worker("Thomas", "Billet", "t.b@gmail.com");
		auto w3 = Worker("Titouan", "Lacombe", "t.l@gmail.com");
		w.add_co_worker(w2);
		w2.add_co_worker(w);
		// test search
	}

	cout << "[RESULTS] " << nb_tests_passed << "/" << nb_tests << " Tests passed" << endl;

	return nb_tests - nb_tests_passed;
}
