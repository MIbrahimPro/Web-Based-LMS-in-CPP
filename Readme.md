# Learning Management System (LMS)

A complete Learning Management System built with **pure C++** using Object-Oriented Analysis and Design (OOAD) principles. Features a web-based interface using HTML/CSS (no JavaScript) and CSV-based data persistence.

![C++](https://img.shields.io/badge/C++-20-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)

---

## Screenshots

*Please add the following screenshots to the `/screenshots/` folder.*

*   **login.png**: A screenshot of the login page showing the role selection for Admin, Teacher, and Student.
*   **admin_dashboard.png**: A screenshot of the main Admin Dashboard, showing the forms for creating users/courses and the tables of existing data.
*   **teacher_dashboard.png**: A screenshot of a Teacher's dashboard, displaying their assigned courses.
*   **attendance.png**: A screenshot of the attendance marking page a teacher sees after clicking on a course, with the list of students and checkboxes.
*   **student_dashboard.png**: A screenshot of a Student's dashboard, showing their course list and attendance percentages.
*   **seeder.png**: A screenshot of the `/admin/seed` page where the admin can confirm the data seeding operation.

### Login Page
![Login Page](/screenshots/login.png)****
*Login interface with role selection (Admin/Teacher/Student)*

### Admin Dashboard
![Admin Dashboard](/screenshots/admin_dashboard.png)
*Admin can create users, courses, and manage enrollments*

### Teacher Dashboard
![Teacher Dashboard](/screenshots/teacher_dashboard.png)
*Teachers can view their courses and mark attendance*

### Attendance Marking
![Attendance](/screenshots/attendance.png)
*Checkbox-based attendance marking system*

### Student Dashboard
![Student Dashboard](/screenshots/student_dashboard.png)
*Students can view their attendance statistics per course*

### Seed Demo Data
![Seeder](/screenshots/seeder.png)
*Admin can populate database with demo data*

---

## Features

### Admin Features
- Create Teachers with unique IDs
- Create Students with unique IDs  
- Create Courses
- Assign Teachers to Courses
- Enroll Students in Courses
- Seed demo data (20 teachers, 25 students, 12 courses)
- View all data in tables

### Teacher Features
- View assigned courses
- See list of enrolled students
- Mark attendance with checkboxes (Present only)
- Automatic date tracking
- Prevention of duplicate attendance

### Student Features
- View personal information
- See enrolled courses
- View attendance statistics per course
- Color-coded attendance percentage
  - Green: >=75%
  - Orange: 50-74%
  - Red: <50%

### Technical Features
- CSV-based data persistence (no database required)
- Session-based authentication
- Input validation with error messages
- Unique ID enforcement
- Demo data seeder with realistic attendance patterns

---

## Project Structure
```
LMS/
├── CMakeLists.txt         # CMake build configuration
├── main.cpp               # Main server application
├── seeder.cpp             # Standalone seeder program
├── README.md              # This file
│
├── include/               # Header files (.h)
│   ├── User.h             # Abstract base class
│   ├── Admin.h            # Admin class (inherits User)
│   ├── Teacher.h          # Teacher class (inherits User)
│   ├── Student.h          # Student class (inherits User)
│   ├── Course.h           # Course class
│   ├── Enrollment.h       # Enrollment association class
│   ├── AttendanceRecord.h # Attendance record class
│   ├── CSVManager.h       # Data persistence manager
│   ├── DataSeeder.h       # Demo data generator
│   └── HTMLTemplates.h    # HTML/CSS templates
│
├── src/                   # Implementation files (.cpp)
│   ├── User.cpp
│   ├── Admin.cpp
│   ├── Teacher.cpp
│   ├── Student.cpp
│   ├── Course.cpp
│   ├── Enrollment.cpp
│   ├── AttendanceRecord.cpp
│   ├── CSVManager.cpp
│   └── DataSeeder.cpp
│
├── libraries/             # Third-party libraries
│   └── httplib.h          # HTTP server library (auto-downloaded)
│
├── data/                  # CSV data files (auto-created)
│   ├── admins.csv
│   ├── teachers.csv
│   ├── students.csv
│   ├── courses.csv
│   ├── enrollments.csv
│   └── attendance.csv
│
├── screenshots/           # Screenshots for README
│
└── _plug_n_play/          # Pre-compiled executables
    ├── lms_server.exe     # Main server executable
    ├── seeder.exe         # Seeder executable
    └── data/              # Data folder for executables
```

---

## Quick Start (Plug & Play)

### For Users Who Just Want to Run It

**No compilation needed!** Use the pre-compiled executables in the `_plug_n_play` folder.

#### Step 1: Navigate to the folder
Open the `_plug_n_play` folder.

#### Step 2: (Optional) Seed demo data
```batch
# Double-click or run in command prompt:
seeder.exe seed
```
Type `yes` when prompted to confirm.

#### Step 3: Start the server
```batch
# Double-click or run in command prompt:
lms_server.exe
```
#### Step 4: Open your browser
Go to: `http://localhost:8080`

#### Step 5: Login
| Role    | Username/ID | Password   |
| ------- | ----------- | ---------- |
| Admin   | admin       | admin123   |
| Teacher | T001-T020   | teacher123 |
| Student | S001-S025   | student123 |

## Building from Source
**Prerequisites**
- Windows 10/11
- CMake (version 3.15 or higher)
- Visual Studio 2019/2022 with C++ workload OR MinGW-w64 (g++ compiler)

### Option 1: Using CMake with Visual Studio
#### Step 1: Clone the project
```batch
git clone https://github.com/MIbrahimPro/Web-Based-LMS-in-CPP-.git
cd Web-Based-LMS-in-CPP-
```
#### Step 2: Create build directory
```batch
mkdir build
cd build
```
#### Step 3: Generate Visual Studio solution
```batch
# For VS 2022
cmake .. -G "Visual Studio 17 2022"

# For VS 2019
cmake .. -G "Visual Studio 16 2019"
```
#### Step 4: Build the project
```batch
cmake --build . --config Release
```
#### Step 5: Find executables
The executables will be in the `build/Release/` directory:
- `lms_server.exe`
- `seeder.exe`

### Option 2: Using CMake with MinGW
#### Step 1: Generate Makefiles
```batch
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
```
#### Step 2: Build
```batch
mingw32-make
```

### Option 3: Manual Compilation (MSVC)
Open `Developer Command Prompt for VS` and run:
```batch
# Compile the main server
cl /EHsc /std:c++20 /I"include" /I"libraries" src\*.cpp main.cpp ws2_32.lib /Fe:lms_server.exe

# Compile the seeder
cl /EHsc /std:c++20 /I"include" /I"libraries" src\*.cpp seeder.cpp ws2_32.lib /Fe:seeder.exe
```

### Option 4: Manual Compilation (MinGW g++)
```batch
# Compile the main server
g++ -std=c++20 -I"include" -I"libraries" src/*.cpp main.cpp -lws2_32 -o lms_server.exe

# Compile the seeder
g++ -std=c++20 -I"include" -I"libraries" src/*.cpp seeder.cpp -lws2_32 -o seeder.exe
```

## How to Use

### Login Credentials
| User Type | ID/Username  | Password   | Notes              |
| --------- | ------------ | ---------- | ------------------ |
| Admin     | admin        | admin123   | Full system access |
| Teacher   | T001 to T020 | teacher123 | After seeding      |
| Student   | S001 to S025 | student123 | After seeding      |

### Admin Workflow
1.  **Login** as admin.
2.  **Create Teachers** - Enter Teacher ID (e.g., T001), name, and password.
3.  **Create Students** - Enter Student ID (e.g., S001), name, and password.
4.  **Create Courses** - Enter Course ID (e.g., CS101) and course name.
5.  **Assign Teachers** - Select a course and assign a teacher to it.
6.  **Enroll Students** - Select a student and enroll them in a course.
7.  **Seed Demo Data** - Click "Seed Demo Data" to populate with test data.

### Teacher Workflow
1.  **Login** as a teacher (e.g., `T001` / `teacher123`).
2.  **View Dashboard** - See a list of assigned courses.
3.  **Click a Course** - View enrolled students for that course.
4.  **Mark Attendance** - Check boxes for students who are present.
5.  **Submit** - Attendance is saved with the current date.

### Student Workflow
1.  **Login** as a student (e.g., `S001` / `student123`).
2.  **View Dashboard** - See personal info and a table of enrolled courses.
3.  **Check Attendance** - View attendance percentage for each course.
    - **Green (>=75%):** Good standing
    - **Orange (50-74%):** Warning
    - **Red (<50%):** Critical

## Demo Data Seeder
The seeder creates realistic demo data for testing.

### What Gets Created
| Data        | Count  | Details                       |
| ----------- | ------ | ----------------------------- |
| Teachers    | 20     | T001-T020, pass: `teacher123` |
| Students    | 25     | S001-S025, pass: `student123` |
| Courses     | 12     | CS101-CS112, various topics   |
| Enrollments | ~95    | Each student in 3-5 courses   |
| Attendance  | ~2500+ | 60 days of weekday attendance |

### Attendance Generation Logic
```
For each of the past 60 days:
  ├── Skip weekends (Saturday/Sunday)
  ├── 87% chance the class happens
  └── For each enrolled student:
      └── 75% chance student is present
```

### Running the Seeder

#### Method 1: Command Line (Recommended)
```batch
# Seed demo data
seeder.exe seed

# Check database status
seeder.exe status

# Clear all data
seeder.exe clear

# Show help
seeder.exe help
```

#### Method 2: Web Interface
1.  Login as admin.
2.  Click the "Seed Demo Data" button.
3.  Type `SEED` to confirm.
4.  Click "Wipe Data & Seed Demo Data".

**Warning:** Seeding will DELETE ALL EXISTING DATA and replace it with demo data.

## Architecture

### Class Diagram (OOAD)
```
                    ┌─────────────────┐
                    │   «abstract»    │
                    │      User       │
                    ├─────────────────┤
                    │ -id: string     │
                    │ -password: string│
                    │ -userType: enum │
                    ├─────────────────┤
                    │ +authenticate() │
                    │ +toCSV()        │
                    │ +fromCSV()      │
                    └────────┬────────┘
                             │
            ┌────────────────┼────────────────┐
            │                │                │
            ▼                ▼                ▼
     ┌──────────┐     ┌───────────┐    ┌───────────┐
     │  Admin   │     │  Teacher  │    │  Student  │
     ├──────────┤     ├───────────┤    ├───────────┤
     │-username │     │-teacherId │    │-studentId │
     │          │     │-name      │    │-name      │
     └──────────┘     └─────┬─────┘    └─────┬─────┘
                            │                │
                            ▼                │
                     ┌───────────┐           │
                     │  Course   │           │
                     ├───────────┤           │
                     │-courseId  │           │
                     │-courseName│           │
                     │-teacherId │◄──────────┤
                     │-totalClasses│         │
                     └─────┬─────┘           │
                           │                 │
                           ▼                 ▼
                    ┌─────────────────────────┐
                    │      Enrollment         │
                    ├─────────────────────────┤
                    │ -enrollmentId           │
                    │ -studentId (FK)         │
                    │ -courseId (FK)          │
                    └───────────┬─────────────┘
                                │
                                ▼
                    ┌─────────────────────────┐
                    │   AttendanceRecord      │
                    ├─────────────────────────┤
                    │ -recordId               │
                    │ -studentId (FK)         │
                    │ -courseId (FK)          │
                    │ -date                   │
                    └─────────────────────────┘
```

### MVC Pattern
```
┌─────────────────────────────────────────────────────────────────┐
│                         MVC Architecture                         │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│   MODEL                CONTROLLER              VIEW              │
│   ─────                ──────────              ────              │
│   User.cpp             main.cpp                HTMLTemplates.h   │
│   Admin.cpp            └─ svr.Get()            └─ LOGIN_PAGE     │
│   Teacher.cpp          └─ svr.Post()           └─ ADMIN_DASHBOARD│
│   Student.cpp                                  └─ TEACHER_DASHBOARD
│   Course.cpp                                   └─ STUDENT_DASHBOARD
│   Enrollment.cpp                               └─ CSS_STYLES     │
│   AttendanceRecord.cpp                                           │
│   CSVManager.cpp                                                 │
│                                                                  │
└─────────────────────────────────────────────────────────────────┘
```

## Data Storage
All data is stored in CSV files in the `data/` folder.

### File Formats
**admins.csv**
```csv
username,password
admin,admin123
```
**teachers.csv**
```csv
teacherId,name,password
T001,Ahmed Khan,teacher123
T002,Fatima Hassan,teacher123
```
**students.csv**
```csv
studentId,name,password
S001,Hamza Malik,student123
S002,Sara Ahmed,student123
```
**courses.csv**
```csv
courseId,courseName,teacherId,totalClasses
CS101,Introduction to Programming,T001,42
CS102,Data Structures,T002,38
```
**enrollments.csv**
```csv
enrollmentId,studentId,courseId
E1,S001,CS101
E2,S001,CS102
```
**attendance.csv**
```csv
recordId,studentId,courseId,date
A1,S001,CS101,2024-01-15
A2,S001,CS101,2024-01-16
```

## Troubleshooting
### Common Issues
1.  **"httplib.h not found"**
    **Solution**: CMake should auto-download it. If not, run this command:
    ```batch
    # Manually download
    curl -o libraries/httplib.h https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
    ```
2.  **"Port 8080 already in use"**
    **Solution**: Close other applications using port 8080, or modify the port in `main.cpp`:
    ```cpp
    svr.listen("localhost", 8081);  // Change to different port
    ```
3.  **"Data folder not found"**
    **Solution**: The program creates it automatically. If issues persist, create it manually:
    ```batch
    mkdir data
    ```
4.  **"Access denied" errors**
    **Solution**: Run the command prompt as Administrator, or check folder permissions.
5.  **Build fails with "ws2_32" errors**
    **Solution**: Ensure you're linking the Windows Sockets library. Add `ws2_32.lib` to your compile command.
6.  **Attendance not saving**
    **Solution**: Check that the teacher is assigned to the course, students are enrolled, and the date is not a duplicate.

## Security Notes
**Warning:** This is a demo project for educational purposes.

- Passwords are stored in plain text.
- Sessions are stored in memory and lost on restart.
- No HTTPS/SSL encryption.
- No rate limiting or CSRF protection.

For production use, implement password hashing (bcrypt, argon2), persistent session storage, HTTPS, input sanitization, and CSRF tokens.

## API Routes
| Method | Route                      | Description              | Access        |
| ------ | -------------------------- | ------------------------ | ------------- |
| GET    | `/`                        | Redirect to login        | Public        |
| GET    | `/login`                   | Login page               | Public        |
| POST   | `/login`                   | Process login            | Public        |
| GET    | `/logout`                  | Logout user              | Authenticated |
| GET    | `/admin`                   | Admin dashboard          | Admin         |
| POST   | `/admin/create-teacher`    | Create teacher           | Admin         |
| POST   | `/admin/create-student`    | Create student           | Admin         |
| POST   | `/admin/create-course`     | Create course            | Admin         |
| POST   | `/admin/assign-teacher`    | Assign teacher to course | Admin         |
| POST   | `/admin/enroll-student`    | Enroll student           | Admin         |
| GET    | `/admin/seed`              | Seed confirmation page   | Admin         |
| POST   | `/admin/seed`              | Execute seeding          | Admin         |
| GET    | `/teacher`                 | Teacher dashboard        | Teacher       |
| GET    | `/teacher/course/:id`      | View course attendance   | Teacher       |
| POST   | `/teacher/mark-attendance` | Submit attendance        | Teacher       |
| GET    | `/student`                 | Student dashboard        | Student       |

## Contributing
1.  Fork the repository.
2.  Create a feature branch (`git checkout -b feature/AmazingFeature`).
3.  Commit changes (`git commit -m 'Add AmazingFeature'`).
4.  Push to the branch (`git push origin feature/AmazingFeature`).
5.  Open a Pull Request.

## License
This project is licensed under the MIT License - see the `LICENSE` file for details.

## Acknowledgments
- cpp-httplib - A header-only HTTP/HTTPS server library.
- Built as a semester project demonstrating OOAD principles in C++.

## Contact
M. Ibrahim - me@mibrahim.pro

Project Link: [https://github.com/MIbrahimPro/Web-Based-LMS-in-CPP-](https://github.com/MIbrahimPro/Web-Based-LMS-in-CPP-.git)

<p align="center">Made with C++</p>
<p align="center">****</p>
<p align="center"> Made with love ❤️ by MIbrahim Pro </p>
<p align="center"> Made with httplib </p>