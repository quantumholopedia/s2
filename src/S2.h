#pragma once
#include <stdexcept>
#include <iostream>
#include <string>

#include "Waveforms.h"
#include "Options.h"
#include "Device.h"
#include "Pulse.h"
#include "Generator.h"
#include "Devices.h"
#include "Program.h"
#include "Preset.h"
#include "Database.h"
#include "ProgressMonitor.h"

namespace S2
{
	class IOError : public std::runtime_error
	{
	public:
		IOError(const char * message);
	};
		
	class DeviceNotFound : IOError
	{
	public:
		DeviceNotFound();
	};

	template <typename CharT, typename Traits = std::char_traits <CharT>, typename Allocator = std::allocator <CharT>>
	std::basic_istream <CharT, Traits> &getline (std::basic_istream <CharT, Traits> &istream, std::basic_string <CharT, Traits, Allocator> &line) {
		auto &result = std::getline (istream, line);
		std::cerr << line.length () << " -> ";
		auto const lineEnd = line.find_last_not_of ("\r\n");
		if (lineEnd == std::basic_string <CharT, Traits, Allocator>::npos) {
			line.clear ();
		} else if (lineEnd < line.length () - 1) {
			line.erase (lineEnd);
		}
		std::cerr << line.length () << std::endl;
		return result;
	}

	int PulseCommand(const Options&, ProgressMonitor &pm, StreamFactory &sf);
	int StatusCommand(const Options&, ProgressMonitor &pm, StreamFactory &sf);
	int Main(int argc, const char*argv[]);
	void PrintHelp();
	void Diagnose();
	int Scan(const Options & options, ProgressMonitor &pm, StreamFactory &sf);
	int Control(const Options & options, ProgressMonitor &pm, StreamFactory &sf);
	void Sleep(double seconds);
	int Send(const char * sendString);
	int Set(const Options & options);
	int Run(const Options & options, ProgressMonitor &pm, StreamFactory &sf);

	int FindCommand(const Options & options, ProgressMonitor &pm);
	int ValidateDatabase(const Options & options);
}
