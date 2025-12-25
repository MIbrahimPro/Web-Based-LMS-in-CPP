#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <direct.h> 

#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include "Course.h"
#include "Enrollment.h"
#include "AttendanceRecord.h"

class CSVManager
{
private:
    static const std::string DATA_DIR;
    static const std::string ADMINS_FILE;
    static const std::string TEACHERS_FILE;
    static const std::string STUDENTS_FILE;
    static const std::string COURSES_FILE;
    static const std::string ENROLLMENTS_FILE;
    static const std::string ATTENDANCE_FILE;

    static std::vector<std::string> splitCSV(const std::string &line);
    static void ensureDirectoryExists();
    static void ensureFileExists(const std::string &filename);

public:
    static void initialize();

    static std::vector<Admin> loadAdmins();
    static void saveAdmins(const std::vector<Admin> &admins);
    static void addAdmin(const Admin &admin);
    static Admin *findAdmin(const std::string &username);

    static std::vector<Teacher> loadTeachers();
    static void saveTeachers(const std::vector<Teacher> &teachers);
    static void addTeacher(const Teacher &teacher);
    static Teacher *findTeacher(const std::string &teacherId);

    static std::vector<Student> loadStudents();
    static void saveStudents(const std::vector<Student> &students);
    static void addStudent(const Student &student);
    static Student *findStudent(const std::string &studentId);

    static std::vector<Course> loadCourses();
    static void saveCourses(const std::vector<Course> &courses);
    static void addCourse(const Course &course);
    static void updateCourse(const Course &course);
    static Course *findCourse(const std::string &courseId);
    static std::vector<Course> findCoursesByTeacher(const std::string &teacherId);

    static std::vector<Enrollment> loadEnrollments();
    static void saveEnrollments(const std::vector<Enrollment> &enrollments);
    static void addEnrollment(const Enrollment &enrollment);
    static std::vector<Enrollment> findEnrollmentsByCourse(const std::string &courseId);
    static std::vector<Enrollment> findEnrollmentsByStudent(const std::string &studentId);
    static bool isEnrolled(const std::string &studentId, const std::string &courseId);

    static std::vector<AttendanceRecord> loadAttendance();
    static void saveAttendance(const std::vector<AttendanceRecord> &records);
    static void addAttendanceRecord(const AttendanceRecord &record);
    static std::vector<AttendanceRecord> findAttendanceByStudent(const std::string &studentId);
    static std::vector<AttendanceRecord> findAttendanceByCourse(const std::string &courseId);
    static std::vector<AttendanceRecord> findAttendanceByStudentAndCourse(
        const std::string &studentId, const std::string &courseId);
    static bool hasAttendanceRecord(const std::string &studentId,
                                    const std::string &courseId, const std::string &date);

    static std::string generateId();
    static std::string getCurrentDate();
};

#endif
