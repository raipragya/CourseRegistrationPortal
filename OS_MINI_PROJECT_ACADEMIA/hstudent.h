
void add_new_student(int cfd){
	int s_id;
	struct student new_stud;
	struct message msg;
	normalmessage(cfd, 1, 1, "\nEnter Name: ");
	structmessage(cfd,&msg);
	strncpy(new_stud.s_name,msg.body, sizeof(new_stud.s_name));

	normalmessage(cfd, 1, 0, "\nEnter Gender (M/F): ");
	structmessage(cfd,&msg);
	new_stud.s_gender = msg.body[0];

	normalmessage(cfd, 1, 1, "\nEnter phone number: ");
	structmessage(cfd,&msg);
	strncpy(new_stud.s_phone,msg.body,sizeof(new_stud.s_phone));

	normalmessage(cfd, 1, 1, "\nEnter email: ");
	structmessage(cfd,&msg);
	strncpy(new_stud.s_email,msg.body,sizeof(new_stud.s_email));

	new_stud.course_count = 0;
	new_stud.active_status = 1;
	new_stud.login_status = 0;
	for(int i=0; i<5; i++){
		new_stud.enrolled_courses[i] = 0;
	}
	strcpy(new_stud.s_login_id,"");
	normalmessage(cfd, 0, 1, "\nGot Details ...");
	s_id=set_new_student(&new_stud);
	integerMessage(cfd, 0,1, "ID: ",s_id);
	if(s_id==-1){
		normalmessage(cfd, 0, 1, "\nCannot Save Student...");
		return;
	}
	else{
		StringMessage(cfd, 0, 1, "\nStudent Created Successfully!\nNote: \nLogin-Id", new_stud.s_login_id);
		StringMessage(cfd, 0, 1, "\nPassword", new_stud.s_password);
	}
}

