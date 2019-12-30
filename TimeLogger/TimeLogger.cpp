// TimeLogger.cpp : Defines the entry point for the application.
//

#include "TimeLogger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

time_t write_time(ofstream &output)
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	output << asctime(timeinfo);

	return rawtime;
}

void commit_message(ofstream &log, string message)
{
	write_time(log);
	log << message;
	log << "\n";
	log.flush();
}

int main()
{
	ofstream log("time_log.txt", ofstream::app);
	string message = "  ";
	string input_line;
	while (1)
	{
		cout << "Enter note: ";
		// read input
		getline(cin, input_line);

		// Figure out what to do with input
		if (input_line.compare("q") == 0)
		{
			cout << "Exiting" << endl;
			log.close();
			exit(0);
		}
		else if (input_line.compare("") == 0)
		{
			commit_message(log, message);
			cout << "Log committed." << endl << endl;
			// reset message
			message = "  ";
		}
		else
		{
			message += input_line + "\n  ";
		}
	}
	return 0;
}
