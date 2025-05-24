import matplotlib.pyplot as plt


sizes_calibrated = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
exec_times_calibrated = [0.002095, 0.005199, 0.013282, 0.017152, 0.029020, 0.031459, 0.055150, 0.064267, 0.071084, 0.077574]


sizes_uncalibrated = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
exec_times_uncalibrated = [0.001113, 0.005746, 0.009911, 0.018706, 0.025266, 0.033888, 0.060307, 0.056272, 0.067918, 0.080784]

plt.figure(figsize=(12, 5))

# First graph: Calibrated
plt.subplot(1, 2, 1)
plt.plot(exec_times_calibrated, sizes_calibrated, marker='o', color='b')
plt.xlabel('Tempo de execução (s)')
plt.ylabel('Tamanho do vetor')
plt.title('Parâmetros a,b,c calibrados')
plt.grid(True)

# Second graph: Uncalibrated
plt.subplot(1, 2, 2)
plt.plot(exec_times_uncalibrated, sizes_uncalibrated, marker='o', color='r')
plt.xlabel('Tempo de execução (s)')
plt.ylabel('Tamanho do vetor')
plt.title('Parâmetros a,b,c não calibrados')
plt.grid(True)

plt.tight_layout()
plt.show()
