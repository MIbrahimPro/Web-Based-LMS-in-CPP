#include "../include/Course.h"
#include <sstream>

Course::Course() : courseId(""), courseName(""), teacherId(""), totalClasses(0) {}

Course::Course(const std::string &courseId, const std::string &courseName,
               const std::string &teacherId, int totalClasses)
    : courseId(courseId), courseName(courseName), teacherId(teacherId), totalClasses(totalClasses) {}

std::string Course::getCourseId() const { return courseId; }
std::string Course::getCourseName() const { return courseName; }
std::string Course::getTeacherId() const { return teacherId; }
int Course::getTotalClasses() const { return totalClasses; }

void Course::setCourseId(const std::string &courseId) { this->courseId = courseId; }
void Course::setCourseName(const std::string &courseName) { this->courseName = courseName; }
void Course::setTeacherId(const std::string &teacherId) { this->teacherId = teacherId; }
void Course::setTotalClasses(int total) { this->totalClasses = total; }
void Course::incrementTotalClasses() { totalClasses++; }

std::string Course::toCSV() const
{
    return courseId + "," + courseName + "," + teacherId + "," + std::to_string(totalClasses);
}

void Course::fromCSV(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ','))
        courseId = token;
    if (std::getline(ss, token, ','))
        courseName = token;
    if (std::getline(ss, token, ','))
        teacherId = token;
    if (std::getline(ss, token, ','))
        totalClasses = std::stoi(token);
}