void view_student(int cfd){
	int student_id;
	struct student stud;
	struct message msg;
	normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
	structmessage(cfd,&msg);
	
	student_id = atoi(msg.body+4);
	stud=get_student(student_id);
	if(stud.s_id==0){
		normalmessage(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}
	integerMessage(cfd, 0, 1, "\nStudent active status", stud.active_status);
	StringMessage(cfd, 0, 1, "\nStudent name", stud.s_name);
	StringMessage(cfd, 0, 1, "\nStudent phone", stud.s_phone);
	StringMessage(cfd, 0, 1, "\nStudent email", stud.s_email);
}

// Function to deactivate a student account and update related course enrollments
void removeStudent(int cfd) {
    int student_id, total;
    struct student stud;
    struct message msg;

    // Prompt user to enter Login ID
    normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
    
    // Read the message containing student ID from the client
    structmessage(cfd, &msg);
    
    // Extract the student ID from the message (assuming message starts with "ID: ")
    student_id = atoi(msg.body + 4);

    // Fetch the student details based on the student ID
    stud = get_student(student_id);

    // Check if student exists
    if (stud.s_id == 0) {
        normalmessage(cfd, 0, 1, "\nStudent not found.");
        return;
    }

    // Get total number of active student records
    total = get_all_record(0);

    // Proceed only if student is currently active
    if (stud.active_status == 1) {

        // If student is enrolled in any courses, update them
        if (stud.course_count > 0) {
            for (int i = 0; i < 5; i++) {
                if (stud.enrolled_courses[i] > 0) {
                    // Fetch each enrolled course
                    struct course cour = get_course(stud.enrolled_courses[i]);
                    int course_id = cour.c_id;

                    // Only update if the course is active
                    if (cour.active_status == 1) {
                        // Remove student from the course
                        stud.enrolled_courses[i] = 0;
                        cour.avail_seats++; // Increase available seats in the course

                        // Update the course data
                        int set3 = set_course(course_id, &cour);
                    }
                }
            }
        }

        // Deactivate the student account
        stud.active_status = 0;

        // Update student record and total active student count
        int set1 = set_student(student_id, &stud);
        int set2 = set_all_record(0, total - 1);

        // Confirm successful deactivation
        if (set1 == 1 && set2 == 1) {
            normalmessage(cfd, 0, 1, "\nStudent got deactivated");
        }
    }
    else {
        // Student is already inactive
        normalmessage(cfd, 0, 1, "\nStudent does not exist");
    }
}

void modify_student_details(int cfd) {
	int student_id;
	struct student stud;
	struct message msg;
	normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
	structmessage(cfd, &msg);

	student_id = atoi(msg.body + 4);
	stud = get_student(student_id);

	if (stud.s_id == 0) 
	{
		normalmessage(cfd, 0, 1, "\nStudent not found.");
		return;
	}

	if (stud.active_status == 1)
	 {
		// Ask for new name
		normalmessage(cfd, 1, 1, "\nEnter new name (leave blank to keep unchanged): ");
		structmessage(cfd, &msg);
		if (strlen(msg.body) > 0)
			strncpy(stud.s_name, msg.body, sizeof(stud.s_name));

		// Ask for new phone
		normalmessage(cfd, 1, 1, "\nEnter new phone (10 digits, leave blank to keep unchanged): ");
		structmessage(cfd, &msg);
		if (strlen(msg.body) == 10)
			strncpy(stud.s_phone, msg.body, sizeof(stud.s_phone));

		// Ask for new email
		normalmessage(cfd, 1, 1, "\nEnter new email (leave blank to keep unchanged): ");
		structmessage(cfd, &msg);
		if (strlen(msg.body) > 0)
			strncpy(stud.s_email, msg.body, sizeof(stud.s_email));

		int set1 = set_student(student_id, &stud);
		if (set1 == 1) {
			normalmessage(cfd, 0, 1, "\nStudent details updated successfully.");
		} else {
			normalmessage(cfd, 0, 1, "\nFailed to update student details.");
		}
	} else {
		normalmessage(cfd, 0, 1, "\nStudent does not exist or is inactive.");
	}
}

void activate_student(int cfd) {
	int student_id;
	struct student stud;
	struct message msg;
	normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
	structmessage(cfd, &msg);

	student_id = atoi(msg.body + 4);
	stud = get_student(student_id);

	if (stud.s_id == 0) {
		normalmessage(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}

	if (stud.active_status == 0)
	 {
		stud.active_status = 1;
		int result = set_student(student_id, &stud);
		if (result == 1) 
		{
			normalmessage(cfd, 0, 1, "\nStudent activated successfully.");
		} else 
		{
			normalmessage(cfd, 0, 1, "\nFailed to activate student.");
		}
	} else 
	{
		normalmessage(cfd, 0, 1, "\nStudent is already active.");
	}
}



void change_password_student(int cfd, int student_id)
 {
    struct student stud;
    struct message msg;

    // Retrieve student record
    stud = get_student(student_id);
    if (stud.s_id == 0 || stud.active_status == 0)
	 {
        normalmessage(cfd, 0, 1, "\nStudent does not exist or is inactive.");
        return;
    }

    // Prompt for current password
    normalmessage(cfd, 1, 1, "\nEnter your current password: ");
    structmessage(cfd, &msg);
    if (strcmp(stud.s_password, msg.body) != 0)
	 {
        normalmessage(cfd, 0, 1, "\nIncorrect current password.");
        return;
    }

    // Prompt for new password
    normalmessage(cfd, 1, 1, "\nEnter your new password (max 10 characters): ");
    structmessage(cfd, &msg);

    if (strlen(msg.body) > 10) 
	{
        normalmessage(cfd, 0, 1, "\nPassword too long.It must be less than equal to 10 characters.");
        return;
    }

    // Update password
    strcpy(stud.s_password, msg.body);
    int status = set_student(student_id, &stud);

    if (status == 1)
	{
        normalmessage(cfd, 0, 1, "\nPassword updated successfully.");
    } else
	{
        normalmessage(cfd, 0, 1, "\nFailed to update password.");
    }
}

// Function to view all courses a student is enrolled in
void view_enrolled_course(int cfd, int student_id)
{
    struct student stud;
    struct message msg;

    // Retrieve student record using student_id
    stud = get_student(student_id);

    // Check if student exists
    if (stud.s_id == 0) {
        normalmessage(cfd, 0, 1, "\nStudent not Found.");
        return;
    }

    // If the student is enrolled in at least one course
    if (stud.course_count > 0) {
        for (int i = 0; i < 5; i++) {
            // For each non-zero enrolled course ID, fetch course info and send it
            if (stud.enrolled_courses[i] != 0) {
                struct course cour = get_course(stud.enrolled_courses[i]);
                integerMessage(cfd, 0, 1, "\n", cour.c_id);     // Send course ID
                StringMessage(cfd, 0, 1, " ", cour.c_name);     // Send course name
            }
        }
    }
    else {
        // No courses found for this student
        normalmessage(cfd, 0, 1, "\nNo Course enrolled");
    }
}

// Function to enroll a student in a course
void enroll_course(int cfd, int student_id)
{
    int course_id;
    struct student stud;
    struct message msg;

    // Ask client for the Course ID to enroll
    normalmessage(cfd, 1, 1, "\nEnter Course ID: ");
    
    // Read input from the client
    structmessage(cfd, &msg);
    
    // Convert the received course ID to integer
    course_id = atoi(msg.body);

    // Get the student record
    stud = get_student(student_id);

    // Check if student exists
    if (stud.s_id == 0) {
        normalmessage(cfd, 0, 1, "\nStudent not found.");
        return;
    }

    // Check if student is already enrolled in the course
    int flag = 0;
    for (int j = 0; j < 5; j++) {
        if (stud.enrolled_courses[j] == course_id) {
            flag = 1;
            break;
        }
    }

    // Proceed only if the student isn't already enrolled and hasn't hit course limit
    if (flag == 0 && stud.course_count < 5) {
        for (int i = 0; i < 5; i++) {
            // Find an empty slot in enrolled courses
            if (stud.enrolled_courses[i] == 0) {

                // Get the course record
                struct course cour = get_course(course_id);

                // Validate course existence
                if (cour.c_id == 0) {
                    normalmessage(cfd, 0, 1, "\nNo id");
                    return;
                }
                else {
                    // Check if course has available seats
                    if (cour.avail_seats > 0) {
                        // Enroll student in the course
                        stud.enrolled_courses[i] = course_id;
                        stud.course_count++;
                        cour.avail_seats--;

                        // Update student and course records
                        int set1 = set_student(student_id, &stud);
                        int set2 = set_course(course_id, &cour);

                        if (set1 == 1 && set2 == 1) {
                            // Notify client of successful enrollment
                            normalmessage(cfd, 0, 1, "\nCourse enrolled successfully ");
                            integerMessage(cfd, 0, 1, "", cour.c_id);
                            StringMessage(cfd, 0, 1, " ", cour.c_name);
                            return;
                        }
                        else {
                            // If update failed
                            normalmessage(cfd, 0, 1, "\nUnable to update ...");
                            return;
                        }
                    }
                    else {
                        // No seats left
                        normalmessage(cfd, 0, 1, "\nNo seats available in this course");
                        return;
                    }
                }
            }
        }
    }
    else {
        // Student already enrolled or exceeded course limit
        normalmessage(cfd, 0, 1, "\nYou cannot enroll in more than five courses or to an already enrolled course");
        return;
    }
}


void drop_course(int cfd, int student_id)
{
	int course_id;
	struct student stud;
	struct message msg;

	normalmessage(cfd, 1, 1, "\nEnter Course ID: ");
	structmessage(cfd,&msg);
	
	course_id=atoi(msg.body);	
	stud=get_student(student_id);
	if(stud.s_id==0){
		normalmessage(cfd, 0, 1, "\nStudent not found.");
		return;
	}
	if(stud.course_count>0)
	{
		for(int i=0; i<5; i++)
		{
			if(stud.enrolled_courses[i]==course_id)
			{
				struct course cour = get_course(course_id);
				stud.enrolled_courses[i]=0;
				stud.course_count++;
				cour.avail_seats++;
				int set1 = set_student(student_id, &stud);
				int set2 = set_course(course_id, &cour);
				if(set1==1 && set2==1)
				{
					normalmessage(cfd, 0, 1, "\nCourse dropped successfully ");
					integerMessage(cfd, 0, 1, "", cour.c_id);
					StringMessage(cfd, 0, 1, " ", cour.c_name);
					return;
				}
				else
				{
					normalmessage(cfd, 0, 1, "\nUnable to update ...");
					return;
				}
				
			}
			else
			{
				normalmessage(cfd, 0, 1, "\nGiven course not enrolled");
				return;
			}
		}
	}
	else
	{
		normalmessage(cfd, 0, 1, "\nNo course enrolled yet");
		return;
	}	

}

