#set the sampling frequency 
samplingFrequency = 1000;

#create the indexes to sample at
timeInterval = 1/samplingFrequency;
signalIndex = seq(0, 1, by=timeInterval);

#define num samples as the dimention of signalIndex. here N = 1000
N = 1000

#amplitude of signal 1 
a1 = 2;  

#amplitude of signal 2 
a2 = 3;  

#frequency of signal 1 
f1 = 10; 

#frequency of signal 2
f2 = 20; 

#10 Hz Sine wave with peak amplitude 2
signal1 = a1 * sin(2 * pi * f1 * signalIndex);

#20 Hz Sine wave with peak amplitude 3
signal2 = a2 * sin(2 * pi * f2 * signalIndex);

#input signal is the sum of two signals in this case with frequencies 10 and 20 Hz
inputSignal = signal1 + signal2;

#the input signal
plot(signalIndex, inputSignal);

#perform the FFT. In this case the number of points (N) will be equal to 1000. Output will be the individual components of the FFT.
fourierComponents = fft(inputSignal);

#get the absolute value of the coefficients  
fourierCoefficients = abs(fourierComponents);

#Normalize coefficients fig 5 here N = 1000 samples so N/2 = 500
normalizedFourierComponents = fourierCoefficients / (N/2);

#get the first 50 coefficients fig 6
mainCoeffs = normalizedFourierComponents[1:50];



