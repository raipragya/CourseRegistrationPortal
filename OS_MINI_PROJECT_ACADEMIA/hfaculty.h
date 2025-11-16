void add_new_faculty(int cfd){
	int f_id;
	struct faculty new_f;
	struct message msg;

	//Getting details
	normalmessage(cfd, 1, 1, "\nEnter Name: ");
	structmessage(cfd,&msg);
	strncpy(new_f.f_name,msg.body, sizeof(new_f.f_name));

	normalmessage(cfd, 1, 0, "\nEnter Gender (M/F): ");
	structmessage(cfd,&msg);
	new_f.f_gender = msg.body[0];

	normalmessage(cfd, 1, 1, "\nEnter phone number: ");
	structmessage(cfd,&msg);
	strncpy(new_f.f_phone,msg.body,sizeof(new_f.f_phone));

	normalmessage(cfd, 1, 1, "\nEnter email: ");
	structmessage(cfd,&msg);
	strncpy(new_f.f_email,msg.body,sizeof(new_f.f_email));
	
	normalmessage(cfd, 1, 1, "\nEnter department: ");
	structmessage(cfd,&msg);
	strncpy(new_f.f_department,msg.body,sizeof(new_f.f_department));

	new_f.course_count = 0;
	new_f.active_status = 1;
	new_f.login_status = 0;
	for(int i=0; i<3; i++){
		new_f.courses[i] = 0;
	}

	//Initializing...
	strcpy(new_f.f_login_id,"");

	//Update to file
	normalmessage(cfd, 0, 1, "\nGot Details ...");
	f_id=set_new_faculty(&new_f);
	integerMessage(cfd, 0,1, "ID: ",f_id);
	if(f_id==-1){
		normalmessage(cfd, 0, 1, "\nCannot Save the Faculty...");
		return;
	}
	else{
		StringMessage(cfd, 0, 1, "\nFaculty Created Successfully!\nNote: \nLogin-Id", new_f.f_login_id);
		StringMessage(cfd, 0, 1, "\nPassword", new_f.f_password);
	}
}

void view_faculty(int cfd){
	int faculty_id;
	struct faculty fac;
	struct message msg;
	char dep[3];
	//Getting details
	normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
	structmessage(cfd,&msg);
	
	faculty_id = atoi(msg.body+3);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	StringMessage(cfd, 0, 1, "\nFaculty name", fac.f_name);
	StringMessage(cfd, 0, 1, "\nFaculty phone", fac.f_phone);
	StringMessage(cfd, 0, 1, "\nFaculty email", fac.f_email);
	strncpy(dep, fac.f_department, 3);
	StringMessage(cfd, 0, 1, "\nFaculty department", dep);
	integerMessage(cfd, 0, 1, "\nFaculty active status", fac.active_status);
}

