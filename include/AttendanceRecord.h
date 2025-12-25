#ifndef ATTENDANCE_RECORD_H
#define ATTENDANCE_RECORD_H

#include <string>

class AttendanceRecord
{
private:
    std::string recordId;
    std::string studentId; 
    std::string courseId;  
    std::string date;      

public:
    AttendanceRecord();
    AttendanceRecord(const std::string &recordId, const std::string &studentId,
                     const std::string &courseId, const std::string &date);

    std::string getRecordId() const;
    std::string getStudentId() const;
    std::string getCourseId() const;
    std::string getDate() const;

    void setRecordId(const std::string &recordId);
    void setStudentId(const std::string &studentId);
    void setCourseId(const std::string &courseId);
    void setDate(const std::string &date);

    std::string toCSV() const;
    void fromCSV(const std::string &csvLine);
};

#endif
