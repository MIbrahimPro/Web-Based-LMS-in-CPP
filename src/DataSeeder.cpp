#include "../include/DataSeeder.h"
#include "../include/CSVManager.h"
#include "../include/Teacher.h"
#include "../include/Student.h"
#include "../include/Course.h"
#include "../include/Enrollment.h"
#include "../include/AttendanceRecord.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

const std::vector<std::string> DataSeeder::COURSE_NAMES = {
    "Introduction to Programming",
    "Data Structures and Algorithms",
    "Object-Oriented Programming",
    "Database Management Systems",
    "Computer Networks",
    "Operating Systems",
    "Software Engineering",
    "Web Development",
    "Artificial Intelligence",
    "Machine Learning",
    "Computer Graphics",
    "Cyber Security"};

const std::vector<std::string> DataSeeder::FIRST_NAMES = {
    "Ahmed", "Ali", "Hassan", "Muhammad", "Omar", "Yusuf", "Ibrahim", "Bilal",
    "Fatima", "Ayesha", "Zainab", "Maryam", "Sara", "Hana", "Noor", "Amina",
    "Hamza", "Usman", "Zaid", "Tariq", "Khalid", "Saad", "Faisal", "Imran",
    "Khadija", "Sumaya", "Hafsa", "Ruqayyah", "Asma", "Layla"};

const std::vector<std::string> DataSeeder::LAST_NAMES = {
    "Khan", "Ahmed", "Ali", "Hassan", "Malik", "Sheikh", "Qureshi", "Syed",
    "Mirza", "Bukhari", "Farooq", "Iqbal", "Raza", "Javed", "Aslam", "Hussain",
    "Rahman", "Karim", "Bashir", "Nawaz", "Sharif", "Akbar", "Saleem", "Tahir"};


std::mt19937 &DataSeeder::getRandomEngine()
{
    static std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));
    return engine;
}

bool DataSeeder::randomChance(int percentage)
{
    std::uniform_int_distribution<int> dist(1, 100);
    return dist(getRandomEngine()) <= percentage;
}

int DataSeeder::randomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(getRandomEngine());
}

std::string DataSeeder::generateTeacherId(int index)
{
    char buffer[10];
    sprintf(buffer, "T%03d", index);
    return std::string(buffer);
}

std::string DataSeeder::generateStudentId(int index)
{
    char buffer[10];
    sprintf(buffer, "S%03d", index);
    return std::string(buffer);
}

std::string DataSeeder::generateCourseId(int index)
{
    char buffer[10];
    sprintf(buffer, "CS%03d", 101 + index);
    return std::string(buffer);
}

std::string DataSeeder::formatDate(int year, int month, int day)
{
    char buffer[11];
    sprintf(buffer, "%04d-%02d-%02d", year, month, day);
    return std::string(buffer);
}

int DataSeeder::getDaysInMonth(int year, int month)
{
    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2)
    {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return isLeap ? 29 : 28;
    }
    return daysInMonth[month - 1];
}

bool DataSeeder::isWeekend(int year, int month, int day)
{
    if (month < 3)
    {
        month += 12;
        year--;
    }

    int k = year % 100;
    int j = year / 100;
    int h = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

    return (h == 0 || h == 1);
}

std::vector<std::string> DataSeeder::getClassDates(int daysBack)
{
    std::vector<std::string> dates;

    time_t now = time(nullptr);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);

    int currentYear = timeinfo.tm_year + 1900;
    int currentMonth = timeinfo.tm_mon + 1;
    int currentDay = timeinfo.tm_mday;

    for (int i = daysBack; i >= 1; i--)
    {
        time_t pastTime = now - (i * 24 * 60 * 60);
        struct tm pastInfo;
        localtime_s(&pastInfo, &pastTime);

        int year = pastInfo.tm_year + 1900;
        int month = pastInfo.tm_mon + 1;
        int day = pastInfo.tm_mday;

        if (!isWeekend(year, month, day))
        {
            dates.push_back(formatDate(year, month, day));
        }
    }

    return dates;
}


