#include "../include/Enrollment.h"
#include <sstream>

Enrollment::Enrollment() : enrollmentId(""), studentId(""), courseId("") {}

Enrollment::Enrollment(const std::string &enrollmentId, const std::string &studentId,
                       const std::string &courseId)
    : enrollmentId(enrollmentId), studentId(studentId), courseId(courseId) {}

std::string Enrollment::getEnrollmentId() const { return enrollmentId; }
std::string Enrollment::getStudentId() const { return studentId; }
std::string Enrollment::getCourseId() const { return courseId; }

void Enrollment::setEnrollmentId(const std::string &enrollmentId) { this->enrollmentId = enrollmentId; }
void Enrollment::setStudentId(const std::string &studentId) { this->studentId = studentId; }
void Enrollment::setCourseId(const std::string &courseId) { this->courseId = courseId; }

std::string Enrollment::toCSV() const
{
    return enrollmentId + "," + studentId + "," + courseId;
}

void Enrollment::fromCSV(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ','))
        enrollmentId = token;
    if (std::getline(ss, token, ','))
        studentId = token;
    if (std::getline(ss, token, ','))
        courseId = token;
}
