#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

// all the strings for the input
char yesno;
std::string image_name;
std::string work_dir;
int work_dir_use;
std::string copy_host_path;
std::string copy_container_path;
int copy_in_use;
int port;
std::vector<std::string> dockerfile_buffer;
std::string tag;
std::string run_command;
std::string entry_point;

int get_term_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void seperator() {
    int counter = get_term_width();
    while (counter != 0) {
        std::cout << "-";
        counter -= 1;
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "build-me-a-container 0.1, dockerfile generator" << std::endl;
    std::cout << "WARNING! Before running this program, make sure you are in a seperate, empty directory because the dockerfile will be generated next to where it is running" << std::endl;
    std::cout << "welcome user, this is an interactive prompt to generate and build a dockerfile" << std::endl;
    seperator();
    std::cout << "first off, lets start off with the very basics, what image will be the base of this container?" << std::endl;
    std::cout << "e.g alpine" << std::endl;
image_name_input:
    std::cout << "image name: ";
    std::cin >> image_name;
    std::cout << "are you sure [y/n]? image name: " << image_name << std::endl;
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            dockerfile_buffer.push_back("FROM " + image_name);
            break;
        default:
            goto image_name_input;
            break;
    }
    

    seperator();
    std::cout << "would you like to set a working directory where the commands will be executed inside the image?[y/n] ";
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            work_dir_use = 1;
            std::cout << "please specify working directory: ";
            std::cin >> work_dir;
            std::cout << "set " << work_dir << " as working directory" << std::endl;
            dockerfile_buffer.push_back("WORKDIR " + work_dir);
            break;
        default:
            work_dir_use = 0;
            std::cout << "no working directory will be used" << std::endl;
            break;
    }
    
    seperator();
    std::cout << "would you like to copy anything? [y/n] ";
copy:
    std::cin >> yesno;
    if (yesno == 'y') {
            std::cout << "please specify path on host: ";
            std::cin >> copy_host_path;
            std::cout << "please specify path on container: ";
            std::cin >> copy_container_path;
            std::cout << copy_host_path << " will be copied to " << copy_container_path << std::endl;
            dockerfile_buffer.push_back("COPY " + copy_host_path + " " + copy_container_path);
            std::cout << "would you like to copy more files? [y/n] ";
            goto copy;
    }
    
    seperator();
    std::cout << "would you like to expose any ports? [y/n] ";
ports:
    std::cin >> yesno;
    if (yesno == 'y') {
        std::cout << "please specify port to expose: ";
        std::cin >> port;
        dockerfile_buffer.push_back("EXPOSE " + std::to_string(port));
        std::cout << "port " << port << " will be exposed" << std::endl;
        std::cout << "would you like to expose any more ports? [y/n] ";
        goto ports;
    }
    seperator();
    std::cout << "would you like to run a command in the container once when its built? e.g adding custom users [y/n] ";
run_question:
    std::cin >> yesno;
    if (yesno == 'y') {
        std::cin.ignore(1000, '\n');
        std::cout << "please enter command to run while the container is built: ";
        std::getline(std::cin, run_command);
        std::cout << run_command << " will be run once while the container is being built" << std::endl;
        dockerfile_buffer.push_back("RUN " + run_command);
        std::cout << "would you like to run other commands? [y/n] ";
        goto run_question;
    }
    seperator();
    std::cout << "would you like to set an entrypoint?(command that will be run every time the image starts) [y/n]";
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            std::cout << "please enter command: ";
            std::cin.ignore();
            std::getline(std::cin, entry_point);
            std::cout << entry_point << " will be executed every time the image runs" << std::endl;
            dockerfile_buffer.push_back("ENTRYPOINT " + entry_point);
            break;
        default:
            break;
    }
    // generates dockerfile
    seperator();
    std::cout << "generating dockerfile" << std::endl;
    std::ofstream dockerfile("Dockerfile");
    dockerfile << "# Generated using build-me-a-container\n";
    for (int i = 0; i < dockerfile_buffer.size(); i++) {
        dockerfile << dockerfile_buffer[i] << "\n";
    }
    dockerfile.close();
    seperator();
    std::cout << "checking for containerisation software..." << std::endl;
    int is_docker = std::system("docker > /dev/null 2>&1");
    int is_podman = std::system("podman > /dev/null 2>&1");
    std::string container_system;
    if (is_docker == 0) {
        container_system = "docker";
        std::cout << "please enter container system, docker autodetected: ";
        std::cin >> container_system;
    } else if (is_podman == 0) {
        container_system = "podman";
        std::cout << "please enter a container system, podman autodetected: ";
        std::cin >> container_system;
    } else {
        std::cout << "no docker or podman detected, dockerfile generated but build is impossible" << std::endl;
        return 1;
    }
    seperator();
    std::cout << "build dockerfile? (make sure you are in an empty folder)[y/n]: ";
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            std::cout << "please enter a tag(name) for the image: ";
            std::cin >> tag;
            if (container_system == "docker") {
                std::string docker_command = "sudo docker build -t " + tag + " .";
                system(docker_command.c_str());
            } else if (container_system == "podman") {
                std::string podman_command = "podman build -t " + tag;
                system(podman_command.c_str());
            }
            break;
        default:
            break;
    }
    return 0;
}