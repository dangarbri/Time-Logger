// TimeLogger.cpp : Defines the entry point for the application.
//

#include "TimeLogger.h"
#include "Log.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

const string LOG_FILE_NAME = "time_log.txt";
const string PROMPT_MESSAGE = "Enter note: ";

/**
 * Pretty prompt for user interface
 */
void print_prompt(bool continuation)
{
	if (!continuation)
	{
		cout << PROMPT_MESSAGE;
	}
	else
	{
		// If continuing a note, don't print the message again,
		// just indent so it's clear it's the same note.
		cout << string(PROMPT_MESSAGE.length(), ' ');
	}
}

int main()
{
#ifdef DEBUG
	cout << "Running in debug mode" << endl;
#endif

	Log logger(LOG_FILE_NAME);
	string message = "  ";
	string input_line;
	bool continuing_note = false;
	while (1)
	{
		print_prompt(continuing_note);

		// read input
		getline(cin, input_line);

		// Figure out what to do with input
		if (input_line.compare("q") == 0)
		{
			cout << "Exiting" << endl;
			break;
		}
		else if (input_line.compare("s") == 0)
		{
#ifdef DEBUG
			cout << "Saving..." << endl;
#endif

			logger.Flush();
			cout << "Saved to disk" << endl << endl;
		}
		else if (input_line.compare("") == 0)
		{
			logger.Write(message);
			cout << "Got it. There are " << logger.GetBufferedLogCount() << " logs pending. Enter 's' to flush to disk" << endl;

			// reset message and state
			message = "  ";
			continuing_note = false;
		}
		else
		{
			message += input_line + "\n  ";
			continuing_note = true;
		}
	}
	return 0;
}
