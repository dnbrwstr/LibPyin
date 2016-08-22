LibPyin pitch detection library
================================

Forked from: https://github.com/xstreck1/LibPyin

In this repository I've included `getSmoothedPitches()`. This pYIN output is much more useful than frame-wise F0 estimation. I've also removed C and C# implementations, since I was not interested in them.

Check `test_vamp_vs_libpyin` folder:

```
   test_vamp_vs_libpyin$ g++ main.cpp -L"." -lLibPyin -lsndfile -std=c++11 -I/usr/include
   test_vamp_vs_libpyin$ rm f0.lst; ./a.out test.wav out.wav >> f0.lst
   test_vamp_vs_libpyin$ sonic-annotator -t pyin.n3 test.wav -w csv --csv-one-file --force f0_gt.csv
   test_vamp_vs_libpyin$ python plot_fps.py
```

![alt text](https://github.com/EliosMolina/LibPyin/raw/master/test_vamp_vs_libpyin/diff.png "Difference")

Note: blue line is result by frame-wise estimation and black line is smoothed pitch contour obtained with sonic annotator.

Now, with `getSmoothedPitches()`, we obtain:
```
   test_vamp_vs_libpyin$ g++ main_smooth.cpp -L"." -lLibPyin -lsndfile -std=c++11 -I/usr/include
   test_vamp_vs_libpyin$ rm f0.lst; ./a.out test.wav out.wav >> f0.lst
   test_vamp_vs_libpyin$ sonic-annotator -t pyin.n3 test.wav -w csv --csv-one-file --force f0_gt.csv
   test_vamp_vs_libpyin$ python plot_fps.py
```

![alt_text](https://github.com/EliosMolina/LibPyin/raw/master/test_vamp_vs_libpyin/diff_smooth.png "Difference with smoothed")

Note: blue line is the result of `getSmoothedPitches()`.

More info in https://github.com/xstreck1/LibPyin

