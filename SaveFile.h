#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <iostream>
#include <fstream>
#include <string>

class SaveFile {
private:
    std::string filename;
public:
    // Constructor to set the filename
    SaveFile(const std::string& file) : filename(file) {}

    // Function to read stats from file
    void readStats(int& mostAttacksWon, int& totalHealthLost) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> mostAttacksWon >> totalHealthLost;
            file.close();
        } else {
            // Initialize with default values if file not found
            mostAttacksWon = 0;
            totalHealthLost = 0;
        }
    }

    // Function to write new stats to file
    void writeStats(int mostAttacksWon, int totalHealthLost) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << mostAttacksWon << std::endl;
            file << totalHealthLost << std::endl;
            file.close();
        } else {
            std::cerr << "Error opening file for writing!" << std::endl;
        }
    }
};

/*
int main() {
    SaveFile save("gameStats.txt");

    int mostAttacksWon = 0;
    int totalHealthLost = 0;

    // Read current stats
    save.readStats(mostAttacksWon, totalHealthLost);
    std::cout << "Current stats: " << std::endl;
    std::cout << "Most Attacks Won: " << mostAttacksWon << std::endl;
    std::cout << "Total Health Lost: " << totalHealthLost << std::endl;

    // Simulate game activity
    mostAttacksWon += 5;    // Assume player won 5 more attacks
    totalHealthLost += 20;  // Assume player lost 20 health

    // Write updated stats
    save.writeStats(mostAttacksWon, totalHealthLost);

    std::cout << "New stats saved!" << std::endl;

    return 0;
}
*/

#endif