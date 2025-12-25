#include "../include/CSVManager.h"
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

const std::string CSVManager::DATA_DIR = "data";
const std::string CSVManager::ADMINS_FILE = "data/admins.csv";
const std::string CSVManager::TEACHERS_FILE = "data/teachers.csv";
const std::string CSVManager::STUDENTS_FILE = "data/students.csv";
const std::string CSVManager::COURSES_FILE = "data/courses.csv";
const std::string CSVManager::ENROLLMENTS_FILE = "data/enrollments.csv";
const std::string CSVManager::ATTENDANCE_FILE = "data/attendance.csv";

std::vector<std::string> CSVManager::splitCSV(const std::string &line)
{
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ','))
    {
        result.push_back(token);
    }
    return result;
}

void CSVManager::ensureDirectoryExists()
{
    _mkdir(DATA_DIR.c_str());
}

void CSVManager::ensureFileExists(const std::string &filename)
{
    std::ifstream checkFile(filename);
    if (!checkFile.good())
    {
        std::ofstream createFile(filename);
        createFile.close();
    }
}

void CSVManager::initialize()
{
    ensureDirectoryExists();
    ensureFileExists(ADMINS_FILE);
    ensureFileExists(TEACHERS_FILE);
    ensureFileExists(STUDENTS_FILE);
    ensureFileExists(COURSES_FILE);
    ensureFileExists(ENROLLMENTS_FILE);
    ensureFileExists(ATTENDANCE_FILE);

    auto admins = loadAdmins();
    if (admins.empty())
    {
        Admin defaultAdmin("admin", "admin123");
        addAdmin(defaultAdmin);
        std::cout << "Created default admin (username: admin, password: admin123)" << std::endl;
    }
}

std::vector<Admin> CSVManager::loadAdmins()
{
    std::vector<Admin> admins;
    std::ifstream file(ADMINS_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            Admin admin;
            admin.fromCSV(line);
            admins.push_back(admin);
        }
    }
    return admins;
}

void CSVManager::saveAdmins(const std::vector<Admin> &admins)
{
    std::ofstream file(ADMINS_FILE);
    for (const auto &admin : admins)
    {
        file << admin.toCSV() << std::endl;
    }
}

void CSVManager::addAdmin(const Admin &admin)
{
    std::ofstream file(ADMINS_FILE, std::ios::app);
    file << admin.toCSV() << std::endl;
}

Admin *CSVManager::findAdmin(const std::string &username)
{
    static std::vector<Admin> admins;
    admins = loadAdmins();
    for (auto &admin : admins)
    {
        if (admin.getUsername() == username)
        {
            return &admin;
        }
    }
    return nullptr;
}

std::vector<Teacher> CSVManager::loadTeachers()
{
    std::vector<Teacher> teachers;
    std::ifstream file(TEACHERS_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            Teacher teacher;
            teacher.fromCSV(line);
            teachers.push_back(teacher);
        }
    }
    return teachers;
}

void CSVManager::saveTeachers(const std::vector<Teacher> &teachers)
{
    std::ofstream file(TEACHERS_FILE);
    for (const auto &teacher : teachers)
    {
        file << teacher.toCSV() << std::endl;
    }
}

void CSVManager::addTeacher(const Teacher &teacher)
{
    std::ofstream file(TEACHERS_FILE, std::ios::app);
    file << teacher.toCSV() << std::endl;
}

Teacher *CSVManager::findTeacher(const std::string &teacherId)
{
    static std::vector<Teacher> teachers;
    teachers = loadTeachers();
    for (auto &teacher : teachers)
    {
        if (teacher.getTeacherId() == teacherId)
        {
            return &teacher;
        }
    }
    return nullptr;
}

std::vector<Student> CSVManager::loadStudents()
{
    std::vector<Student> students;
    std::ifstream file(STUDENTS_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            Student student;
            student.fromCSV(line);
            students.push_back(student);
        }
    }
    return students;
}

void CSVManager::saveStudents(const std::vector<Student> &students)
{
    std::ofstream file(STUDENTS_FILE);
    for (const auto &student : students)
    {
        file << student.toCSV() << std::endl;
    }
}

void CSVManager::addStudent(const Student &student)
{
    std::ofstream file(STUDENTS_FILE, std::ios::app);
    file << student.toCSV() << std::endl;
}

Student *CSVManager::findStudent(const std::string &studentId)
{
    static std::vector<Student> students;
    students = loadStudents();
    for (auto &student : students)
    {
        if (student.getStudentId() == studentId)
        {
            return &student;
        }
    }
    return nullptr;
}

std::vector<Course> CSVManager::loadCourses()
{
    std::vector<Course> courses;
    std::ifstream file(COURSES_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            Course course;
            course.fromCSV(line);
            courses.push_back(course);
        }
    }
    return courses;
}

void CSVManager::saveCourses(const std::vector<Course> &courses)
{
    std::ofstream file(COURSES_FILE);
    for (const auto &course : courses)
    {
        file << course.toCSV() << std::endl;
    }
}

