//Kaleb Loo
//shell.cpp
//CPSC 351
//1/13/14
//
//
//Purpose: This program is designed to simulate a UNIX shell.  It provides
//         several built-in system calls as well as the ability to quit,
//         change directories, run background processes, recieve inputs
//         from files, and direct outputs to files.  This program assumes
//         that the make_cmd.cpp and make_cmd.h file exist.
//Input: The user inputs a UNIX command with parameters.
//       Note that not all UNIX commands are supported.
//Process: The program displays a pseudo shell prompt and waits for user input.
//         If the user enters an empty line, the program does nothing and
//         redisplays the prompt.  If the user enters a command, the program
//         parses the command and places the contents into a cmd_t struc
//         (defined in make_cmd.h).  The program then attempts to execute the
//         command.  It first checks if the user properly entered quit.  If so
//         the program terminates.  Else, it then checks if the user asked to
//         change directories.  If so, it checks if the command was valid.  If
//         the command is invalid, an error displays and the shell prompt is
//         displayed again.  Else, it attempts to change to the appropriate
//         directory.  If no extra parameter was given, the program goes to
//         the HOME directory.  If neither a quit nor cd was inputted, the
//         program forks a child process and then attempts to execute the
//         given command.  It first checks if the user desired a input or
//         output redirect to or from a file.  If so, it attempts to open said
//         file and appropriately redirects the standard input or output
//         according to what was requested.  It then attempts to execute the
//         command using a system call.  If there was an error with the command
//         the error message is displayed.  Lastly, the parent process will
//         wait for the child process to finish unless the user requested that
//         the process be run in the background.
//Example: pa1> ls
//         a.out hello.cpp shell.cpp make_cmd.cpp make_cmd.h
//         pa1> ls > test.txt
//         pa1> cat test.txt
//         a.out
//         hello.cpp
//         shell.cpp
//         make_cmd.cpp
//         make_cmd.h
//Output: The program displays the shell prompt.
//        The program displays the output of any process that is run.
//        The program may display error messages.

#include <iostream>
#include <string>
#include <syscall.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "make_cmd.h"

using namespace std;

//Create Constants
const int SIZE = 500;
const char *QUIT = "quit";
const char *CD = "cd";

int getCommand(char *command, cmd_t &cmd);
//Fills the cmd_t struc with the desired information by calling make_cmd
//and passing in command and cmd.
//IN: command, cmd
//OUT: err, cmd

void execute(int err, cmd_t cmd);
//Takes the cmd_t struc and checks what type of UNIX command is being called.
//For built in commands, it forks a child process to execute the command while
//the parent process waits or moves forward.  Else it executes specific
//instructions.
//IN: err, cmd

void changeDirectory(cmd_t cmd);
//Takes the cmd_t struc and checks if the cd command is in the correct format.
//If so, it makes a system call to chdir according to the given parameters.
//If there are no extra parameters, it directs the program to HOME.
//IN: cmd

int main()
{
  //Create Variables
  char *command = new char;
  cmd_t cmd;
  int err = 0;

  //User Interface
  while(true) {
	//Receive Command
	err = getCommand(command, cmd);
	execute(err, cmd);
  }
  delete command;
  return 0;
}

int getCommand(char *command, cmd_t &cmd) {
  int err = 0;
  while(err == 0) {
	//Create Shell
	cout << "pa1> ";
	cin.getline(command, SIZE);
	//Grab Command
	err = make_cmd(command, cmd);
  }
  return err;
}

void execute(int err, cmd_t cmd) {
  //Check if command is valid
  if(err == -1) 
	cerr << "Error executing command: invalid command" << endl;
  
  //Check if user correctly asks to quit
  else if(strcmp(*cmd.argv, QUIT) == 0 && err == 1)
	exit(-1);
  
  //Check if user asks to change directories
  else if(strcmp(cmd.argv[0], CD) == 0)
	changeDirectory(cmd);
  
  //If none of the above try to fork a child process
  else {
	pid_t pid;
	int infd;
	int outfd;
	pid = fork();

	//Check State of pid
	if(pid < 0) { //Error Forking
	  cerr << "Error creating fork: " << strerror(errno) << endl;
	  exit(-1);
	}else if(pid == 0) { //Child Process
	  //Check if user wants to redirect input/output
	  if(cmd.input_redirect) { //Redirect Input using Specified file
		//Open Input File
		cout << "Here" << endl;
		infd = open(cmd.input_redirect, O_RDONLY, S_IRUSR | S_IWUSR);
		if(infd == -1) {
		  cerr << "Error opening file: " << strerror(errno) << endl;
		}else {
		  //Link standard input
		  if(dup2(infd, STDIN_FILENO) == -1)
			cerr << "Error copying file decriptor: " << strerror(errno)
				 << endl;
		}
	  }
	  if(cmd.output_redirect) { //Output Redirect using Specified File
		//Open or Create Output File
		cout << "There" << endl;
		outfd = open(cmd.output_redirect, O_WRONLY | O_CREAT | O_TRUNC,
				  S_IWUSR | S_IRUSR);
		if(outfd == -1) {
		  cerr << "Error opening file: "  << strerror(errno) << endl;
		}else {
		  //Link standard output
		  if(dup2(outfd, STDOUT_FILENO) == -1)
			cerr << "Error copying file descriptor: " << strerror(errno)
				 << endl;
		}
	  }
	  
	  //Execute Command
	  if(execvp(*cmd.argv, cmd.argv) == -1) {
		cerr << "Error executing command: " << strerror(errno) << endl;
	  };
	  close(infd);
	  close(outfd);
	  exit(-1);
	  
	}else { //Parent Process
	  //Check if background process
	  if(!cmd.background) {
		//Wait for child process
		waitpid(pid, NULL, 0);
	  }
	}
  }
}

void changeDirectory(cmd_t cmd) {
  //Check if command is valid
  if(cmd.argv[2])
	cerr << "Error changing directories: More than one parameter." << endl;
  else if(cmd.argv[1]) { //File path given
	if(chdir(cmd.argv[1]) == -1)
	  cerr << "Error changing directories: " << strerror(errno) << endl;
  }else { //No parameters given
	if(chdir(getenv("HOME")) == -1)
	  cerr << "Error changing directories: " << strerror(errno) << endl;
  }
}
