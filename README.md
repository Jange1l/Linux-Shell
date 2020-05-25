# Linux-Shell


To run the shell:

1. Within the folder directory in the terminal type the "make" command
  * This will compile all the files needed for the shell to work
  
 2. Type "ls" and make sure that an exec file called "shell" is in the directory
 
 3. Run the shell by typing "./shell"
 
 4. Now you are in the Shell program 
 
 5. Check the list of commands to try below
 
 6. When you want to exit the program simply hold ctrl + c
 
 ## Try The Following Commands
 
**Basics**

- / (Forward Slash)    Top level directory
- . (Single Period)    Current directory
- .. (Double Period)    Parent directory
- ~ (Tilde)    Home directory
- sudo [command]    Run command with the security privileges of the super user
- nano [file]    Opens the Terminal editor
- open [file]    Opens a file
- [command] -h    Get help about a command
- man [command]    Show the help manual of the command
- Change Directory
- cd    Home directory
- cd [folder]    Change directory, e.g. cd Documents
- cd ~    Home directory
- cd/    Root of the drive
- cd -    Previous directory or folder you last browsed
- pwd    Show your working directory
- cd..    Move up to the parent directory
- cd../..    Move up two levels

**List Directory Contents**
- ls    Display the name of files and subdirectories in the directory
- ls -C    Force multi-column output of the listing
- ls -a    List all entries including those with .(period) and ..(double period)
- ls -1    Output the list of files in one entry per line format
- ls -F    Display a / (slash) immediately after each path that is a directory, * (asterisk) after executable programs or scripts, and @ after a
symbolic link
- ls -S    Sort files or entries by size
- ls -l    List in a long format. Includes file mode, owner and group name, date and time file was modified, pathname, and more
- ls -lt    List the files sorted by time modified (most recent first)
- ls -lh    Long listing with human readable file sizes in KB, MB, or GB
- ls -lo    List the file names with size, owner, and flags
- ls -la    List detailed directory contents, including hidden files


**File Size and Disk Space**
- du    List usage for each subdirectory and its contents
- du -sh [folder]    Human readable output of all files in a directory
- du -s    Display an entry for each specified file
- du -sk* | sort -nr    List files and folders, totaling the size including the subfolders. Replace sk* with sm* to list directories in MB
- df -h    Calculate your system's free disk space
- df -H    Calculate free disk space in powers of 1,000 (as opposed to 1,024)


**File and Directory Management**
- mkdir <dir>    Create new folder named <dir>
- mkdir -p <dir>/<dir>    Create nested folders
- mkdir <dir1> <dir2> <dir3>    Create several folders at once
- mkdir "<dir>"    Create a folder with a space in the filename
- rmdir <dir>    Delete a folder (only works on empty folders)
- rm -R <dir>    Delete a folder and its contents
- touch <file>    Create a new file without any extension
- cp <file> <dir>    Copy a file to the folder
- cp <file> <newfile>    Copy a file to the current folder
- cp <file>~/<dir>/<newfile>    Copy a file to the folder and rename the copied file
- cp -R <dir> <"new dir">    Copy a folder to a new folder with spaces in the filename
- cp -i <file><dir>    Prompts you before copying a file with a warning overwrite message
- cp <file1> <file2> <file3>/Users/<dir>    Copy multiple files to a folder
- rm <file>    Delete a file (This deletes the file permanently; use with caution.)
- rm -i <file>    Delete a file only when you give confirmation
- rm -f <file>    Force removal without confirmation
- rm <file1> <file2> <file3>    Delete multiple files without any confirmation
- mv <file> <newfilename>    Move/rename
- mv <file> <dir>    Move a file to the folder, possibly by overwriting an existing file
- mv -i <file> <dir>    Optional -i flag to warn you before overwriting the file
- mv *.png ~/<dir>    Move all PNG files from current folder to a different folder


**Permissions**
- ls -ld    Display the default permission for a home directory
- ls -ld/<dir>    Display the read, write, and access permission of a particular folder
- chmod 755 <file>    Change the permission of a file to 755
- chmod -R 600 <dir>    Change the permission of a folder (and its contents) to 600
- chown <user>:<group> <file>    Change the ownership of a file to user and group. Add -R to include folder contents

**Processes**
- ps -ax    Output currently running processes. Here, a shows processes from all users and x shows processes that are not connected with the Terminal
- ps -aux    Shows all the processes with %cpu, %mem, page in, PID, and command
- top    Display live information about currently running processes
- top -ocpu -s 5    Display processes sorted by CPU usage, updating every 5 seconds
- top -o rsize    Sort top by memory usage
- kill PID    Quit process with ID <PID>. You'll see PID as a column in the Activity Monitor
 
