
                if (pipeFound == 1) {

					printf("here!. \n");
                    int pipefd_1[2];
                    if (pipe(pipefd_1) == -1) {
                        perror("pipe error. \n");
                        exit(1);
                    }

                    int status;
                    pid_t pid_1, pid_2;

                    pid_1 = fork();
                    if (pid_1 == 0) {
                        char cmdbuf[BSIZE];
                        bzero(cmdbuf, BSIZE);
                        printf("%s", commands[0]);
                        sprintf(cmdbuf, "%s", commands[0]);
                        dup2(pipefd_1[1], STDOUT_FILENO);

                        close(pipefd_1[0]);
                        close(pipefd_1[1]);

                        if (execvpe(cmdbuf, commands, environ) < 0) {
                            fprintf(stderr, "\nError execing find. ERROR#%d\n", errno);
                            return EXIT_FAILURE;
                        }
                    }

                    pid_2 = fork();
                    if (pid_2 == 0) {
                        char cmdbuf[BSIZE];
                        bzero(cmdbuf, BSIZE);
                        dup2(pipefd_1[0], STDIN_FILENO);
                        sprintf(cmdbuf, "%s", commands[2]);

                        close(pipefd_1[0]);
                        close(pipefd_1[1]);

                        if (execvpe(cmdbuf, commands, environ) < 0) {
                            fprintf(stderr, "\nError execing sort. ERROR#%d\n", errno);
                            return EXIT_FAILURE;
                        }
                    }

                    close(pipefd_1[0]);
                    close(pipefd_1[1]);

					wait(NULL);
                   /* if ((waitpid(pid_1, & status, 0)) == -1) {
                        fprintf(stderr, "Process 1 encountered an error. ERROR%d\n", errno);
                        return EXIT_FAILURE;
                    }
                    if ((waitpid(pid_2, & status, 0)) == -1) {
                        fprintf(stderr, "Process 2 encountered an error. ERROR%d\n", errno);
                        return EXIT_FAILURE;
                    }*/

                } else {
                
                
                
                
                
                 }