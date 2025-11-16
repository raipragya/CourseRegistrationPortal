// Structure to store student details
struct student {
    int s_id;                      // Unique student ID
    char s_name[25];              // Student's name
    char s_gender;                // Gender (e.g., 'M', 'F', 'O')
    char s_phone[10];             // 10-digit phone number (stored as a string to preserve leading zeroes)
    char s_email[35];             // Student's email address
    char s_login_id[11];          // Login ID used for authentication
    char s_password[11];         // Password used for authentication
    int enrolled_courses[5];     // Array of course IDs the student is enrolled in (up to 5 courses)
    int course_count;            // Number of currently enrolled courses
    int login_status;            // Indicates if the student is logged in (e.g., 1 for logged in, 0 for logged out)
    int active_status;           // Indicates if the account is active (1 for active, 0 for deactivated)
};
// Structure to store faculty details
struct faculty {
    int f_id;                     // Unique faculty ID
    char f_name[25];             // Faculty member's name
    char f_gender;               // Gender
    char f_phone[10];            // Phone number
    char f_email[35];            // Faculty's email address
    char f_department[3];        // Department code (e.g., "CS", "ME")
    char f_login_id[11];         // Faculty login ID
    char f_password[11];         // Faculty password
    int courses[3];              // Courses assigned to the faculty (up to 3)
    int course_count;            // Number of courses assigned
    int login_status;            // Indicates if the faculty is logged in
    int active_status;           // Account active status
};

// Structure to define a generic message used for communication between client/server
struct message {
    int id;                      // Unique message ID or sequence number
    int type;                    // Type of message (e.g., 0 for control, 1 for data)
    int action;                  // Specific action to take (based on context)
    char body[1000];             // Message body containing the content (question, response, etc.)
};

// Structure to store administrator details
struct admin 
{
    int id;                      // Admin ID
    char name[25];              // Administrator's name
    char login_id[11];          // Admin login ID
    char password[11];          // Admin password
};

// Structure to hold a summary of record statistics
struct record {
    int total_student;          // Total number of students in the system
    int total_faculty;          // Total number of faculty in the system
    int total_course;           // Total number of courses available
    int new_s;                  // Counter for new student registrations (for tracking/notifications)
    int new_f;                  // Counter for new faculty registrations
    int new_c;                  // Counter for new courses added
};
// Structure to represent a course
struct course {
    int c_id;                   // Unique course ID
    char c_name[5];             // Short course name or code (e.g., "CS01")
    int f_id;                   // Faculty ID of the course instructor
    int credits;                // Number of credits the course carries
    int total_seats;           // Maximum seats available in the course
    int avail_seats;           // Number of seats currently available
    int active_status;         // Indicates if the course is currently active (1 for active, 0 for inactive)
};