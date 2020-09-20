#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <vector>
using namespace std;
pid_t child_pid;
vector<pid_t>pidcol;
static void abc(int sigum){
    exit(0);
}



int main(int argc, char **argv) {

    int pip1[2];
    pipe(pip1);
    int pip2[2];
    pipe(pip2);
    signal(SIGCHLD,abc);
    child_pid = fork();
    if (child_pid == 0) {
        dup2(pip1[1], STDOUT_FILENO);
        close(pip1[0]);
        close(pip1[1]);
        execv("./rgen", argv);}

    else if (child_pid < 0) {
        std::cerr << "Error: could not fork\n";
        return 0;
    }
    pidcol.push_back(child_pid);
    signal(SIGCHLD,abc);
    child_pid = fork();
    if (child_pid == 0) {
        dup2(pip1[0], STDIN_FILENO);
        close(pip1[0]);
        close(pip1[1]);
        dup2(pip2[1], STDOUT_FILENO);
        close(pip1[0]);
        close(pip1[1]);
        char *arge_list1[3];
        arge_list1[0] = (char *) "/usr/bin/python3";
        arge_list1[1] = (char *) "a1ece650.py";
        arge_list1[2] = NULL;
        execv("/usr/bin/python3", arge_list1);}
    else if (child_pid < 0) {
        std::cerr << "Error: no fork\n";
        return 0;
    }
    pidcol.push_back(child_pid);
    signal(SIGCHLD,abc);
    child_pid= fork();
    if(child_pid==0){
        dup2(pip2[0], STDIN_FILENO);
        close(pip2[0]);
        close(pip2[1]);
        char *arge_list2[2];
        arge_list2[0] = (char *) "./a2ece650";
        arge_list2[1] = NULL;
        execv("./a2ece650", arge_list2);
    }
    else if (child_pid < 0) {
        std::cerr << "Error: no fork\n";
        return 0;
    }
    pidcol.push_back(child_pid);
    child_pid = 0;
    dup2(pip2[1], STDOUT_FILENO);
    close(pip2[0]);
    close(pip2[1]);

    while (!std::cin.eof()) {
        string user;
        getline(std::cin, user);
        if (user.size() > 0) {
            std::cout << user << std::endl;
        }

    }
    int mama;
    kill(pidcol[0], SIGKILL);
    kill(pidcol[1], SIGKILL);
    kill(pidcol[2], SIGKILL);

    waitpid(pidcol[0], &mama, 0);
    waitpid(pidcol[1], &mama, 0);
    waitpid(pidcol[2], &mama, 0);
    return 0;
}
