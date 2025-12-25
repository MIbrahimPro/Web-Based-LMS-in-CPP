#ifndef HTML_TEMPLATES_H
#define HTML_TEMPLATES_H

#include <string>

namespace HTMLTemplates
{

    inline const std::string CSS_STYLES = R"(
        <style>
            * { margin: 0; padding: 0; box-sizing: border-box; }
            body { 
                font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                min-height: 100vh;
                padding: 20px;
            }
            .container {
                max-width: 1200px;
                margin: 0 auto;
                background: white;
                border-radius: 15px;
                box-shadow: 0 10px 40px rgba(0,0,0,0.2);
                padding: 30px;
            }
            h1, h2, h3 { color: #333; margin-bottom: 20px; }
            h1 { text-align: center; color: #667eea; }
            .card {
                background: #f8f9fa;
                border-radius: 10px;
                padding: 20px;
                margin-bottom: 20px;
                border-left: 4px solid #667eea;
            }
            .form-group { margin-bottom: 15px; }
            label { 
                display: block; 
                margin-bottom: 5px; 
                font-weight: 600;
                color: #555;
            }
            input[type="text"], 
            input[type="password"],
            select {
                width: 100%;
                padding: 12px;
                border: 2px solid #ddd;
                border-radius: 8px;
                font-size: 14px;
                transition: border-color 0.3s;
            }
            input[type="text"]:focus, 
            input[type="password"]:focus,
            select:focus {
                border-color: #667eea;
                outline: none;
            }
            button, .btn {
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                color: white;
                border: none;
                padding: 12px 25px;
                border-radius: 8px;
                cursor: pointer;
                font-size: 14px;
                font-weight: 600;
                transition: transform 0.2s, box-shadow 0.2s;
                text-decoration: none;
                display: inline-block;
            }
            button:hover, .btn:hover {
                transform: translateY(-2px);
                box-shadow: 0 5px 20px rgba(102, 126, 234, 0.4);
            }
            .btn-danger {
                background: linear-gradient(135deg, #ff6b6b 0%, #ee5a5a 100%);
            }
            .btn-success {
                background: linear-gradient(135deg, #51cf66 0%, #40c057 100%);
            }
            table {
                width: 100%;
                border-collapse: collapse;
                margin-top: 15px;
            }
            th, td {
                padding: 12px;
                text-align: left;
                border-bottom: 1px solid #ddd;
            }
            th {
                background: #667eea;
                color: white;
            }
            tr:hover { background: #f5f5f5; }
            
            .alert {
                padding: 15px 20px;
                border-radius: 8px;
                margin-bottom: 20px;
                display: flex;
                align-items: center;
                gap: 10px;
                font-weight: 500;
            }
            .alert-success { 
                background: #d4edda; 
                color: #155724; 
                border: 1px solid #c3e6cb;
            }
            .alert-success::before {
                content: "✓";
                font-size: 18px;
                font-weight: bold;
            }
            .alert-error { 
                background: #f8d7da; 
                color: #721c24; 
                border: 1px solid #f5c6cb;
            }
            .alert-error::before {
                content: "✕";
                font-size: 18px;
                font-weight: bold;
            }
            .alert-warning {
                background: #fff3cd;
                color: #856404;
                border: 1px solid #ffeeba;
            }
            .alert-warning::before {
                content: "⚠";
                font-size: 18px;
            }
            .alert-info { 
                background: #d1ecf1; 
                color: #0c5460; 
                border: 1px solid #bee5eb;
            }
            .alert-info::before {
                content: "ℹ";
                font-size: 18px;
            }
            
            .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 20px; }
            .nav { 
                display: flex; 
                justify-content: space-between; 
                align-items: center;
                margin-bottom: 30px;
                padding-bottom: 20px;
                border-bottom: 2px solid #eee;
            }
            .stats-box {
                text-align: center;
                padding: 20px;
                background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
                color: white;
                border-radius: 10px;
            }
            .stats-box h2 { color: white; font-size: 36px; }
            .stats-box p { opacity: 0.9; }
            .checkbox-label {
                display: flex;
                align-items: center;
                gap: 10px;
            }
            input[type="checkbox"] {
                width: 20px;
                height: 20px;
                cursor: pointer;
            }
            .login-container {
                max-width: 400px;
                margin: 50px auto;
            }
            
            .required::after {
                content: " *";
                color: #dc3545;
            }
            
            input:invalid {
                border-color: #dc3545;
            }
            input:valid {
                border-color: #28a745;
            }
        </style>
    )";

    inline const std::string LOGIN_PAGE = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>LMS - Login</title>
            {{CSS}}
        </head>
        <body>
            <div class="container login-container">
                <h1>Learning Management System</h1>
                <div class="card">
                    <h2>Login</h2>
                    {{MESSAGE}}
                    <form method="POST" action="/login">
                        <div class="form-group">
                            <label for="userType">Login As:</label>
                            <select name="userType" id="userType" required>
                                <option value="admin">Admin</option>
                                <option value="teacher">Teacher</option>
                                <option value="student">Student</option>
                            </select>
                        </div>
                        <div class="form-group">
                            <label for="userId">Username / ID:</label>
                            <input type="text" name="userId" id="userId" required 
                                   placeholder="Enter your username or ID">
                        </div>
                        <div class="form-group">
                            <label for="password">Password:</label>
                            <input type="password" name="password" id="password" required
                                   placeholder="Enter your password">
                        </div>
                        <button type="submit">Login</button>
                    </form>
                </div>
            </div>
        </body>
        </html>
    )";

    inline const std::string ADMIN_DASHBOARD = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>LMS - Admin Dashboard</title>
            {{CSS}}
        </head>
        <body>
            <div class="container">
                <div class="nav">
                    <h1>Admin Dashboard</h1>
                    <div>
                        <span>Welcome, {{ADMIN_NAME}}</span>
                        <a href="/logout" class="btn btn-danger">Logout</a>
                    </div>
                </div>
                
                {{MESSAGE}}
                
                <div class="grid">
                    <div class="card">
                        <h3>Create Teacher</h3>
                        <form method="POST" action="/admin/create-teacher">
                            <div class="form-group">
                                <label class="required">Teacher ID:</label>
                                <input type="text" name="teacherId" required 
                                       placeholder="e.g., T001" minlength="2" maxlength="20">
                            </div>
                            <div class="form-group">
                                <label class="required">Teacher Name:</label>
                                <input type="text" name="name" required 
                                       placeholder="Full Name" minlength="2" maxlength="100">
                            </div>
                            <div class="form-group">
                                <label class="required">Password:</label>
                                <input type="password" name="password" required 
                                       placeholder="Set password" minlength="4">
                            </div>
                            <button type="submit">Create Teacher</button>
                        </form>
                    </div>
                    
                    <div class="card">
                        <h3>Create Student</h3>
                        <form method="POST" action="/admin/create-student">
                            <div class="form-group">
                                <label class="required">Student ID:</label>
                                <input type="text" name="studentId" required 
                                       placeholder="e.g., S001" minlength="2" maxlength="20">
                            </div>
                            <div class="form-group">
                                <label class="required">Student Name:</label>
                                <input type="text" name="name" required 
                                       placeholder="Full Name" minlength="2" maxlength="100">
                            </div>
                            <div class="form-group">
                                <label class="required">Password:</label>
                                <input type="password" name="password" required 
                                       placeholder="Set password" minlength="4">
                            </div>
                            <button type="submit">Create Student</button>
                        </form>
                    </div>
                    
                    <div class="card">
                        <h3>Create Course</h3>
                        <form method="POST" action="/admin/create-course">
                            <div class="form-group">
                                <label class="required">Course ID:</label>
                                <input type="text" name="courseId" required 
                                       placeholder="e.g., CS101" minlength="2" maxlength="20">
                            </div>
                            <div class="form-group">
                                <label class="required">Course Name:</label>
                                <input type="text" name="courseName" required 
                                       placeholder="Course Title" minlength="2" maxlength="100">
                            </div>
                            <button type="submit">Create Course</button>
                        </form>
                    </div>
                    
                    <div class="card">
                        <h3>Assign Teacher to Course</h3>
                        <form method="POST" action="/admin/assign-teacher">
                            <div class="form-group">
                                <label class="required">Select Course:</label>
                                <select name="courseId" required>
                                    <option value="">-- Select Course --</option>
                                    {{COURSE_OPTIONS}}
                                </select>
                            </div>
                            <div class="form-group">
                                <label class="required">Select Teacher:</label>
                                <select name="teacherId" required>
                                    <option value="">-- Select Teacher --</option>
                                    {{TEACHER_OPTIONS}}
                                </select>
                            </div>
                            <button type="submit">Assign Teacher</button>
                        </form>
                    </div>
                    
                    <div class="card">
                        <h3>Enroll Student in Course</h3>
                        <form method="POST" action="/admin/enroll-student">
                            <div class="form-group">
                                <label class="required">Select Student:</label>
                                <select name="studentId" required>
                                    <option value="">-- Select Student --</option>
                                    {{STUDENT_OPTIONS}}
                                </select>
                            </div>
                            <div class="form-group">
                                <label class="required">Select Course:</label>
                                <select name="courseId" required>
                                    <option value="">-- Select Course --</option>
                                    {{COURSE_OPTIONS}}
                                </select>
                            </div>
                            <button type="submit">Enroll Student</button>
                        </form>
                    </div>
                    
                    <div class="card" style="border-left-color: #ffc107;">
                        <h3>🌱 Demo Data</h3>
                        <p style="color: #666; margin-bottom: 15px;">
                            Populate database with demo teachers, students, courses, and attendance data.
                        </p>
                        <a href="/admin/seed" class="btn" style="background: linear-gradient(135deg, #ffc107 0%, #e0a800 100%); color: #333;">
                            Seed Demo Data
                        </a>
                    </div>
                </div>
                
                <div class="card" style="margin-top: 30px;">
                    <h3>All Teachers</h3>
                    <table>
                        <thead>
                            <tr>
                                <th>Teacher ID</th>
                                <th>Name</th>
                            </tr>
                        </thead>
                        <tbody>
                            {{TEACHERS_TABLE}}
                        </tbody>
                    </table>
                </div>
                
                <div class="card">
                    <h3>All Students</h3>
                    <table>
                        <thead>
                            <tr>
                                <th>Student ID</th>
                                <th>Name</th>
                            </tr>
                        </thead>
                        <tbody>
                            {{STUDENTS_TABLE}}
                        </tbody>
                    </table>
                </div>
                
                <div class="card">
                    <h3>All Courses</h3>
                    <table>
                        <thead>
                            <tr>
                                <th>Course ID</th>
                                <th>Course Name</th>
                                <th>Assigned Teacher</th>
                                <th>Total Classes</th>
                            </tr>
                        </thead>
                        <tbody>
                            {{COURSES_TABLE}}
                        </tbody>
                    </table>
                </div>
                
                <div class="card">
                    <h3>All Enrollments</h3>
                    <table>
                        <thead>
                            <tr>
                                <th>Student ID</th>
                                <th>Student Name</th>
                                <th>Course ID</th>
                                <th>Course Name</th>
                            </tr>
                        </thead>
                        <tbody>
                            {{ENROLLMENTS_TABLE}}
                        </tbody>
                    </table>
                </div>
            </div>
        </body>
        </html>
    )";

    inline const std::string SEED_PAGE = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>LMS - Seed Demo Data</title>
            {{CSS}}
            <style>
                .warning-box {
                    background: #fff3cd;
                    border: 2px solid #ffc107;
                    border-radius: 10px;
                    padding: 20px;
                    margin-bottom: 20px;
                }
                .warning-box h3 {
                    color: #856404;
                }
                .stats-grid {
                    display: grid;
                    grid-template-columns: repeat(auto-fit, minmax(150px, 1fr));
                    gap: 15px;
                    margin: 20px 0;
                }
                .stat-item {
                    background: #f8f9fa;
                    padding: 15px;
                    border-radius: 8px;
                    text-align: center;
                }
                .stat-item h4 {
                    color: #667eea;
                    font-size: 24px;
                    margin-bottom: 5px;
                }
                .danger-btn {
                    background: linear-gradient(135deg, #dc3545 0%, #c82333 100%);
                    color: white;
                    padding: 15px 30px;
                    font-size: 16px;
                }
                .confirm-input {
                    margin: 20px 0;
                }
            </style>
        </head>
        <body>
            <div class="container" style="max-width: 800px;">
                <div class="nav">
                    <h1>🌱 Seed Demo Data</h1>
                    <a href="/admin" class="btn">← Back to Dashboard</a>
                </div>
                
                {{MESSAGE}}

                <div class="warning-box">
                    <h3>⚠️ Warning: Destructive Operation</h3>
                    <p>This will <strong>COMPLETELY WIPE</strong> all existing data and replace it with demo data:</p>
                    <ul style="margin: 15px 0 15px 20px;">
                        <li>20 Teachers (T001-T020, password: teacher123)</li>
                        <li>25 Students (S001-S025, password: student123)</li>
                        <li>12 Courses with teachers assigned</li>
                        <li>Each student enrolled in 3-5 random courses</li>
                        <li>2 months of attendance data (weekdays only)</li>
                    </ul>
                    <p><strong>The default admin account will be preserved.</strong></p>
                </div>
                
                <div class="card">
                    <h3>Current Database Status</h3>
                    <div class="stats-grid">
                        <div class="stat-item">
                            <h4>{{TEACHERS_COUNT}}</h4>
                            <p>Teachers</p>
                        </div>
                        <div class="stat-item">
                            <h4>{{STUDENTS_COUNT}}</h4>
                            <p>Students</p>
                        </div>
                        <div class="stat-item">
                            <h4>{{COURSES_COUNT}}</h4>
                            <p>Courses</p>
                        </div>
                        <div class="stat-item">
                            <h4>{{ENROLLMENTS_COUNT}}</h4>
                            <p>Enrollments</p>
                        </div>
                        <div class="stat-item">
                            <h4>{{ATTENDANCE_COUNT}}</h4>
                            <p>Attendance Records</p>
                        </div>
                    </div>
                </div>
                
                <div class="card">
                    <h3>Confirm Seeding</h3>
                    <p>Type <strong>SEED</strong> below to confirm:</p>
                    <form method="POST" action="/admin/seed">
                        <div class="confirm-input">
                            <input type="text" name="confirm" required 
                                   placeholder="Type SEED to confirm" 
                                   pattern="SEED" 
                                   title="Please type SEED to confirm"
                                   style="max-width: 300px;">
                        </div>
                        <button type="submit" class="danger-btn">
                            🗑️ Wipe Data & Seed Demo Data
                        </button>
                    </form>
                </div>
            </div>
        </body>
        </html>
    )";

    inline const std::string TEACHER_DASHBOARD = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>LMS - Teacher Dashboard</title>
            {{CSS}}
        </head>
        <body>
            <div class="container">
                <div class="nav">
                    <h1>Teacher Dashboard</h1>
                    <div>
                        <span>Welcome, {{TEACHER_NAME}}</span>
                        <a href="/logout" class="btn btn-danger">Logout</a>
                    </div>
                </div>
                
                {{MESSAGE}}
                
                <div class="card">
                    <h3>Your Courses</h3>
                    {{COURSES_LIST}}
                </div>
                
                {{ATTENDANCE_SECTION}}
            </div>
        </body>
        </html>
    )";

