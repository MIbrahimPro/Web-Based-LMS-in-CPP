#ifndef DATA_SEEDER_H
#define DATA_SEEDER_H

#include <string>
#include <vector>
#include <random>
#include <ctime>

class DataSeeder
{
private:
    static std::mt19937 &getRandomEngine();

    static const std::vector<std::string> COURSE_NAMES;
    static const std::vector<std::string> FIRST_NAMES;
    static const std::vector<std::string> LAST_NAMES;

    static bool randomChance(int percentage);
    static int randomInt(int min, int max);
    static std::string generateTeacherId(int index);
    static std::string generateStudentId(int index);
    static std::string generateCourseId(int index);

    static bool isWeekend(int year, int month, int day);
    static int getDaysInMonth(int year, int month);
    static std::vector<std::string> getClassDates(int daysBack);
    static std::string formatDate(int year, int month, int day);

    static void createTeachers(int count);
    static void createStudents(int count);
    static void createCourses();
    static void assignTeachersToCourses();
    static void enrollStudents();
    static void generateAttendance(int daysBack);

public:
    static bool seedDemoData();
    static void clearAllData();
    static void printSeedingSummary();

    static const int NUM_TEACHERS = 20;
    static const int NUM_STUDENTS = 25;
    static const int NUM_COURSES = 12;
    static const int DAYS_BACK = 60;
    static const int CLASS_PROBABILITY = 87;
    static const int ATTENDANCE_PROBABILITY = 75;
};

#endif