void DataSeeder::clearAllData()
{
    std::cout << "[SEEDER] Clearing all existing data..." << std::endl;

    std::ofstream("data/teachers.csv", std::ios::trunc).close();
    std::ofstream("data/students.csv", std::ios::trunc).close();
    std::ofstream("data/courses.csv", std::ios::trunc).close();
    std::ofstream("data/enrollments.csv", std::ios::trunc).close();
    std::ofstream("data/attendance.csv", std::ios::trunc).close();

    std::ofstream adminFile("data/admins.csv", std::ios::trunc);
    adminFile << "admin,admin123" << std::endl;
    adminFile.close();

    std::cout << "[SEEDER] All data cleared. Default admin preserved." << std::endl;
}

void DataSeeder::createTeachers(int count)
{
    std::cout << "[SEEDER] Creating " << count << " teachers..." << std::endl;

    std::set<std::string> usedNames; 

    for (int i = 1; i <= count; i++)
    {
        std::string teacherId = generateTeacherId(i);

        std::string fullName;
        do
        {
            std::string firstName = FIRST_NAMES[randomInt(0, FIRST_NAMES.size() - 1)];
            std::string lastName = LAST_NAMES[randomInt(0, LAST_NAMES.size() - 1)];
            fullName = firstName + " " + lastName;
        } while (usedNames.count(fullName) > 0);

        usedNames.insert(fullName);

        Teacher teacher(teacherId, fullName, "teacher123");
        CSVManager::addTeacher(teacher);

        std::cout << "  Created: " << teacherId << " - " << fullName << std::endl;
    }
}

void DataSeeder::createStudents(int count)
{
    std::cout << "[SEEDER] Creating " << count << " students..." << std::endl;

    std::set<std::string> usedNames;

    for (int i = 1; i <= count; i++)
    {
        std::string studentId = generateStudentId(i);

        std::string fullName;
        do
        {
            std::string firstName = FIRST_NAMES[randomInt(0, FIRST_NAMES.size() - 1)];
            std::string lastName = LAST_NAMES[randomInt(0, LAST_NAMES.size() - 1)];
            fullName = firstName + " " + lastName;
        } while (usedNames.count(fullName) > 0);

        usedNames.insert(fullName);

        Student student(studentId, fullName, "student123");
        CSVManager::addStudent(student);

        std::cout << "  Created: " << studentId << " - " << fullName << std::endl;
    }
}

void DataSeeder::createCourses()
{
    std::cout << "[SEEDER] Creating " << NUM_COURSES << " courses..." << std::endl;

    for (int i = 0; i < NUM_COURSES; i++)
    {
        std::string courseId = generateCourseId(i);
        std::string courseName = COURSE_NAMES[i];

        Course course(courseId, courseName, "", 0);
        CSVManager::addCourse(course);

        std::cout << "  Created: " << courseId << " - " << courseName << std::endl;
    }
}

void DataSeeder::assignTeachersToCourses()
{
    std::cout << "[SEEDER] Assigning teachers to courses..." << std::endl;

    auto courses = CSVManager::loadCourses();
    auto teachers = CSVManager::loadTeachers();

    for (size_t i = 0; i < courses.size(); i++)
    {
        int teacherIndex = i % teachers.size();
        std::string teacherId = teachers[teacherIndex].getTeacherId();

        courses[i].setTeacherId(teacherId);

        std::cout << "  " << courses[i].getCourseId() << " -> "
                  << teacherId << " (" << teachers[teacherIndex].getName() << ")" << std::endl;
    }

    CSVManager::saveCourses(courses);
}


void DataSeeder::enrollStudents()
{
    std::cout << "[SEEDER] Enrolling students in courses..." << std::endl;

    auto students = CSVManager::loadStudents();
    auto courses = CSVManager::loadCourses();

    int enrollmentId = 1;

    for (const auto &student : students)
    {
        int numCourses = randomInt(3, 5);

        std::vector<int> courseIndices;
        for (size_t i = 0; i < courses.size(); i++)
        {
            courseIndices.push_back(static_cast<int>(i));
        }
        std::shuffle(courseIndices.begin(), courseIndices.end(), getRandomEngine());

        std::cout << "  " << student.getStudentId() << " enrolled in: ";

        for (int i = 0; i < numCourses && i < static_cast<int>(courses.size()); i++)
        {
            int courseIdx = courseIndices[i];
            std::string enrollId = "E" + std::to_string(enrollmentId++);

            Enrollment enrollment(enrollId, student.getStudentId(),
                                  courses[courseIdx].getCourseId());
            CSVManager::addEnrollment(enrollment);

            std::cout << courses[courseIdx].getCourseId() << " ";
        }
        std::cout << std::endl;
    }
}


