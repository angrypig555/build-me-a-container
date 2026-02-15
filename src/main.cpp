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

std::vector<std::string> dockerfile_buffer;

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
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            copy:
            std::cout << "please specify path on host: ";
            std::cin >> copy_host_path;
            std::cout << "please specify path on container: ";
            std::cin >> copy_container_path;
            std::cout << copy_host_path << " will be copied to " << copy_container_path << std::endl;
            dockerfile_buffer.push_back("COPY " + copy_host_path + " " + copy_container_path);
            break;
        default:
            break;
    }
    std::cout << "would you like to copy more files? [y/n] ";
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            goto copy;
            break;
        default:
            break;
    }
    seperator();
    
    // generates dockerfile
    std::ofstream dockerfile("Dockerfile");
    dockerfile << "# Generated using build-me-a-container\n";
    for (int i = 0; i < dockerfile_buffer.size(); i++) {
        dockerfile << dockerfile_buffer[i] << "\n";
    }
    dockerfile.close();

    // Old logic, do not use
    // dockerfile << "FROM " << image_name << "\n";
    /*switch(work_dir_use) {
        case 0:
            break;
        case 1:
            dockerfile << "WORKDIR " << work_dir << "\n";
    }
    dockerfile.close();
    */
    std::cout << "build dockerfile? (make sure you are in an empty folder)[y/n]: ";
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            system("sudo docker build .");
            break;
        default:
            break;
    }
    return 0;
}