#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <unordered_map>
#include <filesystem>
#include "Dataset/dataset.h"

using namespace cv;

int main()
{
    int batch_size = 16;
    bool visualize = true;

    std::filesystem::path datapath = std::filesystem::current_path() / "data/images";

    std::unordered_map<std::string, int> classes = {
        {"Abyssinian", 0},
        {"american_bulldog", 1},
        {"american_pit_bull_terrier", 2},
        {"basset_hound", 3},
        {"beagle", 4},
        {"Bengal", 5},
        {"Birman", 6},
        {"Bombay", 7},
        {"boxer", 8},
        {"British_Shorthair", 9},
        {"chihuahua", 10},
        {"Egyptian_Mau", 11},
        {"english_cocker_spaniel", 12},
        {"english_setter", 13},
        {"german_shorthaired", 14},
        {"great_pyrenees", 15},
        {"havanese", 16},
        {"japanese_chin", 17},
        {"keeshond", 18},
        {"leonberger", 19},
        {"Maine_Coon", 20},
        {"miniature_pinscher", 21},
        {"newfoundland", 22},
        {"Persian", 23},
        {"pomeranian", 24},
        {"pug", 25},
        {"Ragdoll", 26},
        {"Russian_Blue", 27},
        {"saint_bernard", 28},
        {"samoyed", 29},
        {"scottish_terrier", 30},
        {"shiba_inu", 31},
        {"Siamese", 32},
        {"Sphynx", 33},
        {"staffordshire_bull_terrier", 34},
        {"wheaten_terrier", 36},
        {"yorkshire_terrier", 36},
    };

    String path_string = String(datapath.string());

    auto dataset = PetDataset(path_string, classes).map(torch::data::transforms::Stack<>());

    // Generate a data loader.
    auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
        std::move(dataset),
        batch_size
    );

    if (visualize) {
        auto& batch = *data_loader

        auto data = batch.data;
        auto labels = batch.target;

        std::cout << "hi" << std::endl;

        return 0
    }

    for (auto& batch : *data_loader) {
        auto data = batch.data;
        auto labels = batch.target;

        std::cout << data << std::endl;

    }

    return 0;
}