void removeFaculty(int cfd){
	int faculty_id, total, total_c;
	struct faculty fac;
	struct message msg;

	//Getting details
	normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
	structmessage(cfd,&msg);
	
	faculty_id = atoi(msg.body+3);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	total = get_all_record(1);
	total_c = get_next_record(2);
	if(fac.active_status==1){
		fac.active_status = 0;
		for(int i=0; i<3; i++){
			for(int j=1; j<total_c; j++){
				struct course cour = get_course(j);
				if(fac.courses[i]==cour.c_id){
					int up = update_course_status(cfd, cour.c_id);
				}
			}
		}
		int set1 = set_faculty(faculty_id, &fac);
		int set2 = set_all_record(1, total-1);
		if(set1==1 && set2==1){
			normalmessage(cfd, 0, 1, "\nFaculty removed");
		}
	}
	else{
		normalmessage(cfd, 0, 1, "\nFaculty does not exit");
	}

}
void modify_faculty_details(int cfd){
    int faculty_id;
    struct faculty fac;
    struct message msg;

    // Prompt for login ID
    normalmessage(cfd, 1, 1, "\nEnter Faculty Login ID to Modify: ");
    structmessage(cfd, &msg);

    // Extract faculty ID
    faculty_id = atoi(msg.body + 3);
    fac = get_faculty(faculty_id);

    // Check if faculty exists
    if(fac.f_id == 0 || fac.active_status == 0){
        normalmessage(cfd, 0, 1, "\nFaculty not found or inactive.");
        return;
    }

    // Display current details (optional)
    char buffer[1024];
    snprintf(buffer, sizeof(buffer),
        "\nCurrent Faculty Details:\nName: %s\nPhone: %s\nEmail: %s\nDepartment: %s\n",
        fac.f_name, fac.f_phone, fac.f_email,fac.f_department);
    //normalmessage(cfd, 1, 1, buffer);

    // Modify fields one by one
    normalmessage(cfd, 1, 1, "\nEnter new Name (or . to keep same): ");
    structmessage(cfd, &msg);
    if(strcmp(msg.body, ".") != 0) strncpy(fac.f_name, msg.body, sizeof(fac.f_name));

    normalmessage(cfd, 1, 1, "Enter new Phone (or . to keep same): ");
    structmessage(cfd, &msg);
    if(strcmp(msg.body, ".") != 0) strncpy(fac.f_phone, msg.body, sizeof(fac.f_phone));

    normalmessage(cfd, 1, 1, "Enter new Email (or . to keep same): ");
    structmessage(cfd, &msg);
    if(strcmp(msg.body, ".") != 0) strncpy(fac.f_email, msg.body, sizeof(fac.f_email));

    normalmessage(cfd, 1, 1, "Enter new Department (or . to keep same): ");
    structmessage(cfd, &msg);
    if(strcmp(msg.body, ".") != 0) strncpy(fac.f_department, msg.body, sizeof(fac.f_department));

    // Save updated faculty
    int set_status = set_faculty(faculty_id, &fac);
    if(set_status == 1){
        normalmessage(cfd, 0, 1, "\nFaculty details updated successfully.");
    } else {
        normalmessage(cfd, 0, 1, "\nFailed to update faculty details.");
    }
}
void change_password_faculty(int cfd, int faculty_id) {
    struct faculty fac = get_faculty(faculty_id);
    struct message msg;
    char current_password[20];
    char new_password[20];
    char confirm_password[20];

    // Check if the faculty exists and is active
    if(fac.f_id == 0 || fac.active_status == 0) {
        normalmessage(cfd, 0, 1, "\nFaculty not found or inactive.");
        return;
    }

    // Prompt for current password
    normalmessage(cfd, 1, 1, "\nEnter current password: ");
    structmessage(cfd, &msg);
    strncpy(current_password, msg.body, sizeof(current_password));

    // Check if password matches
    if(strcmp(current_password, fac.f_password) != 0) {
        normalmessage(cfd, 0, 1, "\nIncorrect current password.");
        return;
    }

    // Prompt for new password
    normalmessage(cfd, 1, 1, "Enter new password: ");
    structmessage(cfd, &msg);
    strncpy(new_password, msg.body, sizeof(new_password));

    // Confirm new password
    normalmessage(cfd, 1, 1, "Confirm new password: ");
    structmessage(cfd, &msg);
    strncpy(confirm_password, msg.body, sizeof(confirm_password));

    // Check if passwords match
    if(strcmp(new_password, confirm_password) != 0) {
        normalmessage(cfd, 0, 1, "\nPasswords do not match. Password change failed.");
        return;
    }

    // Update password
    strncpy(fac.f_password, new_password, sizeof(fac.f_password));
    if(set_faculty(faculty_id, &fac) == 1) {
        normalmessage(cfd, 0, 1, "\nPassword changed successfully.");
    } else {
        normalmessage(cfd, 0, 1, "\nFailed to update password. Please try again.");
    }
}


void add_course(int cfd, int faculty_id){
	int course_id;
	struct faculty fac;
	struct message msg;
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	if(fac.active_status==1 && fac.course_count<3){
		course_id = add_new_course(cfd, faculty_id);
		if(course_id!=0){
			fac.courses[fac.course_count] = course_id;
			fac.course_count++;
			int set = set_faculty(faculty_id, &fac);		
			if(set == 1){
				normalmessage(cfd, 0, 1, "\nDone ... ");
			}
			else{
				normalmessage(cfd, 0, 1, "\nUnable to update faculty details");
			}
		}
		else{
			normalmessage(cfd, 0, 1, "\nSorry try again");
		}
	}
	else{
		normalmessage(cfd, 0, 1, "\nYou have already offered 3 courses... Cannot add more course");
	}
}



