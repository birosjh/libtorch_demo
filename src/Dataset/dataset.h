#ifndef DATASET_H
#define DATASET_H


#include <torch/torch.h>
#include <torch/types.h>
#include <opencv2/opencv.hpp>
#include <unordered_map>


class PetDataset : public torch::data::Dataset<PetDataset>
{
    private:
        std::vector<cv::String> image_files;

    public:
        std::unordered_map<std::string, int> class_labels;

        explicit PetDataset(const cv::String& path, std::unordered_map<std::string, int> class_labels);

        torch::data::Example<> get(size_t index) override;

        torch::optional<size_t> size() const override;
};

#endif // DATASET_H