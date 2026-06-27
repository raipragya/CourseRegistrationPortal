# Course Registration Portal — Academia

A terminal-based **Course Registration Portal** built in **C** using **TCP socket programming**, designed to simulate a real-world academic registration system with multiple user roles: **Admin**, **Faculty**, and **Student**.

The project focuses on core Operating System and Network Programming concepts such as **client-server communication**, **process-based concurrency**, **file-based persistence**, and **record synchronization using file locks**.

---

## Overview

This system allows students, faculty, and administrators to interact with a centralized academic registration server.

The application follows a **client-server architecture**:

- The **server** stores and manages all academic records.
- Multiple **clients** connect to the server over TCP.
- Each client is handled independently by the server using process-based concurrency.
- Shared data is stored in files under the `Records/` directory.
- File locking is used to prevent inconsistent updates during concurrent access.

---

## Key Features

### Admin

- Add new students
- View student records
- Remove students
- Add new faculty
- View faculty records
- Remove faculty
- Activate student accounts
- Modify student details
- Modify faculty details

### Student

- View available courses
- Enroll in a course
- Unenroll from a course
- View enrolled courses
- Change password

### Faculty

- View offered courses
- Add a new course
- Remove an offered course
- Update offered course details
- Change password

---

## Concurrency Highlights

This project is designed to handle multiple users at the same time.

### 1. Concurrent Client Handling using `fork()`

The server continuously waits for incoming client connections using `accept()`.

Whenever a new client connects, the server creates a separate child process using:

```c
fork();
````

This means each connected client gets an independent server-side process.

As a result:

* Multiple students can access the portal simultaneously.
* Faculty and admin users can operate without blocking each other.
* One slow or inactive client does not stop the server from accepting other clients.
* The parent server process keeps listening for new connections while child processes handle active sessions.

Conceptually:

```text
                +----------------+
Client 1 -----> |                | -----> Child Process 1
Client 2 -----> |  Main Server   | -----> Child Process 2
Client 3 -----> |  Process       | -----> Child Process 3
                +----------------+
