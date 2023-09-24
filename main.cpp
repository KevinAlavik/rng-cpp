#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <sys/stat.h>

using namespace std;

void generateRandomJPEG(int width, int height, const string& directory) {
    vector<uint8_t> pixels(width * height * 3);

    for (size_t i = 0; i < pixels.size(); ++i) {
        pixels[i] = rand() % 256;
    }

    string image_name;
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const int name_length = 10;

    for (int i = 0; i < name_length; ++i) {
        image_name += characters[rand() % characters.length()];
    }

    string file_path = directory + "/" + image_name + ".jpg";
    FILE* image_file = fopen(file_path.c_str(), "wb");
    if (image_file) {
        uint8_t jpeg_header[] = { 0xFF, 0xD8 };
        fwrite(jpeg_header, sizeof(jpeg_header), 1, image_file);
        fwrite(pixels.data(), pixels.size(), 1, image_file);
        uint8_t jpeg_footer[] = { 0xFF, 0xD9 };
        fwrite(jpeg_footer, sizeof(jpeg_footer), 1, image_file);
        fclose(image_file);
    }
}

int main() {
    int numIterations = 60;
    int imageWidth = 64;
    int imageHeight = 64;

    string directory = "images";
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    for (int i = 0; i < numIterations; ++i) {
        generateRandomJPEG(imageWidth, imageHeight, directory);
    }

    cout << "Successfully generated random JPEG images." << endl;

    return 0;
}
