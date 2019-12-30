/**
 * This class manages writing timestamped logs to a file.
 * - Manages file I/O
 * - Gets time
 */

#include <string>
#include <fstream>

using namespace std;

class Log
{
private:
	ofstream _log_file;
	int _unflushed_log_count = 0;

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

	int GetBufferedLogCount();
};