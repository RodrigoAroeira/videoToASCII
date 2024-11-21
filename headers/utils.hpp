#pragma once
#include "resolution.hpp"

#include <opencv2/videoio.hpp>
#include <string>

std::string pixelToChar(int pixelBrightness);

Resolution getTerminalRes();

Resolution getVideoRes(const cv::VideoCapture &cap);

bool isValidYTUrl(const std::string &txt) noexcept;

bool fileExists(const std::string &filename);

void tempRename(const std::string &filename, const std::string &dest);

void downloadVideo(const std::string &ytURL, const std::string &outputName);

std::string pixelToColoredChar(cv::Vec3b &pixel);

std::string getStreamURL(const std::string &ytURL);