    inline const std::string ATTENDANCE_FORM = R"(
        <div class="card">
            <h3>Mark Attendance for {{COURSE_NAME}} ({{COURSE_ID}})</h3>
            <p><strong>Date:</strong> {{CURRENT_DATE}}</p>
            <form method="POST" action="/teacher/mark-attendance">
                <input type="hidden" name="courseId" value="{{COURSE_ID}}">
                <input type="hidden" name="date" value="{{CURRENT_DATE}}">
                <table>
                    <thead>
                        <tr>
                            <th>Student ID</th>
                            <th>Student Name</th>
                            <th>Mark Present</th>
                        </tr>
                    </thead>
                    <tbody>
                        {{STUDENTS_CHECKBOXES}}
                    </tbody>
                </table>
                <button type="submit" class="btn-success" style="margin-top: 20px;">
                    Submit Attendance
                </button>
            </form>
        </div>
    )";

    inline const std::string STUDENT_DASHBOARD = R"(
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>LMS - Student Dashboard</title>
            {{CSS}}
        </head>
        <body>
            <div class="container">
                <div class="nav">
                    <h1>Student Dashboard</h1>
                    <div>
                        <span>Welcome, {{STUDENT_NAME}}</span>
                        <a href="/logout" class="btn btn-danger">Logout</a>
                    </div>
                </div>
                
                <div class="card">
                    <h3>Your Information</h3>
                    <p><strong>Student ID:</strong> {{STUDENT_ID}}</p>
                    <p><strong>Name:</strong> {{STUDENT_NAME}}</p>
                </div>
                
                <div class="card">
                    <h3>Enrolled Courses & Attendance</h3>
                    <table>
                        <thead>
                            <tr>
                                <th>Course ID</th>
                                <th>Course Name</th>
                                <th>Teacher</th>
                                <th>Classes Held</th>
                                <th>Classes Attended</th>
                                <th>Attendance %</th>
                            </tr>
                        </thead>
                        <tbody>
                            {{ATTENDANCE_TABLE}}
                        </tbody>
                    </table>
                </div>
                
                <div class="grid" style="margin-top: 20px;">
                    {{ATTENDANCE_STATS}}
                </div>
            </div>
        </body>
        </html>
    )";

}

#endif