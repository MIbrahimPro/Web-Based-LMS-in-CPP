// seeder.cpp - Standalone demo data seeder
// Compile separately: cl /EHsc seeder.cpp src/*.cpp /Fe:seeder.exe
// Run before starting the server: seeder.exe

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "include/DataSeeder.h"
#include "include/CSVManager.h"

void printUsage()
{
    std::cout << std::endl;
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           LMS DEMO DATA SEEDER                               ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  Usage: seeder.exe [command]                                 ║" << std::endl;
    std::cout << "║                                                              ║" << std::endl;
    std::cout << "║  Commands:                                                   ║" << std::endl;
    std::cout << "║    seed     - Seed database with demo data (WIPES EXISTING) ║" << std::endl;
    std::cout << "║    clear    - Clear all data (keep default admin)           ║" << std::endl;
    std::cout << "║    status   - Show current database statistics              ║" << std::endl;
    std::cout << "║    help     - Show this help message                        ║" << std::endl;
    std::cout << "║                                                              ║" << std::endl;
    std::cout << "║  Example:                                                    ║" << std::endl;
    std::cout << "║    seeder.exe seed                                          ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

void showStatus()
{
    CSVManager::initialize();

    auto teachers = CSVManager::loadTeachers();
    auto students = CSVManager::loadStudents();
    auto courses = CSVManager::loadCourses();
    auto enrollments = CSVManager::loadEnrollments();
    auto attendance = CSVManager::loadAttendance();

    std::cout << std::endl;
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           DATABASE STATUS                                    ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  Teachers:           " << teachers.size() << std::endl;
    std::cout << "║  Students:           " << students.size() << std::endl;
    std::cout << "║  Courses:            " << courses.size() << std::endl;
    std::cout << "║  Enrollments:        " << enrollments.size() << std::endl;
    std::cout << "║  Attendance Records: " << attendance.size() << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;
}

bool confirmAction(const std::string &action)
{
    std::cout << std::endl;
    std::cout << "⚠️  WARNING: This will " << action << "!" << std::endl;
    std::cout << "Are you sure? (yes/no): ";

    std::string response;
    std::getline(std::cin, response);

    return (response == "yes" || response == "YES" || response == "y" || response == "Y");
}

int main(int argc, char *argv[])
{
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "   LMS Demo Data Seeder                " << std::endl;
    std::cout << "========================================" << std::endl;

    // Parse command line arguments
    std::string command = "help";
    if (argc >= 2)
    {
        command = argv[1];
    }

    // Convert to lowercase
    for (char &c : command)
    {
        c = tolower(c);
    }

    if (command == "seed")
    {
        if (confirmAction("WIPE all existing data and create new demo data"))
        {
            if (DataSeeder::seedDemoData())
            {
                std::cout << std::endl;
                std::cout << "✓ Demo data seeded successfully!" << std::endl;
                std::cout << "  You can now start the LMS server." << std::endl;
                std::cout << std::endl;
                return 0;
            }
            else
            {
                std::cerr << "✕ Failed to seed demo data!" << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "Operation cancelled." << std::endl;
            return 0;
        }
    }
    else if (command == "clear")
    {
        if (confirmAction("CLEAR all existing data (keep default admin)"))
        {
            CSVManager::initialize();
            DataSeeder::clearAllData();
            std::cout << std::endl;
            std::cout << "✓ All data cleared successfully!" << std::endl;
            std::cout << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Operation cancelled." << std::endl;
            return 0;
        }
    }
    else if (command == "status")
    {
        showStatus();
        return 0;
    }
    else if (command == "help" || command == "-h" || command == "--help")
    {
        printUsage();
        return 0;
    }
    else
    {
        std::cerr << "Unknown command: " << command << std::endl;
        printUsage();
        return 1;
    }
}