
void menu(int cfd)
{
    int choice;
    struct message msg;
    char login_id[15];
    char password[15];

    while (1) {
        normalmessage(cfd, 1, 0, "\n\n---------------------------Welcome Back To Academia :: Course Registration System--------------------\n\nLogin type : \n1. Faculty\n2. Student\n3. Admin\n4. Exit\n\nEnter your choice : ");
        structmessage(cfd, &msg); 
        choice = atoi(msg.body);

        normalmessage(cfd, 1, 1, "\nEnter Login ID: ");
        structmessage(cfd, &msg);
        strncpy(login_id, msg.body, 10);
        login_id[10] = '\0';

        normalmessage(cfd, 1, 2, "\nEnter Password: ");
        structmessage(cfd, &msg);
        strncpy(password, msg.body, 10);
        password[10] = '\0';

        switch (choice) {
            case 1:
                login_faculty(cfd, login_id, password);
                break;
            case 2:
                login_student(cfd, login_id, password);
                break;
            case 3:
                login_admin(cfd, login_id, password);
                break;
            case 4:
                normalmessage(cfd, 0, 0, "");
                exit(0);
            default:
                normalmessage(cfd, 0, 1, "Please enter correct choice ...\n");
        }
    }
}
void student_menu(int cfd, int student_id)
{
    int choice;
    struct message msg;
    while(1){
    normalmessage(cfd, 1, 0, "\n\n------------------Welcome to Student Menu--------------------\n\n1. View_Courses\n2. Enroll in new Course\n3. Unenroll from a course\n4. View Enrolled Courses\n5.Change password\n6. Logout and Exit\n\nENTER YOUR CHOICE : ");
    structmessage(cfd,&msg); 
    choice = atoi(msg.body);

    switch (choice) {
    case 1:
        view_all_course(cfd);
        break;

    case 2:
	    enroll_course(cfd, student_id);
        break;

    case 3:
    	drop_course(cfd, student_id);
        break;

    case 4:
    	view_enrolled_course(cfd, student_id);
    	break;
    case 5:
        change_password_student(cfd,student_id);
        break;
    case 6:
    	normalmessage(cfd, 0, 0, "");
    	exit(0);
    	break;

    default:
       	printf("Please enter correct choice...\n");
        break;
    }
}
}
void faculty_menu(int cfd, int faculty_id)
{
    int choice;
    struct message msg;
    while(1){
    normalmessage(cfd, 1, 0, "\n\n-----------------------------------Welcome to Faculty Menu---------------------------\n\n1. View Offering Courses\n2. Add a new Course\n3. Remove Offered Course\n4. Update Offered Course\n5.Change password\n6. Logout and Exit\n\nENTER YOUR CHOICE : ");
    structmessage(cfd,&msg); 

    choice = atoi(msg.body);
    switch (choice) {
    case 1:
        view_offered_course(cfd, faculty_id);
        break;

    case 2:
	    add_course(cfd, faculty_id);
        break;

    case 3:
    	remove_course(cfd, faculty_id);
        break;

    case 4:
    	update_course(cfd, faculty_id);
    	break;
    case 5:
        change_password_faculty(cfd,faculty_id);
        break;
    case 6:
    	normalmessage(cfd, 0, 0, "");
    	exit(1);
    	break;

    default:
       	printf("Please enter correct choice...\n");
        break;
    }
}
}
void admin_menu(int cfd)
{
    int choice;
    struct message msg;
    // Creating a Main
    // menu for the user
   while(1){
    normalmessage(cfd, 1, 0, "\n\n-------------------------------------Welcome to admin Menu-------------------------------------\n\n1. Add New Student\n2. View Student\n3. Remove Student\n4. Add New Faculty\n5. View Faculty\n6. Remove Faculty\n7.activate_student\n8.modify_student_details\n9.modify_faculty_details\n10. Logout and Exit\n\nENTER YOUR CHOICE : ");
    structmessage(cfd,&msg); 

    choice = atoi(msg.body);
    switch (choice) {
    case 1:
        add_new_student(cfd);
        break;

    case 2:
	view_student(cfd);
        break;

    case 3:
    	removeStudent(cfd);
        break;

    case 4:
    	add_new_faculty(cfd);
    	break;
    case 5:
        view_faculty(cfd);
        break;
    case 6:
	    removeFaculty(cfd);
    	break;
    case 7:
        activate_student(cfd);
        break;
    case 8:
        modify_student_details(cfd);
        break;
    case 9:
        modify_faculty_details(cfd);
        break;
    case 10:
    	normalmessage(cfd, 0, 0, "");
    	exit(1);
    	break;	
    default:
       	printf("Please enter valid choice.\n");
       	break;
    }
}
}

