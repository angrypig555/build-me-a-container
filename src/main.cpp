#include <iostream>
#include <fstream>

// all the strings for the input
char yesno;
std::string image_name;
std::string work_dir;
int work_dir_use;

int main() {
    std::cout << "build-me-a-container 0.1, dockerfile generator" << std::endl;
    std::cout << "welcome user, this is an interactive prompt to generate and build a dockerfile" << std::endl;
    std::cout << "first off, lets start off with the very basics, what image will be the base of this container?" << std::endl;
    std::cout << "e.g alpine" << std::endl;
image_name_input:
    std::cout << "image name:";
    std::cin >> image_name;
    std::cout << "are you sure [y/n]? image name:" << image_name << std::endl;
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            break;
        default:
            goto image_name_input;
            break;
    }
    std::cout << "would you like to set a working directory where the commands will be executed inside the image?[y/n] ";
    std::cin >> yesno;
    switch(yesno) {
        case 'y':
            work_dir_use = 1;
            std::cout << "please specify working directory:" << std::endl;
            std::cin >> work_dir;
            std::cout << "set " << work_dir << " as working directory" << std::endl;
            break;
        default:
            work_dir_use = 0;
            std::cout << "no working directory will be used" << std::endl;
            break;
    }
    std::cout << "creating dockerfile next to executable" << std::endl;

    // create a dockerfile
    std::ofstream dockerfile("Dockerfile");
    dockerfile << "FROM " << image_name << "\n";
    switch(work_dir_use) {
        case 0:
            break;
        case 1:
            dockerfile << "WORKDIR " << work_dir << "\n";
    }
    dockerfile.close();
    return 0;
}