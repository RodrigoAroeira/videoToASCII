#pragma once
#include "resolution.hpp"

#include <opencv2/videoio.hpp>
#include <string>

char pixelToChar(int pixelBrightness);

Resolution getTerminalRes();

Resolution getVideoRes(const cv::VideoCapture &cap);

bool isValidYTUrl(const std::string &txt) noexcept;

bool fileExists(const std::string &filename);

void tempRename(const std::string &filename, const std::string &dest);

void downloadVideo(const std::string &ytURL, const std::string &outputName);

void pixelToColoredChar(const cv::Vec3b &pixel, char *str_out);

std::string getStreamURL(const std::string &ytURL);
