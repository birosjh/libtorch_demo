#include "dataset.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/filesystem.hpp>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <torch/torch.h>
#include <torch/types.h>

using namespace cv;

PetDataset::PetDataset(const String& path, std::unordered_map<std::string, int> class_labels):
class_labels(class_labels)
{
    String pattern = "*.jpg";
    utils::fs::glob(path, pattern, image_files);
}

Mat PetDataset::transform(Mat image) {

    if(dis(gen) < 0.3)
        cv::flip(image, image, 1);

    if(dis(gen) < 0.3)
        cv::Size blur_kernel(5,5);
        cv::blur(image, image, blur_kernel);

    if(dis(gen) < 0.3)
        cv::Size dilate_kernel(5,5);
        cv::dilate(image, image, dilate_kernel);

    return image;
}

torch::data::Example<> PetDataset::get(size_t index) {

    auto image_file = image_files[index];

    std::string delimiter = "/";
    std::string filename = image_file.substr(image_file.find_last_of(delimiter) + 1);

    delimiter = "_";
    std::string classname = filename.substr(0, filename.find(delimiter));

    int label = class_labels[classname];

    at::Tensor tensor_label = torch::full({1}, label);

    float image_size = 300.0;

    Mat image;
    image = imread(image_file, 1);

    resize(image, image, cv::Size(), image_size / image.cols, image_size / image.rows);

    image = transform(image);

    at::Tensor tensor_image = torch::from_blob(image.data, { image.rows, image.cols, 3 }, at::kByte);

    return {tensor_image, tensor_label};
} 

torch::optional<size_t> PetDataset::size() const {

    return image_files.size();
}