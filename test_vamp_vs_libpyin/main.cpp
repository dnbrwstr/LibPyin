#include <vector>
#include <iostream>
#include <libpyincpp.h>
#include <sndfile.h>
#include <cstring>

using namespace std;

#define ARRAY_LEN(x)    ((int) (sizeof (x) / sizeof (x [0])))
#define MAX(x,y)        ((x) > (y) ? (x) : (y))
#define MIN(x,y)        ((x) < (y) ? (x) : (y))

int main(int argc, char ** argv) {
    SNDFILE *infile;
    SF_INFO sfinfo;
    float buffer[1024];
    vector<float> samples;
    sf_count_t count;
    if (argc != 3) {
        printf("\nUsage :\n\n prog <input file> <output file>\n") ;
        exit(0);
    }
 
    memset (&sfinfo, 0, sizeof (sfinfo)) ;
    if ((infile = sf_open (argv [1], SFM_READ, &sfinfo)) == NULL)     {     
        printf ("Error : Not able to open input file '%s'\n", argv [1]);
        sf_close (infile);
        exit (1) ;
    } 
  
    while ((count = sf_read_float (infile, buffer, ARRAY_LEN (buffer))) > 0) {
        for (int i=0; i<ARRAY_LEN(buffer); i++)
            samples.push_back(buffer[i]);
    } 
    sf_close (infile);
    PyinCpp my_pyin(8000, 256, 64);
    vector<float> pitches = my_pyin.feed(samples);
    for (const float pitch: pitches) {
        cout << pitch << endl;
    }
    return 0;
}
