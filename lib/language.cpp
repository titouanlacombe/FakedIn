#include "language.h"
#include "list.h"

#include <cstring>

using namespace std;

char** lang_array = NULL;
int array_size = 0;

void load_language(string path)
{
	ifstream lang_file;
	lang_file.open(path);
	array_size = 0;
	
	string line;
	List<string> lines;
	while (getline(lang_file, line))
	{
		lines.addlast(new string(line));
		array_size++;
	}	
	lang_file.close();

	lang_array = (char**)malloc(array_size * sizeof(char*));

	auto it = lines.first();
	for (int i = 0; i < array_size; i++)
	{
		string tmp = * *it;
		char *char_array = (char*)malloc((tmp.length() + 1) * sizeof(char));
		strcpy(char_array, tmp.c_str());
		lang_array[i] = char_array;
		it++;
	}
}

string get_phrase(int n)
{
	if (n > array_size) return "Error: language data number " + to_string(n) + " not provided";
	else return lang_array[n - 1];
}
