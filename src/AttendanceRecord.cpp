#include "../include/AttendanceRecord.h"
#include <sstream>

AttendanceRecord::AttendanceRecord() : recordId(""), studentId(""), courseId(""), date("") {}

AttendanceRecord::AttendanceRecord(const std::string &recordId, const std::string &studentId,
                                   const std::string &courseId, const std::string &date)
    : recordId(recordId), studentId(studentId), courseId(courseId), date(date) {}

std::string AttendanceRecord::getRecordId() const { return recordId; }
std::string AttendanceRecord::getStudentId() const { return studentId; }
std::string AttendanceRecord::getCourseId() const { return courseId; }
std::string AttendanceRecord::getDate() const { return date; }

void AttendanceRecord::setRecordId(const std::string &recordId) { this->recordId = recordId; }
void AttendanceRecord::setStudentId(const std::string &studentId) { this->studentId = studentId; }
void AttendanceRecord::setCourseId(const std::string &courseId) { this->courseId = courseId; }
void AttendanceRecord::setDate(const std::string &date) { this->date = date; }

std::string AttendanceRecord::toCSV() const
{
    return recordId + "," + studentId + "," + courseId + "," + date;
}

void AttendanceRecord::fromCSV(const std::string &csvLine)
{
    std::stringstream ss(csvLine);
    std::string token;

    if (std::getline(ss, token, ','))
        recordId = token;
    if (std::getline(ss, token, ','))
        studentId = token;
    if (std::getline(ss, token, ','))
        courseId = token;
    if (std::getline(ss, token, ','))
        date = token;
}
