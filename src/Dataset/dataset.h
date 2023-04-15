#ifndef DATASET_H
#define DATASET_H


#include <torch/torch.h>
#include <torch/types.h>
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <random>


class PetDataset : public torch::data::Dataset<PetDataset>
{
    private:
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0, 1);

        std::vector<cv::String> image_files;

        bool vizualize;

    public:
        std::unordered_map<std::string, int> class_labels;

        explicit PetDataset(const cv::String& path, std::unordered_map<std::string, int> class_labels);

        torch::data::Example<> get(size_t index) override;

        torch::optional<size_t> size() const override;

        cv::Mat transform(cv::Mat image);
};

#endif // DATASET_H