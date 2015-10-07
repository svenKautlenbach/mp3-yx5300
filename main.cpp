#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>


#include "ArapUtils.h"

#include "Config.h"

void printUsage(const std::string& myName);

int main (int argc, char* argv[])
{
	if (argc < 2)
	{
		printUsage(argv[0]);
	}
	
	auto printCommands = []() -> void
			{
				std::cout << "exit - exit the utility" << std::endl
					<< "ne - next song" << std::endl
					<< "pr - previous song" << std::endl
					<< "vu - volume up" << std::endl
					<< "vd - volume down" << std::endl
					<< "reset - reset the chip" << std::endl
					<< "pli - play index (asks folder and track number after this command)" << std::endl
					<< "pl - play" << std::endl
					<< "pa - pause" << std::endl
					<< "help - print this help menu" << std::endl; 
			};

	try
	{
		auto port = std::string(argv[1]);
		std::cout << "Opening " << port << std::endl;
		arap::linuxOS::SerialPort serialPort(port, 9600, 0);
		
		std::vector<uint8_t> nextSong = 	{0x7E, 0xFF, 0x06, 0x01, 0, 0, 0, 0xEF};
		std::vector<uint8_t> previousSong = 	{0x7E, 0xFF, 0x06, 0x02, 0, 0, 0, 0xEF};
		std::vector<uint8_t> volumeUp = 	{0x7E, 0xFF, 0x06, 0x04, 0, 0, 0, 0xEF};
		std::vector<uint8_t> volumeDown = 	{0x7E, 0xFF, 0x06, 0x05, 0, 0, 0, 0xEF};
		std::vector<uint8_t> chipReset = 	{0x7E, 0xFF, 0x06, 0x0C, 0, 0, 0, 0xEF};
		std::vector<uint8_t> playIndex = 	{0x7E, 0xFF, 0x06, 0x0F, 0, 0, 0, 0xEF};
		std::vector<uint8_t> play = 		{0x7E, 0xFF, 0x06, 0x0D, 0, 0, 0, 0xEF};
		std::vector<uint8_t> pause = 		{0x7E, 0xFF, 0x06, 0x0E, 0, 0, 0, 0xEF};

		while (true)
		{
			std::string command;
			std::cin >> command;

			if (command == "exit")
			{
				std::cout << "Exiting." << std::endl;
				break;
			}
			else if (command == "ne")
			{
				serialPort.sendData(nextSong);
			}
			else if (command == "pr")
			{
				serialPort.sendData(previousSong);
			}
			else if (command == "vu")
			{
				serialPort.sendData(volumeUp);
			}
			else if (command == "vd")
			{
				serialPort.sendData(volumeDown);
			}
			else if (command == "reset")
			{
				serialPort.sendData(chipReset);
			}
			else if (command == "pli")
			{
				int folderNumber;
				int trackNumber;
				std::cout << "Insert folder number:";
				std::cin >> folderNumber;
				std::cout << "Insert track number:";
				std::cin >> trackNumber;
				auto command = playIndex;
				command.at(5) = static_cast<uint8_t>(folderNumber);
				command.at(6) = static_cast<uint8_t>(trackNumber);
				serialPort.sendData(command);
			}
			else if (command == "pl")
			{
				serialPort.sendData(play);
			}
			else if (command == "pa")
			{
				serialPort.sendData(pause);
			}
			else if (command == "help")
			{
				printCommands();
			}
			else
			{
				std::cout << "Unknown command: " << command << std::endl;
			}
		}
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << "Caught runtime error - " << e.what() << ". Exiting..." << std::endl;
		return -1;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Caught exception - " << e.what() << ". Exiting..." << std::endl;
		return -2;
	}
	catch (...)
	{
		std::cerr << "Caught unknown error. Exiting..." << std::endl;
		return -3;
	}

	return 0;
}

void printUsage(const std::string& myName)
{
	std::cout << "Invoke with super-user rights." << std::endl
		<< "Example:" << std::endl
		<< myName << " [port]" << std::endl;

	exit(1);
}
