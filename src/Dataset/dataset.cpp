#include "dataset.h"
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <torch/torch.h>
#include <torch/types.h>

using namespace cv;

PetDataset::PetDataset(const String& path, std::unordered_map<std::string, int> class_labels):
class_labels(class_labels)
{
    cv::String pattern = "*/*.jpg";
    glob(path, image_files);
}

torch::data::Example<> PetDataset::get(size_t index) {

    auto image_file = image_files[index];

    std::string delimiter = "/";
    std::string classname = image_file.substr(0, image_file.find(delimiter));

    int label = class_labels[classname];

    at::Tensor tensor_label = torch::full({1}, label);

    Mat image;
    image = imread(image_file, 1);

    at::Tensor tensor_image = torch::from_blob(image.data, { image.rows, image.cols, 3 }, at::kByte);
    
    return {tensor_image, tensor_label};
} 

torch::optional<size_t> PetDataset::size() const {

    return image_files.size();
}