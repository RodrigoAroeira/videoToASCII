# TODAY'S TASK: Video to Ascii

STARTING: 2024-09-30 10:47

ENDED: 2024-10-01 11:18

## Requirements

### opencv

```bash
sudo apt install libopencv-dev
```
## Build

```bash
g++ main.cpp $(pkg-config --cflags --libs opencv4)
```
