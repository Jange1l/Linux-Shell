//
//  m2_shell.c
//  
//
//  Created by Juan escobar on 12/13/19.
//

#include "m2_shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int one_command_exec(char **args, int background, char *rd_in, char *rd_out, int redirect_in,int redirect_out, int pipe_f, int num_commands ,int i ,int num, int status, pid_t child_pid, int stat)
{
    //printf("one command\n");
    child_pid = fork();
    
    char **c_args = malloc(sizeof(char) * num);
    for(i = 0; i < num; i++)
    {
        if(strcmp(args[i], "&") != 0)
        {
            c_args[i] = args[i];
        } else {
            if (child_pid != 0)
            {
                printf("[%d]\n", child_pid);
            }
        }
    }
    
    if(child_pid == 0)
    {
        if(execvp(c_args[0], c_args) < 0)
        {
            printf("%s: Command not found\n", c_args[0]);
        }
        exit(EXIT_FAILURE);
    } else if (child_pid < 0) {
        perror("exec");
    }
    else {
        if( background != 1)
        {
            do{
                waitpid(child_pid, &status, 0);
            }while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        free(c_args);
        return child_pid; // Left of here
    }
    free(c_args);
    return 0;
}

int redirect_in_exec(char **args, int background, char *rd_in, char *rd_out, int redirect_in,int redirect_out, int pipe_f, int num_commands ,int i ,int num, int status, pid_t child_pid, int stat)
{
    //Spawn child
    int ret_in = fork();
    char **cmd_one = malloc(sizeof(char) * num);
    char **cmd_two = malloc(sizeof(char) * num);
    int swtch = 0;
    int gap = 1;
    for (i = 0; i < num; i++)
    {
        if((strcmp(args[i], "<") != 0) && (strcmp(args[i], ">") != 0) )
        {
            if(strcmp(args[i], "&") == 0)
            {
                
                if(redirect_in == 1)
                {
                    printf("[%d]\n", ret_in);
                }
                continue;
            }
            if (swtch !=1)
            {
                gap += 1;
                cmd_one[i] = args[i];
                //printf("cmd_one -> %s %d\n", cmd_one[i], i);
            }
            else
            {
                cmd_two[i - gap] = args[i];
                //printf("cmd_two -> %s %d\n", cmd_two[i - gap], i - gap);
            }
        }else{ swtch = 1;}
    }
    
    
    if(ret_in < 0)
    {
        perror("fork");
        
    }
    else if ( ret_in == 0)
    {
        int sub_p = fork();
        if( sub_p == 0)
        {
            close(0);
            
            ///Redirect out put to file "lsit.txt"
            char *cmdtwo = cmd_two[0];
            
            int fd = open(cmdtwo, O_RDONLY);
            
            //printf(" rd in -> file descriptor = %d\n", fd);
            
            if(fd < 0)
            {
                printf("%s: File not found\n", cmdtwo);
                exit(EXIT_FAILURE);
            }
            else {
                //Child launches command "wc"
                char *argv[3];
                argv[0] = cmd_one[0];
                argv[1] = NULL;
                //printf("Child process %s \n", argv[0]);
                execvp(argv[0], argv);
            }
        }else{
            
        }
        exit(EXIT_FAILURE);
    }else{
        if( background != 1)
        {
            do{
                waitpid(ret_in, &status, 0);
            }while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        free(cmd_one);
        free(cmd_two);
        return ret_in;
    }
    
    free(cmd_one);
    free(cmd_two);
    return 0;
}

int redirect_exec(char **args, int background, char *rd_in, char *rd_out, int redirect_in,int redirect_out, int pipe_f, int num_commands ,int i ,int num, int status, pid_t child_pid, int stat)
{
    //printf("redirect\n");
    //Spawn child
    int ret_out = fork();
    
    //int ret = fork();
    
    char **cmd_one = malloc(sizeof(char) * num);
    char **cmd_two = malloc(sizeof(char) * num);
    int swtch = 0;
    int gap = 1;
    for (i = 0; i < num; i++)
    {
        if((strcmp(args[i], "<") != 0) && (strcmp(args[i], ">") != 0) && ( strcmp(args[i], "&") != 0))
        {
            if(strcmp(args[i], "&") == 0)
            {
                if (redirect_out == 1)
                {
                    printf("[%d]\n", ret_out);
                    continue;
                }
                if(redirect_in == 1)
                {
                    //printf("[%d]\n", ret);
                }
            }
            if (swtch !=1)
            {
                gap += 1;
                cmd_one[i] = args[i];
                //printf("cmd_one -> %s %d\n", cmd_one[i], i);
            }
            else
            {
                cmd_two[i - gap] = args[i];
                //printf("cmd_two -> %s %d\n", cmd_two[i - gap], i - gap);
            }
        }else{ swtch = 1;}
    }
    
    if(redirect_out == 1) // ls -l > list.txt
    {
        //printf("in redirect out section\n");
        
        if(ret_out < 0)
        {
            
        }
        else if (ret_out == 0)
        {
            if(open(cmd_two[0], O_WRONLY | O_CREAT, 0660) < 0)
            {
                printf("%s: Cannot create file\n", cmd_two[0]);
                exit(EXIT_FAILURE);
            }
            int sub_p = fork();
            if( sub_p == 0)
            {
                close(1);
                
                ///Redirect out
                char *cmdtwo = cmd_two[0];
                
                int fd = open(cmdtwo, O_WRONLY | O_CREAT, 0660);
                
                
                char *argv[3];
                argv[0] = cmd_one[0];
                argv[1] = cmd_one[1];
                argv[2] = NULL;
                
                execvp(argv[0], argv);
                
            }else{
                
            }
            exit(EXIT_FAILURE);
        }else{
            if( background != 1)
            {
                do{
                    waitpid(ret_out, &status, WNOHANG);
                }while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
            free(cmd_one);
            free(cmd_two);
            return ret_out;
        }
    }
    
    free(cmd_one);
    free(cmd_two);
    return 0;
}


int pipe_exec(char **args, int background, char *rd_in, char *rd_out, int redirect_in,int redirect_out, int pipe_f, int num_commands ,int i ,int num, int status, pid_t child_pid, int stat)
{
    
    //Spawn child
    int ret = fork();
    
    char **cmd_one = malloc(sizeof(char) * num);
    char **cmd_two = malloc(sizeof(char) * num);
    int swtch = 0;
    int gap = 1;
    for (i = 0; i < num; i++)
    {
        if(strcmp(args[i], "&") == 0)
        {
            if (ret != 0)
            {
                printf("[%d]\n", ret);
            }
        }
        if((strcmp(args[i], "|") != 0) && ( strcmp(args[i], "&") != 0))
        {
            if (swtch !=1)
            {
                gap += 1;
                cmd_one[i] = args[i];
                //printf("cmd_one -> %s %d\n", cmd_one[i], i);
            }
            else
            {
                cmd_two[i - gap] = args[i];
                //printf("cmd_two -> %s %d\n", cmd_two[i - gap], i - gap);
            }
        }else{ swtch = 1;}
    }
    
    if(ret < 0)
    {perror("fork");}
    else if ( ret == 0)
    {
        int stat_p;
        pid_t g_pid;
        //Create pipe
        int fds[2];
        pipe(fds);
        //Grand Child
        int sub_p = fork();
        if( sub_p == 0)
        {
            //Close write end of pipe
            close(fds[1]);
            
            //Duplicate read end of pipe in standad input
            close(0);
            dup(fds[0]);
            
            //Child launches command "wc"
            char *argv[2];
            argv[0] = cmd_two[0];
            argv[1] = NULL;
            execvp(argv[0], argv);
            
        }else{
            
            close(fds[0]);
            
            //Duplicate write end of pipe in standard output
            close(1);
            dup(fds[1]);
            
            //parent launches command "ls -l"
            char *argv_p[3];
            argv_p[0] = cmd_one[0];
            argv_p[1] = cmd_one[1];
            argv_p[2] = NULL;
            
            execvp(argv_p[0], argv_p);
        }
        //exit(EXIT_FAILURE);
    }else{
        if( background != 1)
        {
            do{
                waitpid(ret, &status, 0);
            }while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        free(cmd_one);
        free(cmd_two);
        return ret;
    }
    free(cmd_one);
    free(cmd_two);
    return 0;
}

char *read_line(void)
{
    
    int buffer_size = 1024;
    int i = 0;
    char *buffer = malloc(sizeof(char) * buffer_size);
    int c;
    
    if (!buffer)
    {
        
    }
    
    while(1)
    {
        c = getchar();
        
        if(c == EOF || c == '\n')
        {
            buffer[i] = '\0';
            return buffer;
        } else {
            buffer[i] = c;
        }
        i ++;
        
        if( i >= buffer_size)
        {
            buffer_size += 1024;
            buffer = realloc(buffer, buffer_size);
        }
        
    }
}

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"

char **tokenize_line(char *line)
{
    int bufsize = BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    
    if (!tokens) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(line,DELIM);
    while (token != NULL)
    {
        //printf(" %s \n", token);
        tokens[position] = token;
        position++;
        
        if (position >= bufsize) {
            // printf("realloc called\n");
            bufsize += BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        token = strtok(NULL, DELIM);
    }
    //printf("%d position\n", position);
    tokens[position] = NULL;
    return tokens;
    
}
void check_bg(pid_t *bg_p)
{
    int i;
    
    for( i = 0; i < 7 ; i++)
    {
        //printf("%d bg_p[i] %d\n", bg_p[i], i);
        pid_t return_pid = waitpid(bg_p[i], NULL, WNOHANG);
        if(return_pid == -1)
        {
            //perror("error");
        } else if(return_pid != 0)
        {
            
            printf("[%ld] finished\n", (long)bg_p[i]);
            bg_p[i] = 0;
        }
    }
    
}


int execute(char **args)
{
    
    int background = 0;
    char *rd_in;
    char *rd_out;
    int redirect_in = 0;
    int redirect_out = 0;
    int pipe_f = 0;
    int num_commands = 1;
    
    int i = 0;
    int num = -1;
    
    int status;
    pid_t child_pid;
    
    int stat;
    
    
    while(args[++num] != NULL) { }
    
    if (num == 0)
    {
        return 1;
    }
    for(i = 0; i < num; i++)
    {
        if (strcmp(args[i], "&") == 0)
        {
            //printf("background triggered\n");
            background = 1;
            
        }
        if (strcmp(args[i], ">") == 0)
        {
            rd_out = args[i +1];
            redirect_out = 1;
            num_commands +=1;
        }
        if (strcmp(args[i], "<") == 0)
        {
            rd_in = args[i -1];
            redirect_in = 1;
            num_commands +=1;
        }
        if (strcmp(args[i], "|") == 0)
        {
            //printf("pipe found\n");
            pipe_f = 1;
            num_commands += 1;
        }
        if (strcmp(args[i], "cd") == 0)
        {
            if(chdir(args[i + 1])!= 0)
            {
                perror("cd");
            }
            return 1;
        }
        
    }
    
    //*************************** ONE COMMAND *****************************
    if (num_commands == 1)
    {
        
        child_pid = one_command_exec(args, background, rd_in, rd_out, redirect_in, redirect_out, pipe_f, num_commands, i, num, status, child_pid, stat);
        return child_pid;
        
    }
    
    //*************************** PIPE  *****************************
    
    if(pipe_f == 1)
    {
        
        child_pid = pipe_exec(args, background, rd_in, rd_out, redirect_in, redirect_out, pipe_f, num_commands, i, num, status, child_pid, stat);
        return child_pid;
    }
    
    // **************************** REDIRECT *****************************
    if (redirect_out == 1)
    {
        
        child_pid = redirect_exec(args, background, rd_in, rd_out, redirect_in, redirect_out, pipe_f, num_commands, i, num, status, child_pid, stat);
        
        return child_pid;
    }
    if(redirect_in == 1)
    {
        child_pid = redirect_in_exec(args, background, rd_in, rd_out, redirect_in, redirect_out, pipe_f, num_commands, i, num, status, child_pid, stat);
        
        return child_pid;
    }
    
    return 0;
}





void launch_shell()
{
    char *line;
    char **args;
    pid_t status;
    pid_t bg_p[7];
    int count = 0;
    
    do{
        if(count > 7)
        {
            count = 0;
        }
        
        printf("$ ");
        
        line = read_line();
        args = tokenize_line(line);
        check_bg(bg_p);
        status = execute(args);
        
        if(status != 0)
        {
            bg_p[count] = status;
        }
        
        free(line);
        free(args);
        count +=1;
    } while (1);
}

int main(int argc, char **argv)
{
    launch_shell();
    return 1;
}
