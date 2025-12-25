#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "libraries/httplib.h"

#include "include/Admin.h"
#include "include/Teacher.h"
#include "include/Student.h"
#include "include/Course.h"
#include "include/Enrollment.h"
#include "include/AttendanceRecord.h"
#include "include/CSVManager.h"
#include "include/HTMLTemplates.h"
#include "include/DataSeeder.h"

std::map<std::string, std::pair<std::string, UserType>> sessions;

std::string generateSessionId()
{
    static int counter = 0;
    return "session_" + std::to_string(++counter) + "_" + std::to_string(time(nullptr));
}

std::string getSessionId(const httplib::Request &req)
{
    if (req.has_header("Cookie"))
    {
        std::string cookie = req.get_header_value("Cookie");
        size_t pos = cookie.find("session=");
        if (pos != std::string::npos)
        {
            size_t end = cookie.find(";", pos);
            if (end == std::string::npos)
                end = cookie.length();
            return cookie.substr(pos + 8, end - pos - 8);
        }
    }
    return "";
}

std::string replacePlaceholder(const std::string &html, const std::string &placeholder,
                               const std::string &value)
{
    std::string result = html;
    size_t pos;
    while ((pos = result.find(placeholder)) != std::string::npos)
    {
        result.replace(pos, placeholder.length(), value);
    }
    return result;
}

std::string urlDecode(const std::string &str)
{
    std::string result;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == '+')
        {
            result += ' ';
        }
        else if (str[i] == '%' && i + 2 < str.length())
        {
            int value;
            std::istringstream is(str.substr(i + 1, 2));
            if (is >> std::hex >> value)
            {
                result += static_cast<char>(value);
                i += 2;
            }
        }
        else
        {
            result += str[i];
        }
    }
    return result;
}

std::map<std::string, std::string> parseFormData(const std::string &body)
{
    std::map<std::string, std::string> params;
    std::istringstream stream(body);
    std::string pair;

    while (std::getline(stream, pair, '&'))
    {
        size_t pos = pair.find('=');
        if (pos != std::string::npos)
        {
            std::string key = urlDecode(pair.substr(0, pos));
            std::string value = urlDecode(pair.substr(pos + 1));
            params[key] = value;
        }
    }
    return params;
}

std::string getQueryParam(const httplib::Request &req, const std::string &key)
{
    if (req.has_param(key))
    {
        return req.get_param_value(key);
    }
    return "";
}

std::string buildAlertHTML(const std::string &message, const std::string &type)
{
    if (message.empty())
        return "";

    std::string alertClass = "alert-info";
    if (type == "success")
        alertClass = "alert-success";
    else if (type == "error")
        alertClass = "alert-error";
    else if (type == "warning")
        alertClass = "alert-warning";

    return "<div class='alert " + alertClass + "'>" + message + "</div>";
}

std::string urlEncode(const std::string &str)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : str)
    {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
        {
            escaped << c;
        }
        else if (c == ' ')
        {
            escaped << '+';
        }
        else
        {
            escaped << '%' << std::setw(2) << int((unsigned char)c);
        }
    }
    return escaped.str();
}

bool isValidId(const std::string &id)
{
    if (id.empty() || id.length() < 2 || id.length() > 20)
        return false;
    for (char c : id)
    {
        if (!isalnum(c) && c != '_' && c != '-')
            return false;
    }
    return true;
}

bool isValidName(const std::string &name)
{
    if (name.empty() || name.length() < 2 || name.length() > 100)
        return false;
    return true;
}

bool isValidPassword(const std::string &password)
{
    return password.length() >= 4;
}

bool teacherIdExists(const std::string &teacherId)
{
    auto teachers = CSVManager::loadTeachers();
    for (const auto &t : teachers)
    {
        if (t.getTeacherId() == teacherId)
            return true;
    }
    return false;
}

