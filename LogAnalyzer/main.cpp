/**
 * Entry point to the log analyzer
 */

#include <iostream>
#include <fstream>
#include "TimeUtils.h"
#include "constants.h"

using namespace std;

bool are_args_valid(int argc, char** argv)
{
#ifdef DEBUG
	cout << "Arg count is " << argc << endl;
#endif
    /**
     * Arg count has to have 2. Cmd itself + log file
     */
    if (argc < 2)
    {
        return false;
    }

    return true;
}

void print_usage(void)
{
    cout << "This program prints some information retrieved from the given log file" << endl;
    cout << endl;
    cout << "LogAnalyzer <log_file>";
}

int calculate_time_logged(ifstream &fp)
{
	string line;
	time_t total_time = 0;
	time_t start_time;
	while (!fp.eof())
	{
		getline(fp, line);
#ifdef DEBUG
		cout << "Current line: " << line << endl;
#endif
		// Check if line is a session marker
		if (line.find(SESSION_MARKER) == 0)
		{
#ifdef DEBUG
			cout << "Found session marker" << endl;
#endif
			// It is a session marker, check if it's a start or end marker
			if (line.find(SESSION_START_MESSAGE) != string::npos)
			{
#ifdef DEBUG
				cout << "Marker is a start marker" << endl;
#endif
				int offset = SESSION_MARKER.length() + SESSION_START_MESSAGE.length();
				string ascii_time = line.substr(offset);
				// Store the start time of a session to get the difference later.
				start_time = TimeUtils::AsctimeToTime(ascii_time);
#ifdef DEBUG
				cout << "Start time is " << start_time << endl;
#endif
			}
			else if (line.find(SESSION_END_MESSAGE) != string::npos)
			{
#ifdef DEBUG
				cout << "Marker is an end marker" << endl;
#endif
				int offset = SESSION_MARKER.length() + SESSION_END_MESSAGE.length();
				string ascii_time = line.substr(offset);
				// Get session end time.
				time_t end_time = TimeUtils::AsctimeToTime(ascii_time);
#ifdef DEBUG
				cout << "End time is " << end_time << endl;
#endif

				// Add this sessions delta to the total time.
				total_time += end_time - start_time;
			}
		}
	}
	fp.close();

	return total_time;
}

/**
 * Prints the given time_t as hours, minutes, and seconds
 * in the form "HH:MM:SS"
 */
void print_time(time_t time)
{
	int minutes = time / 60;
	int seconds = time % 60;
	int hours = minutes / 60;
	minutes = minutes % 60;

	printf("%02d:%02d:%02d", hours, minutes, seconds);
}

int main(int argc, char** argv)
{
    if (!are_args_valid(argc, argv))
    {
		print_usage();
        return 0;
    }

    ifstream log_file(argv[1], ifstream::in);
    if (log_file.is_open())
    {
		int time_logged = calculate_time_logged(log_file);
		cout << "Time logged is ";
		print_time(time_logged);
		cout << endl;
    }
    else
    {
        cout << "Unable to open file " << argv[1] << endl;
    }

	return 0;
}