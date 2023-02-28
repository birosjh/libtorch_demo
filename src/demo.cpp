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

    std::filesystem::path datapath = std::filesystem::current_path() / "data/train";

    std::unordered_map<std::string, int> classes = {
        {"cats", 0},
        {"dogs", 1}
    };

    String path_string = String(datapath.string());

    PetDataset dataset{path_string, classes};

    // Generate a data loader.
    auto data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
        std::move(dataset),
        batch_size
    );
}