void view_offered_course(int cfd, int faculty_id){
	struct faculty fac;
	struct message msg;
	
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nFaculty not found");
		return;
	}
	if(fac.course_count>0){
		int count=1;
		for(int i=0; i<3; i++){
			if(fac.courses[i]>0){
				struct course cour = get_course(fac.courses[i]);
				integerMessage(cfd, 0, 1, "\n\nCourse", count);
				integerMessage(cfd, 0, 1, "\nCourse ID", cour.c_id);
				StringMessage(cfd, 0, 1, "\nCourse name", cour.c_name);
				integerMessage(cfd, 0, 1, "\nCourse available seats", cour.avail_seats);
				integerMessage(cfd, 0, 1, "\nCourse active status", cour.active_status);
				integerMessage(cfd, 0, 1, "\nCourse credits", cour.credits);
				integerMessage(cfd, 0, 1, "\nCourse total seats", cour.total_seats);
				count++;
			}
		}
	}
	else{
		normalmessage(cfd, 0, 1, "\nNo Course offered");
	}	
	
}

void remove_course(int cfd, int faculty_id){
	int course_id, total;
	struct faculty fac;
	struct course cour;
	struct message msg;

	//Getting details
	normalmessage(cfd, 1, 1, "\nEnter Course ID: ");
	structmessage(cfd,&msg);
	
	course_id = atoi(msg.body);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nFaculty not found.");
		return;
	}
	if(fac.course_count>0){
		for(int i=0; i<3; i++){
			if(fac.courses[i]==course_id){
				fac.courses[i]=0;
				fac.course_count--;
				int up = update_course_status(cfd, course_id);

				int set = set_faculty(faculty_id, &fac);
				if(up==1 && set==1){
					integerMessage(cfd, 0, 1, " ID", course_id);
					return;
				}
			}
		}
	}
	else{
		normalmessage(cfd, 0, 1, "\nNo course offered yet");
		return;
	}
	return;
}

void update_course(int cfd, int faculty_id){
	int course_id, seats, total;
	struct faculty fac;
	struct course cour;
	struct message msg;

	//Getting details
	normalmessage(cfd, 1, 1, "\nEnter Course ID: ");
	structmessage(cfd,&msg);
	
	course_id = atoi(msg.body);
	
	normalmessage(cfd, 1, 1, "\nEnter Updated Seats: ");
	structmessage(cfd,&msg);
	
	seats = atoi(msg.body);

	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	total = get_next_record(0);
	if(fac.course_count>0){
		for(int i=0; i<3; i++){
			if(fac.courses[i]==course_id){
				struct course cour = get_course(course_id);
				if(seats > cour.total_seats && seats > cour.avail_seats){
					cour.avail_seats = cour.avail_seats + (seats - cour.total_seats);
					cour.total_seats = seats;
				}
				else if(seats < cour.total_seats && seats < cour.avail_seats){
					int diff = cour.total_seats - cour.avail_seats;
					cour.avail_seats = seats - diff;
					cour.total_seats = seats;
				}
				else{
					int diff = cour.total_seats - cour.avail_seats;
					diff = diff - seats;
					cour.total_seats = seats;
					cour.avail_seats = 0;
					for(int i=1; i<total; i++){
						if(diff>0){
							struct student stud = get_student(i);
							if(stud.course_count>0){
								for(int j = 0; j<5; j++){
									if(stud.enrolled_courses[j]==course_id){
										stud.enrolled_courses[j]=0;
										stud.course_count--;
										set_student(stud.s_id, &stud);
										diff--;
										break;
									}
								}
							}
						}
						else{
							break;
						}
					}
				}
				int s = set_course(course_id, &cour);
			}

		}
	}
	else{
		normalmessage(cfd, 0, 1, "\nNo course offered yet");
		return;
	}
	return;
}