void CSVManager::addCourse(const Course &course)
{
    std::ofstream file(COURSES_FILE, std::ios::app);
    file << course.toCSV() << std::endl;
}

void CSVManager::updateCourse(const Course &updatedCourse)
{
    auto courses = loadCourses();
    for (auto &course : courses)
    {
        if (course.getCourseId() == updatedCourse.getCourseId())
        {
            course = updatedCourse;
            break;
        }
    }
    saveCourses(courses);
}

Course *CSVManager::findCourse(const std::string &courseId)
{
    static std::vector<Course> courses;
    courses = loadCourses();
    for (auto &course : courses)
    {
        if (course.getCourseId() == courseId)
        {
            return &course;
        }
    }
    return nullptr;
}

std::vector<Course> CSVManager::findCoursesByTeacher(const std::string &teacherId)
{
    std::vector<Course> result;
    auto courses = loadCourses();
    for (const auto &course : courses)
    {
        if (course.getTeacherId() == teacherId)
        {
            result.push_back(course);
        }
    }
    return result;
}

std::vector<Enrollment> CSVManager::loadEnrollments()
{
    std::vector<Enrollment> enrollments;
    std::ifstream file(ENROLLMENTS_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            Enrollment enrollment;
            enrollment.fromCSV(line);
            enrollments.push_back(enrollment);
        }
    }
    return enrollments;
}

void CSVManager::saveEnrollments(const std::vector<Enrollment> &enrollments)
{
    std::ofstream file(ENROLLMENTS_FILE);
    for (const auto &enrollment : enrollments)
    {
        file << enrollment.toCSV() << std::endl;
    }
}

void CSVManager::addEnrollment(const Enrollment &enrollment)
{
    std::ofstream file(ENROLLMENTS_FILE, std::ios::app);
    file << enrollment.toCSV() << std::endl;
}

std::vector<Enrollment> CSVManager::findEnrollmentsByCourse(const std::string &courseId)
{
    std::vector<Enrollment> result;
    auto enrollments = loadEnrollments();
    for (const auto &enrollment : enrollments)
    {
        if (enrollment.getCourseId() == courseId)
        {
            result.push_back(enrollment);
        }
    }
    return result;
}

std::vector<Enrollment> CSVManager::findEnrollmentsByStudent(const std::string &studentId)
{
    std::vector<Enrollment> result;
    auto enrollments = loadEnrollments();
    for (const auto &enrollment : enrollments)
    {
        if (enrollment.getStudentId() == studentId)
        {
            result.push_back(enrollment);
        }
    }
    return result;
}

bool CSVManager::isEnrolled(const std::string &studentId, const std::string &courseId)
{
    auto enrollments = loadEnrollments();
    for (const auto &enrollment : enrollments)
    {
        if (enrollment.getStudentId() == studentId && enrollment.getCourseId() == courseId)
        {
            return true;
        }
    }
    return false;
}

std::vector<AttendanceRecord> CSVManager::loadAttendance()
{
    std::vector<AttendanceRecord> records;
    std::ifstream file(ATTENDANCE_FILE);
    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            AttendanceRecord record;
            record.fromCSV(line);
            records.push_back(record);
        }
    }
    return records;
}

void CSVManager::saveAttendance(const std::vector<AttendanceRecord> &records)
{
    std::ofstream file(ATTENDANCE_FILE);
    for (const auto &record : records)
    {
        file << record.toCSV() << std::endl;
    }
}

void CSVManager::addAttendanceRecord(const AttendanceRecord &record)
{
    std::ofstream file(ATTENDANCE_FILE, std::ios::app);
    file << record.toCSV() << std::endl;
}

std::vector<AttendanceRecord> CSVManager::findAttendanceByStudent(const std::string &studentId)
{
    std::vector<AttendanceRecord> result;
    auto records = loadAttendance();
    for (const auto &record : records)
    {
        if (record.getStudentId() == studentId)
        {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<AttendanceRecord> CSVManager::findAttendanceByCourse(const std::string &courseId)
{
    std::vector<AttendanceRecord> result;
    auto records = loadAttendance();
    for (const auto &record : records)
    {
        if (record.getCourseId() == courseId)
        {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<AttendanceRecord> CSVManager::findAttendanceByStudentAndCourse(
    const std::string &studentId, const std::string &courseId)
{
    std::vector<AttendanceRecord> result;
    auto records = loadAttendance();
    for (const auto &record : records)
    {
        if (record.getStudentId() == studentId && record.getCourseId() == courseId)
        {
            result.push_back(record);
        }
    }
    return result;
}

bool CSVManager::hasAttendanceRecord(const std::string &studentId,
                                     const std::string &courseId, const std::string &date)
{
    auto records = loadAttendance();
    for (const auto &record : records)
    {
        if (record.getStudentId() == studentId &&
            record.getCourseId() == courseId &&
            record.getDate() == date)
        {
            return true;
        }
    }
    return false;
}

std::string CSVManager::generateId()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(10000, 99999);
    return "ID" + std::to_string(dis(gen));
}

std::string CSVManager::getCurrentDate()
{
    time_t now = time(0);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
    return std::string(buffer);
}
