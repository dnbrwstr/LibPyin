LibPyin pitch detection library
================================

Forked from: https://github.com/xstreck1/LibPyin

Here I will try to get the same result as VAMP plugin

**are they different?**

In my experiments yes. Check `test_vamp_vs_libpyin` folder:

```
   test_vamp_vs_libpyin$ g++ main.cpp -L"." -lLibPyin -lsndfile -std=c++11 -I/usr/include
   test_vamp_vs_libpyin$ rm f0.lst; ./a.out test.wav out.wav >> f0.lst
   test_vamp_vs_libpyin$ sonic-annotator -t pyin.n3 test.wav -w csv --csv-one-file --force f0_gt.csv
   test_vamp_vs_libpyin$ python plot_fps.py
```

![alt text](https://github.com/EliosMolina/LibPyin/raw/master/test_vamp_vs_libpyin/diff.png "Difference")

Note: blue line is result by LibPyin and black line result by sonic-annotator


LibPyin is a plug-in library for pitch (fundamental frequency) detection (see here https://en.wikipedia.org/wiki/Pitch_detection_algorithm). The library provides C++ interface for easy incorporability to projects in other languages.

The library depends on the Pyin algorithm by M. Mauch and S. Dixon. See https://code.soundsoftware.ac.uk/projects/pyin for details.

Compiling
---------
A C++11 compliant compiler is needed, however there are no additional dependencies. The repository contains [CMake](https://cmake.org/runningcmake/) and [QMake](http://doc.qt.io/qtcreator/creator-project-opening.html) files for easy compiling. 

If do not want to use either for some reason, and are making a project from the code yourself, do set the `LIBPYIN_BUILD_SHARED` macro to make sure the symbols are correcly exported.

Use
---
From C++. Include `libpyincpp.h` and link against `LibPyin`.

### Can I use LibPyin Source in My Code?
Absolutelly, just copy-paste the `source` folder to your project and add it to the include path.

 
### C++ example on Unix
    
    g++ main.cpp -L"." -lLibPyin -std=c++11
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. // Add the current location to the path so the library is loaded
    ./a.out
    

Cpp interface
-------------
_Creates a PYIN object, for each track you should create one object  
[in]sample_rate  frequency of the track, e.g. 44100 samples per second  
[in]block_size   length of a block used for obtaining a pitch, the higher the slower, 2048 is recommended  
[in]step_size    length of a step between two mined pitches, the smaller the slower, 512 is recommended_  
    
    PyinCpp(const int sample_rate, const int block_size = _DEFAULT_BLOCK_SIZE, const int step_size = _DEFAULT_STEP_SIZE);
    
_The cut off is a number between [0-1] that says whether the pitch is still to be considered as correct based on the estimate probability (the pitch will be ignored if the probability is lower than the number)_
    
    void PyinCpp::setCutOff(const float cut_off);
    float PyinCpp::getCutOff();
    
_Reserves the internal vectors for the given number of expected samples_
    
    void PyinCpp::reserve(int sample_count);
    
_Feed new data and obtain the pitches mined using the new data_

    std::vector<float> PyinCpp::feed(const std::vector<float> & new_samples);
    
_Get all the mined pitches_

    const std::vector<float> & PyinCpp::getPitches() const;

_Resets to the after-construction state_

    void PyinCpp::clear();


Licence
-------
GNU GPLv3 with attribution. The authors of Pyin ask to kindly attribute their work via a citation:

```
@inproceedings{matthias2014a,
    author = {Matthias Mauch and Dixon, Simon},
    title = {pYIN: A Fundamental Frequency Estimator Using Probabilistic Threshold Distributions},
    booktitle = {Proceedings of the IEEE International Conference on Acoustics, Speech, and Signal Processing (ICASSP 2014)},
    note = {in press},
    year = {2014}
} 
```

