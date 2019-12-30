/**
 * This class manages writing timestamped logs to a file.
 * - Manages file I/O
 * - Gets time
 */
#pragma once

#include <string>
#include <fstream>

using namespace std;

class Log
{
private:
	string _file_name;
	ofstream _log_file;
	int _unflushed_log_count = 0;

	/**
	 * Gets current time as a string
	 */
	static string GetTimeString();

public:

	/**
	 * Opens file "file_name" for logging
	 */
	Log(string file_name);

	/**
	 * Closes the open file.
	 */
	~Log();

	/**
	 * Writes the given message to the log.
	 */
	void Write(string message);

	/**
	 * Flush log buffer to disk
	 */
	void Flush();

	/**
	 * Gets the number of logs that have not been
	 * flushed to disk. These logs are sitting in the
	 * ofstream buffer
	 */
	int GetBufferedLogCount();

	/**
	 * Runs through the start/end session lines in the file
	 * to calculate total time spent using the logger.
	 */
	int CalculateTimeLogged();
};
