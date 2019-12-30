#include "Log.h"
#include <iostream>
#include <ctime>

const string SESSION_MARKER = "----- ";
const string SESSION_START_MESSAGE = "Session started at ";
const string SESSION_END_MESSAGE = "Session ended at ";

string Log::GetTimeString()
{
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return string(asctime(timeinfo));
}

Log::Log(string file_name)
{
	this->_log_file.open(file_name, ofstream::app | ofstream::out);
	if (this->_log_file.is_open())
	{
		this->_log_file << SESSION_MARKER << SESSION_START_MESSAGE << Log::GetTimeString() << endl;
	}
	else
	{
		throw exception("Could not open log file");
	}
}

Log::~Log()
{
	if (this->_log_file.is_open())
	{
#ifdef DEBUG
		cout << "Closing log file" << endl;
#endif
		this->_log_file << SESSION_MARKER << SESSION_END_MESSAGE << Log::GetTimeString() << endl;
		this->_log_file.close();
	}
}

void Log::Write(string message)
{
	this->_log_file << Log::GetTimeString();
	this->_log_file << message;
	this->_log_file << endl;

	this->_unflushed_log_count++;
}

void Log::Flush()
{
	this->_log_file.flush();
	this->_unflushed_log_count = 0;
}

int Log::GetBufferedLogCount()
{
	return this->_unflushed_log_count;
}
