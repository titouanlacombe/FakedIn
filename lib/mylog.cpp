#include "mylog.h"

// File containing the logs
std::ofstream log_file;

std::string get_time_str(bool longstr = true)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  if (longstr) strftime(buffer, sizeof(buffer), "%d-%m-%Y %H;%M;%S", timeinfo);
	else strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
  std::string str(buffer);

	return str;
}

void log_begin(std::string folder) {log_file.open("./" + folder + "/log " + get_time_str() + ".txt");}

void log_write(std::string str) {log_file << "[" << get_time_str(false) << "]: " << str << std::endl;}

void log_end(void) {log_file.close();}

void load_log() {return;}
