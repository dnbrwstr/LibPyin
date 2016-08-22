import numpy as np
import matplotlib.pyplot as plt
import librosa as lr
from matplotlib.collections import LineCollection

if __name__ == "__main__":
    x, sr = lr.load("test.wav", sr=8000)
    X = 20 * np.log10(np.abs(lr.stft(x, n_fft=1024, hop_length=64)))
    f0 = np.genfromtxt("f0.lst", delimiter='\n')
    f0_gt = np.genfromtxt("f0_gt.csv", delimiter=',')
    plt.imshow(X, origin='lower')
    plt.gca().set_aspect('auto')
    plt.plot(np.maximum(0, f0_gt[:, 2]) * 1024 / 8000, c='k', lw=2)
    plt.plot(np.maximum(0, f0[:]) * 1024 / 8000, lw=1)
    plt.xlim(1500, 2400)
    plt.ylim(0, 140)
    plt.show()

