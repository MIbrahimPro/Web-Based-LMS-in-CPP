#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>

class Enrollment
{
private:
    std::string enrollmentId;
    std::string studentId; 
    std::string courseId;  

public:
    Enrollment();
    Enrollment(const std::string &enrollmentId, const std::string &studentId,
               const std::string &courseId);

    std::string getEnrollmentId() const;
    std::string getStudentId() const;
    std::string getCourseId() const;

    void setEnrollmentId(const std::string &enrollmentId);
    void setStudentId(const std::string &studentId);
    void setCourseId(const std::string &courseId);

    std::string toCSV() const;
    void fromCSV(const std::string &csvLine);
};

#endif