bool studentIdExists(const std::string &studentId)
{
    auto students = CSVManager::loadStudents();
    for (const auto &s : students)
    {
        if (s.getStudentId() == studentId)
            return true;
    }
    return false;
}

bool courseIdExists(const std::string &courseId)
{
    auto courses = CSVManager::loadCourses();
    for (const auto &c : courses)
    {
        if (c.getCourseId() == courseId)
            return true;
    }
    return false;
}

int main()
{
    CSVManager::initialize();

    httplib::Server svr;

    std::cout << "========================================" << std::endl;
    std::cout << "   Learning Management System (LMS)    " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Server starting on http://localhost:8080" << std::endl;
    std::cout << "Default Admin: username=admin, password=admin123" << std::endl;
    std::cout << "========================================" << std::endl;


    svr.Get("/", [](const httplib::Request &req, httplib::Response &res)
            { res.set_redirect("/login"); });

    svr.Get("/login", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string html = HTMLTemplates::LOGIN_PAGE;
        html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
        
        std::string msg = getQueryParam(req, "msg");
        std::string type = getQueryParam(req, "type");
        html = replacePlaceholder(html, "{{MESSAGE}}", buildAlertHTML(msg, type));
        
        res.set_content(html, "text/html"); });

    svr.Post("/login", [](const httplib::Request &req, httplib::Response &res)
             {
        auto params = parseFormData(req.body);
        std::string userType = params["userType"];
        std::string userId = params["userId"];
        std::string password = params["password"];
        
        bool authenticated = false;
        UserType type = UserType::NONE;
        std::string displayName;
        
        if (userType == "admin") {
            auto admins = CSVManager::loadAdmins();
            for (const auto& admin : admins) {
                if (admin.getUsername() == userId && admin.authenticate(password)) {
                    authenticated = true;
                    type = UserType::ADMIN;
                    displayName = admin.getDisplayName();
                    break;
                }
            }
        } else if (userType == "teacher") {
            auto teachers = CSVManager::loadTeachers();
            for (const auto& teacher : teachers) {
                if (teacher.getTeacherId() == userId && teacher.authenticate(password)) {
                    authenticated = true;
                    type = UserType::TEACHER;
                    displayName = teacher.getDisplayName();
                    break;
                }
            }
        } else if (userType == "student") {
            auto students = CSVManager::loadStudents();
            for (const auto& student : students) {
                if (student.getStudentId() == userId && student.authenticate(password)) {
                    authenticated = true;
                    type = UserType::STUDENT;
                    displayName = student.getDisplayName();
                    break;
                }
            }
        }
        
        if (authenticated) {
            std::string sessionId = generateSessionId();
            sessions[sessionId] = {userId, type};
            
            std::string redirect;
            if (type == UserType::ADMIN) redirect = "/admin";
            else if (type == UserType::TEACHER) redirect = "/teacher";
            else redirect = "/student";
            
            res.set_header("Set-Cookie", "session=" + sessionId + "; Path=/");
            res.set_redirect(redirect);
        } else {
            std::string html = HTMLTemplates::LOGIN_PAGE;
            html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
            html = replacePlaceholder(html, "{{MESSAGE}}", 
                buildAlertHTML("Invalid credentials. Please try again.", "error"));
            res.set_content(html, "text/html");
        } });

    svr.Get("/logout", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string sessionId = getSessionId(req);
        sessions.erase(sessionId);
        res.set_header("Set-Cookie", "session=; Path=/; Max-Age=0");
        res.set_redirect("/login?msg=Logged+out+successfully&type=success"); });


    svr.Get("/admin", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        std::string adminId = sessions[sessionId].first;
        
        std::string html = HTMLTemplates::ADMIN_DASHBOARD;
        html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
        html = replacePlaceholder(html, "{{ADMIN_NAME}}", adminId);
        
        std::string msg = getQueryParam(req, "msg");
        std::string msgType = getQueryParam(req, "type");
        html = replacePlaceholder(html, "{{MESSAGE}}", buildAlertHTML(msg, msgType));
        
        std::string teacherOptions;
        auto teachers = CSVManager::loadTeachers();
        for (const auto& t : teachers) {
            teacherOptions += "<option value='" + t.getTeacherId() + "'>" + 
                             t.getTeacherId() + " - " + t.getName() + "</option>";
        }
        html = replacePlaceholder(html, "{{TEACHER_OPTIONS}}", teacherOptions);
        
        std::string studentOptions;
        auto students = CSVManager::loadStudents();
        for (const auto& s : students) {
            studentOptions += "<option value='" + s.getStudentId() + "'>" + 
                             s.getStudentId() + " - " + s.getName() + "</option>";
        }
        html = replacePlaceholder(html, "{{STUDENT_OPTIONS}}", studentOptions);
        
        std::string courseOptions;
        auto courses = CSVManager::loadCourses();
        for (const auto& c : courses) {
            courseOptions += "<option value='" + c.getCourseId() + "'>" + 
                            c.getCourseId() + " - " + c.getCourseName() + "</option>";
        }
        html = replacePlaceholder(html, "{{COURSE_OPTIONS}}", courseOptions);
        
        std::string teachersTable;
        for (const auto& t : teachers) {
            teachersTable += "<tr><td>" + t.getTeacherId() + "</td><td>" + t.getName() + "</td></tr>";
        }
        if (teachersTable.empty()) teachersTable = "<tr><td colspan='2'>No teachers yet</td></tr>";
        html = replacePlaceholder(html, "{{TEACHERS_TABLE}}", teachersTable);
        
        std::string studentsTable;
        for (const auto& s : students) {
            studentsTable += "<tr><td>" + s.getStudentId() + "</td><td>" + s.getName() + "</td></tr>";
        }
        if (studentsTable.empty()) studentsTable = "<tr><td colspan='2'>No students yet</td></tr>";
        html = replacePlaceholder(html, "{{STUDENTS_TABLE}}", studentsTable);
        
        std::string coursesTable;
        for (const auto& c : courses) {
            std::string teacherName = "Unassigned";
            if (!c.getTeacherId().empty()) {
                for (const auto& t : teachers) {
                    if (t.getTeacherId() == c.getTeacherId()) {
                        teacherName = t.getName();
                        break;
                    }
                }
            }
            coursesTable += "<tr><td>" + c.getCourseId() + "</td><td>" + c.getCourseName() + 
                           "</td><td>" + teacherName + "</td><td>" + 
                           std::to_string(c.getTotalClasses()) + "</td></tr>";
        }
        if (coursesTable.empty()) coursesTable = "<tr><td colspan='4'>No courses yet</td></tr>";
        html = replacePlaceholder(html, "{{COURSES_TABLE}}", coursesTable);
        
        std::string enrollmentsTable;
        auto enrollments = CSVManager::loadEnrollments();
        for (const auto& e : enrollments) {
            std::string studentName, courseName;
            for (const auto& s : students) {
                if (s.getStudentId() == e.getStudentId()) {
                    studentName = s.getName();
                    break;
                }
            }
            for (const auto& c : courses) {
                if (c.getCourseId() == e.getCourseId()) {
                    courseName = c.getCourseName();
                    break;
                }
            }
            enrollmentsTable += "<tr><td>" + e.getStudentId() + "</td><td>" + studentName + 
                               "</td><td>" + e.getCourseId() + "</td><td>" + courseName + "</td></tr>";
        }
        if (enrollmentsTable.empty()) enrollmentsTable = "<tr><td colspan='4'>No enrollments yet</td></tr>";
        html = replacePlaceholder(html, "{{ENROLLMENTS_TABLE}}", enrollmentsTable);
        
        res.set_content(html, "text/html"); });

    svr.Get("/admin/seed", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto teachers = CSVManager::loadTeachers();
        auto students = CSVManager::loadStudents();
        auto courses = CSVManager::loadCourses();
        auto enrollments = CSVManager::loadEnrollments();
        auto attendance = CSVManager::loadAttendance();
        
        std::string html = HTMLTemplates::SEED_PAGE;
        html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
        
        std::string msg = getQueryParam(req, "msg");
        std::string type = getQueryParam(req, "type");
        html = replacePlaceholder(html, "{{MESSAGE}}", buildAlertHTML(msg, type));
        
        html = replacePlaceholder(html, "{{TEACHERS_COUNT}}", std::to_string(teachers.size()));
        html = replacePlaceholder(html, "{{STUDENTS_COUNT}}", std::to_string(students.size()));
        html = replacePlaceholder(html, "{{COURSES_COUNT}}", std::to_string(courses.size()));
        html = replacePlaceholder(html, "{{ENROLLMENTS_COUNT}}", std::to_string(enrollments.size()));
        html = replacePlaceholder(html, "{{ATTENDANCE_COUNT}}", std::to_string(attendance.size()));
        
        res.set_content(html, "text/html"); });
    svr.Post("/admin/seed", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto params = parseFormData(req.body);
        std::string confirm = params["confirm"];
        
        if (confirm != "SEED") {
            res.set_redirect("/admin/seed?msg=Invalid+confirmation.+Please+type+SEED&type=error");
            return;
        }
        

        std::cout << std::endl;
        std::cout << "[ADMIN] Seeding initiated from web interface..." << std::endl;
        
        bool success = DataSeeder::seedDemoData();
        
        if (success) {
            res.set_redirect("/admin?msg=Demo+data+seeded+successfully!+Check+console+for+details.&type=success");
        } else {
            res.set_redirect("/admin?msg=Failed+to+seed+demo+data.+Check+console+for+errors.&type=error");
        } });
    svr.Post("/admin/create-teacher", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto params = parseFormData(req.body);
        std::string teacherId = params["teacherId"];
        std::string name = params["name"];
        std::string password = params["password"];
        
        while (!teacherId.empty() && teacherId.back() == ' ') teacherId.pop_back();
        while (!teacherId.empty() && teacherId.front() == ' ') teacherId.erase(0, 1);
        
        if (teacherId.empty() || name.empty() || password.empty()) {
            res.set_redirect("/admin?msg=All+fields+are+required&type=error");
            return;
        }
        
        if (!isValidId(teacherId)) {
            res.set_redirect("/admin?msg=Teacher+ID+must+be+2-20+alphanumeric+characters&type=error");
            return;
        }
        
        if (!isValidName(name)) {
            res.set_redirect("/admin?msg=Name+must+be+2-100+characters&type=error");
            return;
        }
        
        if (!isValidPassword(password)) {
            res.set_redirect("/admin?msg=Password+must+be+at+least+4+characters&type=error");
            return;
        }
        
        if (teacherIdExists(teacherId)) {
            res.set_redirect("/admin?msg=Teacher+ID+'" + urlEncode(teacherId) + "'+already+exists&type=error");
            return;
        }
        
        Teacher teacher(teacherId, name, password);
        CSVManager::addTeacher(teacher);
        
        res.set_redirect("/admin?msg=Teacher+'" + urlEncode(name) + "'+created+successfully&type=success"); });

    svr.Post("/admin/create-student", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto params = parseFormData(req.body);
        std::string studentId = params["studentId"];
        std::string name = params["name"];
        std::string password = params["password"];
        
        while (!studentId.empty() && studentId.back() == ' ') studentId.pop_back();
        while (!studentId.empty() && studentId.front() == ' ') studentId.erase(0, 1);
        
        if (studentId.empty() || name.empty() || password.empty()) {
            res.set_redirect("/admin?msg=All+fields+are+required&type=error");
            return;
        }
        
        if (!isValidId(studentId)) {
            res.set_redirect("/admin?msg=Student+ID+must+be+2-20+alphanumeric+characters&type=error");
            return;
        }
        
        if (!isValidName(name)) {
            res.set_redirect("/admin?msg=Name+must+be+2-100+characters&type=error");
            return;
        }
        
        if (!isValidPassword(password)) {
            res.set_redirect("/admin?msg=Password+must+be+at+least+4+characters&type=error");
            return;
        }
        
        if (studentIdExists(studentId)) {
            res.set_redirect("/admin?msg=Student+ID+'" + urlEncode(studentId) + "'+already+exists&type=error");
            return;
        }
        
        Student student(studentId, name, password);
        CSVManager::addStudent(student);
        
        res.set_redirect("/admin?msg=Student+'" + urlEncode(name) + "'+created+successfully&type=success"); });

    svr.Post("/admin/create-course", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto params = parseFormData(req.body);
        std::string courseId = params["courseId"];
        std::string courseName = params["courseName"];
        
        while (!courseId.empty() && courseId.back() == ' ') courseId.pop_back();
        while (!courseId.empty() && courseId.front() == ' ') courseId.erase(0, 1);
        
        if (courseId.empty() || courseName.empty()) {
            res.set_redirect("/admin?msg=All+fields+are+required&type=error");
            return;
        }
        
        if (!isValidId(courseId)) {
            res.set_redirect("/admin?msg=Course+ID+must+be+2-20+alphanumeric+characters&type=error");
            return;
        }
        
        if (!isValidName(courseName)) {
            res.set_redirect("/admin?msg=Course+name+must+be+2-100+characters&type=error");
            return;
        }
        
        if (courseIdExists(courseId)) {
            res.set_redirect("/admin?msg=Course+ID+'" + urlEncode(courseId) + "'+already+exists&type=error");
            return;
        }
        
        Course course(courseId, courseName, "", 0);
        CSVManager::addCourse(course);
        
        res.set_redirect("/admin?msg=Course+'" + urlEncode(courseName) + "'+created+successfully&type=success"); });

    svr.Post("/admin/assign-teacher", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto params = parseFormData(req.body);
        std::string courseId = params["courseId"];
        std::string teacherId = params["teacherId"];
        
        if (courseId.empty() || teacherId.empty()) {
            res.set_redirect("/admin?msg=Please+select+both+course+and+teacher&type=error");
            return;
        }
        
        if (!courseIdExists(courseId)) {
            res.set_redirect("/admin?msg=Selected+course+does+not+exist&type=error");
            return;
        }
        
        if (!teacherIdExists(teacherId)) {
            res.set_redirect("/admin?msg=Selected+teacher+does+not+exist&type=error");
            return;
        }
        
        auto courses = CSVManager::loadCourses();
        std::string courseName;
        for (auto& course : courses) {
            if (course.getCourseId() == courseId) {
                course.setTeacherId(teacherId);
                courseName = course.getCourseName();
                break;
            }
        }
        CSVManager::saveCourses(courses);
        
        std::string teacherName = teacherId;
        auto teachers = CSVManager::loadTeachers();
        for (const auto& t : teachers) {
            if (t.getTeacherId() == teacherId) {
                teacherName = t.getName();
                break;
            }
        }
        
        res.set_redirect("/admin?msg=Teacher+'" + urlEncode(teacherName) + 
                        "'+assigned+to+course+'" + urlEncode(courseName) + "'&type=success"); });

    svr.Post("/admin/enroll-student", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::ADMIN) {
            res.set_redirect("/login");
            return;
        }
        
        auto params = parseFormData(req.body);
        std::string studentId = params["studentId"];
        std::string courseId = params["courseId"];
        
        if (studentId.empty() || courseId.empty()) {
            res.set_redirect("/admin?msg=Please+select+both+student+and+course&type=error");
            return;
        }
        
        if (!studentIdExists(studentId)) {
            res.set_redirect("/admin?msg=Selected+student+does+not+exist&type=error");
            return;
        }
        
        if (!courseIdExists(courseId)) {
            res.set_redirect("/admin?msg=Selected+course+does+not+exist&type=error");
            return;
        }
        
        if (CSVManager::isEnrolled(studentId, courseId)) {
            res.set_redirect("/admin?msg=Student+is+already+enrolled+in+this+course&type=warning");
            return;
        }
        
        Enrollment enrollment(CSVManager::generateId(), studentId, courseId);
        CSVManager::addEnrollment(enrollment);
        
        std::string studentName = studentId;
        std::string courseName = courseId;
        
        auto students = CSVManager::loadStudents();
        for (const auto& s : students) {
            if (s.getStudentId() == studentId) {
                studentName = s.getName();
                break;
            }
        }
        
        auto courses = CSVManager::loadCourses();
        for (const auto& c : courses) {
            if (c.getCourseId() == courseId) {
                courseName = c.getCourseName();
                break;
            }
        }
        
        res.set_redirect("/admin?msg=Student+'" + urlEncode(studentName) + 
                        "'+enrolled+in+'" + urlEncode(courseName) + "'&type=success"); });


    svr.Get("/teacher", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::TEACHER) {
            res.set_redirect("/login");
            return;
        }
        
        std::string teacherId = sessions[sessionId].first;
        
        std::string teacherName = teacherId;
        auto teachers = CSVManager::loadTeachers();
        for (const auto& t : teachers) {
            if (t.getTeacherId() == teacherId) {
                teacherName = t.getName();
                break;
            }
        }
        
        auto courses = CSVManager::findCoursesByTeacher(teacherId);
        
        std::string html = HTMLTemplates::TEACHER_DASHBOARD;
        html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
        html = replacePlaceholder(html, "{{TEACHER_NAME}}", teacherName);
        
        std::string msg = getQueryParam(req, "msg");
        std::string msgType = getQueryParam(req, "type");
        html = replacePlaceholder(html, "{{MESSAGE}}", buildAlertHTML(msg, msgType));
        
        std::string coursesList;
        if (courses.empty()) {
            coursesList = "<p>No courses assigned to you yet.</p>";
        } else {
            coursesList = "<ul style='list-style: none; padding: 0;'>";
            for (const auto& c : courses) {
                coursesList += "<li style='margin-bottom: 10px;'>";
                coursesList += "<a href='/teacher/course/" + c.getCourseId() + "' class='btn'>";
                coursesList += c.getCourseId() + " - " + c.getCourseName();
                coursesList += " (Total Classes: " + std::to_string(c.getTotalClasses()) + ")";
                coursesList += "</a></li>";
            }
            coursesList += "</ul>";
        }
        html = replacePlaceholder(html, "{{COURSES_LIST}}", coursesList);
        html = replacePlaceholder(html, "{{ATTENDANCE_SECTION}}", "");
        
        res.set_content(html, "text/html"); });

    svr.Get(R"(/teacher/course/(\w+))", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::TEACHER) {
            res.set_redirect("/login");
            return;
        }
        
        std::string teacherId = sessions[sessionId].first;
        std::string courseId = req.matches[1];
        
        auto course = CSVManager::findCourse(courseId);
        if (!course || course->getTeacherId() != teacherId) {
            res.set_redirect("/teacher?msg=Course+not+found+or+access+denied&type=error");
            return;
        }
        
        std::string teacherName = teacherId;
        auto teachers = CSVManager::loadTeachers();
        for (const auto& t : teachers) {
            if (t.getTeacherId() == teacherId) {
                teacherName = t.getName();
                break;
            }
        }
        
        auto enrollments = CSVManager::findEnrollmentsByCourse(courseId);
        auto students = CSVManager::loadStudents();
        
        std::string currentDate = CSVManager::getCurrentDate();
        
        std::string attendanceForm = HTMLTemplates::ATTENDANCE_FORM;
        attendanceForm = replacePlaceholder(attendanceForm, "{{COURSE_NAME}}", course->getCourseName());
        attendanceForm = replacePlaceholder(attendanceForm, "{{COURSE_ID}}", courseId);
        attendanceForm = replacePlaceholder(attendanceForm, "{{CURRENT_DATE}}", currentDate);
        
        std::string studentCheckboxes;
        for (const auto& e : enrollments) {
            std::string studentName;
            for (const auto& s : students) {
                if (s.getStudentId() == e.getStudentId()) {
                    studentName = s.getName();
                    break;
                }
            }
            
            bool alreadyPresent = CSVManager::hasAttendanceRecord(e.getStudentId(), courseId, currentDate);
            
            studentCheckboxes += "<tr>";
            studentCheckboxes += "<td>" + e.getStudentId() + "</td>";
            studentCheckboxes += "<td>" + studentName + "</td>";
            studentCheckboxes += "<td><label class='checkbox-label'>";
            studentCheckboxes += "<input type='checkbox' name='present_" + e.getStudentId() + "' value='1'";
            if (alreadyPresent) studentCheckboxes += " checked disabled";
            studentCheckboxes += "> Present";
            if (alreadyPresent) studentCheckboxes += " <span style='color: green;'>(Already marked)</span>";
            studentCheckboxes += "</label></td>";
            studentCheckboxes += "</tr>";
        }
        
        if (studentCheckboxes.empty()) {
            studentCheckboxes = "<tr><td colspan='3'>No students enrolled in this course.</td></tr>";
        }
        
        attendanceForm = replacePlaceholder(attendanceForm, "{{STUDENTS_CHECKBOXES}}", studentCheckboxes);
        
        std::string html = HTMLTemplates::TEACHER_DASHBOARD;
        html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
        html = replacePlaceholder(html, "{{TEACHER_NAME}}", teacherName);
        
        std::string msg = getQueryParam(req, "msg");
        std::string msgType = getQueryParam(req, "type");
        html = replacePlaceholder(html, "{{MESSAGE}}", buildAlertHTML(msg, msgType));
        
        html = replacePlaceholder(html, "{{COURSES_LIST}}", 
            "<a href='/teacher' class='btn'>← Back to Dashboard</a>");
        html = replacePlaceholder(html, "{{ATTENDANCE_SECTION}}", attendanceForm);
        
        res.set_content(html, "text/html"); });

    svr.Post("/teacher/mark-attendance", [](const httplib::Request &req, httplib::Response &res)
             {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::TEACHER) {
            res.set_redirect("/login");
            return;
        }
        
        std::string teacherId = sessions[sessionId].first;
        auto params = parseFormData(req.body);
        
        std::string courseId = params["courseId"];
        std::string date = params["date"];
        
        auto course = CSVManager::findCourse(courseId);
        if (!course || course->getTeacherId() != teacherId) {
            res.set_redirect("/teacher?msg=Access+denied&type=error");
            return;
        }
        
        auto enrollments = CSVManager::findEnrollmentsByCourse(courseId);
        int markedCount = 0;
        
        for (const auto& e : enrollments) {
            std::string key = "present_" + e.getStudentId();
            if (params.find(key) != params.end()) {
                if (!CSVManager::hasAttendanceRecord(e.getStudentId(), courseId, date)) {
                    AttendanceRecord record(CSVManager::generateId(), e.getStudentId(), courseId, date);
                    CSVManager::addAttendanceRecord(record);
                    markedCount++;
                }
            }
        }
        
        if (markedCount > 0) {
            auto courses = CSVManager::loadCourses();
            for (auto& c : courses) {
                if (c.getCourseId() == courseId) {
                    c.incrementTotalClasses();
                    break;
                }
            }
            CSVManager::saveCourses(courses);
        }
        
        std::string msg = "Attendance+marked+for+" + std::to_string(markedCount) + "+student(s)";
        res.set_redirect("/teacher/course/" + courseId + "?msg=" + msg + "&type=success"); });


    svr.Get("/student", [](const httplib::Request &req, httplib::Response &res)
            {
        std::string sessionId = getSessionId(req);
        if (sessions.find(sessionId) == sessions.end() || 
            sessions[sessionId].second != UserType::STUDENT) {
            res.set_redirect("/login");
            return;
        }
        
        std::string studentId = sessions[sessionId].first;
        
        std::string studentName = studentId;
        auto students = CSVManager::loadStudents();
        for (const auto& s : students) {
            if (s.getStudentId() == studentId) {
                studentName = s.getName();
                break;
            }
        }
        
        auto enrollments = CSVManager::findEnrollmentsByStudent(studentId);
        auto courses = CSVManager::loadCourses();
        auto teachers = CSVManager::loadTeachers();
        
        std::string html = HTMLTemplates::STUDENT_DASHBOARD;
        html = replacePlaceholder(html, "{{CSS}}", HTMLTemplates::CSS_STYLES);
        html = replacePlaceholder(html, "{{STUDENT_NAME}}", studentName);
        html = replacePlaceholder(html, "{{STUDENT_ID}}", studentId);
        
        std::string attendanceTable;
        std::string attendanceStats;
        
        for (const auto& e : enrollments) {
            std::string courseName, teacherName;
            int classesHeld = 0;
            
            for (const auto& c : courses) {
                if (c.getCourseId() == e.getCourseId()) {
                    courseName = c.getCourseName();
                    classesHeld = c.getTotalClasses();
                    
                    for (const auto& t : teachers) {
                        if (t.getTeacherId() == c.getTeacherId()) {
                            teacherName = t.getName();
                            break;
                        }
                    }
                    break;
                }
            }
            
            auto attendance = CSVManager::findAttendanceByStudentAndCourse(studentId, e.getCourseId());
            int classesAttended = static_cast<int>(attendance.size());
            
            double percentage = 0.0;
            if (classesHeld > 0) {
                percentage = (static_cast<double>(classesAttended) / classesHeld) * 100.0;
            }
            
            std::string color = percentage >= 75.0 ? "green" : (percentage >= 50.0 ? "orange" : "red");
            
            attendanceTable += "<tr>";
            attendanceTable += "<td>" + e.getCourseId() + "</td>";
            attendanceTable += "<td>" + courseName + "</td>";
            attendanceTable += "<td>" + (teacherName.empty() ? "Unassigned" : teacherName) + "</td>";
            attendanceTable += "<td>" + std::to_string(classesHeld) + "</td>";
            attendanceTable += "<td>" + std::to_string(classesAttended) + "</td>";
            attendanceTable += "<td style='color: " + color + "; font-weight: bold;'>";
            
            char buffer[10];
            sprintf(buffer, "%.1f%%", percentage);
            attendanceTable += buffer;
            attendanceTable += "</td></tr>";
            
            attendanceStats += "<div class='stats-box'>";
            attendanceStats += "<h2>" + std::string(buffer) + "</h2>";
            attendanceStats += "<p>" + e.getCourseId() + " - " + courseName + "</p>";
            attendanceStats += "</div>";
        }
        
        if (attendanceTable.empty()) {
            attendanceTable = "<tr><td colspan='6'>Not enrolled in any courses yet.</td></tr>";
            attendanceStats = "<div class='card'><p>No enrollment data available.</p></div>";
        }
        
        html = replacePlaceholder(html, "{{ATTENDANCE_TABLE}}", attendanceTable);
        html = replacePlaceholder(html, "{{ATTENDANCE_STATS}}", attendanceStats);
        
        res.set_content(html, "text/html"); });

    svr.listen("localhost", 8080);

    return 0;
}