void DataSeeder::generateAttendance(int daysBack)
{
    std::cout << "[SEEDER] Generating attendance for past " << daysBack << " days..." << std::endl;

    auto classDates = getClassDates(daysBack);
    std::cout << "  Found " << classDates.size() << " weekdays" << std::endl;

    auto courses = CSVManager::loadCourses();
    auto enrollments = CSVManager::loadEnrollments();

    int attendanceId = 1;
    int totalClassesHeld = 0;
    int totalAttendanceRecords = 0;

    for (auto &course : courses)
    {
        int classesForCourse = 0;

        std::set<std::string> classDatesForCourse;

        for (const auto &date : classDates)
        {
            if (randomChance(CLASS_PROBABILITY))
            {
                classDatesForCourse.insert(date);
                classesForCourse++;

                for (const auto &enrollment : enrollments)
                {
                    if (enrollment.getCourseId() == course.getCourseId())
                    {
                        if (randomChance(ATTENDANCE_PROBABILITY))
                        {
                            std::string recordId = "A" + std::to_string(attendanceId++);
                            AttendanceRecord record(recordId, enrollment.getStudentId(),
                                                    course.getCourseId(), date);
                            CSVManager::addAttendanceRecord(record);
                            totalAttendanceRecords++;
                        }
                    }
                }
            }
        }

        course.setTotalClasses(classesForCourse);
        totalClassesHeld += classesForCourse;

        std::cout << "  " << course.getCourseId() << ": " << classesForCourse << " classes held" << std::endl;
    }

    CSVManager::saveCourses(courses);

    std::cout << "[SEEDER] Total classes held: " << totalClassesHeld << std::endl;
    std::cout << "[SEEDER] Total attendance records: " << totalAttendanceRecords << std::endl;
}


bool DataSeeder::seedDemoData()
{
    std::cout << std::endl;
    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           LMS DEMO DATA SEEDER                               ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  Teachers: " << NUM_TEACHERS << "                                              ║" << std::endl;
    std::cout << "║  Students: " << NUM_STUDENTS << "                                              ║" << std::endl;
    std::cout << "║  Courses:  " << NUM_COURSES << "                                               ║" << std::endl;
    std::cout << "║  Days Back: " << DAYS_BACK << " (excluding weekends)                     ║" << std::endl;
    std::cout << "║  Class Probability: " << CLASS_PROBABILITY << "%                                  ║" << std::endl;
    std::cout << "║  Attendance Probability: " << ATTENDANCE_PROBABILITY << "%                             ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
    std::cout << std::endl;

    try
    {
        CSVManager::initialize();

        clearAllData();
        std::cout << std::endl;

        createTeachers(NUM_TEACHERS);
        std::cout << std::endl;

        createStudents(NUM_STUDENTS);
        std::cout << std::endl;

        createCourses();
        std::cout << std::endl;

        assignTeachersToCourses();
        std::cout << std::endl;

        enrollStudents();
        std::cout << std::endl;

        generateAttendance(DAYS_BACK);
        std::cout << std::endl;

        printSeedingSummary();

        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "[SEEDER ERROR] " << e.what() << std::endl;
        return false;
    }
}

void DataSeeder::printSeedingSummary()
{
    auto teachers = CSVManager::loadTeachers();
    auto students = CSVManager::loadStudents();
    auto courses = CSVManager::loadCourses();
    auto enrollments = CSVManager::loadEnrollments();
    auto attendance = CSVManager::loadAttendance();

    std::cout << "╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           SEEDING COMPLETE - SUMMARY                         ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  Teachers created:     " << teachers.size() << "                                   ║" << std::endl;
    std::cout << "║  Students created:     " << students.size() << "                                   ║" << std::endl;
    std::cout << "║  Courses created:      " << courses.size() << "                                   ║" << std::endl;
    std::cout << "║  Enrollments created:  " << enrollments.size() << "                                   ║" << std::endl;
    std::cout << "║  Attendance records:   " << attendance.size() << "                                ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║  LOGIN CREDENTIALS:                                          ║" << std::endl;
    std::cout << "║  ─────────────────────────────────────────────────────────── ║" << std::endl;
    std::cout << "║  Admin:    username=admin       password=admin123            ║" << std::endl;
    std::cout << "║  Teachers: T001-T020            password=teacher123          ║" << std::endl;
    std::cout << "║  Students: S001-S025            password=student123          ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;
}