#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course
{
private:
    std::string courseId;
    std::string courseName;
    std::string teacherId; 
    int totalClasses;      

public:
    Course();
    Course(const std::string &courseId, const std::string &courseName,
           const std::string &teacherId = "", int totalClasses = 0);

    std::string getCourseId() const;
    std::string getCourseName() const;
    std::string getTeacherId() const;
    int getTotalClasses() const;

    void setCourseId(const std::string &courseId);
    void setCourseName(const std::string &courseName);
    void setTeacherId(const std::string &teacherId);
    void setTotalClasses(int total);
    void incrementTotalClasses();

    std::string toCSV() const;
    void fromCSV(const std::string &csvLine);
};

#endif