```

This demonstrates **process-level concurrency**, where each client session runs independently.

---

### 2. TCP-Based Client-Server Communication

The system uses TCP sockets for reliable communication between client and server.

The server:

* Creates a socket using `socket()`
* Binds it to port `8083`
* Listens for incoming clients using `listen()`
* Accepts client connections using `accept()`

The client:

* Creates a socket
* Connects to the server using `connect()`
* Sends user input to the server
* Receives menu options, prompts, and responses from the server

This enables a clear separation between the user interface and the data-processing logic.

---

### 3. File Locking using `fcntl()`

Since multiple clients may try to access or modify shared records at the same time, the project uses file locking with `fcntl()`.

File locks help prevent race conditions such as:

* Two admins modifying records simultaneously
* A student enrolling while course data is being updated
* Corrupted file writes due to overlapping write operations
* Inconsistent record counts or duplicate IDs

Write locks are applied before modifying shared files and released after the operation is completed.

Example idea:

```c
struct flock lock;
lock.l_type = F_WRLCK;
fcntl(fd, F_SETLKW, &lock);
```

After the write operation:

```c
lock.l_type = F_UNLCK;
fcntl(fd, F_SETLK, &lock);
```

This ensures that critical sections involving file updates are protected.

---

## Why Concurrency Matters Here

In a real course registration system, many users may access the portal at the same time.

For example:

* Multiple students may try to enroll in courses together.
* Faculty may update course details while students are viewing available courses.
* Admin may add or modify records while users are logged in.

Without concurrency control, the system could face problems like:

* Data corruption
* Lost updates
* Duplicate IDs
* Incorrect course enrollment information
* Inconsistent student or faculty records

This project addresses these issues using:

* **Fork-based concurrent client handling**
* **File locks for safe record updates**
* **Centralized server-side validation**
* **Persistent file-based storage**

---

## Tech Stack

| Component       | Technology            |
| --------------- | --------------------- |
| Language        | C                     |
| Communication   | TCP Sockets           |
| Concurrency     | `fork()` system call  |
| Synchronization | `fcntl()` file locks  |
| Storage         | File-based records    |
| Interface       | Terminal-based client |
| Architecture    | Client-server model   |

---

## Project Structure

```text
.
├── client.c
├── server.c
├── set_admin.c
├── set_record.c
├── Records/
│   ├── admin.txt
│   ├── record.txt
│   ├── student records
│   ├── faculty records
│   └── course records
├── functionsd.h
├── ReadWrite.h
├── record_set.h
├── recordg_s.h
├── structs.h
├── hstudent.h
├── hfaculty.h
├── hcourse.h
├── hlogin.h
├── hmenu.h
├── facultyg_s.h
├── studentg_s.h
└── coursegs.h
```

---

## Important Files

### `server.c`

Handles the main server-side execution.

Responsibilities:

* Creates the server socket
* Binds the socket to port `8083`
* Listens for client connections
* Accepts clients in a loop
* Uses `fork()` to handle each client concurrently
* Calls server-side menu handling logic for each connected client

---

### `client.c`

Handles the client-side interface.

Responsibilities:

* Creates a client socket
* Connects to the server
* Displays prompts and menus received from the server
* Reads user input
* Sends user responses back to the server
* Closes the connection gracefully

---

### `set_admin.c`

Initializes the admin account.

Responsibilities:

* Creates or opens the admin record file
* Locks the file before writing
* Writes the initial admin details
* Unlocks the file after writing

---

### `set_record.c`

Initializes the global record metadata.

Responsibilities:

* Creates or opens the main record file
* Initializes student, faculty, and course counts
* Initializes next available IDs
* Uses file locking while writing initial data

---

## How to Compile and Run

### Step 1: Create the records directory

```bash
mkdir Records
```

---

### Step 2: Initialize the admin account

```bash
gcc -o set_admin set_admin.c
./set_admin
```

---

### Step 3: Initialize system records

```bash
gcc -o set_record set_record.c
./set_record
```

---

### Step 4: Compile and start the server

```bash
gcc -o server server.c
./server
```

The server starts listening on port `8083`.

---

### Step 5: Compile and run the client

Open a new terminal and run:

```bash
gcc -o client client.c
./client
```

To test concurrency, open multiple terminals and run several clients at the same time:

```bash
./client
```

Each client will be handled by a separate child process on the server side.

---

## Sample Usage Flow

```text
1. Start the server.
2. Open multiple client terminals.
3. Login as Admin, Faculty, or Student.
4. Admin creates students and faculty.
5. Faculty adds offered courses.
6. Students view and enroll in courses.
7. Multiple users can interact with the server concurrently.
```

---

## Operating System Concepts Demonstrated

This project demonstrates several important OS-level concepts:

* Process creation using `fork()`
* Concurrent client handling
* Inter-process independence
* File locking
* Critical section protection
* Race condition prevention
* Persistent file-based storage
* System calls such as `socket()`, `bind()`, `listen()`, `accept()`, `read()`, `write()`, `open()`, and `fcntl()`

---

## Network Programming Concepts Demonstrated

The project also demonstrates core networking concepts:

* TCP socket creation
* Client-server architecture
* Server binding to a port
* Listening for incoming connections
* Accepting client requests
* Reliable message exchange between client and server

---

## Concurrency Testing

The project can be tested by launching multiple clients in different terminals.

Example:

```bash
# Terminal 1
./server

# Terminal 2
./client

# Terminal 3
./client

# Terminal 4
./client
```

Expected behavior:

* All clients should be able to connect to the server.
* Each client should receive an independent menu session.
* Actions performed by one client should not block other clients.
* Shared file updates should remain consistent because of locking.

---

## Learning Outcome

This project is not just a basic course registration system. It is an implementation of a **concurrent networked application** in C.

It combines:

* Role-based access control
* Persistent record management
* TCP socket communication
* Multi-client handling
* File synchronization

The project provides hands-on understanding of how real-world server systems manage multiple users while protecting shared data from concurrent access issues.

---

## Future Improvements

Possible extensions include:

* Replacing file storage with a database
* Supporting remote clients over a network

---
