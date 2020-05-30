#include "mylog.h"

// File containing the logs
std::ofstream log_file;

void log_begin(std::string folder)
{
  log_file.open("./" + folder + "/log.txt");
}

void log_write(std::string str)
{
  log_file << str << "\n";
}

void log_end(void)
{
  log_file.close();
}

void load_log()
{
	return;
}
