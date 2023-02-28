#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include "Dataset/dataset.h"

using namespace cv;

int main()
{
    std::filesystem::path datapath = std::filesystem::current_path() / "data/train";

    std::unordered_map<std::string, int> classes = {
        {"cats", 0},
        {"dogs", 1}
    };

    String path_string = String(datapath.string());

    PetDataset dataset{path_string, classes};

    auto sample = dataset.get(1);

    std::cout << sample.data << std::endl;

    std::cout << sample.target << std::endl;
}