#include "mylog.h"

#include <sys/stat.h>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
#include <iostream>

std::ofstream log_file; // File containing the logs
time_t start; // Time of start of loging

void log_begin(std::string folder, bool automated_file_name)
{
	check_folder(folder);
	if (automated_file_name) log_file.open("./" + folder + "/log " + get_time_str() + ".txt");
	else log_file.open("./" + folder + "/log.txt");
	time(&start);
}

void log_write(std::string str, bool automated_line_prefix)
{
	time_t elapsed = time(NULL) - start;
	if (automated_line_prefix) log_file << "[" << get_time_str(false, &elapsed) << "]: " << str << std::endl;
	else log_file << str << std::endl;
}

void log_end(void) {log_file.close();}

std::string get_time_str(bool longstr, time_t *elapsed)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  if (elapsed) rawtime = *elapsed;
  else time(&rawtime);
	
  timeinfo = localtime(&rawtime);

  if (longstr) strftime(buffer, sizeof(buffer), "%d-%m-%Y %H;%M;%S", timeinfo);
	else strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
  std::string str(buffer);

	return str;
}

void dump_str(std::string s)
{
  for (unsigned int n = 0; n < s.length(); n++)
  {
    char c = s[n];
    std::cout << (int)c << ",";
  }
  std::cout << "\n";
}

int mygetline(std::string& s, std::string& dest, char limit)
{
	int i = 0;
	auto it = s.begin();
	dest = "";
	while (it != s.end() && *it != limit)
	{
		dest += *it;
		it++;
		i++;
	}
	s.erase(0, i+1);
	return i;
}

inline bool path_exist(const std::string& path)
{
  struct stat buffer;
  return (stat(path.c_str(), &buffer) == 0);
}

void check_folder(std::string folder)
{
	if (!path_exist(folder)) system(("mkdir -p " + folder).c_str());
}
