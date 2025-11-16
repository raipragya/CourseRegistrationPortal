
void login_student(int cfd, char * id, char * pass)
{
	struct message msg;
	int student_id = atoi(id+4);
	struct student stud = get_student(student_id);
	if(stud.s_id==0){
		normalmessage(cfd, 0, 1, "\nStudent doesn't exit");
		return;
	}
	else
	{
		if(stud.active_status==1)
		{
			if(strcmp(stud.s_login_id, id)==0 && strcmp(stud.s_password, pass)==0)
			{
				normalmessage(cfd, 0, 1, "\nLogin Successful ... ");
				student_menu(cfd, student_id);
				return;
			}
			else
			{
				normalmessage(cfd, 0, 1, "\nIncorrect login ID or password");
				return;
			}
		}
		else
		{
			normalmessage(cfd, 0, 1, "\nStudent is inactive");
		}
	}
}

void login_faculty(int cfd, char * id, char * pass)
{
	struct message msg;
	int faculty_id = atoi(id+3);
	struct faculty fac = get_faculty(faculty_id);
	if(fac.f_id==0){
		normalmessage(cfd, 0, 1, "\nFaculty doesn't exit");
		return;
	}
	else
	{
		if(fac.active_status==1)
		{
			if(strcmp(fac.f_login_id, id)==0 && strcmp(fac.f_password, pass)==0)
			{
				normalmessage(cfd, 0, 1, "\nLogin Successful ... ");
				faculty_menu(cfd, faculty_id);
				return;
			}
			else
			{
				normalmessage(cfd, 0, 1, "\nIncorrect login ID or password");
				return;
			}
		}
		else
		{
			normalmessage(cfd, 0, 1, "\nFaculty is inactive");
		}
	}
}

void login_admin(int cfd, char * id, char * pass)
{
	struct message msg;
	struct admin ad = get_admin();
	if(ad.id!=0){
		normalmessage(cfd, 0, 1, "\nAdmin doesn't exit");
		return;
	}
	else
	{
		if(strcmp("pragya", id)==0 && strcmp("pragya", pass)==0)
		{
			normalmessage(cfd, 0, 1, "\nLogin Successful ... ");
			admin_menu(cfd);
			return;
		}
		else
		{
			normalmessage(cfd, 0, 1, "\nIncorrect login ID or password");
			return;
		}
	}
}
struct admin get_admin()
{
	int rd, fd, offset;
	struct admin ad;

	fd=open("./Record_File/admin.txt",O_RDONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return (struct admin){0, "NULL", "NULL", "NULL"};
	}
	offset=lseek(fd,(0)*sizeof(struct admin),SEEK_SET);
	if(offset==-1)
	{
		perror("Error while Repositioning in customer File ");
		return (struct admin){0, "NULL", "NULL", "NULL"};
	}
	struct flock mylock = {F_RDLCK, SEEK_SET, (0)*sizeof(struct admin), sizeof(struct admin), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return (struct admin){0, "NULL", "NULL", "NULL"};
	}
	rd=read(fd,&ad,sizeof(ad));
	mylock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &mylock);
	if(rd<=0){
		perror("Cannot write into the file");
		return (struct admin){0, "NULL", "NULL", "NULL"};
	}
	close(fd);
	return ad;
}
