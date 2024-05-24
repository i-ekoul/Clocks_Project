/* 
Creator: [ Emmalie Cole ] 
Date: [ 23.05.2024 ]
Document: [ CS210; Module 3 - Chada Tech Clocks ] 
*/

#include <iostream>		// Standard input-output stream
#include <iomanip>		// Input-output manipulators
#include <ctime>		// C time library for date and time functions
#include <thread>		// Threading support for sleep operations
#include <chrono>		// Time library for time-related operations


// Base class for Clock
class Clock {
protected:
	int hours;		// Hours
	int minutes;	// Minutes
	int seconds;	// Seconds

public:
	Clock() {}

	// Pure virtual function to display time
	virtual void displayTime() const = 0;

	// Function to update time based on system time
	void updateTime() {
		time_t rawtime;				// Raw time variable
		struct tm timeinfo;         // Time structure
		time(&rawtime);             // Get raw time
		localtime_s(&timeinfo, &rawtime);   // Convert raw time to local time
		hours = timeinfo.tm_hour;   // Get hours
		minutes = timeinfo.tm_min;  // Get minutes
		seconds = timeinfo.tm_sec;  // Get seconds
	}

	// Function to add time
	void addTime(int h, int m, int s) {
		seconds += s;   // Add seconds
		minutes += m;   // Add minutes
		hours += h;     // Add hours

		// Ensure seconds stay within range [0, 59]
		seconds %= 60;
		if (seconds < 0) {
			seconds += 60;
			minutes -= 1; // Adjust minutes when seconds go below 0
		}

		// Ensure minutes stay within range [0, 59]
		minutes %= 60;
		if (minutes < 0) {
			minutes += 60;
			hours -= 1; // Adjust hours when minutes go below 0
		}

		// Ensure hours stay within range [0, 23] for 24-hour clock
		hours %= 24;
		if (hours < 0) hours += 24;
	}
};

// Derived class for 12-hour clock
class Clock12Hour : public Clock {
public:
	Clock12Hour() {
		updateTime();   // Update time when creating object
	}

	// Function to display time in 12-hour format
	void displayTime() const override {
		// Calculate display hours (range: 1-12)
		int displayHours = hours % 12 == 0 ? 12 : hours % 12;
		std::cout << std::setfill('0') << std::setw(2) << displayHours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds
			<< (hours < 12 ? " AM" : " PM") << std::endl; // Display AM/PM
	}
};

// Derived class for 24-hour clock
class Clock24Hour : public Clock {
public:
	Clock24Hour() {
		updateTime();   // Update time when creating object
	}

	// Function to display time in 24-hour format
	void displayTime() const override {
		std::cout << std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds << std::endl; // Display time
	}
};

int main() {
	Clock12Hour clock12;    // Create 12-hour clock object
	Clock24Hour clock24;    // Create 24-hour clock object

	int option;

	while (true) {
		// Clear the console and print clock information
		std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear console
		std::cout << "*************************************" << std::endl;
		std::cout << "*            12-Hour Clock          *" << std::endl;
		std::cout << "*           Time: ";
		clock12.displayTime();  // Display 12-hour clock time
		std::cout << "*************************************" << std::endl << std::endl;

		std::cout << "*************************************" << std::endl;
		std::cout << "*            24-Hour Clock          *" << std::endl;
		std::cout << "*           Time: ";
		clock24.displayTime();  // Display 24-hour clock time
		std::cout << "*************************************" << std::endl << std::endl;

		// Print user menu
		std::cout << "*************************************" << std::endl;
		std::cout << "*              User Menu            *" << std::endl;
		std::cout << "*************************************" << std::endl;
		std::cout << "*          Select an option:        *" << std::endl;
		std::cout << "*          1. Add 1 hour            *" << std::endl;
		std::cout << "*          2. Add 1 minute          *" << std::endl;
		std::cout << "*          3. Add 1 second          *" << std::endl;
		std::cout << "*          4. Exit                  *" << std::endl;
		std::cout << "*************************************" << std::endl;
		std::cout << "Choose an option: ";
		std::cin >> option;

		switch (option) {
			// Add 1 hour, minute, or second based on user choice
		case 1:
			clock12.addTime(1, 0, 0);   // Add 1 hour to 12-hour clock
			clock24.addTime(1, 0, 0);   // Add 1 hour to 24-hour clock
			break;
		case 2:
			clock12.addTime(0, 1, 0);   // Add 1 minute to 12-hour clock
			clock24.addTime(0, 1, 0);   // Add 1 minute to 24-hour clock
			break;
		case 3:
			clock12.addTime(0, 0, 1);   // Add 1 second to 12-hour clock
			clock24.addTime(0, 0, 1);   // Add 1 second to 24-hour clock
			break;
		case 4:
			exit(0);    // Exit the program
		default:
			std::cout << "Invalid option, please try again." << std::endl;
		}

		// Wait for one second before updating again
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}

	return 0;
}
